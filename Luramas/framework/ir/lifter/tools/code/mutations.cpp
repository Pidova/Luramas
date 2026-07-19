#include "../../passes/process/process.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools {

      bool mutates(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &target, const luramas_address start, const luramas_address end) {

            luramas::ir::pass::process::values(pm);
            if (start >= end || target->is_primitive()) {
                  return false;
            }
            const auto exprs = target->extract_ordered_exprs();

            /* Stack */
            boost::unordered_flat_set<luramas_id> used_stack;
            for (const auto &i : exprs) {
                  if (tools::exprs::values::is_stack(i)) {
                        used_stack.insert(i->extract_integral_base());
                  }
            }

            /* Check if target is volatile */
            const auto marked_volatile = std::any_of(exprs.begin(), exprs.end(), [](const auto &curr_expr) { return curr_expr->is_unsafe(); });
            const auto marked_volatile_flag = std::any_of(exprs.begin(), exprs.end(), [](const auto &curr_expr) { return curr_expr->is_flag(); });

            boost::unordered_flat_set<luramas_register> upvalues;
            for (const auto &k : exprs) {
                  for (const auto &c : k->captures) {
                        if (c->is_register_reference()) {
                              upvalues.insert(c->reg);
                        }
                  }
            }

            /* Go through for mutations */
            for (auto i = start; i != end; ++i) {

                  const auto &p = pm[i];

                  if (p->flags.fdead_sideeffects) {
                        continue;
                  }
                  if ((marked_volatile && p->is_volatile()) || (marked_volatile_flag && p->is_flag_volatile()) || (!target->is_primitive() && p->is_paging_control_flow_transfer())) {
                        return true;
                  }
                  const auto &values = pm.processed.values[p];
                  for (const auto &expr : values.lvalues) {
                        for (const auto &curr_expr : exprs) {

                              /* 
                                    start = DATA
                                    ...
                                    DATA = ?
                              */
                              if ((tools::exprs::values::is_upvalue(curr_expr) && upvalues.contains(curr_expr->reg)) || *curr_expr == *expr || (values.edits_flag && curr_expr->is_flag(values.edited_flag))) {
                                    return true;
                              }
                        }
                  }
                  for (const auto &expr : values.rvalues) {
                        if ((marked_volatile && expr->is_volatile()) || (!target->is_primitive() && expr->is_paging())) {
                              return true;
                        }
                  }
                  for (const auto &id : used_stack) {
                        if (tools::stat::is_stack_push(p, id)) {
                              return true;
                        }
                        if (tools::stat::is_stack_pop(p, id)) {
                              return true;
                        }
                  }
            }
            return false;
      }

      bool mutates(luramas::ir::passes::pass_manager &pm, const luramas_register target, const luramas_address start, const luramas_address end) {

            return mutates(pm, exprs::generate::reg(target), start, end);
      }

      bool mutates(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &single_assignment_target, const luramas_address start, const luramas_address end) {

            if (!tools::stat::assignment::is_single_assignment(single_assignment_target) || single_assignment_target->r->is_primitive()) {
                  return false;
            }
            return mutates(pm, single_assignment_target->l, start, end);
      }

      namespace mutations {

            bool pop_cond(luramas::ir::passes::pass_manager &pm, const luramas_address cond, const bool truthy) {

                  if (!pm.contains(cond) || !tools::stat::branch::is_explicit_cond(pm[cond])) {
                        return false;
                  }

                  const auto truncated = tools::truncate::removable_cond(pm, cond);
                  if (truncated.valid) {
                        if (truthy) {
                              /* Remove IF, END */
                              pm.remove(pm[cond], pm[truncated.ending]);
                        } else {
                              /* Remove block */
                              pm.remove(tools::block::orphaned(pm, tools::transform::address_to_range(cond, truncated.ending)));
                        }
                        return true;
                  }
                  switch (truncated.exception_kind) {
                        case condition_kind::else_: {
                              if (truthy) {
                                    /* Remove condition and ELSE block */
                                    pm.remove(pm[cond]);
                                    pm.remove(tools::block::orphaned(pm, tools::transform::address_to_range(truncated.ending, truncated.took_jump)));
                              } else {
                                    /* Remove condition block */
                                    pm.remove(tools::block::orphaned(pm, tools::transform::address_to_range(cond, truncated.ending)));
                                    pm.remove(pm[truncated.took_jump]);
                              }
                              break;
                        }
                        case condition_kind::elseif_: {
                              // TODO ADD LOGIC
                              //if (truthy) {
                              //      pm.remove(truncated.ending, truncated.took_jump);
                              //} else {
                              //      tools::stat::mutate::if_stat_cleared(pm[truncated.ending]);
                              //      pm.remove(cond, truncated.ending);
                              //}
                              return false;
                              break;
                        }
                        default: {
                              return false;
                        }
                  }
                  return true;
            }

            std::shared_ptr<ir_stat> safe_if_dupe(passes::pass_manager &pm, const std::shared_ptr<ir_stat> &stat) {
                  if (!pm.is_safe(stat)) {
                        return stat->clone();
                  }
                  pm.set_safe(stat);
                  return stat;
            }

            bool modified_regs(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range, const boost::unordered_flat_set<luramas_register> &regs) {

                  for (const auto &i : luramas_iter(range)) {

                        if (const auto &p = pm[i]; p) {
                              for (const auto &r : p->extract_ordered_lvalues()) {
                                    if (r->is_register_reference() && regs.contains(r->reg)) {
                                          return true;
                                    }
                              }
                        }
                  }
                  return false;
            }
      } // namespace mutations
} // namespace luramas::ir::tools