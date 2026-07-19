#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::find {

      luramas_address stat(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &stat) {

            for (const auto &i : luramas_iter(pm.range())) {
                  if (pm[i] == stat) {
                        return i;
                  }
            }
            return pm.amount();
      }

      std::optional<luramas_address> stat(luramas::ir::passes::pass_manager &pm, const LURAMAS_IR_DIRECTION_KINDS direction, const luramas_address start, const find_stat_cb &cb) {

            for (auto i = start; i < pm.amount(); direction == LURAMAS_IR_DIRECTION_KINDS::backward ? --i : ++i) {

                  if (cb(pm[i])) {
                        return i;
                  }
                  if (!i && direction == LURAMAS_IR_DIRECTION_KINDS::backward) {
                        break;
                  }
            }
            return std::nullopt;
      }
      luramas_address contiguous_stat(luramas::ir::passes::pass_manager &pm, const LURAMAS_IR_DIRECTION_KINDS direction, const luramas_address start, const find_stat_cb &cb) {

            const auto result = stat(pm, direction, start, [&](const std::shared_ptr<ir_stat> &stat) { return !cb(stat); });
            return result ? *result : pm.amount();
      }

      std::shared_ptr<ir_stat::ir_expr> expr(const std::shared_ptr<ir_stat::ir_expr> &expr, const find_expr_cb &cb) {

            if (!expr) {
                  return nullptr;
            }
            for (const auto &i : expr->extract_ordered_exprs()) {
                  if (cb(i)) {
                        return i;
                  }
            }
            return nullptr;
      }
} // namespace luramas::ir::tools::find