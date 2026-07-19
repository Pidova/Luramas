#include "safety.hpp"

namespace luramas::ir::safety {

      namespace types {

            bool same_type(const std::shared_ptr<ir_stat::ir_expr> &expr, const std::shared_ptr<ir_stat::ir_expr> &type) {

                  return false;
            }

            std::shared_ptr<ir_stat::ir_expr> generate::make_cast(const std::shared_ptr<ir_stat::ir_expr> &input, const std::shared_ptr<ir_stat::ir_expr> &casting_type) {
                  return nullptr;
            }
      } // namespace types

} // namespace luramas::ir::safety