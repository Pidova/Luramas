#include "../generation.hpp"
#include "ssa\ssa_builder.hpp"

struct node_data {
      bool defines = false;
      std::vector<std::pair<luramas_register, luramas_xregister>> dests;
      luramas_registers sources;
      std::optional<boost::unordered_flat_smallpolyset<luramas_register, LURAMAS_PREDICTED_REGS>> captures;
};

generation::ssa::ssa generation::ssa::generate(se_ir &ir, const ssa_flags &f, const std::optional<boost::unordered_flat_map<std::shared_ptr<ir_stat>, luramas::ir::definitions::exprs>> &exprs, const std::optional<cfg::cfg> &ocfg) {

      /* Data */
      generation::ssa::ssa result(ir);
      std::vector<node_data> nodes;                                                                              /* Compiled node data */
      boost::unordered_flat_map<luramas_address, boost::unordered_flat_multiset<luramas_register>> capture_regs; /* Register captured at address */
      boost::unordered_flat_map<luramas_register, luramas_address /* Start */> captured_refs;                    /* Register captured by location */
      boost::unordered_flat_smallpolyset<luramas_address, LURAMAS_PREDICTED_UPVALUES> upvalue_volatile;          /* Addresses where upvalues are volatile */
      boost::unordered_flat_map<luramas_address, boost::unordered_flat_set<luramas_register>> referenced;        /* Regs that where explicitly referenced at address */

      /* Reserve */
      {
            nodes.reserve(ir.data.size());
            result.assignments.reserve(ir.data.size());
      }

      /* Map out dests and sources */
      {
            for (auto loc = LURAMAS_IR_ENTRY; loc < ir.data.size(); ++loc) {
                  node_data node;
                  const auto &i = ir.data[loc];
                  if (exprs) {
                        auto &data = exprs.value().find(i)->second;

                        /* Dests */
                        node.dests.reserve(data.lvalues_regs.size());
                        for (const auto &r : data.lvalues_regs) {
                              result.nodes[i].l.reference(r);
                              node.dests.emplace_back(std::make_pair(r, 0ull));
                        }

                        /* Sources */
                        node.sources.reserve(data.rvalues_regs.size());
                        for (const auto &r : data.rvalues_regs) {
                              result.nodes[i].r.reference(r);
                              node.sources.emplace_back(r);
                        }

                        /* Captures */
                        if (f.finclude_captures) {
                              if (i->is_volatile()) {
                                    upvalue_volatile.insert(loc);
                              }
                              for (const auto &expr : data.all) {
                                    for (const auto &c : expr->captures) {
                                          if (c->is_register_reference() && luramas::il::arch::is_op::upvalue_kind_reg_reference(c->flags.fcapture_kind)) {
                                                if (!node.captures.has_value()) {
                                                      node.captures = boost::unordered_flat_smallpolyset<luramas_register, LURAMAS_PREDICTED_REGS>();
                                                }
                                                node.captures.value().insert(c->reg);
                                                auto [it, inserted] = capture_regs.try_emplace(loc, boost::unordered_flat_multiset<luramas_register>());
                                                it->second.insert(c->reg);
                                                if (c->flags.fcapture_kind == luramas::il::arch::operand::upvalue_kind::reference) {
                                                      captured_refs.try_emplace(c->reg, loc);
                                                }
                                          }
                                    }
                                    if (expr->is_volatile()) {
                                          upvalue_volatile.insert(loc);
                                    }
                              }
                        }
                  } else {

                        /* Dests */
                        const auto dests = i->extract_ordered_dest_regs();
                        node.dests.reserve(dests.size());
                        for (const auto &r : dests) {
                              result.nodes[i].l.reference(r);
                              node.dests.emplace_back(r, 0ull);
                        }

                        /* Sources */
                        node.sources = i->extract_ordered_source_regs();
                        for (const auto &r : node.sources) {
                              result.nodes[i].r.reference(r);
                        }

                        /* Captures */
                        if (f.finclude_captures) {
                              if (i->is_volatile()) {
                                    upvalue_volatile.insert(loc);
                              }
                              for (const auto &expr : i->extract_ordered_exprs()) {
                                    for (const auto &v : expr->extract_ordered_exprs()) {
                                          for (const auto &c : v->captures) {
                                                if (c->is_register_reference() && luramas::il::arch::is_op::upvalue_kind_reg_reference(c->flags.fcapture_kind)) {
                                                      if (!node.captures.has_value()) {
                                                            node.captures = boost::unordered_flat_smallpolyset<luramas_register, LURAMAS_PREDICTED_REGS>();
                                                      }
                                                      node.captures.value().insert(c->reg);
                                                      auto [it, inserted] = capture_regs.try_emplace(loc, boost::unordered_flat_multiset<luramas_register>());
                                                      it->second.insert(c->reg);
                                                      if (c->flags.fcapture_kind == luramas::il::arch::operand::upvalue_kind::reference) {
                                                            captured_refs.try_emplace(c->reg, loc);
                                                      }
                                                }
                                          }
                                    }
                                    if (expr->is_volatile()) {
                                          upvalue_volatile.insert(loc);
                                    }
                              }
                        }
                  }

                  /* Definition */
                  if (i->is_k<keywords::definition>() && node.dests.empty()) {
                        for (const auto &[r, expr] : i->args) {
                              node.dests.emplace_back(r, 0ull);
                        }
                  }
                  nodes.emplace_back(node);
            }
      }

      /* CFG */
      auto cfg = ocfg ? *ocfg : generation::cfg::generate(ir, LURAMAS_IR_ENTRY, ir.fhas_pages);
      result.high_level_scope_id = std::move(cfg.highlevel_scope_ids);

      /* Generate */
      std::vector<luramas::ssa_builder::node> ssa_nodes;
      {
            for (auto i = LURAMAS_IR_ENTRY; i < ir.data.size(); ++i) {
                  auto &node = nodes[i];
                  const auto &stat = ir.data[i];
                  node.defines = stat->is_defines() || stat->is_k<keywords::definition>();
                  luramas::ssa_builder::node ssa_node;
                  if (node.defines) {
                        for (const auto &[r, _] : node.dests) {
                              ssa_node.lvalues.emplace_back(r);
                        }
                  }
                  if (stat->is_k<keywords::retn>() && !stat->smembers.empty() && !stat->args.empty()) {
                        std::transform(stat->args.begin(), stat->args.end(), std::back_inserter(ssa_node.locals), [](const auto &p) { return p.first; });
                  }
                  for (const auto &d : node.sources) {
                        ssa_node.rvalues.emplace_back(d);
                  }
                  ssa_nodes.emplace_back(ssa_node);
            }
      }

      auto ssa = luramas::ssa_builder::generate(ssa_nodes, cfg);
      luramas::ssa_builder::tools::global_version(ssa);

      /* Translate */
      {

            /* Lvalues */
            for (auto i = LURAMAS_IR_ENTRY; i < ssa.size(); ++i) {

                  if (i >= ir.data.size()) {
                        break;
                  }
                  const auto &lvalues = ssa[i].lvalues;
                  const auto &stat = ir.data[i];
                  auto &node = result.nodes[stat];

                  /* Reserve */
                  node.l.regs.reserve(lvalues.size());
                  node.l.assigns.reserve(lvalues.size());
                  for (const auto &[r, v] : lvalues) {

                        /* Assingments, defs */
                        node.l.assign(v, r, true);
                        result.defs.try_emplace(v, std::make_pair(stat, std::make_pair(i, std::make_pair(0u, 0u))));
                        result.assignments.insert(r);

                        /* Reference */
                        if (f.finclude_references) {
                              for (const auto &expr : stat->extract_ordered_exprs()) {
                                    if (expr->u == luramas::il::arch::data::bin_kinds::ref_ && expr->l->is_register_reference()) {
                                          referenced[i].insert(expr->l->reg);
                                    }
                              }
                        }
                  }
            }

            /* Rvalues */
            for (auto i = 0u; i < ssa.size(); ++i) {

                  if (i >= ir.data.size()) {
                        continue;
                  }
                  const auto ref_it = referenced.find(i);
                  const auto &rvalues = ssa[i].rvalues;
                  const auto &stat = ir.data[i];
                  auto &node = result.nodes[stat];

                  /* Reserve */
                  node.r.regs.reserve(rvalues.size());
                  node.r.assigns.reserve(rvalues.size());
                  for (const auto &[r, v] : rvalues) {

                        if (!v) {
                              continue;
                        }

                        /* Captures */
                        if (f.finclude_captures) {
                              if (upvalue_volatile.contains(i)) {
                                    if (const auto cit = captured_refs.find(r); cit != captured_refs.end()) {
                                          if (!luramas::ir::cfg::iterate::is::scope_visible(result.high_level_scope_id, i, cit->second)) {
                                                continue;
                                          }
                                          result.captures.insert(v.uv.begin(), v.uv.end());
                                    }
                              }
                        }

                        for (const auto &x : v.uv) {

                              /* Values */
                              if (v.k == luramas::ssa_builder::kind::phi) {
                                    if (!stat->is_k<keywords::definition>()) {
                                          result.phis.insert(x);
                                    }
                                    node.r.assign<true>(x, r, true);
                              } else {
                                    node.r.assign(x, r, true);
                              }

                              /* Unknown */
                              if (x == generation::ssa::UNKNOWN_SSA_VERSION) {
                                    result.unknown[i].insert(r);
                              }

                              /* Reg explicit reference */
                              if (f.finclude_references) {
                                    if (ref_it != referenced.end() && ref_it->second.contains(r)) {
                                          result.referenced.insert(x);
                                    }
                              }

                              /* References reg */
                              if (const auto it = result.defs.find(x); it != result.defs.end()) {
                                    if (const auto rit = node.r.refrence_regs.find(r); rit != node.r.refrence_regs.end()) {
                                          it->second.second.second.second += rit->second;
                                    }
                                    it->second.second.second.first.insert(i);
                              }

                              /* Captures */
                              if (const auto &it = capture_regs.find(i); it != capture_regs.end()) {
                                    if (const auto &mulit = it->second.find(r); mulit != it->second.end()) {
                                          it->second.erase(r);
                                          continue;
                                    }
                              }
                        }
                  }
            }
      }

      // LURAMAS_PRINTF("SSA:\n");
      // for (const auto &i : ir.data) {
      //       const auto s = result.nodes[i];
      //       const auto &str = i->str();
      //       if (!str.empty()) {
      //             LURAMAS_PRINTF("%s", str.c_str());
      //             for (const auto &p : s.l.assigns) {
      //                   if (p.second.first == generation::ssa::assignment_kind::single) {
      //                         LURAMAS_PRINTF("(L)SSA(%hu) ", p.first);
      //                   } else {
      //                         LURAMAS_PRINTF("(L)PHI(%hu) ", p.first);
      //                   }
      //                   for (const auto &r : p.second.second) {
      //                         LURAMAS_PRINTF("R%llu ", r);
      //                   }
      //             }
      //             for (const auto &p : s.r.assigns) {
      //                   if (p.second.first == generation::ssa::assignment_kind::single) {
      //                         LURAMAS_PRINTF("(R)SSA(%hu) ", p.first);
      //                   } else {
      //                         LURAMAS_PRINTF("(R)PHI(%hu) ", p.first);
      //                   }
      //                   for (const auto &r : p.second.second) {
      //                         LURAMAS_PRINTF("R%llu ", r);
      //                   }
      //             }
      //             LURAMAS_PRINTF("\n");
      //       }
      // }
      //std::cin.get();
      //LURAMAS_PRINTF("============\n");
      //std::cin.get();
      //int idx = 0;
      //std::printf("SSA:\n");
      //for (const auto &i : ir.data) {
      //      const auto s = result.nodes[i];
      //      const auto &str = i->str();
      //      if (!str.empty()) {
      //            std::printf("%s", str.c_str());
      //            for (const auto &p : s.l.assigns) {
      //                  if (p.second.first == generation::ssa::assignment_kind::single) {
      //                        std::printf("(L)SSA(%hu) ", p.first);
      //                  } else {
      //                        std::printf("(L)PHI(%hu) ", p.first);
      //                  }
      //                  for (const auto &r : p.second.second) {
      //                        std::printf("R%llu ", r);
      //                  }
      //            }
      //            for (const auto &p : s.r.assigns) {
      //                  if (p.second.first == generation::ssa::assignment_kind::single) {
      //                        std::printf("(R)SSA(%hu) ", p.first);
      //                  } else {
      //                        std::printf("(R)PHI(%hu) ", p.first);
      //                  }
      //                  for (const auto &r : p.second.second) {
      //                        std::printf("R%llu ", r);
      //                  }
      //            }
      //            std::printf("\n");
      //      }
      //
      //}
      //  std::printf("============\n");
      //luramas::debug::copy_to_clipboard(luramas::ir::cfg::compute::graphviz(ir, cfg));
      //std::cin.get();
      //printf("SSA PRINT\n");
      //std::ostringstream oss;
      //for (const auto &i : ir.data) {
      //      const auto s = result.nodes[i];
      //      const auto &str = i->str();
      //      if (!str.empty()) {
      //            oss << str;
      //            for (const auto &p : s.l.assigns) {
      //                  if (p.second.first == generation::ssa::assignment_kind::single) {
      //                        oss << "(L)SSA(" << p.first << ") ";
      //                  } else {
      //                        oss << "(L)PHI(" << p.first << ") ";
      //                  }
      //                  for (const auto &r : p.second.second) {
      //                        oss << "R" << r << " ";
      //                  }
      //            }
      //            for (const auto &p : s.r.assigns) {
      //                  if (p.second.first == generation::ssa::assignment_kind::single) {
      //                        oss << "(R)SSA(" << p.first << ") ";
      //                  } else {
      //                        oss << "(R)PHI(" << p.first << ") ";
      //                  }
      //                  for (const auto &r : p.second.second) {
      //                        oss << "R" << r << " ";
      //                  }
      //            }
      //            oss << '\n';
      //      }
      //}
      //printf("Printed SSA form\n");
      //oss << "=======kkkkk=====\n";
      //luramas::debug::copy_to_clipboard(oss.str());
      //std::cin.get();

#ifdef DEBUG
      //LURAMAS_PRINTF("SSA:\n");
      //for (const auto &i : ir.data) {
      //      const auto s = result.nodes[i];
      //      const auto &str = i->str();
      //      if (!str.empty()) {
      //            LURAMAS_PRINTF("%s", str.c_str());
      //            for (const auto &p : s.l.assigns) {
      //                  if (p.second.first == generation::ssa::assignment_kind::single) {
      //                        LURAMAS_PRINTF("(L)SSA(%hu) ", p.first);
      //                  } else {
      //                        LURAMAS_PRINTF("(L)PHI(%hu) ", p.first);
      //                  }
      //                  for (const auto &r : p.second.second) {
      //                        LURAMAS_PRINTF("R%llu ", r);
      //                  }
      //            }
      //            for (const auto &p : s.r.assigns) {
      //                  if (p.second.first == generation::ssa::assignment_kind::single) {
      //                        LURAMAS_PRINTF("(R)SSA(%hu) ", p.first);
      //                  } else {
      //                        LURAMAS_PRINTF("(R)PHI(%hu) ", p.first);
      //                  }
      //                  for (const auto &r : p.second.second) {
      //                        LURAMAS_PRINTF("R%llu ", r);
      //                  }
      //            }
      //            LURAMAS_PRINTF("\n");
      //      }
      //}
      //std::printf("DEFS:\n");
      //for (const auto &[reg, data] : result.defs) {
      //      data.first->dump("ASGN");
      //      std::cout << "SSA REG " << reg << std::endl;
      //      for (const auto &o : data.second.second) {
      //            ir.data[o]->dump("  ");
      //      }
      //}
      // std::cin.get();
#endif
      return result;
}