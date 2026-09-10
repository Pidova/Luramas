/*
    Evaluate stats and exprs with regard to depth.
*/
#pragma once
#include "../execution.hpp"

namespace luramas::ir::execution {

      namespace stats {

      }

      namespace exprs {
            exe_expr execute(environment &env, const std::shared_ptr<ir_stat::ir_expr> &expr);
      }
} // namespace luramas::ir::execution