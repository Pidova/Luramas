#include "../../constants.hpp"
#include "includes/common.hpp"
#include "patterns/foldables/compilables/compilables.hpp"
#include "patterns/foldables/if_condition/common.hpp"
#include "patterns/repeatables/repeatables.hpp"

void luramas::ir::passes::constant_fold(pass_manager &pm, shared &s) {

      for (auto i = 0ull; i < pm.amount(); ++i) {

            auto &p = pm[i];
            switch (p->k) {
                  case keywords::condition_goto: {

                        if (pm.valid_prev<1u>(i)) {

                              const auto &prev = pm[i - 1u];

                              /*
                                    if  (?) then
                                        if (?) then goto l; end
                                        /?/
                                    /end/
                                    /::l::/
                              */
                              if (prev->is_k<keywords::condition>() && tools::stat::branch::is_jlabel_target(pm[pm.processed.end_labels[prev->end_label].second + 1u], p) && pm.safe(p, prev)) {

                                    prev->append_cond<expr_logical::and_>(p->l, p->b, p->r);
                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                 if (?) then goto l; end
                                 if (?) then goto l; end
                              */
                              if (tools::stat::branch::same_cond_goto_labels(p, prev) && pm.safe(prev, p)) {

                                    prev->append_cond<expr_logical::or_>(p->l, p->b, p->r);
                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<1u>(i)) {

                              const auto &next = pm[i + 1u];

                              /*                       
                                    if (?) then goto l end
                                    /if  (?) then/
                                        /.../
                                    /end/
                                    /[SAFE END]/
                                    /::l::/
                              */
                              if (tools::stat::branch::is_if_cond(next)) {

                                    const auto end_label = pm.processed.end_labels[next->end_label].second;
                                    if (tools::stat::future(i, end_label) && pm.valid_next<1u>(end_label) && tools::stat::branch::is_cond_goto_label(p, tools::visitors::next_safe_executable_stat(pm, end_label + 1u)) && pm.safe(p, next)) {

                                          next->append_cond<expr_logical::and_, true>(p->l, p->b, p->r);
                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }

                        if (pm.valid_next<2u>(i)) {

                              const auto &[n1, n2] = std::tie(pm[i + 1u], pm[i + 2u]);

                              /* 
                                     if (?) then goto l; end
                                     /COMPARABLE(?)/
                                     /l:/
                              */
                              if (tools::stat::branch::is_cond_goto_label(p, n2) && tools::stat::branch::is_comparable(n1) && pm.safe(n1, n2, p)) {
                                    n1->append_cond<expr_logical::or_, true>(p->l, p->b, p->r);
                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<2u>(i) && pm.valid_prev<1u>(i)) {

                              const auto &[p1, n1, n2] = std::tie(pm[i - 1u], pm[i + 1u], pm[i + 2u]);

                              /*
                                     r = ??;
                                     if (r) then goto l end;
                                     r = ??;
                                     goto l;
                              */
                              if (pm.is_safe(p1, p, n1, n2) && tools::stat::assignment::same_single_assignment(p1, n1) && tools::stat::branch::same_cond_goto_goto_labels(p, n2) &&
                                  tools::stat::branch::is_single_compare(p, p1->l)) {

                                    n1->r = tools::exprs::generate::logical<expr_logical::or_>(p1->r, n1->r);
                                    pm.remove(p1, p);
                                    pm.set_safe(p1, p, n1, n2);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<5u>(i)) {

                              /*
                                   if (?) then goto l end [NO r]
                                   /r = ?/
                                   /[OPTIONAL/PATTERN] if (r) then goto l end [OPPOSITE COND]/
                                   /[OPTIONAL/PATTERN] r = ?/
                                   /if  (r) then/
                                   /::l::/ [SINGLE REF]
                                   /r = ?/
                                   /end/
                              */
                              luramas_address disp = 0u;
                              if (!tools::stat::branch::is_contains_compare(p, pm[i + 1u]->r)) {

                                    const auto next_if = tools::stat::branch::is_if_cond(pm[i + 2u]);
                                    if (next_if || patterns::repeatables::assignments::pattern_1(pm, s, i + 1u, disp)) {

                                          disp += i + 1u;
                                          if (pm.valid_next<5u>(disp) && pm.is_safe(i, disp + 5u)) {

                                                const auto &[n, n1, n2, n3, n4, p1] = std::tie(pm[disp], pm[disp + 1u], pm[disp + 2u], pm[disp + 3u], pm[disp + 4u], pm[disp - 1u]);
                                                if (tools::stat::branch::is_single_label_ref(pm, n2) &&
                                                    tools::stat::branch::is_if_end(n1, n4, n->l) &&
                                                    tools::stat::assignment::same_single_assignment(n, n3) &&
                                                    tools::stat::branch::is_cond_goto_label(p, n2) &&
                                                    tools::stat::branch::is_cond_goto_label(p1, n2)) {

                                                      auto cmp = tools::exprs::generate::logical<expr_logical::and_>(tools::stat::mutate::mimic_compare(n1, n->r), n3->r);
                                                      if (!next_if) {
                                                            cmp = tools::exprs::generate::logical<expr_logical::or_>(patterns::constant_folding::compilables::assignments::pattern_1(pm, s, i + 1u, disp), cmp);
                                                      }
                                                      cmp = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(p), cmp);

                                                      n3->r = cmp;
                                                      pm.remove(i, disp + 3u);
                                                      pm.remove(n4);
                                                      pm.set_safe(n3);
                                                      pm.mut(LURAMAS_DEBUG_LINE);
                                                }
                                          }
                                    }
                              }
                        }

                        if (pm.valid_next<6u>(i)) {

                              const auto &[n1, n2, n3, n4, n5, n6] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u], pm[i + 5u], pm[i + 6u]);

                              if (tools::stat::assignment::is_single_assignment_rvalue(n1) && tools::stat::branch::is_if_cond(n2) && pm.processed.jlabels_refs[p->jlabel].size() <= 1u) {

                                    /*
                                        if (??) then goto l end [1 REF]
                                        /r = VALUE/
                                        /if  (??) then/           [NOT R]
                                        	  /r = VALUE/         [OPTIONAL REPEAT]
                                        	  /if  (??) then/     [NOT R, OPTIONAL REPEAT]
                                        	  	  /::l::/
                                        	  	  /r = ?/
                                        	  /end/
                                        /end/
                                   */
                                    if (!tools::stat::branch::is_contains_compare_reg(n2, n1->l->reg)) {

                                          auto disp = 2u;
                                          const auto &n2_end = pm[pm.processed.end_labels[n2->end_label].second];
                                          while (pm.valid_next(i, disp + 2u)) {

                                                const auto &[assign, condition] = std::tie(pm[i + disp + 1u], pm[i + disp + 2u]);
                                                if (tools::stat::branch::is_cond_goto_label(p, assign)) {
                                                      break;
                                                }
                                                if (!tools::stat::assignment::same_assignment_single(n1, assign) ||
                                                    !tools::stat::branch::is_if_cond(condition) || tools::stat::branch::is_contains_compare_reg(condition, n1->l->reg) ||
                                                    n2_end != pm[pm.processed.end_labels[condition->end_label].second + (disp / 2u)]) {
                                                      disp = 0u;
                                                      break;
                                                }
                                                disp += 2u;
                                          }
                                          if (disp) {

                                                const auto &assign = pm[i + disp + 2u];
                                                if (tools::stat::assignment::same_single_assignment(n1, assign)) {

                                                      const auto ends_amt = disp / 2u;
                                                      const auto end_idx = i + disp + ends_amt + 3u;

                                                      if (tools::stat::common::contiguous<keywords::end>(pm, i + disp + 3u, end_idx) && pm.is_safe(i, end_idx)) {

                                                            pm.remove(p);
                                                            pm.remove(i + 2u, end_idx, true);
                                                            pm.set_safe(i, end_idx);

                                                            /* Compile cmp */
                                                            std::shared_ptr<ir_stat::ir_expr> compiled_cmp = nullptr;
                                                            for (auto e = 2u; e != disp; ++e) {
                                                                  const auto &cmp_p = pm[e + i];
                                                                  if (tools::stat::branch::is_if_cond(cmp_p)) {
                                                                        const auto e_cmp = tools::exprs::mutate::cmp_extract(cmp_p);
                                                                        if (compiled_cmp == nullptr) {
                                                                              compiled_cmp = e_cmp;
                                                                        } else {
                                                                              compiled_cmp = tools::exprs::generate::logical<expr_logical::and_>(compiled_cmp, e_cmp);
                                                                        }
                                                                  }
                                                            }
                                                            const auto cmp = compiled_cmp == nullptr ? tools::exprs::mutate::cmp_extract(n2) : tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::mutate::cmp_extract(n2), compiled_cmp);
                                                            n1->r = tools::exprs::generate::ternary(cmp, assign->r, n1->r);
                                                            pm.mut(LURAMAS_DEBUG_LINE);
                                                      }
                                                }
                                          }
                                    } else {

                                          /*
                                              if (?) then goto l end; [1 REF]
                                              [EXPR] = ?;
                                              if ([EXPR]) then
                                                 [EXPR] = ?;     [OPTIONAL REPEAT]
                                                 if ([EXPR]) then [OPTIONAL REPEAT]
                                                     ::l::
                                                     [EXPR] = ?;
                                                 end
                                              end
                                        */
                                          if (tools::stat::branch::is_single_compare(n2, n1->l)) {

                                                auto disp = 2u;
                                                const auto &n2_end = pm[pm.processed.end_labels[n2->end_label].second];
                                                while (pm.valid_next(i, disp + 2u)) {

                                                      const auto &[assign, condition] = std::tie(pm[i + disp + 1u], pm[i + disp + 2u]);
                                                      if (tools::stat::branch::is_cond_goto_label(p, assign)) {
                                                            break;
                                                      }

                                                      if (!tools::stat::assignment::same_single_assignment(n1, assign) ||
                                                          !tools::stat::branch::is_if_cond(condition) || !tools::stat::branch::is_single_compare(condition, n1->l) ||
                                                          n2_end != pm[pm.processed.end_labels[condition->end_label].second + (disp / 2u)]) {
                                                            disp = 0u;
                                                            break;
                                                      }
                                                      disp += 2u;
                                                }
                                                if (disp) {

                                                      const auto &assign = pm[i + disp + 2u];
                                                      if (tools::stat::assignment::same_single_assignment(n1, assign)) {

                                                            const auto ends_amt = disp / 2u;
                                                            const auto end_idx = i + disp + ends_amt + 3u;

                                                            if (tools::stat::common::contiguous<keywords::end>(pm, i + disp + 3u, end_idx) && pm.is_safe(i, end_idx)) {

                                                                  pm.remove(i, end_idx);
                                                                  pm.set_safe(i, end_idx);

                                                                  /* Compile cmp */
                                                                  std::shared_ptr<ir_stat::ir_expr> compiled_cmp = nullptr;
                                                                  for (auto e = 1u; e != disp; ++e) {
                                                                        const auto &assign = pm[e + i];
                                                                        if (tools::stat::assignment::is_single_assignment(assign)) {
                                                                              if (compiled_cmp == nullptr) {
                                                                                    compiled_cmp = assign->r;
                                                                              } else {
                                                                                    compiled_cmp = tools::exprs::generate::logical<expr_logical::and_>(compiled_cmp, assign->r);
                                                                              }
                                                                        }
                                                                  }
                                                                  if (compiled_cmp) {
                                                                        n1->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::mutate::cmp_extract(p, true), compiled_cmp), assign->r);
                                                                        pm.mut(LURAMAS_DEBUG_LINE);
                                                                  }
                                                            }
                                                      }
                                                }
                                          }
                                    }
                              }

                              /*
                                  if (?) then goto l end; [OPPOSITE]
                                  /r = ?;/
                                  /if (r) then/
                                     /::l::/
                                     /r = ?;/
                                     /::??::/
                                  /end/
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4, n5, n6) && tools::stat::branch::is_cond_goto_label(p, n3) && tools::stat::is_label(n5) && tools::stat::assignment::same_single_assignment(n1, n4) && tools::stat::branch::is_if_end_singlecmp(n2, n6, n1->l)) {

                                    n1->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::mutate::cmp_extract(p, true), n1->r), n4->r);
                                    pm.remove(p, n2, n4, n6, tools::stat::unsafe::ref(pm, n3));
                                    pm.set_safe(p, n1, n2, n4, n6);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<7u>(i)) {

                              /*
                                    if (??) then goto l end
                                    /if  (??) then [not r]/
                                         /r = ??/
                                         /if (r) then goto l2 end/
                                    /end/
                                    [OPTIONAL/REPEAT] if  (??) then [not r]
                                    [OPTIONAL/REPEAT]      r = ??
                                    [OPTIONAL/REPEAT]      if (r) then goto l2 end
                                    [OPTIONAL/REPEAT] end
                                    ::l::
                                    r = ?? 
                                    [NEXT SAFE EXECUTABLE]
                                    ::l2::
                              */
                              const auto &[n1, n2, n3, n4] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u]);
                              if (pm.is_safe(p, n1, n2, n3, n4)) {

                                    luramas_address disp = 0u;
                                    if (patterns::repeatables::if_condition::pattern_1(pm, s, i + 1u, disp) && pm.valid_next<3u>(i + disp) && pm.is_safe(i, i + disp + 4u)) {

                                          const auto &[first_cond_label, assignment] = std::tie(pm[i + disp + 1u], pm[i + disp + 2u]);

                                          if (tools::stat::branch::is_cond_goto_label(p, first_cond_label) && tools::stat::branch::is_cond_goto_label(n3, tools::visitors::next_safe_executable_stat(pm, i + disp + 3u)) &&
                                              tools::stat::assignment::same_single_assignment(n2, assignment)) {

                                                assignment->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(p), patterns::constant_folding::compilables::if_condition::pattern_1(pm, s, i + 1u, i + disp + 4u)), assignment->r);
                                                pm.remove(i, i + disp + 1u);
                                                pm.set_safe(assignment);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }

                        if (pm.valid_next<8u>(i)) {

                              const auto &[n1, n2, n3, n4, n5, n6, n7, n8] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u], pm[i + 5u], pm[i + 6u], pm[i + 7u], pm[i + 8u]);

                              /*
                                    if (??) then goto l end;
                                    /r = ??;/
                                    /if (r) then/
                                       /r = BOOLEAN;/
                                       /if (??) then/ [NOT R]
                                          /::l::/
                                          /r = ? ?? ?;/
                                       /end/
                                    /end/
                             */
                              if (pm.is_safe(p, n1, n2, n3, n4, n5, n6, n7, n8) &&
                                  tools::stat::branch::is_cond_goto_label(p, n5) && tools::stat::assignment::same_single_assignment(n1, n3) && tools::stat::assignment::same_single_assignment(n1, n6) &&
                                  tools::stat::branch::is_if_end_singlecmp(n2, n8, n1->l) && tools::stat::branch::is_if_end(n4, n7) && tools::stat::assignment::is_rvalue_boolean(n3) &&
                                  !tools::stat::branch::is_contains_compare(n4, n1->l) && tools::exprs::branch::equality(n6->r)) {

                                    auto cond = tools::exprs::mutate::cmp_extract(n4);
                                    if (!n3->r->bv) {
                                          tools::exprs::mutate::flip_cmp<true>(cond);
                                    }

                                    n1->r = tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(p), n1->r), cond), n6->r);
                                    pm.remove(p, n2, n3, n4, n5, n6, n7, n8);
                                    pm.set_safe(p, n1, n2, n3, n4, n5, n6, n7, n8);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<9u>(i)) {

                              /*
                                 if (??) then goto l end
                                 /r = ??/
                                 /if  (r) then/
                                    /if  (??) then/                [REPEATABLE]
	                                   	/r = ?? [not r]/           [REPEATABLE]
	                                   	/if (r) then goto l2 end/  [REPEATABLE]
	                                /end/                          [REPEATABLE]
                                    /::l::/                        [SINGLE REF]
                                    /r = ??;/
                                 /end/
                                 /[NEXT EXECUTABLE]/
                                 /l2:/
                             */
                              luramas_address disp = 0u;
                              const auto &[n1, n2] = std::tie(pm[i + 1u], pm[i + 2u]);
                              if (tools::stat::assignment::is_single_assignment(n1) &&
                                  tools::stat::branch::is_if_cond(n2, n1->l) &&
                                  patterns::repeatables::if_condition::pattern_1(pm, s, i + 3u, disp) &&
                                  pm.valid_next<4u>(disp + i + 3u) && pm.is_safe(i, disp + i + 7u)) {

                                    disp += i + 3u;
                                    const auto &[first_cond_label, assignment, if_stat_end, cond_goto] = std::tie(pm[disp], pm[disp + 1u], pm[disp + 2u], pm[disp - 2u]);

                                    if (tools::stat::branch::is_cond_goto_label_single_ref(p, first_cond_label, pm) &&
                                        tools::stat::assignment::same_single_assignment(n1, assignment) &&
                                        tools::stat::branch::is_if_end(n2, if_stat_end) &&
                                        tools::stat::branch::is_cond_goto_label(cond_goto, tools::visitors::next_executable_stat(pm, disp + 3u))) {

                                          n1->r = tools::exprs::generate::logical<expr_logical::or_>(
                                              tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(p), n1->r),
                                              tools::exprs::generate::logical<expr_logical::or_>(patterns::constant_folding::compilables::if_condition::pattern_1(pm, s, i + 3u, disp),
                                                  assignment->r));
                                          pm.remove(p);
                                          pm.remove(i + 2u, disp + 3u);
                                          pm.set_safe(n1);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }

                        if (pm.valid_next<10u>(i)) {

                              const auto &[n1, n2, n3, n4, n5, n6, n7, n8, n9, n10] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u], pm[i + 5u], pm[i + 6u], pm[i + 7u], pm[i + 8u], pm[i + 9u], pm[i + 10u]);

                              /*
                                     if (??) then goto l end
                                     /r = ??/ [RVALUE NOT r]
                                     /if  (r) then/ 
                                     	/if  (??) then/ [NOT r]
                                     		/r = ??/ [RVALUE NOT r]
                                     		/if (r) then goto l2 end/
                                     	/end/
                                     	/::l::/ [SINGLE REF]
                                     	/r = ??/ [RVALUE NOT r]
                                     /end/
                                     /::l2::/
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4, n5, n6, n7, n8, n9, n10) && tools::stat::branch::is_cond_goto_label(p, n7) &&
                                  tools::stat::branch::is_single_label_ref(pm, n5->jlabel) && tools::stat::branch::is_if_end_not_contains(n3, n6, n1->l) &&
                                  tools::stat::assignment::same_single_assignment_rvalue_not_contains(n1, n4, n1->l) && tools::stat::assignment::same_single_assignment_rvalue_not_contains(n4, n8, n1->l) &&
                                  tools::stat::branch::is_if_end_singlecmp(n2, n9, n1->l) && tools::stat::branch::is_cond_goto_label(n5, n10, n1->l)) {

                                    n1->r = tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(p), tools::exprs::generate::logical<expr_logical::and_>(n1->r, tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(n3, true), n4->r))), n8->r);
                                    pm.set_safe(n1);
                                    pm.remove(p, n2, n3, n4, n5, n6, n7, n8, n9);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<12u>(i)) {

                              const auto &[n1, n2, n3, n4] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u]);

                              /*
                                    if (??) then goto l end
                                    /if (??) then goto l2 end/
                                    /r = ??/
                                    /if  (r) then/
                                         /::l2::/                          [SINGLE REF]
                                         /if  (??) then [NOT r]/           [REPEAT]
                                         /    r = ?? [NOT r]/              [REPEAT]
                                         /    if (r0) then goto l3 end/    [REPEAT]
                                         /end/                             [REPEAT]
                                         /::l::/                           [SINGLE REF]
                                         /r = ??/
                                     /[SAFE ENDS]/
                                     /::l3::/
                              */
                              if (pm.is_safe(n1, n2, n3, n4) && tools::stat::assignment::is_single_assignment(n2) &&
                                  tools::stat::branch::is_if_cond(n3, n2->l) &&
                                  tools::stat::branch::is_cond_goto_label_single_ref(n1, n4, pm)) {

                                    luramas_address disp = 0u;
                                    if (patterns::repeatables::if_condition::pattern_1(pm, s, i + 5u, disp) && pm.valid_next<4u>(i + disp + 5u)) {

                                          disp += i + 5u;

                                          const auto &[d, d1, d2, dp1] = std::tie(pm[disp], pm[disp + 1u], pm[disp + 2u], pm[disp - 2u]);
                                          if (pm.is_safe(i, disp + 4u) &&
                                              tools::stat::branch::is_cond_goto_label_single_ref(p, d, pm) &&
                                              tools::stat::assignment::same_single_assignment(n2, d1) &&
                                              tools::stat::branch::is_if_end(n3, d2) &&
                                              tools::stat::branch::is_cond_goto_label(dp1, tools::visitors::next_safe_executable_stat(pm, disp + 3u))) {

                                                n2->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(p),
                                                    tools::exprs::generate::logical<expr_logical::or_>(
                                                        tools::exprs::generate::logical<expr_logical::or_>(
                                                            tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::mutate::cmp_extract(n1), n2->r),
                                                            patterns::constant_folding::compilables::if_condition::pattern_1(pm, s, i + 5u, disp)),
                                                        d1->r));
                                                pm.remove(p, n1);
                                                pm.remove(i + 3u, disp + 3u);
                                                pm.set_safe(n2);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }

                        const auto label = pm.processed.labels[p->jlabel];
                        if (pm.valid_next<1u>(label)) {

                              const auto &label_next = pm[label + 1u];

                              /*
                                    if (??) then goto l; end
                                    /.../
                                    /::l::/
                                    /[TERMINAL];/
                              */
                              if (label_next->is_terminal() && pm.safe(p)) {

                                    tools::stat::mutate::if_stat_cleared(p);
                                    pm.insert(p, label_next->clone(false), tools::stat::generate::end());
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*    
                                    l:
                                    PAGE_FUNCTION_START
                              */
                              if (tools::stat::is_page_function_start(label_next) && pm.safe(p)) {

                                    tools::stat::mutate::if_stat_cleared(p);
                                    pm.insert(p, tools::stat::generate::page_function_jump(label_next->r->clone()), tools::stat::generate::end());
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::end: {

                        if (pm.valid_prev<2u>(i)) {

                              const auto &[p2, p1] = std::tie(pm[i - 2u], pm[i - 1u]);

                              /*
                                  if  (?) then 
                                    if (?) then goto l; end
                                  end
                              */
                              if (tools::stat::branch::is_if_end(p2, p) && p1->is_k<keywords::condition_goto>() && pm.safe(p, p1, p2)) {

                                    p1->append_cond<expr_logical::and_, true>(p2->l, p2->b, p2->r);
                                    pm.remove(p, p2);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::assignment: {

                        if (pm.valid_prev<2u>(i) && pm.valid_next<1u>(i)) {

                              const auto &[p2, p1, next] = std::tie(pm[i - 2u], pm[i - 1u], pm[i + 1u]);

                              /*
                                    r = ?
                                    if (r) then
                                        r = ?
                                    /end/
                              */
                              if (pm.is_safe(p, next, p1, p2) && tools::stat::assignment::same_single_assignment(p, p2) && tools::stat::branch::is_if_end_singlecmp(p1, next, p->l)) {

                                    p2->r = (p1->b == luramas::il::arch::data::bin_kinds::nt_) ? tools::exprs::generate::logical<expr_logical::or_>(p2->r, p->r) : tools::exprs::generate::logical<expr_logical::and_>(p2->r, p->r);
                                    pm.remove(p, p1, next);
                                    pm.set_safe(p, next, p1, p2);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                    r = ?
                                    if (r ...) then
                                        r = ?
                                    /end/
                              */
                              if (pm.is_safe(p2, p1, p, next) && tools::stat::branch::is_if_end(p1, next) && tools::stat::assignment::same_single_assignment(p, p2) && p1->visit_sources(p->l->reg).size() == 1u && *p2->l == *p->l) {

                                    bool clonable = false;
                                    p1->propagate(p->l->reg, p2->r, clonable);
                                    p->r = tools::exprs::generate::logical<expr_logical::and_>(p->r, tools::exprs::mutate::cmp_extract(p1));
                                    pm.remove(p1, p2, next);
                                    pm.remove(next);
                                    pm.set_safe(p2, p1, p, next);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<3u>(i)) {

                              const auto &[n1, n2, n3] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u]);

                              /*
                                     r = ? [not R]
                                    /if (r) then goto l end/
                                    /r = ?/ [not R]
                                    /if (r) then goto l end/                
                              */
                              if (pm.is_safe(p, n1, n2, n3) && tools::stat::assignment::same_single_assignment(p, n2) && tools::stat::branch::is_single_compare(n1, p->l) && tools::stat::branch::same_cond_goto(n1, n3) &&
                                  !p->r->contains(p->l) && !n2->r->contains(p->l)) {

                                    p->r = tools::exprs::generate::logical<expr_logical::or_>(p->r, n2->r);
                                    pm.remove(n2, n3);
                                    pm.set_safe(p, n1, n2, n3);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                     r = BOOLEAN
                                    /if (? ?? ?) then goto l end/ [not r]
                                    /r = BOOLEAN/
                                    /if (? ?? ?) then goto l end/ [not r]        
                              */
                              if (pm.is_safe(p, n1, n2, n3) && tools::stat::assignment::same_single_assignment_rvalue_boolean(p, n2) && tools::stat::branch::same_cond_goto_labels(n1, n3) &&
                                  tools::stat::branch::equality(n1) && tools::stat::branch::equality(n3) &&
                                  !tools::stat::branch::is_contains_compare(n1, p->l) && !tools::stat::branch::is_contains_compare(n3, p->l)) {

                                    bool pass = false;
                                    if (p->r->bv && n2->r->bv) {

                                          pass = true;
                                          p->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(n1), tools::exprs::mutate::cmp_extract(n3));
                                          tools::stat::mutate::replace_cmp(n1, p->l);
                                    } else if (!p->r->bv && !n2->r->bv) {

                                          pass = true;
                                          p->append_cond<expr_logical::or_>(tools::exprs::mutate::cmp_extract(n3));
                                    }
                                    if (pass) {
                                          pm.remove(n2, n3);
                                          pm.set_safe(p, n1, n2, n3);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              /*
                                    r = ?;
                                    /if (r) then/ [OPPOSITE]
                                       /r = ?;/
                                       /if (r) then/ [OPPOSITE]
                                          /.../
                                       /end/
                                    /end/
                              */
                              if (pm.is_safe(p, n1, n2, n3) && tools::stat::assignment::same_single_assignment(p, n2) && tools::stat::branch::is_single_compare(n1, p->l) && tools::stat::branch::same_if(n1, n3) &&
                                  tools::stat::branch::contiguous_ends(pm, n3, n1)) {

                                    const auto &n3_end = tools::visitors::end_label_stat(pm, n3);

                                    p->r = tools::exprs::generate::logical<expr_logical::and_>(tools::stat::mutate::mimic_compare(n1, p->r), tools::stat::mutate::mimic_compare(n3, n2->r));
                                    tools::stat::mutate::cmp_true(n1);
                                    pm.remove(n2, n3, n3_end);
                                    pm.set_safe(p, n1, n2, n3, tools::visitors::end_label_stat(pm, n1), n3_end);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                    r = BOOLEAN
                                    \if  (? ?? ?) then\ [NOT r]
                                      \r = (? ?? ?)\ [NOT r]
                                    \end\
                              */
                              if (pm.is_safe(p, n1, n2, n3) && tools::stat::assignment::same_single_assignment(p, n2) && tools::stat::branch::is_if_end(n1, n3) &&
                                  tools::stat::assignment::is_rvalue_boolean(p) && tools::stat::assignment::is_rvalue_comparitive_equality(n2)) {

                                    bool clonable = false;
                                    const auto cache = p->r;
                                    p->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(n1), n2->r, !cache->bv);
                                    p->r->propagate(p->l->reg, cache, clonable);
                                    pm.set_safe(p);
                                    pm.remove(n1, n2, n3);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              /*
                                    r = (? ?? ?) [NOT r]   
                                    \if  (? ?? ?) then\ [NOT r]
                                      \r = BOOLEAN\
                                    \end\
                              */
                              if (pm.is_safe(p, n1, n2, n3) && tools::stat::assignment::same_single_assignment(p, n2) && tools::stat::branch::is_if_end_not_contains(n1, n3, p->l) &&
                                  tools::stat::assignment::is_rvalue_boolean(n2) && tools::stat::assignment::is_rvalue_comparitive_equality_not_contains(p, p->l)) {

                                    p->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(n1, !n2->r->bv), p->r);
                                    pm.set_safe(p);
                                    pm.remove(n1, n2, n3);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<5u>(i)) {

                              const auto &[n1, n2, n3, n4, n5] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u], pm[i + 5u]);

                              /*
                                r = ?
		                        /if (r) then goto l end/
		                        /if  (??) then [NOT r]/
		                        	/r = ??/
		                        	/if (r) then goto l end/
		                        /end/
                             */
                              if (pm.is_safe(p, n1, n2, n3, n4, n5) &&
                                  tools::stat::branch::same_cond_goto(n1, n4) && tools::stat::branch::is_if_end(n2, n5) && tools::stat::assignment::same_single_assignment(p, n3) &&
                                  tools::stat::branch::is_single_compare(n1, p->l) && !tools::stat::branch::is_contains_compare(n2, p->l)) {

                                    p->r = tools::exprs::generate::logical<expr_logical::or_>(tools::stat::mutate::mimic_compare(n1, p->r),
                                        tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::mutate::cmp_extract(n2), tools::stat::mutate::mimic_compare(n4, n3->r)));

                                    pm.set_safe(p, n2, n3, n4, n5);
                                    pm.remove(n2, n3, n4, n5);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<6u>(i)) {

                              const auto &[n1, n2, n3] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u]);

                              /*
                                   r = [SAME RVALUE];
                                   /if (?) then [NOT R]/
                                      /r = [SAME RVALUE];/
                                      /if (?) then [NOT R]/
                                          ...
                                      /end/
                                   /end/
                             */
                              if (tools::stat::branch::is_if_cond(n3)) {

                                    const auto end = pm.processed.end_labels[n3->end_label].second;
                                    if (pm.valid_next<1u>(end)) {

                                          const auto &[end_stat, next_end_stat] = std::tie(pm[end], pm[end + 1u]);
                                          if (pm.is_safe(p, n1, n2, n3, end_stat, next_end_stat) &&
                                              tools::stat::assignment::same_assignment_single(p, n2) &&
                                              tools::stat::branch::is_if_end(n1, next_end_stat) && tools::stat::branch::is_if_end(n3, end_stat) &&
                                              !tools::stat::branch::is_contains_compare(n1, p->l) && !tools::stat::branch::is_contains_compare(n3, p->l)) {

                                                n1->append_cond<expr_logical::and_>(n3->l, n3->b, n3->r);
                                                pm.remove(n2, n3, end_stat);
                                                pm.set_safe(p, n1, n2, n3, end_stat, next_end_stat);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }

                        if (pm.valid_next<8u>(i)) {

                              const auto &[n1, n2, n3, n4, n5, n6, n7, n8] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u], pm[i + 5u], pm[i + 6u], pm[i + 7u], pm[i + 8u]);

                              /*
                                    r = ?
                                    /if  (r) then/ [nt = and else or]
                                      /if  (?) then/
                                          /r = ?/
                                          /goto l/
                                      /end/
                                      /r = ?/
                                    /end/
                                    /l:/  
                              */
                              if (tools::stat::assignment::same_single_assignment(p, n3) && tools::stat::assignment::same_single_assignment(p, n6) &&
                                  tools::stat::branch::is_if_end_singlecmp(n1, n7, p->l) && tools::stat::branch::is_if_end(n2, n5) && tools::stat::branch::is_goto_label(n4, n8) &&
                                  pm.safe(p, n1, n2, n3, n4, n5, n6, n7, n8)) {

                                    const auto ternary = tools::exprs::generate::ternary(n2->l, n2->r, n2->b, n3->r, n6->r);
                                    p->r = (p->b == il::arch::data::bin_kinds::et_) ? tools::exprs::generate::logical<expr_logical::and_>(p->r, ternary) : tools::exprs::generate::logical<expr_logical::or_>(p->r, ternary);
                                    pm.remove(n1, n2, n3, n4, n5, n6, n7, n8);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<1u>(i) && pm.valid_prev<1u>(i)) {

                              const auto &[prev, next] = std::tie(pm[i - 1u], pm[i + 1u]);

                              /*
                                    if (? ?? ?) then
                                        ? = ?; [EQUALITY IN CMP AND TRUE IS LOGICAL ELSE TERNARY]
                                    /end/
                              */
                              if (tools::stat::branch::is_if_end(prev, next) && tools::stat::assignment::is_single_assignment_rvalue(p) && pm.safe(p, next, prev)) {

                                    p->r = (tools::stat::branch::equality(prev) && p->r->bv) ? tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(prev), p->l)
                                                                                             : tools::exprs::generate::ternary(prev->l, prev->r, prev->b, p->r, p->l);
                                    pm.remove(prev, next);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::table_assign: {

                        if (pm.valid_prev<1u>(i)) {

                              std::size_t offset = 0u;
                              const auto &prev = pm[i - 1u];

                              if (pm.is_safe(prev)) {
                                    do {
                                          const auto &np = pm[i + offset];
                                          /*
                                                r = {?}
                                                r[BASE + AMT] = ? (not r) 
                                                /[r[BASE + AMT] = ? (not r)] (Can repeart)/
                                          */
                                          if (pm.is_safe(np) && tools::stat::assignment::same_single_table_assignment_table_reg(prev, np) && !tools::stat::assignment::is_rvalue_contains(np, prev->l->reg) &&
                                              np->l->r->is_integral() && (np->l->r->n - LURAMAS_IR_CONSTANT_TABLE_BASE) == std::count_if(prev->r->tmembers.begin(), prev->r->tmembers.end(), [](const auto &p) { return p.first == nullptr; })) {

                                                prev->r->emit_table_set(np->r, nullptr);
                                                pm.remove(np);
                                                pm.set_safe(prev);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          } else {
                                                break;
                                          }
                                    } while (pm.contains(i + (++offset)));
                                    if (offset) {
                                          i += offset - 1u;
                                    }
                              }

                              offset = 0u;

                              if (pm.is_safe(prev)) {
                                    do {
                                          const auto &np = pm[i + offset];
                                          /*
                                             r = {?}
                                             r[?] = ?  (not r)    
                                            /r[?] = ? (not r)] (Can repeart)/
                                          */
                                          if (pm.is_safe(np) && tools::stat::assignment::same_single_table_assignment_table_reg(prev, np) && !tools::stat::assignment::is_rvalue_contains(np, prev->l->reg)) {
                                                prev->r->emit_table_set(np->r, np->l->r);
                                                pm.remove(np);
                                                pm.set_safe(prev);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          } else {
                                                break;
                                          }
                                    } while (pm.contains(i + (++offset)));
                                    if (offset) {
                                          i += offset - 1u;
                                    }
                              }
                        }
                        break;
                  }
                  case keywords::label: {

                        if (pm.valid_prev<2u>(i)) {

                              const auto &[prev, cond] = std::tie(pm[i - 1u], pm[i - 2u]);

                              /*
                                 if (x) then goto l; end
                                 if (y) then _GOTO(??) end
                                 ::l::
                              */
                              if (prev->is_k<keywords::condition_goto>() && tools::stat::branch::is_cond_goto_label(cond, p)) {
                                    prev->append_cond<expr_logical::and_, true>(cond->l, cond->b, cond->r);
                                    pm.remove(cond);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::table_setlist: {

                        switch (p->l->k) {
                              case expr_kinds::reg:
                              case expr_kinds::upvalue: {

                                    if (pm.valid_prev<1u>(i)) {

                                          const auto &prev = pm[i - 1u];

                                          /* 
                                             x = {}
                                             SETLIST(x, {})
                                          */
                                          if (prev->is_k<keywords::assignment>() && tools::stat::assignment::is_rvalue_tk<tkind::table>(prev) && tools::stat::assignment::same_single_assignment(prev, p)) {
                                                for (const auto &m : p->tmembers) {
                                                      prev->r->emit_table_set(m);
                                                }
                                                pm.remove(p);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }

                        switch (p->l->tk) {
                              case tkind::table: {

                                    /*
                                        SETLIST({}, {})
                                    */
                                    for (const auto &m : p->tmembers) {
                                          p->l->emit_table_set(m);
                                    }
                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        break;
                  }
                  case keywords::condition: {

                        if (pm.valid_prev<1u>(i)) {

                              const auto &prev = pm[i - 1u];

                              /*
                                   if  (??) then
                                       if (??) then 
                                       /??/
                                       /end/
                                   /end/
                              */
                              if (prev->is_k<keywords::condition>()) {

                                    const auto end_p = pm.processed.end_labels[p->end_label].second;
                                    const auto end_prev = pm.processed.end_labels[prev->end_label].second;
                                    if (end_prev == end_p + 1u) {

                                          const auto &lr = pm[end_p];
                                          if (pm.safe(prev, p, lr)) {

                                                prev->append_cond<expr_logical::and_>(p->l, p->b, p->r);
                                                pm.remove(p, lr);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }

                        if (pm.valid_next<1u>(i)) {

                              const auto &next = pm[i + 1u];

                              /* 
                                  if (??) then
                                  else
                              */
                              if (tools::stat::branch::is_if_cond(p) && tools::stat::branch::is_else_cond(next) && pm.safe(p, next)) {

                                    tools::stat::mutate::flip_cmp(p);
                                    pm.set_safe(p);
                                    pm.remove(next);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<2u>(i) && pm.valid_prev<1u>(i)) {

                              const auto &[p1, n1, n2] = std::tie(pm[i - 1u], pm[i + 1u], pm[i + 2u]);

                              /*              
                                    r = ?
                                    if (?) [NOT r] (No r)
                                       /r = ?/
                                    /end/                    
                               */
                              if (pm.is_safe(p, n1, n2) && tools::stat::branch::is_if_end(p, n2) && tools::stat::assignment::same_single_reg_assignment(p1, n1) && !tools::stat::branch::is_contains_compare_reg(p, p1->l->reg)) {

                                    n1->r = tools::exprs::generate::ternary(p->l, p->r, p->b, n1->r, n1->l);
                                    pm.set_safe(p, n1, n2);
                                    pm.remove(p, n2);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<3u>(i)) {

                              const auto &[n1, n2, n3] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u]);

                              /*
                                   if (??) then
                                      /return {ONE MEMBER};/
                                   /end/
                                   /return {ONE MEMBER};/
                              */
                              if (tools::stat::branch::is_if_end(p, n2) && tools::stat::is_return(n1) && tools::stat::is_return(n3) && n1->members.size() == 1u && n3->members.size() == 1u && pm.safe(p, n1, n2, n3)) {

                                    n3->members.front() = tools::exprs::generate::ternary(tools::exprs::mutate::cmp_extract(p), n1->members.front(), n3->members.front());
                                    pm.remove(p, n1, n2);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                    else
                                        /break/
                                    /end/
                                    /LOOP END/
                              */
                              bool last_loop_end = false;
                              if (pm.is_safe(p, n1, n2) && tools::stat::branch::is_stat_else_end(p, n2) &&
                                  tools::stat::is_break(n1) && tools::visitors::last_safe_end(pm, i + 3u, last_loop_end) && last_loop_end) {

                                    tools::stat::mutate::continue_stat_cleared(n1);
                                    pm.insert(n2, tools::stat::generate::break_stat());
                                    pm.remove(p);
                                    pm.set_safe(p, n1, n2);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                    if (?) then
                                       /FLOW INTERUPT;/
                                    /end/
                                    /[BASIC IF]/
                                       /..../
                                    /end/
                                    /FLOW INTERUPT;/                            
                              */
                              if (pm.is_safe(p, n1, n2, n3) && tools::stat::branch::is_if_end(p, n2) && n1->is_flow_interrupt() && tools::common::basic_if_stat(pm, i + 3u)) {

                                    const auto end = tools::common::safe_take_jump(pm, i + 3u);
                                    if (pm.valid_next<1u>(end) && pm[end + 1u]->compare(n1, false)) {

                                          tools::stat::mutate::flip_cmp(p);
                                          n3->append_cond<expr_logical::and_>(p->l, p->b, p->r);
                                          pm.set_safe(n3);
                                          pm.remove(p, n1, n2);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              /*
                                   if (??) then
                                      /goto x;/ [not l]
                                      /::l::/
                                   /end/
                              */
                              if (pm.is_safe(p, n1, n2, n3) && tools::stat::branch::is_if_end(p, n3) && tools::stat::branch::is_goto(n1) &&
                                  tools::stat::is_label(n2) && !tools::stat::branch::is_goto_label(n1, n2)) {

                                    tools::stat::mutate::cond_goto_stat_cleared(p, n1->jlabel);
                                    pm.set_safe(p);
                                    pm.remove(n1, n3);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<4u>(i)) {

                              const auto &[n1, n2, n3, n4] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u]);

                              /*
                                    if (??) then
                                       \r = ??;\
                                    \else\  
                                       \r = ??\
                                    \end\
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4) && tools::stat::branch::is_if_end(p, n4) && tools::stat::assignment::same_single_assignment(n1, n3, false) &&
                                  tools::stat::branch::is_else_cond(n2)) {

                                    n1->r = tools::exprs::generate::ternary(tools::exprs::mutate::cmp_extract(p), n1->r, n3->r);
                                    pm.set_safe(n1);
                                    pm.remove(p, n2, n3, n4);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                    if (??) then
                                       /??({SINGLE PARAM});/
                                    /else/
                                       /??({SINGLE PARAM});/
                                    /end/
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4) && tools::stat::branch::is_if_end(p, n4) && tools::stat::common::same_call_function_arg_count(n1, n3, static_cast<std::size_t>(1u)) &&
                                  tools::stat::branch::is_else_cond(n2)) {

                                    n1->members.front() = tools::exprs::generate::ternary(tools::exprs::mutate::cmp_extract(p), n1->members.front(), n3->members.front());
                                    pm.set_safe(n1);
                                    pm.remove(p, n2, n3, n4);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<5u>(i)) {

                              const auto &[n1, n2, n3, n4, n5] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u], pm[i + 5u]);

                              /*
                                        if  (?) then
                                          /r = ?/
                                          /if (r OR (? FROM r)) then goto l; end/
                                        /end/
                                        /r = ?/
                                        /(OPTIONAL SAFE END)/
                                        /::l::/    
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4)) {

                                    if (tools::stat::branch::is_if_end(p, n3) && tools::stat::assignment::same_single_assignment(n1, n4) && tools::stat::branch::is_cond_goto(n2) &&
                                        tools::stat::branch::is_single_compare(n2, n1->l, n1->r) && tools::stat::branch::is_cond_goto_label(n2, tools::visitors::next_safe_executable_stat(pm, i + 5u))) {

                                          n4->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::mutate::cmp_extract(p), tools::stat::mutate::mimic_compare(n2, n1->r)), n4->r);
                                          pm.remove(p, n1, n2, n3);
                                          pm.set_safe(p, n1, n2, n3, n4);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              /*

                                  if  (??) then [NOT r IN COMPARE]
	                                /r = BOOLEAN [INDICATES OPPOSITE]/
	                                /if (? ?? ?) then goto l end [NOT r IN COMPARE]/
                                  /end/
                                  /last, ends/
                                  /r = ?/ [NOT r] 
                                  /last, ends/
                                  /::l::/
                             */
                              if (pm.is_safe(p, n1, n2, n3, n4, n5) && tools::stat::assignment::is_reg_assignment_rvalue_boolean(n1)) {

                                    const auto reg = n1->l->reg;
                                    if (!tools::stat::branch::is_contains_compare_reg(p, reg) && tools::stat::branch::is_cond_goto(n2) && !tools::stat::branch::is_contains_compare_reg(n2, reg)) {

                                          bool hit = false;
                                          const auto disp = tools::visitors::last_safe_end(pm, i + 3u, hit);
                                          if (!hit && tools::stat::branch::is_if_end(p, pm[i + 3u]) && pm.valid_next<2u>(disp) && pm.is_safe(i, disp + 2u) &&
                                              tools::stat::assignment::is_reg_assignment(pm[disp + 1u], reg) &&
                                              tools::stat::branch::is_cond_goto_label(n2, tools::visitors::next_safe_executable_stat(pm, disp + 2u))) {

                                                auto &assignment = pm[disp + 1u];
                                                assignment->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::mutate::cmp_extract(p), tools::exprs::mutate::cmp_extract(pm[i + 2u], !pm[i + 1u]->r->bv)), assignment->r);

                                                pm.remove(p, n1, n2, n3);
                                                pm.set_safe(p, n1, n2, n3, assignment);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }

                              /*
                                  if  (?) then 
	                                	/r = ?/
	                                	/goto l/
                                  /end/
                                  /r = ?/
                                  /[LAST SAFE END]/
                                  /l: OR goto l;/
                              */
                              const auto &n5_executable = tools::visitors::next_safe_executable_stat(pm, i + 5u);
                              if (pm.is_safe(p, n1, n2, n3, n4) &&
                                  tools::stat::branch::is_if_end(p, n3) && tools::stat::assignment::same_single_assignment(n1, n4) &&
                                  (tools::stat::branch::is_goto_label(n2, n5_executable) || tools::stat::branch::same_goto(n2, n5_executable))) {

                                    n4->r = tools::exprs::generate::ternary(p->l, p->r, p->b, n1->r, n4->r);
                                    pm.set_safe(p, n1, n2, n3, n4);
                                    pm.remove(p, n1, n2, n3);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                    if (?) then
                                       /r = ?;/
                                       /if (r) then goto l end;/
                                    /end/
                                    /r = ?;/
                                    /l: OR goto l;/
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4, n5) && tools::stat::assignment::same_single_assignment(n1, n4) &&
                                  tools::stat::branch::is_if_end(p, n3) && tools::stat::branch::is_single_compare(n2, n1->l) &&
                                  (tools::stat::branch::same_cond_goto_goto_labels(n2, n5) || tools::stat::branch::is_cond_goto_label(n2, n5))) {

                                    n4->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::mutate::cmp_extract(p), n1->r), n4->r);
                                    pm.set_safe(p, n1, n2, n3);
                                    pm.remove(p, n1, n2, n3);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                   if  (? ?? ?) then
                                   	   /r = boolean/
                                       /if (? ?? ?) then goto l end [NOT r]/
                                   	   /[OPTIONAL REPEAT]/
                                   	   /r = boolean/
                                       /if (? ?? ?) then goto l end [NOT r]/
                                   /end/
                                   /r = [BOOLEAN]/
                                   /goto l/ 
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4, n5) && tools::stat::branch::equality(p) &&
                                  tools::stat::assignment::is_single_assignment_rvalue_boolean(n1) && n2->is_k<keywords::condition_goto>() &&
                                  tools::stat::branch::equality(n2) && !tools::stat::branch::is_contains_compare(n2, n1->l)) {

                                    std::size_t disp = 3u;
                                    while (!pm[i + disp]->is_k<keywords::end>()) {
                                          if (!pm.valid_next<2u>(i + disp)) {
                                                disp = 0u;
                                                break;
                                          }
                                          const auto &assignment = pm[i + disp];
                                          const auto &condition_goto = pm[i + disp + 1u];
                                          if (!tools::stat::assignment::same_single_assignment_rvalue_boolean(assignment, n1) ||
                                              !tools::stat::branch::same_cond_goto_labels(condition_goto, n2) ||
                                              !tools::stat::branch::equality(condition_goto) ||
                                              !tools::stat::branch::is_contains_compare(condition_goto, n1->l)) {
                                                disp = 0u;
                                                break;
                                          }
                                          disp += 2u;
                                    }
                                    if (disp && pm.valid_next<3u>(i + disp)) {

                                          const auto &[end_stat, assignment, goto_stat] = std::tie(pm[i + disp], pm[i + disp + 1u], pm[i + disp + 2u]);
                                          if (pm.is_safe(i, i + disp + 3u) &&
                                              tools::stat::branch::is_if_end(p, end_stat) &&
                                              tools::stat::assignment::same_single_assignment_rvalue_boolean(n1, assignment) &&
                                              tools::stat::branch::same_cond_goto_goto_labels(n2, goto_stat)) {

                                                /* Compile */
                                                bool rv = true;
                                                auto cond = tools::exprs::mutate::cmp_extract(p, !assignment->r->bv);
                                                std::shared_ptr<ir_stat::ir_expr> compiled_cmp = nullptr;
                                                for (auto o = i + 1u; o < disp - 1u; ++o) {
                                                      const auto d = pm[o];
                                                      if (tools::stat::assignment::is_rvalue_boolean(d)) {
                                                            rv = d->r->bv;
                                                      } else if (tools::stat::branch::is_comparable(d)) {
                                                            const auto cmp = tools::exprs::mutate::cmp_extract(d, !rv);
                                                            if (compiled_cmp == nullptr) {
                                                                  compiled_cmp = cmp;
                                                            } else {
                                                                  compiled_cmp = tools::exprs::generate::logical<expr_logical::and_>(compiled_cmp, cmp);
                                                            }
                                                      }
                                                }
                                                if (compiled_cmp) {
                                                      cond = tools::exprs::generate::logical<expr_logical::or_>(cond, compiled_cmp);
                                                }
                                                assignment->r = cond;
                                                pm.remove(i, disp + i + 1u);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }

                              /*
                                    if  (??) then
	                                	/r = ?? [not r]/
	                                	/if (r) then goto l end/
	                                /end/
	                                /r = ?? [not r]/
	                                /if (r) then goto l end/
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4, n5) && tools::stat::assignment::same_single_assignment(n1, n4) &&
                                  tools::stat::branch::is_if_end(p, n3) && tools::stat::branch::is_cond_goto(n2, n1->l) && tools::stat::branch::same_cond_goto(n2, n5) &&
                                  !tools::stat::assignment::is_rvalue_contains(n1, n1->l) && !tools::stat::assignment::is_rvalue_contains(n4, n1->l)) {

                                    n4->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::mutate::cmp_extract(p), n1->r), n4->r);
                                    pm.remove(p, n1, n2, n3);
                                    pm.set_safe(n4, n5);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                    if (??) then
                                       /??({SINGLE PARAM});/
                                       /INTERRUPT;/
                                    /end/
                                    /??({SINGLE PARAM});/
                                    /SAME INTERRUPT/
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4) && tools::stat::branch::is_if_end(p, n3) && tools::stat::common::same_call_function_arg_count(n1, n4, static_cast<std::size_t>(1u)) &&
                                  tools::stat::common::same_interrupts(n2, n5)) {

                                    n1->members.front() = tools::exprs::generate::ternary(tools::exprs::mutate::cmp_extract(p), n1->members.front(), n4->members.front());
                                    pm.set_safe(n1);
                                    pm.remove(p, n2, n3, n4);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                     if (??) then
                                       /r = ??;/
                                       /INTERRUPT;/
                                    /end/
                                    /r = ??;/
                                    /SAME INTERRUPT;/
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4) && tools::stat::branch::is_if_end(p, n3) && tools::stat::assignment::same_single_assignment(n1, n4, false) &&
                                  tools::stat::common::same_interrupts(n2, n5)) {

                                    n1->r = tools::exprs::generate::ternary(tools::exprs::mutate::cmp_extract(p), n1->r, n4->r);
                                    pm.set_safe(n1);
                                    pm.remove(p, n2, n3, n4);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                    if (??) then
                                       /INTERRUPT/
                                    /end/
                                    /if (??) then/
                                       /SAME INTERRUPT/
                                    /end/
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4) && tools::stat::branch::is_if_end(p, n2) && tools::stat::branch::is_if_end(n3, n5) &&
                                  tools::stat::common::same_interrupts(n1, n4)) {

                                    pm.set_safe(p);
                                    p->append_cond<expr_logical::or_>(n3->l, n3->b, n3->r);
                                    pm.remove(n3, n4, n5);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<6u>(i)) {

                              const auto &[n1, n2, n3, n4, n5, n6] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u], pm[i + 5u], pm[i + 6u]);

                              /*
                                    if  (??) then
                                        /r = ??/
                                        /if (r) then goto l end/
                                        /r = if (??) then ?? else r/ [not r in then and cond]
                                    /end/                      
                                    /r = ??/
                                    /::l::/
                              */
                              if (tools::stat::branch::is_if_end(p, n4) &&
                                  tools::stat::assignment::same_single_assignment(n1, n3) && tools::stat::assignment::same_single_assignment(n3, n5) &&
                                  tools::stat::branch::is_cond_goto_label_true(n2, n6, n1->l) && tools::exprs::values::is_ternary_else(n3->r, n1->l) &&
                                  !tools::exprs::common::ternary_then_contains(n3->r, n1->l) && !tools::exprs::common::compare_contains(n3->r, n1->l)) {

                                    n5->r = tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(p, true),
                                                                                                    tools::exprs::generate::logical<expr_logical::and_>(n1->r, tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(n3->r, true), n3->r->ev))),
                                        n5->r);

                                    pm.remove(p, n1, n2, n3, n4);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<7u>(i)) {

                              const auto &[n1, n2, n3, n4, n5, n6, n7] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u], pm[i + 5u], pm[i + 6u], pm[i + 7u]);

                              /*
                                    if  (? ?? ?) then
                                        /goto l/
                                    /end/
                                    /r = BOOLEAN [OPPISITE FROM LABEL]/
                                    /goto l(2)/
                                    /::l::/
                                    /r = BOOLEAN [INDICATES OPPOSITE]/
                                    /::l::(2)/
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4, n5, n6, n7) &&
                                  tools::stat::branch::is_if_equality_end(p, n2) && tools::stat::branch::is_goto_label(n1, n5) && tools::stat::branch::is_goto_label(n4, n7) &&
                                  tools::stat::assignment::same_single_assignment_rvalue_boolean(n3, n6)) {

                                    n6->r = tools::exprs::mutate::cmp_extract(p, !n6->r->bv);
                                    pm.set_safe(p, n1, n2, n3, n4, n5, n6, n7);
                                    pm.remove(p, n1, n2, n3, n4);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<8u>(i)) {

                              const auto &[n1, n2, n3, n4, n5, n6, n7] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u], pm[i + 5u], pm[i + 6u], pm[i + 7u]);

                              /*
                                    if  (??) then
                                    	    /if  (??) then/ [NOT r]
                                    	    	/r = ??/ [NOT r]
                                    	    	/if (r) then goto l end/
                                    	    /end
                                    	    [OPTIONAL REPEAT]/if  (??) then/ [NOT r]
                                    	    [OPTIONAL REPEAT]	/r = ??/ [NOT r]
                                    	    [OPTIONAL REPEAT]	/if (r) then goto l end/
                                    	    [OPTIONAL REPEAT]/end
                                    /end/
                                    /r0 = ??/ [NOT r]
                                    /[NEXT EXECUTABLE]
                                    /::l::/
                              */
                              if (pm.is_safe(p, n1, n2, n3, n4, n5, n6, n7)) {

                                    luramas_address disp = 0u;
                                    if (patterns::repeatables::if_condition::pattern_1(pm, s, i + 1u, disp) && pm.valid_next<3u>(i + disp + 1u)) {

                                          disp += i + 1u;
                                          const auto &[cond_end, assignment] = std::tie(pm[disp], pm[disp + 1u]);

                                          if (pm.is_safe(i, disp + 2u) &&
                                              tools::stat::branch::is_if_end(p, cond_end) &&
                                              tools::stat::branch::is_cond_goto_label(n3, tools::visitors::next_executable_stat(pm, disp + 2u)) &&
                                              tools::stat::assignment::same_single_assignment(n2, assignment)) {

                                                assignment->r = tools::exprs::generate::logical<expr_logical::or_>(patterns::constant_folding::compilables::if_condition::pattern_1(pm, s, i + 1u, disp), assignment->r);
                                                pm.remove(i, disp + 1u);
                                                pm.set_safe(assignment);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }

                        if (pm.valid_prev<1u>(i) && pm.valid_next<11u>(i)) {

                              const auto &[p1, n1] = std::tie(pm[i - 1u], pm[i + 1u]);

                              /*
                                   r = ?
                                   if  (r) then
                                   	/if  (?) then/
                                   		/r = ?/                        [OPTIONAL REPEAT]
                                   		/if (r) then goto l; end/     [OPTIONAL REPEAT]
                                        ...
                                        /r = ?/                        [OPTIONAL REPEAT]
                                   		/if (r) then goto l; end/     [OPTIONAL REPEAT]
                                   	/end/
                                   	/if  (?) then/
                                   		/r = ?/
                                   		/goto l/
                                   	/end/
                                   	/r = ?/
                                   /end/
                                   /::l::/
                              */
                              if (pm.is_safe(p, p1, n1)) {

                                    auto disp = 0ull;
                                    std::shared_ptr<ir_stat> cond_goto_stat = nullptr;
                                    while (tools::stat::assignment::same_single_assignment(p1, pm[i + disp + 2u]) &&
                                           ((cond_goto_stat == nullptr && pm[i + disp + 3u]->is_k<keywords::condition_goto>() && (cond_goto_stat = pm[i + disp + 3u])) ||
                                               (cond_goto_stat != nullptr && tools::stat::branch::same_cond_goto_labels(cond_goto_stat, pm[i + disp + 3u])))) {
                                          disp += 2u;
                                          if (!tools::stat::branch::is_single_compare(cond_goto_stat, cond_goto_stat->l) || !pm.is_safe(pm[i + disp + 2u], pm[i + disp + 3u])) {
                                                disp = 0u;
                                                break;
                                          }
                                    }
                                    if (disp && pm.valid_next(8u, i + disp + 2u)) {

                                          disp += i + 2u;

                                          const auto &[n2, n3, n4, n5, n6, n7, n8, n9] = std::tie(pm[disp], pm[disp + 1u], pm[disp + 2u], pm[disp + 3u], pm[disp + 4u], pm[disp + 5u], pm[disp + 6u], pm[disp + 7u]);
                                          if (pm.is_safe(n2, n3, n4, n5, n6, n7, n8, n9) &&
                                              tools::stat::branch::is_if_end(n1, n2) && tools::stat::branch::is_if_end(n3, n6) && tools::stat::branch::is_if_end_singlecmp(p, n8, p1->l) &&
                                              tools::stat::assignment::same_single_assignment(p1, n4) && tools::stat::assignment::same_single_assignment(p1, n7) &&
                                              tools::stat::branch::is_goto_label(n5, n9) && tools::stat::branch::is_cond_goto_label(cond_goto_stat, n9)) {

                                                /* Compile repeats */
                                                std::shared_ptr<ir_stat::ir_expr> rep_expr = nullptr;
                                                for (auto o = i + 2u; o < disp; o += 2u) {
                                                      auto expr = pm[o]->r;
                                                      expr->b = pm[o + 1u]->b;
                                                      rep_expr = (rep_expr == nullptr) ? expr : tools::exprs::generate::logical<expr_logical::or_>(rep_expr, expr);
                                                }

                                                // TODO: FINISH LOGICAL TERNARYS
                                                p1->r = rep_expr;
                                                pm.remove(i, disp + 7u);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                        }

                        if (pm.valid_prev<1u>(i) && pm.valid_next<7u>(i)) {

                              const auto &[p1, n1, n2, n3, n4, n5, n6, n7] = std::tie(pm[i - 1u], pm[i + 1u], pm[i + 2u], pm[i + 3u], pm[i + 4u], pm[i + 5u], pm[i + 6u], pm[i + 7u]);

                              /*
                                    r = ??
                                    if  (??) then
                                    	/if  (??) then/
                                    		/r = ??/
                                    		/goto l/
                                    	/end/
                                    	/r = ??/
                                    /end/
                                    /::l::/
                              */
                              if (pm.is_safe(p, p1, n1, n2, n3, n4, n5, n6, n7) && tools::stat::branch::is_if_end(n1, n4) && tools::stat::branch::is_if_end(p, n6) &&
                                  tools::stat::assignment::same_single_assignment(p1, n2) && tools::stat::assignment::same_single_assignment(p1, n5) && tools::stat::branch::is_goto_label(n3, n7)) {

                                    p1->r = tools::exprs::generate::ternary(tools::exprs::mutate::cmp_extract(p), tools::exprs::generate::ternary(tools::exprs::mutate::cmp_extract(n1), n2->r, n5->r), p1->r);
                                    pm.remove(p, n1, n2, n3, n4, n5, n6);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::forloop_generic: {

                        if (pm.valid_prev<1u>(i)) {

                              const auto &prev = pm[i - 1u];

                              /*
                                    r(n), ... = ??
                                    for r(n), ... in ... do
                              */
                              if (pm.is_safe(prev) && prev->is_k<keywords::assignment>()) {

                                    for (const auto &target : p->extract_dest_regs()) {

                                          const auto dests = prev->extract_dest_regs();
                                          if (dests.find(target) != dests.end()) {

                                                const auto it = std::find_if(prev->members.begin(), prev->members.end(), [&](const auto &m) { return m->is_reg(target); });
                                                if (it != prev->members.end()) {
                                                      prev->members.erase(std::remove(prev->members.begin(), prev->members.end(), *it));
                                                      if (prev->members.size() == 1u) {
                                                            prev->l = prev->members.front();
                                                            prev->members.clear();
                                                      }
                                                      pm.set_safe(prev);
                                                      pm.mut(LURAMAS_DEBUG_LINE);
                                                }
                                          }
                                    }
                              }
                        }
                        break;
                  }
                  case keywords::goto_label: {

                        if (pm.valid_prev<1>(i) && pm.valid_next<1>(i)) {

                              const auto &[p1, n1] = std::tie(pm[i - 1u], pm[i + 1u]);

                              /*                       
                                  if  (?) then
                                    goto l;
                                  /end/
                              */
                              if (tools::stat::branch::is_if_end(p1, n1) && pm.is_safe(p, p1)) {

                                    const auto &end = pm[pm.processed.end_labels[p1->end_label].second];
                                    if (pm.is_safe(end)) {

                                          tools::stat::mutate::cond_goto_stat_cleared(p1, p->jlabel);
                                          pm.set_safe(p1);
                                          pm.remove(p, end);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }

                        if (pm.valid_next<2u>(i)) {

                              const auto &[n1, n2] = std::tie(pm[i + 1u], pm[i + 2u]);

                              /*
                                    goto l
		                        /end/
                                /goto l/
                              */
                              if (tools::stat::branch::same_goto(p, n2) && n1->is_k<keywords::end>() && pm.safe(p, n1, n2)) {

                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        const auto label = tools::common::safe_take_jump(pm, i);

                        if (pm.valid_next<1u>(label)) {

                              const auto &label_next = pm[label + 1u];

                              /*
                                  goto l
                                  /.../
                                  /::l::/
                                  /[TERMINAL];/
                              */
                              if (label_next->is_terminal() && pm.safe(p)) {

                                    pm.remove(p);
                                    pm.insert(p, label_next->clone(false));
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*    
                                    l:
                                    PAGE_FUNCTION_START
                              */
                              if (tools::stat::is_page_function_start(label_next) && pm.safe(p)) {
                                    pm.remove(p);
                                    pm.insert(p, tools::stat::generate::page_function_jump(label_next->r->clone()));
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<2u>(label)) {

                              const auto &[ln1, ln2] = std::tie(pm[label + 1u], pm[label + 2u]);

                              /*
                                  goto l
                                  /.../
                                  /::l::/
                                  /Page_start/
                                  /DEF/
                            */
                              if (tools::stat::is_page_function_start(ln1) && tools::stat::is_definition(ln2) && pm.safe(p)) {

                                    pm.remove(p);
                                    pm.insert(p, tools::stat::generate::page_function_jump(ln1->r, ln2));
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        /*
                                  goto l
                                  /.../
                                  /::l::/
                                  /[END OF CODE]/
                         */
                        if (!pm.valid_next<1u>(label)) {
                              pm.remove(p);
                              pm.insert(p, tools::stat::generate::retn());
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                        break;
                  }
                  case keywords::stack_pop: {

                        if (pm.valid_next<1u>(i)) {

                              const auto &next = pm[i + 1u];

                              /* 
                                     STACK_POP (??, ID)
                                     STACK_POP (??, ID)
                              */
                              if (tools::stat::common::same_stack_pop(p, next) && pm.safe(p, next)) {

                                    p->members.reserve(p->members.size() + next->members.size());
                                    p->members.insert(p->members.end(), next->members.begin(), next->members.end());
                                    pm.remove(next);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::stack_push: {

                        if (pm.valid_next<1u>(i)) {

                              const auto &next = pm[i + 1u];

                              /* 
                                     STACK_PUSH (??, ID)
                                     STACK_PUSH (??, ID)
                              */
                              if (tools::stat::common::same_stack_push(p, next) && pm.safe(p, next)) {

                                    p->members.reserve(p->members.size() + next->members.size());
                                    p->members.insert(p->members.end(), next->members.begin(), next->members.end());
                                    pm.remove(next);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::continue_: {

                        if (pm.valid_next<2u>(i)) {

                              /* 
                                      continue
                                     /[NEXT SAFE EXECUTABLE] continue;/
                              */
                              const auto next = tools::trackers::next_safe_executable(pm, i);
                              if (next != i && tools::stat::branch::same_continue(p, pm[next]) && pm.is_safe(p)) {

                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::retn: {

                        if (pm.valid_next<2u>(i)) {

                              /* 
                                  return ??;
                                 /[NEXT SAFE EXECUTABLE] return ??;/
                              */
                              const auto next = tools::trackers::next_safe_executable(pm, i);
                              if (next != i && tools::stat::common::same_returns(p, pm[next]) && pm.is_safe(p, pm[next])) {

                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::while_: {

                        if (pm.valid_next<3u>(i)) {

                              const auto &[n1, n2, n3] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u]);

                              /*
                                    while (true) do
                                        if (...) then
                                           break;
                                        end
                               */
                              if (tools::stat::branch::is_while_true(p) && tools::stat::branch::is_if_end(n1, n3) && tools::stat::is_break(n2) && pm.is_safe(p, n1, n2, n3)) {

                                    tools::stat::mutate::flip_cmp(n1);
                                    tools::stat::mutate::replace_cmp(p, n1->l, n1->b, n1->r);
                                    pm.remove(n1, n2, n3);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }

                              /*
                                 while (??) do
                                     if (...) then
                                        break;
                                     end
                              */
                              if (tools::stat::branch::is_if_end(n1, n3) && tools::stat::is_break(n2) && pm.is_safe(p, n1, n2, n3)) {

                                    tools::stat::mutate::flip_cmp(n1);
                                    p->append_cond<expr_logical::and_>(n1->l, n1->b, n1->r);
                                    pm.set_safe(p);
                                    pm.remove(n1, n2, n3);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::page_function_start: {

                        if (pm.valid_next<1u>(i)) {

                              const auto &n = pm[i + 1u];

                              /* 
                                    Page start/
                                    /end/
                              */
                              if (tools::stat::is_end(n) && pm.safe(p, n)) {
                                    pm.insert_front(i, n);
                                    pm.remove(n);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        if (pm.valid_next<2u>(i)) {

                              const auto &[n1, n2] = std::tie(pm[i + 1u], pm[i + 2u]);

                              /* 
                                    Page start
                                    def
                                    end
                                    [[END]]
                              */
                              if (tools::stat::is_definition(n1) && tools::stat::is_page_function_end(n2, p->r->extract_integral_base()) && !pm.contains(i + 3u) && pm.safe(p, n1, n2)) {
                                    pm.insert(n1, tools::stat::generate::retn());
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                        break;
                  }
                  case keywords::bitwrite: {

                        if (pm.valid_next<1u>(i)) {

                              const auto &n = pm[i + 1u];

                              /* 
									 bitwrite(x, b, [n(p1), n(p2)]);
                                     bitwrite(x, b, [n in range of [n(p1), n(p2)] , n2]);                 
                              */
                              if (tools::stat::is_bitwrite(n) && tools::stat::is_bitwrite(p, n->l, n->r) && tools::exprs::basic::is_integral(p->v, p->lba, n->v, n->lba) &&
                                  math::is::range_ii(p->lba->extract_integral() + 1u, n->v->extract_integral(), n->lba->extract_integral())) {

                                    n->v->n = p->v->n;
                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }

                        break;
                  }
                  case keywords::until: {

                        const auto rep = tools::common::reverse_safe_take_jump(pm, i);

                        /* 
                           repeat 
                            ...
                           until (true)                            
                        */
                        if (const auto &srep = pm[rep]; tools::stat::branch::is_until_true(p) && pm.safe(p, srep)) {

                              pm.insert(srep, tools::stat::generate::while_stat(p->l, p->b, p->r));
                              pm.insert(p, tools::stat::generate::end());
                              pm.remove(p, srep);
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                        break;
                  }
                  case keywords::page_function_goto: {

                        /* Page jump has stack values */
                        if (tools::stat::is_page_function_jump(p) && p->l && p->lba && pm.safe(p)) {
                              p->pfk = page_function_goto_kind::call;
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }

                        /* Decast L */
                        if (tools::exprs::values::is_cast(p->l) && pm.safe(p)) {
                              p->l = p->l->l;
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
      }

      if (s.ffast_folder) {
            for (const auto &[k, v] : pm.processed.labels) {
                  if (const auto it = pm.processed.jlabels_refs.find(k); it == pm.processed.jlabels_refs.end() || it->second.empty()) {
                        pm.remove(pm[v]);
                  }
            }
      }
      return;
}