#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools {

      std::shared_ptr<ir_stat> idx(const ir_stat::space &main, const std::shared_ptr<ir_stat::ir_expr> &potiential_closure, const luramas_address idx) {

            return exprs::values::is_closure(potiential_closure) ? potiential_closure->closure[idx] : main[idx];
      }
} // namespace luramas::ir::tools