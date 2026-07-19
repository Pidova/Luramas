#include "../../generation/cfg/sort.hpp"
#include "../extras/stats.hpp"
#include "../tools.hpp"
#include <queue>

namespace luramas::ir::tools::extract {

      std::vector<luramas_blockrange> blocks(luramas::ir::passes::pass_manager &pm, const luramas_address start) {

            std::vector<luramas_blockrange> result;
            if (!pm.contains(start) || !pm[start]->is_scopeable()) {
                  return result;
            }

            result.emplace_back(start, violations::block_violates(pm, start + 1u, pm.amount()).ending_loc);

            while (tools::stat::branch::is_else_conditional(pm[result.back().second])) {
                  const auto start = result.back().second;
                  result.emplace_back(start, violations::block_violates(pm, start + 1u, pm.amount()).ending_loc);
            }
            return result;
      }

      std::vector<luramas_blockrange> parent_ifcond_blocks(luramas::ir::passes::pass_manager &pm, const luramas_address loc) {

            luramas_address buffer = 0u;
            return tools::visitors::parent_ifcond(pm, loc, buffer) ? extract::blocks(pm, buffer) : std::vector<luramas_blockrange>();
      }

      std::vector<luramas_addresses> dominate_blocks(luramas::ir::passes::pass_manager &pm, const luramas_address start) {

            std::vector<luramas_addresses> result;
            for (const auto &[start, end] : extract::blocks(pm, start)) {
                  result.emplace_back(accumulate::dominant(pm, start + 1u, end));
            }
            return result;
      }

      std::shared_ptr<ir_stat::ir_expr> base_expr(const std::shared_ptr<ir_stat::ir_expr> &expr) {

            switch (expr->k) {
                  case expr_kinds::unary: {
                        return expr->l;
                  }
                  default: {
                        break;
                  }
            }
            return nullptr;
      }

      luramas_addresses cond_conditions(luramas::ir::passes::pass_manager &pm, const luramas_address start) {

            luramas_addresses result;
            for (const auto &[start, end] : blocks(pm, start)) {
                  result.emplace_back(start - 1u);
            }
            return result;
      }

      std::vector<std::shared_ptr<ir_stat::ir_expr>> closures(luramas::ir::passes::pass_manager &pm, const bool deep) {

            std::vector<std::shared_ptr<ir_stat::ir_expr>> result;
            boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> visited;

            std::vector<ir_stat::space> closures = {pm.ir.data};
            do {

                  const auto curr = closures.back();
                  closures.pop_back();
                  for (const auto &i : pm.ir.data) {

                        for (const auto &expr : i->extract_ordered_deep_exprs()) {

                              if (!expr->closure.empty() && !visited.emplace(expr).second) {

                                    if (deep) {
                                          closures.emplace_back(expr->closure);
                                    }
                                    result.emplace_back(expr);
                              }
                        }
                  }
            } while (!closures.empty());
            return result;
      }

      ir_stat::space space(passes::pass_manager &pm, const luramas_blockrange &range) {

            ir_stat::space result;
            if (!pm.contains(range.first) || !pm.contains(range.second)) {
                  return result;
            }
            if (range.second > range.first) {
                  result.reserve(range.second - range.first);
            }
            for (const auto &i : luramas_iter(range)) {
                  result.emplace_back(pm[i]);
            }
            return result;
      }

      luramas_registers assignment_regs(const std::shared_ptr<ir_stat> &assignment_stat) {

            luramas_registers result;
            if (!tools::stat::is_assignment(assignment_stat)) {
                  return result;
            }

            if (assignment_stat->l && assignment_stat->l->is_register_reference()) {
                  result.emplace_back(assignment_stat->l->reg);
            }
            for (const auto &e : assignment_stat->members) {
                  if (e && e->is_register_reference()) {
                        result.emplace_back(e->reg);
                  }
            }
            return result;
      }

      namespace space_stat {

            ir_stat::space unresolved_gotos(const ir_stat::space &space) {

                  ir_stat::space result;

                  boost::unordered_flat_set<luramas_address> labels;
                  boost::unordered_flat_map<luramas_address, std::shared_ptr<ir_stat>> jlabels;

                  for (const auto &i : space) {
                        if (i->is_goto_label()) {
                              jlabels[i->jlabel] = i;
                        }
                        if (tools::stat::is_label(i)) {
                              labels.insert(i->label);
                        }
                  }
                  for (const auto &[target, stat] : jlabels) {
                        if (const auto it = labels.find(target); it == labels.end()) {
                              result.emplace_back(stat);
                        }
                  }
                  return result;
            }

            ir_stat::space extract(const ir_stat::space &space, const keywords k) {

                  ir_stat::space result;

                  for (const auto &i : space) {
                        if (i->is_k(k)) {
                              result.emplace_back(i);
                        }
                  }
                  return result;
            }

            ir_stat::ir_expr::space upvalues(const ir_stat::space &space) {

                  ir_stat::ir_expr::space result;

                  boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> upvalues;
                  for (const auto &i : space) {
                        for (const auto &expr : i->extract_exprs()) {
                              if (tools::exprs::values::is_upvalue(expr)) {
                                    upvalues.insert(expr);
                              }
                        }
                  }
                  result.reserve(result.size() + upvalues.size());
                  result.insert(result.begin(), upvalues.begin(), upvalues.end());
                  return result;
            }
      } // namespace space_stat

      namespace ir {

            std::set<luramas_register> lazy_undefined_registers(se_ir &ir, const boost::unordered_flat_set<luramas_register> &upvalues) {

                  std::set<luramas_register> result;

                  std::vector<luramas_registers> sources;
                  std::vector<luramas_registers> dests;
                  std::vector<ir_stat::ir_expr::space> captures;

                  dests.reserve(ir.data.size());
                  sources.reserve(ir.data.size());
                  for (const auto &i : ir.data) {
                        dests.emplace_back(i->extract_ordered_dest_regs());
                        sources.emplace_back(i->extract_ordered_source_regs());
                        captures.emplace_back(!sources.empty() ? i->extract_ordered_source_captures() : ir_stat::ir_expr::space());
                  }

                  const auto cfg = generation::cfg::generate(ir, LURAMAS_IR_ENTRY, ir.fhas_pages);
                  const auto dominants = cfg::sort::dominant(cfg);

                  boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, boost::unordered_flat_set<luramas_register>> block_data;
                  block_data.reserve(dominants.size());

                  for (auto idx = 0u; idx < dominants.size(); ++idx) {

                        const auto &block = dominants[idx];

                        /* Get undefined in block */
                        auto &data = block_data[block];
                        for (const auto &loc : block->get_iter()) {

                              const auto &dest = dests[loc];
                              const auto &source = sources[loc];

                              /* If source is capture but is dest in same stat without used again its defined */
                              if (const auto &capture = captures[loc]; !capture.empty()) {
                                    for (const auto &s : source) {
                                          if (std::find(dest.begin(), dest.end(), s) != dest.end() &&
                                              static_cast<std::size_t>(std::count(source.begin(), source.end(), s)) <= luramas::ir::tools::exprs::count(capture, s)) {
                                                data.insert(s);
                                          }
                                    }
                              }
                              for (const auto &s : source) {
                                    if (!data.contains(s) && !upvalues.contains(s)) {
                                          result.insert(s);
                                    }
                              }
                              data.insert(dest.begin(), dest.end());
                        }

                        /* Propagate  */
                        for (auto t_idx = idx + 1u; t_idx < dominants.size(); ++t_idx) {

                              const auto &t_block = dominants[t_idx];
                              if (cfg.highlevel_scope_ids[t_block->get_front()] < cfg.highlevel_scope_ids[block->get_front()]) {
                                    break;
                              }
                              block_data[t_block].insert(data.begin(), data.end());
                        }
                  }
                  return result;
            }
      } // namespace ir

      namespace stats {

            boost::unordered_flat_map<luramas_register, boost::unordered_flat_set<expr_kinds>> all_reg_doms(const std::shared_ptr<ir_stat> &curr) {

                  boost::unordered_flat_map<luramas_register, boost::unordered_flat_set<expr_kinds>> result;

                  auto stack = curr->extract_shallow_ordered_exprs();
                  while (!stack.empty()) {

                        const auto e = stack.back();
                        stack.pop_back();

                        if (tools::exprs::values::is_reg(e)) {
                              result[e->reg].insert(e->k);
                        }

                        e->extract_shallow_ordered_exprs(stack);
                  }
                  return result;
            }
      } // namespace stats

      namespace exprs {

            std::vector<std::shared_ptr<ir_stat::ir_expr>> path(const std::shared_ptr<ir_stat::ir_expr> &start, const std::shared_ptr<ir_stat::ir_expr> &target) {

                  std::vector<std::shared_ptr<ir_stat::ir_expr>> result;
                  if (!start || !target) {
                        return result;
                  }

                  ir_stat::ir_expr::space extraction;
                  boost::unordered_flat_map<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat::ir_expr>> parent;
                  std::queue<std::shared_ptr<ir_stat::ir_expr>> q;
                  q.push(start);
                  parent[start] = nullptr;

                  while (!q.empty()) {

                        auto curr = q.front();
                        q.pop();

                        if (curr == target) {
                              for (auto p = curr; p; p = parent[p]) {
                                    result.emplace_back(p);
                              }
                              std::reverse(result.begin(), result.end());
                              return result;
                        }

                        extraction.clear();
                        curr->extract_shallow_ordered_exprs(extraction);
                        for (const auto &i : extraction) {
                              if (!parent.contains(i)) {
                                    parent[i] = curr;
                                    q.push(i);
                              }
                        }
                  }
                  return result;
            }
      } // namespace exprs

} // namespace luramas::ir::tools::extract