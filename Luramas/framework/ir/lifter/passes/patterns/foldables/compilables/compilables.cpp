#include "compilables.hpp"
#include "../../private.hpp"

std::shared_ptr<ir_stat::ir_expr> luramas::ir::passes::patterns::constant_folding::compilables::if_condition::pattern_1(pass_manager &pm, shared &s, const luramas_address start, const luramas_address end) {

      std::shared_ptr<ir_stat::ir_expr> current_cmp = nullptr;
      std::shared_ptr<ir_stat::ir_expr> compiled_cmp = nullptr;
      for (auto e = start; e < end; ++e) {
            const auto &p = pm[e];
            if (tools::stat::branch::is_if_cond(p)) {
                  current_cmp = tools::exprs::mutate::cmp_extract(p);
            } else if (tools::stat::is_assignment(p)) {
                  current_cmp = tools::exprs::generate::logical<expr_logical::and_>(current_cmp, p->r);
            } else if (tools::stat::branch::is_cond_goto(p)) {
                  tools::stat::mutate::mimic_compare(p, current_cmp);
                  compiled_cmp = (!compiled_cmp) ? current_cmp : tools::exprs::generate::logical<expr_logical::or_>(compiled_cmp, current_cmp);
            }
      }
      return compiled_cmp;
}

std::shared_ptr<ir_stat::ir_expr> luramas::ir::passes::patterns::constant_folding::compilables::assignments::pattern_1(pass_manager &pm, shared &s, const luramas_address start, const luramas_address end) {

      std::shared_ptr<ir_stat::ir_expr> current_cmp = nullptr;
      std::shared_ptr<ir_stat::ir_expr> compiled_cmp = nullptr;
      for (auto e = start; e < end; ++e) {
            const auto &p = pm[e];
            if (tools::stat::branch::is_if_cond(p)) {
                  current_cmp = tools::stat::mutate::mimic_compare(p, current_cmp);
                  compiled_cmp = (!compiled_cmp) ? current_cmp : tools::exprs::generate::logical<expr_logical::or_>(compiled_cmp, current_cmp);
            } else if (tools::stat::is_assignment(p)) {
                  current_cmp = p->r;
            }
      }
      return compiled_cmp;
}
