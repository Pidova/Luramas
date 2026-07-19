#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::compute {

      namespace strings {

            bool flatten_concat(std::shared_ptr<ir_stat::ir_expr> &expr) {

                  if (!tools::exprs::values::is_concat(expr)) {
                        return false;
                  }

                  luramas_flag fmutated = false;
                  if (tools::count::is(expr->members, data::concatable) > 1u) {

                        /* Perform concatables */
                        luramas_flag flast_str_member = false;
                        ir_stat::ir_expr::space vect;
                        vect.reserve(expr->members.size());
                        for (const auto &i : expr->members) {

                              const auto can_concat = i->is_concatable_tk();
                              if (flast_str_member && can_concat) {
                                    vect.back() = vect.back()->clone();
                                    const auto str = luramas_str_concat_qouted(vect.back()->str(), i->str());
                                    vect.back()->clear();
                                    vect.back()->emit_str(str);
                              } else {
                                    vect.emplace_back(i);
                              }
                              flast_str_member = can_concat;
                        }

                        if (vect.size() != expr->members.size()) {
                              expr->members = std::move(vect);
                              fmutated = true;
                        }
                  }
                  if (expr->members.size() == 1u) {
                        expr = expr->members.front();
                        return true;
                  }
                  return fmutated;
            }
      } // namespace strings

      std::shared_ptr<ir_stat::ir_expr> compute(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r, expr_logical b, const bool primitive_object) {

            if (l == nullptr || r == nullptr) {
                  return nullptr;
            }

            /* Early short circuit with a boolean */
            if (tools::exprs::values::is_boolean(l, true) && b == expr_logical::or_) {
                  return l;
            }
            if (tools::exprs::values::is_boolean(l, false) && b == expr_logical::and_) {
                  return l;
            }
            if (!l->is_primitive()) {
                  return nullptr;
            }
            switch (b) {
                  case expr_logical::or_: {
                        return tools::exprs::evaluate::is_implicit(l, primitive_object) == LURAMAS_IR_EVAL_KINDS::true_ ? l : r;
                  }
                  case expr_logical::and_: {
                        return tools::exprs::evaluate::is_implicit(l, primitive_object) == LURAMAS_IR_EVAL_KINDS::true_ ? r : l;
                  }
                  default: {
                        break;
                  }
            }
            return nullptr;
      }

      luramas::ir::tools::compute::comparable compare(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r, luramas::il::arch::data::bin_kinds b, const bool primitive_object) {

            if (!l) {
                  return comparable::none_;
            }
            if (b == luramas::il::arch::data::bin_kinds::nothing) {
                  b = luramas::il::arch::data::bin_kinds::et_;
            }
            if (r) {

                  /* ~(x(NO VOLATILES) & 1) == n */
                  if (r->is_integral() && tools::exprs::values::is_unary<il::arch::data::bin_kinds::bitnot_>(l) &&
                      tools::exprs::values::is_arith<il::arch::data::bin_kinds::and_>(l->l) && l->l->r && l->l->r->extract_integral() == 1u &&
                      l->l->l && !l->l->l->contains_volatile()) {

                        /* EXPR & will either be 0 or 1 test it */
                        if (const auto r_int = r->extract_integral(); !compute<std::intptr_t, luramas_int, bool>(~1, r_int, b) && !compute<std::intptr_t, luramas_int, bool>(~0, r_int, b)) {
                              return comparable::false_;
                        }
                  }
            }
            if (l->is_primitive()) {
                  if (!r) {

                        if (l->is_tk<tkind::lura_int>()) {
                              return compute(l->n, b, primitive_object) ? comparable::true_ : comparable::false_;
                        }
                        if (l->is_tk<tkind::boolean>()) {
                              return compute(l->bv, b, primitive_object) ? comparable::true_ : comparable::false_;
                        }
                        if (l->is_tk<tkind::string>()) {
                              return comparable::true_;
                        }
                  } else if (r->is_primitive()) {

                        if (l->is_tk<tkind::lura_int>() || r->is_tk<tkind::lura_int>()) {
                              return compute<luramas_int, luramas_int, bool>(l->n, r->n, b) ? comparable::true_ : comparable::false_;
                        }
                        if (l->is_tk<tkind::boolean>() || r->is_tk<tkind::boolean>()) {
                              return compute<bool, bool, bool>(l->bv, r->bv, b) ? comparable::true_ : comparable::false_;
                        }
                        if (l->is_tk<tkind::none_obj>() && r->is_tk<tkind::none_obj>()) {
                              return b == luramas::il::arch::data::bin_kinds::eq_ ? comparable::true_ : comparable::false_;
                        }
                        if (l->is_tk<tkind::string>() && r->is_tk<tkind::string>()) {
                              return compare_eq<std::string, std::string>(l->v, r->v, b) ? comparable::true_ : comparable::false_;
                        }
                        if (l->is_tk<tkind::none_obj>() && !r->is_tk<tkind::none_obj>()) {
                              return b == luramas::il::arch::data::bin_kinds::eq_ ? comparable::false_ : comparable::true_;
                        }
                  }
            }
            return comparable::none_;
      }

      std::shared_ptr<ir_stat::ir_expr> constant_evaluation(passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &expr, const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &precomputed) {

            boost::unordered_flat_map<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat::ir_expr>> computed;

            const auto exprs = expr->extract_order_of_operation_exprs();
            computed.reserve(exprs.size());

            std::shared_ptr<ir_stat::ir_expr> last_expr = nullptr;
            for (const auto &i : exprs) {

                  if (i->is_register_reference()) {
                        if (auto it = precomputed.find(i->reg); it != precomputed.end()) {
                              last_expr = it->second;
                              if (!last_expr->is_primitive()) {
                                    return nullptr;
                              }
                              computed.try_emplace(i, last_expr);
                              continue;
                        }
                  }

                  last_expr = i->clone(false);
                  last_expr->shallow_replace(computed);

                  compute::exprs::simplify(pm, last_expr);

                  if (!last_expr->is_primitive()) {
                        return nullptr;
                  }
                  computed.try_emplace(i, last_expr);
            }
            return last_expr;
      }

} // namespace luramas::ir::tools::compute
