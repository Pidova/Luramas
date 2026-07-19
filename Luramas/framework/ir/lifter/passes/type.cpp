#include "includes/common.hpp"

namespace luramas::ir::passes {

      void make_registers_unique(pass_manager &pm, shared &s) {

            pass::process::values(pm);

            boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> regs;
            for (const auto &i : pm.iter()) {

                  const auto &p = pm[i];
                  const auto &data = pm.processed.values.find(p)->second;

                  for (const auto &r : data.rvalues) {
                        r->shallow_replace(regs);
                  }

                  if (p->flags.fdefine && tools::stat::is_assignment(p)) {

                        for (const auto &r : data.lvalues) {
                              if (tools::exprs::values::is_general_purpose_register(r)) {
                                    regs[r->reg] = r;
                              }
                        }
                        continue;
                  }
                  if (tools::stat::is_definition(p)) {

                        for (const auto &[_, e] : p->args) {
                              if (tools::exprs::values::is_general_purpose_register(e)) {
                                    regs[e->reg] = e;
                              }
                        }
                        continue;
                  }

                  p->shallow_replace(regs);
                  for (const auto &r : data.lvalues) {
                        r->shallow_replace(regs);
                  }
            }
            return;
      }

      void definition_inference(pass_manager &pm, shared &s) {

            /* Make all registers unique */
            pass::process::values(pm);
            auto ssa = generation::ssa::generate(pm.ir, generation::ssa::ssa_flags({.finclude_captures = true, .finclude_references = pm.env_flags.fhas_references}), pm.processed.values);
            const auto process = [&](const auto &def, const auto &block_range) {
                  /* Extract args */
                  boost::unordered_flat_set<luramas_register> args;
                  if (tools::stat::is_definition(def)) {
                        for (const auto &r : def->args) {
                              args.insert(r.first);
                        }
                  }
                  for (const auto &i : luramas_iter(block_range)) {

                        const auto &n = pm[i];
                        if (const auto assigns = ssa.nodes[n].l.assigns.size(); assigns) {
                              n->flags.fdefine = tools::ssa::all_undefined(pm, ssa, i, args).size() == assigns;
                        }
                  }
                  return;
            };

            /* Main, pages */
            process(pm.ir.data.front(), pm.range());
            if (pm.env_flags.fhas_pages) {
                  for (const auto &[exp, data] : tools::paging::gen_details(pm).pages) {
                        for (const auto &[id, page] : data) {
                              process(page.definition, page.range);
                        }
                  }
            }

            /* Unique registers */
            make_registers_unique(pm, s);
            return;
      }

      void static_definition_inference(pass_manager &pm, shared &s) {

            boost::unordered_flat_set<luramas_register> used;
            pass::process::values(pm);
            auto ssa = generation::ssa::generate(pm.ir, generation::ssa::ssa_flags({.finclude_captures = true, .finclude_references = pm.env_flags.fhas_references}), pm.processed.values);
            for (const auto &i : pm.iter()) {

                  const auto &p = pm[i];
                  auto &rssa = ssa.nodes[p];
                  if (!tools::stat::assignment::is_lvalues_contains_upvalue(p)) {
                        for (const auto &r : rssa.l.regs) {

                              if (!p->r) {
                                    break;
                              }

                              /* Deadset */
                              if (ssa.defs[*rssa.l.assigns[r].second.begin()].second.second.first.empty()) {
                                    if (const auto lv = p->visit_lvalue(r); lv) {
                                          lv->flags.fdeadset = false;
                                    }
                              }

                              if (ssa.assignments.count(r) == 1u) {
                                    if (const auto lv = p->visit_lvalue(r); lv) {
                                          lv->flags.fconstant = true;
                                    }
                              }
                        }
                  }

                  if (p->is_self_referential_assignment() && p->l) {
                        if (p->l->is_register_reference()) {
                              p->l->flags.fconstant = false;
                        }
                        for (const auto &expr : p->l->extract_exprs()) {
                              if (expr->is_k<expr_kinds::idx>() && expr->l && expr->l->is_register_reference()) {
                                    expr->l->flags.fconstant = false;
                              }
                        }
                  }
            }
            return;
      }

      void dead_type_elimination(pass_manager &pm, shared &s, generation::ssa::ssa &ssa) {

            luramas::ir::pass::process::values(pm);

            std::vector<std::shared_ptr<ir::types::object::type>> vect;
            const auto types = tools::types::ssa_types(ssa);
            for (const auto &[stat, data] : pm.processed.values) {

                  const auto analyze = [&](const auto &expr, const auto &data) {
                        for (const auto &t : tools::types::extract(expr)) {
                              switch (t.t) {
                                    case tools::types::extraction_kind::reg: {

                                          const auto d_it = data.find(t.reg);
                                          if (d_it == data.end()) {
                                                return false;
                                          }

                                          const auto &[kinds, regs] = d_it->second;
                                          if (regs.empty()) {
                                                return false;
                                          }

                                          const auto cit = types.find(*regs.begin());
                                          if (cit == types.end() || !cit->second) {
                                                return false;
                                          }

                                          if (regs.size() != 1u) {
                                                if (!std::all_of(regs.begin(), regs.end(), [&](const auto &i) {const auto it = types.find(i); return it != types.end() && it->second && *it->second == *cit->second; })) {
                                                      return false;
                                                }
                                          }
                                          vect.emplace_back(cit->second);
                                          break;
                                    }
                                    case tools::types::extraction_kind::type: {

                                          vect.emplace_back(t.type);
                                          break;
                                    }
                                    default: {
                                          break;
                                    }
                              }
                        }
                        return true;
                  };

                  const auto &node = ssa.nodes[stat];
                  for (const auto &i : data.lvalues) {

                        if (tools::exprs::values::is_cast(i)) {

                              if (!analyze(i->l, node.l.assigns)) {
                                    vect.clear();
                                    continue;
                              }
                              if (const auto dom = tools::types::dominant(vect); dom && *dom == *i->non_native) {
                                    i->non_native = nullptr;
                                    i->emit_blank_lvalue();
                              }
                              vect.clear();
                        }
                  }
                  for (const auto &i : data.rvalues) {

                        if (tools::exprs::values::is_cast(i)) {

                              if (!analyze(i->l, node.r.assigns)) {
                                    vect.clear();
                                    continue;
                              }
                              if (const auto dom = tools::types::dominant(vect); dom && *dom == *i->non_native) {
                                    i->non_native = nullptr;
                                    i->emit_blank_lvalue();
                              }
                              vect.clear();
                        }
                  }
            }
            dead_type_dependant_elimination(pm, s, ssa, types);
            return;
      }

      void definition_types(pass_manager &pm, shared &s) {

            luramas::ir::pass::process::values(pm);

            const auto types = tools::types::casted_regs(pm, pm.range());

            /* Main */
            if (const auto &def = pm.ir.data.front(); tools::stat::is_definition(def) && std::any_of(def->meta.begin(), def->meta.end(), [](const auto &i) { return !i; })) {

                  if (std::any_of(def->meta.begin(), def->meta.end(), [](const auto &i) { return !i; })) {

                        for (const auto &[r, t] : tools::types::frequent(pm.range(), types)) {

                              if (const auto it = def->args.find(r); it != def->args.end()) {

                                    if (auto &v = def->meta[std::distance(def->args.begin(), it)]; !tools::exprs::values::is_cast(v, t)) {
                                          v = tools::exprs::generate::cast(it->second, t);
                                    }
                              }
                        }
                  }
            }

            /* Pages */
            for (const auto &[expr, map] : tools::paging::gen_details(pm).pages) {
                  for (const auto &[pid, page] : map) {

                        if (const auto &def = pm[page.range.first + 1u]; tools::stat::is_definition(def)) {

                              if (std::any_of(def->meta.begin(), def->meta.end(), [](const auto &i) { return !i; })) {

                                    for (const auto &[r, t] : tools::types::frequent({page.range.first, page.range.second}, types)) {

                                          if (const auto it = def->args.find(r); it != def->args.end()) {

                                                if (auto &v = def->meta[std::distance(def->args.begin(), it)]; !tools::exprs::values::is_cast(v, t)) {
                                                      v = tools::exprs::generate::cast(it->second, t);
                                                }
                                          }
                                    }
                              }
                        }
                  }
            }
            return;
      }

      void set_descriptor_types(pass_manager &pm, shared &s) {

            pass::process::values(pm);
            auto ssa = generation::ssa::generate(pm.ir, generation::ssa::ssa_flags({.finclude_captures = true, .finclude_references = pm.env_flags.fhas_references}), pm.processed.values);
            const auto ssa_types = tools::types::ssa_types(ssa);

            /* Reg types */
            for (const auto &[reg, t] : ssa_types) {

                  const auto &[asgn, data] = ssa.defs[reg];

                  if (tools::stat::is_assignment(asgn)) {
                        if (asgn->l->is_reg(data.first)) {
                              asgn->l->non_native = t;
                        } else {
                              for (const auto &i : asgn->members) {
                                    if (i->is_reg(data.first)) {
                                          i->non_native = t;
                                    }
                              }
                        }
                  }
                  for (const auto &i : data.second.first) {
                        for (const auto &e : pm.processed.values[pm[i]].all) {
                              if (e->is_reg(data.first)) {
                                    e->non_native = t;
                              }
                        }
                  }
            }

            /* Defaults */
            if (pm.env_flags.options.odefault_type) {

                  /* Definition */
                  for (const auto &p : pm.ir.data) {

                        if (tools::stat::is_definition(p)) {

                              boost::unordered_flat_map<luramas_register, std::pair<luramas_id, std::shared_ptr<ir_stat::ir_expr>>> reg_to_index;

                              luramas_id idx = 0u;
                              for (const auto &[r, expr] : p->args) {
                                    reg_to_index[r] = {idx++, expr};
                              }
                              for (const auto &[r, d] : reg_to_index) {

                                    if (const auto &[id, expr] = d; id < p->meta.size()) {

                                          auto e = p->meta[id];
                                          if (tools::exprs::values::is_cast(e)) {
                                                continue;
                                          }
                                          if (!tools::exprs::values::is_general_purpose_register(expr)) {
                                                e = d.second;
                                          }
                                          p->meta[id] = tools::exprs::generate::cast(!e ? tools::exprs::generate::reg(r) : e, pm.env_flags.options.odefault_type);
                                    }
                              }
                        }
                  }
            }

            /* Set defition returns */
            for (const auto &[expr, map] : tools::paging::gen_details(pm).pages) {

                  for (const auto &[pid, page] : map) {

                        if (page.definition) {

                              /* Extract */
                              std::vector<std::shared_ptr<ir::types::object::type>> def_retns;
                              for (auto i = page.range.first; i < page.range.second; ++i) {

                                    if (const auto &p = pm[i]; tools::stat::is_page_return(p)) {

                                          for (auto mi = 0u; mi < p->members.size(); ++mi) {

                                                if (const auto t = tools::types::dominant(tools::types::extract(p, p->members[mi], ssa, ssa_types)); mi >= def_retns.size()) {
                                                      def_retns.emplace_back(t ? t : pm.env_flags.options.odefault_type ? types::generate::basic(pm.env_flags.options.odefault_type)
                                                                                                                        : t);
                                                } else {
                                                      def_retns[mi] = tools::types::dominant(t, def_retns[mi]);
                                                }
                                          }
                                    }
                              }

                              /* Set */
                              page.definition->smembers.clear();
                              for (const auto &i : def_retns) {
                                    page.definition->smembers.emplace_back(i ? tools::exprs::generate::cast(tools::exprs::generate::none_object(), i) : tools::exprs::generate::none_object());
                              }
                        }
                  }
            }
            return;
      }
} // namespace luramas::ir::passes