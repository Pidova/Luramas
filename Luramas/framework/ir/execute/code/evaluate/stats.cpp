#include "common.hpp"

namespace luramas::ir::execution::evaluate::stats {

      void action::emit_jump_loc(const luramas_address loc) {
            this->k = action_kind::jump_loc;
            this->jump = loc;
            return;
      }
      void action::emit_jump_label(const luramas_address label) {
            this->k = action_kind::jump_label;
            this->jump = label;
            return;
      }

      error::result<action, errors::kinds> execute(environment &env, const std::shared_ptr<ir_stat> &stat) {

            error::result<action, errors::kinds> result;

            if (!stat) {
                  exe_error<errors::kinds::null_pointer>(result);
                  return result;
            }

            const auto assign = [&](const auto &l, const auto &r) {
                  if (!l || !r) {
                        exe_error<errors::kinds::null_pointer>(result);
                        return;
                  }
                  if (l->flags.fconstant) {
                        exe_error<errors::kinds::assign_invalid_constant>(result);
                        return;
                  }
                  switch (l->k) {
                        case expr_kinds::reg: {

                              if (const auto obj = exprs::execute(env, r); obj) {
                                    env.registers[l->reg] = obj;
                              } else {
                                    exe_error<errors::kinds::assign_invalid_rvalue>(result);
                                    return;
                              }
                              break;
                        }
                        case expr_kinds::nothing: {

                              switch (l->tk) {
                                    case tkind::global: {
                                          if (const auto obj = exprs::execute(env, r); obj) {
                                                env.globals[l->v] = obj;
                                          } else {
                                                exe_error<errors::kinds::assign_invalid_rvalue>(result);
                                                return;
                                          }
                                          break;
                                    }
                                    default: {
                                          exe_error<errors::kinds::assign_invalid_lvalue>(result);
                                          return;
                                    }
                              }
                              break;
                        }
                        default: {
                              exe_error<errors::kinds::assign_invalid_lvalue>(result);
                              return;
                        }
                  }
                  return;
            };

            switch (stat->k) {

                  case keywords::forloop_generic: {
                        break;
                  }
                  case keywords::forloop_numeric: {
                        break;
                  }
                  case keywords::call: {
                        break;
                  }
                  case keywords::assignment: {

                        if (stat->l) {

                              assign(stat->l, stat->r);
                              if (result) {
                                    return result;
                              }
                        } else {
                        }
                        break;
                  }
                  case keywords::retn: {
                        break;
                  }
                  case keywords::condition: {
                        break;
                  }
                  case keywords::condition_goto: {
                        break;
                  }
                  case keywords::goto_label: {

                        result.d.emit_jump_label(stat->jlabel);
                        break;
                  }
                  case keywords::table_assign: {
                        break;
                  }
                  case keywords::table_setlist: {
                        break;
                  }
                  case keywords::break_: {

                        if (env.breakables.empty()) {
                              exe_error<errors::kinds::break_outside_loop>(result);
                              return result;
                        }
                        result.d.emit_jump_loc(env.breakables.back().second + 1u);
                        break;
                  }
                  case keywords::continue_: {

                        if (env.breakables.empty()) {
                              exe_error<errors::kinds::continue_outside_loop>(result);
                              return result;
                        }
                        result.d.emit_jump_loc(env.breakables.back().first);
                        break;
                  }
                  case keywords::repeat: {
                        break;
                  }
                  case keywords::until: {
                        break;
                  }
                  case keywords::while_: {
                        break;
                  }
                  case keywords::label: {
                        break;
                  }
                  case keywords::definition: {
                        break;
                  }
                  case keywords::for_loop_init: {
                        break;
                  }
                  case keywords::memoryset: {
                        break;
                  }
                  case keywords::switch_: {
                        break;
                  }
                  case keywords::switch_case: {
                        break;
                  }
                  case keywords::switch_default: {
                        break;
                  }
                  case keywords::stack_push: {
                        break;
                  }
                  case keywords::stack_pop: {
                        break;
                  }
                  case keywords::stack_read: {
                        break;
                  }
                  case keywords::isolate: {
                        break;
                  }
                  case keywords::set_flag: {
                        break;
                  }
                  case keywords::create_stack: {
                        break;
                  }
                  case keywords::page_function_closure: {
                        break;
                  }
                  case keywords::page_function_start: {
                        break;
                  }
                  case keywords::page_function_end: {
                        break;
                  }
                  case keywords::page_function_goto: {
                        break;
                  }
                  case keywords::globals_preset: {
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return result;
      }
} // namespace luramas::ir::execution::evaluate::stats