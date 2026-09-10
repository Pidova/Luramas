/*
   Itemized evaluation of stats and exprs
*/
#pragma once
#include "../../execution.hpp"

namespace luramas::ir::execution::process::exprs {

      /* If theres an error in exe_expr will return exe_expr that has the error, nullopt mean no error */
      using process_result = std::optional<exe_expr>;

      /* Process arithmetic objects */
      process_result arith(environment &env, const il::arch::data::bin_kinds b, const exe_expr &l, const exe_expr &r, exe_expr &result);

      /* Process unary object */
      //process_result unary(environment &env, const il::arch::data::bin_kinds u, const exe_expr &v, exe_expr &result);

      /* Process tkind */
      process_result tkind(environment &env, const std::shared_ptr<ir_stat::ir_expr> &expr, exe_expr &result);
} // namespace luramas::ir::execution::process::exprs