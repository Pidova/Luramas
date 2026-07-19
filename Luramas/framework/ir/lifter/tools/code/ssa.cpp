#include "../../passes/process/process.hpp"
#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::ssa {

      bool defined_scope(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const luramas_register target, const bool skip_current_scope) {

            if (!pm.contains(start)) {
                  return true;
            }

            auto curr_id = ssa.high_level_scope_id[start];
            if (curr_id && skip_current_scope) {
                  --curr_id;
            }
            for (auto i = static_cast<signed>(start); i >= 0; --i) {

                  const auto &stat = pm[i];
                  if (stat->is_paging()) {
                        break;
                  }

                  const auto on_id = ssa.high_level_scope_id[i];
                  if (curr_id < on_id) {
                        continue;
                  }

                  curr_id = on_id;
                  if (ssa.nodes[stat].l.assigns.contains(target)) {
                        return true;
                  }
            }
            return false;
      }
      bool defined_scope(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const std::shared_ptr<ir_stat::ir_expr> &target, const bool skip_current_scope) {

            return tools::exprs::values::is_reg(target) && defined_scope(pm, ssa, start, target->reg, skip_current_scope);
      }

      bool used(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const luramas_address end, const luramas_register target) {

            for (auto i = start; i < end; ++i) {
                  if (ssa.nodes[pm[i]].r.refrence_regs.contains(target)) {
                        return true;
                  }
            }
            return false;
      }
      bool used(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_blockrange &range, const luramas_register target) {
            return used(pm, ssa, range.first, range.second, target);
      }

      namespace extract {

            boost::unordered_flat_map<luramas_register, std::vector<luramas_blockrange>> same_assignments(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const std::vector<luramas_addresses> &blocks, const bool same_rvalues, const bool dominant) {

                  luramas_registers to_remove;
                  boost::unordered_flat_set<luramas_register> hit_registers;
                  boost::unordered_flat_set<luramas_register> removed_registers;
                  boost::unordered_flat_map<luramas_register, std::vector<luramas_blockrange>> result;

                  bool first_block = true;
                  for (const auto &block : blocks) {

                        for (auto it = block.rbegin(); it != block.rend(); ++it) {

                              for (const auto &[reg, ssa_data] : ssa.nodes[pm[*it]].l.assigns) {

                                    if ((!first_block && !hit_registers.contains(reg)) || removed_registers.contains(reg) || (dominant && hit_registers.contains(reg)) || !tools::stat::is_assignment(pm[*it])) {
                                          continue;
                                    }

                                    const auto [iter, inserted] = result.try_emplace(reg, std::vector<luramas_blockrange>{std::make_pair(*it, block.back())});
                                    if (!inserted) {
                                          if (same_rvalues && *pm[iter->second.back().first]->r != *pm[*it]->r) {
                                                continue;
                                          }
                                          iter->second.emplace_back(*it, block.back());
                                    }
                                    hit_registers.insert(reg);
                              }
                        }
                        for (const auto &[reg, data] : result) {
                              if (!hit_registers.contains(reg)) {
                                    to_remove.emplace_back(reg);
                                    removed_registers.insert(reg);
                              }
                        }
                        for (const auto &i : to_remove) {
                              result.erase(i);
                        }
                        to_remove.clear();
                        hit_registers.clear();
                        first_block = false;
                  }
                  return result;
            }

            std::vector<std::pair<luramas_address, luramas_blockrange>> block_assignment(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const std::vector<luramas_blockrange> &blocks, const luramas_register target, const hit_type type) {

                  std::vector<std::pair<luramas_address, luramas_blockrange>> result;
                  for (const auto &range : blocks) {

                        bool hit = false;
                        for (auto i = range.first; i < range.second; ++i) {

                              for (const auto &[reg, ssa_data] : ssa.nodes[pm[i]].l.assigns) {

                                    if (reg != target || (hit && type == hit_type::first)) {
                                          continue;
                                    }
                                    if (hit && type == hit_type::dominant) {
                                          result.pop_back();
                                    }

                                    hit = true;
                                    result.emplace_back(i, range);
                              }
                        }
                  }
                  return result;
            }
            std::vector<std::pair<luramas_address, luramas_blockrange>> block_assignment(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const std::vector<luramas_blockrange> &blocks, const boost::unordered_flat_set<luramas_register> &targets, const hit_type type) {

                  boost::unordered_flat_map<luramas_register, bool> hit_map;
                  std::vector<std::pair<luramas_address, luramas_blockrange>> result;
                  for (const auto &range : blocks) {

                        hit_map.clear();
                        for (const auto &r : targets) {
                              hit_map.try_emplace(r, false);
                        }

                        for (auto i = range.first; i < range.second; ++i) {

                              for (const auto &[reg, ssa_data] : ssa.nodes[pm[i]].l.assigns) {

                                    if (!targets.contains(reg) || (type == hit_type::first && hit_map[reg])) {
                                          continue;
                                    }
                                    if (type == hit_type::dominant && hit_map[reg]) {
                                          result.pop_back();
                                    }

                                    hit_map[reg] = true;
                                    result.emplace_back(i, range);
                              }
                        }
                  }
                  return result;
            }

            luramas_xregisters all_dominant_singletons(generation::ssa::ssa &ssa) {

                  luramas_xregisters result;

                  boost::unordered_flat_set<luramas_xregister> ignore;
                  for (const auto &[stat, node] : ssa.nodes) {

                        for (const auto &node : {node.l, node.r}) {

                              for (const auto &[linked, reg] : node.assigns) {

                                    if (!reg.second.empty()) {

                                          /* Get dominant */
                                          const auto skip = *std::min_element(reg.second.begin(), reg.second.end(), [&](const auto &a, const auto &b) {
                                                return ssa.high_level_scope_id[ssa.defs[a].second.first] < ssa.high_level_scope_id[ssa.defs[b].second.first];
                                          });

                                          /* Exclude rest */
                                          for (const auto &j : reg.second) {
                                                if (j != skip) {
                                                      ignore.insert(j);
                                                }
                                          }
                                    }
                              }
                        }
                  }

                  for (const auto &[ssa, node] : ssa.defs) {

                        if (!ignore.contains(ssa)) {
                              result.emplace_back(ssa);
                        }
                  }
                  return result;
            }

            std::optional<luramas_address> dominant_define(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const luramas_register target) {

                  if (!pm.contains(start)) {
                        return std::nullopt;
                  }

                  auto curr_id = ssa.high_level_scope_id[start];
                  for (const auto &i : luramas_riter(luramas_blockrange(0u, start - 1u))) {

                        const auto on_id = ssa.high_level_scope_id[i];
                        if (curr_id > on_id) {
                              return std::nullopt;
                        }
                        if (const auto &stat = pm[i]; tools::stat::is_assignment(stat)) {

                              const auto found = ssa.nodes[stat].l.assigns.contains(target);
                              if (curr_id < on_id) {
                                    if (found) {
                                          return std::nullopt;
                                    }
                                    continue;
                              }
                              if (found) {
                                    return i;
                              }
                        }
                        curr_id = on_id;
                  }
                  return std::nullopt;
            }

            std::optional<luramas_address> next_assignment_inscope_assignment(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const luramas_register target) {

                  const auto curr_id = ssa.high_level_scope_id[start];
                  for (auto i = start; i < pm.amount(); ++i) {

                        const auto id = ssa.high_level_scope_id[i];
                        if (curr_id > id) {
                              return std::nullopt;
                        }
                        if (curr_id == id) {
                              continue;
                        }
                        if (const auto &stat = pm[i]; tools::stat::is_assignment(stat) && ssa.nodes[stat].l.assigns.contains(target)) {
                              return i;
                        }
                  }
                  return std::nullopt;
            }

            std::optional<luramas_address> next_assignment_same_scope_assignment(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const luramas_register target) {

                  const auto curr_id = ssa.high_level_scope_id[start];
                  for (auto i = start + 1u; i < pm.amount(); ++i) {

                        const auto id = ssa.high_level_scope_id[i];
                        if (curr_id != id) {
                              return std::nullopt;
                        }
                        if (const auto &stat = pm[i]; tools::stat::is_assignment(stat) && ssa.nodes[stat].l.assigns.contains(target)) {
                              return curr_id == id ? std::optional<luramas_address>(i) : std::nullopt;
                        }
                  }
                  return std::nullopt;
            }

            std::optional<luramas_register> linked(const generation::ssa::ssa &ssa, const luramas_xregister ssa_reg) {

                  const auto def_it = ssa.defs.find(ssa_reg);
                  if (def_it == ssa.defs.end()) {
                        return std::nullopt;
                  }

                  const auto node_it = ssa.nodes.find(def_it->second.first);
                  if (node_it == ssa.nodes.end()) {
                        return std::nullopt;
                  }

                  for (const auto &[reg, def] : node_it->second.l.assigns) {
                        if (def.second.contains(ssa_reg)) {
                              return reg;
                        }
                  }
                  return std::nullopt;
            }

            boost::unordered_flat_map<luramas_xregister, std::optional<luramas_address>> parent_page(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa) {

                  boost::unordered_flat_map<luramas_xregister, std::optional<luramas_address>> result;
                  for (const auto &[ssa_reg, data] : ssa.defs) {
                        result[ssa_reg] = paging::parent_page(pm, data.second.first);
                  }
                  return result;
            }

            ir_stat::ir_expr::space exprs(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa, const luramas_xregister ssa_reg) {

                  ir_stat::ir_expr::space result;
                  luramas::ir::pass::process::values(pm);

                  const auto link = linked(ssa, ssa_reg);
                  if (!link) {
                        return result;
                  }

                  const auto def_it = ssa.defs.find(ssa_reg);
                  if (def_it == ssa.defs.end()) {
                        return result;
                  }

                  /* Lvalue */
                  for (const auto &i : pm.processed.values[def_it->second.first].lvalues) {
                        if (tools::exprs::values::is_reg(i, *link)) {
                              result.emplace_back(i);
                        }
                  }

                  for (const auto &i : boost::unordered_flat_set<luramas_address>(def_it->second.second.second.first.begin(), def_it->second.second.second.first.end())) {

                        const auto &stat = pm[i];
                        const auto &values = pm.processed.values[stat];

                        /* Rvalues */
                        for (const auto &j : values.rvalues) {
                              if (tools::exprs::values::is_reg(j, *link)) {
                                    result.emplace_back(j);
                              }
                        }
                        if (tools::stat::is_assignment(stat)) {

                              /* Go through mulret */
                              for (const auto &j : stat->members) {

                                    if (tools::exprs::values::is_reg(j, *link)) {
                                          continue;
                                    }
                                    for (const auto &k : j->extract_ordered_exprs()) {
                                          if (tools::exprs::values::is_reg(k, *link)) {
                                                result.emplace_back(k);
                                          }
                                    }
                              }
                              continue;
                        }
                        for (const auto &j : values.lvalues) {
                              if (tools::exprs::values::is_reg(j, *link)) {
                                    result.emplace_back(j);
                              }
                        }
                  }
                  return result;
            }
      } // namespace extract

      std::shared_ptr<luramas::ir::types::object::type> get_type(const std::shared_ptr<ir_stat::ir_expr> &expr, generation::ssa::ssa &ssa, const luramas_xregister ssa_reg) {

            if (!expr) {
                  return nullptr;
            }
            if (expr->non_native) {
                  return expr->non_native;
            }
            switch (expr->k) {
                  case expr_kinds::arith: {

                        if (tools::exprs::values::types::is_basic(expr->l->non_native) && tools::exprs::values::types::is_basic(expr->r->non_native)) {
                              return expr->l->non_native->basic_dominant(expr->r->non_native);
                        }
                        break;
                  }
                  case expr_kinds::reg: {

                        if (const auto it = ssa.defs.find(ssa_reg); it != ssa.defs.end()) {
                              const auto rv = it->second.first->r;
                              if (rv->non_native) {
                                    return rv->non_native;
                              }
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return nullptr;
      }

      luramas_registers all_undefined(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_address start, const boost::unordered_flat_set<luramas_register> &args) {

            luramas_registers result;

            const auto &n = pm[start];
            if (!stat::is_assignment(n) || n->flags.fvolatile) {
                  return result;
            }

            const auto &assigns = ssa.nodes[n].l.assigns;
            for (auto it = assigns.begin(); it != assigns.end(); ++it) {

                  const auto &[reg, data] = *it;
                  if (args.contains(reg) || (start && tools::ssa::defined_scope(pm, ssa, start - 1u, reg, false))) {
                        continue;
                  }

                  result.emplace_back(reg);
            }
            return result;
      }

      std::vector<std::optional<boost::unordered_flat_map<luramas_xregister, std::optional<luramas_address>>>> referenced_out_of_page(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa, const std::vector<std::optional<luramas_address>> &pages) {

            boost::unordered_flat_map<luramas_xregister, luramas_count> ndom_refs;
            std::vector<std::optional<boost::unordered_flat_map<luramas_xregister, std::optional<luramas_address>>>> result;

            for (auto i = 0u; i < pm.ir.data.size(); ++i) {

                  const auto &stat = pm[i];
                  std::optional<boost::unordered_flat_map<luramas_xregister, std::optional<luramas_address>>> curr = std::nullopt;

                  for (const auto &[linked, data] : ssa.nodes.at(stat).r.assigns) {

                        if (!curr.has_value()) {
                              curr.emplace();
                        }
                        for (const auto &ssa_reg : data.second) {

                              if (ssa_reg == generation::ssa::UNKNOWN_SSA_VERSION) {
                                    (*curr)[ssa_reg] = LURAMAS_IR_ENTRY;
                                    continue;
                              }
                              if (const auto it = ssa.defs.find(ssa_reg); it == ssa.defs.end()) {
                                    (*curr)[ssa_reg] = std::nullopt;
                              } else {
                                    if (const auto assign_p = pages[it->second.second.first]; pages[i] != assign_p) {
                                          (*curr)[ssa_reg] = assign_p;
                                    }
                              }
                        }
                  }
                  ndom_refs.clear();
                  result.emplace_back(curr);
            }
            return result;
      }

      std::vector<use_def_result> use_def_chain(const generation::ssa::ssa &ssa, const luramas_xregister target, const luramas_address limit) {

            boost::unordered_flat_set<luramas_xregister> visited;
            std::vector<use_def_result> result;

            luramas_xregisters targets = {target};
            while (!targets.empty()) {

                  const auto t = targets.back();
                  if (targets.pop_back(); !visited.insert(t).second) {
                        continue;
                  }

                  /* Defs */
                  const auto dit = ssa.defs.find(t);
                  if (dit == ssa.defs.end()) {
                        continue;
                  }

                  /* Out of range */
                  if (dit->second.second.first < limit) {
                        continue;
                  }

                  /* Nodes */
                  const auto nit = ssa.nodes.find(dit->second.first);
                  if (nit == ssa.nodes.end()) {
                        continue;
                  }
                  for (const auto &[rssa, d] : nit->second.r.assigns) {

                        use_def_result res;
                        res.k = d.first;
                        if (res.k == generation::ssa::assignment_kind::single) {
                              res.scalar = *d.second.begin();
                              targets.emplace_back(res.scalar);
                        } else {
                              res.phis.emplace();
                              (*res.phis).insert((*res.phis).begin(), d.second.begin(), d.second.end());
                              targets.insert(targets.begin(), d.second.begin(), d.second.end());
                        }
                        result.emplace_back(res);
                  }
            }
            return result;
      }

      bool is_placeholder_variable(luramas::ir::passes::pass_manager &pm, generation::ssa::ssa &ssa, const luramas_xregister target, const luramas_address start) {

            /* Defs */
            const auto dit = ssa.defs.find(target);
            if (dit == ssa.defs.end()) {
                  return false;
            }

            const auto linked = tools::ssa::extract::linked(ssa, target);
            if (!linked) {
                  return false;
            }
            const auto end = tools::common::safe_block_end(pm, start + 1u);
            const auto curr_id = ssa.high_level_scope_id[start];

            /* Check high level scop ID if changes back in return false */
            for (const auto &i : luramas_iter(luramas_blockrange(start + 1u, end))) {

                  if (tools::stat::is_assignment(pm[i], *linked)) {
                        return ssa.high_level_scope_id[i] != curr_id;
                  }
            }
            return false;
      }

} // namespace luramas::ir::tools::ssa