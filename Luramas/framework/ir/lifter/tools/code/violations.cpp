#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::violations {

      block_violation_results block_violates(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end, const block_violates_flags &flags) {

            block_violation_results result;
            if (flags.fbackwards ? start < end : start > end) {
                  result.make_exception<block_violation_exceptions::invalid>(start);
                  return result;
            }

            std::optional<boost::unordered_flat_map<luramas_id, std::pair<bool, bool>>> paging;
            if (flags.finclude_pages || (pm.env_flags.fpromote_safety && pm.env_data.fseperated_pages)) {
                  paging.emplace();
            }

            auto o = start;
            bool hit = false;
            auto end_cond_stack = 0, until_cond_stack = 0;
            for (; o < end; flags.fbackwards ? --o : ++o) {

                  const auto &d = pm[o];
                  if (flags.close_on && !end_cond_stack && !until_cond_stack && flags.close_on->compare(d, false, true)) {
                        hit = true;
                        break;
                  }
                  const auto s = stat::branch::condition_stack(d);
                  if (stat::branch::is_else_conditional(d) && !end_cond_stack) {
                        result.make_exception<block_violation_exceptions::invalid_else_conditional>(o);
                        return result;
                  }
                  if (paging) {
                        if (stat::is_page_function_start(d)) {
                              auto &[s, e] = (*paging)[d->r->extract_integral_base()];
                              if (s) {
                                    result.make_exception<block_violation_exceptions::invalid_page_start>(o);
                                    return result;
                              }
                              s = true;
                        }
                        if (stat::is_page_function_end(d)) {
                              auto &[s, e] = (*paging)[d->r->extract_integral_base()];
                              if (e) {
                                    result.make_exception<block_violation_exceptions::invalid_page_start>(o);
                                    return result;
                              }
                              e = true;
                        }
                  }
                  if (s > 0) {
                        if (stat::branch::expects_until(d)) {
                              if (!flags.fbackwards) {
                                    ++until_cond_stack;
                              } else if (until_cond_stack) {
                                    --until_cond_stack;
                              } else {
                                    result.make_exception<block_violation_exceptions::invalid_scope_start>(o);
                                    return result;
                              }
                        } else if (!flags.fbackwards) {
                              ++end_cond_stack;
                        } else if (end_cond_stack) {
                              --end_cond_stack;
                        } else {
                              result.make_exception<block_violation_exceptions::invalid_scope_start>(o);
                              return result;
                        }
                  } else if (s < 0) {
                        if (d->is_k<keywords::end>()) {
                              if (flags.fbackwards) {
                                    ++end_cond_stack;
                              } else if (end_cond_stack) {
                                    --end_cond_stack;
                              } else {
                                    result.make_exception<block_violation_exceptions::invalid_end>(o);
                                    return result;
                              }
                        } else if (flags.fbackwards) {
                              ++until_cond_stack;
                        } else if (until_cond_stack) {
                              --until_cond_stack;
                        } else {
                              result.make_exception<block_violation_exceptions::invalid_until>(o);
                              return result;
                        }
                  }
                  if (!end_cond_stack && !until_cond_stack) {
                        if (flags.finclude_gotos && tools::stat::branch::is_goto(d)) {
                              result.make_exception<block_violation_exceptions::invalid_goto>(o);
                              return result;
                        }
                        if (flags.finclude_implicit && d->is_implicit_flow_interrupt()) {
                              result.make_exception<block_violation_exceptions::invalid_implicit>(o);
                              return result;
                        }
                        if ((flags.finclude_terminals && d->is_terminal()) || (flags.ovalid_cb && (*flags.ovalid_cb)(d))) {
                              result.ending_loc = o;
                              return result;
                        }
                        if (flags.valid_extract) {
                              flags.valid_extract->emplace_back(o);
                        }
                  }
            }
            if (!flags.fbackwards) {
                  result.ending_loc = o - (o == pm.amount());
            }
            if (paging) {
                  for (const auto &[id, p] : (*paging)) {
                        if (!p.second || !p.first) {
                              result.make_exception<block_violation_exceptions::invalid_unfinished_page>(o);
                              break;
                        }
                  }
            }
            if (hit) {
                  result.make_exception<block_violation_exceptions::hit_closing_on>(o);
            } else if (end_cond_stack || until_cond_stack) {
                  result.make_exception<block_violation_exceptions::invalid_unfinished_conditions>(o);
            }
            return result;
      }

      namespace accumulate {

            std::vector<block_violation_results> violations(luramas::ir::passes::pass_manager &pm, luramas_address start, const luramas_address end, const block_violates_flags &flags) {

                  std::vector<block_violation_results> result;
                  while (start != end) {

                        const auto violation = block_violates(pm, start, end, flags);
                        result.emplace_back(violation);
                        if (violation.valid) {
                              break;
                        }
                        start = violation.ending_loc;
                  }
                  return result;
            }

            std::vector<block_violation_results> violations_safe(luramas::ir::passes::pass_manager &pm, luramas_address start, const luramas_address end) {

                  std::vector<block_violation_results> result;
                  while (start < end) {

                        const auto violation = block_violates(pm, start, end);
                        result.emplace_back(violation);
                        if (violation.valid) {
                              break;
                        }
                        const auto jmp = common::safe_take_jump(pm, violation.ending_loc);
                        if (start = jmp ? jmp : violation.ending_loc; start > end) {
                              result.emplace_back(block_violation_results());
                        }
                  }
                  return result;
            }

      } // namespace accumulate

} // namespace luramas::ir::tools::violations