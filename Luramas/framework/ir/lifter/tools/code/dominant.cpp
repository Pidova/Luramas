#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::dominant {

      namespace extract {

            std::optional<addr_expr> immediate_expr_in_expr_or_stat(luramas::ir::passes::pass_manager &pm, const luramas_address loc, const std::shared_ptr<ir_stat::ir_expr> &target) {

                  addr_expr result;
                  result.n = loc;

                  const auto &stat = pm[loc];

                  ir_stat::ir_expr::space extraction;
                  recursion::manager<std::shared_ptr<ir_stat::ir_expr>> m(LURAMAS_PREDICTED_RECURSION);
                  stat->extract_shallow_ordered_exprs(extraction);
                  for (const auto &i : extraction) {
                        if (*target == *i) {
                              result.stat = true;
                              return result;
                        }
                        m.push(i);
                  }
                  while (m) {

                        extraction.clear();
                        stat->extract_shallow_ordered_exprs(extraction);
                        const auto curr = m.curr();
                        for (const auto &i : extraction) {
                              if (*target == *i) {
                                    result.e = curr;
                                    return result;
                              }
                              m.push(i);
                        }
                  }
                  return std::nullopt;
            }

            std::shared_ptr<ir_stat::ir_expr> immediate_volatile_expr(luramas::ir::passes::pass_manager &pm, const luramas_address loc, const std::shared_ptr<ir_stat::ir_expr> &target) {

                  std::shared_ptr<ir_stat::ir_expr> result = nullptr;
                  for (const auto &i : pm[loc]->extract_shallow_ordered_exprs()) {

                        for (const auto &i : tools::extract::exprs::path(i, target)) {
                              if (i->is_volatile()) {
                                    result = i;
                              }
                        }
                        if (result) {
                              return result;
                        }
                  }
                  return result;
            }

            std::shared_ptr<ir_stat::ir_expr> expr(luramas::ir::passes::pass_manager &pm, const luramas_address loc, const std::shared_ptr<ir_stat::ir_expr> &target) {

                  for (const auto &i : pm[loc]->extract_shallow_ordered_exprs()) {

                        if (const auto path = tools::extract::exprs::path(i, target); path.size() > 1u) {
                              return path[path.size() - 1u];
                        }
                  }
                  return nullptr;
            }
      } // namespace extract

} // namespace luramas::ir::tools::dominant