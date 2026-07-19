#pragma once
#include "../../../passes.hpp"
#include "../builder/exprs.hpp"
#include "exprs.hpp"

namespace luramas::ir::tools::stat {

      inline bool future(const luramas_address curr, const luramas_address target) {
            return target > curr;
      }
      inline bool past(const luramas_address curr, const luramas_address target) {
            return !future(curr, target);
      }

      /* end */
      inline bool is_end(const std::shared_ptr<ir_stat> &end_stat) {
            return end_stat && end_stat->is_k<keywords::end>();
      }
      /* until */
      inline bool is_until(const std::shared_ptr<ir_stat> &until_stat) {
            return until_stat && until_stat->is_k<keywords::until>();
      }
      /* repeat */
      inline bool is_repeat(const std::shared_ptr<ir_stat> &repeat_stat) {
            return repeat_stat && repeat_stat->is_k<keywords::repeat>();
      }
      /* while */
      inline bool is_while(const std::shared_ptr<ir_stat> &while_stat) {
            return while_stat && while_stat->is_k<keywords::while_>();
      }
      /* break */
      inline bool is_break(const std::shared_ptr<ir_stat> &break_stat) {
            return break_stat && break_stat->is_k<keywords::break_>();
      }
      /* label */
      inline bool is_label(const std::shared_ptr<ir_stat> &label_stat) {
            return label_stat && label_stat->is_k<keywords::label>();
      }
      /* continue */
      inline bool is_continue(const std::shared_ptr<ir_stat> &continue_stat) {
            return continue_stat && continue_stat->is_k<keywords::continue_>();
      }
      /* return */
      inline bool is_return(const std::shared_ptr<ir_stat> &return_stat) {
            return return_stat && return_stat->is_k<keywords::retn>();
      }
      /* return with count */
      inline bool is_return(const std::shared_ptr<ir_stat> &return_stat, const luramas_count n) {
            return is_return(return_stat) && return_stat->members.size() == n;
      }
      /* return goes to pages */
      inline bool is_page_return(const std::shared_ptr<ir_stat> &return_stat) {
            return is_return(return_stat) && !return_stat->smembers.empty();
      }
      /* return is empty */
      inline bool is_return_empty(const std::shared_ptr<ir_stat> &return_stat) {
            return is_return(return_stat, 0u) && return_stat->smembers.empty() && return_stat->args.empty();
      }
      /* assignment */
      inline bool is_assignment(const std::shared_ptr<ir_stat> &assign) {
            return assign && assign->is_k<keywords::assignment>();
      }
      /* call */
      inline bool is_call(const std::shared_ptr<ir_stat> &call) {
            return call && call->is_k<keywords::call>();
      }
      /* global preset */
      inline bool is_global_preset(const std::shared_ptr<ir_stat> &global_preset) {
            return global_preset && global_preset->is_k<keywords::globals_preset>();
      }
      /* definition */
      inline bool is_definition(const std::shared_ptr<ir_stat> &definition) {
            return definition && definition->is_k<keywords::definition>();
      }
      /* switch */
      inline bool is_switch(const std::shared_ptr<ir_stat> &switch_stat) {
            return switch_stat && switch_stat->is_k<keywords::switch_>();
      }
      /* switch case */
      inline bool is_switch_case(const std::shared_ptr<ir_stat> &switch_case_stat) {
            return switch_case_stat && switch_case_stat->is_k<keywords::switch_case>();
      }
      /* switch default case */
      inline bool is_switch_default(const std::shared_ptr<ir_stat> &switch_default_stat) {
            return switch_default_stat && switch_default_stat->is_k<keywords::switch_default>();
      }
      /* virtual function call */
      inline bool is_virtual_function_call(const std::shared_ptr<ir_stat> &vfcall) {
            return vfcall && vfcall->is_k<keywords::call>() && vfcall->flags.fsynthetic && vfcall->l && vfcall->l->is_integral();
      }
      /* stack pop */
      inline bool is_stack_pop(const std::shared_ptr<ir_stat> &pop_stat) {
            return pop_stat && pop_stat->is_k<keywords::stack_pop>();
      }
      /* stack pop */
      inline bool is_stack_pop(const std::shared_ptr<ir_stat> &pop_stat, const luramas_int &id) {
            return is_stack_pop(pop_stat) && pop_stat->v && pop_stat->v->is_integral(id);
      }
      /* stack pop */
      inline bool is_stack_push(const std::shared_ptr<ir_stat> &push_stat) {
            return push_stat && push_stat->is_k<keywords::stack_push>();
      }
      /* stack pop */
      inline bool is_stack_push(const std::shared_ptr<ir_stat> &push_stat, const luramas_int &id) {
            return is_stack_push(push_stat) && push_stat->v && push_stat->v->is_integral(id);
      }
      /* stack read */
      inline bool is_stack_read(const std::shared_ptr<ir_stat> &stack_read_stat, const luramas_int &stack_id = LURAMAS_IR_DEFAULT_STACK_ID) {
            return stack_read_stat && stack_read_stat->is_k<keywords::stack_read>() && stack_read_stat->v && stack_read_stat->v->is_integral(stack_id);
      }
      /* isolate */
      inline bool is_isolate(const std::shared_ptr<ir_stat> &isolate_stat) {
            return isolate_stat && isolate_stat->is_k<keywords::isolate>();
      }
      /* set flag */
      inline bool is_set_flag(const std::shared_ptr<ir_stat> &set_flag_stat) {
            return set_flag_stat && set_flag_stat->is_k<keywords::set_flag>();
      }
      /* page function start */
      inline bool is_page_function_start(const std::shared_ptr<ir_stat> &page_function_start_stat) {
            return page_function_start_stat && page_function_start_stat->is_k<keywords::page_function_start>();
      }
      /* page function start */
      inline bool is_page_function_start(const std::shared_ptr<ir_stat> &page_function_start_stat, const luramas_id id) {
            return is_page_function_start(page_function_start_stat) && page_function_start_stat->r && page_function_start_stat->r->is_integral(id);
      }
      /* page function closure */
      inline bool is_page_function_closure(const std::shared_ptr<ir_stat> &page_function_closure_stat) {
            return page_function_closure_stat && page_function_closure_stat->is_k<keywords::page_function_closure>();
      }
      /* page function end */
      inline bool is_page_function_end(const std::shared_ptr<ir_stat> &page_function_end_stat) {
            return page_function_end_stat && page_function_end_stat->is_k<keywords::page_function_end>();
      }
      /* page function end */
      inline bool is_page_function_end(const std::shared_ptr<ir_stat> &page_function_end_stat, const luramas_id id) {
            return is_page_function_end(page_function_end_stat) && page_function_end_stat->r && page_function_end_stat->r->is_integral(id);
      }
      /* page function pass */
      inline bool is_page_function_pass(const std::shared_ptr<ir_stat> &page_function_pass_stat) {
            return page_function_pass_stat && page_function_pass_stat->is_k<keywords::page_function_pass>();
      }
      /* page function goto */
      inline bool is_page_function_goto(const std::shared_ptr<ir_stat> &page_function_goto_stat) {
            return page_function_goto_stat && page_function_goto_stat->is_k<keywords::page_function_goto>();
      }
      /* page function call */
      inline bool is_page_function_call(const std::shared_ptr<ir_stat> &page_function_call_stat) {
            return is_page_function_goto(page_function_call_stat) && page_function_call_stat->pfk == page_function_goto_kind::call;
      }
      /* page function call */
      inline bool is_page_function_call(const std::shared_ptr<ir_stat> &page_function_call_stat, const luramas_id page_id) {
            return is_page_function_call(page_function_call_stat) && page_function_call_stat->r && page_function_call_stat->r->is_integral(page_id);
      }
      /* page function jump */
      inline bool is_page_function_jump(const std::shared_ptr<ir_stat> &page_function_jump_stat) {
            return is_page_function_goto(page_function_jump_stat) && page_function_jump_stat->pfk == page_function_goto_kind::jump;
      }
      /* page function jump */
      inline bool is_page_function_jump(const std::shared_ptr<ir_stat> &page_function_jump_stat, const luramas_id page_id) {
            return is_page_function_jump(page_function_jump_stat) && page_function_jump_stat->r && page_function_jump_stat->r->is_integral(page_id);
      }
      /* maybe stack */
      inline bool is_create_stack(const std::shared_ptr<ir_stat> &create_stack) {
            return create_stack && create_stack->is_k<keywords::create_stack>();
      }
      /* BASIC CONDITION (NOT LOGICAL)? */
      inline bool is_anonfunction_call(const std::shared_ptr<ir_stat> &call) {
            return is_call(call) && exprs::values::is_closure(call->l);
      }
      /* ASSIGNMENT */
      inline bool is_assignment(const std::shared_ptr<ir_stat> &assign, const std::shared_ptr<ir_stat::ir_expr> &lvalue) {
            return is_assignment(assign) && assign->l && *assign->l == *lvalue;
      }
      /* ASSIGNMENT */
      inline bool is_assignment(const std::shared_ptr<ir_stat> &assign, const std::shared_ptr<ir_stat::ir_expr> &lvalue, const std::shared_ptr<ir_stat::ir_expr> &rvalue) {
            return is_assignment(assign, lvalue) && assign->r && rvalue && *assign->r == *rvalue;
      }
      /* ASSIGNMENT */
      inline bool is_assignment(const std::shared_ptr<ir_stat> &assign, const luramas_register r) {
            return is_assignment(assign) && exprs::values::is_reg(assign->l, r);
      }
      /* ASSIGNMENT */
      inline bool is_assignment(const std::shared_ptr<ir_stat> &assign, const luramas_register r, const luramas_flag fcontains) {
            if (!is_assignment(assign)) {
                  return false;
            }
            if (exprs::values::is_reg(assign->l, r)) {
                  return true;
            }
            for (const auto &i : assign->members) {
                  if (exprs::values::is_reg(i, r)) {
                        return true;
                  }
            }
            return false;
      }
      /* ASSIGNMENT */
      inline bool is_assignment(const std::shared_ptr<ir_stat> &assign, const luramas_register r, const std::shared_ptr<ir_stat::ir_expr> &rvalue) {
            return is_assignment(assign, r) && assign->r && rvalue && *assign->r == *rvalue;
      }
      /* METADATA */
      inline bool is_metadata(const std::shared_ptr<ir_stat> &metadata_stat) {
            return metadata_stat && metadata_stat->is_k<keywords::metadata>();
      }
      /* TAG */
      inline bool is_tag_start(const std::shared_ptr<ir_stat> &tag_stat) {
            return tag_stat && tag_stat->is_k<keywords::tag_start>();
      }
      /* TAG END */
      inline bool is_tag_end(const std::shared_ptr<ir_stat> &tag_end_stat) {
            return tag_end_stat && tag_end_stat->is_k<keywords::tag_end>();
      }
      /* ENTRY POINT */
      inline bool is_entry_point(const std::shared_ptr<ir_stat> &entry_point_stat) {
            return entry_point_stat && entry_point_stat->is_k<keywords::entry_point>();
      }
      /* COMMAND */
      inline bool is_command(const std::shared_ptr<ir_stat> &command_stat) {
            return command_stat && command_stat->is_k<keywords::command>();
      }
      /* BITWRITE */
      inline bool is_bitwrite(const std::shared_ptr<ir_stat> &bitwrite_stat) {
            return bitwrite_stat && bitwrite_stat->is_k<keywords::bitwrite>();
      }
      /* BITWRITE */
      inline bool is_bitwrite(const std::shared_ptr<ir_stat> &bitwrite_stat, const std::shared_ptr<ir_stat::ir_expr> &dest) {
            return is_bitwrite(bitwrite_stat) && bitwrite_stat->l && dest && (*bitwrite_stat->l == *dest);
      }
      /* BITWRITE */
      inline bool is_bitwrite(const std::shared_ptr<ir_stat> &bitwrite_stat, const std::shared_ptr<ir_stat::ir_expr> &dest, const std::shared_ptr<ir_stat::ir_expr> &src) {
            return is_bitwrite(bitwrite_stat, dest) && bitwrite_stat->r && src && (*bitwrite_stat->r == *src);
      }
      /* MEMSET */
      inline bool is_memoryset(const std::shared_ptr<ir_stat> &memset_stat) {
            return memset_stat && memset_stat->is_k<keywords::memoryset>();
      }
      /* MEMSET */
      inline bool is_memoryset(const std::shared_ptr<ir_stat> &memset_stat, const std::shared_ptr<ir_stat::ir_expr> &l) {
            return is_memoryset(memset_stat) && l && memset_stat->l && *l == *memset_stat->l;
      }
      /* MEMSET */
      inline bool is_memoryset(const std::shared_ptr<ir_stat> &memset_stat, const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r) {
            return is_memoryset(memset_stat, l) && ((r && memset_stat->r && *r == *memset_stat->r) || (!r && !memset_stat->r));
      }
      /* MEMSET */
      inline bool is_memoryset(const std::shared_ptr<ir_stat> &memset_stat, const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r, const std::shared_ptr<ir_stat::ir_expr> &v) {
            return is_memoryset(memset_stat, l, r) && v && memset_stat->v && *v == *memset_stat->v;
      }
      /* MEMSET */
      inline bool is_memoryset(const std::shared_ptr<ir_stat> &memset_stat, const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r, const std::shared_ptr<ir_stat::ir_expr> &v, const luramas_address extra_bits) {
            return is_memoryset(memset_stat, l, r, v) && memset_stat->extra_bits == extra_bits;
      }
      /* MEMSET */
      inline bool is_memoryset(const std::shared_ptr<ir_stat> &memset_stat, const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r, const luramas_address extra_bits) {
            return is_memoryset(memset_stat, l, r) && memset_stat->extra_bits == extra_bits;
      }

      namespace flags {

            /* IS SYNTHETIC? */
            inline bool is_synthetic(const std::shared_ptr<ir_stat> &stat) {
                  return stat && stat->flags.fsynthetic;
            }
            /* IS FLAGABLE? */
            inline bool is_flagable(const std::shared_ptr<ir_stat> &stat) {
                  return stat && stat->flags.fflagable;
            }
            /* IS IMMUTABLE? */
            inline bool is_immutable(const std::shared_ptr<ir_stat> &stat) {
                  return stat && stat->flags.fimmutable;
            }
            /* IS SYNTHETIC FLAGABLE? */
            inline bool is_synthetic_flagable(const std::shared_ptr<ir_stat> &stat) {
                  return is_synthetic(stat) && is_flagable(stat);
            }
      } // namespace flags

      namespace branch {

            /* PAIRED ENDINGS? */
            inline bool is_ending_paired(const std::shared_ptr<ir_stat> &condition, const std::shared_ptr<ir_stat> &ending) {
                  if (!condition || !ending) {
                        return false;
                  }
                  switch (condition->k) {
                        case keywords::condition:
                        case keywords::forloop_generic:
                        case keywords::forloop_numeric:
                        case keywords::while_: {
                              return ending->is_k<keywords::end>();
                        }
                        case keywords::repeat: {
                              return ending->is_k<keywords::until>();
                        }
                        default: {
                              break;
                        }
                  }
                  return false;
            }

            /* LABEL HAS 1 REF */
            inline bool is_single_label_ref(passes::pass_manager &pm, const std::shared_ptr<ir_stat> &label) {
                  return label && label->label && pm.processed.jlabels_refs[label->label].size() == 1u;
            }
            /* LABEL HAS 1 REF */
            inline bool is_single_label_ref(passes::pass_manager &pm, const luramas_address label) {
                  if (!label) {
                        return false;
                  }
                  const auto it = pm.processed.jlabels_refs.find(label);
                  return it != pm.processed.jlabels_refs.end() && it->second.size() == 1u;
            }
            /* COND GOTO */
            inline bool is_cond_goto(const std::shared_ptr<ir_stat> &cond_goto) {
                  return cond_goto && cond_goto->is_k<keywords::condition_goto>();
            }
            /* IF */
            inline bool is_if_cond(const std::shared_ptr<ir_stat> &if_stat) {
                  return if_stat && if_stat->is_k<keywords::condition>() && (if_stat->c == condition_kind::if_ || if_stat->c == condition_kind::nothing);
            }
            /* IF (? ?? ?) */
            template <il::arch::data::bin_kinds b>
            inline bool is_if_cond(const std::shared_ptr<ir_stat> &if_stat) {
                  return is_if_cond(if_stat) && if_stat->b == b;
            }
            /* IF (? ?? ?) */
            template <il::arch::data::bin_kinds b = il::arch::data::bin_kinds::et_>
            inline bool is_if_cond(const std::shared_ptr<ir_stat> &if_stat, const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r) {
                  return is_if_cond<b>(if_stat) && if_stat->l == l && if_stat->r == r;
            }
            /* ELSEIF*/
            inline bool is_elseif_cond(const std::shared_ptr<ir_stat> &elseif_stat) {
                  return elseif_stat && elseif_stat->is_k<keywords::condition>() && elseif_stat->c == condition_kind::elseif_;
            }
            /* ELSE */
            inline bool is_else_cond(const std::shared_ptr<ir_stat> &else_stat) {
                  return else_stat && else_stat->is_k<keywords::condition>() && else_stat->c == condition_kind::else_;
            }
            /* ELSE OR ELSEIF */
            inline bool is_else_conditional(const std::shared_ptr<ir_stat> &stat) {
                  return is_else_cond(stat) || is_elseif_cond(stat);
            }

            /* COND GOTO, IF, ELSEIF */
            inline bool is_comparable(const std::shared_ptr<ir_stat> &stat) {
                  if (!stat) {
                        return false;
                  }
                  switch (stat->k) {
                        case keywords::condition: {
                              return is_if_cond(stat) || is_elseif_cond(stat);
                        }
                        case keywords::while_:
                        case keywords::until:
                        case keywords::condition_goto: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }
            /* ANY COMPARABLE STAT? */
            inline bool is_any_comparable(const std::shared_ptr<ir_stat> &stat) {
                  if (!stat) {
                        return false;
                  }
                  switch (stat->k) {
                        case keywords::condition: {
                              return is_if_cond(stat) || is_elseif_cond(stat);
                        }
                        case keywords::while_:
                        case keywords::condition_goto: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }
            /* (? ?? ?) */
            inline bool equality(const std::shared_ptr<ir_stat> &stat) {
                  return is_comparable(stat) && stat->l && stat->r && luramas::il::arch::data::is_kinds::equality(stat->b);
            }
            /* CMP ? */
            inline bool is_single_compare(const std::shared_ptr<ir_stat> &stat) {
                  return is_comparable(stat) && stat->l && !stat->r && !luramas::il::arch::data::is_kinds::equality(stat->b);
            }
            /* CMP ? == cmp */
            inline bool is_single_compare(const std::shared_ptr<ir_stat> &stat, const std::shared_ptr<ir_stat::ir_expr> &lcmp) {
                  return is_single_compare(stat) && lcmp && *stat->l == *lcmp;
            }
            /* CMP ? == cmp (MULTI) */
            template <typename... exprs>
            inline bool is_single_compare(const std::shared_ptr<ir_stat> &stat, const std::shared_ptr<ir_stat::ir_expr> &first, const exprs &...va) {
                  return is_single_compare(stat, first) || is_single_compare(stat, va...);
            }
            /* CMP == CMP */
            inline bool is_compare(const std::shared_ptr<ir_stat> &stat, const std::shared_ptr<ir_stat::ir_expr> &lcmp, const std::shared_ptr<ir_stat::ir_expr> &rcmp) {
                  return equality(stat) && lcmp && rcmp && *stat->l == *lcmp && *stat->r == *rcmp;
            }
            /* IF (CMP == EXPR) */
            inline bool is_if_cond(const std::shared_ptr<ir_stat> &if_stat, const std::shared_ptr<ir_stat::ir_expr> &lcmp) {
                  return is_if_cond(if_stat) && is_single_compare(if_stat, lcmp);
            }
            /* COMPARE CONTAINS REGISTER? */
            inline bool is_contains_compare_reg(const std::shared_ptr<ir_stat> &stat, const luramas_register reg) {
                  return is_comparable(stat) && ((stat->l && stat->l->contains(reg)) || (stat->r && stat->r->contains(reg)));
            }
            /* COMPARE CONTAINS EXPR? */
            inline bool is_contains_compare(const std::shared_ptr<ir_stat> &stat, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return is_comparable(stat) && expr && ((stat->l && stat->l->contains(expr)) || (stat->r && stat->r->contains(expr)));
            }
            /* COMPARE CONTAINS VOLATILE? */
            inline bool is_contains_compare_volatile(const std::shared_ptr<ir_stat> &stat) {
                  return is_comparable(stat) && ((stat->l && stat->l->contains_volatile()) || (stat->r && stat->r->contains_volatile()));
            }
            /* IS GOTO */
            inline bool is_goto(const std::shared_ptr<ir_stat> &goto_stat) {
                  return goto_stat && goto_stat->is_k<keywords::goto_label>();
            }
            /* IS GOTO LABEL? */
            inline bool is_goto(const std::shared_ptr<ir_stat> &goto_stat, const luramas_address jlabel) {
                  return is_goto(goto_stat) && goto_stat->jlabel == jlabel;
            }
            /* LABEL LOC == CURR JLABEL */
            inline bool is_jlabel_target(const std::shared_ptr<ir_stat> &label_stat, const std::shared_ptr<ir_stat> &curr) {
                  return label_stat && curr && label_stat->is_k<keywords::label>() && label_stat->label == curr->jlabel;
            }
            /* LABEL == LABEL */
            inline bool same_labels(const std::shared_ptr<ir_stat> &label_l, const std::shared_ptr<ir_stat> &label_r) {
                  return is_label(label_l) && is_label(label_r) && label_l->label == label_r->label;
            }
            /* GOTO, COND GOTO */
            inline bool is_jump(const std::shared_ptr<ir_stat> &curr) {
                  return curr && (curr->is_k<keywords::goto_label>() || is_cond_goto(curr));
            }
            /* CONDITION STAT ?? */
            inline bool is_cond(const std::shared_ptr<ir_stat> &curr) {
                  return is_if_cond(curr) || is_elseif_cond(curr) || is_cond_goto(curr);
            }
            /* CONDITION STAT ?? */
            inline bool is_cond(const std::shared_ptr<ir_stat> &curr, const luramas::il::arch::data::bin_kinds &b) {
                  return is_cond(curr) && curr->b == b;
            }
            /* IF/ELSE IF/ELSE? */
            inline bool is_explicit_cond(const std::shared_ptr<ir_stat> &curr) {
                  return is_if_cond(curr) || is_elseif_cond(curr) || is_else_cond(curr);
            }
            /* IS ELSE/ELSEIF STAT??? */
            inline bool is_else_stat(const std::shared_ptr<ir_stat> &curr) {
                  return is_else_cond(curr) || is_elseif_cond(curr);
            }
            /* IF(? == INPUT REG [?? ?])*/
            inline bool is_if_lvalue(const std::shared_ptr<ir_stat> &if_stat, const luramas_register reg) {
                  return is_if_cond(if_stat) && if_stat->l && if_stat->l->is_reg(reg);
            }
            /* IF(? == INPUT [?? ?])*/
            inline bool is_if_lvalue(const std::shared_ptr<ir_stat> &if_stat, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return is_if_cond(if_stat) && if_stat->l && *if_stat->l == *expr;
            }
            /* COND GOTO(? == INPUT REG [?? ?])*/
            inline bool is_if_cond_lvalue(const std::shared_ptr<ir_stat> &cond_goto, const luramas_register reg) {
                  return is_cond_goto(cond_goto) && cond_goto->l && cond_goto->l->is_reg(reg);
            }
            /* COND GOTO(? == EXPR)*/
            inline bool is_if_cond_lvalue(const std::shared_ptr<ir_stat> &cond_goto, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return is_cond_goto(cond_goto) && expr && cond_goto->l && *cond_goto->l == *expr;
            }
            /* IF (? == REG) */
            inline bool is_if_reg(const std::shared_ptr<ir_stat> &if_stat, const luramas_register reg) {
                  return is_if_lvalue(if_stat, reg) && is_single_compare(if_stat);
            }
            /* COND IF (? == REG) */
            inline bool is_cond_goto(const std::shared_ptr<ir_stat> &cond_goto, const luramas_register reg) {
                  return is_if_cond_lvalue(cond_goto, reg) && is_single_compare(cond_goto);
            }
            /* COND IF (? == EXPR) */
            inline bool is_cond_goto(const std::shared_ptr<ir_stat> &cond_goto, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return is_if_cond_lvalue(cond_goto, expr) && is_single_compare(cond_goto);
            }
            /* COND GOTO IF (? == REG) */
            inline bool is_cond_goto(const std::shared_ptr<ir_stat> &cond_goto, const luramas::il::arch::data::bin_kinds b) {
                  return is_cond_goto(cond_goto) && cond_goto->b == b;
            }
            /* COND GOTO IF (? == REG) */
            inline bool is_cond_goto(const std::shared_ptr<ir_stat> &cond_goto, const std::shared_ptr<ir_stat::ir_expr> &l, const luramas::il::arch::data::bin_kinds b) {
                  return is_cond_goto(cond_goto, b) && cond_goto->l;
            }
            /* NOT CMP */
            inline bool is_not_compare(const std::shared_ptr<ir_stat> &stat) {
                  return is_single_compare(stat) && (il::arch::data::is_kinds::not_k(stat->b) || il::arch::data::is_kinds::not_k(stat->l->u));
            }
            /* (??) */
            inline bool is_cond_true(const std::shared_ptr<ir_stat> &stat) {
                  return is_cond(stat) && stat->b == il::arch::data::bin_kinds::et_;
            }
            /* (EXPR) */
            inline bool is_single_cond_true(const std::shared_ptr<ir_stat> &stat, const std::shared_ptr<ir_stat::ir_expr> &lvalue) {
                  return is_single_compare(stat) && is_cond_true(stat) && *stat->l == *lvalue;
            }
            /* GOING TO A LABEL (goto/cond goto)? */
            inline bool is_goto_basic(const std::shared_ptr<ir_stat> &goto_stat) {
                  return is_goto(goto_stat) || is_cond_goto(goto_stat);
            }

            /* STAT GOTO END == END */
            inline bool same_ending(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &end) {
                  return l && end && end->is_k<keywords::end>() && l->end_label == end->end_label;
            }
            /* CONDITION GOTO LABEL == CONDITION GOTO LABEL  */
            inline bool same_cond_goto_labels(const std::shared_ptr<ir_stat> &lcond_goto, const std::shared_ptr<ir_stat> &rcond_goto) {
                  return is_cond_goto(lcond_goto) && is_cond_goto(rcond_goto) && lcond_goto->jlabel == rcond_goto->jlabel;
            }
            /* CONDITION GOTO == CONDITION GOTO LEFT RIGHT VALUES  */
            inline bool same_cond_goto_lr(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r) {
                  return same_cond_goto_labels(l, r) && ((l->l && r->l && *l->l == *r->l) && ((l->r && r->r && *l->r == *r->r) || (!l->r && !r->r && l->r == r->r)));
            }
            /* CONDITION GOTO == CONDITION GOTO  */
            inline bool same_cond_goto(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r) {
                  return same_cond_goto_lr(l, r) && l->b == r->b;
            }
            /* CONDITION GOTO == GOTO LABELS */
            inline bool same_cond_goto_goto_labels(const std::shared_ptr<ir_stat> &cond_goto, const std::shared_ptr<ir_stat> &goto_stat) {
                  return goto_stat && is_cond_goto(cond_goto) && goto_stat->is_k<keywords::goto_label>() && cond_goto->jlabel == goto_stat->jlabel;
            }
            /* GOTO == GOTO  */
            inline bool same_goto(const std::shared_ptr<ir_stat> &goto_l, const std::shared_ptr<ir_stat> &goto_r) {
                  return is_goto(goto_l) && is_goto(goto_r) && goto_l->jlabel == goto_r->jlabel;
            }
            /* IF == IF */
            inline bool same_if(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r) {
                  return is_if_cond(l) && is_if_cond(r) && ((l->l && r->l && *l->l == *r->l) || (l->r && r->r && *l->r == *r->r));
            }
            /* ELSEIF == ELSEIF */
            inline bool same_elseif(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r) {
                  return is_elseif_cond(l) && is_elseif_cond(r) && ((l->l && r->l && *l->l == *r->l) || (l->r && r->r && *l->r == *r->r));
            }
            /* CONTINUE == CONTINUE  */
            inline bool same_continue(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r) {
                  return l && r && is_continue(l) && is_continue(r) && l->underlying_jump == r->underlying_jump;
            }

            /* GOTO LABEL == LABEL */
            inline bool is_goto_label(const std::shared_ptr<ir_stat> &goto_stat, const std::shared_ptr<ir_stat> &label) {
                  return goto_stat && label && goto_stat->is_k<keywords::goto_label>() && label->is_k<keywords::label>() && goto_stat->jlabel == label->label;
            }
            /* CONDITION GOTO LABEL == LABEL  */
            inline bool is_cond_goto_label(const std::shared_ptr<ir_stat> &cond_goto, const std::shared_ptr<ir_stat> &label) {
                  return label && is_cond_goto(cond_goto) && label->is_k<keywords::label>() && cond_goto->jlabel == label->label;
            }
            /* CONDITION GOTO LABEL == LABEL  */
            inline bool is_cond_goto_label(const std::shared_ptr<ir_stat> &cond_goto, const luramas_address jlabel) {
                  return is_cond_goto(cond_goto) && cond_goto->jlabel == jlabel;
            }
            /* CONDITION GOTO LABEL == LABEL, SINGLE COMPARE == EXPR  */
            inline bool is_cond_goto_label(const std::shared_ptr<ir_stat> &cond_goto, const std::shared_ptr<ir_stat> &label, const std::shared_ptr<ir_stat::ir_expr> &lcmp) {
                  return is_cond_goto_label(cond_goto, label) && is_single_compare(cond_goto, lcmp);
            }
            /* CONDITION GOTO LABEL == LABEL, SINGLE COMPARE == EXPR  */
            inline bool is_cond_goto_label(const std::shared_ptr<ir_stat> &cond_goto, const luramas_address jlabel, const std::shared_ptr<ir_stat::ir_expr> &lcmp) {
                  return is_cond_goto_label(cond_goto, jlabel) && is_single_compare(cond_goto, lcmp);
            }
            /* CONDITION GOTO LABEL == LABEL, COMPARE == COMPARE  */
            inline bool is_cond_goto_label(const std::shared_ptr<ir_stat> &cond_goto, const std::shared_ptr<ir_stat> &label, const std::shared_ptr<ir_stat::ir_expr> &lcmp, const std::shared_ptr<ir_stat::ir_expr> &rcmp) {
                  return is_cond_goto_label(cond_goto, label) && is_compare(cond_goto, lcmp, rcmp);
            }
            /* CONDITION GOTO LABEL == LABEL, SINGLE COMPARE == EXPR, CMP == TRUE  */
            inline bool is_cond_goto_label_true(const std::shared_ptr<ir_stat> &cond_goto, const std::shared_ptr<ir_stat> &label, const std::shared_ptr<ir_stat::ir_expr> &lcmp) {
                  return is_cond_goto_label(cond_goto, label, lcmp) && cond_goto->b == il::arch::data::bin_kinds::et_;
            }
            /* CONDITION GOTO LABEL == LABEL, SINGLE REF LABEL  */
            inline bool is_cond_goto_label_single_ref(const std::shared_ptr<ir_stat> &cond_goto, const std::shared_ptr<ir_stat> &label, passes::pass_manager &pm) {
                  return is_cond_goto_label(cond_goto, label) && is_single_label_ref(pm, label);
            }

            /* CONDITION GOTO LABEL > i  */
            inline bool is_cond_goto_future(passes::pass_manager &pm, const std::shared_ptr<ir_stat> &cond_goto, const luramas_address i) {
                  return is_cond_goto(cond_goto) && future(i, pm.processed.labels[cond_goto->jlabel]);
            }
            /* CONDITION GOTO LABEL < i  */
            inline bool is_cond_goto_past(passes::pass_manager &pm, const std::shared_ptr<ir_stat> &cond_goto, const luramas_address i) {
                  return is_cond_goto(cond_goto) && past(i, pm.processed.labels[cond_goto->jlabel]);
            }

            /* GOTO LABEL > i  */
            inline bool is_goto_future(passes::pass_manager &pm, const std::shared_ptr<ir_stat> &goto_stat, const luramas_address i) {
                  return is_goto(goto_stat) && future(i, pm.processed.labels[goto_stat->jlabel]);
            }
            /* GOTO LABEL < i  */
            inline bool is_goto_past(passes::pass_manager &pm, const std::shared_ptr<ir_stat> &goto_stat, const luramas_address i) {
                  return is_goto(goto_stat) && past(i, pm.processed.labels[goto_stat->jlabel]);
            }

            /* IF END == END */
            inline bool is_if_end(const std::shared_ptr<ir_stat> &if_stat, const std::shared_ptr<ir_stat> &end) {
                  return is_if_cond(if_stat) && same_ending(if_stat, end);
            }
            /* IF END == END, CMP == EXPR */
            inline bool is_if_end(const std::shared_ptr<ir_stat> &if_stat, const std::shared_ptr<ir_stat> &end, const std::shared_ptr<ir_stat::ir_expr> &lcmp) {
                  return is_if_end(if_stat, end) && is_single_compare(if_stat, lcmp);
            }
            /* ELSEIF END == END */
            inline bool is_elseif_end(const std::shared_ptr<ir_stat> &elseif_stat, const std::shared_ptr<ir_stat> &end) {
                  return is_elseif_cond(elseif_stat) && same_ending(elseif_stat, end);
            }
            /* IF STAT && END */
            inline bool is_stat_if_end(const std::shared_ptr<ir_stat> &if_stat, const std::shared_ptr<ir_stat> &end) {
                  return is_if_cond(if_stat) && end->is_k<keywords::end>();
            }
            /* ELSEIF STAT && END */
            inline bool is_stat_elseif_end(const std::shared_ptr<ir_stat> &elseif_stat, const std::shared_ptr<ir_stat> &end) {
                  return is_elseif_cond(elseif_stat) && end->is_k<keywords::end>();
            }
            /* ELSE STAT && END */
            inline bool is_stat_else_end(const std::shared_ptr<ir_stat> &else_stat, const std::shared_ptr<ir_stat> &end) {
                  return is_else_cond(else_stat) && end->is_k<keywords::end>();
            }
            /* ELSE END == END */
            inline bool is_else_end(const std::shared_ptr<ir_stat> &else_stat, const std::shared_ptr<ir_stat> &end) {
                  return is_else_cond(else_stat) && same_ending(else_stat, end);
            }
            /* IF(? ?? ?) END == END */
            inline bool is_if_equality_end(const std::shared_ptr<ir_stat> &if_stat, const std::shared_ptr<ir_stat> &end) {
                  return is_if_end(if_stat, end) && equality(if_stat);
            }
            /* ELSEIF(? ?? ?) END == END */
            inline bool is_elseif_equality_end(const std::shared_ptr<ir_stat> &elseif_stat, const std::shared_ptr<ir_stat> &end) {
                  return is_elseif_end(elseif_stat, end) && equality(elseif_stat);
            }
            /* IF(?) END == END */
            inline bool is_if_end_singlecmp(const std::shared_ptr<ir_stat> &if_stat, const std::shared_ptr<ir_stat> &end) {
                  return is_if_cond(if_stat) && same_ending(if_stat, end) && !equality(if_stat);
            }
            /* ELSEIF(?) END == END */
            inline bool is_elseif_end_singlecmp(const std::shared_ptr<ir_stat> &elseif_stat, const std::shared_ptr<ir_stat> &end) {
                  return is_elseif_cond(elseif_stat) && same_ending(elseif_stat, end) && is_single_compare(elseif_stat);
            }
            /* IF, SINGLE CMP */
            inline bool is_if_singlecmp(const std::shared_ptr<ir_stat> &if_stat) {
                  return is_if_cond(if_stat) && is_single_compare(if_stat);
            }
            /* IF(CMP == ?) END == END */
            inline bool is_if_end_singlecmp(const std::shared_ptr<ir_stat> &if_stat, const std::shared_ptr<ir_stat> &end, const std::shared_ptr<ir_stat::ir_expr> &cmp) {
                  return is_if_singlecmp(if_stat) && same_ending(if_stat, end) && *if_stat->l == *cmp;
            }
            /* ELSEIF(CMP == ?) END == END */
            inline bool is_elseif_end_singlecmp(const std::shared_ptr<ir_stat> &elseif_stat, const std::shared_ptr<ir_stat> &end, const std::shared_ptr<ir_stat::ir_expr> &cmp) {
                  return is_elseif_cond(elseif_stat) && same_ending(elseif_stat, end) && is_single_compare(elseif_stat) && *elseif_stat->l == *cmp;
            }
            /* while(true) */
            inline bool is_while_true(const std::shared_ptr<ir_stat> &while_stat) {
                  return is_while(while_stat) && while_stat->l && while_stat->l->is_tk<tkind::boolean>() && while_stat->l->bv;
            }
            /* until(true) */
            inline bool is_until_true(const std::shared_ptr<ir_stat> &until_stat) {
                  return until_stat && until_stat->is_k<keywords::until>() && until_stat->l && until_stat->l->is_tk<tkind::boolean>() && until_stat->l->bv;
            }
            /* COMPARE CONTAINS? */
            inline bool compare_contains(const std::shared_ptr<ir_stat> &stat, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return is_cond(stat) && expr && ((stat->l && stat->l->contains(expr)) || (stat->r && stat->r->contains(expr)));
            }
            /* IF END == END, COMPARE DOESNT CONTAIN EXPR? */
            inline bool is_if_end_not_contains(const std::shared_ptr<ir_stat> &if_stat, const std::shared_ptr<ir_stat> &end, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return is_if_end(if_stat, end) && !compare_contains(if_stat, expr);
            }
            /* IF END == END, COMPARE CONTAINS EXPR? */
            inline bool is_if_end_contains(const std::shared_ptr<ir_stat> &if_stat, const std::shared_ptr<ir_stat> &end, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return is_if_end(if_stat, end) && compare_contains(if_stat, expr);
            }
            /* LOOP END == ENDING */
            inline bool is_loop_end(const std::shared_ptr<ir_stat> &loop_stat, const std::shared_ptr<ir_stat> &end) {
                  return loop_stat && end && loop_stat->is_loop() && is_ending_paired(loop_stat, end) && loop_stat->end_label == end->end_label;
            }
            /* ENDING IS LOOP ENDING? */
            inline bool is_loop_end(passes::pass_manager &pm, const std::shared_ptr<ir_stat> &end, const luramas_flag fonly_end = false) {
                  return end && (is_end(end) || (fonly_end && is_until(end))) && pm[pm.processed.end_labels[end->end_label].first]->is_loop();
            }
            /* REPEAT UNTIL? */
            inline bool is_repeat_until(const std::shared_ptr<ir_stat> &repeat_stat, const std::shared_ptr<ir_stat> &until_stat) {
                  return is_repeat(repeat_stat) && is_until(until_stat) && repeat_stat->end_label == until_stat->end_label;
            }
            /* WHILE END? */
            inline bool is_while_end(const std::shared_ptr<ir_stat> &while_stat, const std::shared_ptr<ir_stat> &end_stat) {
                  return is_while(while_stat) && is_end(end_stat) && while_stat->end_label == end_stat->end_label;
            }
            /* UNCONDITIONAL? */
            inline bool is_unconditional(const std::shared_ptr<ir_stat> &unconditional_stat) {
                  return is_else_cond(unconditional_stat) || is_switch_default(unconditional_stat);
            }

            /*
                if(SYNTHETIC FLAGABLE) then
                    /KEYYWORD/
                /end/        
            */
            template <keywords k>
            inline bool is_flagable_synthetic_keyword(passes::pass_manager &pm, const luramas_address start) {
                  const auto &if_stat = pm[start];
                  return pm.valid_next<2u>(start) && is_if_end_singlecmp(if_stat, pm[start + 2u]) && flags::is_synthetic_flagable(if_stat) && pm[start + 1u]->is_k<k>();
            }

            /*  
                [ENDLABEL]
               [ENDLABEL]
            */
            inline bool contiguous_ends(passes::pass_manager &pm, const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r) {
                  return l && r && l->end_label && r->end_label && pm.processed.end_labels[l->end_label].second + 1u == pm.processed.end_labels[r->end_label].second;
            }

            inline bool is_condition_stack_scope(const std::shared_ptr<ir_stat> &stat) {
                  switch (stat->k) {
                        case keywords::condition: {
                              return is_if_cond(stat);
                        }
                        case keywords::forloop_generic:
                        case keywords::forloop_numeric:
                        case keywords::repeat:
                        case keywords::while_: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }
            inline bool expects_until(const std::shared_ptr<ir_stat> &stat) {
                  switch (stat->k) {
                        case keywords::repeat: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }
            inline bool is_condition_stack(const std::shared_ptr<ir_stat> &stat) {
                  switch (stat->k) {
                        case keywords::condition: {
                              return is_if_cond(stat);
                        }
                        case keywords::forloop_generic:
                        case keywords::forloop_numeric:
                        case keywords::repeat:
                        case keywords::while_:
                        case keywords::end:
                        case keywords::until: {
                              return true;
                        }
                        default: {
                              return false;
                        }
                  }
            }
            inline std::int8_t condition_stack(const std::shared_ptr<ir_stat> &stat) {
                  switch (stat->k) {
                        case keywords::condition: {
                              return is_if_cond(stat);
                        }
                        case keywords::forloop_generic:
                        case keywords::forloop_numeric:
                        case keywords::repeat:
                        case keywords::while_: {
                              return 1;
                        }
                        case keywords::end:
                        case keywords::until: {
                              return -1;
                        }
                        default: {
                              return 0;
                        }
                  }
            }
            inline bool valid_condition(const std::shared_ptr<ir_stat> &top, const std::shared_ptr<ir_stat> &stat) {
                  if (!stat->is_scope_end()) {
                        return true;
                  }
                  switch (top->k) {
                        case keywords::condition:
                        case keywords::forloop_generic:
                        case keywords::forloop_numeric:
                        case keywords::while_: {
                              return stat->is_k<keywords::end>();
                        }
                        case keywords::repeat: {
                              return stat->is_k<keywords::until>();
                        }
                        default: {
                              return false;
                        }
                  }
            }
            /* if (CONTROLLER == ??) then goto ??; */
            inline bool is_controller_if_cond_goto(const std::shared_ptr<ir_stat> &if_stat) {
                  return is_cond_goto(if_stat) && exprs::values::is_controller(if_stat->l) && exprs::basic::is_integral(if_stat->r);
            }
            /* if (CONTROLLER == ??) then */
            inline bool is_controller_if_cond(const std::shared_ptr<ir_stat> &if_stat) {
                  return is_cond(if_stat) && exprs::values::is_controller(if_stat->l) && exprs::basic::is_integral(if_stat->r);
            }
            /* if (CONTROLLER == ??) then */
            inline bool is_controller_if_cond(const std::shared_ptr<ir_stat> &if_stat, const luramas_id &id) {
                  return is_controller_if_cond(if_stat) && if_stat->r->is_integral(id);
            }
            /*if (CONTROLLER == ??) then/ GOTO */
            inline bool is_controller_if(const std::shared_ptr<ir_stat> &if_stat) {
                  return is_controller_if_cond(if_stat) || is_controller_if_cond_goto(if_stat);
            }
            /* CONSTANT FOR LOOP */
            // inline bool is_constant_for_loop(const std::shared_ptr<ir_stat> &for_stat) {
            //       return for_stat != nullptr && for_stat->is_for_loop() && for_stat->l != nullptr &&
            // }

      } // namespace branch

      namespace assignment {

            /* RVALUE != nullptr */
            inline bool is_rvalue(const std::shared_ptr<ir_stat> &stat) {
                  return stat && stat->r;
            }
            /* LVALUE(S) != nullptr */
            inline bool is_lvalues(const std::shared_ptr<ir_stat> &stat) {
                  return stat && (stat->l || !stat->members.empty());
            }
            /* LVALUE(S) CONTAIN UPVALUE? */
            inline bool is_lvalues_contains_upvalue(const std::shared_ptr<ir_stat> &stat) {
                  if (!stat) {
                        return false;
                  }
                  if (stat->l && stat->l->contains_upvalue()) {
                        return true;
                  }
                  for (const auto &m : stat->members) {
                        if (m && m->contains_upvalue()) {
                              return true;
                        }
                  }
                  return false;
            }
            /* RVALUE == expr kind */
            template <expr_kinds e>
            constexpr bool is_rvalue_k(const std::shared_ptr<ir_stat> &stat) {
                  return is_rvalue(stat) && stat->r->is_k<e>();
            }
            /* RVALUE == tkind */
            template <tkind e>
            constexpr bool is_rvalue_tk(const std::shared_ptr<ir_stat> &stat) {
                  return is_rvalue(stat) && stat->r->is_tk<e>();
            }
            /* ASSIGNMENT RVALUE == PRIMITIVE */
            inline bool is_rvalue_primitive(const std::shared_ptr<ir_stat> &assign) {
                  return is_rvalue(assign) && assign->is_k<keywords::assignment>() && assign->r->is_primitive();
            }
            /* ASSIGNMENT RVALUE == EQUALITY CMP */
            inline bool is_rvalue_equality(const std::shared_ptr<ir_stat> &assign) {
                  return is_rvalue(assign) && assign->is_k<keywords::assignment>() && exprs::branch::equality(assign->r);
            }
            /* RVALUE CONTAINS REGISTER? */
            inline bool is_rvalue_contains(const std::shared_ptr<ir_stat> &stat, const luramas_register r) {
                  return is_rvalue(stat) && stat->r->contains(r);
            }
            /* RVALUE CONTAINS EXPR? */
            inline bool is_rvalue_contains(const std::shared_ptr<ir_stat> &stat, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return is_rvalue(stat) && stat->r->contains(expr);
            }
            /* ASSIGNMENT SINGLE ASSIGNED */
            inline bool is_single_assignment(const std::shared_ptr<ir_stat> &assign) {
                  return assign && (assign->is_k<keywords::memoryset>() || assign->is_k<keywords::assignment>() || assign->is_k<keywords::table_assign>()) && assign->l && assign->members.empty();
            }
            /* ASSIGNMENT SINGLE LVALUE == REG */
            inline bool is_reg_assignment(const std::shared_ptr<ir_stat> &assign) {
                  return assign && assign->is_k<keywords::assignment>() && assign->l && assign->members.empty() && assign->l->is_register_reference();
            }
            /* ASSIGNMENT SINGLE LVALUE == REG, RVALUE != nullptr */
            inline bool is_reg_assignment_has_rvalue(const std::shared_ptr<ir_stat> &assign) {
                  return is_reg_assignment(assign) && assign->r;
            }
            /* TABLE REG ASSIGN == REG */
            inline bool is_table_assign_reg(const std::shared_ptr<ir_stat> &table_assign, const luramas_register reg) {
                  return table_assign && table_assign->is_k<keywords::table_assign>() && table_assign->l && table_assign->l->l && table_assign->l->l->is_reg(reg);
            }
            /* ASSIGNMENT SINGLE ASSIGNED, HAS RVALUE */
            inline bool is_single_assignment_rvalue(const std::shared_ptr<ir_stat> &assign) {
                  return is_single_assignment(assign) && assign->r;
            }
            /* ASSIGNMENT RVALUE == BOOLEAN */
            inline bool is_rvalue_boolean(const std::shared_ptr<ir_stat> &assign) {
                  return is_rvalue_primitive(assign) && assign->r->is_tk<tkind::boolean>();
            }
            /* ASSIGNMENT RVALUE == COMPARITIVE EQUALITY */
            inline bool is_rvalue_comparitive_equality(const std::shared_ptr<ir_stat> &assign) {
                  return assign->r && exprs::branch::equality(assign->r);
            }
            /* ASSIGNMENT RVALUE == COMPARITIVE EQUALITY, NOT CONTAINS */
            inline bool is_rvalue_comparitive_equality_not_contains(const std::shared_ptr<ir_stat> &assign, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return is_rvalue_comparitive_equality(assign) && !assign->r->contains(expr);
            }
            /* ASSIGNMENT RVALUE == COMPARITIVE EQUALITY, NOT CONTAINS */
            inline bool is_rvalue_comparitive_equality_contains(const std::shared_ptr<ir_stat> &assign, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return is_rvalue_comparitive_equality(assign) && assign->r->contains(expr);
            }
            /* ASSIGNMENT SINGLE ASSIGNED, RVALUE BOOLEAN */
            inline bool is_single_assignment_rvalue_boolean(const std::shared_ptr<ir_stat> &assign) {
                  return is_single_assignment(assign) && is_rvalue_boolean(assign);
            }
            /* ASSIGNMENT RVALUE == TABLE */
            inline bool is_rvalue_table(const std::shared_ptr<ir_stat> &assign) {
                  return is_rvalue(assign) && assign->is_k<keywords::assignment>() && exprs::values::is_table(assign->r);
            }
            /* SINGLE LVALUE == REG */
            inline bool is_reg_assignment(const std::shared_ptr<ir_stat> &assign, const luramas_register reg) {
                  return is_reg_assignment(assign) && assign->l->is_reg(reg);
            }
            /* ASSIGNMENT SINGLE LVALUE == REG, RVALUE == BOOLEAN */
            inline bool is_reg_assignment_rvalue_boolean(const std::shared_ptr<ir_stat> &assign) {
                  return is_reg_assignment(assign) && is_rvalue_boolean(assign);
            }
            /* ASSIGNMENT SINGLE LVALUE == REG, RVALUE == BOOLEAN */
            inline bool is_reg_assignment_rvalue_boolean(const std::shared_ptr<ir_stat> &assign, const luramas_register reg) {
                  return is_reg_assignment(assign, reg) && is_rvalue_boolean(assign);
            }

            /* RVALUE == RVALUE */
            inline bool same_rvalue_assignment(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r, const bool safe = true) {
                  return is_rvalue(l) && is_rvalue(r) && l->r->compare(r->r, safe);
            }
            /* STAT SINGLE LVALUE = ??, STAT SINGLE LVALUE = ??, LVALUE == LVALUE */
            inline bool same_single_assignment(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r, const bool safe = true) {
                  return is_single_assignment(l) && is_single_assignment(r) && l->k == r->k && l->l->compare(r->l, safe) &&
                         ((!is_memoryset(l) && !is_memoryset(r)) || ((!l->v && !r->v) || l->v->compare(r->v, safe)));
            }
            /* STAT SINGLE LVALUE = ??, STAT SINGLE LVALUE = ??, LVALUE == LVALUE, RVALUE DOES NOT CONTAIN EXPR */
            inline bool same_single_assignment_rvalue_not_contains(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return same_single_assignment(l, r) && expr && l->r && r->r && !l->r->contains(expr) && !r->r->contains(expr);
            }
            /* STAT SINGLE LVALUE = ??, STAT SINGLE LVALUE = ??, LVALUE == LVALUE, RVALUE == RVALUE */
            inline bool same_assignment_single(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r, const bool safe = true) {
                  return same_single_assignment(l, r, safe) && same_rvalue_assignment(l, r, safe);
            }
            /* STAT SINGLE LVALUE = ??, STAT SINGLE LVALUE = ??, LVALUE REG == LVALUE REG */
            inline bool same_single_reg_assignment(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r) {
                  return is_single_assignment(l) && is_single_assignment(r) && l->l->is_register_reference() && r->l->is_reg(l->l->reg);
            }
            /* SINGLE LVALUE = SINGLE LVALUE, LVALUE == LVALUE, RVALUE == BOOLEAN, RVALUE == BOOLEAN */
            inline bool same_single_assignment_rvalue_boolean(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r) {
                  return same_single_assignment(l, r) && is_rvalue_boolean(l) && is_rvalue_boolean(r);
            }
            /*  ASSIGNMENT == SINGULAR && REG, RVALUE == TABLE,  TABLE ASSIGNMENT TABLE == REG  */
            inline bool same_single_table_assignment_table_reg(const std::shared_ptr<ir_stat> &assign, const std::shared_ptr<ir_stat> &table_assign) {
                  return is_reg_assignment(assign) && is_rvalue_table(assign) && is_table_assign_reg(table_assign, assign->l->reg);
            }

            /* ASSIGNEMENT = ASSIGNMENT [ARITH OP] ?? */
            inline bool arithmetic_assignment(const std::shared_ptr<ir_stat> &assign) {
                  return is_reg_assignment(assign) && exprs::values::is_arith(assign->r) && assign->r->l && *assign->l == *assign->r->l;
            }
      } // namespace assignment

      namespace mutate {

            /* FLIP STAT CMP */
            inline void flip_cmp(const std::shared_ptr<ir_stat> &stat) {
                  if (stat->b == il::arch::data::bin_kinds::nothing) {
                        stat->b = il::arch::data::bin_kinds::et_;
                  }
                  stat->b = il::arch::data::bin_kindflip(stat->b);
                  return;
            }

            /* Mutates compare to just ET */
            inline void cmp_true(const std::shared_ptr<ir_stat> &stat) {
                  stat->b = il::arch::data::bin_kinds::et_;
                  return;
            }

            /* REPLACE CMP */
            inline void replace_cmp(const std::shared_ptr<ir_stat> &stat, const std::shared_ptr<ir_stat::ir_expr> &l, const luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing, const std::shared_ptr<ir_stat::ir_expr> &r = nullptr) {
                  stat->l = l;
                  stat->b = b;
                  stat->r = r;
                  return;
            }

            /* CLEAR STAT CHANGE IT TO IF COND */
            template <bool flip = false, bool swap = false>
            inline void if_stat_cleared(std::shared_ptr<ir_stat> &stat) {
                  auto l = stat->l;
                  auto b = stat->b;
                  auto r = stat->r;
                  stat->clear();
                  if (swap) {
                        std::swap(l, r);
                  }
                  stat->emit_cond(l, b, r);
                  if (flip) {
                        flip_cmp(stat);
                  }
                  return;
            }

            /* CLEAR STAT CHANGE IT TO IF COND */
            template <bool flip = false, bool swap = false>
            inline void cond_goto_stat_cleared(const std::shared_ptr<ir_stat> &stat, const luramas_address label) {
                  auto l = stat->l;
                  auto b = stat->b;
                  auto r = stat->r;
                  stat->clear();
                  if (swap) {
                        std::swap(l, r);
                  }
                  stat->emit_cond_goto(l, b, label, r);
                  if (flip) {
                        flip_cmp(stat);
                  }
                  return;
            }

            template <bool flip = false, bool swap = false>
            inline void until_stat_cleared(const std::shared_ptr<ir_stat> &stat) {
                  auto l = stat->l;
                  auto b = stat->b;
                  auto r = stat->r;
                  stat->clear();
                  if (swap) {
                        std::swap(l, r);
                  }
                  stat->emit_until(l, b, r);
                  if (flip) {
                        flip_cmp(stat);
                  }
                  return;
            }

            template <bool flip = false, bool swap = false>
            inline void while_stat_cleared(const std::shared_ptr<ir_stat> &stat) {
                  auto l = stat->l;
                  auto b = stat->b;
                  auto r = stat->r;
                  stat->clear();
                  if (swap) {
                        std::swap(l, r);
                  }
                  stat->emit_while(l, b, r);
                  if (flip) {
                        flip_cmp(stat);
                  }
                  return;
            }

            /* CLEAR STAT, EMIT CONTINUE */
            inline void continue_stat_cleared(const std::shared_ptr<ir_stat> &stat) {
                  stat->clear();
                  stat->emit_continue();
                  return;
            }

            /* CLEAR STAT, EMIT BREAK */
            inline void break_stat_cleared(const std::shared_ptr<ir_stat> &stat) {
                  stat->clear();
                  stat->emit_break();
                  return;
            }

            /* CLEAR STAT, GOTO */
            inline void goto_stat_cleared(const std::shared_ptr<ir_stat> &stat, const luramas_address goto_loc) {
                  stat->clear();
                  stat->emit_goto(goto_loc);
                  return;
            }

            /* EXTRACT VOLATILES FROM EXPS AS STATS */
            inline ir_stat::space extract_volatiles_stats(const std::shared_ptr<ir_stat> &stat) {

                  ir_stat::space result;
                  ir_stat::ir_expr::space parents;
                  boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> ignore;

                  for (auto &e : stat->extract_ordered_exprs()) {
                        tools::exprs::extraction::parent_volatiles(e, parents, ignore);
                  }
                  for (const auto &i : parents) {
                        if (const auto p = i->transform(); p) {
                              result.emplace_back(p);
                        }
                  }
                  return result;
            }

            /* MIMIC EITHER ET OR NT FROM STAT COND (TO UNARY) */
            template <bool flip = false>
            inline std::shared_ptr<ir_stat::ir_expr> mimic_compare(const std::shared_ptr<ir_stat> &comparable_stat, std::shared_ptr<ir_stat::ir_expr> &expr) {
                  if (!branch::is_comparable(comparable_stat)) {
                        return expr;
                  }
                  auto bin = comparable_stat->b;
                  if (flip) {
                        bin = il::arch::data::bin_kindflip(bin);
                  }
                  switch (bin) {
                        case il::arch::data::bin_kinds::et_: {
                              if (tools::exprs::values::is_unary(expr)) {
                                    expr = expr->l;
                              } else {
                                    expr->u = il::arch::data::bin_kinds::nothing;
                              }
                              break;
                        }
                        case il::arch::data::bin_kinds::nt_: {
                              if (!tools::exprs::values::is_unary(expr)) {
                                    expr = tools::exprs::generate::unary(expr, il::arch::data::bin_kinds::not_);
                              } else {
                                    expr->u = il::arch::data::bin_kinds::not_;
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  return expr;
            }

            /* MIMIC EITHER ET OR NT FROM STAT COND (TO UNARY) */
            inline void mimic_compare(const std::shared_ptr<ir_stat> &target, const std::shared_ptr<ir_stat> &source) {
                  if (!branch::is_any_comparable(target) || !branch::is_any_comparable(source)) {
                        return;
                  }
                  target->l = source->l;
                  target->r = source->r;
                  target->b = source->b;
                  return;
            }

      } // namespace mutate

      namespace generate {

            /* GENERATE END STAT */
            inline std::shared_ptr<ir_stat> end() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_end();
                  return result;
            }

            /* GENERATE COND GOTO STAT */
            inline std::shared_ptr<ir_stat> cond_goto_label(const std::shared_ptr<ir_stat::ir_expr> &l, const luramas::il::arch::data::bin_kinds b, const luramas_address &loc, const std::shared_ptr<ir_stat::ir_expr> &r) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_cond_goto(l, b, loc, r);
                  return result;
            }

            /* GENERATE WHILE STAT */
            inline std::shared_ptr<ir_stat> while_stat(const std::shared_ptr<ir_stat::ir_expr> &l, const luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing, const std::shared_ptr<ir_stat::ir_expr> &r = nullptr) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_while(l, b, r);
                  return result;
            }

            /* GENERATE UNTIL STAT */
            inline std::shared_ptr<ir_stat> until(const std::shared_ptr<ir_stat::ir_expr> &l, const luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing, const std::shared_ptr<ir_stat::ir_expr> &r = nullptr) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_until(l, b, r);
                  return result;
            }

            /* GENERATE GOTO STAT */
            inline std::shared_ptr<ir_stat> goto_label(const luramas_address &loc) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_goto(loc);
                  return result;
            }

            /* GENERATE DEFINITION STAT */
            inline std::shared_ptr<ir_stat> definition() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_definition();
                  return result;
            }

            /* GENERATE LABEL STAT */
            inline std::shared_ptr<ir_stat> label(const luramas_address &loc) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_label(loc);
                  return result;
            }

            /* GENERATE CONTINUE STAT */
            inline std::shared_ptr<ir_stat> continue_stat() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_continue();
                  return result;
            }

            /* GENERATE BREAK STAT */
            inline std::shared_ptr<ir_stat> break_stat() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_break();
                  return result;
            }

            /* GENERATE ELSE STAT */
            inline std::shared_ptr<ir_stat> else_stat() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_else();
                  return result;
            }

            /* GENERATE REPEAT STAT */
            inline std::shared_ptr<ir_stat> repeat() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_repeat();
                  return result;
            }

            /* GENERATE MAYBE STACK STAT */
            inline std::shared_ptr<ir_stat> create_stack(const std::shared_ptr<ir_stat::ir_expr> &l) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_create_stack(l);
                  return result;
            }

            /* GENERATE COND STAT */
            inline std::shared_ptr<ir_stat> cond(const std::shared_ptr<ir_stat::ir_expr> &l, const luramas::il::arch::data::bin_kinds b = luramas::il::arch::data::bin_kinds::nothing, const std::shared_ptr<ir_stat::ir_expr> &r = nullptr) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_cond(l, b, r);
                  return result;
            }

            /* GENERATE TABLE ASSIGNMENT STAT */
            inline std::shared_ptr<ir_stat> table_assignment(const std::shared_ptr<ir_stat::ir_expr> &t, const std::shared_ptr<ir_stat::ir_expr> &idx, const std::shared_ptr<ir_stat::ir_expr> &v) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_tab_assign(t, idx, v);
                  return result;
            }

            /* GENERATE STACK PUSH STAT */
            inline std::shared_ptr<ir_stat> stack_push(const std::shared_ptr<ir_stat::ir_expr> &value, const std::shared_ptr<ir_stat::ir_expr> &id) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_stack_push(value, id);
                  return result;
            }

            /* GENERATE STACK READ STAT */
            inline std::shared_ptr<ir_stat> stack_read(const std::shared_ptr<ir_stat::ir_expr> &dest, const std::shared_ptr<ir_stat::ir_expr> &amt, const std::shared_ptr<ir_stat::ir_expr> &id) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_stack_read(dest, amt, id);
                  return result;
            }

            /* GENERATE STACK POP STAT */
            inline std::shared_ptr<ir_stat> stack_pop(const std::shared_ptr<ir_stat::ir_expr> &value, const std::shared_ptr<ir_stat::ir_expr> &id) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_stack_pop(value, id);
                  return result;
            }

            /* GENERATE MEMSET STAT */
            inline std::shared_ptr<ir_stat> memoryset(const std::shared_ptr<ir_stat::ir_expr> &target, const std::shared_ptr<ir_stat::ir_expr> &source, const luramas_address set_bits, const std::shared_ptr<ir_stat::ir_expr> &offset = nullptr) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_memoryset(target, source, set_bits, offset);
                  return result;
            }

            /* GENERATE ASSIGNMENT STAT */
            inline std::shared_ptr<ir_stat> assignment(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_assignment(l, r);
                  return result;
            }

            /* GENERATE ASSIGNMENT STAT */
            inline std::shared_ptr<ir_stat> assignment(const ir_stat::ir_expr::space &l, const std::shared_ptr<ir_stat::ir_expr> &r) {
                  auto result = std::make_shared<ir_stat>();
                  for (const auto &i : l) {
                        result->emit_mul_lv(i);
                  }
                  result->r = r;
                  return result;
            }

            /* GENERATE PAGE FUNCTION START STAT */
            inline std::shared_ptr<ir_stat> page_function_start(const std::shared_ptr<ir_stat::ir_expr> &id) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_page_function_start(id);
                  return result;
            }

            /* GENERATE PAGE FUNCTION END STAT */
            inline std::shared_ptr<ir_stat> page_function_end(const std::shared_ptr<ir_stat::ir_expr> &id) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_page_function_end(id);
                  return result;
            }

            /* GENERATE PAGE FUNCTION END STAT */
            inline std::shared_ptr<ir_stat> page_function_pass() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_page_function_pass();
                  return result;
            }

            /* GENERATE PAGE FUNCTION CALL STAT */
            inline std::shared_ptr<ir_stat> page_function_call(const std::shared_ptr<ir_stat::ir_expr> &id, const std::shared_ptr<ir_stat::ir_expr> &insertion_where, const std::shared_ptr<ir_stat::ir_expr> &value) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_page_function_call(id, insertion_where, value);
                  return result;
            }
            /* GENERATE PAGE FUNCTION CALL */
            inline std::shared_ptr<ir_stat> page_function_call(const std::shared_ptr<ir_stat::ir_expr> &id, const std::shared_ptr<ir_stat::ir_expr> &insertion_where, const std::shared_ptr<ir_stat::ir_expr> &value, const std::shared_ptr<ir_stat> &definition) {
                  if (!is_definition(definition)) {
                        return nullptr;
                  }
                  auto result = page_function_call(id, insertion_where, value);
                  for (const auto &[r, _] : definition->args) {
                        result->members.emplace_back(exprs::generate::reg(r));
                  }
                  return result;
            }

            /* GENERATE PAGE FUNCTION JUMP STAT */
            inline std::shared_ptr<ir_stat> page_function_jump(const std::shared_ptr<ir_stat::ir_expr> &id) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_page_function_jump(id);
                  return result;
            }
            /* GENERATE PAGE FUNCTION JUMP */
            inline std::shared_ptr<ir_stat> page_function_jump(const std::shared_ptr<ir_stat::ir_expr> &id, const std::shared_ptr<ir_stat> &definition) {
                  if (!is_definition(definition)) {
                        return nullptr;
                  }
                  auto result = page_function_jump(id);
                  for (const auto &[r, _] : definition->args) {
                        result->members.emplace_back(exprs::generate::reg(r));
                  }
                  return result;
            }
            /* GENERATE PAGE FUNCTION JUMP */
            inline std::shared_ptr<ir_stat> page_function_jump(const std::shared_ptr<ir_stat::ir_expr> &id, const ir_stat::ir_expr::space &v) {

                  auto result = page_function_jump(id);
                  result->members = v;
                  return result;
            }

            /* GENERATE FOR LOOP INIT STAT */
            inline std::shared_ptr<ir_stat> for_loop_init() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_for_loop_init();
                  return result;
            }

            /* GENERATE CALL STAT */
            inline std::shared_ptr<ir_stat> call(const std::shared_ptr<ir_stat::ir_expr> &func, const ir_stat::ir_expr::space &args, const luramas_flag fsafe = false) {
                  auto result = std::make_shared<ir_stat>();
                  for (const auto &a : args) {
                        result->emit_arg(a);
                  }
                  result->emit_call(func);
                  result->flags.fsafe = fsafe;
                  return result;
            }

            /* GENERATE RETURN STAT */
            inline std::shared_ptr<ir_stat> retn(const ir_stat::ir_expr::space &args) {
                  auto result = std::make_shared<ir_stat>();
                  for (const auto &a : args) {
                        result->emit_return(a);
                  }
                  return result;
            }

            /* GENERATE RETURN STAT */
            inline std::shared_ptr<ir_stat> retn() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_return();
                  return result;
            }

            /* GENERATES ISOLATE */
            inline std::shared_ptr<ir_stat> isolate() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_isolate();
                  return result;
            }

            /* GENERATES SET FLAG */
            inline std::shared_ptr<ir_stat> set_flag(const std::shared_ptr<ir_stat::ir_expr> &flag, const std::shared_ptr<ir_stat::ir_expr> &source) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_setflag(flag, source);
                  return result;
            }

            /* GENERATE PAGE FUNCTION CLOSURE STAT */
            inline std::shared_ptr<ir_stat> page_function_closure(const std::shared_ptr<ir_stat::ir_expr> &id, const std::shared_ptr<ir_stat::ir_expr> &closure) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_page_function_closure(id, closure);
                  return result;
            }

            /* GENERATES NOTHING */
            inline std::shared_ptr<ir_stat> nothing() {
                  auto result = std::make_shared<ir_stat>();
                  return result;
            }

            /* GENERATE METADATA STAT */
            inline std::shared_ptr<ir_stat> metadata(const std::shared_ptr<ir_stat::ir_expr> &name, const std::shared_ptr<ir_stat::ir_expr> &data) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_metadata(name, data);
                  return result;
            }

            /* GENERATE TAG START STAT */
            inline std::shared_ptr<ir_stat> tag_start(const std::shared_ptr<ir_stat::ir_expr> &name, const std::shared_ptr<ir_stat::ir_expr> &table) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_tag_start(name, table);
                  return result;
            }

            /* GENERATE TAG END STAT */
            inline std::shared_ptr<ir_stat> tag_end() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_tag_end();
                  return result;
            }

            /* GENERATE ENTRY POINT STAT */
            inline std::shared_ptr<ir_stat> entry_point() {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_entry_point();
                  return result;
            }

            /* GENERATE COMMAND STAT */
            inline std::shared_ptr<ir_stat> command(const std::shared_ptr<ir_stat::ir_expr> &name) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_command(name);
                  return result;
            }

            /* GENERATE BITWRITE STAT */
            inline std::shared_ptr<ir_stat> bitwrite(const std::shared_ptr<ir_stat::ir_expr> &dest, const std::shared_ptr<ir_stat::ir_expr> &src, const std::shared_ptr<ir_stat::ir_expr> &min, const std::shared_ptr<ir_stat::ir_expr> &max) {
                  auto result = std::make_shared<ir_stat>();
                  result->emit_bitwrite(dest, src, min, max);
                  return result;
            }

            namespace flags {

                  namespace paging {

                        /* SET FLAGS */
                        inline std::shared_ptr<ir_stat> definition(const std::shared_ptr<ir_stat> &def_stat) {
                              if (!def_stat) {
                                    return def_stat;
                              }
                              def_stat->flags.flink_regs = true;
                              def_stat->flags.fpage_keyword = true;
                              return def_stat;
                        }

                        /* SET FLAGS */
                        inline std::shared_ptr<ir_stat> seperator(const std::shared_ptr<ir_stat> &stat) {
                              if (!stat) {
                                    return stat;
                              }
                              stat->flags.fpage_seperator = true;
                              return stat;
                        }

                  } // namespace paging

                  namespace immutable {

                        /* SET FLAGS */
                        inline std::shared_ptr<ir_stat> set(const std::shared_ptr<ir_stat> &stat, const luramas_flag fsynthetic = false) {
                              if (!stat) {
                                    return stat;
                              }
                              stat->flags.fimmutable = true;
                              if (fsynthetic) {
                                    stat->flags.fsynthetic = fsynthetic;
                              }
                              return stat;
                        }
                  } // namespace immutable

                  namespace synthetic::flagable {

                        /* SET FLAGS */
                        inline void set(const std::shared_ptr<ir_stat> &stat) {
                              if (!stat) {
                                    return;
                              }
                              stat->flags.fflagable = true;
                              stat->flags.fsynthetic = true;
                              return;
                        }

                        /* GENERATE SYNTHETIC FLAGABLE PASS */
                        inline std::shared_ptr<ir_stat> pass_init_assign(const passes::pass_manager &pm) {
                              auto result = std::make_shared<ir_stat>();
                              const auto reg = exprs::generate::reg(pm.ir.avaliable_register());
                              result->emit_assignment(reg, exprs::generate::boolean(false));
                              set(result);
                              reg->flags.fsynthetic = true;
                              return result;
                        }

                        /* GENERATE SYNTHETIC FLAGGABLE COND STAT */
                        inline std::shared_ptr<ir_stat> cond(const std::shared_ptr<ir_stat::ir_expr> &l) {
                              auto result = std::make_shared<ir_stat>();
                              result->emit_cond(l, luramas::il::arch::data::bin_kinds::nothing, nullptr);
                              set(result);
                              return result;
                        }

                  } // namespace synthetic::flagable
            } // namespace flags

            namespace emitter {

                  /* EMIT ANNOTATION */
                  inline void annotation(const std::shared_ptr<ir_stat> &buffer, const std::string &str) {
                        buffer->annotation = str;
                        return;
                  }
            } // namespace emitter
      } // namespace generate

      namespace common {

            /* STAT RETURN == RETURN */
            inline bool same_returns(const std::shared_ptr<ir_stat> &return_l, const std::shared_ptr<ir_stat> &return_r) {
                  if (!return_l || !return_r || !return_l->is_k<keywords::retn>() || !return_r->is_k<keywords::retn>() || return_l->members.size() != return_r->members.size()) {
                        return false;
                  }
                  for (auto i = 0u; i < return_l->members.size(); ++i) {
                        if (*return_l->members[i] != *return_r->members[i]) {
                              return false;
                        }
                  }
                  return true;
            }
            /* RETURN WITH NO PARAMS */
            inline bool empty_return(const std::shared_ptr<ir_stat> &return_stat) {
                  return is_return(return_stat) && return_stat->members.empty();
            }
            /* SAME EMPTY RETURNS */
            inline bool empty_return(const std::shared_ptr<ir_stat> &return_stat_l, const std::shared_ptr<ir_stat> &return_stat_r) {
                  return empty_return(return_stat_l) && empty_return(return_stat_r);
            }
            /* SAME STACK PUSH WITH IDS */
            inline bool same_stack_push(const std::shared_ptr<ir_stat> &stack_push_stat_l, const std::shared_ptr<ir_stat> &stack_push_stat_r) {
                  return is_stack_push(stack_push_stat_l) && is_stack_push(stack_push_stat_r) && is_stack_push(stack_push_stat_r, stack_push_stat_l->v->extract_integral());
            }
            /* SAME STACK POP WITH IDS */
            inline bool same_stack_pop(const std::shared_ptr<ir_stat> &stack_pop_stat_l, const std::shared_ptr<ir_stat> &stack_pop_stat_r) {
                  return is_stack_pop(stack_pop_stat_l) && is_stack_pop(stack_pop_stat_r) && is_stack_pop(stack_pop_stat_r, stack_pop_stat_l->v->extract_integral());
            }

            /* CONTIGUOUS KEYWORD */
            template <keywords k>
            inline bool contiguous(passes::pass_manager &pm, const luramas_address start, const luramas_address end) {
                  for (auto e = start; e < end; ++e) {
                        if (!pm[e]->is_k<k>()) {
                              return false;
                        }
                  }
                  return true;
            }

            /* COMPARE CONTAINS EXPR? */
            inline bool compare_contains(const std::shared_ptr<ir_stat> &stat, const std::shared_ptr<ir_stat::ir_expr> &expr) {
                  return branch::is_comparable(stat) && expr && ((stat->l && stat->l->contains(expr)) || (stat->r && stat->r->contains(expr)));
            }

            /* SAME FUNCTION CALL? */
            inline bool same_call_function(const std::shared_ptr<ir_stat> &call_l, const std::shared_ptr<ir_stat> &call_r) {
                  return is_call(call_l) && is_call(call_r) && call_l->l && *call_l->l == *call_r->l;
            }
            /* SAME CALLING ARG COUNT? */
            inline bool same_call_arg_count(const std::shared_ptr<ir_stat> &call_l, const std::shared_ptr<ir_stat> &call_r) {
                  return is_call(call_l) && is_call(call_r) && call_l->members.size() == call_r->members.size();
            }
            /* SAME FUNCTION CALL AND ARG COUNT? */
            inline bool same_call_function_arg_count(const std::shared_ptr<ir_stat> &call_l, const std::shared_ptr<ir_stat> &call_r) {
                  return same_call_function(call_l, call_r) && same_call_arg_count(call_l, call_r);
            }
            /* SAME FUNCTION CALL AND ARG COUNT? */
            inline bool same_call_function_arg_count(const std::shared_ptr<ir_stat> &call_l, const std::shared_ptr<ir_stat> &call_r, const luramas_count n) {
                  return same_call_function(call_l, call_r) && same_call_arg_count(call_l, call_r) && call_l->members.size() == n;
            }
            /* JLABEL REFERENCES LABEL? */
            inline bool is_ref(const std::shared_ptr<ir_stat> &stat) {
                  return branch::is_goto(stat) || branch::is_cond_goto(stat);
            }
            /* JLABEL REFERENCES LABEL? */
            inline bool is_ref(const std::shared_ptr<ir_stat> &stat, const luramas_address jlabel) {
                  return branch::is_goto(stat, jlabel) || branch::is_cond_goto_label(stat, jlabel);
            }
            /* SAME STATEMENTS? */
            inline bool same_stats(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r, const bool safe = true, const bool labels = false) {
                  return l && r && l->compare(r, safe, labels);
            }
            /* SAME INTERRUPTS? */
            inline bool same_interrupts(const std::shared_ptr<ir_stat> &l, const std::shared_ptr<ir_stat> &r) {
                  return l && r && l->is_flow_interrupt() && r->is_flow_interrupt() && same_stats(l, r, false);
            }

            /* Clone stat if allowed */
            inline std::shared_ptr<ir_stat> clone(const std::shared_ptr<ir_stat> &p, const luramas_flag fallow_clone = true) {
                  return p && fallow_clone ? p->clone() : p;
            }
      } // namespace common

      namespace unsafe {

            inline std::shared_ptr<ir_stat> ref(passes::pass_manager &pm, const std::shared_ptr<ir_stat> &stat) {
                  if (!stat) {
                        return nullptr;
                  }
                  switch (stat->k) {
                        case keywords::label: {
                              if (branch::is_single_label_ref(pm, stat)) {
                                    return stat;
                              }
                              break;
                        }
                        default: {
                              return stat;
                        }
                  }
                  return nullptr;
            }
      } // namespace unsafe

      namespace bitwise {

            /* BITWRITE */
            inline bool is_bitwrite_contiguous(const std::shared_ptr<ir_stat> &bitwrite_stat, const std::shared_ptr<ir_stat> &bitwise_stat_l) {
                  return is_bitwrite(bitwrite_stat) && is_bitwrite(bitwise_stat_l) && exprs::basic::is_integral(bitwrite_stat->lba, bitwise_stat_l->v) && bitwrite_stat->lba->extract_integral() + 1u == bitwise_stat_l->v->extract_integral();
            }
            /* BITWRITE BITS */
            inline luramas_int extract_bitwrite_bits(const std::shared_ptr<ir_stat> &bitwrite_stat) {
                  if (is_bitwrite(bitwrite_stat) && !exprs::basic::is_integral(bitwrite_stat->v, bitwrite_stat->lba)) {
                        return 0u;
                  }
                  const auto min = bitwrite_stat->v->extract_integral();
                  const auto max = bitwrite_stat->lba->extract_integral();
                  return min > max ? 0u : (max - min) + 1u;
            }
      } // namespace bitwise

      /* INC BASED ON VALID NEXT(1) */
      inline void valid_next(passes::pass_manager &pm, luramas_address &buffer) {
            buffer += pm.valid_next<1u>(buffer);
            return;
      }
      /* DEC BASED ON VALID NEXT(1) */
      inline void valid_prev(passes::pass_manager &pm, luramas_address &buffer) {
            buffer -= pm.valid_prev<1u>(buffer);
            return;
      }

      /* INC BASED ON VALID NEXT(1) */
      inline luramas_address valid_next_n(passes::pass_manager &pm, const luramas_address n) {
            auto buff = n;
            valid_next(pm, buff);
            return buff;
      }
      /* DEC BASED ON VALID NEXT(1) */
      inline luramas_address valid_prev_n(passes::pass_manager &pm, const luramas_address n) {
            auto buff = n;
            valid_prev(pm, buff);
            return buff;
      }

      /* CREATE JLABLE ITER N */
      inline std::int8_t iter(const luramas_address start, const luramas_address end) {
            return end > start ? 1 : -1;
      }

      /* Changes buffer to on the end of condition/loop if its greater, else does not change buffer. */
      inline void safe_jump_end(luramas::ir::passes::pass_manager &pm, const luramas_address idx, luramas_address &buffer) {

            const auto &e = pm[idx];
            if (const auto end_label = e->end_label ? e->end_label : e->elif_end_label; end_label) {
                  if (const auto end = pm.processed.end_labels[end_label].second; end > buffer) {
                        buffer = end;
                  }
            }
            return;
      }
} // namespace luramas::ir::tools::stat