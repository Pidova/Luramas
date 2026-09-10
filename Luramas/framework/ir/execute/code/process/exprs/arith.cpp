#include "../common.hpp"

namespace luramas::ir::execution::process::exprs {

      process_result arith(environment &env, const il::arch::data::bin_kinds b, const exe_expr &l, const exe_expr &r, exe_expr &result) {

            if (!l || !l.d) {
                  return l;
            }
            if (!r || !r.d) {
                  return r;
            }

            const auto &lk = l.d->k;
            const auto &rk = r.d->k;
            switch (lk) {
                  case tkind::boolean:
                  case tkind::lura_int: {
                        switch (rk) {
                              case tkind::boolean:
                              case tkind::lura_int: {

                                    /* Check booleans */
                                    if ((lk == tkind::boolean || rk == tkind::boolean) && !env.flags.fcan_arith_boolean) {
                                          exe_error<errors::kinds::unsupported_error>(result);
                                          return result;
                                    }

                                    /* types */
                                    const auto &lv = lk == tkind::lura_int ? std::get<luramas_int>(l.d->v) : (std::get<bool>(l.d->v) ? static_cast<luramas_int>(1) : static_cast<luramas_int>(0));
                                    const auto &rv = rk == tkind::lura_int ? std::get<luramas_int>(r.d->v) : (std::get<bool>(r.d->v) ? static_cast<luramas_int>(1) : static_cast<luramas_int>(0));
                                    switch (b) {
                                          case il::arch::data::bin_kinds::add_: {
                                                result.d->emit(lv + rv);
                                                break;
                                          }
                                          case il::arch::data::bin_kinds::sub_: {
                                                result.d->emit(lv - rv);
                                                break;
                                          }
                                          case il::arch::data::bin_kinds::mul_: {
                                                result.d->emit(lv * rv);
                                                break;
                                          }
                                          case il::arch::data::bin_kinds::div_: {
                                                result.d->emit(lv / rv);
                                                break;
                                          }
                                          case il::arch::data::bin_kinds::idiv_: {
                                                result.d->emit(math::floor_div(lv, rv));
                                                break;
                                          }
                                          case il::arch::data::bin_kinds::mod_: {
                                                result.d->emit(lv % rv);
                                                break;
                                          }
                                          case il::arch::data::bin_kinds::pow_: {
                                                result.d->emit(math::pow(lv, rv));
                                                break;
                                          }
                                          case il::arch::data::bin_kinds::and_: {
                                                result.d->emit(lv & rv);
                                                break;
                                          }
                                          case il::arch::data::bin_kinds::xor_: {
                                                result.d->emit(lv ^ rv);
                                                break;
                                          }
                                          case il::arch::data::bin_kinds::shl_: {
                                                result.d->emit(lv << rv);
                                                break;
                                          }
                                          case il::arch::data::bin_kinds::shr_: {
                                                result.d->emit(lv >> rv);
                                                break;
                                          }
                                          case il::arch::data::bin_kinds::or_: {
                                                result.d->emit(lv | rv);
                                                break;
                                          }
                                          default: {
                                                exe_error<errors::kinds::unsupported_error>(result);
                                                return result;
                                          }
                                    }

                                    /* Wrap boolean */
                                    if (lk == tkind::boolean && rk == tkind::boolean) {
                                          result.d->emit(env.flags.fboolean_arith_wraps ? !(std::get<luramas_int>(l.d->v) % 2) : std::get<luramas_int>(result.d->v) != 0);
                                    }
                                    break;
                              }
                              default: {
                                    exe_error<errors::kinds::unsupported_error>(result);
                                    return result;
                              }
                        }
                        break;
                  }
                  default: {
                        exe_error<errors::kinds::unsupported_error>(result);
                        return result;
                  }
            }
            return std::nullopt;
      }
} // namespace luramas::ir::execution::exprs::process