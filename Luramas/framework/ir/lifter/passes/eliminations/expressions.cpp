#include "../includes/common.hpp"

namespace luramas::ir::passes {

      void expression_canonicalization_elimination(pass_manager &pm, shared &s) {

            boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> processed;
            processed.reserve(pm.amount() * LURAMAS_PREDICTED_EXPRS);

            /* Contraints */
            std::optional<tools::types::map> tmap = std::nullopt;
            if (pm.env_flags.fallow_expr_opt_type_constraints && pm.env_flags.fhas_types) {
                  luramas::ir::pass::process::values(pm);
                  tmap = tools::types::generate_type_map(pm, generation::ssa::generate(pm.ir, generation::ssa::ssa_flags({.finclude_captures = true, .finclude_references = pm.env_flags.fhas_references}), pm.processed.values));
            }

            std::function<void(std::shared_ptr<ir_stat::ir_expr> &, const bool singleton)> compute_expr = [&](std::shared_ptr<ir_stat::ir_expr> &expr, const bool singleton) {
                  if (!expr || processed.contains(expr)) {
                        return;
                  }
                  processed.insert(expr);
                  tools::compute::exprs::simplify(pm, expr, singleton, true, std::nullopt, tmap);
                  compute_expr(expr->l, false);
                  compute_expr(expr->r, false);
                  compute_expr(expr->ev, false);
                  compute_expr(expr->xv, false);
                  for (auto &m : expr->members) {
                        compute_expr(m, false);
                  }
                  for (auto &m : expr->captures) {
                        compute_expr(m, false);
                  }
                  for (auto &[i, v] : expr->tmembers) {
                        if (i) {
                              compute_expr(i, false);
                        }
                        if (v) {
                              compute_expr(v, false);
                        }
                  }
                  return;
            };

            for (const auto &i : pm.iter()) {

                  if (auto &p = pm[i]; pm.is_safe(p)) {

                        if (tools::compute::stats::simplify(pm, i, p, true, tmap)) {
                              continue;
                        }
                        compute_expr(p->l, true);
                        compute_expr(p->r, true);
                        compute_expr(p->v, true);
                        for (auto &v : p->members) {
                              compute_expr(v, true);
                        }
                        for (auto &v : p->smembers) {
                              compute_expr(v, true);
                        }
                        for (auto &v : p->tmembers) {
                              compute_expr(v, true);
                        }
                        switch (p->k) {
                              case keywords::bitwrite: {
                                    compute_expr(p->lba, true);
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  }
            }
            return;
      }

      void dead_store_elimination(pass_manager &pm, shared &s) {

            luramas::ir::pass::process::values(pm);

            /* Paging */
            const auto page_details = tools::paging::gen_details(pm);
            const auto parent_pages = tools::paging::parent_pages(pm);
            boost::unordered_flat_map<luramas_id, tools::paging::return_data> retn_cache;

            //std::cout << tools::debug::graph(pm) << std::endl;
            auto ssa = generation::ssa::generate(pm.ir, generation::ssa::ssa_flags({.finclude_captures = true, .finclude_references = pm.env_flags.fhas_references}), pm.processed.values);
            for (const auto &i : pm.iter()) {

                  const auto &p = pm[i];
                  auto &rssa = ssa.nodes[p];

                  /* Skip loops */
                  if (!tools::stat::is_assignment(p)) {
                        continue;
                  }

                  /* Unsafe memory reads? */
                  if (pm.env_flags.fhas_memory && !pm.env_flags.fmemory_read_safe && rssa.l.assigns.size() == 1u) {

                        if (const tools::find::find_expr_cb has_memread = [](const std::shared_ptr<ir_stat::ir_expr> &expr) { return expr->is_k<expr_kinds::memoryread>(); }; tools::find::expr(has_memread, p->r)) {

                              if (const auto b = rssa.l.assigns.begin(); b->second.second.size() == 1u && ssa.defs[*b->second.second.begin()].second.second.first.empty()) {
                                    p->flags.fdead_sideeffects = true;
                                    continue;
                              }
                        }
                  }

                  /* Synthetic */
                  if (p->flags.fsynthetic && pm.env_flags.fremove_dead_synthetics && rssa.l.assigns.size() == 1u) {

                        if (const auto b = rssa.l.assigns.begin(); b->second.second.size() == 1u && ssa.defs[*b->second.second.begin()].second.second.first.empty() &&
                                                                   !tools::ssa::is_placeholder_variable(pm, ssa, *b->second.second.begin(), i)) {
                              pm.remove(p);
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                        continue;
                  }

                  /* Unsafe assignment */
                  if (p->flags.fvolatile || p->flags.fsynthetic) {
                        continue;
                  }

                  /* Page results */
                  if (!rssa.l.regs.empty() && tools::exprs::values::is_page_function_call(p->r) && tools::exprs::values::is_integer(p->r->r)) {

                        const auto id = p->r->r->extract_integral_base();
                        if (const auto &page = page_details.index_page(id); page) {

                              const auto original = p->r->members.size();
                              if (const auto [it, _] = retn_cache.try_emplace(id, tools::paging::gen_return_data(pm, (*page).second, parent_pages));
                                  it->second.maximum < original) {

                                    p->r->members.resize(it->second.maximum);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              if (p->r->members.empty()) {

                                    pm.remove(p);
                                    pm.insert(p, p->r->transform());
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              if (original != p->r->members.size()) {
                                    continue;
                              }
                        }
                  }

                  if (rssa.l.regs.size() != 1u) {

                        /* Members */
                        for (auto it = p->members.end(); it != p->members.begin();) {

                              --it;
                              if (const auto &expr = *it; tools::exprs::values::is_reg(expr)) {

                                    if (const auto it = rssa.l.assigns.find(expr->reg); it != rssa.l.assigns.end()) {
                                          if (const auto ssa_reg = *it->second.second.begin(); ssa.defs[ssa_reg].second.second.first.empty()) {
                                                p->members.pop_back();
                                          } else {
                                                break;
                                          }
                                    } else {
                                          break; /* Unexpected ignore it, let other passes handle it */
                                    }
                              }
                        }
                        continue;
                  } else if (!rssa.l.regs.empty()) {

                        const auto reg = *rssa.l.regs.begin();
                        if (pm.is_safe(p) && !p->r->contains_volatile() && ssa.defs[*rssa.l.assigns[reg].second.begin()].second.second.first.empty()) {

                              if (const auto dom = tools::ssa::extract::dominant_define(pm, ssa, i, reg); dom && *pm[*dom] == *p && !tools::mutates(pm, p->r, *dom, i)) {

                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              } else if (!tools::ssa::extract::next_assignment_inscope_assignment(pm, ssa, i, reg)) {

                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              } else if (!dom) {

                                    if (tools::ssa::extract::next_assignment_same_scope_assignment(pm, ssa, i, reg)) {
                                          pm.remove(p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              } else if (dom && *dom != i) {

                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                  }
            }
            if (pm.env_flags.fallow_definition_flattening && !s.fran_definition_flattening) {
                  passes::definition_flattening(pm, s, ssa);
                  s.fran_definition_flattening = true;
            }
            return;
      }

      void flag_optimization(pass_manager &pm, shared &s) {

            luramas::ir::pass::process::values(pm);
            auto fssa = generation::flag_ssa::generate(pm.ir, pm.processed.values);

            passes::dead_flag_elimination(pm, s, fssa);
            passes::flag_propagation(pm, s, fssa);
            return;
      }
} // namespace luramas::ir::passes