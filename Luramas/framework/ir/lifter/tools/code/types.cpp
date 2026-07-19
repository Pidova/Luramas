
#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::types {

      extraction extract_expr_type(const std::shared_ptr<ir_stat::ir_expr> &expr) {

            extraction result(expr);
            if (tools::exprs::values::is_cast(expr) || tools::exprs::values::is_memoryread(expr) ||
                tools::exprs::values::is_bitread(expr) || tools::exprs::values::is_bitwrite(expr) ||
                tools::exprs::values::types::is_virtualized_function_rtype(expr)) {
                  result.emit(tools::exprs::values::types::has_xtype(expr) ? expr->xtype : expr->non_native);
            }
            if (tools::exprs::values::is_reg(expr) && expr->non_native) {
                  result.emit(expr->non_native);
            }
            if (tools::exprs::values::is_general_purpose_register(expr)) {
                  result.emit(expr->reg);
            }
            return result;
      }

      extraction_result extract(const std::shared_ptr<ir_stat::ir_expr> &expr) {

            extraction_result result;

            std::vector<std::shared_ptr<ir_stat::ir_expr>> pending = {expr};
            pending.reserve(LURAMAS_PREDICTED_RECURSION);

            while (!pending.empty()) {

                  const auto curr = pending.back();
                  pending.pop_back();
                  if (!curr) {
                        continue;
                  }

                  if (const auto t = extract_expr_type(curr); !t.empty()) {
                        result.emplace_back(t);
                        continue;
                  }

                  pending.emplace_back(curr->l);
                  pending.emplace_back(curr->r);
                  pending.emplace_back(curr->ev);
                  pending.emplace_back(curr->xv);
                  for (const auto &m : curr->captures) {
                        pending.emplace_back(m);
                  }
                  for (const auto &m : curr->members) {
                        pending.emplace_back(m);
                  }
                  for (const auto &[i, v] : curr->tmembers) {
                        if (i) {
                              pending.emplace_back(i);
                        }
                        if (v) {
                              pending.emplace_back(v);
                        }
                  }
            };
            return result;
      }
      std::vector<std::shared_ptr<ir::types::object::type>> extract(const std::shared_ptr<ir_stat> &parent_stat, const std::shared_ptr<ir_stat::ir_expr> &expr, const generation::ssa::ssa &ssa, const boost::unordered_flat_map<luramas_xregister, std::shared_ptr<ir::types::object::type>> &ssa_types) {

            std::vector<std::shared_ptr<ir::types::object::type>> result;
            for (const auto &t : extract(expr)) {
                  switch (t.t) {
                        case extraction_kind::type: {
                              result.emplace_back(t.type);
                              break;
                        }
                        case extraction_kind::reg: {

                              const auto it = ssa.nodes.find(parent_stat);
                              if (it == ssa.nodes.end()) {
                                    break;
                              }
                              const auto lit = it->second.r.assigns.find(t.reg);
                              if (lit == it->second.r.assigns.end()) {
                                    break;
                              }
                              for (const auto ssav : lit->second.second) {

                                    if (const auto it = ssa_types.find(ssav); it != ssa_types.end() && it->second) {
                                          result.emplace_back(it->second);
                                    }
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

      luramas::types::underlying_type dominant(luramas::ir::passes::pass_manager &pm, const luramas::types::underlying_type &a, const luramas::types::underlying_type &b) {

            return a.dominant_t(b, pm.env_flags.options.osign_dominance);
      }

      std::shared_ptr<ir::types::object::type> dominant(const std::shared_ptr<ir::types::object::type> &l, const std::shared_ptr<ir::types::object::type> &r) {

            if (!l || !r) {
                  return r ? r : l;
            }
            if (!l->basic() || !r->basic()) {
                  return !l->basic() ? l : r;
            }
            if (l->basic() && r->basic()) {
                  return l->basic_dominant(r);
            }
            return nullptr;
      }

      std::shared_ptr<ir::types::object::type> dominant(const std::vector<std::shared_ptr<ir::types::object::type>> &v) {

            if (v.empty()) {
                  return nullptr;
            }
            auto result = v.front();
            for (const auto &t : v) {
                  if (const auto d = tools::types::dominant(result, t); d) {
                        result = d;
                  }
            }
            return result;
      }

      boost::unordered_flat_map<luramas_xregister, std::shared_ptr<ir::types::object::type>> ssa_types(const generation::ssa::ssa &ssa) {

            std::vector<std::shared_ptr<ir::types::object::type>> extracted;
            boost::unordered_flat_map<luramas_xregister, std::shared_ptr<ir::types::object::type>> result;

            for (auto _ = 0u; _ < INT_MAX; ++_) {

                  bool mutated = false;
                  for (const auto &[i, data] : ssa.defs) {

                        if (result.contains(i)) {
                              continue;
                        }
                        const auto &stat = data.first;
                        if (!stat) {
                              continue;
                        }
                        switch (stat->k) {
                              case keywords::definition: {

                                    if (const auto linked = tools::ssa::extract::linked(ssa, i); linked) {
                                          for (const auto &m : stat->meta) {
                                                if (tools::exprs::values::is_cast_reg(m, *linked)) {
                                                      mutated = true;
                                                      result[i] = m->non_native;
                                                }
                                          }
                                    }
                                    break;
                              }
                              case keywords::assignment: {

                                    if (stat->r) {
                                          extracted.clear();
                                          bool incomplete = false;
                                          for (const auto &o : extract(stat->r)) {

                                                switch (o.t) {
                                                      case extraction_kind::reg: {

                                                            if (const auto it = result.find(i); it != result.end()) {
                                                                  if (it->second) {
                                                                        extracted.emplace_back(it->second);
                                                                  }
                                                                  break;
                                                            }
                                                            incomplete = true;
                                                            break;
                                                      }
                                                      case extraction_kind::type: {

                                                            if (o.type) {
                                                                  extracted.emplace_back(o.type);
                                                            }
                                                            break;
                                                      }
                                                      default: {
                                                            break;
                                                      }
                                                }
                                                if (incomplete) {
                                                      break;
                                                }
                                          }
                                          if (incomplete) {
                                                continue;
                                          }
                                          if (const auto dom = types::dominant(extracted); dom) {
                                                mutated = true;
                                                result[i] = dom;
                                          }
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  }
                  if (!mutated) {
                        break;
                  }
            }
            return result;
      }

      boost::unordered_flat_map<luramas_register, std::vector<std::pair<luramas_address, std::shared_ptr<ir::types::object::type>>>> casted_regs(passes::pass_manager &pm, const luramas_blockrange &r) {

            boost::unordered_flat_map<luramas_register, std::vector<std::pair<luramas_address, std::shared_ptr<ir::types::object::type>>>> result;

            if (pm.processed.values.empty()) {
                  return result;
            }
            for (auto i = r.first; i < r.second; ++i) {

                  for (const auto &expr : pm.processed.values[pm[i]].all) {

                        if (tools::exprs::values::is_cast_reg(expr)) {
                              result[expr->l->reg].emplace_back(std::make_pair(i, expr->non_native));
                        }
                  }
            }
            return result;
      }

      boost::unordered_flat_map<luramas_register, std::shared_ptr<ir::types::object::type>> frequent(const luramas_blockrange &r, const boost::unordered_flat_map<luramas_register, std::vector<std::pair<luramas_address, std::shared_ptr<ir::types::object::type>>>> &types) {

            boost::unordered_flat_map<luramas_register, std::shared_ptr<ir::types::object::type>> result;

            /* Types */
            boost::unordered_map<luramas_register, std::vector<std::shared_ptr<ir::types::object::type>>> reg_types;
            for (const auto &[reg, data] : types) {
                  for (const auto &[addr, type] : data) {
                        if (tools::contains::address(r, addr)) {
                              reg_types[reg].emplace_back(type);
                        }
                  }
            }

            for (const auto &[reg, types] : reg_types) {

                  /* Most frequent */
                  std::size_t max_count = 0;
                  std::shared_ptr<ir::types::object::type> most_frequent = nullptr;

                  for (const auto &i : types) {
                        if (const auto count = std::count_if(types.begin(), types.end(), [&](const auto &x) {
                                  return x && i && *x == *i;
                            });
                            count > max_count) {
                              max_count = count;
                              most_frequent = i;
                        }
                  }
                  if (most_frequent) {
                        result[reg] = most_frequent;
                  }
            }
            return result;
      }

      map generate_type_map(luramas::ir::passes::pass_manager &pm, const generation::ssa::ssa &ssa) {

            map result;
            for (const auto &[i, e] : ssa_types(ssa)) {

                  for (const auto &j : ssa::extract::exprs(pm, ssa, i)) {

                        auto &m = result[j];
                        if (std::none_of(m.begin(), m.end(), [&](const auto &t) { return t->compare(*e); })) {
                              m.emplace_back(e);
                        }
                  }
            }
            return result;
      }

      std::optional<std::vector<std::shared_ptr<ir::types::object::type>>> get_types(const std::shared_ptr<ir_stat::ir_expr> &expr, const map &m) {

            if (const auto it = m.find(expr); it != m.end()) {
                  return it->second;
            }
            return std::nullopt;
      }
} // namespace luramas::ir::tools::types