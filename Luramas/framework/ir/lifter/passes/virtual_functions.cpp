#include "includes/common.hpp"

namespace luramas::ir::passes {

      void virtual_function_inline(pass_manager &pm, shared &s) {

            for (auto i = 0ull; i < pm.amount(); ++i) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::table_setlist: {

                              /* SETLIST[n, amt] = {} */
                              if (pm.safe(p)) {

                                    auto idx = p->table_index;
                                    for (const auto &m : p->tmembers) {
                                          pm.insert(p, tools::stat::generate::table_assignment(p->l, tools::exprs::generate::integral(idx++), m));
                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
            return;
      }

      void virtual_function_reconstruction(pass_manager &pm, shared &s) {

            if (pm.env_flags.options.oexpr_virtual_functions.empty() || pm.env_flags.options.ostat_virtual_functions.empty()) {
                  return;
            }

            boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> processed;
            processed.reserve(pm.amount() * LURAMAS_PREDICTED_EXPRS);

            std::function<std::shared_ptr<ir_stat::ir_expr>(std::shared_ptr<ir_stat::ir_expr> &)> compute_expr = [&](std::shared_ptr<ir_stat::ir_expr> &expr) -> std::shared_ptr<ir_stat::ir_expr> {
                  if (!expr || processed.contains(expr)) {
                        return nullptr;
                  }
                  processed.insert(expr);

                  for (const auto &[k, v] : pm.env_flags.options.oexpr_virtual_functions) {
                        if (const auto p = tools::replace::match_wild_cards(expr, k, v); p) {
                              return p;
                        }
                  }
                  for (auto *p : {&expr->l, &expr->r, &expr->ev, &expr->xv}) {
                        if (!*p) {
                              continue;
                        }
                        if (auto j = compute_expr(*p); j) {
                              *p = std::move(j);
                              return nullptr;
                        }
                  }
                  for (auto &p : expr->members) {
                        if (!p) {
                              continue;
                        }
                        if (auto j = compute_expr(p); j) {
                              p = std::move(j);
                              return nullptr;
                        }
                  }

                  for (auto &p : expr->captures) {
                        if (!p) {
                              continue;
                        }
                        if (auto j = compute_expr(p); j) {
                              p = std::move(j);
                              return nullptr;
                        }
                  }

                  for (auto &[i, v] : expr->tmembers) {
                        if (i) {
                              if (auto j = compute_expr(i); j) {
                                    i = std::move(j);
                                    return nullptr;
                              }
                        }
                        if (v) {
                              if (auto j = compute_expr(v); j) {
                                    v = std::move(j);
                                    return nullptr;
                              }
                        }
                  }
                  return nullptr;
            };

            for (const auto &i : pm.iter()) {

                  if (auto &p = pm[i]; pm.is_safe(p)) {

                        for (auto *i : {&p->l, &p->r, &p->v}) {
                              if (!*i) {
                                    continue;
                              }
                              if (auto j = compute_expr(*i); j) {
                                    *i = std::move(j);
                              }
                        }

                        for (auto &v : p->members) {
                              if (!v) {
                                    continue;
                              }
                              if (auto j = compute_expr(v); j) {
                                    v = std::move(j);
                              }
                        }

                        for (auto &v : p->smembers) {
                              if (!v) {
                                    continue;
                              }
                              if (auto j = compute_expr(v); j) {
                                    v = std::move(j);
                              }
                        }

                        for (auto &v : p->tmembers) {
                              if (!v) {
                                    continue;
                              }
                              if (auto j = compute_expr(v); j) {
                                    v = std::move(j);
                              }
                        }

                        switch (p->k) {
                              case keywords::bitwrite: {
                                    if (p->lba) {
                                          if (auto j = compute_expr(p->lba); j) {
                                                p->lba = std::move(j);
                                          }
                                    }
                                    break;
                              }
                              default:
                                    break;
                        }
                  }
            }
            return;
      }
} // namespace luramas::ir::passes