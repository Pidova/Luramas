#include "common.hpp"

namespace luramas::ir::execution::evaluate::exprs {

      namespace can_cmp {

            /* Object can compare? */
            inline constexpr bool object(const tkind k, const environment_flags &f) {
                  switch (k) {
                        case tkind::object: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            /* Stack can compare? */
            inline constexpr bool stack(const tkind k, const environment_flags &f) {
                  switch (k) {
                        case tkind::stack: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            /* Global can compare? */
            inline constexpr bool global(const tkind k, const environment_flags &f) {
                  switch (k) {
                        case tkind::global: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            /* Kvalue can compare? */
            inline constexpr bool kvalue(const tkind k, const environment_flags &f) {
                  switch (k) {
                        case tkind::kvalue: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            /* None obj can compare? */
            inline constexpr bool none_obj(const tkind k, const environment_flags &f) {
                  switch (k) {
                        case tkind::none_obj: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            /* Variadic can compare? */
            inline constexpr bool variadic(const tkind k, const environment_flags &f) {
                  switch (k) {
                        case tkind::variadic: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            /* Table can compare? */
            inline constexpr bool table(const tkind k, const environment_flags &f) {
                  switch (k) {
                        case tkind::table: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            /* String can compare? */
            inline constexpr bool string(const tkind k, const environment_flags &f) {
                  switch (k) {
                        case tkind::string: {
                              return true;
                        }
                        case tkind::lura_int: {
                              return f.fcondition_string_int;
                        }
                        case tkind::boolean: {
                              return f.fcondition_string_boolean;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            /* Integral can compare? */
            inline constexpr bool integral(const tkind k, const environment_flags &f) {
                  switch (k) {
                        case tkind::lura_int: {
                              return true;
                        }
                        case tkind::string: {
                              return f.fcondition_string_int;
                        }
                        case tkind::boolean: {
                              return f.fcondition_int_boolean;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            /* Boolean can compare? */
            inline constexpr bool boolean(const tkind k, const environment_flags &f) {
                  switch (k) {
                        case tkind::boolean: {
                              return true;
                        }
                        case tkind::lura_int: {
                              return f.fcondition_int_boolean;
                        }
                        case tkind::string: {
                              return f.fcondition_string_boolean;
                        }
                        default: {
                              return false;
                        }
                  }
            }

            /*  Can values compare? */
            inline constexpr bool cmp(const tkind l, const tkind r, const environment_flags &f) {
                  switch (l) {
                        case tkind::object: {
                              return object(r, f);
                        }
                        case tkind::stack: {
                              return stack(r, f);
                        }
                        case tkind::kvalue: {
                              return kvalue(r, f);
                        }
                        case tkind::global: {
                              return global(r, f);
                        }
                        case tkind::string: {
                              return string(r, f);
                        }
                        case tkind::table: {
                              return table(r, f);
                        }
                        case tkind::variadic: {
                              return variadic(r, f);
                        }
                        case tkind::none_obj: {
                              return none_obj(r, f);
                        }
                        case tkind::boolean: {
                              return boolean(r, f);
                        }
                        case tkind::lura_int: {
                              return integral(r, f);
                        }
                        default: {
                              return false;
                        }
                  }
            }
      } // namespace can_cmp

      error::result<types::object, errors::kinds> unary(const types::object &obj, const luramas::il::arch::data::bin_kinds b, const environment_flags &f) {

            error::result<types::object, errors::kinds> result;

            if (!il::arch::data::is_kinds::unary(b)) {
                  exe_error<errors::kinds::invalid_unary_kind>(result);
                  return result;
            }

            switch (b) {
                  case luramas::il::arch::data::bin_kinds::len_: {
                        switch (obj.k) {
                              case tkind::table: {
                                    result.d.emit(std::get<types::object::table>(obj.v).map.size());
                                    break;
                              }
                              case tkind::lura_int: {
                                    if (f.funary_len_int) {
                                          result.d.emit(math::count_digits(std::get<luramas_int>(obj.v)));
                                          break;
                                    } else {
                                          exe_error<errors::kinds::invalid_unary_operand>(result);
                                          return result;
                                    }
                                    break;
                              }
                              case tkind::string: {
                                    if (f.funary_len_string) {
                                          result.d.emit(std::get<std::string>(obj.v).length());
                                          break;
                                    } else {
                                          exe_error<errors::kinds::invalid_unary_operand>(result);
                                          return result;
                                    }
                                    break;
                              }
                              default: {
                                    exe_error<errors::kinds::invalid_unary_operand>(result);
                                    return result;
                              }
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::minus_: {
                        switch (obj.k) {
                              case tkind::lura_int: {
                                    result.d.emit(-std::get<luramas_int>(obj.v));
                                    break;
                              }
                              default: {
                                    exe_error<errors::kinds::invalid_unary_operand>(result);
                                    return result;
                              }
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::not_: {
                        switch (obj.k) {
                              case tkind::boolean: {
                                    result.d.emit(!std::get<bool>(obj.v));
                                    break;
                              }
                              case tkind::lura_int: {
                                    if (f.funary_not_int) {
                                          result.d.emit(!std::get<luramas_int>(obj.v));
                                          break;
                                    } else {
                                          exe_error<errors::kinds::invalid_unary_operand>(result);
                                          return result;
                                    }
                                    break;
                              }
                              default: {
                                    exe_error<errors::kinds::invalid_unary_operand>(result);
                                    return result;
                              }
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::bitnot_: {
                        switch (obj.k) {
                              case tkind::lura_int: {
                                    result.d.emit(~std::get<luramas_int>(obj.v));
                                    break;
                              }
                              default: {
                                    exe_error<errors::kinds::invalid_unary_operand>(result);
                                    return result;
                              }
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::plus_: {
                        switch (obj.k) {
                              case tkind::lura_int: {
                                    result.d.emit(+std::get<luramas_int>(obj.v));
                                    break;
                              }
                              default: {
                                    exe_error<errors::kinds::invalid_unary_operand>(result);
                                    return result;
                              }
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::ref_: {
                        switch (obj.k) {
                              default: {
                                    exe_error<errors::kinds::invalid_unary_operand>(result);
                                    return result;
                              }
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return result;
      }

      error::result<types::object, errors::kinds> condition(const types::object &l, const types::object &r, const luramas::il::arch::data::bin_kinds b, const environment_flags &f) {

            // todo finish
            error::result<types::object, errors::kinds> result;

            if (!ir_kinds::condition(l.k, r.k, f) || !can_cmp::cmp(l.k, r.k, f)) {
                  exe_error<errors::kinds::comparison_on_incompatible_types>(result);
                  return result;
            }
            if (!il::arch::data::is_kinds::condition(b)) {
                  exe_error<errors::kinds::invalid_condition_type>(result);
                  return result;
            }

            switch (b) {
                  case luramas::il::arch::data::bin_kinds::ne_:
                  case luramas::il::arch::data::bin_kinds::eq_: {
                        switch (l.k) {
                              case tkind::string: {

                                    break;
                              }
                              case tkind::lura_int: {

                                    if (!can_cmp::integral(r.k, f)) {
                                          exe_error<errors::kinds::comparison_on_incompatible_types>(result);
                                          return result;
                                    }

                                    break;
                              }
                              case tkind::boolean: {
                                    switch (r.k) {
                                          case tkind::string: {

                                                break;
                                          }
                                          default: {
                                                break;
                                          }
                                    }
                                    break;
                              }
                              case tkind::table: {
                                    switch (r.k) {
                                          case tkind::string: {

                                                break;
                                          }
                                          default: {
                                                break;
                                          }
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::lt_:
                  case luramas::il::arch::data::bin_kinds::gt_:
                  case luramas::il::arch::data::bin_kinds::lte_:
                  case luramas::il::arch::data::bin_kinds::gte_: {

                        if (!ir_kinds::arithmetic(l.k, f) || !ir_kinds::arithmetic(r.k, f)) {
                              exe_error<errors::kinds::comparison_on_incompatible_types>(result);
                              return result;
                        }

                        const auto lv = l.k == tkind::boolean ? luramas_int(std::get<bool>(l.v)) : std::get<luramas_int>(l.v);
                        const auto rv = r.k == tkind::boolean ? luramas_int(std::get<bool>(r.v)) : std::get<luramas_int>(r.v);

                        switch (b) {
                              case luramas::il::arch::data::bin_kinds::lt_: {
                                    const auto res = lv < rv;
                                    if (f.fprimitive_objects) {
                                          result.d.emit(res);
                                    } else {
                                          result.d.emit(luramas_int(res));
                                    }
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::gt_: {
                                    const auto res = lv > rv;
                                    if (f.fprimitive_objects) {
                                          result.d.emit(res);
                                    } else {
                                          result.d.emit(luramas_int(res));
                                    }
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::lte_: {
                                    const auto res = lv <= rv;
                                    if (f.fprimitive_objects) {
                                          result.d.emit(res);
                                    } else {
                                          result.d.emit(luramas_int(res));
                                    }
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::gte_: {
                                    const auto res = lv >= rv;
                                    if (f.fprimitive_objects) {
                                          result.d.emit(res);
                                    } else {
                                          result.d.emit(luramas_int(res));
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::et_:
                  case luramas::il::arch::data::bin_kinds::nt_: {

                        if (!ir_kinds::arithmetic(l.k, f) || (f.fprimitive_objects && l.k != tkind::boolean)) {
                              exe_error<errors::kinds::comparison_on_incompatible_types>(result);
                              return result;
                        }

                        const auto lv = l.k == tkind::boolean ? luramas_int(std::get<bool>(l.v)) : std::get<luramas_int>(l.v);

                        switch (b) {
                              case luramas::il::arch::data::bin_kinds::et_: {
                                    const auto res = lv == true;
                                    if (f.fprimitive_objects) {
                                          result.d.emit(res);
                                    } else {
                                          result.d.emit(luramas_int(res));
                                    }
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::nt_: {
                                    const auto res = lv != true;
                                    if (f.fprimitive_objects) {
                                          result.d.emit(res);
                                    } else {
                                          result.d.emit(luramas_int(res));
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return result;
      }

      error::result<types::object, errors::kinds> arithmetic(const types::object &l, const types::object &r, const luramas::il::arch::data::bin_kinds b, const environment_flags &f) {

            error::result<types::object, errors::kinds> result;

            if (!ir_kinds::arithmetic(l.k, f) || !ir_kinds::arithmetic(r.k, f)) {
                  exe_error<errors::kinds::arithmetic_on_non_valid>(result);
                  return result;
            }
            if (!il::arch::data::is_kinds::arith(b)) {
                  exe_error<errors::kinds::arithmetic_on_non_arithmetic_binkind>(result);
                  return result;
            }

            const auto lv = l.k == tkind::boolean ? luramas_int(std::get<bool>(l.v)) : std::get<luramas_int>(l.v);
            const auto rv = r.k == tkind::boolean ? luramas_int(std::get<bool>(r.v)) : std::get<luramas_int>(r.v);

            switch (b) {
                  case luramas::il::arch::data::bin_kinds::or_: {
                        result.d.emit(lv | rv);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::add_: {
                        result.d.emit(lv + rv);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::sub_: {
                        result.d.emit(lv - rv);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::mul_: {
                        result.d.emit(lv * rv);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::div_: {
                        if (rv == 0u) {
                              if (f.farithmetic_nan_zero) {
                                    result.d.emit(0u);
                              } else {
                                    exe_error<errors::kinds::division_by_zero>(result);
                                    return result;
                              }
                        } else {
                              result.d.emit(lv / rv);
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::mod_: {
                        result.d.emit(lv % rv);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::pow_: {
                        result.d.emit(math::pow(lv, rv));
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::and_: {
                        result.d.emit(lv & rv);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::xor_: {
                        result.d.emit(lv ^ rv);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::shl_: {
                        result.d.emit(lv << rv);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::shr_: {
                        result.d.emit(lv >> rv);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::idiv_: {
                        result.d.emit(math::floor(lv / rv));
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return result;
      }

      types::object execute(environment &env, const std::shared_ptr<ir_stat::ir_expr> &expr) {

            types::object result;
            if (!expr) {
                  return result;
            }
            switch (expr->k) {
                        //  case expr_kinds::reg: {
                        //        if (expr->reg >= env.registers.size()) {
                        //              return result; // Return empty object
                        //        }
                        //        result = env.registers[expr->reg];
                        //        break;
                        //  }
                        //  case expr_kinds::global: {
                        //        if (expr->global >= env.globals.size()) {
                        //              return result; // Return empty object
                        //        }
                        //        result = env.globals[expr->global];
                        //        break;
                        //  }
                        //  case expr_kinds::value: {
                        //        result = expr->value;
                        //        break;
                        //  }
                        //  case expr_kinds::call: {
                        //        // Handle function call expression
                        //        break;
                        //  }
                  default: {
                        break;
                  }
            }
            return result;
      }
} // namespace luramas::ir::execution::evaluate::exprs