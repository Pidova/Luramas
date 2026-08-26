#include "common.hpp"

namespace luramas::ir::execution::exprs {

      static error::result<types::object, errors::kinds> execute(environment &env, const std::shared_ptr<ir_stat::ir_expr> &expr) {

            error::result<types::object, errors::kinds> result;

            if (!expr) {
                  exe_error<errors::kinds::null_pointer>(result);
                  return result;
            }

            switch (expr->k) {
                  case expr_kinds::memoryread: {
                        break;
                  }
                  case expr_kinds::bitread: {
                        break;
                  }
                  case expr_kinds::call: {
                        break;
                  }
                  case expr_kinds::arith: {

                        auto l = execute(env, expr->l);
                        if (l) {
                              return l;
                        }
                        auto r = execute(env, expr->r);
                        if (r) {
                              return r;
                        }

                        break;
                  }
                  case expr_kinds::condition: {
                        break;
                  }
                  case expr_kinds::unpack: {
                        break;
                  }
                  case expr_kinds::concat: {
                        break;
                  }
                  case expr_kinds::idx: {
                        break;
                  }
                  case expr_kinds::unary: {
                        break;
                  }
                  case expr_kinds::reg: {
                        break;
                  }
                  case expr_kinds::self: {
                        break;
                  }
                  case expr_kinds::page_function_call: {
                        break;
                  }
                  case expr_kinds::closure: {
                        break;
                  }
                  case expr_kinds::upvalue: {
                        break;
                  }
                  case expr_kinds::ternary: {
                        break;
                  }
                  case expr_kinds::cast: {
                        break;
                  }
                  case expr_kinds::flag: {
                        break;
                  }
                  case expr_kinds::nothing: {

                        switch (expr->tk) {
                              case tkind::none_obj: {
                                    result.d.emit();
                                    break;
                              }
                              case tkind::variadic: {
                                    break;
                              }
                              case tkind::table: {
                                    break;
                              }
                              case tkind::string: {
                                    result.d.emit(expr->v);
                                    break;
                              }
                              case tkind::lura_int: {
                                    result.d.emit(expr->n);
                                    break;
                              }
                              case tkind::global: {
                                    break;
                              }
                              case tkind::boolean: {
                                    result.d.emit(expr->bv);
                                    break;
                              }
                              case tkind::kvalue: {
                                    break;
                              }
                              case tkind::stack: {
                                    break;
                              }
                              case tkind::object: {
                                    break;
                              }
                              case tkind::controller: {
                                    break;
                              }
                              case tkind::extpr: {
                                    break;
                              }
                              default: {
                                    exe_error<errors::kinds::unsupported_expr_tkind>(result);
                                    return result;
                              }
                        }
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