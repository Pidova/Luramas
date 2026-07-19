#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::truncate {

      luramas_address block(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end, const bool encapsulate, const bool include_gotos, const bool include_terminals, const std::shared_ptr<ir_stat> &close_on) {

            const auto violation = violations::block_violates(pm, (encapsulate && tools::stat::branch::is_explicit_cond(pm[start])) ? start + 1u : start, end, violations::block_violates_flags({.finclude_gotos = include_gotos, .finclude_terminals = include_terminals, .close_on = close_on}));
            return violation.valid ? end : violation.reason == violations::block_violation_exceptions::hit_closing_on ? violation.ending_loc
                                       : violation.ending_loc                                                         ? violation.ending_loc - 1u
                                                                                                                      : 0u;
      }

      removable_cond_result removable_cond(luramas::ir::passes::pass_manager &pm, const luramas_address start) {

            removable_cond_result result;
            if (!pm.contains(start) || !tools::stat::branch::is_explicit_cond(pm[start])) {
                  return result;
            }

            const auto take_jump = tools::common::safe_take_jump(pm, start);
            const auto violation = violations::block_violates(pm, start + 1u, pm.amount());
            if (violation.ending_loc == take_jump) {
                  result.ending = take_jump;
                  return result;
            }
            result.valid = false;
            result.took_jump = take_jump;
            result.ending = violation.ending_loc;
            result.exception_kind = pm[violation.ending_loc]->c;
            return result;
      }

      luramas_address most_relative_valid_block(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_addresses &ends) {

            luramas_address result = 0u;
            for (const auto &i : ends) {
                  if (i > result && i > start && violations::block_violates(pm, start, i).valid) {
                        result = i;
                  }
            }
            return result;
      }
} // namespace luramas::ir::tools::truncate