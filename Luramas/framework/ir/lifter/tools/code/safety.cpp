#include "../tools.hpp"

namespace luramas::ir::tools::safety {

      namespace arith {

            bool is_safe(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &expr) {

                  if (!exprs::values::is_arith(expr)) {
                        return false;
                  }

                  if (pm.env_flags.fhas_nan && tools::exprs::common::arith_possible_nan(expr)) {
                        return false;
                  }
                  if (expr->l && expr->l->is_integral()) {

                        const auto n = expr->l->extract_integral();
                        if (pm.env_flags.safety.sarith_lvalue_neg.contains(expr->b) && n.negative()) {
                              return false;
                        }
                        if (pm.env_flags.safety.sarith_lvalue_zero.contains(expr->b) && !n) {
                              return false;
                        }
                  }
                  if (expr->r && expr->r->is_integral()) {

                        const auto n = expr->r->extract_integral();
                        if (pm.env_flags.safety.sarith_rvalue_neg.contains(expr->b) && n.negative()) {
                              return false;
                        }
                        if (pm.env_flags.safety.sarith_rvalue_zero.contains(expr->b) && !n) {
                              return false;
                        }
                  }
                  return true;
            }
      } // namespace arith

      bool combine_integrals(const std::shared_ptr<ir_stat::ir_expr> &a, const std::shared_ptr<ir_stat::ir_expr> &b, luramas_int &buffer, const il::arch::data::bin_kinds arith_k, const bool allow_overflow) {

            if (!a || !b || !a->is_integral() || !b->is_integral()) {
                  return false;
            }

            const auto av = a->extract_integral();
            const auto bv = b->extract_integral();

            switch (arith_k) {
                  case il::arch::data::bin_kinds::add_: {
                        buffer = av + bv;
                        break;
                  }
                  case il::arch::data::bin_kinds::sub_: {
                        buffer = av - bv;
                        break;
                  }
                  case il::arch::data::bin_kinds::mul_: {
                        if (!allow_overflow && (av != 0 && bv > av.max() / av)) {
                              return false;
                        }
                        buffer = av * bv;
                        break;
                  }
                  default: {
                        luramas::error::error("Can not combine with a non arith kind");
                  }
            }
            return buffer > av && buffer > bv;
      }

      bool page(passes::pass_manager &pm, const generation::ssa::ssa &ssa) {

            return false;
      }
} // namespace luramas::ir::tools::safety