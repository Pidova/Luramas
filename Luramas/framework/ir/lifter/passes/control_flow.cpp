#include "../generation/cfg/traversal.hpp"
#include "includes/common.hpp"

namespace luramas::ir::passes {

      void control_flow_simplification(pass_manager &pm, shared &s) {

            for (const auto &i : pm.iter()) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::condition: {

                              if (pm.valid_next<2u>(i)) {

                                    const auto &[n1, n2] = std::tie(pm[i + 1u], pm[i + 2u]);

                                    /*                       
                                            if  (r) then [OPPOSITE]
                                                 /r = ?/
                                            /end/
                                    */
                                    if (pm.is_safe(p, n1, n2) && tools::stat::assignment::is_single_assignment(n1) && tools::stat::branch::is_if_end_singlecmp(p, n2, n1->l)) {

                                          n1->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::mutate::cmp_extract(p, true), n1->r);
                                          pm.remove(p, n2);
                                          pm.set_safe(n1);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              if (pm.valid_next<3u>(i)) {

                                    const auto &[n1, n2, n3] = std::tie(pm[i + 1u], pm[i + 2u], pm[i + 3u]);

                                    /*                       
                                                if  (?) then [OPPOSITE, NO r REGS]
                                                     /r = ?/
                                                /end/
                                                /r = ?/
                                     */
                                    if (pm.is_safe(p, n1, n2, n3) && tools::stat::branch::is_if_end(p, n2) && tools::stat::assignment::same_single_assignment(n1, n3) &&
                                        !tools::stat::branch::is_contains_compare_reg(p, n1->l->reg)) {

                                          n3->r = tools::exprs::generate::logical<expr_logical::or_>(tools::exprs::generate::logical<expr_logical::and_>(tools::exprs::mutate::cmp_extract(p, true), n3->r), n1->r);
                                          pm.set_safe(n3);
                                          pm.remove(p, n1, n2);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }

                              if (pm.valid_next<1u>(i) && pm.safe(p)) {

                                    auto &next = pm[i + 1u];

                                    /*
                                        if  (??) then
                                           /if (??) then goto l; end/
                                           /.../
                                           /goto l/
                                        /end/
                                    */
                                    const auto end = tools::common::safe_take_jump(pm, i);
                                    if (next->is_k<keywords::condition_goto>()) {

                                          const auto &prev = pm[end - 1u];
                                          if (prev->is_k<keywords::goto_label>() && prev->jlabel == next->jlabel && pm.safe(next)) {
                                                tools::stat::mutate::if_stat_cleared(next);
                                                pm.insert(pm[end - 2u], tools::stat::generate::end());
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }

                                    /*
                                        if  (??) then
                                           /[MARK END LABELS]/
                                           /.../
                                           /[TERMINATOR]/
                                           /.../
                                        /end/
                                     */
                                    auto term = i;
                                    luramas_address end_label = 0u;
                                    for (auto o = end; o > i; --o) {
                                          const auto &e = pm[o];
                                          if (end_label && end_label == e->end_label) {
                                                end_label = 0u;
                                          } else if (!end_label) {
                                                end_label = e->end_label;
                                                if (e->is_terminator() || e->is_k<keywords::goto_label>()) {
                                                      term = o;
                                                      break;
                                                }
                                          }
                                    }
                                    if (term != i) {

                                          pm.insert(pm[term], tools::stat::generate::end());
                                          pm.remove(pm[end]);
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

      void agressive_thread_out(pass_manager &pm, shared &s) {

            std::optional<generation::cfg::cfg> cfg;
            for (const auto &i : pm.iter()) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::goto_label:
                        case keywords::condition_goto: {

                              const auto label = tools::common::safe_take_jump(pm, i);
                              if (!cfg.has_value()) {
                                    cfg = generation::cfg::generate(pm.ir, LURAMAS_IR_ENTRY, pm.env_flags.fhas_pages);
                              }

                              /* Get path */
                              const auto path = cfg::traverse::pathing::path_with_loop((*cfg).visit(i + 1u), (*cfg).visit(label), *cfg);

                              /* Propagate */
                              bool ss = false;
                              std::vector<std::shared_ptr<generation::cfg::block>> v;
                              for (const auto &[simulated, block] : path) {
                                    if (simulated) {
                                          ss = true;
                                          break;
                                    }
                                    v.emplace_back(block);
                              }
                              if (ss) {
                                    continue;
                              }

                              /* Optimize blocks */
                              auto optimized_blocks = cfg::traverse::pathing::optimize(pm.ir, v, cfg.value());
                              if (optimized_blocks.empty()) {
                                    continue;
                              }

                              /* Remove current */
                              optimized_blocks.pop_back();

                              /* Unsafe */
                              if (std::none_of(optimized_blocks.begin(), optimized_blocks.end(), [&](const auto &i) { return pm.is_safe(pm[i.second->get_front()]); })) {
                                    continue;
                              }

                              if (!optimized_blocks.empty()) {
                                    std::vector<luramas_blockrange> unsafe;

                                    /* Insert */
                                    const auto flag = tools::stat::generate::flags::synthetic::flagable::pass_init_assign(pm);

                                    if (tools::stat::is_definition(pm[0u])) {
                                          pm.insert(pm[0u], flag);
                                    } else {
                                          pm.push_front(flag);
                                    }
                                    pm.remove(p);
                                    {
                                          const auto asgn = tools::stat::generate::assignment(flag->l, tools::exprs::generate::boolean(true));
                                          tools::stat::generate::flags::synthetic::flagable::set(asgn);
                                          pm.insert(p, asgn);
                                    }
                                    pm.set_safe(p);

                                    for (const auto &[keyword, block] : optimized_blocks) {

                                          if (std::any_of(unsafe.begin(), unsafe.end(), [&](const auto &i) { return tools::treshold(block->get_front(), i); })) {
                                                continue;
                                          }

                                          const auto first = block == optimized_blocks.front().second;
                                          switch (keyword) {
                                                case keywords::break_: {

                                                      if (first) {
                                                            pm.insert(p, tools::stat::generate::break_stat());
                                                      } else {
                                                            pm.insert(pm[block->get_front()], tools::stat::generate::flags::synthetic::flagable::cond(flag->l), tools::stat::generate::break_stat(), tools::stat::generate::end());
                                                      }
                                                      break;
                                                }
                                                case keywords::continue_: {

                                                      if (first) {
                                                            pm.insert(p, tools::stat::generate::continue_stat());
                                                      } else {
                                                            pm.insert(pm[block->get_front()], tools::stat::generate::flags::synthetic::flagable::cond(flag->l), tools::stat::generate::continue_stat(), tools::stat::generate::end());
                                                      }
                                                      break;
                                                }
                                                default: {

                                                      const auto curr = block->get_front() + 1u;
                                                      if (const auto end = tools::violations::block_violates(pm, curr, label).ending_loc; curr != end) {
                                                            auto cond = tools::stat::generate::flags::synthetic::flagable::cond(flag->l);
                                                            tools::stat::mutate::flip_cmp(cond);
                                                            pm.insert(pm[block->get_front()], cond);
                                                            pm.insert_front(end, tools::stat::generate::end());
                                                            unsafe.emplace_back(tools::transform::address_to_range(curr, end));
                                                      }
                                                      break;
                                                }
                                          }
                                          pm.set_safe(pm[block->get_front()]);
                                    }
                                    pm.mut(LURAMAS_DEBUG_LINE);
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

      void redundant_condition_elimination(pass_manager &pm, shared &s) {

            const auto cfg = generation::cfg::generate(pm.ir, LURAMAS_IR_ENTRY, pm.env_flags.fhas_pages);

            // TODO: FINISH

            return;
      }
} // namespace luramas::ir::passes