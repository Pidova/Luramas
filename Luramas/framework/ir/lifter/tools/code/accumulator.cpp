#include "../../passes/includes/common.hpp"
#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::accumulate {

      luramas_vaddresses paths(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &block) {

            luramas_vaddresses result;
            for (auto i = block.first; i < block.second; ++i) {

                  const auto &stat = pm[i];
                  if (stat::branch::is_goto_basic(stat)) {

                        result.emplace_back(common::safe_take_jump(pm, i));
                  }
                  if (stat->is_terminal()) {

                        result.emplace_back(-1);
                  } else if (i == block.second - 1u) {

                        result.emplace_back(-2);
                  }
            }
            return result;
      }

      luramas_addresses jump_outs(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &block) {

            luramas_addresses result;
            for (auto i = block.first; i < block.second; ++i) {

                  const auto &stat = pm[i];
                  if (stat::branch::is_goto_basic(stat) && !treshold(common::safe_take_jump(pm, i), block)) {

                        result.emplace_back(i);
                  }
            }
            return result;
      }

      luramas_addresses refs(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range, const luramas_address jlabel) {

            luramas_addresses result;
            for (auto i = range.first; i < range.second; ++i) {

                  if (!pm.contains(i)) {
                        break;
                  }
                  if (const auto &e = pm[i]; stat::common::is_ref(e, jlabel)) {
                        result.emplace_back(i);
                  }
            }
            return result;
      }

      luramas_addresses dominant(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end) {

            luramas_addresses result;
            for (auto i = start; i < end; ++i) {
                  result.emplace_back(i);
                  tools::stat::safe_jump_end(pm, i, i);
            }
            return result;
      }

      std::vector<luramas_addresses> dominant(luramas::ir::passes::pass_manager &pm, const std::vector<luramas_blockrange> &v) {

            std::vector<luramas_addresses> result;
            for (const auto &[start, end] : v) {
                  result.emplace_back(dominant(pm, start + 1u, end));
            }
            return result;
      }

      std::vector<luramas_addresses> dominant(luramas::ir::passes::pass_manager &pm, const luramas_address start) {
            return accumulate::dominant(pm, extract::blocks(pm, start));
      }

      luramas_addresses keyword(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &block, const keywords specifier) {

            luramas_addresses result;
            for (auto i = block.first; i < block.second; ++i) {

                  if (pm[i]->is_k(specifier)) {
                        result.emplace_back(i);
                  }
            }
            return result;
      }
      std::vector<luramas_addresses> keyword(luramas::ir::passes::pass_manager &pm, const std::vector<luramas_addresses> &blocks, const keywords specifier) {

            std::vector<luramas_addresses> result;
            result.reserve(blocks.size());

            for (const auto &v : blocks) {

                  luramas_addresses keyword_blocks;
                  keyword_blocks.reserve(v.size());
                  for (const auto &i : v) {
                        if (pm[i]->is_k(specifier)) {
                              keyword_blocks.emplace_back(i);
                        }
                  }
                  result.emplace_back(keyword_blocks);
            }
            return result;
      }

      luramas_addresses reverse_dominant(luramas::ir::passes::pass_manager &pm, const luramas_address start) {

            luramas_addresses result;
            result.reserve(start / 2u);
            for (auto i = start;; --i) {

                  const auto &e = pm[i];
                  result.emplace_back(i);

                  if (tools::stat::branch::is_goto_past(pm, e, i)) {
                        i = tools::common::safe_take_jump(pm, i);
                  }
                  if (const auto rev = tools::common::reverse_safe_take_jump(pm, i); rev != i) {
                        i = rev;
                        result.emplace_back(i);
                  }
                  if (!i) {
                        break;
                  }
            }
            return result;
      }

      luramas_addresses parent_loops(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end) {

            luramas_addresses result;
            for (const auto &[loc, stat] : tools::trackers::unfinished_condition(pm, start, end)) {

                  if (stat->is_loop()) {
                        result.emplace_back(loc);
                  } else if (tools::stat::branch::is_loop_end(pm, stat)) {
                        result.emplace_back(pm.processed.end_labels[stat->end_label].first);
                  }
            }
            return result;
      }

      luramas_addresses explicit_jump_past(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end) {

            luramas_addresses result;
            for (auto i = start; i < end; ++i) {
                  switch (pm[i]->k) {
                        case keywords::goto_label:
                        case keywords::condition_goto: {
                              const auto jmp = tools::common::safe_take_jump(pm, i);
                              if (jmp > end) {
                                    result.emplace_back(i);
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
            return result;
      }

      luramas_addresses goto_labels(luramas::ir::passes::pass_manager &pm, const luramas_addresses &addresses) {

            luramas_addresses result;
            result.reserve(addresses.size());

            for (const auto &i : addresses) {

                  if (!pm.contains(i)) {
                        continue;
                  }
                  result.emplace_back(tools::common::safe_take_jump(pm, i));
            }
            return result;
      }

      luramas_addresses break_outs(luramas::ir::passes::pass_manager &pm, const luramas_address loop_start) {

            luramas_addresses result;
            if (!pm.contains(loop_start) || !pm[loop_start]->is_loop()) {
                  return result;
            }

            const auto end = common::safe_take_jump(pm, loop_start);
            for (auto i = loop_start; i < end; ++i) {
                  switch (pm[i]->k) {
                        case keywords::goto_label:
                        case keywords::condition_goto:
                        case keywords::break_: {
                              if (const auto jmp = common::safe_take_jump(pm, i); jmp >= end || loop_start > jmp) {
                                    result.emplace_back(i);
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
            return result;
      }

      boost::unordered_flat_map<luramas_address, luramas_addresses> labels(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {

            boost::unordered_flat_map<luramas_address, luramas_addresses> result;
            for (auto i = range.first; i < range.second; ++i) {

                  if (!pm.contains(i)) {
                        break;
                  }
                  if (const auto &stat = pm[i]; stat && stat->is_goto_label()) {
                        result[common::safe_take_jump(pm, i)].emplace_back(i);
                  }
            }
            return result;
      }

      ir_stat::ir_expr::space page_arg(luramas::ir::passes::pass_manager &pm, const luramas_id page, const luramas_index idx) {

            ir_stat::ir_expr::space result;

            luramas::ir::pass::process::values(pm);

            for (const auto &[s, exps] : pm.processed.values) {

                  if ((stat::is_page_function_jump(s, page) || stat::is_page_function_call(s, page)) && s->members.size() > idx) {

                        result.emplace_back(s->members[idx]);
                  }
                  for (const auto &i : exps.all) {

                        if (exprs::values::is_page_function_call(i, page) && s->members.size() > idx) {

                              result.emplace_back(s->members[idx]);
                        }
                  }
            }
            return result;
      }

      namespace orphans {

            luramas_addresses implicit_gotos(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {

                  luramas_addresses result;
                  boost::unordered_flat_set<luramas_address> loop_ends;
                  for (auto i = range.first; i < range.second; ++i) {

                        loop_ends.erase(i);
                        const auto &stat = pm[i];
                        if (stat->is_loop()) {
                              loop_ends.insert(tools::common::safe_take_jump(pm, i));
                        }
                        if (loop_ends.empty() && stat->is_implicit_flow_interrupt()) {
                              result.emplace_back(i);
                        }
                  }
                  return result;
            }

            luramas_addresses page_declaration(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {

                  luramas_addresses result;
                  std::map<luramas_id, luramas_address> contained_pages;
                  for (auto i = range.first; i < range.second; ++i) {

                        const auto &stat = pm[i];
                        if (tools::stat::is_page_function_start(stat)) {
                              contained_pages[stat->r->extract_integral_base()] = i;
                        }
                        if (tools::stat::is_page_function_end(stat)) {
                              if (const auto it = contained_pages.find(stat->r->extract_integral_base()); it != contained_pages.end()) {
                                    contained_pages.erase(it);
                              } else {
                                    result.emplace_back(i);
                              }
                        }
                  }
                  for (const auto &[_, i] : contained_pages) {
                        result.emplace_back(i);
                  }
                  return result;
            }
      } // namespace orphans
} // namespace luramas::ir::tools::accumulate