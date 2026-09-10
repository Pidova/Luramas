#include "../common.hpp"
#include "../../common.hpp"

namespace luramas::ir::execution::process::exprs {

      process_result tkind(environment &env, const std::shared_ptr<ir_stat::ir_expr> &expr, exe_expr &result) {

            switch (expr->tk) {
                  case tkind::none_obj: {
                        result.d->emit();
                        break;
                  }
                  case tkind::variadic: {
                        if (env.flags.fref_variadics) {
                              result.d->emit(env.input_variadic);
                              break;
                        }
                        std::vector<std::shared_ptr<types::object>> v;
                        for (const auto &m : expr->members) {
                              if (!m) {
                                    exe_error<errors::kinds::unsupported_error>(result);
                                    return result;
                              }
                              auto me = execution::exprs::execute(env, m);
                              if (!me) {
                                    exe_error<errors::kinds::unsupported_error>(result);
                                    return result;
                              }
                              v.emplace_back(me.d);
                        }
                        result.d->emit(v);
                        break;
                  }
                  case tkind::table: {
                        types::object::table t(env.flags.input.istart_table_index);
                        for (const auto &[k, v] : expr->tmembers) {
                              if (!k || !v) {
                                    exe_error<errors::kinds::unsupported_error>(result);
                                    return result;
                              }
                              auto ke = execution::exprs::execute(env, k);
                              auto ve = execution::exprs::execute(env, v);
                              if (!ke) {
                                    exe_error<errors::kinds::unsupported_error>(result);
                                    return result;
                              }
                              if (!ve) {
                                    exe_error<errors::kinds::unsupported_error>(result);
                                    return result;
                              }
                              t.add(ke.d, ve.d);
                        }
                        for (const auto &m : expr->members) {
                              if (!m) {
                                    exe_error<errors::kinds::unsupported_error>(result);
                                    return result;
                              }
                              auto me = execution::exprs::execute(env, m);
                              if (!me) {
                                    return me;
                              }
                              t.append(me.d);
                        }
                        result.d->emit(t);
                        break;
                  }
                  case tkind::string: {
                        result.d->emit(expr->v);
                        break;
                  }
                  case tkind::lura_int: {
                        result.d->emit(expr->n);
                        break;
                  }
                  case tkind::global: {
                        if (const auto it = env.globals.find(expr->v); it != env.globals.end()) {
                              result = it->second;
                        } else {
                              result.d->emit();
                        }
                        break;
                  }
                  case tkind::boolean: {
                        result.d->emit(expr->n != 0U);
                        break;
                  }
                  case tkind::kvalue: {
                        result.d->emitk(expr->v);
                        break;
                  }
                  case tkind::object: {
                        result.d->emit(expr->non_native);
                        break;
                  }
                  case tkind::stack: {
                        result.d->emits(expr->n);
                        break;
                  }
                  case tkind::controller: {
                        if (env.controller.empty()) {
                              exe_error<errors::kinds::unsupported_error>(result);
                              return result;
                        }   
                        result.d = env.controller.back();
                        break;
                  }
                  case tkind::extpr: {
                        if (const auto it = env.exprts.find(expr->extract_integral_base()); it != env.exprts.end()) {
                              result = execution::exprs::execute(env, it->second);
                        } else {
                              exe_error<errors::kinds::undefined_exprt>(result);
                              return result;
                        }
                        break;
                  }
                  default: {
                        exe_error<errors::kinds::unsupported_expr_tkind>(result);
                        return result;
                  }
            }
            return std::nullopt;
      }
} // namespace luramas::ir::execution::exprs::process