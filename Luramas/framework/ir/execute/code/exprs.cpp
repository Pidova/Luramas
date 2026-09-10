#include "common.hpp"
#include "process/common.hpp"

namespace luramas::ir::execution::exprs {

      exe_expr execute(environment &env, const std::shared_ptr<ir_stat::ir_expr> &expr) {

            exe_expr result;

            if (!expr) {
                  exe_error<errors::kinds::null_pointer>(result);
                  return result;
            }
            result.d = std::make_shared<types::object>();
            switch (expr->k) {

                  case expr_kinds::nothing: {
                                   
                        if (auto res = process::exprs::tkind(env, expr, result); res) {
                              return *res;
                        }
                        break;
                  }
                  case expr_kinds::reg: {

                        if (const auto it = env.registers.find(expr->reg); it != env.registers.end()) {
                              result = it->second;
                        } else {
                              result.d->emit(luramas_int(0U));
                        }
                        break;
                  }
                  case expr_kinds::blank_lvalue: {
                        result = execute(env, expr->l);
                        break;
                  }
                  case expr_kinds::flag: {

                        if (const auto it = env.registers.find(static_cast<luramas_register>(expr->extract_integral_base())); it != env.registers.end()) {
                              result = it->second;
                        } else {
                              exe_error<errors::kinds::unsupported_error>(result);
                              return result;
                        }
                        break;
                  }
                  case expr_kinds::arith: {

                        auto l = execute(env, expr->l);
                        auto r = execute(env, expr->r);
                        if (!l) {
                              return l;
                        }
                        if (!r) {
                              return r;
                        }
                        if (auto res = process::exprs::arith(env, expr->b, l, r, result); res) {
                              return *res;
                        }
                        break;
                  }

                  case expr_kinds::unary: {

                        auto l = execute(env, expr->l);
                        if (!l) {
                              return l;
                        }
                        if (expr->b == il::arch::data::bin_kinds::ref_) {
                              result.d->emit_ref(l.d);
                              return result;
                        }
                        // todo implement
                      // if (auto res = process::exprs::unary(env, expr->b, l, result); res) {
                      //       return *res;
                      // }
                        break;
                  }
                  default: {
                        exe_error<errors::kinds::unsupported_expr_type>(result);
                        return result;
                  }
            }

            return result;
      }
} // namespace luramas::ir::execution::exprs