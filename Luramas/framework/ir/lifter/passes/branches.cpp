#include "includes/common.hpp"

void luramas::ir::passes::branch_simplification(pass_manager &pm, shared &s) {

      for (const auto &i : pm.iter()) {

            auto &p = pm[i];
            switch (p->k) {
                  case keywords::condition: {

                        if (pm.valid_prev<1u>(i)) {

                              const auto &prev = pm[i - 1u];
                              if (tools::stat::branch::is_else_cond(prev)) {

                                    /* 
                                        else 
                                            if ()
                                                /.../ 
                                                /[NOT INTERRUPT]/
                                            /end/
                                        /end/
                                    */
                                    const auto end_loc = pm.processed.end_labels[p->end_label].second;
                                    const auto &end = pm[end_loc];
                                    if (pm.valid_prev<1u>(end_loc) && pm.valid_next<1u>(end_loc) &&
                                        !pm[end_loc - 1u]->is_flow_interrupt() && tools::stat::is_end(pm[end_loc + 1u]) && pm.safe(end, p)) {
                                          p->c = condition_kind::elseif_;
                                          pm.remove(end, prev);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
      }
      return;
}

void luramas::ir::passes::branch_optimization(pass_manager &pm, shared &s) {

      std::optional<generation::cfg::cfg> cfg;
      for (const auto &i : pm.iter()) {

            auto &p = pm[i];
            switch (p->k) {
                  case keywords::condition_goto: {

                        const auto label = tools::common::safe_take_jump(pm, i);
                        if (pm.valid_next<1u>(i)) {

                              const auto &next = pm[i + 1u];

                              /*
                                    if (?) then goto l end
                                    /[VALID CONDITION]/
                                    /[TERMINATE] goto l;/
                              */
                              if (pm.is_safe(p)) {

                                    auto valid = std::make_shared<luramas_addresses>();
                                    tools::violations::block_violates(pm, i + 1u, pm.amount(), tools::violations::block_violates_flags({.valid_extract = valid}));
                                    for (const auto &vi : *valid) {
                                          if (tools::stat::branch::same_cond_goto_goto_labels(p, pm[vi])) {

                                                if (!tools::violations::block_violates(pm, i + 1u, vi).valid) {
                                                      continue;
                                                }

                                                tools::stat::mutate::if_stat_cleared<true>(p);
                                                pm.insert_front(vi, tools::stat::generate::end());
                                                pm.set_safe(p);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                                break;
                                          }
                                    }
                              }

                              /*
                                    if (?) then goto l end
                                    /.../
                                    /[VALID BREAKOUT]/
                                    /::l::/
                              */
                              if (pm.is_safe(p) && tools::can_breakout(pm, i, label)) {

                                    tools::stat::mutate::if_stat_cleared(p);

                                    pm.set_safe(p);
                                    pm.insert(p, tools::stat::generate::break_stat(), tools::stat::generate::end());
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                    if (?) then goto l end
                                    /if  (?) then/
                                      /.../
                                      /goto l2/
                                      /::l::/
                                      /[CONDITION STACK MUST BE 0]/
                                      /..../
                                    /[ENDINGS]/
                                    /::l2::/
                              */
                              if (pm.is_safe(p) && tools::stat::branch::is_if_cond(next) && tools::stat::future(i, label)) {

                                    bool valid = true;
                                    const auto prev_label = pm[label - 1u];
                                    if (prev_label->is_k<keywords::goto_label>()) {

                                          const auto back = tools::backtrack(pm, pm.processed.end_labels[next->end_label].second, valid, prev_label->jlabel);
                                          if (valid && tools::stat::branch::is_goto_label(prev_label, pm[back])) {

                                                const auto cond_stack = tools::stack_validate(pm, label, back - 1u);
                                                if (cond_stack.valid || cond_stack.reason == tools::cond_stack_reason::closing) {

                                                      const auto closing_end = cond_stack.reason == tools::cond_stack_reason::closing ? cond_stack.closing_index - 1u : cond_stack.closing_index;

                                                      tools::stat::mutate::if_stat_cleared(p);

                                                      pm.move(p, {label + 1u, closing_end});
                                                      pm.insert(p, tools::stat::generate::goto_label(pm[back]->label), tools::stat::generate::end());
                                                      pm.set_safe(p);
                                                      pm.mut(LURAMAS_DEBUG_LINE);
                                                }
                                          }
                                    }
                              }

                              /* 
                                 if (?) then goto l end;
                                 /.../
                                 /[NO OTHER GOTO REF, AND NO REFS TO [VALID REST] BLOCK VISE VERSA]/
                                 /TERMINAL;/
                                 /::l::/
                                 /[VALID REST]/
                              */
                              if (pm.is_safe(p) && pm.valid_prev<1u>(label) && pm[label - 1u]->is_terminal() && tools::common::is_rest_safe_block_end(pm, label) &&
                                  !tools::contains::refs(pm, tools::transform::address_to_range(i + 1, label), pm.range(label)) && pm.is_safe(label, pm.amount())) {

                                    tools::stat::mutate::if_stat_cleared(p);
                                    pm.set_safe(p);
                                    pm.move(p, pm.range(label));
                                    pm.insert(p, tools::stat::generate::end());
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*                       
                                    if (?) then goto l end
                                    /if  (?) then/
                                        /.../
                                    /end/
                                    /[TRACK NEXT SAFE EXECUTABLE]/
                                    /::l::/
                              */
                              if (tools::stat::branch::is_if_cond(next)) {

                                    const auto end_label = tools::common::safe_take_jump(pm, i + 1u);
                                    if (tools::stat::future(i, end_label) && pm.valid_next<1u>(end_label) && tools::stat::branch::is_cond_goto_label(p, pm[tools::trackers::next_safe_executable(pm, end_label, true)]) && pm.safe(p, next)) {

                                          next->append_cond<expr_logical::and_>(p->l, p->b, p->r);
                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              /*                       
                                    if (?) then goto l end
                                    /[PARENT LOOP END]/
                                    /[TRACK NEXT SAFE EXECUTABLE]/
                              */
                              const auto parent_loop = tools::trackers::parent_loop(pm, i);
                              if (parent_loop.second && tools::stat::branch::is_cond_goto_label(p, pm[tools::trackers::next_safe_executable(pm, parent_loop.second, true)]) && pm.safe(p)) {

                                    tools::stat::mutate::if_stat_cleared(p);
                                    pm.insert(p, tools::stat::generate::break_stat(), tools::stat::generate::end());
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*                    
                                    if (?) then goto l end
                                    /[VALID]/
                                    /::l::/
                              */
                              const auto violation = tools::violations::block_violates(pm, i, label);
                              if (pm.is_safe(p) && violation.valid) {

                                    tools::stat::mutate::if_stat_cleared(p);
                                    pm.set_safe(p, pm[label]);
                                    pm.insert_front(label, tools::stat::generate::end());
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*   
                                while(true) do
                                    /[NO BREAKS CONTINUES]/
                                /end/         
                                /end [REVERSE TAKE JUMP TO NON LOOP]/
                                [SAFE BLOCK]
                                [OR SAFE NEXT EXECUTABLE]
                             */
                              luramas_address parent_loop_loc = 0u;
                              if (pm.is_safe(p) && tools::visitors::parent_loop(pm, i, parent_loop_loc) && tools::stat::branch::is_while_true(pm[parent_loop_loc])) {

                                    const auto end = tools::common::safe_take_jump(pm, parent_loop_loc);
                                    if (pm.valid_next<2u>(end) &&
                                        pm.is_safe(pm[end + 1u]) &&
                                        !tools::contains::implicit::any_to(pm, tools::transform::range_to_addresses(tools::transform::address_to_range(i, parent_loop_loc)), parent_loop_loc) &&
                                        tools::stat::is_end(pm[end + 1u]) && !pm[tools::common::reverse_safe_take_jump(pm, end + 1u)]->is_loop()) {

                                          const auto block = tools::violations::block_violates(pm, end + 2u, pm.amount(), tools::violations::block_violates_flags({.close_on = pm[tools::common::safe_take_jump(pm, i)]}));
                                          const auto ending = (block.reason != tools::violations::block_violation_exceptions::hit_closing_on) ? tools::visitors::next_safe_executable(pm, block.ending_loc) : block.ending_loc;

                                          if (tools::stat::branch::is_cond_goto_label(p, pm[ending])) {

                                                tools::stat::mutate::if_stat_cleared(p);
                                                pm.insert(p, tools::stat::generate::break_stat(), tools::stat::generate::end());

                                                pm.insert(pm[end + 1u], tools::stat::generate::else_stat());
                                                pm.move(pm[block.ending_loc - 1u], pm[end + 1u]);
                                                pm.set_safe(p);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }

                              /*                    
                                if (?) then goto l end
                                /[VIOLATION END/ELSE]/
                                /[SAFE NEXT STAT]/
                                /::l::/
                              */
                              if (pm.is_safe(p) &&
                                  (violation.reason == tools::violations::block_violation_exceptions::invalid_else_conditional || violation.reason == tools::violations::block_violation_exceptions::invalid_end) &&
                                  tools::stat::branch::is_cond_goto_label(p, pm[tools::trackers::next_safe_executable(pm, violation.ending_loc - 1u, true)])) {

                                    tools::stat::mutate::if_stat_cleared(p);
                                    pm.set_safe(p);
                                    pm.insert(pm[violation.ending_loc - 1u], tools::stat::generate::end());
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                    ::l::
                                    if (??) then [BASIC IF, NO ORPHANED CONTINUES, BREAKS]
                                       ...
                                       if (??) then goto l end;
                                    end
                              */
                              if (pm.is_safe(p, next) && tools::stat::is_end(next)) {

                                    const auto if_stat = tools::common::reverse_safe_take_jump(pm, i + 1u);
                                    if (pm.is_safe(pm[if_stat]) && pm.valid_prev<1u>(if_stat) &&
                                        tools::stat::branch::is_cond_goto_label(p, pm[if_stat - 1u]) && tools::common::basic_if_stat(pm, if_stat) &&
                                        !tools::contains::orphans::implicit_goto(pm, tools::transform::address_to_range(if_stat, i + 1u))) {

                                          tools::stat::mutate::while_stat_cleared(pm[if_stat]);
                                          tools::stat::mutate::if_stat_cleared<true>(p);
                                          pm.insert(p, tools::stat::generate::break_stat(), tools::stat::generate::end());

                                          pm.set_safe(p, next, pm[if_stat]);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              /*
                                    if  (...) then
                                        if (...) then goto l end
                                        /return ??/
                                    /end/
                                    /.../
                                    /::label_20:: [SAME SCOPE AS THIS]/
                              */
                              if (pm.valid_next<1u>(i) && pm.is_safe(p)) {
                                    if (const auto &next = pm[i + 1u]; tools::stat::is_return(next)) {

                                          const auto end = i + 2u;
                                          if (pm.is_safe(next, pm[end]) &&
                                              tools::stat::is_end(pm[end]) &&
                                              tools::common::basic_if_stat(pm, tools::common::reverse_safe_take_jump(pm, end)) &&
                                              tools::contains::safe_label(pm, end + 1u, pm[label])) {

                                                tools::stat::mutate::if_stat_cleared<true>(p);
                                                pm.insert(next, tools::stat::generate::end());
                                                pm.insert(pm[end], tools::stat::generate::else_stat());
                                                pm.move(pm[label - 1u], pm[end]);
                                                pm.set_safe(p, next, pm[end]);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }

                        /*
                            ::l::
                            ...
                            [VALID CONTINUE]
                            if (?) then goto l end
                            [OPTIONAL] /::l::/
                            [OPTIONAL, END LABEL OF LOOP] /end/
                        */
                        if (pm.is_safe(p) && tools::can_continue(pm, i, label)) {

                              tools::stat::mutate::if_stat_cleared(p);

                              pm.set_safe(p);
                              pm.insert(p, tools::stat::generate::continue_stat(), tools::stat::generate::end());
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }

                        /*
                            if (??) then goto l end
                            /.../
                            /goto l2;/
                            /::l::/ [ONE REF]
                       */
                        if (pm.is_safe(p) && tools::stat::future(i, label) && tools::count::refs(pm, label) == 1u &&
                            pm.valid_prev<1u>(label) && tools::stat::branch::is_goto(pm[label - 1u])) {

                              if (const auto end = tools::common::safe_block_end(pm, label + 1u); label != end) {
                                    tools::stat::mutate::if_stat_cleared(p);
                                    pm.move(p, {label + 1u, end + 1u});
                                    pm.insert(p, tools::stat::generate::goto_label(pm[label]->label), tools::stat::generate::end());
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        /*
                            ::l::
                            ... [NO ORPHANED IMPLICITS, VALID]
                            if (??) then goto l end;               
                        */
                        if (pm.is_safe(p, pm[label]) && tools::stat::past(i, label) && tools::safe(pm, tools::transform::address_to_range(label, i)) && pm.is_safe(label, i)) {

                              pm.insert(pm[label], tools::stat::generate::repeat());
                              tools::stat::mutate::until_stat_cleared(p);
                              pm.set_safe(label, i);
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }

                        /*
                            /if (??) then/
                               if (??) then goto l end;
                               ..
                               TERMINAL;
                            end
                            ..
                            ::l::
                        */
                        if (pm.is_safe(p, pm[label])) {

                              const auto end = tools::violations::block_violates(pm, i, label);
                              if (pm.valid_prev<1u>(end.ending_loc) && end.reason == tools::violations::block_violation_exceptions::invalid_end &&
                                  pm[end.ending_loc - 1u]->is_terminal() && tools::common::basic_if_stat(pm, tools::common::reverse_safe_take_jump(pm, end.ending_loc)) &&
                                  tools::violations::block_violates(pm, end.ending_loc + 1u, label).valid) {

                                    tools::stat::mutate::if_stat_cleared<true>(p);
                                    pm.set_safe(p, pm[label]);
                                    pm.insert_front(end.ending_loc, tools::stat::generate::end(), tools::stat::generate::else_stat());
                                    pm.move(pm[label - 1u], pm[end.ending_loc]);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::goto_label: {

                        const auto label = pm.processed.labels[p->jlabel];
                        const auto &label_next = tools::visitors::next(pm, label);
                        if (pm.valid_next<1u>(i)) {

                              const auto &next = pm[i + 1u];

                              /*
                                    goto l;
                                    /.../
                                    /[VALID BREAKOUT]/
                                    /l:/
                              */
                              if (pm.is_safe(p) && tools::can_breakout(pm, i, label)) {
                                    p->clear();
                                    p->emit_break();
                                    pm.set_safe(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                   [if stat] (No else statement)
                                    goto l;
                                    /end/
                                    /.../
                                    /[VALID ELSE]/
                                    /l:/
                              */
                              if (pm.is_safe(i, label + 1u) && tools::stat::is_end(next)) {

                                    const auto if_stat = tools::common::reverse_safe_take_jump(pm, i + 1u);
                                    if (pm.is_safe(if_stat, label) && tools::stat::branch::is_if_cond(pm[if_stat]) && !tools::condition_has_else(pm, if_stat, i + 1u) &&
                                        tools::violations::block_violates(pm, i + 2u, label).valid) {

                                          pm.insert(next, tools::stat::generate::else_stat());
                                          pm.insert(pm[label - 1u], next);
                                          pm.set_safe(if_stat, label + 1u);

                                          pm.remove(p, next);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              /* 
                                    if (??) then [NO ELSE]
                                       ...
                                       goto l;
                                    /end/         
                                    [SAFE END]
                                    [TRACK TO SAFE END]
                              */
                              if (pm.is_safe(p, next) && tools::stat::is_end(next)) {

                                    const auto if_loc = tools::common::reverse_safe_take_jump(pm, i + 1u);
                                    if (pm.is_safe(pm[if_loc]) && tools::common::basic_if_stat(pm, if_loc)) {

                                          const auto end = tools::common::safe_block_end(pm, i + 2u);
                                          if (end > i && label > end) {

                                                const auto hit = *pm[end] == *p;
                                                if (pm.is_safe(pm[end]) && (hit || tools::stat::branch::is_goto_label(p, pm[tools::trackers::next_safe_executable(pm, end)]))) {

                                                      pm.remove(p, next);
                                                      pm.insert(next, tools::stat::generate::else_stat());
                                                      if (hit) {
                                                            /*
                                                                 goto l;
                                                                 end
                                                                 ...
                                                                 goto l;                                             
                                                             */
                                                            pm.insert_front(end, next);
                                                      } else {
                                                            pm.insert(pm[end], next);
                                                      }
                                                      pm.set_safe(pm[if_loc], pm[end]);
                                                      pm.mut(LURAMAS_DEBUG_LINE);
                                                }
                                          }
                                    }
                              }
                        }

                        /*
                            ::l::
                            ...
                            [VALID CONTINUE]
                            goto l;
                            [OPTIONAL] /::l::/
                            [OPTIONAL, END LABEL OF LOOP] /end/
                        */
                        if (pm.is_safe(p) && tools::can_continue(pm, i, label)) {

                              p->clear();
                              p->emit_continue();
                              pm.set_safe(p);
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }

                        /*                    
                                 goto l 
                                /[SAFE NEXT STAT, LOOP END]/
                                /[SAFE NEXT STAT]/
                                /::l::/
                         */
                        if (pm.is_safe(p)) {

                              if (auto fend = tools::trackers::next_safe_executable(pm, i, true); tools::stat::branch::is_loop_end(pm, pm[fend])) {
                                    if (fend = tools::trackers::next_safe_executable(pm, fend, true); fend == tools::common::safe_take_jump(pm, i)) {
                                          tools::stat::mutate::break_stat_cleared(p);
                                          pm.set_safe(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }

                        /*
                               if  (...) then
                                   if  (...) then
                                       ...
                                       goto l
                                   /end/
                                  /return ??;/
                               /end/ 
                               /.../
                               ::l::
                        */
                        if (pm.valid_next<4u>(i) && pm.is_safe(p)) {

                              const auto &[n1, n2, n3] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u]);
                              if (tools::stat::is_end(n1) && tools::stat::is_return(n2) && tools::stat::is_end(n3) &&
                                  tools::common::basic_if_stat(pm, tools::common::reverse_safe_take_jump(pm, i + 3u)) &&
                                  tools::contains::safe_label(pm, i + 4u, pm[label])) {

                                    pm.insert(n1, tools::stat::generate::else_stat());
                                    pm.move(n2, n1);
                                    pm.insert(n3, tools::stat::generate::else_stat());
                                    pm.move(pm[label - 1u], n3);
                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::label: {

                        if (pm.valid_prev<1u>(i)) {

                              const auto &prev = pm[i - 1u];

                              /*
                                 /[IF STAT, NO ELSE]/
                                   /.../
                                   /[NO LABEL REFS]/
                                   /.../
                                   /[LABEL]/
                                 end
                                 [End hits as loop]
                              */
                              const auto prev_cond_loc = tools::visitors::prev_cond(pm, i);
                              auto &prev_cond = pm[prev_cond_loc];
                              if (pm.is_safe(p, prev_cond) && tools::stat::branch::is_if_cond(prev_cond) &&
                                  tools::common::basic_if_stat(pm, prev_cond_loc) && !tools::contains::refs(pm, {prev_cond_loc, i}, p->label)) {

                                    const auto end_block = tools::common::safe_cond_block_end<true>(pm, prev_cond_loc);
                                    if (pm.contains(prev_cond_loc + 1u, end_block, i) && tools::common::fall_loop_end(pm, end_block) && pm.is_safe(prev_cond_loc + 1u, end_block)) {

                                          pm.set_safe(prev_cond);
                                          tools::stat::mutate::flip_cmp(prev_cond);
                                          pm.insert(prev_cond, tools::stat::generate::continue_stat());
                                          pm.move(pm[end_block], {prev_cond_loc + 1u, end_block});
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              /*
                                    if (??) then
                                      ...
                                      return;
                                      ::l::
                                      /.../
                                    /end/
                              */
                              if (pm.is_safe(p) && prev->is_terminal()) {

                                    const auto end = tools::violations::block_violates(pm, i, pm.amount());
                                    if (end.reason == tools::violations::block_violation_exceptions::invalid_end && pm.is_safe(pm[end.ending_loc]) && tools::stat::branch::is_if_cond(pm[tools::common::reverse_safe_take_jump(pm, end.ending_loc)])) {

                                          pm.set_safe(p, pm[end.ending_loc]);
                                          pm.move(prev, pm[end.ending_loc]);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }

                        if (pm.valid_next<1u>(i)) {

                              /*
                                     [NO GOTO L]
                                     {cond}
                                     ::l::
                                     ...
                                     else
                                     TERMINATOR
                                     end
                              */
                              const auto unfinished = tools::stack_validate(pm, i + 1u, pm.amount());
                              if (unfinished.reason == tools::cond_stack_reason::termination && pm.valid_next<3u>(unfinished.closing_index)) {

                                    const auto &[end_stat, terminator, else_stat] = std::tie(pm[unfinished.closing_index + 3u], pm[unfinished.closing_index + 2u], pm[unfinished.closing_index + 1u]);
                                    if (tools::stat::branch::is_else_cond(else_stat) && terminator->is_terminator() && pm.is_safe(i, unfinished.closing_index + 1u)) {

                                          if (const auto end_label = end_stat->end_label; end_label && std::ranges::none_of(std::views::iota(pm.processed.end_labels[end_label].first, unfinished.closing_index + 1u), [&](const auto s) { return tools::stat::branch::is_goto_label(pm[s], p); })) {

                                                pm.move(end_stat, {i, unfinished.closing_index + 1u});
                                                pm.set_safe(i, unfinished.closing_index + 1u);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }
                        break;
                  }
                  case keywords::while_: {

                        if (pm.valid_next<3u>(i)) {

                              auto &next = pm[i + 1u];

                              /*
                                    while (true) do
                                        /if (...) then/ [NO ELSES]
                                           /.../
                                           /continue;/
                                        /end/
                                        /break;/
                                    /end/
                              */
                              if (tools::stat::branch::is_while_true(p) && tools::common::basic_if_stat(pm, i + 1u)) {

                                    const auto end = tools::common::safe_take_jump(pm, i + 1u);
                                    if (pm.valid_prev<1u>(end) && pm.valid_next<2u>(end) && pm.is_safe(p, next)) {

                                          const auto &[continue_stat, break_stat, loop_end] = std::tie(pm[end - 1u], pm[end + 1u], pm[end + 2u]);
                                          if (pm.is_safe(continue_stat, break_stat, loop_end) &&
                                              tools::stat::is_continue(continue_stat) && tools::stat::is_continue(break_stat) && tools::stat::branch::is_while_end(p, loop_end)) {

                                                tools::stat::mutate::while_stat_cleared(next);
                                                pm.set_safe(next);
                                                pm.remove(p, continue_stat, break_stat, loop_end);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }
                        if (pm.valid_next<4u>(i)) {

                              auto &next = pm[i + 1u];

                              /*
                                   while (true) do
                                      /if (??) then/ [NO ELSES]
                                         /.../
                                         /continue;/
                                      /end/
                                      /break;/
                                   /end/
                              */
                              if (tools::stat::branch::is_while_true(p) && tools::stat::branch::is_if_cond(next)) {

                                    const auto end = pm.processed.end_labels[next->end_label].second;
                                    if (!tools::condition_has_else(pm, i + 1u, pm.amount()) && pm.valid_next<2u>(end) && pm.valid_prev<1u>(end)) {

                                          const auto &[n1, n2, p1] = std::tie(pm[end + 1u], pm[end + 2u], pm[end - 1u]);
                                          if (tools::stat::is_continue(p1) && tools::stat::is_break(n1) && tools::stat::branch::is_loop_end(p, n2)) {

                                                tools::stat::mutate::mimic_compare(p, next);
                                                pm.remove(next, p1, pm[end], n1);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }

                              /*
                                   while (true) do
                                      /if (??) then/
                                         /.../
                                      /else/
                                        /break;/
                                      /end/
                                   /end/
                              */
                              if (tools::stat::branch::is_while_true(p) && tools::stat::branch::is_if_cond(next) && pm.is_safe(p, next)) {

                                    const auto end = pm.processed.end_labels[next->end_label].second;
                                    if (pm.valid_next<1u>(end) && tools::stat::branch::is_while_end(p, pm[end + 1u])) {

                                          const auto blocks = tools::extract::blocks(pm, i + 1u);
                                          if (blocks.size() == 2u) {

                                                if (const auto else_block = blocks.back(); tools::count::insts(else_block) == 1u && tools::stat::is_break(pm[else_block.first])) {

                                                      tools::stat::mutate::while_stat_cleared(next);
                                                      pm.remove(p);
                                                      pm.remove(else_block.first, else_block.first + 3u);
                                                      pm.mut(LURAMAS_DEBUG_LINE);
                                                }
                                          }
                                    }
                              }
                        }
                        break;
                  }
                  case keywords::condition: {

                        const auto basic_if = tools::common::basic_if_stat(pm, i);
                        if (pm.valid_next<3u>(i)) {

                              /*

                                    repeat
                                          while (true) do
                                             [NO OTHER BREAKS BESIDES ONE LISTED]
                                             ...
                                             if (??) then [SIMPLE IF]
                                                /.../
                                                /continue;/
                                             /end/
                                             /break;/
                                          /end/
                              */
                              if (basic_if) {

                                    const auto end = tools::common::safe_take_jump(pm, i);
                                    if (pm.valid_prev<1u>(end) && pm.valid_next<2u>(end)) {

                                          const auto &[continue_stat, break_stat, loop_end] = std::tie(pm[end - 1u], pm[end + 1u], pm[end + 2u]);
                                          if (pm.is_safe(continue_stat, break_stat, loop_end) &&
                                              tools::stat::is_continue(continue_stat) && tools::stat::is_break(break_stat) && tools::stat::branch::is_loop_end(pm, loop_end)) {

                                                const auto loop_loc = pm.processed.end_labels[loop_end->end_label].first;
                                                const auto breaks = tools::accumulate::keyword(pm, loop_loc, end - 1u, keywords::break_);

                                                if (pm.valid_prev<1u>(loop_loc) && !tools::contains::implicit::break_to(pm, breaks, loop_loc)) {

                                                      const auto &[while_stat, repeat_stat] = std::tie(pm[loop_loc], pm[loop_loc - 1u]);
                                                      if (pm.is_safe(while_stat) && tools::stat::branch::is_while_true(while_stat) && tools::stat::is_repeat(repeat_stat)) {

                                                            pm.remove(while_stat, loop_end, break_stat);
                                                            pm.mut(LURAMAS_DEBUG_LINE);
                                                      }
                                                }
                                          }
                                    }
                              }
                        }

                        /*
                            ::l::
                            if 
                               /.../
                               [ANY GOTO TO l];
                               /TERMINATOR/
                            /end/
                        */
                        if (basic_if && pm.valid_prev<1u>(i)) {

                              const auto &prev = pm[i - 1u];
                              const auto block_end = tools::common::safe_take_jump(pm, i);
                              const auto &prev_end = pm[block_end - 1u];
                              if (pm.is_safe(prev, prev_end) && tools::stat::is_label(prev) && prev_end->is_terminal() && tools::contains::refs(pm, {i, block_end}, prev->label)) {

                                    tools::stat::mutate::while_stat_cleared(p);
                                    for (const auto &goto_loc : tools::accumulate::keyword<keywords::goto_label>(pm, i, block_end)) {

                                          const auto &gstat = pm[goto_loc];
                                          if (tools::stat::branch::is_goto_label(gstat, prev) && pm.safe(gstat)) {
                                                tools::stat::mutate::continue_stat_cleared(gstat);
                                          }
                                    }
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        /*
                            if (??) then
                            ...
                            end
                            [TRACES TO LOOP END]                   
                        */
                        const auto end = tools::common::safe_take_jump(pm, i);
                        if (const auto loop_end = tools::common::traces_to_loop_end(pm, end); loop_end && pm.is_safe(p, pm[loop_end])) {

                              const auto blocks = tools::extract::blocks(pm, i);
                              if (blocks.size() > 1u) {
                                    for (const auto &[start, end] : blocks) {

                                          auto &cond = pm[start];
                                          auto &cond_end = pm[end];

                                          if (tools::stat::branch::is_else_cond(cond)) {
                                                pm.remove(cond, cond_end);
                                          } else if (tools::stat::branch::is_cond(cond)) {
                                                tools::stat::mutate::if_stat_cleared(cond);
                                                pm.insert(cond_end, tools::stat::generate::continue_stat(), tools::stat::generate::end());
                                          }
                                          pm.set_safe(cond, cond_end);
                                    }
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        /*
                           if  (??) then [SIMPLE IF]
                                   [NO BREAK, CONTINUE]
                                   ...
                           end
                           [SAFE ENDS]
                           break
                        */
                        if (pm.is_safe(p) && basic_if && !pm[i + 1u]->is_implicit_flow_interrupt()) {

                              const auto end = tools::common::safe_take_jump(pm, i);
                              if (tools::stat::is_break(tools::visitors::next_safe_executable_stat(pm, end))) {

                                    tools::stat::mutate::if_stat_cleared<true>(p);
                                    pm.insert(p, tools::stat::generate::break_stat());
                                    pm.move(pm[end], {i + 1u, end});
                                    pm.set_safe(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
      }
      return;
}

void luramas::ir::passes::branch_redirection(pass_manager &pm, shared &s) {

      for (const auto &i : pm.ir.data) {

            if (i->jlabel) {

                  const auto lab = pm.processed.labels[i->jlabel];
                  if (pm.valid_next<1u>(lab)) {

                        const auto &next = pm[lab + 1u];
                        if (next->is_k<keywords::goto_label>() && pm.safe(i)) {
                              i->jlabel = next->jlabel;
                        }
                  }
            }
      }
      return;
}

void luramas::ir::passes::branch_threading(pass_manager &pm, shared &s) {

      for (auto i = 0u; i < pm.amount(); ++i) {

            auto &p = pm[i];
            switch (p->k) {
                  case keywords::condition_goto: {

                        const auto label_loc = pm.processed.labels[p->jlabel];

                        /*
                                 if (??) then goto l end; [ONE REF]
                                 ....
                                 [TERMINATOR];
                                 ::l::
                                 [GET VALIDITY TO COND ESCAPE]
                        */
                        if (tools::stat::future(i, label_loc) && pm.processed.jlabels_refs[p->jlabel].size() == 1u && pm.valid_prev<1u>(label_loc) && pm[label_loc - 1u]->is_terminator()) {

                              const auto valid = tools::stack_validate(pm, label_loc, pm.amount());
                              if ((valid.reason == tools::cond_stack_reason::closing || valid.reason == tools::cond_stack_reason::nothing) && pm.is_safe(label_loc, valid.closing_index)) {

                                    const auto goto_loc = tools::next_valid_jump(pm);

                                    tools::stat::mutate::if_stat_cleared(p);
                                    pm.move(p, {label_loc, valid.closing_index - 1u});
                                    pm.insert(p, tools::stat::generate::goto_label(goto_loc), pm[valid.closing_index - 1u]->clone(), tools::stat::generate::end());
                                    pm.insert(tools::visitors::last_safe_end_stat(pm, valid.closing_index), tools::stat::generate::label(goto_loc));
                                    pm.set_safe(label_loc, valid.closing_index);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::condition: {

                        const auto basic_if = tools::common::basic_if_stat(pm, i);

                        /* 
                           if  (??) then [SIMPLE IF]
                               ...
                               [ANY GOTOS AFTER THE NEXT INSTRUCTION OF END]
                               ...
                               [TERMINAL];
                           end
                           [NONE OF THE LABELS IN THE CONDITION BLOCK]
                        */
                        if (pm.is_safe(p) && basic_if) {

                              if (const auto end = tools::common::safe_take_jump(pm, i);
                                  pm.valid_next<1u>(end) && pm.valid_prev<1u>(end) && pm[end - 1u]->is_terminal() && pm.is_safe(pm[end])) {

                                    const auto next = pm[end + 1u];
                                    const auto gotos = tools::accumulate::keyword(pm, i, end, keywords::condition_goto, keywords::goto_label);

                                    auto base_end = pm.amount();
                                    for (const auto &g : gotos) {
                                          if (const auto jmp = tools::common::safe_take_jump(pm, g); jmp > end + 1u && base_end > jmp) {
                                                base_end = jmp;
                                          }
                                    }

                                    if (std::any_of(gotos.begin(), gotos.end(), [&](const auto &g) { return tools::common::safe_take_jump(pm, g) > end + 1u; }) &&
                                        (!tools::stat::is_label(next) || std::none_of(gotos.begin(), gotos.end(), [&](const auto &g) { return tools::common::safe_take_jump(pm, g) == end + 1u; }))) {

                                          if (auto block_end = tools::violations::block_violates(pm, end + 1u, base_end).ending_loc;
                                              block_end != end + 1u && block_end - 1u != end) {

                                                auto end_lab = (block_end - 1u);
                                                end_lab += !pm[end_lab]->is_goto_label();

                                                pm.insert(pm[end], tools::stat::generate::else_stat());
                                                pm.insert_front(end_lab, tools::stat::generate::end());
                                                pm.remove(pm[end]);
                                                pm.set_safe(p);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
      }
      return;
}