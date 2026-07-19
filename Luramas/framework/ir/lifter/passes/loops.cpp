#include "includes/common.hpp"

void luramas::ir::passes::loop_simplification(pass_manager &pm, shared &s) {

      for (auto i = pm.amount() - 1u; i > 0ull; --i) {

            auto &p = pm[i];
            switch (p->k) {
                  case keywords::condition_goto: {

                        if (pm.valid_prev<1u>(i)) {

                              const auto label = pm.processed.labels[p->jlabel];
                              if (tools::stat::past(i, label) && pm.valid_next<1u>(label)) {

                                    const auto &label_stat = pm[label];
                                    auto unfinished = tools::trackers::unfinished_condition(pm, label, i);

                                    /*
                                             ::l::
                                            (NOT LOOP)
                                            [VALID BLOCK]
                                            ..
                                            if  ?? then goto(l) end
                                     */
                                    if (tools::violations::block_violates(pm, label, i).valid && !std::any_of(unfinished.begin(), unfinished.end(), [](const auto &c) { return c.second->is_loop(); }) && pm.safe(p, label_stat)) {

                                          /*
                                                ::l::
                                                if (...) then [SIMPLE IF]
                                                    ...
                                                    if  ?? then goto(l) end
                                                \end\                                      
                                          */
                                          bool loop_while = false;
                                          if (pm.valid_next<1u>(label) && pm.valid_next<1u>(i) &&
                                              tools::stat::branch::is_if_end(pm[label + 1u], pm[i + 1u]) &&
                                              tools::common::basic_if_stat(pm, label + 1u)) {

                                                tools::stat::mutate::while_stat_cleared(pm[label + 1u]);
                                          } else {

                                                loop_while = true;
                                                pm.insert_front(tools::trackers::next_safe_executable(pm, label), tools::stat::generate::while_stat(tools::exprs::generate::boolean(true)));
                                          }
                                          tools::stat::mutate::if_stat_cleared<true>(p);
                                          pm.insert(p, tools::stat::generate::break_stat(), tools::stat::generate::end());
                                          if (loop_while) {
                                                pm.insert(p, tools::stat::generate::end());
                                          }
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }

                                    /*
                                             ::l::
                                            (LOOP)
                                            [UNFINISHED WHILE(TRUE)]
                                            ..
                                            if  ?? then goto(l) end
                                     */
                                    if (pm.valid_next<2u>(label) && pm[label + 1u]->is_loop()) {

                                          luramas_flag floop = false;
                                          std::pair<std::size_t, std::shared_ptr<ir_stat>> cond = {0u, nullptr};
                                          unfinished = tools::trackers::unfinished_condition(pm, label + 2u, i);
                                          if (std::all_of(unfinished.rbegin(), unfinished.rend(), [&](const auto &c) {
                                                    if (!floop) {
                                                          floop = c.second->is_loop();
                                                    }
                                                    if (floop) {
                                                          const auto no_cond_loop = tools::stat::branch::is_while_true(c.second);
                                                          if (!cond.second && !no_cond_loop) {
                                                                cond = c;
                                                                return true;
                                                          } else if (cond.second) {
                                                                return no_cond_loop && c.first == --cond.first;
                                                          }
                                                          return no_cond_loop;
                                                    }
                                                    return true;
                                              }) &&
                                              floop && pm.safe(p)) {

                                                /* Propagate continues */
                                                //for (const auto &[idx, stat] : unfinished) {
                                                //
                                                //      if (stat->is_loop() && (tools::stat::branch::is_while_true(stat) || stat == cond.second) && !tools::stat::is_continue(tools::visitors::next(pm, pm.processed.end_labels[stat->end_label].second)) && pm.safe(stat)) {
                                                //            pm.insert(pm[pm.processed.end_labels[stat->end_label].second], tools::stat::generate::continue_stat());
                                                //            pm.mut(LURAMAS_DEBUG_LINE);
                                                //      }
                                                //}

                                                tools::stat::mutate::if_stat_cleared(p);
                                                pm.insert(p, tools::stat::generate::break_stat(), tools::stat::generate::end());
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

      for (auto i = 0ull; i < pm.amount(); ++i) {

            auto &p = pm[i];
            switch (p->k) {
                  case keywords::condition: {

                        if (pm.valid_prev<1u>(i)) {

                              const auto end = pm.processed.end_labels[p->end_label].second;
                              if (pm.valid_prev<1u>(end)) {

                                    const auto &[prev, pm_goto] = std::tie(pm[i - 1u], pm[end - 1u]);

                                    /*
                                        ::l::
                                        if  (??) then [BASIC STAT]
                                        /.../
                                        /goto 1/
                                        /end/
                                    */
                                    if (pm.is_safe(p, pm_goto) && tools::common::basic_if_stat(pm, i) && tools::stat::branch::is_goto_label(pm_goto, prev)) {

                                          tools::stat::mutate::while_stat_cleared(p);
                                          pm.set_safe(p, pm_goto);
                                          pm.remove(pm_goto);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }

                        if (pm.valid_next<3u>(i) && pm.valid_prev<1u>(i)) {

                              const auto &[n1, n2, n3] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u]);

                              /*
                                while (true)
                                         ...
                                         if (??) then
                                             break;
                                         end
                                 end
                              */
                              if (tools::stat::branch::is_if_end(p, n2) && tools::stat::is_break(n1) && tools::stat::is_end(n3)) {

                                    const auto &cond = pm[pm.processed.end_labels[n3->end_label].first];
                                    if (tools::stat::branch::is_while_true(cond)) {

                                          tools::stat::mutate::until_stat_cleared(p);
                                          pm.insert(cond, tools::stat::generate::repeat());
                                          pm.remove(cond, n1, n2, n3);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }
                        break;
                  }
                  case keywords::repeat: {

                        const auto until_pos = pm.processed.end_labels[p->end_label].second;
                        auto &until_stat = pm[until_pos];

                        if (pm.valid_next<3u>(i)) {

                              const auto &[n1, n2, n3] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u]);

                              /*
                                 repeat
                                 	    if  (??) then
                                 	    	break;
                                 	    end
                                 	    ...
                                 until (??)
                              */
                              if (tools::stat::branch::is_if_end(n1, n3) && n2->is_k<keywords::break_>() && pm.safe(p, n1, n2, n3, until_stat)) {

                                    tools::stat::mutate::while_stat_cleared<true>(n1);
                                    tools::stat::mutate::if_stat_cleared<true>(until_stat);
                                    pm.insert(pm[until_pos - 1u], until_stat, tools::stat::generate::break_stat(), tools::stat::generate::end(), tools::stat::generate::end());
                                    pm.remove(p, n2, n3, until_stat);
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

void luramas::ir::passes::loop_winding(pass_manager &pm, shared &s) {

      for (auto i = pm.amount(); i > 0; --i) {

            auto &p = pm[i - 1u];
            switch (p->k) {
                  case keywords::goto_label: {

                        const auto label = pm.processed.labels[p->jlabel];
                        const auto &p_label = pm[label];

                        if (pm.valid_next<1u>(i)) {

                              /*
                                          goto l;
                                        /[NEXT SAFE EXECUTABLE]/
                                        /goto l;/                     
                              */
                              const auto next_safe = pm[tools::trackers::next_safe_executable(pm, i, {keywords::label}, false, tools::common::safe_take_jump(pm, i))];
                              if (tools::stat::branch::same_goto(p, next_safe)) {
                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        /*
                             l:
                             ...
                             goto l;
                        */
                        if (pm.is_safe(p_label) && tools::stat::past(i, label)) {

                              const auto unfinished = tools::trackers::unfinished_condition(pm, label, i);
                              if (!unfinished.empty()) {
                                    if (!std::any_of(unfinished.begin(), unfinished.end(), [](const auto &c) { return c.second->is_loop(); })) {

                                          bool pass = true;
                                          boost::unordered_flat_set<luramas_address> end_labels;
                                          boost::unordered_flat_set<std::shared_ptr<ir_stat>> goto_mutate;
                                          for (const auto &u : unfinished) {
                                                if (u.second->end_label) {
                                                      const auto end_label = pm.processed.end_labels[u.second->end_label].second;
                                                      const auto &goto_stat = tools::visitors::prev_executable_stat(pm, end_label);
                                                      if (tools::stat::branch::same_goto(p, goto_stat)) {
                                                            end_labels.insert(end_label);
                                                            goto_mutate.insert(goto_stat);
                                                            continue;
                                                      }
                                                }
                                                pass = false;
                                                break;
                                          }
                                          if (pass) {

                                                const auto jump_out_labels = tools::accumulate::goto_labels(pm, tools::accumulate::explicit_jump_past(pm, label, i));
                                                const auto most_valid = tools::truncate::most_relative_valid_block(pm, label, jump_out_labels);

                                                auto last_end = i - 1u;
                                                if (last_end < most_valid) {
                                                      last_end = most_valid - 1u;
                                                }
                                                for (const auto &end : end_labels) {
                                                      last_end = std::max(last_end, end);
                                                }
                                                for (auto &i : goto_mutate) {
                                                      if (pm.safe(i)) {
                                                            tools::stat::mutate::continue_stat_cleared(i);
                                                      }
                                                }

                                                tools::stat::mutate::continue_stat_cleared(p);
                                                pm.insert(p_label, tools::stat::generate::while_stat(tools::exprs::generate::boolean(true)));
                                                pm.insert(pm[last_end], tools::stat::generate::break_stat(), tools::stat::generate::end());
                                                pm.set_safe(p_label);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              } else {

                                    /* VALID BLOCK LABEL -> GOTO LABEL; */
                                    if (tools::violations::block_violates(pm, label, i).valid) {

                                          pm.insert(p_label, tools::stat::generate::while_stat(tools::exprs::generate::boolean(true)));
                                          pm.insert(p, tools::stat::generate::end());
                                          pm.remove(p);
                                          pm.set_safe(p_label);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }
                        break;
                  }
                  case keywords::condition_goto: {

                        const auto label = tools::common::safe_take_jump(pm, i - 1u);

                        /*
                            ::l::
                            (NO CONTIUES, BREAKS) [
                                [ANY BASIC contiguous IF CONDS]
                                if (x) then [BASIC IF]
                                ...    
                                if (?) then goto l end
                                /end/
                                ...
                                /end/ [OPTIONAL REPEAT]
                            ]
                        */
                        if (pm.is_safe(p, pm[label])) {

                              bool hit = false;
                              const auto last_end = tools::visitors::last_safe_end(pm, i, hit);
                              if (!hit && last_end != i) {

                                    const auto violation = tools::violations::block_violates(pm, label, last_end + 1u);
                                    if (tools::treshold_ei(violation.ending_loc, i, last_end) && !tools::contains::orphans::implicit_goto(pm, tools::transform::address_to_range(label, violation.ending_loc)) &&
                                        tools::common::basic_if_end_stat(pm, tools::transform::address_to_range(i, violation.ending_loc))) {

                                          pm.insert(pm[label], tools::stat::generate::repeat());
                                          for (auto o = i; o < violation.ending_loc; ++o) {
                                                const auto &if_stat = pm[tools::common::reverse_safe_take_jump(pm, o)];
                                                pm.remove(pm[o]);
                                                pm.insert(if_stat, tools::stat::generate::break_stat(), tools::stat::generate::end());
                                                pm.set_safe(if_stat);
                                          }
                                          tools::stat::mutate::until_stat_cleared(p);
                                          pm.move(pm[violation.ending_loc - 1u], p);
                                          pm.set_safe(pm[label], p);
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

void luramas::ir::passes::loop_unroll(pass_manager &pm, shared &s) {

      for (auto i = 0ull; i < pm.amount(); ++i) {

            auto &p = pm[i];
            switch (p->k) {
                  case keywords::goto_label: {

                        if (pm.valid_next<4u>(i)) {

                              const auto &[n1, n2, n3, n4] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u]);

                              /*
                                    goto l;
                                    /repeat/
                                        /break;/
                                        /::l::/
                                    /until (??)/
                              */
                              if (tools::stat::branch::is_repeat_until(n1, n4) && tools::stat::is_break(n2) && tools::stat::branch::is_goto_label(p, n3) && pm.safe(p, n1, n2, n3, n4)) {

                                    pm.insert(p, tools::stat::generate::cond(n4->l, n4->b, n4->r), tools::stat::generate::end());
                                    pm.remove(p, n1, n2, n4);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                    goto l;
                                    /while(??)/
                                        /break;/
                                        /::l::/
                                    /end/
                              */
                              if (tools::stat::branch::is_while_end(n1, n4) && tools::stat::is_break(n2) && tools::stat::branch::is_goto_label(p, n3) && pm.safe(p, n1, n2, n3, n4)) {

                                    pm.insert(p, tools::stat::generate::cond(n1->l, n1->b, n1->r), tools::stat::generate::end());
                                    pm.remove(p, n1, n2, n4);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::repeat: {

                        if (pm.valid_next<1u>(i)) {

                              const auto &next = pm[i + 1u];

                              /*
                                repeat
                                until(??)
                              */
                              if (tools::stat::is_until(next)) {

                                    tools::stat::mutate::while_stat_cleared<true>(next);

                                    pm.remove(p);
                                    pm.insert(next, tools::stat::generate::end());
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

void luramas::ir::passes::loop_canonicalize_exits(pass_manager &pm, shared &s) {

      for (const auto &i : pm.iter()) {

            auto &p = pm[i];
            switch (p->k) {
                  case keywords::while_: {

                        /*
                            while (true) do 
                             /SINGLE BREAK OUT (COND GOTO/GOTO);/
                            /end/
                            /[TRACE NEXT SAFE EXECUTABLE]/
                            /(END OF IF/ELSEIF COND)/
                            /[END OF SAFE BLOCK]/
                            /::l::/
                        */
                        if (tools::stat::branch::is_while_true(p)) {

                              const auto break_outs = tools::accumulate::break_outs(pm, i);
                              if (break_outs.size() == 1u && (tools::stat::branch::is_goto(pm[break_outs.front()]) || tools::stat::branch::is_cond_goto(pm[break_outs.front()]))) {

                                    auto &breakout = pm[break_outs.front()];
                                    const auto end = tools::common::safe_take_jump(pm, i);
                                    const auto next_executable = tools::trackers::next_safe_executable(pm, end + 1u);
                                    const auto safe_cond = tools::common::reverse_safe_take_jump(pm, next_executable - 1u);
                                    if (tools::stat::branch::is_if_cond(pm[safe_cond]) && !tools::condition_has_else(pm, safe_cond, next_executable - 1u) && pm.is_safe(pm[safe_cond])) {

                                          const auto violation = tools::violations::block_violates(pm, next_executable, pm.amount());
                                          if ((violation.reason == tools::violations::block_violation_exceptions::invalid_end || violation.reason == tools::violations::block_violation_exceptions::invalid_else_conditional) &&
                                              tools::stat::branch::is_jlabel_target(pm[tools::trackers::next_safe_executable(pm, violation.ending_loc - 1u)], breakout)) {

                                                if (tools::stat::branch::is_goto(breakout)) {
                                                      pm.insert(breakout, tools::stat::generate::break_stat());
                                                      pm.remove(breakout);
                                                } else {
                                                      tools::stat::mutate::if_stat_cleared(breakout);
                                                      pm.insert(breakout, tools::stat::generate::break_stat(), tools::stat::generate::end());
                                                }
                                                pm.insert(pm[next_executable - 1u], tools::stat::generate::else_stat());
                                                pm.move(pm[violation.ending_loc - 1u], pm[next_executable - 1u]);
                                                pm.set_safe(pm[safe_cond]);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }
                        break;
                  }
                  case keywords::condition_goto: {

                        // const auto label = tools::common::safe_take_jump(pm, i);
                        // if (pm.is_safe(p)) {
                        //
                        //        auto violation = tools::violations::block_violates(pm, i + 1u, label, true, true);
                        //        if (!violation.valid &&
                        //            std::any_of(mutated.exceptions.begin(), mutated.exceptions.end(), [](const auto &o) { return o.reason == tools::violations::mutate_if_exceptions::invalid_loop_exit; }) &&
                        //            std::none_of(mutated.exceptions.begin(), mutated.exceptions.end(), [](const auto &o) { return o.reason == tools::violations::mutate_if_exceptions::invalid_unclosed_condition || o.reason == tools::violations::mutate_if_exceptions::invalid; })) {
                        //
                        //              if (mutated.exception_break) {
                        //
                        //                    // TODO: MAKE REST OF PASS
                        //                    for (const auto &e : mutated.mutable_synthetics) {
                        //                          pm.insert(p, tools::stat::generate::assignment(e, tools::exprs::generate::boolean(false)));
                        //                    }
                        //                    mutated.exceptions.pop_back();
                        //                    for (const auto &e : mutated.exceptions) {
                        //
                        //                          if (e.reason == tools::violations::mutate_if_exceptions::invalid_loop_exit && pm.safe(pm[e.closing_loc])) {
                        //                                auto flag = tools::stat::generate::flags::synthetic::flagable::pass_init_assign(pm);
                        //
                        //                                pm.insert(pm[tools::trackers::relative_scope(pm, e.closing_loc) - 1u], flag);
                        //                                pm.insert(pm[e.closing_loc], tools::stat::generate::flags::synthetic::flagable::cond(flag->l), tools::stat::generate::break_stat(), tools::stat::generate::end());
                        //                                pm.insert(p, tools::stat::generate::assignment(flag->l, tools::exprs::generate::boolean(true)));
                        //                          }
                        //                    }
                        //
                        //                    tools::stat::mutate::if_stat_cleared(p);
                        //                    pm.insert(p, tools::stat::generate::break_stat(), tools::stat::generate::end());
                        //              } else {
                        //                    tools::stat::mutate::if_stat_cleared<true>(p);
                        //                    pm.insert(pm[label_loc - 1u], tools::stat::generate::end());
                        //              }
                        //              pm.set_safe(p);
                        //              pm.mut(LURAMAS_DEBUG_LINE);
                        //        }
                        // }
                        break;
                  }
                  default: {
                        break;
                  }
            }
      }
      return;
}