#include "../../../tables/data/ariths.hpp"
#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::combine {

      bool can(const il::arch::data::bin_kinds l, const il::arch::data::bin_kinds r) {
            switch (l) {
                  case il::arch::data::bin_kinds::add_:
                  case il::arch::data::bin_kinds::sub_: {
                        return r == il::arch::data::bin_kinds::add_ || r == il::arch::data::bin_kinds::sub_;
                  }
                  case il::arch::data::bin_kinds::mul_:
                  case il::arch::data::bin_kinds::div_:
                  case il::arch::data::bin_kinds::idiv_:
                  case il::arch::data::bin_kinds::shl_:
                  case il::arch::data::bin_kinds::shr_:
                  case il::arch::data::bin_kinds::and_:
                  case il::arch::data::bin_kinds::or_:
                  case il::arch::data::bin_kinds::xor_: {
                        return l == r;
                  }
                  default: {
                        return false;
                  }
            }
      }

      std::shared_ptr<ir_stat::ir_expr> unary(passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &expr) {

            if (!exprs::values::is_unary(expr) || !expr->l) {
                  return nullptr;
            }

            switch (expr->u) {
                  case il::arch::data::bin_kinds::minus_: {

                        /* -(INTEGRAL) */
                        if (expr->l->is_integral()) {
                              const auto e = expr->l;
                              e->n = -e->n;
                              return e;
                        }

                        /* -CAST[int32_t](-TYPE[int64_t])*/
                        if (tools::exprs::values::is_cast(expr->l, luramas::types::native::t_int32) &&
                            tools::exprs::values::is_unary<il::arch::data::bin_kinds::minus_>(expr->l->l) &&
                            tools::exprs::values::types::is_resulting_type(expr->l->l->l, luramas::types::native::t_int64)) {

                              expr->l->l = expr->l->l->l;
                              return expr->l;
                        }
                        break;
                  }
                  case il::arch::data::bin_kinds::bitnot_: {

                        /* ~(INTEGRAL) */
                        if (expr->l->is_integral()) {
                              const auto e = expr->l;
                              e->n = ~e->n;
                              return e;
                        }

                        /* ~(~?) */
                        if (tools::exprs::values::is_unary<il::arch::data::bin_kinds::bitnot_>(expr->l)) {

                              return expr->l->l;
                        }

                        /* ~(? | -CONSTANT) */
                        if (tools::exprs::values::is_arith<il::arch::data::bin_kinds::or_>(expr->l) && expr->l->r->is_integral() && expr->l->r->extract_integral() < 0) {
                              expr->l->l = tools::exprs::generate::unary(expr->l->l, il::arch::data::bin_kinds::bitnot_);
                              expr->l->b = il::arch::data::bin_kinds::and_;
                              expr->l->r->n = (-expr->l->r->n) - 1;
                              return expr->l;
                        }
                        break;
                  }
                  case il::arch::data::bin_kinds::not_: {

                        if (pm.env_flags.fprimitive_object) {

                              /* not {PRIMITIVE Implicit} */
                              if (const auto implicit = tools::exprs::evaluate::is_implicit(expr->l, pm.env_flags.fprimitive_object); implicit != LURAMAS_IR_EVAL_KINDS::nothing) {

                                    return tools::exprs::generate::boolean(implicit == LURAMAS_IR_EVAL_KINDS::false_);
                              }
                        } else {

                              /* not {Integral} */
                              if (expr->l->is_integral()) {
                                    const auto e = expr->l;
                                    e->n = -e->n;
                                    return e;
                              }
                        }

                        /* not CMP */
                        if (tools::exprs::values::is_basic_condition(expr->l)) {
                              const auto e = expr->l;
                              e->b = il::arch::data::bin_kindflip(e->b);
                              return e;
                        }

                        /* not not not (??) */
                        if (tools::exprs::values::is_unary<il::arch::data::bin_kinds::not_>(expr->l) && tools::exprs::values::is_unary<il::arch::data::bin_kinds::not_>(expr->l->l)) {

                              return expr->l->l;
                        }

                        break;
                  }
                  case il::arch::data::bin_kinds::len_: {

                        /* #"??" */
                        if (pm.env_flags.fstring_basic_len) {

                              if (tools::exprs::values::is_string(expr->l)) {

                                    return tools::exprs::generate::integral(expr->l->v.length() - 2u);
                              }
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return nullptr;
      }

      std::shared_ptr<ir_stat::ir_expr> arith(passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &expr, const std::optional<types::map> &tmap) {

            if (!exprs::values::is_arith(expr) || !expr->l || !expr->r || (expr->l->is_integral() && expr->r->is_integral())) {
                  return nullptr;
            }

            /* BOOLEAN ARITH? */
            if (!pm.env_flags.fprimitive_object) {
                  if (exprs::values::is_boolean(expr->l)) {
                        expr->l = exprs::generate::integral(expr->l->bv);
                        return expr;
                  }
                  if (exprs::values::is_boolean(expr->r)) {
                        expr->r = exprs::generate::integral(expr->r->bv);
                        return expr;
                  }
            }

            /* USE CSE TABLE */
            if (pm.env_flags.fexprcanon_use_table) {
                  for (const auto &i : tables::data::arith::table) {
                        if (!pm.env_flags.fuse_bitwise && tools::contains::is(i.val->extract_ordered_exprs(), il::arch::data::is_kinds::bitwise)) {
                              continue;
                        }
                        if (const auto p = tables::data::arith::replace(expr, i); p) {
                              return p;
                        }
                  }
            }

            switch (expr->b) {
                  case luramas::il::arch::data::bin_kinds::add_: {

                        /* 0 + ? */
                        if (expr->l->is_integral(0)) {
                              return expr->r;
                        }

                        /* ? + 0 */
                        if (expr->r->is_integral(0)) {
                              return expr->l;
                        }

                        /* ? + -INTEGRAL */
                        if (expr->r->is_integral() && !expr->r->is_max_integral() && !expr->r->is_min_integral() && expr->r->extract_integral() < 0) {
                              expr->r->curr_replace(math::abs(expr->r->extract_integral()));
                              expr->b = luramas::il::arch::data::bin_kinds::sub_;
                              return expr;
                        }

                        /* ? + {0 > INT} */
                        if (expr->r->is_integral()) {
                              if (const auto it = expr->r->extract_integral(); it < 0) {
                                    expr->r->curr_replace(-it);
                                    expr->b = luramas::il::arch::data::bin_kinds::sub_;
                                    return expr;
                              }
                        }

                        /* ? + (-??) */
                        if (tools::exprs::values::is_unary<il::arch::data::bin_kinds::minus_>(expr->r)) {
                              expr->r = expr->r->l;
                              expr->b = luramas::il::arch::data::bin_kinds::sub_;
                              return expr;
                        }

                        /* UNSIGN + UNSIGN (UNSIGN == UNSIGN) */
                        if (tools::exprs::values::types::is_under_unsigned(expr->l) && tools::exprs::values::types::is_under_unsigned(expr->r) && tools::exprs::values::types::is_same_implicit(expr->l, expr->r)) {
                              const auto t = expr->l->non_native->under;
                              expr->l = expr->l->l;
                              expr->r = expr->r->l;
                              return tools::exprs::generate::cast(expr, t);
                        }

                        /* (?? + CONSTANT) + CONSTANT */
                        if (expr->r->is_integral() && tools::exprs::values::is_arith<il::arch::data::bin_kinds::add_>(expr->l) && expr->l->r->is_integral()) {
                              expr->l->r->n += expr->r->n;
                              return expr->l;
                        }

                        /* (?? - CONSTANT) + CONSTANT */
                        if (expr->r->is_integral() && tools::exprs::values::is_arith<il::arch::data::bin_kinds::sub_>(expr->l) && expr->l->r->is_integral()) {
                              expr->l->r->n = expr->r->n - expr->l->r->n;
                              return expr->l;
                        }

                        /* (?? - CONSTANT) + CONSTANT [CONSTANT_2 - CONSTANT_1 == 0] */
                        if (expr->r->is_integral() && tools::exprs::values::is_arith<il::arch::data::bin_kinds::sub_>(expr->l->c()) && expr->l->c()->r->is_integral() &&
                            !(expr->l->c()->r->extract_integral() - expr->r->extract_integral())) {

                              return expr->l->c()->l;
                        }

                        /* (?? << CONSTANT) + ??) */
                        if (tools::exprs::values::is_arith<il::arch::data::bin_kinds::shl_>(expr->l) && expr->l->r->is_integral() && *expr->l->l == *expr->r) {

                              expr->l->b = luramas::il::arch::data::bin_kinds::mul_;
                              expr->l->r->n = luramas::math::pow(2u, expr->l->r->n) + 1u;
                              return expr->l;
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::sub_: {

                        /* 0 - ? */
                        if (expr->l->is_integral(0)) {
                              return exprs::generate::unary(expr->r, luramas::il::arch::data::bin_kinds::minus_);
                        }

                        /* ? - 0 */
                        if (expr->r->is_integral(0)) {
                              return expr->l;
                        }

                        /* ? - {0 > INT} */
                        if (expr->r->is_integral() && !expr->r->is_max_integral() && !expr->r->is_min_integral()) {
                              if (const auto it = expr->r->extract_integral(); it < 0) {
                                    expr->r->curr_replace(luramas::math::abs(it));
                                    expr->b = luramas::il::arch::data::bin_kinds::add_;
                                    return expr;
                              }
                        }

                        /* ? - (-??) */
                        if (exprs::values::is_unary<il::arch::data::bin_kinds::minus_>(expr->r)) {
                              expr->r = expr->r->l;
                              expr->b = luramas::il::arch::data::bin_kinds::add_;
                              return expr;
                        }

                        /* (?? + CONSTANT) - CONSTANT */
                        if (expr->r->is_integral() && tools::exprs::values::is_arith<il::arch::data::bin_kinds::add_>(expr->l) && expr->l->r->is_integral()) {
                              expr->l->r->n -= expr->r->n;
                              return expr->l;
                        }

                        /* (?? - CONSTANT) - CONSTANT */
                        if (expr->r->is_integral() && tools::exprs::values::is_arith<il::arch::data::bin_kinds::sub_>(expr->l) && expr->l->r->is_integral()) {
                              expr->l->r->n = -expr->l->r->n - expr->r->n;
                              return expr->l;
                        }

                        /* (?? + CONSTANT) - CONSTANT [CONSTANT_1 - CONSTANT_2 == 0] */
                        if (expr->r->is_integral() && tools::exprs::values::is_arith<il::arch::data::bin_kinds::add_>(expr->l->c()) && expr->l->c()->r->is_integral() &&
                            !(expr->r->extract_integral() - expr->l->c()->r->extract_integral())) {

                              return expr->l->c()->l;
                        }

                        /* (?? << CONSTANT) - ??) */
                        if (tools::exprs::values::is_arith<il::arch::data::bin_kinds::shl_>(expr->l) && expr->l->r->is_integral() && *expr->l->l == *expr->r) {

                              expr->l->b = luramas::il::arch::data::bin_kinds::mul_;
                              expr->l->r->n = luramas::math::pow(2, expr->l->r->n) - 1;
                              return expr->l;
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::and_: {

                        /* (? & n) & n */
                        if (expr->r->is_integral() && tools::exprs::values::is_arith<il::arch::data::bin_kinds::and_>(expr->l) && expr->l->r && expr->l->r->is_integral() && expr->r->extract_integral() == expr->l->r->extract_integral()) {
                              return expr->l;
                        }

                        /* (~((expr)) & n) & n) */
                        if (expr->r->is_integral() && tools::exprs::values::is_unary<il::arch::data::bin_kinds::bitnot_>(expr->l) && tools::exprs::values::is_arith<il::arch::data::bin_kinds::and_>(expr->l->l) &&
                            expr->l->l->r && expr->l->l->r->is_integral() && expr->r->extract_integral() == expr->l->l->r->extract_integral()) {
                              return expr->l;
                        }

                        /* 0 & ?(NO VOLATILES) */
                        if (expr->l->is_integral(0) && !expr->l->contains_volatile()) {
                              return tools::exprs::generate::integral(0);
                        }

                        /* ?(NO VOLATILES) & 0 */
                        if (expr->r->is_integral(0) && !expr->r->contains_volatile()) {
                              return tools::exprs::generate::integral(0);
                        }

                        /* (a ^ ~b) & a */
                        if (exprs::values::is_arith<il::arch::data::bin_kinds::xor_>(expr->l) && exprs::values::is_unary<il::arch::data::bin_kinds::bitnot_>(expr->l->r) &&
                            *expr->l->l == *expr->r) {

                              const auto l = expr->r;
                              const auto r = expr->l->r->l;
                              expr->l = l;
                              expr->r = r;
                              expr->b = luramas::il::arch::data::bin_kinds::and_;
                              return expr;
                        }

                        /* (a | b) & (a | ~b) */
                        if (exprs::values::is_arith<il::arch::data::bin_kinds::or_>(expr->l) && exprs::values::is_arith<il::arch::data::bin_kinds::or_>(expr->r) &&
                            tools::exprs::values::is_unary<il::arch::data::bin_kinds::bitnot_>(expr->r->r) &&
                            *expr->l->l == *expr->r->l && *expr->l->r == *expr->r->r->l) {

                              return expr->l->l;
                        }

                        /* (cast<Tn>(a) >> {n - 1}) & 1 */
                        if (exprs::values::is_arith<il::arch::data::bin_kinds::shr_>(expr->l) && expr->r->is_integral(1u) &&
                            exprs::values::is_cast(expr->l->l, luramas::types::signess::sign) && expr->l->l->non_native->under.bits() &&
                            expr->l->r->is_integral(expr->l->l->non_native->under.bits() - 1u)) {

                              return exprs::generate::cond(expr->l->l, luramas::il::arch::data::bin_kinds::lt_, exprs::generate::integral(0u));
                        }

                        /* (SIZE & bitmask(n) */
                        if (expr->r->is_integral()) {

                              if (const auto type = tools::types::extract_expr_type(expr->l); type && type.basic()) {

                                    if (auto n = expr->r->extract_integral(); !n.precise()) {

                                          std::uint16_t s = 0u;
                                          std::uint16_t e = 0u;
                                          if (n = n.extend(type.type->under.bits(), type.type->under.unsign); math::is::range_mask(n, s, e)) {

                                                return exprs::generate::bitread(expr->l, exprs::generate::integral(s), exprs::generate::integral(e), type.type);
                                          }
                                    }
                              }
                        }

                        /* a & 1 */
                        if (expr->r->is_integral(1u)) {
                              expr->b = il::arch::data::bin_kinds::mod_;
                              expr->r->n = luramas_int(2u);
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::mul_: {

                        /* 1 * ? */
                        if (expr->l->is_integral(1)) {
                              return expr->r;
                        }

                        /* ? * 1 */
                        if (expr->r->is_integral(1)) {
                              return expr->l;
                        }

                        /* 0 * ? */
                        if (expr->l->is_integral(0) && !expr->r->contains_volatile()) {
                              return tools::exprs::generate::integral(0);
                        }

                        /* ? * 0 */
                        if (expr->r->is_integral(0) && !expr->l->contains_volatile()) {
                              return tools::exprs::generate::integral(0);
                        }

                        /* (? * INTEGRAL) * INTEGRAL */
                        if (expr->r->is_integral() && tools::exprs::values::is_arith<il::arch::data::bin_kinds::mul_>(expr->l) && expr->l->r->is_integral()) {

                              if (luramas_int n = 0; tools::safety::combine_integrals(expr->r, expr->l->r, n, il::arch::data::bin_kinds::mul_)) {
                                    expr->l->r->curr_replace(n);
                                    return expr->l;
                              }
                        }

                        /* INTEGRAL * (INTEGRAL * ?) */
                        if (expr->l->is_integral() && tools::exprs::values::is_arith<il::arch::data::bin_kinds::mul_>(expr->r) && expr->r->l->is_integral()) {

                              if (luramas_int n = 0; tools::safety::combine_integrals(expr->l, expr->r->l, n, il::arch::data::bin_kinds::mul_)) {
                                    expr->r->l->curr_replace(n);
                                    return expr->r;
                              }
                        }

                        /* ? * -1 */
                        if (expr->r->is_integral(-1)) {
                              return exprs::generate::unary(expr->l, il::arch::data::bin_kinds::minus_);
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::or_: {

                        /* 0 | ? */
                        if (expr->l->is_integral(0)) {
                              return expr->r;
                        }
                        /* ? | 0 */
                        if (expr->r->is_integral(0)) {
                              return expr->l;
                        }

                        /* (a & b) | (a & ~b) */
                        if (exprs::values::is_arith<il::arch::data::bin_kinds::and_>(expr->l) && exprs::values::is_arith<il::arch::data::bin_kinds::and_>(expr->r) &&
                            tools::exprs::values::is_unary<il::arch::data::bin_kinds::bitnot_>(expr->r->r) &&
                            *expr->l->l == *expr->r->l && *expr->l->r == *expr->r->r->l) {

                              return expr->l->l;
                        }

                        /* (a & b) | (~a & b) */
                        if (exprs::values::is_arith<il::arch::data::bin_kinds::and_>(expr->l) && exprs::values::is_arith<il::arch::data::bin_kinds::and_>(expr->r) &&
                            tools::exprs::values::is_unary<il::arch::data::bin_kinds::bitnot_>(expr->r->l) &&
                            *expr->l->l == *expr->r->l->l && *expr->l->r == *expr->r->r) {

                              return expr->l->r;
                        }

                        /* (~a & b) | (a & ~b) */
                        if (exprs::values::is_arith<il::arch::data::bin_kinds::and_>(expr->l) && exprs::values::is_arith<il::arch::data::bin_kinds::and_>(expr->r) &&
                            tools::exprs::values::is_unary<il::arch::data::bin_kinds::bitnot_>(expr->l->l) && tools::exprs::values::is_unary<il::arch::data::bin_kinds::bitnot_>(expr->r->r) &&
                            *expr->l->l->l == *expr->r->l && *expr->l->r == *expr->r->r->l) {

                              const auto l = expr->r->l;
                              const auto r = expr->l->r;
                              expr->l = l;
                              expr->r = r;
                              expr->b = luramas::il::arch::data::bin_kinds::xor_;
                              return expr;
                        }

                        /* (a & b) | (a ^ b) */
                        if (exprs::values::is_arith<il::arch::data::bin_kinds::and_>(expr->l) && exprs::values::is_arith<il::arch::data::bin_kinds::xor_>(expr->r) &&
                            *expr->l->l == *expr->r->l && *expr->l->r == *expr->r->r) {

                              const auto l = expr->l->l;
                              const auto r = expr->l->r;
                              expr->l = l;
                              expr->r = r;
                              expr->b = luramas::il::arch::data::bin_kinds::or_;
                              return expr;
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::xor_: {

                        /* ? xor ? */
                        if (*expr->l == *expr->r) {
                              return tools::exprs::generate::integral(0);
                        }

                        /* a xor (a & b) */
                        if (exprs::values::is_arith<il::arch::data::bin_kinds::and_>(expr->r) && *expr->l == *expr->r->l) {

                              const auto l = expr->l;
                              const auto r = exprs::generate::unary(expr->r->r, il::arch::data::bin_kinds::bitnot_);
                              expr->l = l;
                              expr->r = r;
                              expr->b = luramas::il::arch::data::bin_kinds::and_;
                              return expr;
                        }

                        /* a xor (a | b) */
                        if (exprs::values::is_arith<il::arch::data::bin_kinds::or_>(expr->r) && *expr->l == *expr->r->l) {

                              const auto l = exprs::generate::unary(expr->l, il::arch::data::bin_kinds::bitnot_);
                              const auto r = expr->r->r;
                              expr->l = l;
                              expr->r = r;
                              expr->b = luramas::il::arch::data::bin_kinds::and_;
                              return expr;
                        }

                        for (const auto &[l, r] : {std::make_pair(expr->l, expr->r), std::make_pair(expr->r, expr->l)}) {

                              if (l->is_integral()) {

                                    /* ANY MAX INT xor ?? */
                                    if (const auto byte_count = math::count_byte_max(l->extract_integral()); byte_count) {

                                          if (!pm.env_flags.fcast_power_of_2 || math::is::power_of_2(byte_count)) {

                                                return exprs::generate::unary(tools::guarantee::exprs::cast(r, luramas::types::underlying_type(false, luramas::types::read_type::bits, 0u, byte_count * 8u), true), luramas::il::arch::data::bin_kinds::bitnot_);
                                          }
                                    }
                              }
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::pow_: {

                        /* 1 ^ ? */
                        if (expr->l->is_integral(1) && !expr->r->contains_volatile()) {
                              return tools::exprs::generate::integral(1);
                        }
                        /* ? ^ 1 */
                        if (expr->r->is_integral(1)) {
                              return expr->l;
                        }

                        /* 0 ^ ? */
                        if (expr->l->is_integral(0) && !expr->r->contains_volatile()) {
                              return tools::exprs::generate::integral(0);
                        }
                        /* ? ^ 0 */
                        if (expr->r->is_integral(0) && !expr->l->contains_volatile()) {
                              return tools::exprs::generate::integral(1);
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::shl_: {

                        /* ? << 0 */
                        if (expr->r->is_integral(0)) {
                              return expr->l;
                        }

                        /* (? << n) << n */
                        if (expr->r->is_integral() && tools::exprs::values::is_arith<luramas::il::arch::data::bin_kinds::shl_>(expr->l) && expr->l->r->is_integral()) {
                              expr->l->r->n += expr->l->extract_integral();
                              return expr->l;
                        }

                        /* ((?? * CONSTANT) << CONSTANT) */
                        if (tools::exprs::values::is_arith<il::arch::data::bin_kinds::mul_>(expr->l) && expr->l->r->is_integral() && expr->r->is_integral()) {

                              expr->l->r->n *= luramas::math::pow(2u, expr->r->n);
                              return expr->l;
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::shr_: {

                        /* ? >> 0 */
                        if (expr->r->is_integral(0)) {
                              return expr->l;
                        }

                        /* (? >> n) >> n */
                        if (expr->r->is_integral() && tools::exprs::values::is_arith<luramas::il::arch::data::bin_kinds::shr_>(expr->l) && expr->l->r->is_integral()) {
                              expr->l->r->n += expr->l->extract_integral();
                              return expr->l;
                        }

                        if (tmap) {

                              /* R >> INT */
                              if (tools::exprs::values::is_general_purpose_register(expr->l) && expr->r->is_integral()) {

                                    if (const auto types = tools::types::get_types(expr->l, *tmap); types && types->size() == 1u) {

                                          /* int8_t >> 7 */
                                          if (*types->front() == luramas::types::native::t_int8 && expr->r->extract_integral() == 7u) {

                                                return tools::exprs::generate::cond(expr->l, il::arch::data::bin_kinds::lt_, tools::exprs::generate::integral(0u));
                                          }

                                          /* int16_t >> 15 */
                                          if (*types->front() == luramas::types::native::t_int16 && expr->r->extract_integral() == 15u) {

                                                return tools::exprs::generate::cond(expr->l, il::arch::data::bin_kinds::lt_, tools::exprs::generate::integral(0u));
                                          }

                                          /* int32_t >> 31 */
                                          if (*types->front() == luramas::types::native::t_int32 && expr->r->extract_integral() == 31u) {

                                                return tools::exprs::generate::cond(expr->l, il::arch::data::bin_kinds::lt_, tools::exprs::generate::integral(0u));
                                          }

                                          /* int64_t >> 63 */
                                          if (*types->front() == luramas::types::native::t_int64 && expr->r->extract_integral() == 63u) {

                                                return tools::exprs::generate::cond(expr->l, il::arch::data::bin_kinds::lt_, tools::exprs::generate::integral(0u));
                                          }
                                    }
                              }
                        }
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::mod_: {

                        /* (a[NO VOLATILES] * 2) % 2 */
                        if (expr->r->is_integral(2u) && tools::exprs::values::is_arith<il::arch::data::bin_kinds::mul_>(expr->l) && expr->l->r->is_integral(2u) &&
                            !expr->l->l->contains_volatile()) {
                              return tools::exprs::generate::integral(0u);
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return nullptr;
      }

      std::shared_ptr<ir_stat::ir_expr> cond(passes::pass_manager &pm, std::shared_ptr<ir_stat::ir_expr> &expr) {

            if (expr->k != expr_kinds::condition) {
                  return nullptr;
            }

            /* ? ?? ? */
            if (expr->r) {

                  /* L == R */
                  if (*expr->r == *expr->l) {
                        switch (expr->b) {
                              case luramas::il::arch::data::bin_kinds::ne_:
                              case luramas::il::arch::data::bin_kinds::lt_:
                              case luramas::il::arch::data::bin_kinds::gt_: {
                                    return tools::exprs::generate::boolean(false);
                              }
                              case luramas::il::arch::data::bin_kinds::eq_:
                              case luramas::il::arch::data::bin_kinds::lte_:
                              case luramas::il::arch::data::bin_kinds::gte_: {
                                    return tools::exprs::generate::boolean(true);
                              }
                              case luramas::il::arch::data::bin_kinds::and_:
                              case luramas::il::arch::data::bin_kinds::or_: {
                                    return expr->l;
                              }
                              default: {
                                    switch (expr->e) {
                                          case expr_logical::or_:
                                          case expr_logical::and_: {
                                                return expr->l;
                                          }
                                          default: {
                                                break;
                                          }
                                    }
                                    break;
                              }
                        }
                        return nullptr;
                  }

                  if (expr->e != expr_logical::nothing) {

                        /* Compute logical */
                        if (const auto eval = tools::compute::compute(expr->l, expr->r, expr->e, pm.env_flags.fprimitive_object); eval) {
                              return eval;
                        }
                  }

                  /* BOOLEAN int */
                  if (pm.env_flags.fprimitive_object) {

                        /* BOOLEAN ?? INTEGRAL */
                        if (expr->l->is_tk<tkind::boolean>() && expr->r->is_integral()) {
                              const auto bv = tools::compute::compute<luramas_int, luramas_int, bool>(luramas_int(expr->l->bv), expr->r->n, expr->b);
                              expr->l->clear();
                              expr->l->emit_boolean(bv);
                              return expr->l;
                        }

                        /* INTEGRAL ?? BOOLEAN */
                        if (expr->l->is_integral() && expr->r->is_tk<tkind::boolean>()) {
                              const auto bv = tools::compute::compute<luramas_int, luramas_int, bool>(expr->l->n, luramas_int(expr->r->bv), expr->b);
                              expr->l->clear();
                              expr->l->emit_boolean(bv);
                              return expr->l;
                        }
                  }

                  /* BOOLEAN ?? BOOLEAN */
                  if (expr->l->is_tk<tkind::boolean>() && expr->r->is_tk<tkind::boolean>()) {
                        const auto bv = tools::compute::compute<bool, bool, bool>(expr->l->bv, expr->r->bv, expr->b);
                        expr->l->clear();
                        expr->l->emit_boolean(bv);
                        return expr->l;
                  }

                  /* INTEGRAL ?? INTEGRAL */
                  if (expr->l->is_integral() && expr->r->is_integral()) {
                        const auto bv = tools::compute::compute<luramas_int, luramas_int, bool>(expr->l->n, expr->r->n, expr->b);
                        expr->l->clear();
                        expr->l->emit_boolean(bv);
                        return expr->l;
                  }

                  /* COMPARITIVE OR 0 */
                  if (!pm.env_flags.fprimitive_object && tools::exprs::branch::is_equality_compare(expr->l) && expr->e == expr_logical::or_ && expr->r->is_integral(0)) {
                        return expr->l;
                  }

                  /* != BOOLEAN */
                  if (expr->b == il::arch::data::bin_kinds::ne_ && expr->r->is_tk<tkind::boolean>()) {
                        tools::exprs::mutate::flip_cmp(expr);
                        expr->r->bv = !expr->r->bv;
                        return expr;
                  }

                  /* (? - ?) == 0 */
                  if (expr->b == il::arch::data::bin_kinds::eq_ && expr->r->is_integral(0) && tools::exprs::values::is_arith<il::arch::data::bin_kinds::sub_>(expr->l)) {
                        const auto &l = expr->l->l;
                        const auto &r = expr->l->r;
                        expr->l = l;
                        expr->r = r;
                        return expr;
                  }

                  /* (? - ?) != 0 */
                  if (expr->b == il::arch::data::bin_kinds::ne_ && expr->r->is_integral(0) && tools::exprs::values::is_arith<il::arch::data::bin_kinds::sub_>(expr->l)) {
                        const auto &l = expr->l->l;
                        const auto &r = expr->l->r;
                        expr->l = l;
                        expr->r = r;
                        return expr;
                  }

                  /* (x >> 56) & 0xFF == 0 */
                  /* (x[x_T.bits() > b] >> b) & ([~((x_T.bits() - b)_t(0))])  == 0 */
                  if (expr->b == il::arch::data::bin_kinds::eq_ && expr->r->is_integral(0u) && exprs::values::is_arith<il::arch::data::bin_kinds::and_>(expr->l) && expr->l->r->is_integral() &&
                      exprs::values::is_arith<il::arch::data::bin_kinds::shr_>(expr->l->l) && expr->l->l->r->is_integral()) {

                        const auto b = expr->l->l->r->extract_integral_base();
                        const auto x_t = types::extract_expr_type(expr->l->l->l);

                        if (x_t.basic()) {

                              if (const auto bits = x_t.type->under.bits(); bits > b && expr->l->r->extract_integral() == luramas_int(0u).mask(bits - b)) {

                                    x_t.type->under.unsign = true;
                                    expr->l = expr->l->l;
                                    expr->l->l = tools::exprs::generate::cast(expr->l->l, x_t.type);
                                    return expr;
                              }
                        }
                  }

                  /* (? ?? ?) or (? ?? ?)  *AND* ? == ?*/
                  if (expr->e == expr_logical::or_ && exprs::branch::same_logical_operands(expr->l, expr->r)) {

                        const auto l = expr->l->l;
                        const auto r = expr->l->r;

                        /* (? < ?) or (? == ?) */
                        if (expr->l->is_b<il::arch::data::bin_kinds::lt_>() && expr->r->is_b<il::arch::data::bin_kinds::eq_>()) {
                              expr->clear();
                              expr->emit_cond(l, il::arch::data::bin_kinds::lte_, r);
                              return expr;
                        }
                        /* (? == ?) or (? < ?) */
                        if (expr->l->is_b<il::arch::data::bin_kinds::eq_>() && expr->r->is_b<il::arch::data::bin_kinds::lt_>()) {
                              expr->clear();
                              expr->emit_cond(l, il::arch::data::bin_kinds::lte_, r);
                              return expr;
                        }

                        /* (? > ?) or (? == ?) */
                        if (expr->l->is_b<il::arch::data::bin_kinds::gt_>() && expr->r->is_b<il::arch::data::bin_kinds::eq_>()) {
                              expr->clear();
                              expr->emit_cond(l, il::arch::data::bin_kinds::gte_, r);
                              return expr;
                        }
                        /* (? == ?) or (? > ?) */
                        if (expr->l->is_b<il::arch::data::bin_kinds::eq_>() && expr->r->is_b<il::arch::data::bin_kinds::gt_>()) {
                              expr->clear();
                              expr->emit_cond(l, il::arch::data::bin_kinds::gte_, r);
                              return expr;
                        }
                  }

                  /* {NO VOLATILES} and false */
                  if (expr->e == expr_logical::and_ && tools::exprs::values::is_boolean(expr->r, false) && !expr->l->contains_volatile()) {
                        expr->clear();
                        expr->emit_cond(tools::exprs::generate::boolean(false), il::arch::data::bin_kinds::et_);
                        return expr;
                  }
            } else {

                  switch (expr->b) {
                        case luramas::il::arch::data::bin_kinds::not_: {

                              /* not (not ??) */
                              if (tools::exprs::values::is_condition(expr->l, false) && expr->l->b == luramas::il::arch::data::bin_kinds::not_) {
                                    expr->l->b = luramas::il::arch::data::bin_kinds::et_;
                                    return expr->l;
                              }

                              /* not {BOOLEAN} */
                              if (tools::exprs::values::is_boolean(expr->l) && expr->l->b == luramas::il::arch::data::bin_kinds::not_) {
                                    expr->l->b = luramas::il::arch::data::bin_kinds::et_;
                                    expr->l->bv = !expr->l->bv;
                                    return expr->l;
                              }

                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::et_:
                        case luramas::il::arch::data::bin_kinds::nothing: {
                              return expr->l;
                        }
                        case luramas::il::arch::data::bin_kinds::nt_: {

                              /* BOOLEAN */
                              if (expr->l->is_tk<tkind::boolean>()) {
                                    tools::exprs::mutate::flip_cmp(expr);
                                    expr->l->bv = !expr->l->bv;
                                    return expr;
                              }

                              /* not (not ) */
                              if (expr->l->u == luramas::il::arch::data::bin_kinds::not_ || expr->l->b == luramas::il::arch::data::bin_kinds::nt_) {
                                    expr->l->k = expr_kinds::condition;
                                    expr->l->b = luramas::il::arch::data::bin_kinds::et_;
                                    expr->l->u = luramas::il::arch::data::bin_kinds::nothing;
                                    return expr->l;
                              }

                              /* not {OBJECT PRIMITIVES} */
                              if (pm.env_flags.fprimitive_object && expr->l->is_primitive()) {
                                    return tools::exprs::generate::boolean(false);
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
            return nullptr;
      }
} // namespace luramas::ir::tools::combine