#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools {

      bool breaks_out(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address label) {

            const auto unfinished = tools::trackers::unfinished_condition(pm, start, label, tools::stat::iter(start, label) == 1);

            return std::any_of(unfinished.begin(), unfinished.end(), [&](const auto &c) {
                  return c.second->is_loop() || tools::stat::branch::is_loop_end(pm, c.second);
            });
      }

      bool can_breakout(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address label) {

            if (stat::past(start, label)) {
                  return false;
            }

            const auto unfinished = tools::trackers::unfinished_condition(pm, start, label);
            if (std::count_if(unfinished.begin(), unfinished.end(), [&](const auto &i) { return tools::stat::branch::is_loop_end(pm, i.second); }) != 1u) {
                  return false;
            }
            return std::any_of(unfinished.begin(), unfinished.end(), [&pm, label](const auto &i) { return tools::stat::branch::is_loop_end(pm, i.second) &&
                                                                                                          tools::stat::branch::same_labels(tools::visitors::next_safe_executable_stat(pm, i.first + 1u), pm[label]); });
      }

      bool can_continue(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address label, const bool pending_label_loop) {

            luramas_address parent_loop = 0u;
            if (!pm.valid_next<1u>(label) || tools::stat::future(start, label) || !tools::visitors::parent_loop(pm, start, parent_loop)) {
                  return false;
            }

            const auto &next = tools::visitors::next_safe_executable_stat(pm, label + 1u);
            const auto end_loop = next->end_label && pm[pm.processed.end_labels[next->end_label].first]->is_loop();

            if (!pending_label_loop && !next->is_loop() && !end_loop) {
                  return false;
            }

            const auto unfinished = end_loop ? tools::trackers::unfinished_condition(pm, start, label) : tools::trackers::unfinished_condition(pm, label + 2u, start);
            return std::none_of(unfinished.begin(), unfinished.end(), [](const auto &c) {
                  return c.second->is_loop();
            });
      }

      struct condition_stack {
            std::intptr_t stack = 0;
            ir_stat::space c;
      };

      cond_stack stack_validate(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end) {
            cond_stack result;
            if (stat::past(start, end)) {
                  return result;
            }
            condition_stack cs;

            result.closing_index = start;
            while (result.closing_index < end) {

                  const auto &p = pm[result.closing_index];
                  if (tools::stat::branch::is_condition_stack(p)) {
                        if (tools::stat::branch::is_condition_stack_scope(p)) {
                              cs.c.emplace_back(p);
                        } else if (cs.c.empty()) {
                              result.reason = cond_stack_reason::closing;
                              return result;
                        } else if (!tools::stat::branch::valid_condition(cs.c.back(), p)) {
                              result.reason = cond_stack_reason::mismatch;
                              return result;
                        } else {
                              cs.c.pop_back();
                        }
                        if ((result.closing_val += tools::stat::branch::condition_stack(p)) < 0) {
                              result.reason = cond_stack_reason::closing;
                              return result;
                        }
                  }
                  if (!result.closing_val && p->is_interrupt()) {
                        result.reason = cond_stack_reason::termination;
                        return result;
                  }
                  ++result.closing_index;
            }
            --result.closing_index;
            if (result.closing_val) {
                  result.reason = cond_stack_reason::no_closing;
            } else {
                  result.valid = true;
            }
            return result;
      }

      luramas_address backtrack(luramas::ir::passes::pass_manager &pm, const luramas_address scope_end_stat, bool &valid, const luramas_address break_label) {

            bool broke_out = false;
            auto i = scope_end_stat;
            luramas_address else_label = 0u;
            while (i < pm.amount()) {

                  const auto &p = pm[i++];
                  if (p->is_k<keywords::label>() && p->label == break_label) {
                        valid = true;
                        return i - 1u;
                  }
                  if (!else_label && (tools::stat::branch::is_elseif_cond(p) || tools::stat::branch::is_else_cond(p))) {
                        else_label = p->elif_end_label;
                  } else {
                        if (else_label) {
                              if (p->end_label != else_label) {
                                    continue;
                              }
                              else_label = 0u;
                        }
                        if (!broke_out) {
                              if (p->is_k<keywords::break_>()) {
                                    broke_out = true;
                              } else if ((!p->is_k<keywords::label>() && !p->is_scope_end()) || p->is_k<keywords::until>()) {
                                    valid = true;
                                    return i - 1u;
                              }
                        } else if (p->end_label) {

                              const auto it = pm.processed.end_labels.find(p->end_label);
                              broke_out = !(it != pm.processed.end_labels.end() && pm[it->second.first]->is_loop());
                        }
                  }
            }
            valid = broke_out;
            return i - 1u;
      }

      luramas_address next_valid_jump(luramas::ir::passes::pass_manager &pm) {

            luramas_address result = 0u;
            for (const auto &i : pm.ir.data) {
                  if (result < i->jlabel) {
                        result = i->jlabel;
                  }
                  if (result < i->label) {
                        result = i->label;
                  }
            }
            return result + (++pm.label_padding);
      }

      bool condition_has_else(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end) {

            if (start >= end || !tools::stat::branch::is_cond(pm[start])) {
                  return false;
            }

            std::intptr_t s = 0u;
            for (auto o = start + 1u; o < end; ++o) {
                  const auto &d = pm[o];
                  s += stat::branch::condition_stack(d);
                  if (!s && tools::stat::branch::is_else_stat(d)) {
                        return true;
                  }
                  if (s < 0) {
                        return false;
                  }
            }
            return false;
      }

      namespace block {

            bool independent(const ir_stat::space &data) {

                  for (const auto &i : data) {
                        for (const auto &expr : i->extract_ordered_deep_exprs()) {
                              if (expr->is_volatile() || expr->is_closure_sensitive()) {
                                    return false;
                              }
                        }
                  }
                  return true;
            }

            ir_stat::space orphaned(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {

                  ir_stat::space result;
                  boost::unordered_flat_set<std::shared_ptr<ir_stat>> pending_back_edges;

                  result.reserve(tools::count::insts(range));

                  bool dependant = false;
                  for (auto loc = range.first; loc < range.second; ++loc) {

                        const auto &i = pm[loc];
                        if (dependant) {

                              const auto violation = violations::block_violates(pm, loc, range.second);
                              if (violation.valid) {
                                    break;
                              } else {
                                    const auto &violates_on = pm[violation.ending_loc];
                                    if (tools::stat::branch::is_loop_end(pm, violates_on)) {
                                          pending_back_edges.erase(pm[tools::common::reverse_safe_take_jump(pm, violation.ending_loc)]);
                                    } else {
                                          switch (violation.reason) {
                                                case violations::block_violation_exceptions::invalid_end: {
                                                      result.emplace_back(violates_on);
                                                      break;
                                                }
                                                case violations::block_violation_exceptions::invalid_else_conditional: {
                                                      for (auto i = violation.ending_loc; i < tools::common::safe_take_jump(pm, violation.ending_loc) + 1u; ++i) {
                                                            result.emplace_back(pm[i]);
                                                      }
                                                      break;
                                                }
                                                default: {
                                                      break;
                                                }
                                          }
                                    }
                              }
                              loc = violation.ending_loc;
                        } else if (tools::stat::is_label(i)) {
                              dependant = true;
                        } else if (i->is_loop()) {
                              pending_back_edges.insert(i);
                        } else {
                              result.emplace_back(i);
                        }
                  }
                  for (const auto &i : pending_back_edges) {
                        result.emplace_back(i);
                  }
                  return result;
            }
      } // namespace block

      namespace control_flow {

            namespace block {

                  bool is_jump(const std::shared_ptr<generation::cfg::block> &b) {
                        return b && !b->fall && !b->then && b->jump;
                  }

            } // namespace block

            std::vector<std::pair<generation::cfg::block_kind, luramas_address>> exits(luramas::ir::passes::pass_manager &pm, const generation::cfg::cfg &cfg, const luramas_address start, const luramas_address target) {

                  std::vector<std::pair<generation::cfg::block_kind, luramas_address>> result;

                  if (!pm.contains(start)) {
                        return result;
                  }

                  const auto entry = cfg.visit(start);
                  if (!entry) {
                        return result;
                  }

                  struct block {
                        luramas_address incomming_end = 0u;
                        std::shared_ptr<generation::cfg::block> curr_block = nullptr;
                        generation::cfg::block_kind edge = generation::cfg::block_kind::jump;
                  };

                  boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> visited;
                  std::vector<block> stack;

                  if (entry->jump) {
                        stack.emplace_back(block(entry->ending, entry->jump, generation::cfg::block_kind::jump));
                  }
                  if (entry->then) {
                        stack.emplace_back(block(entry->ending, entry->then, generation::cfg::block_kind::then));
                  }
                  if (entry->fall) {
                        stack.emplace_back(block(entry->ending, entry->fall, generation::cfg::block_kind::fall));
                  }
                  while (!stack.empty()) {

                        const auto curr = stack.back();
                        stack.pop_back();

                        if (!curr.curr_block || visited.contains(curr.curr_block)) {
                              continue;
                        }
                        visited.insert(curr.curr_block);
                        if (curr.curr_block->get_front() >= target || curr.curr_block->get_end() >= target) {
                              result.emplace_back(curr.edge, curr.incomming_end);
                              continue;
                        }

                        if (curr.curr_block->jump) {
                              stack.emplace_back(block(curr.curr_block->ending, curr.curr_block->jump, generation::cfg::block_kind::jump));
                        }
                        if (curr.curr_block->then) {
                              stack.emplace_back(block(curr.curr_block->ending, curr.curr_block->then, generation::cfg::block_kind::then));
                        }
                        if (curr.curr_block->fall) {
                              stack.emplace_back(block(curr.curr_block->ending, curr.curr_block->fall, generation::cfg::block_kind::fall));
                        }
                  }
                  return result;
            }

            void fence_region(generation::cfg::cfg &cfg, const luramas_blockrange &range, const bool include_end) {

                  boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> invalid;

                  for (const auto &b : cfg.blocks) {

                        if (contains::address(range, b->get_front()) || (include_end && contains::address(range, b->get_end()))) {
                              invalid.insert(b->then);
                        }

                        for (const auto &ptr : std::array<std::shared_ptr<generation::cfg::block> *, 3u>({&b->jump, &b->fall, &b->then})) {
                              if (auto &edge = *ptr; edge && (contains::address(range, edge->get_front()) || (include_end && contains::address(range, edge->get_end())))) {
                                    invalid.insert(edge);
                                    edge = nullptr;
                              }
                        }
                  }

                  if (!invalid.empty()) {
                        cfg.blocks.erase(std::remove_if(cfg.blocks.begin(), cfg.blocks.end(), [&](const auto &b) { return invalid.contains(b); }), cfg.blocks.end());
                  }
                  return;
            }

            std::vector<std::pair<generation::cfg::block_kind, std::shared_ptr<generation::cfg::block>>> jumps_out_range(const generation::cfg::cfg &cfg, const luramas_blockrange &range, const luramas_flag finclude_end) {

                  std::vector<std::pair<generation::cfg::block_kind, std::shared_ptr<generation::cfg::block>>> result;

                  boost::unordered_set<std::shared_ptr<generation::cfg::block>> visited;
                  std::vector<std::pair<generation::cfg::block_kind, std::shared_ptr<generation::cfg::block>>> on = {{generation::cfg::block_kind::none, cfg.visit(range.first)}};

                  while (!on.empty()) {

                        const auto [kind, curr] = on.back();
                        on.pop_back();

                        if (!curr || !visited.insert(curr).second) {
                              continue;
                        }

                        /* Add */
                        if (!tools::contains::address(range, curr->get_front()) || !tools::contains::address(range, curr->get_end() - 1u)) {
                              if (!on.empty() || finclude_end) {
                                    result.emplace_back(kind, curr);
                              }
                              continue;
                        }

                        /* Skip */
                        if (curr->get_end() == range.second) {
                              continue;
                        }

                        /* Log */
                        for (const auto &[k, b] : {std::make_pair(generation::cfg::block_kind::fall, curr->fall), std::make_pair(generation::cfg::block_kind::jump, curr->jump), std::make_pair(generation::cfg::block_kind::then, curr->then)}) {
                              if (b) {
                                    on.emplace_back(k, b);
                              }
                        }
                  }
                  return result;
            }

            std::vector<std::pair<generation::cfg::block_kind, std::shared_ptr<generation::cfg::block>>> accumulate_ranged_jumps_outs(const generation::cfg::cfg &cfg, const luramas_blockrange &range) {

                  std::vector<std::pair<generation::cfg::block_kind, std::shared_ptr<generation::cfg::block>>> result;

                  boost::unordered_set<std::shared_ptr<generation::cfg::block>> visited;
                  std::vector<std::pair<generation::cfg::block_kind, std::shared_ptr<generation::cfg::block>>> on = {{generation::cfg::block_kind::none, cfg.visit(range.first)}};

                  while (!on.empty()) {

                        const auto [kind, curr] = on.back();
                        on.pop_back();

                        if (!curr || !visited.insert(curr).second) {
                              continue;
                        }

                        /* Add */
                        result.emplace_back(kind, curr);

                        /* Skip */
                        if (!tools::contains::address(range, curr->get_front()) || !tools::contains::address(range, curr->get_end() - 1u)) {
                              continue;
                        }

                        /* Log */
                        for (const auto &[k, b] : {std::make_pair(generation::cfg::block_kind::fall, curr->fall), std::make_pair(generation::cfg::block_kind::jump, curr->jump), std::make_pair(generation::cfg::block_kind::then, curr->then)}) {
                              if (b) {
                                    on.emplace_back(k, b);
                              }
                        }
                  }
                  return result;
            }

            bool next_instruction_executed(luramas::ir::passes::pass_manager &pm, const luramas_address start) {

                  return !pm[start]->is_flow_interrupt() && !loops::infitely(pm, start);
            }
      } // namespace control_flow

} // namespace luramas::ir::tools