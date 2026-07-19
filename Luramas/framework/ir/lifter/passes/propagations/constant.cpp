#include "../includes/common.hpp"

namespace luramas::ir::passes {

      namespace analyze {

            /* Is expr basic enough to propgate without side effects no matter reference count? */
            bool propable_basic(const std::shared_ptr<ir_stat::ir_expr> &expr) {

                  const auto curr = tools::exprs::values::is_cast(expr) ? expr->l : expr;
                  return curr && (curr->is_primitive() || curr->is_register_reference() || tools::exprs::values::is_stack(curr));
            }

            /* Helpers for constant propagation or other promotions */
            void helpers(pass_manager &pm, shared &s, generation::ssa::ssa &ssa, const generation::cfg::cfg &cfg) {

                  if (pm.env_flags.fhas_types) {
                        if (pm.env_flags.fallow_definition_cast) {
                              passes::definition_types(pm, s);
                        }
                        passes::dead_type_elimination(pm, s, ssa);
                        if (pm.env_flags.fhas_pages) {
                              if (pm.env_flags.fremove_page_dead_args) {
                                    passes::dead_page_definition_elimination(pm, s, ssa);
                              }
                        }
                  }
                  if (pm.env_flags.fremove_main_dead_args) {
                        passes::dead_main_definition_elimination(pm, s, ssa);
                  }
                  passes::instruction_hoisting(pm, s, ssa);
                  passes::instruction_scheduling(pm, s, ssa);
                  if (pm.env_flags.feliminate_flags) {
                        /* Clear values because other passes may have changed up values */
                        pm.processed.values.clear();
                        passes::flag_optimization(pm, s);
                  }
                  return;
            }
      } // namespace analyze

      void constant_propagation(pass_manager &pm, shared &s) {

            boost::unordered_flat_set<luramas_xregister> packed;
            boost::unordered_flat_set<std::shared_ptr<ir_stat>> propagation_targets;

            luramas::ir::pass::process::values(pm);

            /* Inline data before hand */
            if (s.ffirst_const_prop) {
                  passes::inline_functions(pm, s);
            }

            const auto cfg = generation::cfg::generate(pm.ir, LURAMAS_IR_ENTRY, pm.ir.fhas_pages);
            auto ssa = generation::ssa::generate(pm.ir, generation::ssa::ssa_flags({.finclude_captures = true, .finclude_references = pm.env_flags.fhas_references}), pm.processed.values, cfg);

            for (auto i = pm.amount(); i > 0; --i) {

                  const auto &p = pm[i - 1u];

                  packed.clear();
                  auto &rssa = ssa.nodes[p];
                  for (const auto &r : rssa.r.regs) {

                        const auto &[assignment, data] = rssa.r.assigns[r];
                        const auto &tssa = *data.begin();
                        const auto is_phi = ssa.phis.contains(tssa);
                        if (data.size() != 1u || tssa == generation::ssa::UNKNOWN_SSA_VERSION) {
                              continue;
                        }

                        const auto &past = ssa.defs[tssa];
                        if (!past.first->is_data_assignment() || past.first->flags.finternal_store || tools::stat::is_definition(p)) {
                              continue;
                        }

                        const auto ref_count = rssa.r.refrence_regs[r];
                        const auto is_phi_not_primitive_complex = is_phi && ((!past.first->r->is_primitive()) || (assignment == generation::ssa::assignment_kind::phi && tools::stat::future(i, past.second.first)));
                        const auto is_phi_not_complex_reg_cast = is_phi && tools::exprs::values::types::is_reg_cast(past.first->r) && past.second.second.first.size() == 2u && past.second.second.first.contains(past.second.first) && tools::stat::future(past.second.first, i);

                        /* Ignore packed, references, and pasts */
                        if ((!is_phi_not_complex_reg_cast && is_phi_not_primitive_complex) || packed.contains(tssa) || ssa.referenced.contains(tssa) || !ssa.defs.contains(tssa) || pm.is_removed(p)) {
                              continue;
                        }

                        propagation_targets.clear();

                        /* Check if propagations are possible */
                        const auto is_unsafe = !pm.is_safe(past.first);
                        const auto is_captured = ssa.captures.contains(tssa);
                        auto is_complex_non_primitive = !is_phi_not_complex_reg_cast && (past.second.second.first.size() > 1u || ref_count > 1u) && !analyze::propable_basic(past.first->r);
                        if (is_complex_non_primitive && !pm.fpmut) {

                              /* FOLDS, (REG ARITH INT) */
                              const auto folds = tools::propagations::constant_folds(pm, ssa, tssa);
                              is_complex_non_primitive = !(folds && (folds == ref_count || folds + 1u == ref_count) && tools::exprs::values::is_general_purpose_register(past.first->r->l));
                        }
                        const auto is_table_assign_conflict = p->is_k<keywords::table_assign>() && p->l && p->l->l == past.first->l && past.first->r && tools::exprs::values::is_table(past.first->r);
                        const auto is_volatile_or_table_assign = past.first->flags.fvolatile || past.first->is_k<keywords::table_assign>();
                        const auto is_first_const_prop_with_table = s.ffirst_const_prop && past.first->r && tools::exprs::values::is_table(past.first->r);
                        const auto is_future_use = past.second.first > i;
                        if (is_unsafe || (is_complex_non_primitive && (!pm.env_flags.options.opropagation_exception || !pm.env_flags.options.opropagation_exception(past.first))) || is_captured || is_table_assign_conflict ||
                            is_volatile_or_table_assign || is_first_const_prop_with_table || is_future_use) {

                              // LURAMAS_PRINTF("REG %s\n", std::to_string(r).c_str());
                              // if (is_unsafe) {
                              //       LURAMAS_PRINTF("is_unsafe %d\n", is_unsafe);
                              // }
                              // if (is_captured) {
                              //       LURAMAS_PRINTF("is_captured %d\n", is_captured);
                              // }
                              // if (is_complex_non_primitive) {
                              //       LURAMAS_PRINTF("is_complex_non_primitive %d\n", is_complex_non_primitive);
                              // }
                              // if (is_table_assign_conflict) {
                              //       LURAMAS_PRINTF("is_table_assign_conflict %d\n", is_table_assign_conflict);
                              // }
                              // if (is_volatile_or_table_assign) {
                              //       LURAMAS_PRINTF("is_volatile_or_table_assign %d\n", is_volatile_or_table_assign);
                              // }
                              // if (is_first_const_prop_with_table) {
                              //       LURAMAS_PRINTF("is_first_const_prop_with_table %d\n", is_first_const_prop_with_table);
                              // }
                              // if (is_future_use) {
                              //       LURAMAS_PRINTF("is_future_use %d\n", is_future_use);
                              // }
                              continue;
                        }

                        if (past.first->r && past.first->is_k<keywords::assignment>() && (rssa.r.regs.count(r) == 1u || !past.first->r->is_tk<tkind::nothing>() || past.first->r->is_register_reference())) {

                              /* Check if set and past it is used as an upvalue */
                              bool pass = true;
                              bool pack = false;
                              const auto &dests = ssa.nodes[past.first].l.regs;
                              if (dests.size() > 1u) {

                                    pass = pm.env_flags.fcan_pack_registers;
                                    if (pass) {
                                          /* Extract regs from lists */
                                          luramas_registers dest_list;
                                          std::vector<luramas_registers> list;

                                          for (const auto &l : p->extract_list()) {
                                                if (const auto regs = tools::exprs::extractions::register_references(l); !regs.empty()) {
                                                      list.emplace_back(std::move(regs));
                                                }
                                          }
                                          tools::exprs::extractions::register_references(past.first->members, dest_list);

                                          /* Make sure list is contigious */
                                          pass = std::any_of(list.begin(), list.end(), [&](const auto &list_vec) {
                                                if (dest_list.size() > list_vec.size()) {
                                                      return false;
                                                }
                                                return std::search(list_vec.begin(), list_vec.end(), dest_list.begin(), dest_list.end()) != list_vec.end();
                                          });

                                          /* Make sure every dest is propagatable */
                                          boost::unordered_flat_set<luramas_register> packables;
                                          boost::unordered_flat_set<luramas_xregister> packed_ssa;
                                          auto &dssa = ssa.nodes[past.first].l;
                                          if (pass) {
                                                for (const auto &d : dest_list) {
                                                      if (!rssa.r.regs.contains(d)) {
                                                            pass = false;
                                                            break;
                                                      }
                                                      const auto dlssa = *dssa.assigns[d].second.begin();
                                                      if (!ssa.defs.contains(dlssa) || ssa.phis.contains(dlssa)) {
                                                            pass = false;
                                                            break;
                                                      }
                                                      if (ssa.defs[dlssa].second.second.first.size() > 1u) {
                                                            pass = false;
                                                            break;
                                                      }
                                                      if (d != r) {
                                                            packed_ssa.insert(dlssa);
                                                            packables.insert(d);
                                                      }
                                                }
                                          }

                                          /* Ignore if dupes */
                                          if (pass) {
                                                for (const auto &r : packed_ssa) {
                                                      if (ssa.defs[r].second.second.second > 1u) {
                                                            pass = false;
                                                            break;
                                                      }
                                                }
                                          }

                                          /* Propagate packables */
                                          if (pass) {
                                                pass = pm.is_safe(past.first) && !std::any_of(packables.begin(), packables.end(), [&](const auto &w) { return p->propagate_violates(w) || luramas::ir::tools::mutates(pm, w, past.second.first + 1u, i - 1u); });
                                                if (pass) {
                                                      pack = true;
                                                      bool clonable = false;
                                                      for (const auto &w : packables) {
                                                            p->propagate(w, nullptr, clonable);
                                                      }
                                                      for (const auto &r : rssa.r.regs) {
                                                            packed.insert(*rssa.r.assigns[r].second.begin());
                                                      }
                                                }
                                          }
                                    }
                              }
                              if (pass) {

                                    propagation_targets.insert(p);

                                    /* Check if any of the sources in past rvalues get set between current and then. */
                                    if (auto start = i - 1u; i) {

                                          for (const auto &e : past.second.second.first) {
                                                if (e > start) {
                                                      start = e;
                                                }
                                          }

                                          if (start > past.second.first + 1u) {

                                                const auto &srcs = pm.processed.values[past.first].rvalues_regs;
                                                for (auto o = start; o > past.second.first; --o) {
                                                      const auto &n = pm[o];
                                                      if (o == i - 1u) {
                                                            continue;
                                                      }
                                                      if (past.first == n) {
                                                            break;
                                                      }
                                                      const auto &dests = ssa.nodes[n].l.regs;
                                                      pass = !std::any_of(srcs.begin(), srcs.end(), [&](const auto &k) { return dests.contains(k); });
                                                      if (!pass) {
                                                            break;
                                                      }
                                                      const auto &pssa = ssa.nodes[n];
                                                      const auto it = pssa.r.assigns.find(r);
                                                      if (it != pssa.r.assigns.end() && it->second.first != generation::ssa::assignment_kind::phi && it->second.second.contains(tssa)) {
                                                            propagation_targets.insert(n);
                                                      }
                                                }
                                                if (!pass) {
                                                      continue;
                                                }
                                          }

                                          /* Propagate */
                                          auto &t = past.first->r;
                                          if (pack) {
                                                t = tools::exprs::generate::packed(t, packed.size() + 1u);
                                          }

                                          auto clonable = propagation_targets.size() > 1u;
                                          if (past.first->r->is_primitive()) {

                                                if (std::none_of(propagation_targets.begin(), propagation_targets.end(), [&](const auto &stat) { return pm.is_removed(stat); }) &&
                                                    !std::any_of(propagation_targets.begin(), propagation_targets.end(), [&](const auto &stat) { return stat->propagate_violates(r); })) {
                                                      for (const auto &stat : propagation_targets) {
                                                            stat->propagate(r, t, clonable);
                                                      }
                                                      if (!is_phi) {
                                                            pm.remove(past.first);
                                                            pm.mut(LURAMAS_DEBUG_LINE);
                                                      }
                                                }
                                          } else {

                                                if (!luramas::ir::tools::mutates(pm, t, past.second.first + 1u, start)) {
                                                      if (pm.is_safe(p) && pm.safe(past.first)) {

                                                            for (const auto &stat : propagation_targets) {
                                                                  stat->propagate(r, t, clonable);
                                                            }
                                                            if (is_phi_not_complex_reg_cast || !is_phi) {
                                                                  pm.remove(past.first);
                                                                  pm.mut(LURAMAS_DEBUG_LINE);
                                                            }
                                                            if (t->is_register_reference()) {
                                                                  if (const auto &asgns = ssa.nodes[past.first].r.assigns; !asgns.empty()) {
                                                                        const auto tvalue_tssa = *((*asgns.begin()).second.second.begin());
                                                                        pm.set_safe(ssa.defs[tvalue_tssa].first);
                                                                  }
                                                            }
                                                      }
                                                } else {
                                                      if (const auto &vec = pm.processed.values[past.first].rvalues;
                                                          !vec.empty() &&
                                                          std::all_of(vec.begin(), vec.end(), [](const auto &s) { return s->is_unsafe_k(); })) {
                                                            pm.set_safe(past.first);
                                                      }
                                                }
                                          }
                                    }
                              }
                        }
                  }
            }

            if (!pm.is_mut() && pm.env_flags.fallow_advance_constant_prop) {
                  analyze::helpers(pm, s, ssa, cfg);
            }
            s.ffirst_const_prop = false;
            return;
      }
} // namespace luramas::ir::passes