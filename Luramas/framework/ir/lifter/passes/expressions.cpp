#include "includes/common.hpp"

namespace luramas::ir::passes {

      void sub_expression_reordering(pass_manager &pm, shared &s) {

            boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> processed;
            for (const auto &i : pm.iter()) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::until:
                        case keywords::while_:
                        case keywords::condition:
                        case keywords::condition_goto: {

                              /*           
                                     if (CONSTANT ?? ?(NOT INT)) then
                              */
                              if (tools::stat::branch::is_comparable(p) && !p->l->is_tk<tkind::nothing>() && p->r && !p->r->is_integral() && !data::reference(p->l->tk) && pm.safe(p)) {
                                    std::swap(p->l, p->r);
                                    if (il::arch::data::is_kinds::swap_side_effects(p->b)) {
                                          tools::stat::mutate::flip_cmp(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }

                  const auto reorder_expr = [&](const auto &expr) {
                        std::vector<std::shared_ptr<ir_stat::ir_expr>> exprs = {expr};
                        exprs.reserve(LURAMAS_PREDICTED_RECURSION);
                        while (!exprs.empty()) {

                              auto current = exprs.back();
                              exprs.pop_back();
                              if (current && !processed.contains(current)) {

                                    processed.insert(current);

                                    tools::compute::exprs::reorder(pm, current);

                                    for (const auto &e : {expr->l, expr->r, expr->ev, expr->xv}) {
                                          if (e) {
                                                exprs.emplace_back(e);
                                          }
                                    }
                                    for (const auto &m : expr->members) {
                                          if (m) {
                                                exprs.emplace_back(m);
                                          }
                                    }
                                    for (const auto &m : expr->captures) {
                                          if (m) {
                                                exprs.emplace_back(m);
                                          }
                                    }
                                    for (const auto &[i, v] : expr->tmembers) {
                                          if (i) {
                                                exprs.emplace_back(i);
                                          }
                                          if (v) {
                                                exprs.emplace_back(v);
                                          }
                                    }
                              }
                        }
                        return;
                  };

                  reorder_expr(p->l);
                  reorder_expr(p->r);
                  reorder_expr(p->v);
                  for (auto &v : p->members) {
                        reorder_expr(v);
                  }
                  for (auto &v : p->smembers) {
                        reorder_expr(v);
                  }
                  for (auto &v : p->tmembers) {
                        reorder_expr(v);
                  }
            }
            return;
      }
} // namespace luramas::ir::passes