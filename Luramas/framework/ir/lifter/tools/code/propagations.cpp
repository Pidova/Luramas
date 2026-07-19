#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::propagations {

      luramas_count constant_folds(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa, const luramas_xregister target_ssa) {

            luramas_count result = 0u;

            const auto linked = ssa::extract::linked(ssa, target_ssa);
            if (!linked) {
                  return result;
            }

            const auto defs = ssa.defs.find(target_ssa);
            if (defs == ssa.defs.end()) {
                  return result;
            }

            /* (?? ARITH INT)? */
            if (!exprs::values::is_arith(defs->second.first->r) || !exprs::values::is_integer(defs->second.first->r->r)) {
                  return result;
            }

            /* Count (SSA ARITH INT) */
            for (const auto &i : boost::unordered_flat_set<luramas_address>(defs->second.second.second.first.begin(), defs->second.second.second.first.end())) {

                  for (const auto &e : pm[i]->extract_ordered_deep_exprs()) {

                        result += (exprs::values::is_arith(e) && exprs::values::is_integer(e->r) && exprs::values::is_reg(e->l, *linked) && combine::can(e->b, defs->second.first->r->b));
                  }
            }
            return result;
      }
} // namespace luramas::ir::tools::propagations