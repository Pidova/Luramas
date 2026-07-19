
#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::contains {

      bool refs(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &block_1, const luramas_blockrange &block_2) {

            boost::unordered_flat_set<luramas_address> labels;

            for (const auto &i : accumulate::keyword(pm, block_1, keywords::label)) {
                  labels.insert(pm[i]->label);
            }
            for (const auto &i : accumulate::keyword(pm, block_2, keywords::label)) {
                  labels.insert(pm[i]->label);
            }

            for (const auto &i : luramas_iter(block_1)) {
                  if (const auto &stat = pm[i]; stat::branch::is_goto_basic(stat) && labels.contains(stat->jlabel)) {
                        return true;
                  }
            }
            for (const auto &i : luramas_iter(block_2)) {
                  if (const auto &stat = pm[i]; stat::branch::is_goto_basic(stat) && labels.contains(stat->jlabel)) {
                        return true;
                  }
            }
            return false;
      }

      bool refs(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range, const luramas_address jlabel) {

            for (const auto &i : luramas_iter(range)) {
                  if (stat::common::is_ref(pm[i], jlabel)) {
                        return true;
                  }
            }
            return false;
      }

      bool unconditional_block(luramas::ir::passes::pass_manager &pm, const std::vector<luramas_blockrange> &blocks) {

            for (const auto &[start, end] : blocks) {
                  if (pm.contains(start) && tools::stat::branch::is_unconditional(pm[start])) {
                        return true;
                  }
            }
            return false;
      }
      bool unconditional_block(luramas::ir::passes::pass_manager &pm, const luramas_addresses &blocks) {

            for (const auto &start : blocks) {
                  if (pm.contains(start) && tools::stat::branch::is_unconditional(pm[start])) {
                        return true;
                  }
            }
            return false;
      }

      namespace orphans {

            bool loop_orphan_manager(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range, auto &&predicate) {

                  boost::unordered_flat_set<luramas_address> loop_ends;
                  for (const auto &i : luramas_iter(range)) {
                        loop_ends.erase(i);

                        const auto &stat = pm[i];
                        if (stat->is_loop()) {
                              loop_ends.insert(tools::common::safe_take_jump(pm, i));
                        }
                        if (loop_ends.empty() && predicate(pm, stat)) {
                              return true;
                        }
                  }
                  return false;
            }

            bool implicit_goto(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {

                  return loop_orphan_manager(pm, range, [](luramas::ir::passes::pass_manager &pm, const auto &stat) { return stat->is_implicit_flow_interrupt(); });
            }

            bool loop_end(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {

                  return loop_orphan_manager(pm, range, [](luramas::ir::passes::pass_manager &pm, const auto &stat) { return tools::stat::branch::is_loop_end(pm, stat); });
            }

            bool pages(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {

                  boost::unordered_flat_map<luramas_id, std::pair<bool, bool>> pages;
                  for (const auto &i : luramas_iter(range)) {

                        const auto &stat = pm[i];
                        if (stat::is_page_function_start(stat)) {
                              auto &page = pages[stat->r->extract_integral_base()];
                              page.first = !page.first;
                        }
                        if (stat::is_page_function_end(stat)) {
                              auto &page = pages[stat->r->extract_integral_base()];
                              page.second = !page.second;
                        }
                  }
                  for (const auto &[id, page] : pages) {
                        if (!page.first || !page.second) {
                              return true;
                        }
                  }
                  return false;
            }

      } // namespace orphans

      namespace implicit {

            bool break_to(luramas::ir::passes::pass_manager &pm, const luramas_addresses &data, const luramas_address target_loop) {
                  return std::any_of(data.begin(), data.end(), [&](const auto &loc) { return tools::common::breaks_to_loop(pm, pm[loc], target_loop); });
            }

            bool continues_to(luramas::ir::passes::pass_manager &pm, const luramas_addresses &data, const luramas_address target_loop) {
                  return std::any_of(data.begin(), data.end(), [&](const auto &loc) { return tools::common::continues_to_loop(pm, pm[loc], target_loop); });
            }

            bool any_to(luramas::ir::passes::pass_manager &pm, const luramas_addresses &data, const luramas_address target_loop) {
                  return std::any_of(data.begin(), data.end(), [&](const auto &loc) { return tools::common::continues_to_loop(pm, pm[loc], target_loop) || tools::common::breaks_to_loop(pm, pm[loc], target_loop); });
            }
      } // namespace implicit

      bool if_cond_else(luramas::ir::passes::pass_manager &pm, const luramas_address if_cond_loc) {
            return pm.contains(if_cond_loc) && stat::branch::is_if_cond(pm[if_cond_loc]) && violations::block_violates(pm, if_cond_loc + 1u, pm.amount()).reason == violations::block_violation_exceptions::invalid_else_conditional;
      }

      bool address(const luramas_blockrange &range, const luramas_address n) {
            return n >= range.first && n < range.second;
      }

      bool safe_label(luramas::ir::passes::pass_manager &pm, const luramas_address start, const std::shared_ptr<ir_stat> &label) {
            return tools::stat::is_label(label) && violations::block_violates(pm, start, pm.amount(), violations::block_violates_flags({.close_on = label})).reason == violations::block_violation_exceptions::hit_closing_on;
      }

      bool is(const ir_stat::ir_expr::space &v, const data::cb_tkind &cb) {
            for (const auto &i : v) {
                  if (cb(i->tk)) {
                        return true;
                  }
            }
            return false;
      }
      bool is(const ir_stat::ir_expr::space &v, const data::cb_kinds &cb) {
            for (const auto &i : v) {
                  if (cb(i->k)) {
                        return true;
                  }
            }
            return false;
      }
      bool is(const ir_stat::ir_expr::space &v, const data::cb_bkinds &cb) {
            for (const auto &i : v) {
                  if (cb(i->b) || cb(i->u)) {
                        return true;
                  }
            }
            return false;
      }
      bool is(const ir_stat::space &v, const data::cb_keywords &cb) {
            for (const auto &i : v) {
                  if (cb(i->k)) {
                        return true;
                  }
            }
            return false;
      }
} // namespace luramas::ir::tools::contains