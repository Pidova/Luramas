#include "includes/common.hpp"
#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace luramas::ir::passes {

      namespace promote {

            /* Delete page */
            inline void page_deletion(pass_manager &pm, const tools::paging::details::page &page) {

                  if (page.fhas_start) {
                        pm.remove(pm[page.range.first]);
                        if (pm.valid_next<1u>(page.range.first)) {
                              if (const auto &def = pm[page.range.first + 1u]; tools::stat::is_definition(def) && def->flags.fpage_keyword) {
                                    pm.remove(def);
                              }
                        }
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
                  if (page.fvalid) {
                        pm.remove(pm[page.range.second - 1u]);
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
                  return;
            }

            /* Promote page to a label */
            inline void page_to_label(pass_manager &pm, const tools::paging::details::page &page) {

                  const auto avaliable = pm.ir.avaliable_label();

                  pm.insert(pm[page.range.first], tools::stat::generate::label(avaliable));

                  for (const auto &[exp, a_es] : page.references) {

                        for (const auto &i : a_es) {

                              if (i.stat) {
                                    if (const auto &stat = (!exp ? pm[i.n] : exp->closure[i.n]); tools::stat::is_page_function_jump(stat)) {
                                          pm.remove(stat);
                                          pm.insert(stat, tools::stat::generate::goto_label(avaliable));
                                          continue;
                                    }
                              }
                        }
                  }
                  page_deletion(pm, page);
                  return;
            }
      } // namespace promote

      void page_promotion(pass_manager &pm, shared &s) {

            for (const auto &[expr, pages] : tools::paging::gen_details(pm).pages) {

                  for (const auto &[id, page] : pages) {

                        if (pm[page.range.first]->flags.fpage_seperated) {
                              continue;
                        }
                        switch (tools::paging::suggest_promotion(pm, page)) {
                              case tools::paging::promotion_kind::closure_label: {
                                    break;
                              }
                              case tools::paging::promotion_kind::page_label: {

                                    promote::page_to_label(pm, page);
                                    break;
                              }
                              case tools::paging::promotion_kind::none: {

                                    promote::page_deletion(pm, page);
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

      void merge_label_page(pass_manager &pm, shared &s) {

            const auto pages = tools::paging::gen_details(pm);

            for (const auto &[label_loc, refs_locs] : tools::accumulate::labels(pm, tools::transform::address_to_range(0u, pm.ir.data.size()))) {

                  /* 
                     LABEL: (SAFELY TRACE TO ALL REFS LABEL)
                     PAGE_START (ALL OPTIONAL PAGES)
                     PAGE_START { 
                         ...
                         [ALL REFS]
                     /} PAGE END/
                  */
                  if (pm.valid_next<1u>(label_loc) && tools::stat::is_page_function_start(pm[label_loc + 1u])) {

                        if (const auto id = pages.same_page(refs_locs); id) {

                              if (const auto &[page_found, page_loc] = tools::trackers::safe_trace_page(pm, label_loc + 1u, *id); page_found) {

                                    pm.move(pm[page_loc], pm[label_loc]);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                        }
                  }
            }
            return;
      }

      void close_pages(pass_manager &pm, shared &s) {

            boost::container::flat_set<luramas_int_base> open_pages;
            for (const auto &i : pm.ir.data) {

                  switch (i->k) {
                        case keywords::page_function_start: {

                              if (i->r->is_integral()) {
                                    open_pages.insert(i->r->extract_integral_base());
                              }
                              break;
                        }
                        case keywords::page_function_end: {

                              if (i->r->is_integral()) {
                                    open_pages.erase(i->r->extract_integral_base());
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
            for (const auto &p : boost::adaptors::reverse(open_pages)) {
                  pm.push_back(tools::stat::generate::page_function_end(tools::exprs::generate::integral(p)));
            }
            return;
      }

      void allign_pages(pass_manager &pm, shared &s) {

            std::vector<tools::paging::details::page> valid_pages;

            /* Valid pages */
            for (const auto &[expr, pages] : tools::paging::gen_details(pm).pages) {
                  for (const auto &[id, page] : pages) {
                        if (page.fvalid && !pm[page.range.second - 1u]->flags.fpage_seperated) {
                              valid_pages.emplace_back(page);
                        }
                  }
            }

            const auto copy_valid = valid_pages;

            /* Organize */
            std::vector<luramas_index> organized_starts;
            std::vector<luramas_index> organized_ends;
            {
                  organized_starts.reserve(valid_pages.size());
                  organized_ends.reserve(valid_pages.size());
                  for (auto i = 0u; i < valid_pages.size(); ++i) {
                        organized_starts.emplace_back(i);
                        organized_ends.emplace_back(i);
                  }
                  std::sort(organized_starts.begin(), organized_starts.end(), [&](const auto l, const auto r) {
                        return valid_pages[l].range.first < valid_pages[r].range.first;
                  });
                  std::sort(organized_ends.begin(), organized_ends.end(), [&](const auto l, const auto r) {
                        return valid_pages[l].range.second < valid_pages[r].range.second;
                  });
            }

            /* contiguous sort */
            {

                  /* Starts */
                  for (auto it = organized_starts.begin(); it != organized_starts.end();) {
                        auto run_end = it;
                        while (std::next(run_end) != organized_starts.end() && valid_pages[*run_end].range.first + 1u == valid_pages[*std::next(run_end)].range.first) {
                              ++run_end;
                        }
                        if (run_end != it) {
                              std::vector<luramas_index> sub(it, std::next(run_end));
                              const std::vector<luramas_index> csub(it, std::next(run_end));
                              std::sort(sub.begin(), sub.end(), [&](const auto l, const auto r) {
                                    return valid_pages[l].range.second > valid_pages[r].range.second;
                              });
                              std::vector<luramas_address> ends;
                              for (auto idx = 0u; idx < csub.size(); ++idx) {
                                    ends.emplace_back(valid_pages[sub[idx]].range.first);
                              }
                              for (auto idx = 0u; idx < csub.size(); ++idx) {
                                    valid_pages[csub[idx]].range.first = ends[idx];
                              }
                        }
                        it = std::next(run_end);
                  }

                  /* Ends */
                  for (auto it = organized_ends.begin(); it != organized_ends.end();) {
                        auto run_end = it;
                        while (std::next(run_end) != organized_ends.end() && valid_pages[*run_end].range.second + 1u == valid_pages[*std::next(run_end)].range.second) {
                              ++run_end;
                        }
                        if (run_end != it) {
                              std::vector<luramas_index> sub(it, std::next(run_end));
                              const std::vector<luramas_index> csub(it, std::next(run_end));
                              std::sort(sub.begin(), sub.end(), [&](const auto l, const auto r) {
                                    return valid_pages[l].range.first > valid_pages[r].range.first;
                              });
                              std::vector<luramas_address> ends;
                              for (auto idx = 0u; idx < csub.size(); ++idx) {
                                    ends.emplace_back(valid_pages[sub[idx]].range.second);
                              }
                              for (auto idx = 0u; idx < csub.size(); ++idx) {
                                    valid_pages[csub[idx]].range.second = ends[idx];
                              }
                        }
                        it = std::next(run_end);
                  }
            }

            /* Mutate */
            {

                  for (auto i = 0u; i < valid_pages.size(); ++i) {

                        const auto &[og_s, og_e] = copy_valid[i].range;
                        const auto &[curr_s, curr_e] = valid_pages[i].range;
                        if (og_s != curr_s) {
                              pm.move(pm[og_s], pm[curr_s]);
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                        if (og_e != curr_e) {
                              pm.move(pm[og_e - 1u], pm[curr_e - 1u]);
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                  }
            }
            return;
      }

      void complete_pages(pass_manager &pm, shared &s) {

            const auto cfg = generation::cfg::generate(pm.ir, LURAMAS_IR_ENTRY, pm.env_flags.fhas_pages);
            for (const auto &[expr, map] : tools::paging::gen_details(pm).pages) {
                  for (const auto &[pid, page] : map) {

                        if (page.fhas_start && !page.fvalid) {

                              const auto end_stat = tools::stat::generate::page_function_end(tools::exprs::generate::integral(pid));
                              end_stat->flags.funsafe = pm.env_flags.funsafe_pages;
                              pm[page.range.first]->flags.funsafe = pm.env_flags.funsafe_pages;

                              const auto def = tools::stat::generate::flags::paging::definition(tools::guarantee::stats::definition(pm, page.range.first, page.range.first + 1u));
                              if (pm[page.range.first]->flags.fpage_main) {
                                    def->flags.fpage_main = true;
                              }
                              if (const auto end = tools::paging::get_pending_page_end_loc(pm, cfg, page); end) {
                                    pm.insert(pm[*end], end_stat);
                              } else {
                                    pm.insert(pm[page.range.first], end_stat);
                              }
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                  }
            }
            return;
      }

      void generate_page_pass(pass_manager &pm, shared &s) {

            boost::unordered_flat_map<luramas_id, tools::paging::details::page> pages;
            for (const auto &[expr, map] : tools::paging::gen_details(pm).pages) {
                  for (const auto &[pid, page] : map) {
                        pages[pid] = page;
                  }
            }

            std::vector<boost::unordered_flat_set<luramas_register>> stack;
            for (auto i = 0u; i < pm.ir.data.size(); ++i) {

                  const auto &stat = pm[i];
                  if (tools::stat::is_page_function_start(stat)) {

                        stack.emplace_back(boost::unordered_flat_set<luramas_register>());
                  }

                  if (!stack.empty() && tools::stat::is_page_function_end(stat)) {

                        if (tools::paging::analyze_page_falls(pm, pages[stat->r->extract_integral_base()]).ffalls_out && !stack.back().empty()) {

                              /* Generate */
                              const auto p = tools::stat::generate::page_function_pass();
                              for (const auto &i : stack.back()) {
                                    p->members.emplace_back(tools::exprs::generate::reg(i));
                              }
                              pm.insert(pm[i], p);
                              pm.mut(LURAMAS_DEBUG_LINE);

                              /* Popagate back */
                              const auto &tail = stack.back();
                              for (auto j = stack.size() - 1u; j > 0; --j) {
                                    stack[j - 1u].insert(tail.begin(), tail.end());
                              }
                        }
                        stack.pop_back();
                  }

                  /* Add values */
                  if (!stack.empty()) {
                        for (const auto &r : stat->extract_ordered_lvalues()) {
                              if (tools::exprs::values::is_reg(r)) {
                                    stack.back().insert(r->reg);
                              }
                        }
                  }
            }
            return;
      }

      void organize_pages(pass_manager &pm, shared &s) {

            /* Set main page flag */
            {
                  auto i = pm.ir.data.size() - 1u;
                  for (; i; --i) {

                        const auto &p = pm[i];
                        if (tools::stat::is_page_function_end(p)) {
                              if (const auto it = pm.processed.pages.find(p->r->extract_integral_base()); it != pm.processed.pages.end()) {
                                    i = it->second.first;
                                    continue;
                              }
                        }
                        if (tools::stat::is_page_function_start(p)) {
                              continue;
                        }
                        break;
                  }
                  pm[i]->flags.fend_main_page = true;
            }

            /* Sort pages if they dont fall */
            {

                  /* Setup pages */
                  boost::unordered_flat_set<luramas_id> using_ids;
                  boost::unordered_flat_set<luramas_id> ignore_ids;
                  std::vector<tools::paging::details::page> organized_pages;
                  for (const auto &[exp, data] : tools::paging::gen_details(pm).pages) {

                        for (const auto &[pid, page] : data) {

                              if (!page.fvalid || (page.parent_id && using_ids.contains(*page.parent_id))) {
                                    continue;
                              }
                              const auto &start = pm[page.range.first];
                              if (start->flags.fpage_main || ignore_ids.contains(page.id) || start->flags.fpage_seperated) {
                                    continue;
                              }
                              if (const auto falls = tools::paging::analyze_page_falls(pm, page); !falls.ffalls_into && !falls.ffalls_out && tools::safe(pm, page.code_range(pm.ir.data))) {

                                    for (const auto &i : falls.dependant_pages_out) {
                                          organized_pages.erase(std::find_if(organized_pages.begin(), organized_pages.end(), [&](const auto &a) { return a.id == i; }));
                                    }
                                    using_ids.insert(page.id);
                                    organized_pages.emplace_back(page);
                                    ignore_ids.insert(falls.dependant_pages_out.begin(), falls.dependant_pages_out.end());
                              }
                        }
                  }
                  /* Sort pages by dependancies */

                  /* Move */
                  tools::paging::move_organized_pages(pm, organized_pages);
            }
            return;
      }

      void page_return_promotion(pass_manager &pm, shared &s) {

            const auto pages = tools::paging::gen_details(pm);
            for (const auto &i : pm.ir.data) {

                  switch (i->k) {
                        case keywords::retn: {

                              for (auto it = i->smembers.begin(); it != i->smembers.end();) {

                                    bool mut = false;
                                    if (const auto &p = *it; p->is_integral()) {

                                          if (const auto page_opt = pages.index_page(p->n.extract_base()); page_opt) {

                                                if (const auto page = *page_opt; page.second.fhas_start && page.second.range.first && page.second.references.size() == 1u) {

                                                      auto &env = page.first ? page.first->closure : pm.ir.data;
                                                      const auto &def = env[page.second.range.first + 1u];
                                                      if (auto &prev = env[page.second.range.first - 1u]; tools::stat::is_page_function_call(prev) && tools::stat::is_definition(def) && def->flags.flink_regs) {

                                                            /* Result Indexes */
                                                            i->flags.flink_regs = true;
                                                            boost::unordered_flat_set<luramas_index> idxs;
                                                            for (const auto &[r, expr] : def->args) {
                                                                  if (const auto it = i->args.find(r); it != i->args.end() && it->second->is_integral()) {
                                                                        idxs.insert(it->second->extract_integral_base());
                                                                  } else {
                                                                        i->members.emplace_back(expr);
                                                                        i->args[r] = tools::exprs::generate::integral(i->members.size() - 1u);
                                                                        idxs.insert(i->args[r]->extract_integral_base());
                                                                  }
                                                            }

                                                            /* Pad from results to assignments from indexes with nil */
                                                            if (!idxs.empty()) {

                                                                  /* Assignment */
                                                                  ir_stat::ir_expr::space result_regs;
                                                                  for (auto j = 0u; !idxs.empty(); ++j) {
                                                                        if (const auto it = idxs.find(j); it != idxs.end()) {
                                                                              tools::errors::in_range(j, i->members.size());
                                                                              idxs.erase(it);
                                                                              i->members[j]->rk = expr_reg_kinds::reg;
                                                                              result_regs.emplace_back(i->members[j]);
                                                                        } else {
                                                                              result_regs.emplace_back(tools::exprs::generate::none_object());
                                                                        }
                                                                  }

                                                                  const auto page_call = tools::exprs::generate::page_function_call(prev->r, prev->l, prev->lba, prev->members);
                                                                  page_call->flags.fexternal_page_goto = prev->flags.fexternal_page_goto;
                                                                  prev = tools::stat::generate::assignment(result_regs, page_call);
                                                                  promote::page_deletion(pm, page.second);
                                                                  pm.mut(LURAMAS_DEBUG_LINE);
                                                                  it = i->smembers.erase(it);
                                                                  mut = true;
                                                            }
                                                      }
                                                }
                                          }
                                    }
                                    if (!mut) {
                                          ++it;
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

      void page_adjust_linked(pass_manager &pm, shared &s) {

            luramas::ir::pass::process::values(pm);
            const auto details = tools::paging::gen_details(pm);
            const auto cfg = generation::cfg::generate(pm.ir, LURAMAS_IR_ENTRY, pm.ir.fhas_pages);
            const auto ssa = generation::ssa::generate(pm.ir, generation::ssa::ssa_flags({.finclude_captures = true, .finclude_references = pm.env_flags.fhas_references}), pm.processed.values, cfg);
            tools::linked::parameters::pre_adjust(pm, cfg, ssa, details, tools::paging::parent_pages(pm));
            tools::linked::args::adjust(pm, details);
            return;
      }

      void page_return_params_adjust(pass_manager &pm, shared &s) {

            const auto det = tools::paging::gen_details(pm);
            const auto parent_pages = tools::paging::parent_pages(pm);
            for (const auto &[exp, data] : det.pages) {

                  for (const auto &[pid, page] : data) {

                        if (!page.fvalid) {
                              continue;
                        }
                        for (const auto &addr : luramas_iter(page.range)) {

                              if (parent_pages[addr] != pid) {
                                    continue;
                              }
                              if (const auto &ret = pm[addr]; tools::stat::is_page_return(ret)) {

                                    for (const auto &id : ret->smembers) {

                                          if (id->is_integral()) {

                                                if (const auto &page = det.index_page(id->extract_integral_base()); page) {

                                                      if (const auto &def = (*page).second.definition; def && ret->members.size() < def->args.size()) {

                                                            /* Go through each definitio see if it exists in page return index */
                                                            for (const auto &[r, _] : def->args) {

                                                                  if (ret->args.try_emplace(r, tools::exprs::generate::integral(ret->members.size())).second) {
                                                                        ret->members.emplace_back(tools::exprs::generate::reg(r));
                                                                  }
                                                            }
                                                      }
                                                }
                                          }
                                    }
                              }
                        }
                  }
            }
            return;
      }

      void page_code_organization(pass_manager &pm, shared &s) {

            /* Organize by scope */
            for (const auto &[exp, data] : tools::paging::gen_details(pm).pages) {

                  for (const auto &[pid, page] : data) {

                        /* Already safe? */
                        if (pm[page.range.first]->flags.fpage_seperated || (page.fhas_start && !pm.is_safe(pm[page.range.first])) || (page.fvalid && !pm.is_safe(pm[page.range.second - 1u]))) {
                              continue;
                        }

                        /* End see if there is any errors */
                        const auto end = tools::paging::page_safe_end(pm, page);
                        if (!end || *end == page.range.second - 2u) {
                              continue;
                        }

                        /* Contigous ends  */
                        if (page.fvalid) {

                              const tools::find::find_stat_cb pend = [](const std::shared_ptr<ir_stat> &stat) { return tools::stat::is_page_function_end(stat); };
                              const auto contig_end = tools::find::contiguous_stat(pm, LURAMAS_IR_DIRECTION_KINDS::backward, *end, pend);
                              if (const auto addr = tools::find::contiguous_stat(pm, LURAMAS_IR_DIRECTION_KINDS::forward, tools::stat::valid_next_n(pm, contig_end), pend); tools::contains::address({contig_end, addr}, page.range.second - 1u)) {
                                    continue;
                              }
                        }

                        /* Insert */
                        const auto &[where, stat] = std::tie(pm[*end], pm[page.range.second - 1u]);
                        if (page.fvalid) {

                              if (!pm.safe(where, stat)) {
                                    continue;
                              }
                              pm.move(where, stat);
                        } else {

                              if (!pm.safe(where)) {
                                    continue;
                              }
                              pm.insert(where, tools::stat::generate::page_function_end(tools::exprs::generate::integral(page.id)));
                        }
                        pm.mut(LURAMAS_DEBUG_LINE);
                  }
            }
            return;
      }

      void page_referenced_out_of_scope(pass_manager &pm, shared &s) {

            /* Organize by scope */
            for (auto &[exp, data] : tools::paging::gen_details(pm).pages) {

                  for (const auto &[pid, page] : data) {

                        for (const auto &[env, ae] : page.references) {

                              for (const auto &i : ae) {

                                    if (page.fhas_start && i.n > page.range.first) {

                                          pm[page.range.first]->flags.fpage_referenced_out_scope = true;
                                          if (page.fvalid) {
                                                pm[page.range.second]->flags.fpage_referenced_out_scope = true;
                                          }
                                          if (i.stat) {
                                                pm[i.n]->flags.fpage_referenced_out_scope = true;
                                          } else {
                                                i.e->flags.fpage_referenced_out_scope = true;
                                          }
                                    }
                              }
                        }
                  }
            }
            return;
      }

      void page_promote_nofall_part1(pass_manager &pm, shared &s) {

            std::vector<tools::paging::details::page> organized_pages;
            for (auto &[exp, data] : tools::paging::gen_details(pm).pages) {

                  for (const auto &[pid, page] : data) {

                        if (!page.fvalid || pm[page.range.first]->flags.fpage_main) {
                              continue;
                        }
                        const auto falls = tools::paging::analyze_page_falls(pm, page);
                        if ((falls.ffalls_into || falls.ffalls_out) && tools::safe(pm, page.code_range(pm.ir.data))) {

                              if (falls.ffalls_into) {
                                    s.scheduled_inserts[pm[tools::visitors::prev_loc(pm, page.range.first)]].emplace_back(tools::stat::generate::page_function_jump(tools::exprs::generate::integral(pid)));
                              }
                              if (falls.ffalls_out) {
                                    const auto label = pm.ir.avaliable_label();
                                    s.scheduled_inserts[pm[page.range.second - 2u]].emplace_back(tools::stat::generate::goto_label(label));
                                    pm.insert(pm[page.range.second - 1u], tools::stat::generate::label(label));
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              organized_pages.emplace_back(page);
                        }
                  }
            }
            tools::paging::move_organized_pages(pm, organized_pages);
            return;
      }
      void page_promote_nofall_part2(pass_manager &pm, shared &s) {

            for (const auto &[on, data] : s.scheduled_inserts) {
                  pm.insert(on, data);
                  pm.mut(LURAMAS_DEBUG_LINE);
            }
            s.scheduled_inserts.clear();
            return;
      }
      void add_page_promote_nofall(pass_manager &pm, const flags &flag, const std::string &debug) {
            pm.add(page_promote_nofall_part1, flag, debug);
            pm.add(page_promote_nofall_part2, flag, debug);
            return;
      }

      void page_generate_main_page(pass_manager &pm, shared &s) {

            const auto pn = pm.ir.avaliable_page();
            const auto p = tools::stat::generate::page_function_start(tools::exprs::generate::integral(pn));
            p->flags.fpage_main = true;
            pm.insert(pm[LURAMAS_IR_ENTRY], p);
            pm.mut(LURAMAS_DEBUG_LINE);
            return;
      }

      void page_promote_global_gotos_controllers(pass_manager &pm, shared &s) {

            const auto pages = tools::paging::gen_details(pm);
            const auto parent_pages = tools::paging::parent_pages(pm);

            boost::unordered_flat_map<luramas_id, boost::unordered_flat_set<luramas_address>> controlling_gotos;
            for (const auto &i : pm.iter()) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::goto_label:
                        case keywords::condition_goto: {

                              const auto label = tools::common::safe_take_jump(pm, i);
                              if (i >= parent_pages.size() || label >= parent_pages.size()) {
                                    continue;
                              }

                              const auto &pcurr = parent_pages[i];
                              const auto &plabel = parent_pages[label];
                              if (!pcurr || !plabel) {
                                    continue;
                              }
                              if (pcurr == plabel) {
                                    continue;
                              }

                              const auto lab = p->jlabel;
                              const auto plabel_id = pm[*plabel]->r->extract_integral();
                              if (const auto id = tools::exprs::generate::integral(plabel_id); tools::stat::branch::is_goto(p)) {

                                    const auto j = tools::stat::generate::page_function_jump(id);
                                    j->v = tools::exprs::generate::integral(lab);
                                    pm.insert(p, j);
                                    pm.remove(p);
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              } else if (tools::stat::branch::is_cond_goto(p)) {

                                    const auto j = tools::stat::generate::page_function_jump(id);
                                    j->v = tools::exprs::generate::integral(lab);
                                    tools::stat::mutate::if_stat_cleared(p);
                                    pm.insert(p, j, tools::stat::generate::end());
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              } else {
                                    continue;
                              }
                              controlling_gotos[plabel_id.extract_base()].insert(lab);
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }

            for (auto &[pid, refs] : controlling_gotos) {

                  if (const auto p = pages.index_page(pid); p) {

                        const auto &page = (*p).second;
                        const auto range = page.code_range(pm.ir.data);

                        /* Remove already controlled */
                        auto i = range.first;
                        while (pm.contains(i)) {

                              const auto &s = pm[i];
                              if (tools::stat::branch::is_controller_if_cond_goto(s)) {
                                    refs.erase(s->r->extract_integral_base());
                                    i = tools::common::safe_take_jump(pm, i) + 1u;
                                    continue;
                              }
                              break;
                        }

                        /* Add */
                        for (const auto &r : refs) {
                              pm.insert_front(range.first, tools::stat::generate::cond_goto_label(tools::exprs::generate::controller(), il::arch::data::bin_kinds::eq_, r, tools::exprs::generate::integral(r)));
                        }
                  }
            }
            // pm.mut(LURAMAS_DEBUG_LINE);
            return;
      }

      void page_promote_orphans(pass_manager &pm, shared &s) {

            const auto parent_pages = tools::paging::parent_pages(pm);
            for (const auto &[exp, data] : tools::paging::gen_details(pm).pages) {

                  for (const auto &[pid, page] : data) {

                        if (!page.fvalid) {
                              continue;
                        }
                        const auto &start = pm[page.range.first];
                        if (start->flags.fpage_main || start->flags.fpage_seperated) {
                              continue;
                        }
                        if (const auto r = page.code_range(pm.ir.data); tools::safe_page_code_no_loops(pm, r) && tools::contains::orphans::implicit_goto(pm, r)) {

                              for (const auto &i : tools::accumulate::orphans::implicit_gotos(pm, r)) {

                                    const auto &stat = pm[i];
                                    if (tools::stat::is_break(stat)) {

                                          const auto lab = pm.ir.avaliable_label();
                                          pm.insert(stat, tools::stat::generate::goto_label(lab));
                                          pm.insert(pm[tools::common::safe_take_jump(pm, i)], tools::stat::generate::label(lab));
                                          pm.remove(stat);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                          continue;
                                    }
                                    if (tools::stat::is_continue(stat)) {

                                          const auto lab = pm.ir.avaliable_label();
                                          pm.insert(stat, tools::stat::generate::goto_label(lab));
                                          pm.insert_front(tools::common::safe_take_jump(pm, i), tools::stat::generate::label(lab));
                                          pm.remove(stat);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                          continue;
                                    }
                              }
                        }
                  }
            }
            return;
      }

      void pages_set_controller_flag(pass_manager &pm, shared &s) {

            for (const auto &[expr, map] : tools::paging::gen_details(pm).pages) {
                  for (const auto &[pid, page] : map) {

                        if (!page.definition || !page.fvalid) {
                              continue;
                        }
                        for (auto i = page.range.first; i < page.range.second; ++i) {

                              if (pm[i]->contains(tkind::controller)) {
                                    page.definition->flags.fdef_uses_controller = true;
                              }
                        }
                  }
            }
            return;
      }

      void page_inliner(pass_manager &pm, shared &s) {

            const auto page_details = tools::paging::gen_details(pm);
            const auto parent_pages = tools::paging::parent_pages(pm);
            for (const auto &[expr, map] : page_details.pages) {
                  for (const auto &[pid, page] : map) {

                        if (!tools::inliner::cva::can_inline(pm, parent_pages, page) ||
                            !pm.is_safe(page.range) ||
                            !std::ranges::all_of(page.references, [&](const auto &p) { return std::ranges::all_of(p.second, [&](const auto &b) { return pm.is_safe(pm[b.n]); }); })) {
                              continue;
                        }

                        tools::eliminate::page(pm, page_details, page);
                        pm.remove(page.range);
                  }
            }
            return;
      }

      void dead_controller_removal(pass_manager &pm, shared &s) {

            luramas::ir::pass::process::values(pm);

            auto parent_pages = tools::paging::parent_pages(pm);
            auto set_controllers = tools::controllers::set(pm);

            for (const auto &i : pm.iter()) {

                  const auto &p = pm[i];
                  if (tools::stat::branch::is_controller_if(p)) {
                        if (const auto pid = parent_pages[i]; pid && !set_controllers[*pid].contains(p->r->extract_integral_base())) {
                              p->l = tools::exprs::generate::boolean(true);
                              p->r = tools::exprs::generate::boolean(false);
                        }
                  }
                  for (const auto &e : pm.processed.values.find(p)->second.all) {
                        if (tools::exprs::values::is_cond_controller(e)) {
                              if (const auto pid = parent_pages[i]; pid && !set_controllers[*pid].contains(e->r->extract_integral_base())) {
                                    const auto b = e->b;
                                    e->clear();
                                    e->emit_boolean(b == il::arch::data::bin_kinds::ne_);
                              }
                        }
                  }
            }
            return;
      }
} // namespace luramas::ir::passes