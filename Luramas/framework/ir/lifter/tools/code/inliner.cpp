#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::inliner {

      namespace cva {

            bool can_inline(const ir_stat::space &data, const ir_stat::ir_expr::space &args) {

                  if (data.empty() || !tools::stat::is_definition(data.front()) || data.front()->args.size() != args.size()) {
                        return false;
                  }
                  for (const auto &i : data) {
                        if (i->contains(tkind::variadic)) {
                              return false;
                        }
                  }
                  return true;
            }

            bool can_inline(luramas::ir::passes::pass_manager &pm, const std::vector<std::optional<luramas_address>> &parent_pages, const tools::paging::details::page &page, const luramas_count max_references) {

                  if (!page.definition || !page.fvalid || pm[page.range.first]->flags.fpage_main || page.references.size() != 1u || (*page.references.begin()).second.size() > max_references) {
                        return false;
                  }

                  /* Can do function? */
                  for (const auto &[_, ae] : page.references) {
                        for (const auto &i : ae) {
                              if (contains::address(page.range, i.n)) { /* Recursive */
                                    return false;
                              }
                              if (i.stat) {
                                    if (stat::is_page_function_call(pm[i.n]) && !pm.env_flags.fallow_page_function_call_inline) {
                                          return false;
                                    }
                                    if (stat::is_page_return(pm[i.n]) && !pm.env_flags.fallow_page_function_return_inline) {
                                          return false;
                                    }
                                    continue;
                              }
                              if (exprs::values::is_page_function_call(i.e) && !pm.env_flags.fallow_page_function_call_inline) {
                                    return false;
                              }
                        }
                  }

                  const auto range = page.code_range(pm.ir.data);

                  /* Encapsulating pages? */
                  for (const auto &i : luramas_iter(range)) {
                        if (parent_pages[i] != page.range.first) {
                              return false;
                        }
                  }
                  return tools::safe(pm, range) && tools::paging::analyze_page_falls(pm, page).findependant;
            }
      } // namespace cva

      ir_stat::space inline_dynamic(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &tstat, const std::optional<luramas_address> &loc_target) {

            ir_stat::space result;

            if (!tstat) {
                  return result;
            }
            auto stat = tstat;
            while (true) {
                  switch (stat->k) {
                        case keywords::page_function_goto: {

                              if (loc_target && tools::stat::is_page_function_start(pm[*loc_target])) {

                                    if (const auto &def = pm[*loc_target]; tools::stat::is_definition(def)) {

                                          auto it = def->args.begin();
                                          for (auto i = 0u; i < stat->members.size(); ++i) {

                                                if (it == def->args.end()) {
                                                      break;
                                                }
                                                result.emplace_back(tools::stat::generate::assignment((*def->args.begin()).second, stat->members[i]));
                                                ++it;
                                          }
                                          stat = def;
                                          continue;
                                    }
                              }
                              break;
                        }
                        case keywords::definition: {

                              for (auto i = 0u; i < stat->meta.size(); ++i) {

                                    if (i >= stat->args.size()) {
                                          break;
                                    }
                                    if (const auto &cast = stat->meta[i]; tools::exprs::values::is_cast(cast)) {
                                          result.emplace_back(tools::stat::generate::assignment(stat->args[i], tools::exprs::generate::cast(stat->args[i], cast->non_native)));
                                    }
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  break;
            }
            return result;
      }

      ir_stat::space inline_dynamic(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat::ir_expr> &texpr, const std::optional<luramas_address> &loc_target) {

            ir_stat::space result;

            if (!texpr) {
                  return result;
            }
            switch (texpr->k) {
                  case expr_kinds::page_function_call: {

                        if (loc_target && tools::stat::is_page_function_start(pm[*loc_target])) {

                              if (const auto &def = pm[*loc_target]; tools::stat::is_definition(def)) {

                                    auto it = def->args.begin();
                                    for (auto i = 0u; i < texpr->members.size(); ++i) {

                                          if (it == def->args.end()) {
                                                break;
                                          }
                                          result.emplace_back(tools::stat::generate::assignment((*def->args.begin()).second, texpr->members[i]));
                                          ++it;
                                    }
                                    const auto v = inline_dynamic(pm, def, loc_target);
                                    result.insert(result.end(), std::make_move_iterator(v.begin()), std::make_move_iterator(v.end()));
                              }
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return result;
      }

      ir_stat::space inline_data(luramas::ir::passes::pass_manager &pm, const ir_stat::space &data, const ir_stat::ir_expr::space &calle_assigns, const ir_stat::ir_expr::space args, const bool register_calle_assigns) {

            ir_stat::space result;

            const auto early_return_loc = se_ir::avaliable_label(data) + pm.ir.avaliable_label();

            /* Ignore variadic */
            if (!cva::can_inline(data, args)) {
                  return result;
            }

            if (register_calle_assigns) {
                  luramas_register avaliable = 0u;
                  for (auto &i : calle_assigns) {
                        if (i->is_register_reference()) {
                              continue;
                        }
                        avaliable += (avaliable) ? 1u : se_ir::avaliable_register(data) + pm.ir.avaliable_register();
                        i->clear();
                        i->emit_reg(avaliable);
                  }
            }

            boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> params;

            bool exits_early = false;
            for (auto i = 0ull; i < data.size(); ++i) {

                  auto p = data[i];

                  /* Map definitions */
                  if (p->is_k<keywords::definition>()) {

                        params.clear();
                        for (auto a = 0u; a < p->parameters.size(); ++a) {

                              if (a >= args.size()) {
                                    return result;
                              }
                              params.try_emplace(p->parameters[a]->reg, args[a]);
                        }
                  }

                  /* Ignore meta */
                  if (p->is_meta()) {
                        continue;
                  }

                  p = p->clone();
                  for (auto &i : p->extract_ordered_deep_exprs()) {
                        if (tools::exprs::values::is_arg(i)) {
                              if (const auto it = params.find(i->reg); it != params.end()) {
                                    i->clear();
                                    it->second->clone(i);
                              } else {
                                    result.clear();
                                    return result;
                              }
                        }
                  }

                  switch (p->k) {
                        case keywords::retn: {

                              const auto last_return = i == data.size() - 1u;
                              if (last_return && tools::stat::common::empty_return(p)) {
                                    break;
                              }
                              for (auto reti = 0u; reti < p->members.size(); ++reti) {

                                    if (reti >= calle_assigns.size()) {
                                          break;
                                    }
                                    result.emplace_back(tools::stat::generate::assignment(calle_assigns[reti], p->members[reti]));
                              }
                              if (!last_return) {
                                    exits_early = true;
                                    result.emplace_back(tools::stat::generate::goto_label(early_return_loc));
                              }
                              break;
                        }
                        default: {
                              result.emplace_back(p);
                              break;
                        }
                  }
            }
            if (exits_early) {
                  result.emplace_back(tools::stat::generate::label(early_return_loc));
            }
            rebaser::labels(early_return_loc, result);
            return result;
      }

      inlined_page_results page(luramas::ir::passes::pass_manager &pm, const addr_expr &ref, const paging::details &page_details, const paging::details::page &page, const inline_page_flags &flags) {

            luramas_flag fopened_cond = false;
            inlined_page_results result;

            if (!page.fvalid) {
                  return result;
            }

            /* Map params */
            if (ref.stat && (stat::is_page_function_goto(pm[ref.n]) || stat::is_page_return(pm[ref.n]))) {

                  const auto dyn = inline_dynamic(pm, pm[ref.n], page.range.first);
                  result.data.insert(result.data.end(), std::make_move_iterator(dyn.begin()), std::make_move_iterator(dyn.end()));
            }
            if (ref.e && exprs::values::is_page_function_call(ref.e)) {

                  const auto dyn = inline_dynamic(pm, pm[ref.n], page.range.first);
                  result.data.insert(result.data.end(), std::make_move_iterator(dyn.begin()), std::make_move_iterator(dyn.end()));
            }

            /* Cbs */
            if (pm.env_flags.options.opage_call_action_s && ref.stat && stat::is_page_function_call(pm[ref.n])) {

                  const auto dyn = pm.env_flags.options.opage_call_action_s(pm[ref.n]);
                  result.data.insert(result.data.end(), std::make_move_iterator(dyn.begin()), std::make_move_iterator(dyn.end()));
            }
            if (pm.env_flags.options.opage_call_action_e && ref.e && exprs::values::is_page_function_call(ref.e)) {

                  const auto dyn = pm.env_flags.options.opage_call_action_e(ref.e);
                  result.data.insert(result.data.end(), std::make_move_iterator(dyn.begin()), std::make_move_iterator(dyn.end()));
            }
            if (pm.env_flags.options.opage_return_read && ref.stat && stat::is_page_return(pm[ref.n])) {

                  fopened_cond = true;
                  result.data.emplace_back(tools::stat::generate::cond(pm.env_flags.options.opage_return_read(pm[ref.n]), il::arch::data::bin_kinds::eq_, tools::exprs::generate::integral(page.id)));
            }

            const auto range = page.code_range(pm.ir.data);
            for (auto i = range.first; i < range.second; ++i) {

                  const auto &p = pm[i];
                  switch (p->k) {
                        case keywords::definition: {

                              auto dyn = inline_dynamic(pm, p);
                              result.data.insert(result.data.end(), std::make_move_iterator(dyn.begin()), std::make_move_iterator(dyn.end()));
                              break;
                        }
                        case keywords::retn: {

                              if (tools::stat::is_page_return(p)) {

                                    /* Values */
                                    for (const auto &[reg, idx] : p->args) {
                                          result.data.emplace_back(tools::stat::generate::assignment(result.results.try_emplace(reg, tools::exprs::generate::reg(pm.ir.avaliable_register())).first->second, p->members[idx->extract_integral_base()]));
                                    }

                                    /* Return adjust */
                                    if (pm.env_flags.options.opage_return_action) {
                                          const auto v = pm.env_flags.options.opage_return_action();
                                          result.data.insert(result.data.end(), v.begin(), v.end());
                                    }

                                    /* Jump table */
                                    if (!p->smembers.empty()) {

                                          const auto r = tools::exprs::generate::reg(pm.ir.avaliable_register());
                                          if (pm.env_flags.options.opage_return_read) {
                                                result.data.emplace_back(tools::stat::generate::assignment(r, pm.env_flags.options.opage_return_read(p)));
                                          }
                                          for (const auto &l : p->smembers) {

                                                if (!l->is_integral()) {
                                                      continue;
                                                }
                                                if (const auto &lp = page_details.index_page(l->extract_integral_base()); lp) {

                                                      result.data.emplace_back(tools::stat::generate::cond(r, il::arch::data::bin_kinds::eq_, l));

                                                      /* Link */
                                                      ir_stat::ir_expr::space args;
                                                      if ((*lp).second.definition) {
                                                            for (const auto &[a, e] : (*lp).second.definition->args) {
                                                                  if (const auto it = result.results.find(a); it != result.results.end()) {
                                                                        args.emplace_back(it->second);
                                                                  } else {
                                                                        args.emplace_back(e);
                                                                  }
                                                            }
                                                      } else {
                                                            for (const auto &[reg, idx] : p->args) {
                                                                  args.emplace_back(p->members[idx->extract_integral_base()]);
                                                            }
                                                      }
                                                      result.data.insert(result.data.end(), {tools::stat::generate::page_function_jump(l, args), tools::stat::generate::end()});
                                                }
                                          }
                                    }
                                    break;
                              }
                              /* Let it fall */
                              [[fallthrough]];
                        }
                        default: {

                              result.data.emplace_back(tools::stat::common::clone(p, flags.fclone));
                              break;
                        }
                  }
            }

            if (fopened_cond) {
                  result.data.emplace_back(tools::stat::generate::end());
            }
            return result;
      }
} // namespace luramas::ir::tools::inliner