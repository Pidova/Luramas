#include "../tools.hpp"

namespace luramas::ir::tools::linked {

      namespace parameters {

            void adjust_referenced_out(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa, const std::vector<std::optional<luramas_address>> &parent_pages) {

                  const auto refed_out = tools::ssa::referenced_out_of_page(pm, ssa, parent_pages);

                  boost::unordered_flat_map<luramas_address, boost::unordered_flat_set<luramas_register>> pending_defs;

                  /* Add unknowns */
                  for (const auto &[addr, regs] : ssa.unknown) {
                        if (const auto &parent_page = parent_pages[addr]; parent_page) {
                              pending_defs.try_emplace(*parent_page, boost::unordered_flat_set<luramas_register>()).first->second.insert(regs.begin(), regs.end());
                        }
                  }

                  /* Make definition for parent page */
                  for (auto i = 0u; i < refed_out.size(); ++i) {

                        const auto &out_ref = refed_out[i];
                        if (!out_ref) {
                              continue;
                        }
                        if (const auto &parent_page = parent_pages[i]; parent_page) {
                              for (const auto &[ssa_reg, p_addr] : *out_ref) {
                                    if (const auto linked = tools::ssa::extract::linked(ssa, ssa_reg); linked) {
                                          pending_defs.try_emplace(*parent_page, boost::unordered_flat_set<luramas_register>()).first->second.insert(*linked);
                                    }
                              }
                        }
                  }

                  /* Add it */
                  boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> current_casts;
                  for (const auto &[addr, s] : pending_defs) {

                        const auto def = tools::stat::generate::flags::paging::definition(tools::guarantee::stats::definition(pm, addr, addr + 1u));
                        for (const auto &e : def->meta) {
                              if (tools::exprs::values::is_cast_reg(e)) {
                                    current_casts[e->l->reg] = e;
                              }
                        }
                        def->args.clear();
                        def->meta.clear();
                        for (const auto &r : s) {
                              if (def->args.try_emplace(r, tools::exprs::generate::reg_arg(r)).second) {
                                    if (const auto it = current_casts.find(r); it != current_casts.end()) {
                                          def->meta.emplace_back(it->second);
                                    } else {
                                          def->meta.emplace_back(nullptr);
                                    }
                              }
                        }
                        current_casts.clear();
                  }
                  return;
            }

            void adjust_by_successors(luramas::ir::passes::pass_manager &pm, const generation::cfg::cfg &cfg, const tools::paging::details &page_details, const std::vector<std::optional<luramas_address>> &parent_pages) {

                  const auto successors = tools::paging::successor_pages(pm, page_details, cfg, parent_pages, tools::paging::parents_encapsulating_pages(tools::paging::encapsulating_pages(pm, page_details, parent_pages)));
                  const auto defs = tools::paging::map_definitions(page_details);

                  /* Traverse successors */
                  std::vector<luramas_id> stack;
                  boost::unordered_flat_set<luramas_id> visited;
                  std::map<luramas_register, std::pair<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<luramas::ir::types::object::type>>> args;

                  for (const auto &[pid, def] : defs) {

                        args.clear();
                        visited.clear();
                        stack = {pid};

                        while (!stack.empty()) {

                              /* Current  */
                              const auto curr = stack.back();
                              stack.pop_back();
                              if (!visited.insert(curr).second) {
                                    continue;
                              }

                              /* Add */
                              if (const auto it = defs.find(curr); it != defs.end()) {
                                    luramas_index idx = 0u;
                                    const auto has_types = it->second->args.size() == it->second->meta.size();
                                    for (const auto &[r, expr] : it->second->args) {
                                          args[r] = std::make_pair(expr, has_types ? it->second->meta[idx] ? it->second->meta[idx]->non_native : nullptr : nullptr);
                                          idx += has_types;
                                    }
                              }

                              /* Add successors */
                              if (const auto it = successors.find(curr); it != successors.end()) {
                                    for (const auto &[_, pid] : it->second) {
                                          stack.emplace_back(pid);
                                    }
                              }
                        }

                        /* Update */
                        for (const auto &[reg, data] : args) {
                              if (def->args.try_emplace(reg, data.first).second) {
                                    def->meta.emplace_back(data.second ? tools::exprs::generate::cast(data.first, data.second) : nullptr);
                              }
                        }
                  }
                  return;
            }

            void adjust_dead_removal(luramas::ir::passes::pass_manager &pm) {

                  return;
            }

            void pre_adjust(luramas::ir::passes::pass_manager &pm, const generation::cfg::cfg &cfg, const generation::ssa::ssa &ssa, const tools::paging::details &page_details, const std::vector<std::optional<luramas_address>> &parent_pages) {

                  adjust_referenced_out(pm, ssa, parent_pages);
                  adjust_by_successors(pm, cfg, page_details, parent_pages);
                  adjust_dead_removal(pm);
                  return;
            }
      } // namespace parameters

      namespace args {

            bool adjust(luramas::ir::passes::pass_manager &pm, const tools::paging::details &page_details) {

                  bool result = false;
                  boost::unordered_flat_map<luramas_register, luramas_index> already_set;
                  for (const auto &[exp, data] : page_details.pages) {

                        for (const auto &[pid, page] : data) {

                              if (page.fvalid) {

                                    if (const auto &def = pm[page.range.first + 1u]; tools::stat::is_definition(def) && def->flags.fpage_keyword) {

                                          for (const auto &[rexp, a_es] : page.references) {

                                                for (const auto &a_e : a_es) {

                                                      if (a_e.stat) {

                                                            if (const auto &stat = pm[a_e.n]; tools::stat::is_page_function_goto(stat)) {

                                                                  auto copy = stat->members;
                                                                  stat->members.clear();
                                                                  for (auto i = 0u; i < stat->smembers.size(); ++i) {
                                                                        if (const auto &e = stat->smembers[i]; exprs::values::is_general_purpose_register(e)) {
                                                                              already_set[e->reg] = i;
                                                                        }
                                                                  }
                                                                  stat->smembers.clear();
                                                                  for (const auto &[r, e] : def->args) {
                                                                        if (const auto it = already_set.find(r); it != already_set.end() && copy.size() > it->second) {
                                                                              stat->members.emplace_back(copy[it->second]);
                                                                        } else {
                                                                              stat->members.emplace_back(e);
                                                                        }
                                                                        stat->smembers.emplace_back(e);
                                                                  }
                                                                  result |= stat->members.size() != copy.size();
                                                                  already_set.clear();
                                                            }

                                                      } else if (tools::exprs::values::is_page_function_call(a_e.e)) {

                                                            auto copy = a_e.e->members;
                                                            a_e.e->members.clear();
                                                            for (auto i = 0u; i < a_e.e->tmembers.size(); ++i) {
                                                                  if (const auto &[e, _] = a_e.e->tmembers[i]; exprs::values::is_general_purpose_register(e)) {
                                                                        already_set[e->reg] = i;
                                                                  }
                                                            }
                                                            a_e.e->tmembers.clear();
                                                            for (const auto &[r, e] : def->args) {
                                                                  if (const auto it = already_set.find(r); it != already_set.end() && copy.size() > it->second) {
                                                                        a_e.e->members.emplace_back(copy[it->second]);
                                                                  } else {
                                                                        a_e.e->members.emplace_back(e);
                                                                  }
                                                                  a_e.e->tmembers.emplace_back(e, nullptr);
                                                            }
                                                            result |= a_e.e->members.size() != copy.size();
                                                            already_set.clear();
                                                      }
                                                }
                                          }
                                    }
                              }
                        }
                  }
                  return result;
            }
      } // namespace args
} // namespace luramas::ir::tools::linked