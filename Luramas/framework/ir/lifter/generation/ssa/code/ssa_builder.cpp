#include "../ssa_builder.hpp"
//#define LURAMAS_DEBUG_SSA_STEPS 1

namespace luramas::ssa_builder {

      ssa_rv_reg::operator bool() const {
            return this->fvalid;
      }

      std::pair<luramas_flag, std::string> ssa_node::str() const {
            std::ostringstream oss;

            /* Lvalues */
            oss << "lvalues: ";
            for (const auto &[r, v] : this->lvalues) {
                  oss << "r(" << r << "): " << v << " ";
            }
            oss << "\n";

            luramas_flag fhas_data = !this->lvalues.empty();

            /* Rvalues */
            oss << "rvalues:\n";
            for (const auto &[reg, sreg] : this->rvalues) {

                  oss << "  r(" << reg << ") ";
                  if (sreg.k == kind::scalar) {
                        oss << "scalar(";
                        for (const auto &v : sreg.v) {
                              oss << v << " ";
                        }
                        oss << ")";
                  } else if (sreg.k == kind::phi) {
                        oss << "phi(";
                        for (const auto &v : sreg.v) {
                              oss << v << " ";
                        }
                        oss << ")";
                  }
                  oss << "\n";
            }
            if (!fhas_data) {
                  fhas_data = !this->rvalues.empty();
            }
            return {fhas_data, oss.str()};
      }

      std::vector<ssa_node> generate(const std::vector<node> &nodes, const generation::cfg::cfg &cfg) {

            std::vector<ssa_node> result;
            boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, boost::unordered_flat_set<luramas_register>> phi_nodes;
            boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, luramas_index>> phi_predecessor_idx;

            /* Adjust */
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Adjust\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  result.resize(nodes.size());
                  phi_nodes.reserve(cfg.blocks.size());
                  phi_predecessor_idx.reserve(cfg.blocks.size());
            }

#ifdef LURAMAS_DEBUG_SSA_STEPS
            std::printf("IDOM Generation\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

            const auto idoms = luramas::ir::cfg::compute::immediate_dominators(cfg);
            const auto df = luramas::ir::cfg::compute::dominance_frontier(cfg, idoms);
            const auto dom_tree = luramas::ir::cfg::compute::dominator_tree(idoms);

            /* Place phis */
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Placing Phis\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  /* Def blocks */
                  boost::unordered_flat_map<luramas_register, boost::unordered_map<std::shared_ptr<generation::cfg::block>, luramas_address>> def_blocks;
                  for (const auto &b : cfg.blocks) {
                        for (const auto &i : b->get_iter()) {
                              for (const auto &r : nodes[i].lvalues) {
                                    def_blocks[r][b] = i;
                              }
                        }
                  }

                  std::vector<std::shared_ptr<generation::cfg::block>> worklist;
                  boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> has_already;
                  boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> ever_on_worklist;
                  std::vector<std::shared_ptr<generation::cfg::block>> sorted_defs;
                  has_already.reserve(cfg.blocks.size());
                  ever_on_worklist.reserve(cfg.blocks.size());
                  for (const auto &[v, defs] : def_blocks) {

                        has_already.clear();
                        ever_on_worklist.clear();
                        worklist.clear();
                        sorted_defs.clear();

                        /* Sort before inserting */
                        {
                              for (const auto &[x, idx] : defs) {
                                    sorted_defs.push_back(x);
                              }

                              std::sort(sorted_defs.begin(), sorted_defs.end(), [](const auto &a, const auto &b) {
                                    return a->get_front() < b->get_front();
                              });
                              for (const auto &x : sorted_defs) {
                                    ever_on_worklist.insert(x);
                                    worklist.emplace_back(x);
                              }
                        }

                        while (!worklist.empty()) {

                              const auto x = worklist.back();
                              worklist.pop_back();

                              const auto df_it = df.find(x);
                              if (df_it == df.end()) {
                                    continue;
                              }
                              for (const auto &y : df_it->second) {

                                    if (!cfg.predecessors.contains(y)) {
                                          continue;
                                    }
                                    if (!has_already.insert(y).second) {
                                          continue;
                                    }
                                    if (phi_nodes[y].insert(v); ever_on_worklist.insert(y).second) {
                                          worklist.emplace_back(y);
                                    }
                              }
                        }
                  }
            }

            /* Placeholder phis */
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Placeholders\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  for (auto const &[b, vars] : phi_nodes) {

                        auto &host = result[b->get_front()];
                        const auto pit = cfg.predecessors.find(b);
                        if (pit == cfg.predecessors.end()) {
                              continue;
                        }
                        for (const auto &v : vars) {

                              host.lvalues[v] = generation::ssa::UNKNOWN_SSA_VERSION;
                              auto &r = host.rvalues[v];
                              r.k = kind::phi;
                              r.fset_unknown = true;
                              r.v.assign(pit->second.size(), generation::ssa::UNKNOWN_SSA_VERSION);
                        }
                  }
            }

            /* Index preds */
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Indexing Preds\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  for (const auto &[block, preds] : cfg.predecessors) {

                        std::vector<std::shared_ptr<generation::cfg::block>> sorted_preds(preds.begin(), preds.end());
                        std::sort(sorted_preds.begin(), sorted_preds.end(), [](const auto &a, const auto &b) {
                              return a->get_front() < b->get_front();
                        });

                        luramas_index idx = 0u;
                        for (const auto &p : sorted_preds) {
                              phi_predecessor_idx[block][p] = idx++;
                        }
                  }
            }

            /* Rename */
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Renaming\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  enum class visit_state : std::uint8_t {
                        ENTER,
                        EXIT
                  };

                  boost::unordered_flat_map<luramas_register, luramas_xregister> counters;
                  boost::unordered_flat_map<luramas_register, luramas_xregisters> stacks;

                  const auto gen_name = [&](const auto v) {
                        const auto i = ++(counters[v]);
                        stacks.try_emplace(v, luramas_xregisters()).first->second.emplace_back(i);
                        return i;
                  };

                  boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> visited;
                  std::vector<std::pair<std::shared_ptr<generation::cfg::block>, visit_state>> worklist;
                  worklist.emplace_back(cfg.entry, visit_state::ENTER);

                  while (!worklist.empty()) {

                        const auto [block, state] = worklist.back();
                        worklist.pop_back();
                        if (state == visit_state::ENTER) {

                              /* Already visited */
                              if (!visited.insert(block).second) {
                                    continue;
                              }

                              /* Clean up */
                              worklist.emplace_back(block, visit_state::EXIT);

                              /* Init phi nodes */
                              if (auto phi_vars_it = phi_nodes.find(block); phi_vars_it != phi_nodes.end()) {

                                    auto &first_node = result[block->get_front()];
                                    for (const auto &var : phi_vars_it->second) {

                                          first_node.lvalues[var] = gen_name(var);
                                          auto &rval = first_node.rvalues[var];
                                          rval.k = kind::phi;
                                    }
                              }

                              /* Rename */
                              for (const auto &i : block->get_iter()) {

                                    auto &res_stat = result[i];
                                    const auto &stat = nodes[i];
                                    for (const auto &v : stat.rvalues) {

                                          auto &r = res_stat.rvalues[v];
                                          if (r.k == kind::phi) {
                                                continue;
                                          }
                                          r.k = kind::scalar;
                                          if (const auto it = stacks.find(v); it != stacks.end() && !it->second.empty()) {
                                                r.v = {it->second.back()};
                                          } else {
                                                r.v = {generation::ssa::UNKNOWN_SSA_VERSION};
                                          }
                                          r.fset_unknown = (r.v.back() == generation::ssa::UNKNOWN_SSA_VERSION);
                                    }
                                    for (const auto &v : stat.lvalues) {
                                          result[i].lvalues[v] = gen_name(v);
                                    }

                                    /* Fake version for it let it be removed later */
                                    for (const auto &v : stat.locals) {
                                          gen_name(v);
                                    }
                              }

                              /* Place phi defs */
                              for (const auto &y : block->get_block_successors()) {

                                    /* Phis */
                                    const auto phi_vars_it = phi_nodes.find(y);
                                    if (phi_vars_it == phi_nodes.end()) {
                                          continue;
                                    }

                                    /* Y pred index */
                                    const auto pred_idx_it = phi_predecessor_idx.find(y);
                                    if (pred_idx_it == phi_predecessor_idx.end()) {
                                          continue;
                                    }

                                    /* Pred mapped block */
                                    const auto pred_map_it = pred_idx_it->second.find(block);
                                    if (pred_map_it == pred_idx_it->second.end()) {
                                          continue;
                                    }

                                    /* Place j as phi def */
                                    const auto j = pred_map_it->second;
                                    auto &succ_phi_host_node = result[y->get_front()];
                                    for (const auto &v : phi_vars_it->second) {

                                          const auto phi_r_it = succ_phi_host_node.rvalues.find(v);
                                          if (phi_r_it == succ_phi_host_node.rvalues.end()) {
                                                continue;
                                          }

                                          const auto stack_it = stacks.find(v);
                                          const auto sval = (stack_it != stacks.end() && !stack_it->second.empty()) ? stack_it->second.back() : generation::ssa::UNKNOWN_SSA_VERSION;
                                          phi_r_it->second.v[j] = sval;
                                          phi_r_it->second.fset_unknown |= (sval == generation::ssa::UNKNOWN_SSA_VERSION);
                                    }
                              }

                              /* Walk dom tree */
                              if (auto it = dom_tree.find(block); it != dom_tree.end()) {
                                    std::vector<std::shared_ptr<generation::cfg::block>> sorted_children(it->second.begin(), it->second.end());
                                    std::sort(sorted_children.begin(), sorted_children.end(), [](const auto &a, const auto &b) {
                                          return a->get_front() < b->get_front();
                                    });
                                    for (const auto &child : sorted_children) {
                                          worklist.emplace_back(child, visit_state::ENTER);
                                    }
                              }
                              continue;
                        }

                        /* Pop stacks */
                        {
                              /* Pop instruction lvalue first */
                              for (auto i = block->get_end(); i > block->get_front(); --i) {

                                    for (const auto &v : nodes[i - 1u].lvalues) {
                                          if (auto it = stacks.find(v); it != stacks.end() && !it->second.empty()) {
                                                it->second.pop_back();
                                          }
                                    }

                                    /* Pop locals that were pushed during the rename phase to prevent stack leaks */
                                    for (const auto &v : nodes[i - 1u].locals) {
                                          if (auto it = stacks.find(v); it != stacks.end() && !it->second.empty()) {
                                                it->second.pop_back();
                                          }
                                    }
                              }

                              /* Pop phi lvalues */
                              if (auto phi_vars_it = phi_nodes.find(block); phi_vars_it != phi_nodes.end()) {
                                    for (const auto &v : phi_vars_it->second) {
                                          if (auto it = stacks.find(v); it != stacks.end() && !it->second.empty()) {
                                                it->second.pop_back();
                                          }
                                    }
                              }
                        }
                  }
            }

            /* Clean up */
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Cleaning up\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  for (auto i = LURAMAS_IR_ENTRY; i < result.size(); ++i) {

                        auto &ssa_n = result[i];
                        const auto &orig_node = nodes[i];

                        boost::unordered_flat_set<luramas_register> orig_lvalues(orig_node.lvalues.begin(), orig_node.lvalues.end());
                        boost::unordered_flat_set<luramas_register> orig_rvalues(orig_node.rvalues.begin(), orig_node.rvalues.end());

                        /* Lvalues */
                        for (auto it = ssa_n.lvalues.begin(); it != ssa_n.lvalues.end();) {
                              if (const auto rit = ssa_n.rvalues.find(it->first); rit != ssa_n.rvalues.end() && rit->second.k == kind::phi) {
                                    ++it;
                                    continue;
                              }
                              if (!orig_lvalues.contains(it->first)) {
                                    it = ssa_n.lvalues.erase(it);
                              } else {
                                    ++it;
                              }
                        }

                        /* Rvalues */
                        for (auto it = ssa_n.rvalues.begin(); it != ssa_n.rvalues.end();) {
                              if (it->second.k == kind::phi) {
                                    ++it;
                                    continue;
                              }
                              if (!orig_rvalues.contains(it->first)) {
                                    it = ssa_n.rvalues.erase(it);
                                    continue;
                              }
                              ++it;
                        }

                        /* Remove no unknowns */
                        for (auto &[_, nssa] : ssa_n.rvalues) {
                              if (!nssa.fset_unknown || nssa.k == kind::phi) {
                                    nssa.v.erase(std::remove(nssa.v.begin(), nssa.v.end(), generation::ssa::UNKNOWN_SSA_VERSION), nssa.v.end());
                              }
                        }
                  }
            }

            /* Prune */
            {

#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Pruning\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  boost::unordered_flat_map<luramas_register, boost::unordered_flat_set<luramas_xregister>> used_versions;

                  /* Get */
                  for (const auto &ssa_n : result) {
                        for (const auto &[reg, value] : ssa_n.rvalues) {
                              auto &s = used_versions[reg];
                              s.reserve(value.v.size());
                              s.insert(value.v.begin(), value.v.end());
                        }
                  }

                  bool changed = true;
                  while (changed) {
                        changed = false;

                        for (auto &ssa_n : result) {
                              for (auto it = ssa_n.lvalues.begin(); it != ssa_n.lvalues.end();) {

                                    const auto [reg, def_ver] = *it;

                                    /* Lvalue phi? */
                                    const auto r_it = ssa_n.rvalues.find(reg);
                                    if (r_it == ssa_n.rvalues.end() || r_it->second.k != kind::phi) {
                                          ++it;
                                          continue;
                                    }

                                    const auto &phi_vec = r_it->second.v;

                                    /* Get unique phi not self */
                                    auto target_val = def_ver;
                                    for (const auto &val : phi_vec) {
                                          if (val != def_ver) {
                                                target_val = val;
                                                break;
                                          }
                                    }

                                    /* If the phi only references itself, it represents an uninitialized or dead loop value.
                                       We must substitute it with UNKNOWN_SSA_VERSION to avoid leaving dangling references downstream. */
                                    if (target_val == def_ver) {
                                          target_val = generation::ssa::UNKNOWN_SSA_VERSION;
                                    }

                                    /* A phi is trivial if all operands are either the target_val or the phi itself */
                                    luramas_flag ftrivial = true;
                                    for (const auto &val : phi_vec) {
                                          if (val != def_ver && val != target_val) {
                                                ftrivial = false;
                                                break;
                                          }
                                    }

                                    /* Never pruyne a phi with unfilled slots */
                                    if (ftrivial && r_it->second.fset_unknown) {
                                          ftrivial = false;
                                    }

                                    if (ftrivial) {

                                          /* Propagate actual value to all downstream uses before erasing */
                                          if (target_val != def_ver) {
                                                for (auto &scan_node : result) {
                                                      if (auto scan_r = scan_node.rvalues.find(reg);
                                                          scan_r != scan_node.rvalues.end()) {
                                                            for (auto &v_val : scan_r->second.v) {
                                                                  if (v_val == def_ver) {
                                                                        v_val = target_val;
                                                                        changed = true;
                                                                  }
                                                            }
                                                      }
                                                }
                                          }
                                          it = ssa_n.lvalues.erase(it);
                                          ssa_n.rvalues.erase(reg);
                                          changed = true;
                                          continue;
                                    }
                                    ++it;
                              }
                        }
                  }
            }

            /* Uv rvalues */
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Uvs\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  for (auto &n : result) {
                        for (auto &[_, r] : n.rvalues) {
                              r.uv.reserve(r.v.size());
                              r.uv.insert(r.v.begin(), r.v.end());
                        }
                  }
            }

            /* Map */
            struct mapped {
                  boost::unordered_flat_set<luramas_register> l;
                  boost::unordered_flat_set<luramas_register> r;
            };
            std::vector<mapped> map;
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Maping");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  map.resize(result.size());
                  for (auto i = LURAMAS_IR_ENTRY; i < result.size(); ++i) {

                        auto &m = map[i];
                        const auto &og = nodes[i];
                        m.l.reserve(og.lvalues.size());
                        m.l.insert(og.lvalues.begin(), og.lvalues.end());
                        m.r.reserve(og.rvalues.size());
                        m.r.insert(og.rvalues.begin(), og.rvalues.end());
                  }
            }

            /* Cleanup */
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Cleanup\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  for (auto i = LURAMAS_IR_ENTRY; i < result.size(); ++i) {

                        auto &node = result[i];
                        const auto &og = map[i];

                        /* Lvalues (Very rare to have really any invalid lvalues) */
                        for (auto it = node.lvalues.begin(); it != node.lvalues.end();) {
                              if (!og.l.contains(it->first)) {

                                    /* Keep it if it is a phi lvalue, propagation needs it */
                                    if (const auto r_it = node.rvalues.find(it->first); r_it != node.rvalues.end() && r_it->second.k == kind::phi) {
                                          ++it;
                                          continue;
                                    }

                                    it = node.lvalues.erase(it);
                                    continue;
                              }
                              ++it;
                        }

                        /* Rvalues (mark) */
                        for (auto &[r, d] : node.rvalues) {
                              if (d.k == kind::phi || og.r.contains(r)) {
                                    continue;
                              }
                              d.fvalid = false;
                        }
                  }
            }

            /* Propagate phis */
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Propagating Phis\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  /* Map Rvalue SSA to address {ssa_target_reg, {target_version, addresses}} */
                  boost::unordered_flat_map<luramas_register, boost::unordered_flat_map<luramas_xregister, boost::unordered_flat_set<luramas_address>>> rssa_addr;
                  rssa_addr.reserve(result.size());
                  for (auto i = LURAMAS_IR_ENTRY; i < result.size(); ++i) {
                        for (const auto &[reg, ssar] : result[i].rvalues) {
                              for (const auto &r : ssar.uv) {
                                    rssa_addr[reg][r].insert(i);
                              }
                        }
                  }

                  /* 
                    Gather all internal/synthetic phi definitions that need propagation
                    Format: { address, vector<{ register, ssa_version, source_versions }> }
                  */
                  std::vector<std::pair<luramas_address, std::vector<std::tuple<luramas_register, luramas_xregister, boost::unordered_flat_set<luramas_xregister>>>>> pending_phi_props;

                  for (auto maddr = LURAMAS_IR_ENTRY; maddr < result.size(); ++maddr) {
                        const auto &node = result[maddr];
                        const auto &m = map[maddr];
                        std::vector<std::tuple<luramas_register, luramas_xregister, boost::unordered_flat_set<luramas_xregister>>> local_phis;

                        for (const auto &[v, x] : node.lvalues) {
                              /* If our SSA contains an Lvalue not present in the original program, it's a synthetic phi */
                              if (!m.l.contains(v)) {
                                    if (const auto it = node.rvalues.find(v); it != node.rvalues.end() && it->second.k == kind::phi) {
                                          local_phis.emplace_back(v, x, it->second.uv);
                                    }
                              }
                        }
                        if (!local_phis.empty()) {
                              pending_phi_props.emplace_back(maddr, std::move(local_phis));
                        }
                  }

                  /* Propagate using a worklist/changed approach to handle cascading dependencies safely */
                  bool phi_changed = true;
                  while (phi_changed) {
                        phi_changed = false;

                        for (const auto &[maddr, phis] : pending_phi_props) {
                              for (const auto &[r, target_version, _] : phis) {

                                    /* Live lookup  picks up versions deposited by earlier phis
                                       in the same or prior iterations, fixing cascade failures */
                                    const auto live_phi = result[maddr].rvalues.find(r);
                                    if (live_phi == result[maddr].rvalues.end()) {
                                          continue;
                                    }

                                    const auto source_versions = live_phi->second.uv;

                                    auto &curr_ver_map = rssa_addr[r];
                                    const auto it = curr_ver_map.find(target_version);
                                    if (it == curr_ver_map.end()) {
                                          continue;
                                    }

                                    const auto target_addresses = it->second;

                                    /* Erase the mapping now that we are resolving this synthetic version */
                                    curr_ver_map.erase(it);

                                    for (const auto &use_addr : target_addresses) {
                                          auto &use_node = result[use_addr].rvalues[r];

                                          if (use_node.k != kind::phi) {
                                                use_node.k = kind::phi;
                                                phi_changed = true;
                                          }

                                          /* Erase the intermediate target version from the use node 
                                             so it gets cleanly replaced by the actual source versions */
                                          if (use_node.uv.erase(target_version)) {
                                                phi_changed = true;
                                          }

                                          for (const auto &x : source_versions) {
                                                if (x != target_version) {
                                                      if (use_node.uv.insert(x).second) {
                                                            curr_ver_map[x].insert(use_addr);
                                                            phi_changed = true;
                                                      }
                                                }
                                          }
                                    }
                              }
                        }
                  }

                  /* Cleanup the synthetic definitions now that values have safely reached their final targets */
                  for (const auto &[maddr, phis] : pending_phi_props) {
                        auto &node = result[maddr];
                        for (const auto &[r, target_version, _] : phis) {
                              node.lvalues.erase(r);
                              if (!map[maddr].r.contains(r)) {
                                    node.rvalues.erase(r);
                              }
                        }
                  }
            }

            /* More agrressive cleanup */
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Agressive Cleanup\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  for (auto i = LURAMAS_IR_ENTRY; i < result.size(); ++i) {

                        auto &node = result[i];
                        const auto &og = map[i];

                        /* Rvalues */
                        for (auto it = node.rvalues.begin(); it != node.rvalues.end();) {
                              if (!og.r.contains(it->first)) {
                                    it = node.rvalues.erase(it);
                                    continue;
                              }
                              ++it;
                        }
                  }
            }

            /* Reinit Uv rvalues */
            {
#ifdef LURAMAS_DEBUG_SSA_STEPS
                  std::printf("Reinit\n");
#endif // LURAMAS_DEBUG_SSA_STEPS

                  for (auto &n : result) {
                        for (auto &[_, r] : n.rvalues) {

                              r.v.clear();
                              r.v.reserve(r.uv.size());
                              r.v.insert(r.v.begin(), r.uv.begin(), r.uv.end());
                        }
                  }

                  for (auto &n : result) {
                        for (auto &[_, sreg] : n.rvalues) {

                              sreg.uv.insert(sreg.v.begin(), sreg.v.end());
                        }
                  }
            }
            return result;
      }

} // namespace luramas::ssa_builder