#include "../../passes/process/process.hpp"
#include "../tools.hpp"
#include <stack>

namespace luramas::ir::tools::paging {

      bool details::page::is_recoverable() const {
            return !this->references.empty() && this->fhas_start;
      }
      luramas_blockrange details::page::code_range(const ir_stat::space &p) const {
            if (this->fvalid) {
                  auto result = this->range;
                  result.first += tools::stat::is_definition(p[++result.first]);
                  --result.second;
                  return result;
            }
            return this->range;
      }

      std::optional<luramas_id> details::get_page(const luramas_address &loc, const std::shared_ptr<ir_stat::ir_expr> &parent_closure_expr) const {

            luramas_id result = 0u;
            auto [found, dominant_start] = std::make_pair(false, static_cast<luramas_address>(0u));

            if (const auto it = this->pages.find(parent_closure_expr); it != this->pages.end()) {
                  for (const auto &[id, page] : it->second) {
                        if (tools::stat::past(page.range.first, loc)) {
                              break;
                        }
                        if (page.fhas_start && tools::contains::address(page.range, loc) && (!found || dominant_start < page.range.first)) {
                              found = true;
                              result = page.id;
                              dominant_start = page.range.first;
                        }
                  }
            }
            return found ? std::optional<luramas_id>(result) : std::nullopt;
      }

      std::optional<luramas_id> details::same_page(const luramas_addresses &loc, const std::shared_ptr<ir_stat::ir_expr> &parent_closure_expr) const {

            if (loc.empty()) {
                  return std::nullopt;
            }

            const auto target = this->get_page(loc.front(), parent_closure_expr);
            for (auto it = std::next(loc.begin()); it != loc.end(); ++it) {
                  if (this->get_page(*it, parent_closure_expr) != target) {
                        return std::nullopt;
                  }
            }
            return target;
      }

      std::optional<std::pair<std::shared_ptr<ir_stat::ir_expr>, details::page>> details::index_page(const luramas_id id) const {

            for (const auto &[expr, data] : this->pages) {
                  for (const auto &[pid, page] : data) {
                        if (pid == id) {
                              return std::make_pair(expr, page);
                        }
                  }
            }
            return std::nullopt;
      }

      details gen_details(passes::pass_manager &pm, const bool deep) {

            details result;

            /* Propagate */
            result.pages[nullptr] = boost::unordered_flat_map<luramas_id, details::page>();
            if (deep) {
                  for (const auto &i : tools::extract::closures(pm, true)) {
                        result.pages[i] = boost::unordered_flat_map<luramas_id, details::page>();
                  }
            }

            for (auto &[expr, map] : result.pages) {

                  const auto &closure = !expr ? pm.ir.data : expr->closure;

                  std::stack<luramas_id> page_stack;
                  for (auto i = LURAMAS_IR_ENTRY; i < closure.size(); ++i) {

                        const auto &p = closure[i];
                        switch (p->k) {
                              case keywords::page_function_closure: {
                                    const auto idx = p->r->extract_integral_base();
                                    auto &page = map[idx];
                                    page.id = idx;
                                    page.fpromoted = true;
                                    page.range.first = i;
                                    page.index = expr;
                                    page.fhas_start = true;
                                    if (!page_stack.empty()) {
                                          page.parent_id = page_stack.top();
                                          map[*page.parent_id].encapsulating_pages.emplace_back(idx);
                                    }
                                    break;
                              }
                              case keywords::page_function_start: {
                                    const auto idx = p->r->extract_integral_base();
                                    auto &page = map[idx];
                                    page.id = idx;
                                    page.fvalid = true;
                                    page.range.first = i;
                                    page.index = expr;
                                    page.fhas_start = true;
                                    if (!page_stack.empty()) {
                                          page.parent_id = page_stack.top();
                                          map[*page.parent_id].encapsulating_pages.emplace_back(idx);
                                    }
                                    if (closure.size() > i + 1u && tools::stat::is_definition(closure[i + 1u])) {
                                          page.definition = closure[i + 1u];
                                    }
                                    page_stack.push(idx);
                                    break;
                              }
                              case keywords::page_function_end: {
                                    if (auto it = map.find(p->r->extract_integral_base()); it != map.end()) {
                                          it->second.range.second = i + 1u;
                                          if (!page_stack.empty()) {
                                                page_stack.pop();
                                          }
                                    }
                                    break;
                              }
                              case keywords::page_function_goto: {
                                    map[p->r->extract_integral_base()].references[expr].emplace_back(i);
                                    break;
                              }
                              case keywords::retn: {
                                    if (tools::stat::is_page_return(p)) {
                                          for (const auto &m : p->smembers) {
                                                if (!m->is_integral()) {
                                                      continue;
                                                }
                                                map[m->extract_integral_base()].references[expr].emplace_back(i);
                                          }
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }

                        /* Extract expr calls */
                        for (const auto &e : p->extract_ordered_exprs()) {
                              if (tools::exprs::values::is_page_function_call(e) && e->r->is_integral()) {
                                    map[e->r->extract_integral_base()].references[expr].emplace_back(addr_expr(i, e));
                              }
                        }
                  }
            }

            for (auto &[expr, map] : result.pages) {
                  for (auto &[id, page] : map) {
                        page.fvalid = page.range.second;
                  }
            }
            return result;
      }

      promotion_kind suggest_promotion(passes::pass_manager &pm, const details::page &target) {

            /* Not valid */
            if (!target.fvalid) {
                  return promotion_kind::none;
            }

            /* Main page? */
            if (pm[target.range.first]->flags.fpage_main) {
                  return promotion_kind::immutable;
            }

            /* No refs */
            if (target.references.empty()) {
                  return target.fcall_exclusive ? promotion_kind::none : target.fpromoted ? promotion_kind::closure_label
                                                                                          : promotion_kind::page_label;
            }

            /* Already promoted */
            if (target.fpromoted) {
                  return promotion_kind::immutable;
            }

            /* Accumulate call refs and jump refs */
            luramas_count call_refs = 0u;
            luramas_count jump_refs = 0u;
            luramas_count retn_refs = 0u;
            for (const auto &[expr, a_es] : target.references) {

                  const auto &data = (!expr ? pm.ir.data : expr->closure);
                  for (const auto &a_e : a_es) {

                        if (a_e.stat) {
                              const auto &stat = data[a_e.n];
                              call_refs += tools::stat::is_page_function_call(stat);
                              jump_refs += tools::stat::is_page_function_jump(stat);
                              retn_refs += tools::stat::is_return(stat) && stat->flags.fpage_keyword;
                        } else {
                              call_refs += tools::exprs::values::is_page_function_call(a_e.e);
                        }
                  }
            }

            if (call_refs || retn_refs) {
                  return promotion_kind::immutable;
            }

            if (jump_refs == 1u) {
                  const auto first_id = target.references.begin()->first;
                  return std::ranges::all_of(target.references, [&](const auto &i) { return i.first == first_id; }) ? promotion_kind::page_label : promotion_kind::immutable;
            }

            /* No call/ret refs */
            return promotion_kind::page_label;
      }

      std::optional<luramas_address> get_pending_page_end_loc(passes::pass_manager &pm, const generation::cfg::cfg &cfg, const details::page &page) {

            if (page.fvalid || !tools::stat::is_page_function_start(pm[page.range.first])) {
                  return std::nullopt;
            }

            auto result = page.range.first + 1u;
            const auto entry = cfg.visit(result);
            if (!entry) {
                  return std::nullopt;
            }

            std::vector<std::shared_ptr<generation::cfg::block>> pending = {entry};
            boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> visited;

            while (!pending.empty()) {

                  /* Setup */
                  const auto b = pending.back();
                  pending.pop_back();

                  if (!b || visited.contains(b) || contains::address({0u, page.range.first}, b->get_front())) {
                        continue;
                  }
                  visited.insert(b);

                  /* Out of bounds */
                  if (b->get_front() < page.range.first) {
                        continue;
                  }

                  if (b->get_end() > result) {
                        result = b->get_end() ? b->get_end() - 1u : result;
                  }
                  if (pending.empty() && (control_flow::block::is_jump(b) || pm[b->get_end() - 1u]->is_terminator())) {
                        break;
                  }

                  pending.emplace_back(b->jump);
                  pending.emplace_back(b->fall);
            }
            return result;
      }

      std::optional<luramas_address> parent_page(passes::pass_manager &pm, const luramas_address curr) {

            if (!pm.contains(curr)) {
                  return std::nullopt;
            }

            boost::unordered_flat_set<luramas_id> visited;
            for (auto i = curr;; --i) {
                  const auto &stat = pm[i];
                  if (tools::stat::is_page_function_start(stat) && !visited.contains(stat->r->extract_integral_base())) {
                        return i;
                  }
                  if (tools::stat::is_page_function_end(stat)) {
                        visited.insert(stat->r->extract_integral_base());
                  }
                  if (!i) {
                        break;
                  }
            }
            return std::nullopt;
      }

      std::vector<std::optional<luramas_address>> parent_pages(passes::pass_manager &pm) {

            std::vector<std::optional<luramas_address>> result;
            std::vector<std::pair<luramas_address, luramas_id>> stack;
            for (auto i = 0u; i < pm.ir.data.size(); ++i) {
                  const auto &stat = pm[i];
                  result.emplace_back(!stack.empty() ? std::optional<luramas_address>(stack.back().first) : std::nullopt);
                  if (tools::stat::is_page_function_start(stat)) {
                        stack.emplace_back(i, stat->r->extract_integral_base());
                  }
                  if (tools::stat::is_page_function_end(stat)) {
                        const auto id = stat->r->extract_integral_base();
                        std::erase_if(stack, [&](const auto &p) {
                              return p.second == id;
                        });
                  }
            }
            return result;
      }

      boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> encapsulating_pages(passes::pass_manager &pm, const details &pages, const std::vector<std::optional<luramas_address>> &parent_pages) {

            boost::unordered_flat_set<luramas_address> visited;
            boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> result;
            result.reserve(pages.pages.size());

            for (const auto &[exp, data] : pages.pages) {

                  for (const auto &[pid, page] : data) {

                        if (page.fvalid) {

                              if (const auto it = std::find_if(parent_pages.begin(), parent_pages.end(), [&](const auto &opt) { return opt && (*opt == page.range.first); }); it != parent_pages.end()) {

                                    visited = {it->value()};

                                    if (const auto curr_start = (exp ? exp->closure : pm.ir.data)[it->value()]; tools::exprs::basic::is_integral(curr_start->r)) {

                                          visited = {it->value()};
                                          for (auto i = static_cast<std::size_t>(std::distance(parent_pages.begin(), it)); i < parent_pages.size(); ++i) {

                                                if (tools::stat::is_page_function_end(pm[i], curr_start->r->extract_integral_base())) {
                                                      break;
                                                }

                                                if (const auto v = parent_pages[i]; v) {

                                                      if (const auto &page_start = (exp ? exp->closure : pm.ir.data)[*v]; tools::stat::is_page_function_start(page_start) && tools::exprs::basic::is_integral(page_start->r)) {

                                                            if (const auto id = page_start->r->extract_integral_base(); visited.insert(*v).second) {

                                                                  result.try_emplace(page.id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>()).first->second.emplace_back(exp, id);
                                                            }
                                                      }
                                                }
                                          }
                                    }
                              }
                        }
                  }
            }
            return result;
      }

      boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> parents_encapsulating_pages(const boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> &encapsulating_pages) {

            boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> result;
            result.reserve(encapsulating_pages.size());

            for (const auto &[pid, data] : encapsulating_pages) {
                  for (const auto &[exp, encap_pid] : data) {
                        result[encap_pid].emplace_back(exp, pid);
                  }
            }
            return result;
      }

      boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> successor_pages(passes::pass_manager &pm, const details &pages, const generation::cfg::cfg &cfg, const std::vector<std::optional<luramas_address>> &parent_pages, const boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> &encapsulated_parents) {

            boost::unordered_flat_set<luramas_id> visited;
            boost::unordered_flat_map<luramas_id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>> result;
            result.reserve(pages.pages.size());

            /* Add */
            for (const auto &[exp, data] : pages.pages) {

                  for (const auto &[pid, page] : data) {

                        if (page.fvalid) {

                              visited.clear();
                              for (const auto &[k, b] : control_flow::accumulate_ranged_jumps_outs(cfg, page.range)) {

                                    if (k != generation::cfg::block_kind::fall) {

                                          if (const auto v = parent_pages[b->get_front()]; v) {

                                                if (const auto &page_start = (exp ? exp->closure : pm.ir.data)[*v]; tools::stat::is_page_function_start(page_start) && tools::exprs::basic::is_integral(page_start->r)) {

                                                      if (const auto id = page_start->r->extract_integral_base(); visited.insert(id).second) {

                                                            result.try_emplace(page.id, std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas_id>>()).first->second.emplace_back(exp, id);
                                                      }
                                                }
                                          }
                                    }
                              }
                        }
                  }
            }

            /* Remove */
            for (const auto &[pid, data] : encapsulated_parents) {

                  for (const auto &[exp, parent_pid] : data) {

                        for (auto &[rid, rdata] : result) {

                              for (auto it = rdata.begin(); it != rdata.end();) {
                                    if (it->second == parent_pid || it->second == rid) {
                                          it = rdata.erase(it);
                                    } else {
                                          ++it;
                                    }
                              }
                        }
                  }
            }
            return result;
      }

      boost::unordered_flat_map<luramas_id, std::shared_ptr<ir_stat>> map_definitions(const details &det) {

            boost::unordered_flat_map<luramas_id, std::shared_ptr<ir_stat>> result;
            for (const auto &[exp, data] : det.pages) {
                  for (const auto &[pid, page] : data) {
                        if (page.fvalid && page.definition) {
                              result[page.id] = page.definition;
                        }
                  }
            }
            return result;
      }

      page_falls_result analyze_page_falls(passes::pass_manager &pm, const details::page &target) {

            page_falls_result result;

            const find::find_stat_cb f = [](const std::shared_ptr<ir_stat> &stat) { return !stat::is_page_function_end(stat) && !stat->is_psuedo(); };

            /* Fall into */
            if (target.fhas_start) {
                  if (const auto addr = find::stat(pm, LURAMAS_IR_DIRECTION_KINDS::backward, stat::valid_prev_n(pm, target.range.first), f); addr) {

                        result.ffalls_into = control_flow::next_instruction_executed(pm, *addr);
                        if (result.ffalls_into) {
                              for (auto i = *addr + 1u; i < target.range.first; ++i) {
                                    if (const auto &e = pm[i]; tools::stat::is_page_function_end(e)) {
                                          result.dependant_pages_into.emplace_back(e->r->extract_integral_base());
                                    }
                              }
                        }
                  }
            }

            /* Fall out */
            if (target.fvalid) {
                  if (const auto addr = find::stat(pm, LURAMAS_IR_DIRECTION_KINDS::backward, target.range.second - 2u, f); addr) {

                        result.ffalls_out = control_flow::next_instruction_executed(pm, *addr);
                        if (result.ffalls_out) {
                              for (auto i = *addr + 1u; i < target.range.second - 2u; ++i) {
                                    if (const auto &e = pm[i]; tools::stat::is_page_function_end(e)) {
                                          result.dependant_pages_out.emplace_back(e->r->extract_integral_base());
                                    }
                              }
                        }
                  }
            }

            result.findependant = !result.ffalls_into && !result.ffalls_out;
            return result;
      }

      std::optional<luramas_address> page_safe_end(luramas::ir::passes::pass_manager &pm, const details::page &page) {
            if (!page.fhas_start) {
                  return std::nullopt;
            }
            if (pm[page.range.first]->flags.fpage_main) {
                  return pm.amount() - 1u;
            }
            const auto result = violations::block_violates(pm, page.range.first, pm.amount(), violations::block_violates_flags({.finclude_gotos = true, .finclude_terminals = true, .ovalid_cb = [](const std::shared_ptr<ir_stat> &stat) { return stat->is_paging_control_flow_transfer(); }, .finclude_implicit = true}));
            auto res = result.valid ? result.ending_loc : result.ending_loc - 1u;
            while (stat::is_page_function_start(pm[res])) {
                  --res;
            }
            return res;
      }

      bool is_recursive(const details &det, const luramas_id tid, const luramas_address loc, const std::vector<std::optional<luramas_address>> &parent_pages) {

            if (const auto pid = det.get_page(loc); pid) {

                  if (const auto page = det.index_page(*pid); page) {

                        if (const auto l = (*page).second.range.first + 1u; l < parent_pages.size()) {

                              return parent_pages[l] == tid;
                        }
                  }
            }
            return false;
      }

      bool referenced_in_page(const details::page &page) {

            if (page.fvalid) {

                  for (const auto &[_, e] : page.references) {
                        for (const auto &i : e) {
                              if (tools::contains::address(page.range, i.n)) {
                                    return true;
                              }
                        }
                  }
            }
            return false;
      }

      void move_organized_pages(luramas::ir::passes::pass_manager &pm, const std::vector<tools::paging::details::page> &organized_pages) {

            if (organized_pages.empty()) {
                  return;
            }

            const auto label = pm.ir.avaliable_label();
            auto entry = pm[LURAMAS_IR_ENTRY];
            if (pm.valid_next<1u>(LURAMAS_IR_ENTRY) && tools::stat::branch::is_goto(pm[LURAMAS_IR_ENTRY + 1u])) {
                  entry = pm[LURAMAS_IR_ENTRY + 1u];
            }
            if (!entry->flags.fpage_seperator) {
                  pm.insert(entry, tools::stat::generate::flags::paging::seperator(tools::stat::generate::goto_label(label)));
                  pm.mut(LURAMAS_DEBUG_LINE);
            }

            /* Handle intersects then move */
            {
                  boost::unordered_flat_map<luramas_address, luramas_index> addr_range;

                  for (auto i = 0u; i < organized_pages.size(); ++i) {

                        const auto &page = organized_pages[i];
                        for (auto n = page.range.first; n < page.range.second; ++n) {

                              if (page.range.first == n || page.range.second == n - 1u) {
                                    addr_range[n] = i;
                              } else if (const auto it = addr_range.find(n); it == addr_range.end() || (page.range.second - page.range.first) < (organized_pages[it->second].range.second - organized_pages[it->second].range.first)) {
                                    addr_range[n] = i;
                              }
                        }
                  }
                  for (auto i = 0u; i < organized_pages.size(); ++i) {

                        luramas_flag fmuted = false;
                        const auto &page = organized_pages[i];
                        for (auto n = page.range.first; n < page.range.second; ++n) {

                              if (addr_range[n] == i) {
                                    fmuted = true;
                                    pm.move(entry, pm[n]);
                              }
                        }
                        if (fmuted) {
                              pm[page.range.first]->flags.fpage_seperated = true;
                              pm[page.range.second - 1u]->flags.fpage_seperated = true;
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                  }
            }
            if (!entry->flags.fpage_seperator) {
                  pm.insert(entry, tools::stat::generate::flags::paging::seperator(tools::stat::generate::label(label)));
                  pm.mut(LURAMAS_DEBUG_LINE);
            }
            return;
      }

      return_data gen_return_data(luramas::ir::passes::pass_manager &pm, const details::page &page, const std::vector<std::optional<luramas_address>> &parent_pages) {

            return_data result;
            luramas_flag first_pass = false;
            for (const auto &i : luramas_iter(page.range)) {

                  if (parent_pages[i] != page.id) {
                        continue;
                  }
                  if (const auto &p = pm[i]; tools::stat::is_return(p) && p->flags.fpage_keyword) {
                        result.garunteed = (first_pass ? std::min(result.garunteed, p->members.size()) : (first_pass = true, p->members.size()));
                        result.maximum = std::max(result.maximum, p->members.size());
                  }
            }
            return result;
      }

      luramas_flag is_procedural(luramas::ir::passes::pass_manager &pm, const details::page &page, const std::vector<std::optional<luramas_address>> &parent_pages, const luramas_flag fcheck_safety) {

            if (fcheck_safety) {
                  if (const auto safe_end = page_safe_end(pm, page); !safe_end || *safe_end < page.range.second) {
                        return false;
                  }
            }
            if (!analyze_page_falls(pm, page).findependant) {
                  return false;
            }

            ir_stat::ir_expr::space exprs;
            for (const auto &i : luramas_iter(page.range)) {

                  const auto &p = pm[i];

                  /* Start or end of new page? */
                  if ((stat::is_page_function_start(p) && i != page.range.first) || (stat::is_page_function_end(p) && i != page.range.second)) {
                        return false;
                  }

                  /* Jumps out? */
                  if (stat::branch::is_goto(p) || stat::branch::is_cond_goto(p)) {

                        if (const auto loc = tools::common::safe_take_jump(pm, i); !parent_pages[loc] || *parent_pages[loc] != page.range.first) {
                              return false;
                        }
                  }

                  /* Page jump or call out? */
                  if (!p->flags.fvirtualized && (stat::is_page_function_jump(p) || stat::is_page_function_call(p))) {

                        if (p->r->is_integral() && p->r->extract_integral_base() != page.id) {
                              return false;
                        }
                  }

                  /* Expr calls */
                  exprs.clear();
                  p->extract_ordered_exprs(exprs);
                  for (const auto &e : exprs) {

                        /* Page call out? */
                        if (tools::exprs::values::is_page_function_call(e) && e->r->is_integral() && e->r->extract_integral_base() != page.id) {
                              return false;
                        }
                  }

                  /* Jumps in? */
                  if (stat::is_label(p)) {

                        if (const auto it = pm.processed.jlabels_refs.find(p->label); it != pm.processed.jlabels_refs.end()) {

                              for (const auto &i : it->second) {

                                    if (!parent_pages[i] || *parent_pages[i] != page.range.first) {
                                          return false;
                                    }
                              }
                        }
                  }
            }
            return true;
      }
} // namespace luramas::ir::tools::paging