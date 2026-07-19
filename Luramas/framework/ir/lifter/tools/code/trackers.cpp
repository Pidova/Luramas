#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::trackers {

      std::vector<std::pair<luramas_address, std::shared_ptr<ir_stat>>> unfinished_condition(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end, const bool forward) {

            std::vector<std::pair<luramas_address, std::shared_ptr<ir_stat>>> result;
            if ((forward && start >= end) || (!forward && start <= end)) {
                  return result;
            }

            std::vector<std::pair<luramas_address, std::shared_ptr<ir_stat>>> end_cond_stack;
            std::vector<std::pair<luramas_address, std::shared_ptr<ir_stat>>> until_cond_stack;
            for (auto o = start; forward ? o < end : o > end; forward ? ++o : --o) {
                  const auto &d = pm[o];
                  const auto s = stat::branch::condition_stack(d);
                  if (s > 0) {
                        const auto p = std::make_pair(o, d);
                        if (stat::branch::expects_until(d)) {
                              until_cond_stack.emplace_back(p);
                        } else {
                              end_cond_stack.emplace_back(p);
                        }
                  } else if (s < 0) {
                        if (d->is_k<keywords::end>()) {
                              if (!end_cond_stack.empty() && end_cond_stack.back().second->end_label == d->end_label) {
                                    end_cond_stack.pop_back();
                              } else {
                                    result.emplace_back(o, d);
                              }
                        } else {
                              if (!until_cond_stack.empty() && until_cond_stack.back().second->end_label == d->end_label) {
                                    until_cond_stack.pop_back();
                              } else {
                                    result.emplace_back(o, d);
                              }
                        }
                  }
            }

            result.reserve(result.size() + end_cond_stack.size() + until_cond_stack.size());
            std::copy(end_cond_stack.begin(), end_cond_stack.end(), std::back_inserter(result));
            std::copy(until_cond_stack.begin(), until_cond_stack.end(), std::back_inserter(result));
            return result;
      }

      luramas_address loop_break(luramas::ir::passes::pass_manager &pm, const luramas_address start) {

            return (!pm.valid(start) || !tools::stat::is_break(pm[start])) ? 0u : tools::common::safe_take_jump(pm, start);
      }
      luramas_address loop_continue(luramas::ir::passes::pass_manager &pm, const luramas_address start) {

            return (!pm.valid(start) || !tools::stat::is_continue(pm[start])) ? 0u : tools::common::safe_take_jump(pm, start);
      }

      luramas_address else_end(luramas::ir::passes::pass_manager &pm, const luramas_address start) {

            if (!pm.valid(start) || !tools::stat::branch::is_else_conditional(pm[start])) {
                  return 0u;
            }

            std::intptr_t stack = 0;
            for (auto o = start; o < pm.amount(); ++o) {
                  stack += stat::branch::condition_stack(pm[o]);
                  if (stack < 0) {
                        return o;
                  }
            }
            return 0u;
      }

      luramas_address relative_scope(luramas::ir::passes::pass_manager &pm, const luramas_address most_out_scope, generation::cfg::cfg *cfg) {

            static generation::cfg::cfg c;
            if (!cfg) {
                  c = generation::cfg::generate(pm.ir, LURAMAS_IR_ENTRY, pm.env_flags.fhas_pages);
                  cfg = &c;
            }
            const auto contiguous = cfg->contiguous_firstlast_scopeid(cfg->highlevel_scope_ids[most_out_scope + 1u]);
            return contiguous > most_out_scope ? 0u : contiguous;
      }

      luramas_address next_safe_executable(luramas::ir::passes::pass_manager &pm, luramas_address start, const bool include_implicit_gotos, const luramas_vaddress expecting_goto) {
            const auto t_start = start;
            if (!pm.contains(start + 1u)) {
                  return start;
            }
            while (pm.contains(start)) {

                  const auto &e = pm[++start];
                  if (!e) {
                        break;
                  }
                  if (tools::stat::branch::is_else_conditional(e)) {
                        start = tools::trackers::else_end(pm, start);
                  } else if (stat::branch::is_goto(e) || (include_implicit_gotos && tools::stat::is_break(e))) {

                        const auto taken = tools::common::safe_take_jump(pm, start);
                        if (expecting_goto == taken || taken < start) {
                              break;
                        }
                        start = taken;
                  }
                  if (tools::stat::branch::is_loop_end(pm, pm[start]) || !tools::stat::is_end(pm[start])) {
                        break;
                  }
            }
            return !pm.contains(start) ? t_start : start;
      }

      luramas_blockrange parent_loop(luramas::ir::passes::pass_manager &pm, const luramas_address start) {

            if (!pm.contains(start)) {
                  return std::make_pair(0u, 0u);
            }
            if (pm[start]->is_loop()) {
                  return std::make_pair(start, tools::common::safe_take_jump(pm, start));
            }

            std::size_t stack = 0u;
            for (auto o = start; o < pm.amount(); ++o) {

                  if (const auto &d = pm[o]; d->is_loop()) {
                        ++stack;
                  } else if (tools::stat::branch::is_loop_end(pm, d)) {
                        if (stack) {
                              --stack;
                        } else {
                              return std::make_pair(pm.processed.end_labels[d->end_label].first, o);
                        }
                  }
            }
            return std::make_pair(0u, 0u);
      }

      std::pair<bool, luramas_address> safe_trace_page(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_id id, const bool include_end) {

            for (auto o = start; o < pm.amount(); ++o) {

                  if (const auto &d = pm[o]; tools::stat::is_page_function_start(d) || (include_end && tools::stat::is_page_function_end(d))) {

                        if (d->r && d->r->is_integral(id)) {
                              return {true, o};
                        }
                  } else {
                        break;
                  }
            }
            return {false, 0u};
      }

      luramas_address ending_parent_loop(luramas::ir::passes::pass_manager &pm, const luramas_address loop_end) {
            return !pm.contains(loop_end) || !stat::branch::is_loop_end(pm, pm[loop_end]) ? 0u : pm.processed.end_labels[pm[loop_end]->end_label].first;
      }

      luramas_address next_safe_executable(luramas::ir::passes::pass_manager &pm, luramas_address start, const boost::unordered_flat_set<keywords> &k, const bool include_implicit_gotos, const luramas_vaddress expecting_goto) {

            auto next = next_safe_executable(pm, start, include_implicit_gotos, expecting_goto);
            while (k.contains(pm[next]->k)) {
                  const auto tnext = next_safe_executable(pm, next, include_implicit_gotos, expecting_goto);
                  if (tnext == next) {
                        return next;
                  }
                  next = tnext;
            };
            return next;
      }
} // namespace luramas::ir::tools::trackers