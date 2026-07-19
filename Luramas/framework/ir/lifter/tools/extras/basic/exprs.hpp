#pragma once
#include "../../../../../debug.hpp"
#include "../../../passes.hpp"

namespace luramas::ir::tools::exprs {

      namespace basic {

            template <typename T>
            inline bool is_integral(const std::shared_ptr<T> &expr) {
                  return expr && expr->is_integral();
            }
            template <typename... T>
            inline bool is_integral(const T &...exprs) {
                  return (is_integral(exprs) && ...);
            }
      } // namespace basic

      namespace values {

            /* UNARY? */
            template <il::arch::data::bin_kinds u = il::arch::data::bin_kinds::nothing>
            inline bool is_unary(const std::shared_ptr<ir_stat::ir_expr> &unary) {
                  return unary && unary->is_k<expr_kinds::unary>() && (u == il::arch::data::bin_kinds::nothing || unary->u == u);
            }
            /* TABLE? */
            inline bool is_table(const std::shared_ptr<ir_stat::ir_expr> &tab) {
                  return tab && tab->is_tk<tkind::table>();
            }
            /* EMPTY TABLE? */
            inline bool is_empty_table(const std::shared_ptr<ir_stat::ir_expr> &l) {
                  return is_table(l) && l->members.empty();
            }
            /* SAME REF? */
            inline bool same_reference(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r) {
                  return l && r && ((l->is_register_reference() && r->is_reg(l->reg)) || (l->is_mutable_tk() && r->is_mutable_tk() && l->tk == r->tk && l->v == r->v));
            }
            /* () ? : ? */
            inline bool is_ternary(const std::shared_ptr<ir_stat::ir_expr> &ternary) {
                  return ternary && ternary->is_k<expr_kinds::ternary>() && ternary->xv && ternary->ev;
            }
            /* () ? : EXPR  */
            inline bool is_ternary_else(const std::shared_ptr<ir_stat::ir_expr> &ternary, const std::shared_ptr<ir_stat::ir_expr> &else_expr) {
                  return is_ternary(ternary) && *ternary->xv == *else_expr;
            }
            /* () EXPR : ?  */
            inline bool is_ternary_then(const std::shared_ptr<ir_stat::ir_expr> &ternary, const std::shared_ptr<ir_stat::ir_expr> &then_expr) {
                  return is_ternary(ternary) && *ternary->ev == *then_expr;
            }
            /* CMP == CMP Ternaries  */
            inline bool is_ternary_cmp(const std::shared_ptr<ir_stat::ir_expr> &ternary_r, const std::shared_ptr<ir_stat::ir_expr> &ternary_l) {
                  return is_ternary(ternary_r) && is_ternary(ternary_l) && *ternary_l->l == *ternary_r->l && ternary_l->b == ternary_r->b && ((ternary_l->r == ternary_r->r) || (*ternary_l->r == *ternary_r->r));
            }
            /* CAST? */
            inline bool is_cast(const std::shared_ptr<ir_stat::ir_expr> &cast, const bool basic = false) {
                  return cast && cast->is_k<expr_kinds::cast>() && (!basic || cast->non_native->basic());
            }
            /* CAST? */
            inline bool is_cast(const std::shared_ptr<ir_stat::ir_expr> &cast, const luramas::types::signess signess) {
                  return is_cast(cast, true) && cast->non_native->under.signess_t() == signess;
            }
            /* CAST? */
            inline bool is_cast_reg(const std::shared_ptr<ir_stat::ir_expr> &cast, const luramas_register reg) {
                  return is_cast(cast) && cast->l && cast->l->is_reg(reg);
            }
            /* CAST? */
            inline bool is_cast_reg(const std::shared_ptr<ir_stat::ir_expr> &cast) {
                  return is_cast(cast) && cast->l && cast->l->is_register_reference();
            }
            /* CAST? */
            inline bool is_cast(const std::shared_ptr<ir_stat::ir_expr> &cast, const luramas::types::underlying_type &under, const bool bits = false) {
                  return is_cast(cast, true) && (cast->non_native->under == under || (bits && cast->non_native->under.storage_size == under.storage_size));
            }
            /* CAST? */
            inline bool is_cast(const std::shared_ptr<ir_stat::ir_expr> &cast, const luramas_bitwidth bits, const luramas::types::signess signess = luramas::types::signess::sign) {
                  return is_cast(cast, luramas::types::underlying_type((signess == luramas::types::signess::sign ? false : true), luramas::types::read_type::bits, 0u, bits), true);
            }
            /* CAST? */
            inline bool is_cast(const std::shared_ptr<ir_stat::ir_expr> &cast, const std::shared_ptr<luramas::ir::types::object::type> &obj) {
                  return is_cast(cast) && (cast->non_native == obj || (cast->non_native && obj && *cast->non_native == *obj));
            }
            /* BLANK LVALUE? */
            inline bool is_blank_lvalue(const std::shared_ptr<ir_stat::ir_expr> &blank_lvalue) {
                  return blank_lvalue && blank_lvalue->is_k<expr_kinds::blank_lvalue>();
            }
            /* ARITH? */
            template <il::arch::data::bin_kinds b = il::arch::data::bin_kinds::nothing>
            inline bool is_arith(const std::shared_ptr<ir_stat::ir_expr> &l) {
                  return l && l->is_k<expr_kinds::arith>() && (b == il::arch::data::bin_kinds::nothing || l->b == b);
            }
            /* ARITH? */
            template <il::arch::data::bin_kinds b = il::arch::data::bin_kinds::nothing>
            inline bool is_arith(const std::shared_ptr<ir_stat::ir_expr> &l, const luramas_int &rvalue) {
                  return is_arith<b>(l) && l->r && l->r->is_integral(rvalue);
            }
            /* BOOLEAN? */
            inline bool is_boolean(const std::shared_ptr<ir_stat::ir_expr> &l) {
                  return l && l->is_tk<tkind::boolean>();
            }
            /* BOOLEAN? */
            inline bool is_boolean(const std::shared_ptr<ir_stat::ir_expr> &l, const bool b) {
                  return is_boolean(l) && l->bv == b;
            }
            /* BIT READ? */
            inline bool is_bitread(const std::shared_ptr<ir_stat::ir_expr> &bitread) {
                  return bitread && bitread->is_k<expr_kinds::bitread>();
            }
            /* BIT WRITE? */
            inline bool is_bitwrite(const std::shared_ptr<ir_stat::ir_expr> &bitwrite) {
                  return bitwrite && bitwrite->is_k<expr_kinds::bitwrite>();
            }
            /* MEMORY READ? */
            inline bool is_memoryread(const std::shared_ptr<ir_stat::ir_expr> &memoryread) {
                  return memoryread && memoryread->is_k<expr_kinds::memoryread>();
            }
            /* GENERAL PURPOSE REGISTER? */
            inline bool is_general_purpose_register(const std::shared_ptr<ir_stat::ir_expr> &reg) {
                  return reg && reg->is_k<expr_kinds::reg>();
            }
            /* REGISTER? */
            inline bool is_reg(const std::shared_ptr<ir_stat::ir_expr> &reg) {
                  return is_general_purpose_register(reg) && reg->is_rk<expr_reg_kinds::reg>();
            }
            /* REGISTER? */
            inline bool is_reg(const std::shared_ptr<ir_stat::ir_expr> &reg, const luramas_register r) {
                  return is_reg(reg) && reg->reg == r;
            }
            /* ARGUEMENT? */
            inline bool is_arg(const std::shared_ptr<ir_stat::ir_expr> &arg) {
                  return is_general_purpose_register(arg) && arg->is_rk<expr_reg_kinds::arg>();
            }
            /* UPVALUE? */
            inline bool is_upvalue(const std::shared_ptr<ir_stat::ir_expr> &reg) {
                  return reg && reg->is_k<expr_kinds::upvalue>();
            }
            /* REFERENCE? */
            inline bool is_reference(const std::shared_ptr<ir_stat::ir_expr> &ref) {
                  return ref && is_unary<il::arch::data::bin_kinds::ref_>(ref);
            }
            /* REFERENCE? */
            inline bool is_reference(const std::shared_ptr<ir_stat::ir_expr> &ref, const std::shared_ptr<ir_stat::ir_expr> &v) {
                  return is_reference(ref) && v && *ref->l == *v;
            }
            /* STACK? */
            inline bool is_stack(const std::shared_ptr<ir_stat::ir_expr> &stack, const luramas_int &id = 0u) {
                  return stack && stack->is_tk<tkind::stack>() && stack->n == id;
            }
            /* CONTROLLER? */
            inline bool is_controller(const std::shared_ptr<ir_stat::ir_expr> &controller) {
                  return controller && controller->is_tk<tkind::controller>();
            }
            /* EXTPR? */
            inline bool is_extpr(const std::shared_ptr<ir_stat::ir_expr> &extpr, const luramas_int &id = 0u) {
                  return extpr && extpr->is_tk<tkind::extpr>() && extpr->n == id;
            }
            /* STRING? */
            inline bool is_string(const std::shared_ptr<ir_stat::ir_expr> &str) {
                  return str && str->is_tk<tkind::string>();
            }
            /* LURA INTEGER? */
            inline bool is_integer(const std::shared_ptr<ir_stat::ir_expr> &integer) {
                  return integer && integer->is_tk<tkind::lura_int>();
            }
            /* CALL? */
            inline bool is_call(const std::shared_ptr<ir_stat::ir_expr> &call) {
                  return call && call->is_k<expr_kinds::call>();
            }
            /* CLOSURE? */
            inline bool is_closure(const std::shared_ptr<ir_stat::ir_expr> &closure) {
                  return closure && closure->is_k<expr_kinds::closure>();
            }
            /* KVALUE? */
            inline bool is_kvalue(const std::shared_ptr<ir_stat::ir_expr> &kvalue) {
                  return kvalue && kvalue->is_tk<tkind::kvalue>();
            }
            /* GLOBAL? */
            inline bool is_global(const std::shared_ptr<ir_stat::ir_expr> &global) {
                  return global && global->is_tk<tkind::global>();
            }
            /* NONE OBJ? */
            inline bool is_none_obj(const std::shared_ptr<ir_stat::ir_expr> &none_obj) {
                  return none_obj && none_obj->is_tk<tkind::none_obj>();
            }
            /* OBJECT? */
            inline bool is_object(const std::shared_ptr<ir_stat::ir_expr> &object) {
                  return object && object->is_tk<tkind::object>();
            }
            /* CONCAT? */
            inline bool is_concat(const std::shared_ptr<ir_stat::ir_expr> &concat) {
                  return concat && concat->is_k<expr_kinds::concat>();
            }
            /* CONDITION? */
            template <il::arch::data::bin_kinds b = il::arch::data::bin_kinds::nothing>
            inline bool is_condition(const std::shared_ptr<ir_stat::ir_expr> &condition, const bool logical = true) {
                  return condition && condition->is_k<expr_kinds::condition>() && (b == il::arch::data::bin_kinds::nothing || condition->b == b) && (logical || condition->e == expr_logical::nothing);
            }
            /* LOGICAL CONDITION? */
            inline bool is_logical(const std::shared_ptr<ir_stat::ir_expr> &logical) {
                  return is_condition(logical) && logical->e != expr_logical::nothing;
            }
            /* BASIC CONDITION (NOT LOGICAL)? */
            inline bool is_basic_condition(const std::shared_ptr<ir_stat::ir_expr> &condition) {
                  return is_condition(condition) && !is_logical(condition);
            }
            /* BASIC CONDITION (NOT LOGICAL)? */
            inline bool is_anonfunction_call(const std::shared_ptr<ir_stat::ir_expr> &call) {
                  return is_call(call) && is_closure(call->l);
            }
            /* FLAG? */
            inline bool is_flag(const std::shared_ptr<ir_stat::ir_expr> &flag) {
                  return flag && flag->is_k<expr_kinds::flag>();
            }
            /* SELF REFERENTIAL ARITH REGISTER? (x ? (x ? ??))*/
            inline bool is_self_referential_arith_register(const std::shared_ptr<ir_stat::ir_expr> &stat) {
                  return is_arith(stat) && is_arith(stat->r) && is_reg(stat->l) && is_reg(stat->r->l) && *stat->l == *stat->r->l;
            }
            /* PAGE FUNCTION CALL? */
            inline bool is_page_function_call(const std::shared_ptr<ir_stat::ir_expr> &page_function_call_stat) {
                  return page_function_call_stat && page_function_call_stat->is_k<expr_kinds::page_function_call>();
            }
            /* PAGE FUNCTION CALL? */
            inline bool is_page_function_call(const std::shared_ptr<ir_stat::ir_expr> &page_function_call_stat, const luramas_id id) {
                  return is_page_function_call(page_function_call_stat) && page_function_call_stat->r && page_function_call_stat->r->is_integral(id);
            }
            /* (?? ? CONTROLLER)? */
            inline bool is_cond_controller(const std::shared_ptr<ir_stat::ir_expr> &cond_controller) {
                  return is_condition(cond_controller) && is_controller(cond_controller->l) && cond_controller->r;
            }
            /* VIRTUALIZED FUNCTION? */
            inline bool is_virtualized_function(const std::shared_ptr<ir_stat::ir_expr> &vf) {
                  return is_call(vf) && vf->flags.fvirtualized;
            }
            /* INT?? */
            inline bool is_integer(const std::shared_ptr<ir_stat::ir_expr> &expr, const luramas_int &n) {
                  return is_integer(expr) && expr->n == n;
            }
            namespace types {

                  /* BASIC? */
                  inline bool is_basic(const std::shared_ptr<ir::types::object::type> &type) {
                        return type && type->basic();
                  }
                  /* IS SAME L AND R VALUES HAVE SAME IMPLICIT CAST? */
                  inline bool is_same_implicit(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r) {
                        return (l->non_native == r->non_native) || (l->non_native && r->non_native && l->non_native->compare(*r->non_native));
                  }
                  /* IS EXPR RESTRICTED BY NON NATIVE? */
                  inline bool is_restricted(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                        return expr && expr->non_native;
                  }
                  /* IS RESULTING TYPE? */
                  inline bool is_resulting_type(const std::shared_ptr<ir_stat::ir_expr> &expr, const luramas::types::underlying_type &ut) {
                        return is_restricted(expr) && *expr->non_native == ut;
                  }
                  /* IS THERE AN UNDERLYING TYPE AND IS IT SIGNED? */
                  inline bool is_under_signed(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                        return is_restricted(expr) && expr->non_native->basic() && !expr->non_native->under.unsign;
                  }
                  /* IS THERE AN UNDERLYING TYPE AND IS IT UNSIGNED? */
                  inline bool is_under_unsigned(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                        return is_restricted(expr) && expr->non_native->basic() && expr->non_native->under.unsign;
                  }
                  /* IS EXPR UNRESTRICTED OR IF IT IS UNDER SIGNED?*/
                  inline bool is_unrestricted_under_signed(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                        return !is_restricted(expr) && is_under_signed(expr);
                  }
                  /* IS EXPR CASTING JUST A REGISTER?*/
                  inline bool is_reg_cast(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                        return is_cast(expr) && is_general_purpose_register(expr->l);
                  }
                  /* Is integral boolean (0 or 1)? */
                  inline bool is_boolean_integral(const std::shared_ptr<ir_stat::ir_expr> &integral) {
                        return integral && (integral->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_FALSE) || integral->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_TRUE));
                  }
                  /* IS EXPR CAST BOOLEAN? */
                  inline bool is_boolean_cast(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                        return is_cast(expr) && is_basic(expr->non_native) && expr->non_native->under.bits() == 1u && expr->non_native->under.unsign;
                  }
                  /* HAS XTYPE? */
                  inline bool has_xtype(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                        return expr && expr->xtype;
                  }
                  /* VIRUTALIZED FUNCTION HAS RETURN TYPE? */
                  inline bool is_virtualized_function_rtype(const std::shared_ptr<ir_stat::ir_expr> &vf) {
                        return is_virtualized_function(vf) && vf->non_native;
                  }
            } // namespace types

            namespace test {

                  /* CMP (!=/==) (0/1) */
                  inline bool is_boolean_comparision(const std::shared_ptr<ir_stat::ir_expr> &l, const il::arch::data::bin_kinds b, const std::shared_ptr<ir_stat::ir_expr> &r) {
                        return l && r && l->r && is_condition(l, false) && (b == il::arch::data::bin_kinds::eq_ || b == il::arch::data::bin_kinds::ne_) && types::is_boolean_integral(r);
                  }
                  /* (?? (!=/==) ??) (!=/==) (0/1) */
                  inline bool is_boolean_identity(const std::shared_ptr<ir_stat::ir_expr> &l, const il::arch::data::bin_kinds b, const std::shared_ptr<ir_stat::ir_expr> &r) {
                        return is_boolean_comparision(l, b, r) && (l->b == il::arch::data::bin_kinds::eq_ || l->b == il::arch::data::bin_kinds::ne_);
                  }
                  /* 0/1? */
                  inline bool is_comparative_integral(const std::shared_ptr<ir_stat::ir_expr> &integral) {
                        return integral && (integral->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_FALSE) || integral->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_TRUE));
                  }
                  /* 0/1? */
                  inline bool is_comparative_integral(const std::shared_ptr<ir_stat::ir_expr> &integral, const bool v) {
                        return is_comparative_integral(integral) && ((v && integral->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_TRUE)) || (!v && integral->is_integral(LURAMAS_IR_COMPARATIVE_NON_OBJECT_FALSE)));
                  }
            } // namespace test

            namespace bitwise {

                  /* SAME BITREAD INTEGRALS RANGE */
                  inline bool same_bitread_integrals_range(const std::shared_ptr<ir_stat::ir_expr> &bitread_l, const std::shared_ptr<ir_stat::ir_expr> &bitread_r) {
                        return is_bitwrite(bitread_l) && is_bitwrite(bitread_r) && basic::is_integral(bitread_l->ev, bitread_l->xv, bitread_r->ev, bitread_r->xv) && *bitread_l->ev == *bitread_r->ev && *bitread_l->xv == *bitread_r->xv;
                  }
                  /* SAME BITREAD INTEGRALS RANGE AND CAST */
                  inline bool same_bitread_integrals_range_cast(const std::shared_ptr<ir_stat::ir_expr> &bitread_l, const std::shared_ptr<ir_stat::ir_expr> &bitread_r) {
                        return same_bitread_integrals_range(bitread_l, bitread_r) && types::is_same_implicit(bitread_l, bitread_r);
                  }

                  /* EXTRACT BITREAD BITS */
                  inline luramas_int extract_bitread_bits(const std::shared_ptr<ir_stat::ir_expr> &bitread) {
                        if (is_bitread(bitread) && !exprs::basic::is_integral(bitread->r, bitread->ev)) {
                              return 0u;
                        }
                        const auto min = bitread->r->extract_integral();
                        const auto max = bitread->ev->extract_integral();
                        return min > max ? 0u : (max - min) + 1u;
                  }
            } // namespace bitwise
      } // namespace values

      namespace extraction {

            inline std::function<void(std::shared_ptr<ir_stat::ir_expr> &, ir_stat::ir_expr::space &, boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &)> parent_volatiles = [](std::shared_ptr<ir_stat::ir_expr> &expr, ir_stat::ir_expr::space &result, boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &ignore) {
                  if (expr == nullptr || ignore.contains(expr)) {
                        return;
                  }
                  ignore.insert(expr);

                  if (expr->is_volatile()) {
                        result.emplace_back(expr);
                        return;
                  }

                  parent_volatiles(expr->l, result, ignore);
                  parent_volatiles(expr->r, result, ignore);

                  if (expr->ev) {
                        parent_volatiles(expr->ev, result, ignore);
                  }
                  if (expr->xv) {
                        parent_volatiles(expr->xv, result, ignore);
                  }
                  for (auto &m : expr->members) {
                        parent_volatiles(m, result, ignore);
                  }
                  for (auto &m : expr->captures) {
                        parent_volatiles(m, result, ignore);
                  }
                  if (expr->k != expr_kinds::page_function_call) {
                        for (auto &[i, v] : expr->tmembers) {
                              if (i) {
                                    parent_volatiles(i, result, ignore);
                              }
                              if (v) {
                                    parent_volatiles(v, result, ignore);
                              }
                        }
                  }
                  return;
            };
      } // namespace extraction

      namespace branch {

            /* (? ?? ?) */
            inline bool equality(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return expr && expr->l && expr->r && luramas::il::arch::data::is_kinds::equality(expr->b);
            }
            /* REG == REG */
            inline bool same_reg(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r) {
                  return l && r && l->is_register_reference() && r->is_reg(l->reg);
            }
            /* ? {and/or} ? */
            inline bool logical(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return expr && expr->e != expr_logical::nothing;
            }
            /* IS COMPARE? */
            inline bool is_compare(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return expr && expr->k == expr_kinds::condition;
            }
            /* IS EQUALITY BUT COMPARE? */
            inline bool is_equality_compare(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return is_compare(expr) && equality(expr);
            }
            /* TERNARY SINGLE CMP? */
            inline bool is_ternary_singlecmp(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return values::is_ternary(expr) && !expr->r;
            }
            /* SAME CONDITION OPERANDS? (Does compare exact match but if there logically can be the same) */
            inline bool same_logical_operands(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r) {
                  if (!values::is_condition(l) || !values::is_condition(r) || !l->l || !l->r || !r->l || !r->r) {
                        return false;
                  }
                  return *l->l == *r->l && *l->r == *r->r;
            }
      } // namespace branch

      namespace mutate {

            /* FLIP EXPR UNARY */
            inline void flip_unary(std::shared_ptr<ir_stat::ir_expr> &expr) {
                  switch (expr->u) {
                        case il::arch::data::bin_kinds::not_: {
                              expr->u = il::arch::data::bin_kinds::nothing;
                              break;
                        }
                        case il::arch::data::bin_kinds::nothing: {
                              expr->u = il::arch::data::bin_kinds::not_;
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  return;
            }

            /* FLIP EXPR CMP */
            template <bool deep = false>
            inline void flip_cmp(std::shared_ptr<ir_stat::ir_expr> &expr) {

                  if constexpr (deep) {

                        std::deque<std::shared_ptr<ir_stat::ir_expr>> exprs = {expr};
                        while (!exprs.empty()) {
                              auto current = exprs.front();
                              exprs.pop_front();

                              current->b = il::arch::data::bin_kindflip(current->b);
                              if (current->b == il::arch::data::bin_kinds::nothing) {
                                    flip_unary(current);
                              }
                              if (current->is_k<expr_kinds::ternary>() && current->e != expr_logical::nothing) {
                                    if (current->l) {
                                          exprs.emplace_back(current->l);
                                    }
                                    if (current->r) {
                                          exprs.emplace_back(current->r);
                                    }
                              }
                        }
                  } else {
                        expr->b = il::arch::data::bin_kindflip(expr->b);
                        if (expr->b == il::arch::data::bin_kinds::nothing) {
                              flip_unary(expr);
                        }
                  }
                  return;
            }

            /* EXTRACT CMP EXPR FROM STAT */
            inline std::shared_ptr<ir_stat::ir_expr> cmp_extract(const std::shared_ptr<ir_stat> &stat, const bool flip = false /* FLIP CMP? */) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_cond(stat->l, stat->b, stat->r);
                  if (flip) {
                        flip_cmp(result);
                  }
                  return result;
            }

            /* EXTRACT CMP EXPR FROM EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> cmp_extract(const std::shared_ptr<ir_stat::ir_expr> &expr, const bool flip = false /* FLIP CMP? */) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_cond(expr->l, expr->b, expr->r);
                  if (flip) {
                        flip_cmp(result);
                  }
                  return result;
            }

            /* COPY STAT OPERATION TO NEW EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> copy_operation(const std::shared_ptr<ir_stat> &stat, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  if (stat == nullptr || (!stat->is_k<keywords::condition>() && !stat->is_k<keywords::condition_goto>()) || stat->b == il::arch::data::bin_kinds::nothing) {
                        return expr;
                  }
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_cond(expr, stat->b);
                  return result;
            }

            /* MIMIC EITHER ET OR NT FROM EXPR COND (TO UNARY) */
            inline std::shared_ptr<ir_stat::ir_expr> mimic_compare(const std::shared_ptr<ir_stat::ir_expr> &expr_cond, std::shared_ptr<ir_stat::ir_expr> &expr) {
                  if (!tools::exprs::branch::is_compare(expr_cond)) {
                        return expr;
                  }
                  switch (expr_cond->b) {
                        case il::arch::data::bin_kinds::et_: {
                              expr->u = il::arch::data::bin_kinds::nothing;
                              break;
                        }
                        case il::arch::data::bin_kinds::nt_: {
                              expr->u = il::arch::data::bin_kinds::not_;
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  return expr;
            }
      } // namespace mutate

      namespace generate {

            /* GENERATE LOGICAL EXPR */
            template <expr_logical e>
            std::shared_ptr<ir_stat::ir_expr> logical(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r, const bool flip = false) {
                  LURAMAS_ASSERT((l == nullptr || r == nullptr), "Expected non nullptr");
                  std::shared_ptr<ir_stat::ir_expr> result = nullptr;
                  if (flip) {
                        switch (e) {
                              case expr_logical::or_: {
                                    result = logical<expr_logical::and_>(l, r);
                                    break;
                              }
                              case expr_logical::and_: {
                                    result = logical<expr_logical::or_>(l, r);
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  } else {
                        result = std::make_shared<ir_stat::ir_expr>();
                        result->emit_logical<e>(l, r);
                  }
                  return result;
            }

            /* GENERATE TERNARY EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> ternary(const std::shared_ptr<ir_stat::ir_expr> &cond_l, const std::shared_ptr<ir_stat::ir_expr> &cond_r, luramas::il::arch::data::bin_kinds b, const std::shared_ptr<ir_stat::ir_expr> &then_v, const std::shared_ptr<ir_stat::ir_expr> &else_v) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_ternary(cond_l, cond_r, b, then_v, else_v);
                  return result;
            }

            /* GENERATE TERNARY WITH CONDITION EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> ternary(const std::shared_ptr<ir_stat::ir_expr> &cond, const std::shared_ptr<ir_stat::ir_expr> &then_v, const std::shared_ptr<ir_stat::ir_expr> &else_v) {
                  LURAMAS_ASSERT((cond == nullptr || then_v == nullptr || else_v == nullptr), "Expected non nullptr");
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_ternary(cond, then_v, else_v);
                  return result;
            }

            /* GENERATE INTEGRAL EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> integral(const luramas_int &i) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_int(i);
                  return result;
            }

            /* GENERATE NONE OBJECT EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> none_object() {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_none();
                  return result;
            }

            /* GENERATE BOOLEAN EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> boolean(const bool b) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_boolean(b);
                  return result;
            }

            /* GENERATE STRING EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> string(const std::string &str) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_str(str);
                  return result;
            }

            /* GENERATE PACKED EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> packed(const std::shared_ptr<ir_stat::ir_expr> &expr, const luramas_address n) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_unpack(expr, n);
                  return result;
            }

            /* GENERATE COND EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> cond(const std::shared_ptr<ir_stat::ir_expr> &l, const luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing, const std::shared_ptr<ir_stat::ir_expr> &r = nullptr) {
                  LURAMAS_ASSERT((l == nullptr || (il::arch::data::is_kinds::equality(b) && r == nullptr)), "Expected non nullptr");
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_cond(l, b, r);
                  return result;
            }

            /* GENERATE BITREAD EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> bitread(const std::shared_ptr<ir_stat::ir_expr> &value, const std::shared_ptr<ir_stat::ir_expr> &min, const std::shared_ptr<ir_stat::ir_expr> &max, const std::shared_ptr<luramas::ir::types::object::type> &non_native) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_bitread(value, min, max, non_native);
                  return result;
            }

            /* GENERATE BITWRITE EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> bitwrite(const std::shared_ptr<ir_stat::ir_expr> &value, const std::shared_ptr<ir_stat::ir_expr> &lvalue, const std::shared_ptr<ir_stat::ir_expr> &min, const std::shared_ptr<ir_stat::ir_expr> &max, const std::shared_ptr<luramas::ir::types::object::type> &non_native) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_bitwrite(value, lvalue, min, max, non_native);
                  return result;
            }

            /* GENERATE MEMREAD EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> memoryread(const std::shared_ptr<ir_stat::ir_expr> &target, const luramas_bitwidth set_bits, const std::shared_ptr<ir_stat::ir_expr> &offset = nullptr) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_memoryread(target, set_bits, offset);
                  return result;
            }

            /* GENERATE CAST EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> cast(const std::shared_ptr<luramas::ir::types::object::type> &object, const std::shared_ptr<ir_stat::ir_expr> &v) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_cast(object, v);
                  return result;
            }

            /* GENERATE REGISTER EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> reg(const luramas_register reg) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_reg(reg);
                  return result;
            }

            /* GENERATE ARG REGISTER EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> reg_arg(const luramas_register reg) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_reg_arg(reg);
                  return result;
            }

            /* GENERATE REGISTER EXPR WITH ANNOTATION */
            inline std::shared_ptr<ir_stat::ir_expr> reg(const luramas_register reg, const std::string &annotation) {
                  auto result = generate::reg(reg);
                  result->emit_register_annotation(annotation);
                  return result;
            }

            /* GENERATE ARG REGISTER EXPR WITH ANNOTATION */
            inline std::shared_ptr<ir_stat::ir_expr> reg_arg(const luramas_register reg, const std::string &annotation) {
                  auto result = generate::reg_arg(reg);
                  result->emit_register_annotation(annotation);
                  return result;
            }

            /* GENERATE TABLE EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> table() {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_table();
                  return result;
            }

            /* GENERATE STACK EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> stack(const std::intptr_t id = 0u) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_stack(id);
                  return result;
            }

            /* GENERATE CONTROLLER EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> controller() {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_controller();
                  return result;
            }

            /* GENERATE TABLE INDEX */
            inline std::shared_ptr<ir_stat::ir_expr> table_index(const std::shared_ptr<ir_stat::ir_expr> &tab, const std::shared_ptr<ir_stat::ir_expr> &idx) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_idx(tab, idx);
                  return result;
            }

            /* GENERATE UNARY */
            inline std::shared_ptr<ir_stat::ir_expr> unary(const std::shared_ptr<ir_stat::ir_expr> &l, const luramas::il::arch::data::bin_kinds u) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_unary(l, u);
                  return result;
            }

            /* GENERATE ARITH */
            inline std::shared_ptr<ir_stat::ir_expr> arith(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r, luramas::il::arch::data::bin_kinds b) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_arith(l, r, b);
                  return result;
            }

            /* GENERATE VARIADIC EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> variadic() {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_variadic();
                  return result;
            }

            /* GENERATE SELF EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> self(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_self(l, r);
                  return result;
            }

            /* GENERATE UPVALUE EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> upval(const luramas_register r, const luramas_vregister vreg) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_upvalue(r, vreg);
                  return result;
            }

            /* GENERATE GLOBAL EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> global(const std::string &g) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_global(g);
                  return result;
            }

            /* GENERATE WILD CARD EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> wild_card(const std::string &g) {
                  auto result = global(g);
                  result->flags.fglobal_wild = true;
                  return result;
            }

            /* GENERATE CLOSURE EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> closure(const ir_stat::space &space) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_closure(space);
                  return result;
            }

            /* GENERATE NOTHING EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> nothing() {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_nothing();
                  return result;
            }

            /* GENERATE BASIC OBJECT EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> basic_object(const luramas_bitwidth bits, const bool unsign, const std::uint8_t precision) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_object(luramas::ir::types::generate::basic(bits, unsign, precision));
                  return result;
            }

            /* GENERATE BASIC TYPE */
            inline std::shared_ptr<luramas::ir::types::object::type> non_native(const luramas_bitwidth bits, const bool unsign, const std::uint8_t precision) {
                  return luramas::ir::types::generate::basic(bits, unsign, precision);
            }

            /* GENERATE CAST */
            inline std::shared_ptr<ir_stat::ir_expr> cast(const std::shared_ptr<ir_stat::ir_expr> &v, const std::shared_ptr<luramas::ir::types::object::type> &obj) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_cast(obj, v);
                  return result;
            }

            /* GENERATE CAST */
            inline std::shared_ptr<ir_stat::ir_expr> cast(const std::shared_ptr<ir_stat::ir_expr> &v, const luramas_bitwidth bits, const bool unsign, const std::uint8_t precision) {
                  return cast(v, non_native(bits, unsign, precision));
            }

            /* GENERATE CAST */
            inline std::shared_ptr<ir_stat::ir_expr> cast(const std::shared_ptr<ir_stat::ir_expr> &v, const luramas::types::underlying_type &t) {
                  return cast(v, luramas::ir::types::generate::basic(t));
            }

            /* GENERATE FLAG EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> flag(const std::shared_ptr<ir_stat::ir_expr> &id) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_flag(id);
                  return result;
            }

            /* GENERATE PAGE FUNCTION CALL EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> page_function_call(const std::shared_ptr<ir_stat::ir_expr> &id, const std::shared_ptr<ir_stat::ir_expr> &insertion_where, const std::shared_ptr<ir_stat::ir_expr> &value) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  result->emit_page_function_call(id, insertion_where, value);
                  return result;
            }

            /* GENERATE PAGE FUNCTION CALL EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> page_function_call(const std::shared_ptr<ir_stat::ir_expr> &id, const std::shared_ptr<ir_stat::ir_expr> &insertion_where, const std::shared_ptr<ir_stat::ir_expr> &value, const ir_stat::ir_expr::space &args) {
                  auto result = page_function_call(id, insertion_where, value);
                  result->members = args;
                  return result;
            }

            /* GENERATE CALL EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> call(const std::shared_ptr<ir_stat::ir_expr> &func, const ir_stat::ir_expr::space &args, const luramas_flag fsafe = false) {
                  auto result = std::make_shared<ir_stat::ir_expr>();
                  for (const auto &a : args) {
                        result->emit_arg(a);
                  }
                  result->emit_call(func);
                  result->flags.fsafe = fsafe;
                  return result;
            }

            /* GENERATE VFCALL EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> virtualfunction_call(const std::shared_ptr<ir_stat::ir_expr> &func, const ir_stat::ir_expr::space &args, const luramas_int &id, const luramas_flag fsafe = false) {
                  auto result = call(func, args, fsafe);
                  result->flags.fvirtualized = true;
                  result->n = id;
                  return result;
            }

            /* GENERATE VFCALL EXPR */
            inline std::shared_ptr<ir_stat::ir_expr> virtualfunction_call(const std::shared_ptr<ir_stat::ir_expr> &func, const ir_stat::ir_expr::space &args, const luramas::types::underlying_type &t, const luramas_int &id, const luramas_flag fsafe = false) {
                  auto result = virtualfunction_call(func, args, id, fsafe);
                  result->non_native = luramas::ir::types::generate::basic(t);
                  return result;
            }

            /* Generate with binkind */
            inline std::shared_ptr<ir_stat::ir_expr> bin_kind(const std::shared_ptr<ir_stat::ir_expr> &l, const il::arch::data::bin_kinds b, const std::shared_ptr<ir_stat::ir_expr> &r = nullptr) {

                  if (il::arch::data::is_kinds::arith(b)) {
                        return arith(l, r, b);
                  }
                  if (il::arch::data::is_kinds::condition(b)) {
                        return cond(l, b, r);
                  }
                  if (il::arch::data::is_kinds::unary(b)) {
                        return unary(l, b);
                  }
                  return nullptr;
            }
      } // namespace generate

      namespace common {

            /* () ? : EXPR  */
            inline bool ternary_else_contains(const std::shared_ptr<ir_stat::ir_expr> &ternary, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return values::is_ternary(ternary) && ternary->xv->contains(expr);
            }
            /* () EXPR : ?  */
            inline bool ternary_then_contains(const std::shared_ptr<ir_stat::ir_expr> &ternary, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return values::is_ternary(ternary) && ternary->ev->contains(expr);
            }
            /* COMPARE CONTAINS EXPR? */
            inline bool compare_contains(const std::shared_ptr<ir_stat::ir_expr> &compare, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return branch::is_compare(compare) && expr && ((compare->l && compare->l->contains(expr)) || (compare->r && compare->r->contains(expr)));
            }
            /* TERNARY COMPARE CONTAINS VOLATILES? */
            inline bool ternary_compare_volatile(const std::shared_ptr<ir_stat::ir_expr> &ternary) {
                  return values::is_ternary(ternary) && ((ternary->l && ternary->l->contains_volatile()) || (ternary->r && ternary->r->contains_volatile()));
            }
            /* TERNARY THEN AND ELSE CONDITIONS ARE THE SAME? */
            inline bool ternary_same_then_else(const std::shared_ptr<ir_stat::ir_expr> &ternary, const bool safe = false) {
                  return values::is_ternary(ternary) && ternary->ev->compare(ternary->xv, safe);
            }
            /* CAN BE NAN? */
            inline bool arith_possible_nan(const std::shared_ptr<ir_stat::ir_expr> &arith) {
                  return values::is_arith(arith) && (arith->b == il::arch::data::bin_kinds::div_ || arith->b == il::arch::data::bin_kinds::idiv_) && arith->r->is_integral(0);
            }
      } // namespace common

      namespace extractions {

            /* Append all register references to vector from expr */
            inline void register_references(const ir_stat::ir_expr::space &exprs, luramas_registers &buffer) {
                  for (const auto &e : exprs) {
                        if (e->is_register_reference()) {
                              buffer.emplace_back(e->reg);
                        }
                  }
                  return;
            }

            /* Extract all register references in expr */
            inline luramas_registers register_references(const ir_stat::ir_expr::space &exprs) {
                  luramas_registers result;
                  register_references(exprs, result);
                  return result;
            }

      } // namespace extractions

      namespace evaluate {

            /* UNSIGNED DOMINANCE? */
            inline bool unsigned_dominance(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r) {
                  return l && r && (l->flags.funsigned || r->flags.funsigned);
            }

            /* GET DOMINANT ARITHMETIC BITS */
            inline std::intptr_t arithmetic_bits(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r, bool &unsign) {
                  if (l && r) {
                        unsign = unsigned_dominance(l, r);
                  }
                  if (!values::is_cast(l) || !values::is_cast(r) || !l->non_native || !r->non_native || !l->non_native->basic() || !r->non_native->basic()) {
                        return pm.env_flags.options.odefault_bits;
                  }
                  return std::max(l->non_native->under.bits(), r->non_native->under.bits());
            }

            /* GET BITS FROM ARITHMETIC STATEMENT */
            inline std::intptr_t arithmetic_bits(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &arith, bool &unsign) {
                  if (arith) {
                        unsign = arith->flags.funsigned;
                  }
                  if (!values::is_arith(arith)) {
                        return pm.env_flags.options.odefault_bits;
                  }
                  return (!arith->n) ? arithmetic_bits(pm, arith->l, arith->r, unsign) : pm.env_flags.options.odefault_bits;
            }

            inline LURAMAS_IR_EVAL_KINDS is_implicit(const std::shared_ptr<ir_stat::ir_expr> &expr, const bool primitive_object = false) {
                  if (!expr || !expr->is_primitive()) {
                        return LURAMAS_IR_EVAL_KINDS::nothing;
                  }
                  if (!primitive_object) {
                        if (expr->is_integral()) {
                              return expr->extract_integral() ? LURAMAS_IR_EVAL_KINDS::true_ : LURAMAS_IR_EVAL_KINDS::false_;
                        }
                  }
                  return tools::exprs::values::is_none_obj(expr) || tools::exprs::values::is_boolean(expr, false) ? LURAMAS_IR_EVAL_KINDS::false_ : LURAMAS_IR_EVAL_KINDS::true_;
            }

            inline std::optional<luramas_int> bitread_size(const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  if (!values::is_bitread(expr) || !expr->r || !expr->ev || !expr->r->is_integral() || !expr->ev->is_integral()) {
                        return std::nullopt;
                  }
                  const auto min = expr->r->extract_integral();
                  const auto max = expr->ev->extract_integral();
                  return min > max ? 0u : (max - min) + 1u;
            }
      } // namespace evaluate

      template <typename t>
      inline constexpr bool is(const std::shared_ptr<ir_stat::ir_expr> &expr, const t &d) {

            if (expr == nullptr) {
                  return false;
            }
            if constexpr (std::is_same_v<t, bool>) {
                  return expr->is_tk<tkind::boolean>() && expr->bv == d;
            } else if constexpr (std::is_integral_v<t>) {
                  return expr->is_tk<tkind::lura_int>() && expr->n == luramas_int(d);
            } else if constexpr (std::is_same_v<t, std::string>) {
                  return expr->is_tk<tkind::string>() && expr->v == d;
            }
            return false;
      }

      /* EXPR HAS REG */
      inline bool reg_ref(const std::shared_ptr<ir_stat::ir_expr> &expr, const luramas_register reg) {
            return expr && expr->contains(reg);
      }

} // namespace luramas::ir::tools::exprs