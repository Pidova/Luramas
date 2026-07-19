#include "../includes/common.hpp"

namespace luramas::ir::passes {

      void dead_code_elimination(pass_manager &pm, shared &s) {

            std::optional<generation::ssa::ssa> ssa;
            for (const auto &i : pm.iter()) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::condition_goto: {

                              /*
                    	         if (?) then goto l end
                                 [ends]
                                 ::l::
                              */
                              if (pm.valid_next<2u>(i)) {

                                    const auto &executable = tools::visitors::next_safe_executable_stat(pm, i + 1u);
                                    if (tools::stat::branch::is_cond_goto_label(p, executable) && pm.safe(p)) {

                                          for (const auto &v : tools::stat::mutate::extract_volatiles_stats(p)) {
                                                pm.insert(p, v);
                                          }
                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        case keywords::goto_label: {

                              if (pm.valid_next<1u>(i)) {

                                    const auto &next = pm[i + 1u];

                                    /*
                                        goto l;
                                        /goto n;/
                                    */
                                    if (next->is_k<keywords::goto_label>() && pm.safe(next)) {
                                          pm.remove(next);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }

                                    /*
                                        goto l;
                                        end [NEXT SAFE EXECUTABLE]
                                        /::l::/
                                    */
                                    const auto &executable = tools::visitors::next_safe_executable_stat(pm, i + 1u);
                                    if (tools::stat::branch::is_goto_label(p, executable) && pm.safe(p)) {
                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }

                                    /*
                                        goto l;
                                        /::l::/
                                    */
                                    if (tools::stat::branch::is_goto_label(p, next) && pm.safe(p, next)) {
                                          pm.remove(p, next);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              if (pm.valid_prev<1u>(i)) {

                                    const auto &prev = pm[i - 1u];

                                    /*
                                        if (?) then goto l; end
                                        ::l::
                                     */
                                    if (tools::stat::branch::is_cond_goto_label(prev, p) && pm.safe(p)) {
                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        case keywords::assignment: {

                              /*
                                      = ??
                                    No Lvalues
                              */
                              if (p->l == nullptr && p->members.empty()) {
                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                                    break;
                              }

                              if (p->members.size() > 1u) {

                                    /*
                                            r(n), r(n1), ... = ?; (assignments only used once)
                                            ?(n) = r(n);
                                            ?(n1) = r(n1);
                                            ... = ...
                                    */
                                    luramas_registers regs;
                                    boost::unordered_flat_set<luramas_register> un_regs;
                                    for (const auto &i : p->members) {
                                          if (!i->is_k<expr_kinds::reg>() && !i->is_k<expr_kinds::upvalue>()) {
                                                break;
                                          }
                                          regs.emplace_back(i->reg);
                                          un_regs.insert(regs.back());
                                    }

                                    bool pass = true;
                                    boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat>> assignments;
                                    for (auto g = i + 1u; g < pm.amount(); ++g) {
                                          const auto &s = pm[g];
                                          if (assignments.size() == regs.size()) {
                                                break;
                                          }
                                          if (!s->is_k<keywords::assignment>() || s->l == nullptr || s->r == nullptr || (!s->r->is_k<expr_kinds::reg>() && !s->r->is_k<expr_kinds::upvalue>())) {
                                                pass = false;
                                                break;
                                          }
                                          const auto reg = s->r->reg;
                                          if (assignments.find(reg) != assignments.end() || un_regs.find(reg) == un_regs.end()) {
                                                pass = false;
                                                break;
                                          } else {
                                                assignments.try_emplace(reg, s);
                                          }
                                    }
                                    if (pass && !assignments.empty()) {

                                          if (!ssa.has_value()) {
                                                ssa.emplace(generation::ssa::generate(pm.ir));
                                          }

                                          for (const auto &s : ssa->nodes[p].l.assigns) {
                                                const auto rssa = *s.second.second.begin();
                                                if (ssa->defs[rssa].second.second.first.size() > 1u || ssa->phis.find(rssa) != ssa->phis.end()) {
                                                      pass = false;
                                                      break;
                                                }
                                          }
                                          if (pass && pm.safe(p)) {

                                                for (auto idx = 0u; idx < p->members.size(); ++idx) {
                                                      p->members[idx] = assignments[p->members[idx]->reg]->l;
                                                }
                                                for (const auto &g : assignments) {
                                                      pm.remove(g.second);
                                                }
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                                    pass = true;

                                    /*
                                            r(n), r(n1), ... = ?; 
                                            (Deadstores after n will be eliminated, cancels if there is a deadstore next.)
                                    */
                                    if (regs.size() == p->members.size()) {

                                          if (!ssa.has_value()) {
                                                ssa.emplace(generation::ssa::generate(pm.ir));
                                          }
                                          bool checked = false;
                                          luramas_registers removals;
                                          auto &rssa = ssa->nodes[p];
                                          for (const auto &m : regs) {

                                                const auto &lssa = rssa.l.assigns[m];
                                                if (lssa.second.empty()) {
                                                      break;
                                                }
                                                const auto &rssa = *lssa.second.begin();
                                                if (ssa->defs.find(rssa) == ssa->defs.end() || ssa->phis.find(rssa) != ssa->phis.end()) {
                                                      pass = false;
                                                      break;
                                                }

                                                const auto &past = ssa->defs[rssa];
                                                if (past.second.second.first.size()) {
                                                      if (checked) {
                                                            pass = false;
                                                            break;
                                                      }
                                                } else {
                                                      if (!checked) {
                                                            checked = true;
                                                      }
                                                      removals.emplace_back(m);
                                                }
                                          }
                                          if (!pass || removals.empty()) {
                                                break;
                                          }

                                          std::shared_ptr<ir_stat::ir_expr> member = nullptr;
                                          do {
                                                member = nullptr;
                                                for (const auto &m : p->members) {
                                                      if (m->is_reg(removals.back())) {
                                                            member = m;
                                                            removals.pop_back();
                                                            break;
                                                      }
                                                }
                                                if (member) {
                                                      p->members.erase(std::remove(p->members.begin(), p->members.end(), member));
                                                }
                                          } while (!removals.empty() && member);
                                          if (p->members.size() == 1u) {
                                                p->l = p->members.front();
                                                p->members.clear();
                                          }
                                    }
                              } else {

                                    /*
                                        r = r
                                    */
                                    if (!p->flags.finternal_store && p->l && p->r && *p->l == *p->r) {
                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              if (!tools::stat::assignment::is_lvalues(p) && tools::stat::assignment::is_rvalue(p)) {
                                    for (const auto &v : tools::stat::mutate::extract_volatiles_stats(p)) {
                                          pm.insert(p, v);
                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        case keywords::forloop_generic: {

                              /*
                                 for r in ?, nil, nil
                              */
                              p->smembers.erase(std::remove_if(p->smembers.begin(), p->smembers.end(), [](const auto &o) { return o->template is_tk<tkind::none_obj>(); }), p->smembers.end());

                              /* TODO: PERABLY DO IT IF ANY MEMBER HAS ANY META DATA THAT CAN BE INLINED */
                              if (pm.valid_prev<1u>(i)) {

                                    /*
                                        r(n), r = ?? (ALL IS META)
                                        for ? in r do 
                                    */
                                    const auto &prev = pm[i - 1u];
                                    if (!p->meta.empty() && prev->is_k<keywords::assignment>() && pm.safe(prev) && !prev->members.empty()) {

                                          if (!ssa.has_value()) {
                                                ssa.emplace(generation::ssa::generate(pm.ir));
                                          }

                                          ir_stat::ir_expr::space targets;
                                          for (const auto &s : ssa->nodes[prev].l.assigns) {
                                                if (!ssa->defs[*s.second.second.begin()].second.second.first.size()) {
                                                      const auto expr = *prev->visit(s.first).begin();
                                                      if (std::find(p->meta.begin(), p->meta.end(), expr) != p->meta.end()) {
                                                            targets.emplace_back(expr);
                                                      }
                                                }
                                          }
                                          for (const auto &t : targets) {
                                                auto it = std::remove(prev->members.begin(), prev->members.end(), t);
                                                if (it != prev->members.end()) {
                                                      prev->members.erase(it);
                                                }
                                                it = std::remove(p->meta.begin(), p->meta.end(), t);
                                                if (it != p->meta.end()) {
                                                      p->meta.erase(it);
                                                }
                                          }
                                    }
                              }
                              break;
                        }
                        case keywords::end: {

                              if (pm.valid_prev<1u>(i)) {

                                    const auto &prev = pm[i - 1u];

                                    /*
                                         if (?) then
                                         end
                                    */
                                    if (tools::stat::branch::is_if_cond(prev) && pm.safe(p, prev)) {

                                          for (const auto &v : tools::stat::mutate::extract_volatiles_stats(prev)) {
                                                pm.insert(prev, v);
                                          }
                                          pm.remove(p, prev);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        case keywords::condition: {

                              if (pm.valid_next<1u>(i)) {

                                    const auto &next = pm[i + 1u];

                                    /*
                                        else
                                        /end/
                                    */
                                    if (tools::stat::branch::is_stat_else_end(p, next) && pm.safe(p)) {
                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }

                                    /*
                                        else
                                        /else/                         
                                    */
                                    if (tools::stat::branch::is_else_cond(p) && tools::stat::branch::is_else_cond(next) && pm.safe(p)) {
                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }

                                    /*
                                        if (??)
                                        else
                                    */
                                    if (tools::stat::branch::is_if_cond(p) && tools::stat::branch::is_else_cond(next) && pm.safe(p, next)) {

                                          tools::stat::mutate::if_stat_cleared<true>(p);
                                          pm.remove(next);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }

                                    /*
                                            if (false) then
                                                /.../
                                            /end/
                                    */
                                    if (tools::stat::branch::is_if_cond(p) && !tools::stat::branch::equality(p) && p->l && p->l->is_tk<tkind::boolean>() && p->l->bv == (p->b == il::arch::data::bin_kinds::nt_)) {

                                          pm.remove(tools::block::orphaned(pm, tools::transform::address_to_range(i, pm.processed.end_labels[p->end_label].second)));
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        case keywords::label: {

                              if (pm.valid_next<1u>(i)) {

                                    const auto &next = pm[i + 1u];

                                    /*
                                        ::l::
                                        /::l2::/
                                    */
                                    if (tools::stat::is_label(next) && pm.safe(p, next)) {

                                          for (auto j = 0ull; j < pm.amount(); ++j) {

                                                auto &jp = pm[j];
                                                if (tools::stat::common::is_ref(jp, next->label)) {
                                                      jp->jlabel = p->label;
                                                }
                                          }
                                          pm.remove(next);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        case keywords::retn: {

                              if (pm.valid_prev<3u>(i)) {

                                    const auto &[p1, p2, p3] = std::tie(pm[i - 1u], pm[i - 2u], pm[i - 3u]);

                                    /*
                                         if (??) then NO VOLATILES
                                            return;
                                         end
                                         return;
                                    */
                                    if (pm.is_safe(p, p1, p2, p3) && tools::stat::branch::is_if_end(p3, p1) && tools::stat::common::same_returns(p, p2) && !tools::exprs::mutate::cmp_extract(p3)->contains_volatile()) {

                                          pm.set_safe(p, p1, p2, p3);
                                          pm.remove(p1, p2, p3);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        case keywords::continue_: {

                              if (pm.valid_next<1u>(i)) {

                                    const auto &next = pm[i + 1u];

                                    /*
                                        continue;
                                        [ends]
                                        end of loop
                                    */
                                    if (next->is_scope_end()) {

                                          bool hit = false;
                                          tools::visitors::last_safe_end(pm, i + 1u, hit);
                                          if (hit && pm.safe(p)) {
                                                pm.remove(p);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }

                                    /*
                                            continue;
                                            /continue;/
                                    */
                                    if (tools::stat::is_continue(next) && pm.safe(next)) {

                                          pm.remove(next);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }

                                    /*
                                            continue;
                                            /break;/
                                    */
                                    if (tools::stat::is_break(next) && pm.safe(next)) {

                                          pm.remove(next);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              if (pm.valid_prev<1u>(i) && pm.valid_next<2u>(i)) {

                                    const auto &[p1, n1, n2] = std::tie(pm[i - 1u], pm[i + 1u], pm[i + 2u]);

                                    /*
                                         l:
                                             continue;
                                         /l2:/
                                         /[End of loop]/
                                    */
                                    if (tools::stat::is_label(p1) && tools::stat::is_label(n1) && tools::stat::branch::is_loop_end(pm, n2, true)) {

                                          for (const auto &r : tools::accumulate::refs(pm, pm.range(), p1->label)) {
                                                pm[r]->jlabel = n1->label;
                                          }
                                          pm.remove(p1, p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        case keywords::break_: {

                              if (pm.valid_next<1u>(i)) {

                                    const auto &next = pm[i + 1u];

                                    /*
                                            break;
                                            /break;/
                                     */
                                    if (tools::stat::is_break(next) && pm.safe(next)) {

                                          pm.remove(next);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }

                                    /*
                                        break;
                                        /continue;/
                                     */
                                    if (tools::stat::is_continue(next) && pm.safe(next)) {

                                          pm.remove(next);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        case keywords::call: {

                              /* 
                                     (function (..)
                                         return ?; [INDEPENDANT]
                                     end)()  (NO VOLATILES)
                                */
                              if (tools::stat::is_anonfunction_call(p)) {

                                    const auto closure = p->l;
                                    if (closure->closure.size() == 2u &&
                                        tools::block::independent(closure->closure) &&
                                        !tools::contains::is(p->members, luramas::ir::data::volatile_)) {

                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        case keywords::bitwrite: {

                              /* bitwrite(x, bitread<???>(x, n1, n2), [n1, n2]) */
                              if (tools::exprs::basic::is_integral(p->v, p->lba) && tools::exprs::values::is_bitread(p->r) && tools::exprs::basic::is_integral(p->r->r, p->r->ev) &&
                                  p->v->n == p->r->r->n && p->lba->n == p->r->ev->n && p->l && p->r->l && *p->l == *p->r->l) {

                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              break;
                        }
                        case keywords::page_function_goto: {

                              if (tools::stat::is_page_function_jump(p)) {

                                    if (pm.valid_next<1u>(i)) {

                                          const auto &n = pm[i + 1u];

                                          if (pm.env_flags.fallow_page_falls) {

                                                /* 
									                page jump[n]
                                                    /page start[n]/                    
                                                */
                                                if (tools::stat::is_page_function_start(n, p->r->extract_integral_base()) && pm.safe(p)) {
                                                      if (const auto it = pm.processed.pages.find(p->r->extract_integral_base()); it != pm.processed.pages.end()) {
                                                            if (const auto &def = pm[it->second.first + 1u]; tools::stat::is_definition(def)) {

                                                                  for (auto i = 0u; i < def->args.size(); ++i) {
                                                                        if (i > p->members.size()) {
                                                                              break;
                                                                        }
                                                                        auto arg = def->args.begin();
                                                                        std::advance(arg, i);
                                                                        pm.insert(p, tools::stat::generate::assignment(arg->second, p->members[i]));
                                                                  }
                                                            }
                                                      }
                                                      pm.remove(p);
                                                      pm.mut(LURAMAS_DEBUG_LINE);
                                                }
                                          }

                                          /* 
									        page jump[n]
                                            /page jump[n]/                       
                                          */
                                          if (tools::stat::is_page_function_jump(n)) {
                                                pm.remove(n);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                              break;
                        }
                        case keywords::stack_push: {

                              /* SPUSH([?], {NO VALUES}) */
                              if (p->members.empty()) {
                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              if (pm.valid_next<1u>(i)) {

                                    const auto &n = pm[i + 1u];

                                    /* 
									    SPUSH([n], {?? (NO STACK)});
                                        SPOP([n], {?? (NO STACK)});                  
                                    */
                                    if (tools::stat::is_stack_pop(n, p->v->extract_integral()) && pm.is_safe(p, n)) {

                                          const auto id = p->v->extract_integral();
                                          const tools::find::find_expr_cb f = [&](const std::shared_ptr<ir_stat::ir_expr> &expr) { return expr->is_tk<tkind::stack>() && expr->n == id; };

                                          for (auto it = n->members.begin(); it != n->members.end();) {

                                                const auto &e = *it;
                                                if (tools::find::expr(e, f)) {
                                                      continue;
                                                }

                                                if (const auto rit = std::find_if(p->members.rbegin(), p->members.rend(), [&](const auto &m) { return *e == *m; }); rit != p->members.rend()) {
                                                      p->members.erase(std::prev(rit.base()));
                                                      it = n->members.erase(it);
                                                      pm.set_safe(p, n);
                                                      pm.mut(LURAMAS_DEBUG_LINE);
                                                } else {
                                                      ++it;
                                                }
                                          }
                                    }
                              }
                              break;
                        }
                        case keywords::stack_pop: {

                              /* SPOP([?], {NO VALUES}) */
                              if (p->members.empty()) {
                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              break;
                        }
                        case keywords::memoryset: {

                              const tools::find::find_expr_cb has_memread = [](const std::shared_ptr<ir_stat::ir_expr> &expr) { return expr->is_k<expr_kinds::memoryread>(); };

                              if (pm.valid_next<1u>(i)) {

                                    const auto &n = pm[i + 1u];

                                    /* 
                                        memset<i>(??) = ?
                                        memset<i>(??) = ?           
                                        NO MEMREADS
                                    */
                                    if (pm.is_safe(n, p) && tools::stat::is_memoryset(n, p->l, p->v, p->extra_bits) && !p->r->contains_volatile() && !n->r->contains_volatile() && !tools::find::expr(has_memread, p->l, p->v, p->r, n->l, n->v, n->r)) {
                                          pm.remove(p);
                                          pm.set_safe(p, n);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              if (pm.env_flags.fmemory_assign_safe) {

                                    /* memset<T>(??) = memread<T>(??) */
                                    // if (pm.is_safe(p) && ) {
                                    //       pm.remove(p);
                                    //       pm.mut(LURAMAS_DEBUG_LINE);
                                    // }
                              }
                              break;
                        }
                        case keywords::definition: {

                              /* args.size() < casts.size() */
                              if (p->args.size() < p->meta.size()) {
                                    p->meta.resize(p->args.size());
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

      void dead_label_elimination(pass_manager &pm, shared &s) {

            boost::unordered_flat_set<luramas_address> refs;
            ir_stat::space labels;
            for (const auto &p : pm.ir.data) {
                  if (tools::stat::branch::is_jump(p)) {
                        refs.insert(p->jlabel);
                  }
                  switch (p->k) {
                        case keywords::label: {
                              labels.emplace_back(p);
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }

            for (const auto &i : labels) {

                  /*
                        (No jumps to it)
                        l: 
                  */
                  if (refs.find(i->label) == refs.end()) {
                        pm.remove(i);
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
            }
            return;
      }

      void unreachable_code_elimination(pass_manager &pm, shared &s) {

            std::optional<tools::paging::details> page_details = std::nullopt;
            if (pm.env_flags.fhas_pages) {
                  page_details = tools::paging::gen_details(pm);
            }

            const auto cfg = generation::cfg::generate(pm.ir, LURAMAS_IR_ENTRY, pm.env_flags.fhas_pages);
            for (const auto &i : pm.iter()) {
                  const auto &stat = pm[i];
                  if (!cfg.interacted_nodes.contains(i)) {
                        if (stat->is_scope_end() && cfg.interacted_nodes.contains(tools::common::reverse_safe_take_jump(pm, i))) {
                              continue;
                        }
                        pm.force_mutable_safe(stat);
                        if (pm.safe(stat)) {
                              pm.remove(stat);
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                  } else if (tools::stat::is_page_function_end(stat) && page_details) {
                        if (const auto &page = (*page_details).pages[nullptr][stat->r->extract_integral_base()]; page.fhas_start && !cfg.interacted_nodes.contains(page.range.first)) {
                              pm.force_mutable_safe(stat);
                              pm.remove(stat, pm[page.range.first], page.definition);
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                  }
                  if (tools::stat::branch::is_else_conditional(stat) && pm.is_removed(pm[tools::common::reverse_safe_take_jump(pm, i)])) {
                        pm.remove(i, tools::common::safe_take_jump(pm, i) + 1u);
                        pm.mut(LURAMAS_DEBUG_LINE);
                  } else if (tools::stat::is_end(stat) && pm.is_removed(pm[tools::common::reverse_safe_take_jump(pm, i)])) {
                        pm.remove(stat);
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
            }
            return;
      }

      void psuedo_instruction_elimination(pass_manager &pm, shared &s) {

            for (const auto &i : pm.iter()) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::create_stack: {

                              pm.remove(p);
                              pm.mut(LURAMAS_DEBUG_LINE);
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
            return;
      }

      void dead_main_definition_elimination(pass_manager &pm, shared &s, generation::ssa::ssa &ssa) {

            std::vector<luramas_index> args;

            /* Remove */
            const auto &def = pm[0u];
            if (tools::stat::is_definition(def) && def->flags.flink_regs) {

                  for (const auto &[linked, data] : ssa.nodes[def].l.assigns) {

                        if (ssa.defs[(*data.second.begin())].second.second.first.empty()) {

                              if (const auto it = def->args.find(linked); it != def->args.end()) {

                                    const auto idx = static_cast<std::size_t>(std::distance(def->args.begin(), it));
                                    args.emplace_back(idx);
                                    def->args.erase(it);
                                    if (idx < def->meta.size()) {
                                          def->meta.erase(def->meta.begin() + idx);
                                    }
                              }
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                  }
            }
            return;
      }
} // namespace luramas::ir::passes