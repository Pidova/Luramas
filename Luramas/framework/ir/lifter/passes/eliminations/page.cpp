#include "../includes/common.hpp"

namespace luramas::ir::passes {

      void dead_page_elimination(pass_manager &pm, shared &s) {

            const auto page_details = tools::paging::gen_details(pm);
            for (const auto &[expr, map] : page_details.pages) {

                  for (const auto &[pid, page] : map) {

                        /* Not safe */
                        if (!pm.is_safe(page.range.first, page.range.second)) {
                              continue;
                        }

                        if (page.fvalid && page.references.empty()) {

                              /* 
                                  P {
                                    return;
                                  }
                              */
                              if (const auto range = page.code_range(pm.ir.data); tools::count::insts(range) == 1u && tools::stat::is_return(pm[range.first]) && !tools::paging::referenced_in_page(page)) {

                                    tools::eliminate::page(pm, page_details, page);
                                    continue;
                              }
                        }
                  }
            }
            return;
      }

      void dead_page_definition_elimination(pass_manager &pm, shared &s, generation::ssa::ssa &ssa) {

            for (const auto &[expr, map] : tools::paging::gen_details(pm).pages) {

                  for (const auto &[pid, page] : map) {

                        luramas_flag fmutated = false;
                        std::vector<luramas_index> args;

                        /* Remove */
                        const auto &def = pm[page.range.first + 1u];
                        if (tools::stat::is_definition(def) && def->flags.flink_regs) {

                              for (const auto &[linked, data] : ssa.nodes[def].l.assigns) {

                                    if (ssa.defs[(*data.second.begin())].second.second.first.empty()) {

                                          if (const auto it = def->args.find(linked); it != def->args.end()) {

                                                const auto idx = static_cast<std::size_t>(std::distance(def->args.begin(), it));
                                                args.emplace_back(idx);
                                                def->args.erase(it);
                                                if (idx < def->meta.size()) {
                                                      def->meta.erase(def->meta.begin() + idx);
                                                }
                                                fmutated = true;
                                          }
                                    }
                              }
                        }

                        /* Reinitialize args */
                        if (fmutated) {
                              for (const auto &[exp, a_es] : page.references) {

                                    for (const auto &i : a_es) {

                                          if (i.stat) {

                                                if (const auto &p = (!exp ? pm[i.n] : exp->closure[i.n]); tools::stat::is_page_function_goto(p)) {

                                                      if (p->members.empty()) {
                                                            for (const auto &[r, expr] : def->args) {
                                                                  p->members.emplace_back(expr);
                                                            }
                                                      } else {
                                                            for (const auto &i : args) {
                                                                  if (i < p->members.size()) {
                                                                        p->members.erase(p->members.begin() + i);
                                                                  }
                                                            }
                                                      }
                                                }
                                          } else if (tools::exprs::values::is_page_function_call(i.e)) {

                                                if (i.e->members.empty()) {
                                                      for (const auto &[r, expr] : def->args) {
                                                            i.e->members.emplace_back(expr);
                                                      }
                                                } else {
                                                      for (const auto &a : args) {
                                                            if (a < i.e->members.size()) {
                                                                  i.e->members.erase(i.e->members.begin() + a);
                                                            }
                                                      }
                                                }
                                          }
                                    }
                              }
                        }
                  }
            }
            return;
      }
} // namespace luramas::ir::passes