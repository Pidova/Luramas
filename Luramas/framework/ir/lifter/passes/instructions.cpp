#include "includes/common.hpp"
#include <ranges>

namespace luramas::ir::passes {

      void instruction_scheduling(pass_manager &pm, shared &s, generation::ssa::ssa &ssa) {

            if (s.frunning_again) {
                  return;
            }

#if defined(DEBUG) && !defined(LURAMAS_PROFILE)
            //   std::printf("SCHEDULING IR\n");
#endif // NDEBUG

            for (const auto &i : pm.iter()) {

                  const auto &p = pm[i];
                  auto &rssa = ssa.nodes[p];
                  for (const auto &r : rssa.r.regs) {

                        if (const auto &ssv = *rssa.r.assigns[r].second.begin(); i && !ssa.phis.contains(ssv)) {

                              if (const auto &past = ssa.defs[ssv]; past.first && past.first->is_k<keywords::assignment>() && pm.is_safe(past.first) && !ssa.captures.contains(ssv) && !tools::common::expects_definition(pm, i - 1u)) {

                                    const auto assignment_regs = tools::extract::assignment_regs(past.first);
                                    if (const auto &t = past.first->r; t && !tools::mutations::modified_regs(pm, tools::transform::address_to_range(past.second.first, i - 1u), {assignment_regs.begin(), assignment_regs.end()}) &&
                                                                       !s.scheduled_stats.contains(past.first) && pm.safe(past.first) &&
                                                                       tools::ssa::same_highlevel_scope_id(pm, ssa, past.second.first, i) &&
                                                                       !luramas::ir::tools::mutates(pm, t, past.second.first, i)) {

                                          pm.move(pm[i - 1u], past.first);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                          s.scheduled_stats.insert(past.first);
                                    }
                              }
                        }
                  }
            }
            return;
      }

      void jump_threading(pass_manager &pm, shared &s) {

            for (const auto &i : pm.iter()) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::condition_goto: {

                              const auto label = tools::common::safe_take_jump(pm, i);
                              const auto violation = tools::violations::block_violates(pm, i, label);

                              bool unsafe = false;
                              for (auto l = i; l < label; ++l) {

                                    const auto &p = pm[l];

                                    /*
                                         ::l(2)::
                                         cond_goto l;
                                         goto l(2):
                                         ::l::
                                    */
                                    if (p->is_k<keywords::goto_label>() && tools::stat::past(i, pm.processed.labels[p->jlabel])) {
                                          unsafe = true;
                                          break;
                                    }
                              }
                              if (!unsafe) {

                                    auto valid = violation.valid;
                                    if (!valid && violation.reason == tools::violations::block_violation_exceptions::invalid_end) {

                                          bool hit = false;
                                          const auto last = tools::visitors::last_safe_end(pm, violation.ending_loc, hit);
                                          valid = !hit && tools::stat::is_end(pm[last]) && tools::stat::branch::is_cond_goto_label(p, pm[last + 1u]);
                                    }
                                    if (pm.is_safe(p) && valid) {

                                          tools::stat::mutate::if_stat_cleared<true>(p);

                                          pm.insert(pm[label - 1u], tools::stat::generate::end());
                                          pm.set_safe(p);
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

      void instruction_hoisting(pass_manager &pm, shared &s, generation::ssa::ssa &ssa) {

            boost::unordered_flat_map<luramas_address, boost::unordered_flat_set<luramas_register>> inserted;

            for (const auto &i : pm.iter()) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::condition: {

                              if (tools::contains::if_cond_else(pm, i)) {

                                    const auto end = tools::common::safe_take_jump(pm, i);
                                    const auto blocks = tools::extract::dominate_blocks(pm, i);
                                    if (blocks.size() > 1u) {
                                          for (const auto &[reg, assignments] : tools::ssa::extract::same_assignments(pm, ssa, blocks, true, true)) {

                                                /* Is safe? */
                                                if (!std::none_of(assignments.begin(), assignments.end(), [&](const auto &p) { return !pm.is_safe(pm[p.first]); })) {
                                                      continue;
                                                }

                                                /* Canonicalize */
                                                if (std::all_of(assignments.begin(), assignments.end(), [&](const auto &pair) {
                                                          const auto &[node, end_block] = pair;
                                                          return !tools::ssa::used(pm, ssa, node, end_block, reg) &&
                                                                 !tools::mutates(pm, p, node, end_block);
                                                    })) {

                                                      for (const auto &[node, end_block] : assignments) {
                                                            pm.remove(pm[node]);
                                                      }
                                                      pm.insert(pm[tools::trackers::next_safe_executable(pm, end) - 1u], pm[assignments.back().first]);
                                                      pm.mut(LURAMAS_DEBUG_LINE);
                                                }
                                          }
                                    }
                              }
                              break;
                        }
                        case keywords::assignment: {

                              // TODO  IMPL  AUTO HIOST IF NOT USED WITHIN SCOPE FOR PRIMIIVE ELSE DO NULL DEF ITF ITS NOT A PRIMITIVE mark immutable

                              /* Must be PHI */
                              bool phis = true;
                              luramas_register target = 0u;
                              for (const auto &[reg, data] : ssa.nodes[p].l.assigns) {
                                    for (const auto &ssa_reg : data.second) {
                                          target = reg;
                                          if (!ssa.phis.contains(ssa_reg)) {
                                                phis = false;
                                                break;
                                          }
                                    }
                              }
                              if (!phis || !pm.is_safe(p)) {
                                    break;
                              }

                              /* Must have multiple blocks */
                              const auto blocks = tools::extract::parent_ifcond_blocks(pm, i);
                              if (blocks.size() <= 1 || !tools::contains::unconditional_block(pm, blocks)) {
                                    break;
                              }

                              if (p->l && ssa.nodes[p].l.assigns.size() == 1u) {

                                    const auto assignment_blocks = tools::ssa::extract::block_assignment(pm, ssa, blocks, target, tools::ssa::extract::hit_type::first);
                                    if (assignment_blocks.size() != blocks.size()) {
                                          break;
                                    }

                                    /* Used from [Start block, assignment)? */
                                    if (std::any_of(assignment_blocks.begin(), assignment_blocks.end(), [&](const auto &i) { return tools::ssa::used(pm, ssa, i.second.first, i.first, target); })) {
                                          break;
                                    }

                                    luramas_address primitive_assignment = 0u;
                                    for (const auto &[asign, range] : assignment_blocks) {
                                          if (const auto &p = pm[asign]; p->is_assignment() && p->r && p->r->is_primitive() && pm.is_safe(p)) {
                                                primitive_assignment = asign;
                                                break;
                                          }
                                    }
                                    if (primitive_assignment) {

                                          pm.move_front(assignment_blocks.front().second.first, pm[primitive_assignment]);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    } else {

                                          /* See if dominant above blocks reg is getting used? */
                                          if (const auto rev = tools::accumulate::reverse_dominant(pm, i - 1u); std::any_of(rev.begin(), rev.end(), [&](const auto &a) {
                                                    const auto it = inserted.find(a);
                                                    return (it != inserted.end() && it->second.contains(target)) || ssa.nodes[pm[a]].l.refrence_regs.contains(target) || ssa.nodes[pm[a]].r.refrence_regs.contains(target);
                                              })) {
                                                break;
                                          }

                                          const auto loc = assignment_blocks.front().second.first;
                                          pm.insert_front(loc, tools::stat::generate::flags::immutable::set(tools::stat::generate::assignment(p->l, tools::exprs::generate::none_object()), true));

                                          if (const auto it = inserted.find(loc); it != inserted.end()) {
                                                it->second.insert(target);
                                          } else {
                                                inserted.try_emplace(loc, target);
                                          }
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              } else {

                                    /* TODO ADD MULRET LOGIC */
                              }
                              break;
                        }
                        case keywords::label: {

                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
            return;
      }

      void definition_flattening(pass_manager &pm, shared &s, generation::ssa::ssa &ssa) {

            boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> unsafe_regs;
            std::vector<std::pair<luramas_address, std::size_t>> used_scope_ids;

            std::optional<tools::paging::details> pdetails;
            if (pm.env_flags.fhas_pages) {
                  pdetails = tools::paging::gen_details(pm);
            }

            for (const auto &reg : tools::ssa::extract::all_dominant_singletons(ssa)) {

                  const auto def = ssa.defs[reg];

                  /* Check for phis */
                  for (const auto &loc : def.second.second.first) {
                        used_scope_ids.emplace_back(loc, ssa.high_level_scope_id[loc]);
                  }

                  if (const auto current_id = ssa.high_level_scope_id[def.second.first]; std::ranges::any_of(used_scope_ids, [&](const auto &p) { return current_id > p.second; })) {

                        auto [loc, id] = *std::min_element(used_scope_ids.begin(), used_scope_ids.end(), [](const auto &a, const auto &b) { return a.second < b.second; });

                        while (loc) {
                              if (ssa.high_level_scope_id[loc--] < id) {
                                    break;
                              }
                        }

                        if (const auto linked = tools::ssa::extract::linked(ssa, reg); linked) {

                              if (const auto rexpr = tools::common::get_reg_expr_assignment(def.first, *linked); rexpr && !unsafe_regs.contains(rexpr)) {

                                    /* Already in page arg?  */
                                    if (pdetails) {
                                          if (const auto &p = pdetails->get_page(def.second.first); p) {
                                                if (const auto &idxp = pdetails->index_page(*p); idxp) {
                                                      if (const auto [idx, pg] = *idxp; pg.definition && pg.definition->args.contains(*linked)) {
                                                            continue;
                                                      }
                                                }
                                          }
                                    }

                                    /* See if it has been synthesized before */
                                    if (const auto integral = tools::exprs::generate::integral(0u); !std::any_of(pm.ir.data.begin(), pm.ir.data.end(), [&](const auto &i) { return tools::stat::is_assignment(i, rexpr, integral) && i->flags.fsynthetic; })) {

                                          loc += tools::stat::is_page_function_start(tools::visitors::next(pm, loc));
                                          loc += tools::stat::is_definition(tools::visitors::next(pm, loc));

                                          unsafe_regs.insert(rexpr);
                                          const auto assignment = tools::stat::generate::assignment(rexpr, integral);
                                          tools::stat::generate::flags::synthetic::flagable::set(assignment);
                                          pm.insert(pm[loc], assignment);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }
                  }
                  used_scope_ids.clear();
            }
            return;
      }

      void definition_flattening(pass_manager &pm, shared &s) {

            luramas::ir::pass::process::values(pm);
            auto ssa = generation::ssa::generate(pm.ir, generation::ssa::ssa_flags({.finclude_captures = true, .finclude_references = pm.env_flags.fhas_references}), pm.processed.values);
            definition_flattening(pm, s, ssa);
            return;
      }

      void update_closure_definition(pass_manager &pm, shared &s) {

            tools::closure::space_stat::definition::update(pm.ir.data);
            return;
      }
} // namespace luramas::ir::passes