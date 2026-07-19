#include "../../../generation.hpp"
#include <boost/container/flat_set.hpp>
#include <stack>

struct condition {
      luramas_address cond_loc = 0u;
      luramas_address ending_loc = 0u;
      luramas_address else_loc = 0u;

      explicit condition() = default;
      explicit condition(const luramas_address loc)
          : cond_loc(loc), ending_loc(0u), else_loc(0u) {
      }
};

namespace generation::cfg {

      /* Blocks */
      void block::emit(const std::shared_ptr<block> &jump, const std::shared_ptr<block> &then, const std::shared_ptr<block> &fall) {
            this->jump = jump;
            this->then = then;
            this->fall = fall;
            return;
      }
      void block::emit(const luramas_address entry, const luramas_address ending, const luramas_address nodes_begin, const luramas_address nodes_end) {
            this->entry = entry;
            this->ending = ending;
            this->node_range = {nodes_begin, nodes_end};
            return;
      }
      void block::emit(const luramas_address entry, const luramas_address ending, const luramas_blockrange range) {
            this->emit(entry, ending, range.first, range.second);
            return;
      }
      boost::fixed_vector<std::pair<edge_kind, std::shared_ptr<block>>, 3u> block::get_successors() const {

            boost::fixed_vector<std::pair<edge_kind, std::shared_ptr<block>>, 3u> result;
            if (this->fall) {
                  result.push_back({this->fallk, this->fall});
            }
            if (this->then) {
                  result.push_back({this->thenk, this->then});
            }
            if (this->jump) {
                  result.push_back({this->jumpk, this->jump});
            }
            return result;
      }
      boost::fixed_vector<std::pair<block_kind, std::shared_ptr<block>>, 3u> block::get_successors_bk() const {

            boost::fixed_vector<std::pair<block_kind, std::shared_ptr<block>>, 3u> result;
            if (this->fall) {
                  result.push_back({block_kind::fall, this->fall});
            }
            if (this->then) {
                  result.push_back({block_kind::then, this->then});
            }
            if (this->jump) {
                  result.push_back({block_kind::jump, this->jump});
            }
            return result;
      }
      boost::fixed_vector<std::shared_ptr<generation::cfg::block>, 3u> block::get_block_successors() const {
            boost::fixed_vector<std::shared_ptr<generation::cfg::block>, 3u> result;
            for (const auto &[_, b] : this->get_successors()) {
                  result.push_back(b);
            }
            return result;
      }
      edge_kind block::dominant_successor_edge(const std::shared_ptr<block> &target) const {
            if (this->jump == target && this->jumpk == edge_kind::back) {
                  return edge_kind::back;
            }
            if (this->then == target && this->thenk == edge_kind::back) {
                  return edge_kind::back;
            }
            if (this->fall == target && this->fallk == edge_kind::back) {
                  return edge_kind::back;
            }
            return this->jump == target || this->then == target || this->fall == target ? edge_kind::none : edge_kind::jump;
      }
      luramas_address block::get_end() const {
            return this->node_range.second;
      }
      luramas_address block::get_front() const {
            return this->node_range.first;
      }

      luramas_range_iter block::get_iter() const {
            return luramas_iter(this->node_range);
      }
      luramas_range_reverse_iter block::get_riter() const {
            return luramas_riter(this->node_range);
      }

      cfg generate(se_ir &ir, const luramas_address entry, const luramas_flag finclude_pages) {

            /* Data */
            generation::cfg::cfg result;
            boost::unordered_flat_map<luramas_address, std::vector<luramas_id>> expr_pages_refed;
            boost::unordered_flat_map<luramas_address, luramas_address> labels;
            boost::unordered_flat_map<luramas_address, condition> end_labels;
            boost::unordered_flat_map<luramas_address, std::shared_ptr<generation::cfg::block>> blocks;
            boost::unordered_flat_map<luramas_address, std::shared_ptr<generation::cfg::block>> paged_extra_blocks;
            boost::unordered_flat_map<luramas_address, std::vector<std::shared_ptr<generation::cfg::block>>> pages_n_edges_blocks;
            boost::unordered_flat_map<luramas_id, luramas_oblockrange> pages;
            std::vector<std::optional<luramas_address>> parent_ids;
            boost::unordered_flat_map<luramas_id, std::vector<luramas_address>> parent_page_linked_returns;

            /* Reserve */
            {
                  const auto size = ir.data.size() / 10u;
                  labels.reserve(size);
                  end_labels.reserve(size);
                  result.highlevel_scope_ids.reserve(ir.data.size());
                  if (finclude_pages) {
                        parent_ids.reserve(ir.data.size());
                        parent_page_linked_returns.reserve(size);
                  }
            }

            /* Set parent page IDs */
            if (finclude_pages) {
                  std::vector<std::pair<luramas_address, luramas_id>> stack;
                  for (auto i = LURAMAS_IR_ENTRY; i < ir.data.size(); ++i) {
                        const auto &stat = ir.data[i];
                        parent_ids.emplace_back(!stack.empty() ? std::optional<luramas_address>(stack.back().first) : std::nullopt);
                        if (stat->is_k<keywords::page_function_start>()) {
                              stack.emplace_back(i, stat->r->extract_integral_base());
                        }
                        if (stat->is_k<keywords::page_function_end>()) {
                              const auto id = stat->r->extract_integral_base();
                              std::erase_if(stack, [&](const auto &p) {
                                    return p.second == id;
                              });
                        }
                  }
            }

            /* Go through linked */
            if (finclude_pages) {
                  for (auto i = entry; i < ir.data.size(); ++i) {
                        if (const auto &p = ir.data[i]; p->flags.fpage_call_internally_managed && p->k == keywords::page_function_goto) {
                              parent_page_linked_returns[p->r->extract_integral_base()].emplace_back(i + 1u);
                        }
                  }
            }

            /* Map starts */
            {
                  luramas_id scope_id = 0u;
                  for (auto i = entry; i < ir.data.size(); ++i) {

                        const auto &p = ir.data[i];
                        if (p->end_label) {
                              if (auto [it, inserted] = end_labels.try_emplace(p->end_label, condition(i)); !inserted) {
                                    it->second.ending_loc = i;
                              }
                        }
                        if (p->elif_end_label) {
                              end_labels[p->elif_end_label].else_loc = i;
                        }
                        if (p->label) {
                              labels.try_emplace(p->label, i);
                        }
                        if (p->is_k<keywords::page_function_start>()) {
                              ++scope_id;
                              pages[p->r->extract_integral_base()].first = i;
                        }
                        if (p->is_k<keywords::page_function_end>()) {
                              if (scope_id) {
                                    --scope_id;
                              }
                              pages[p->r->extract_integral_base()].second = i;
                        }
                        if (finclude_pages) {
                              for (const auto &e : p->extract_ordered_deep_exprs()) {
                                    if (e->is_k<expr_kinds::page_function_call>()) {
                                          expr_pages_refed[i].emplace_back(e->r->extract_integral_base());
                                    }
                              }
                              if (p->is_k<keywords::retn>() && p->flags.fpage_keyword) {
                                    for (const auto &m : p->smembers) {
                                          if (m->is_integral()) {
                                                expr_pages_refed[i].emplace_back(m->extract_integral_base());
                                          }
                                    }
                                    if (const auto &pid = parent_ids[i]; pid) {
                                          if (const auto it = parent_page_linked_returns.find(*pid); it != parent_page_linked_returns.end()) {
                                                auto &ref = expr_pages_refed[i];
                                                ref.insert(ref.end(), it->second.begin(), it->second.end());
                                          }
                                    }
                              }
                        }
                        scope_id -= p->is_scope_end();
                        result.highlevel_scope_ids.emplace_back(scope_id - (p->c == condition_kind::else_ || p->c == condition_kind::elseif_));
                        scope_id += p->is_scope_start_highlevel();
                  }
            }

            /* Reserve */
            {
                  const auto size = (end_labels.size() * 2u) + labels.size();
                  blocks.reserve(size);
            }

            /* Map out entries */
            {
                  bool forced = false;
                  blocks.try_emplace(entry, std::make_shared<generation::cfg::block>());
                  for (auto i = entry; i < ir.data.size(); ++i) {

                        const auto &p = ir.data[i];
                        if (p->is_scope_start() || p->is_implicit_flow_interrupt()) {
                              blocks.try_emplace(i + 1u, std::make_shared<generation::cfg::block>());
                              blocks.try_emplace(p->end_label ? end_labels[p->end_label].ending_loc : p->jlabel ? labels[p->jlabel]
                                                                                                                : p->underlying_jump,
                                  std::make_shared<generation::cfg::block>());
                        }
                        switch (p->k) {
                              case keywords::for_loop_init: {
                                    blocks.try_emplace(i + 1u, std::make_shared<generation::cfg::block>());
                                    break;
                              }
                              case keywords::while_:
                              case keywords::repeat: {
                                    blocks.try_emplace(i, std::make_shared<generation::cfg::block>());
                                    break;
                              }
                              case keywords::end:
                              case keywords::until: {
                                    blocks.try_emplace(i + 1u, std::make_shared<generation::cfg::block>());
                                    break;
                              }
                              case keywords::page_function_end: {
                                    blocks.try_emplace(i, std::make_shared<generation::cfg::block>()).first->second->fforced_end = forced;
                                    blocks.try_emplace(i + 1u, std::make_shared<generation::cfg::block>());
                                    break;
                              }
                              case keywords::page_function_goto: {
                                    if (p->pfk == page_function_goto_kind::call) {
                                          blocks.try_emplace(i + 1u, std::make_shared<generation::cfg::block>());
                                    }
                                    break;
                              }
                              case keywords::page_function_start: {
                                    blocks.try_emplace(i, std::make_shared<generation::cfg::block>());
                                    blocks.try_emplace(i + 1u, std::make_shared<generation::cfg::block>());
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        if (!p->is_k<keywords::page_function_end>() && !p->is_psuedo()) {
                              forced = p->is_terminal();
                        }
                        if (p->label) {
                              blocks.try_emplace(labels[p->label], std::make_shared<generation::cfg::block>());
                        }
                        if (finclude_pages) {
                              for (const auto &v : expr_pages_refed[i]) {
                                    if (const auto it = pages.find(v); it != pages.end()) {
                                          pages_n_edges_blocks[i].emplace_back(std::make_shared<generation::cfg::block>());
                                    }
                              }
                              if (!p->is_terminal()) {
                                    blocks.try_emplace(i + 1u, std::make_shared<generation::cfg::block>());
                                    paged_extra_blocks.try_emplace(i, std::make_shared<generation::cfg::block>());
                              }
                        }
                  }
            }

            /* Go through blocks init and connect them */
            {
                  for (const auto &[entry, block] : blocks) {

                        if (block) {

                              block->entry = entry;
                              block->node_range.second = entry;
                              block->node_range.first = entry;
                              for (auto i = entry; i < ir.data.size(); ++i) {

                                    const auto &p = ir.data[i];
                                    const auto has_pages_edges = finclude_pages && pages_n_edges_blocks.contains(i);
                                    auto exit = has_pages_edges;
                                    bool premature_exit = false;
                                    if (p->is_terminal() || block->fforced_end) {
                                          exit = true;
                                    } else {
                                          if (i == entry && p->k == keywords::page_function_end) {
                                                exit = true;
                                                ++i;
                                          } else {
                                                if (i != entry || p->is_scope_start() || p->is_paging() || p->is_k<keywords::until>() || p->is_k<keywords::end>()) {
                                                      switch (p->k) {
                                                            case keywords::end: {

                                                                  exit = true;
                                                                  if (i != entry) {
                                                                        premature_exit = true;
                                                                        if (const auto it = blocks.find(i); it != blocks.end()) {
                                                                              block->fall = it->second;
                                                                        }
                                                                  } else if (const auto cond = end_labels[p->end_label].cond_loc; ir.data[cond]->is_loop()) {
                                                                        const auto it = blocks.find(cond + (!ir.data[cond]->is_k<keywords::while_>() && !ir.data[cond]->is_k<keywords::repeat>()));
                                                                        if (it != blocks.end()) {
                                                                              block->jump = it->second;
                                                                        }
                                                                  } else {
                                                                        if (const auto it = blocks.find(i + 1u); it != blocks.end()) {
                                                                              block->fall = it->second;
                                                                        }
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::label: {
                                                                  exit = true;
                                                                  if (const auto it = blocks.find(i); it != blocks.end()) {
                                                                        block->fall = it->second;
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::goto_label: {
                                                                  exit = true;
                                                                  if (const auto it = blocks.find(labels[p->jlabel]); it != blocks.end()) {
                                                                        block->jump = it->second;
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::until: {
                                                                  exit = true;
                                                                  if (i == entry) {
                                                                        auto it = blocks.find(end_labels[p->end_label].cond_loc);
                                                                        if (it != blocks.end()) {
                                                                              block->then = it->second;
                                                                        }
                                                                        if (it = blocks.find(i + 1u); it != blocks.end()) {
                                                                              block->jump = it->second;
                                                                        }
                                                                  } else if (const auto it = blocks.find(i); it != blocks.end()) {
                                                                        block->fall = it->second;
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::page_function_start: {
                                                                  exit = true;
                                                                  if (i == entry) {
                                                                        if (const auto &page = pages[p->r->extract_integral_base()]; page.second) {
                                                                              if (auto it = blocks.find(*page.second); it != blocks.end()) {
                                                                                    block->jump = it->second;
                                                                                    if (it = blocks.find(i + 1u); it != blocks.end()) {
                                                                                          block->then = it->second;
                                                                                    }
                                                                              } else if (it = blocks.find(i + 1u); it != blocks.end()) {
                                                                                    block->fall = it->second;
                                                                              }
                                                                        } else if (const auto it = blocks.find(i + 1u); it != blocks.end()) {
                                                                              block->fall = it->second;
                                                                        }
                                                                  } else if (const auto it = blocks.find(i); it != blocks.end()) {
                                                                        --i;
                                                                        premature_exit = true;
                                                                        block->fall = it->second;
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::page_function_goto: {
                                                                  exit = true;
                                                                  if (const auto pit = pages.find(p->r->extract_integral_base()); pit != pages.end() && pit->second.first) {
                                                                        if (const auto it = blocks.find(*pit->second.first); it != blocks.end()) {
                                                                              block->jump = it->second;
                                                                        }
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::page_function_end: {
                                                                  exit = true;
                                                                  auto curr = i;
                                                                  while (curr < ir.data.size() && ir.data[curr]->is_k<keywords::page_function_end>()) {
                                                                        ++curr;
                                                                  }
                                                                  --i;
                                                                  if (const auto it = blocks.find(curr); it != blocks.end()) {
                                                                        block->fall = it->second;
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::condition: {
                                                                  exit = true;
                                                                  if (p->c == condition_kind::else_) {
                                                                        if (const auto it = blocks.find(end_labels[p->elif_end_label].ending_loc); it != blocks.end()) {
                                                                              block->jump = it->second;
                                                                        }
                                                                  } else {
                                                                        auto it = blocks.find(i + 1u);
                                                                        if (it != blocks.end()) {
                                                                              block->then = it->second;
                                                                        }
                                                                        const auto &ending = end_labels[p->end_label];
                                                                        if (it = blocks.find(ending.else_loc ? ending.else_loc + 1u : ending.ending_loc); it != blocks.end()) {
                                                                              block->jump = it->second;
                                                                        }
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::condition_goto: {
                                                                  exit = true;
                                                                  auto it = blocks.find(i + 1u);
                                                                  if (it != blocks.end()) {
                                                                        block->then = it->second;
                                                                  }
                                                                  if (it = blocks.find(labels[p->jlabel]); it != blocks.end()) {
                                                                        block->jump = it->second;
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::repeat: {
                                                                  exit = true;
                                                                  if (i != entry) {
                                                                        premature_exit = true;
                                                                        if (const auto it = blocks.find(i); it != blocks.end()) {
                                                                              block->fall = it->second;
                                                                        }
                                                                  } else {
                                                                        if (const auto it = blocks.find(i + 1u); it != blocks.end()) {
                                                                              block->fall = it->second;
                                                                        }
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::while_: {
                                                                  if (i != entry) {
                                                                        premature_exit = true;
                                                                        if (const auto it = blocks.find(i); it != blocks.end()) {
                                                                              block->fall = it->second;
                                                                        }
                                                                  } else {
                                                                        exit = true;
                                                                        auto it = blocks.find(i + 1u);
                                                                        if (!p->l || p->r || !p->l->is_tk<tkind::boolean>() || !p->l->bv) {
                                                                              if (it != blocks.end()) {
                                                                                    block->then = it->second;
                                                                              }
                                                                              it = blocks.find(end_labels[p->end_label].ending_loc + 1u);
                                                                              if (it != blocks.end()) {
                                                                                    block->jump = it->second;
                                                                              }
                                                                        } else {
                                                                              if (it != blocks.end()) {
                                                                                    block->fall = it->second;
                                                                              }
                                                                        }
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::forloop_generic:
                                                            case keywords::forloop_numeric: {
                                                                  exit = true;
                                                                  if (const auto it = blocks.find(i + 1u); it != blocks.end()) {
                                                                        block->fall = it->second;
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::break_:
                                                            case keywords::continue_: {
                                                                  exit = true;
                                                                  if (const auto it = blocks.find(p->underlying_jump); it != blocks.end()) {
                                                                        block->jump = it->second;
                                                                  }
                                                                  break;
                                                            }
                                                            default: {
                                                                  break;
                                                            }
                                                      }
                                                } else {
                                                      switch (p->k) {
                                                            case keywords::for_loop_init: {
                                                                  exit = true;
                                                                  auto it = blocks.find(i + 1u);
                                                                  if (it != blocks.end()) {
                                                                        block->then = it->second;
                                                                  }
                                                                  if (it = blocks.find(end_labels[ir.data[i - 1u]->end_label].ending_loc); it != blocks.end()) {
                                                                        block->jump = it->second;
                                                                  }
                                                                  break;
                                                            }
                                                            case keywords::break_:
                                                            case keywords::continue_: {
                                                                  exit = true;
                                                                  if (const auto it = blocks.find(p->underlying_jump); it != blocks.end()) {
                                                                        block->jump = it->second;
                                                                  }
                                                                  break;
                                                            }
                                                            default: {
                                                                  break;
                                                            }
                                                      }
                                                }
                                          }
                                    }

                                    block->ending = i;
                                    if (premature_exit) {
                                          block->node_range.second += block->node_range.second == entry;
                                          break;
                                    }
                                    if (exit) {

                                          block->node_range.second += !p->is_scope_end() || block->fforced_end || p->is_k<keywords::until>();
                                          if (has_pages_edges) {

                                                luramas_flag extra_step = true;
                                                std::shared_ptr<generation::cfg::block> prev = nullptr;
                                                std::shared_ptr<generation::cfg::block> first = nullptr;
                                                const auto &data = pages_n_edges_blocks[i];
                                                for (auto idx = 0u; idx < data.size(); ++idx) {
                                                      const auto &p = data[idx];
                                                      p->emit(i, i, i, i + extra_step);
                                                      if (!first) {
                                                            first = p;
                                                      }
                                                      extra_step = false;
                                                      if (finclude_pages) {
                                                            if (const auto it = pages.find(expr_pages_refed[i][idx]); it != pages.end() && it->second.first) {
                                                                  p->jump = blocks[*it->second.first];
                                                            }
                                                      }
                                                      if (prev) {
                                                            if (!prev->jump) {
                                                                  prev->fall = p;
                                                            } else {
                                                                  prev->then = p;
                                                            }
                                                      }
                                                      prev = p;
                                                }
                                                block->node_range.second = i;
                                                if (prev) {
                                                      if (block->fall || block->jump || block->then) {
                                                            const auto b = paged_extra_blocks[i];
                                                            prev->fall = b;
                                                            b->emit(block->jump, block->then, block->fall);
                                                            b->emit(i, i, i, i + extra_step);
                                                            extra_step = false;
                                                      } else if (!p->is_terminal()) {
                                                            if (const auto it = blocks.find(i + 1u); it != blocks.end()) {
                                                                  prev->fall = it->second;
                                                            }
                                                      }
                                                }
                                                block->emit(nullptr, nullptr, first);
                                          }
                                          block->node_range.second += block->node_range.second == entry;
                                          break;
                                    }
                                    ++block->node_range.second;
                                    if (p->is_terminal()) {
                                          break;
                                    }
                              }
                        }
                  }
            }

            /* Traverse CFG and add predecessors */
            {
                  result.entry = blocks[entry];
                  result.blocks.reserve(blocks.size());
                  std::vector<std::shared_ptr<block>> block_stack;
                  block_stack.reserve(blocks.size());
                  block_stack.emplace_back(result.entry);
                  result.interacted_nodes.reserve(ir.data.size());
                  while (!block_stack.empty()) {

                        auto b = block_stack.back();
                        block_stack.pop_back();
                        if (!b || b->fanalyzed) {
                              continue;
                        }
                        if (b == b->jump) {
                              b->jumpk = edge_kind::back;
                        }
                        if (b->jump) {
                              result.predecessors[b->jump].insert(b);
                              if (b->entry > b->jump->entry) {
                                    b->jumpk = edge_kind::back;
                              }
                              block_stack.emplace_back(b->jump);
                        }
                        if (b->then) {
                              result.predecessors[b->then].insert(b);
                              if (b->entry > b->then->entry) {
                                    b->thenk = edge_kind::back;
                              }
                              block_stack.emplace_back(b->then);
                        }
                        if (b->fall) {
                              result.predecessors[b->fall].insert(b);
                              if (b->entry > b->fall->entry) {
                                    b->fallk = edge_kind::back;
                              }
                              block_stack.emplace_back(b->fall);
                        }
                        for (auto i = b->get_front(); i < b->get_end(); ++i) {
                              result.interacted_nodes.insert(i);
                        }
                        b->fanalyzed = true;
                        result.blocks.emplace_back(b);
                  }
            }

            //for (const auto &o : result.blocks) {
            //      LURAMAS_PRINTF("\nBLOCK: %p %zu %zu\n", (void *)o.get(), o->get_front(), o->get_end());
            //      for (auto s = o->get_front(); s < o->get_end(); ++s) {
            //            LURAMAS_PRINTF("  %s (%lld)\n", ir.data[s]->str().c_str(), ir.data[s]->underlying_jump);
            //      }
            //      if (o->fall) {
            //            LURAMAS_PRINTF("FALL %p%s\n", (void *)o->fall.get(), o->fallk == edge_kind::back ? " BACK " : "");
            //      }
            //      if (o->jump) {
            //            LURAMAS_PRINTF("JUMP %p%s\n", (void *)o->jump.get(), o->jumpk == edge_kind::back ? " BACK " : "");
            //      }
            //      if (o->then) {
            //            LURAMAS_PRINTF("THEN %p%s\n", (void *)o->then.get(), o->thenk == edge_kind::back ? " BACK " : "");
            //      }
            //      LURAMAS_PRINTF("-----------------------------------------------------\n");
            //}
            // std::cin.get();
            // for (auto idx = 0u; idx < ir.data.size(); ++idx) {
            //       LURAMAS_PRINTF("%s%s\n", (!result.interacted_nodes.contains(idx) ? "[E] " : ""), ir.data[idx]->str().c_str());
            // }
            //for (const auto &[block, blocks] : result.predecessors) {
            //      LURAMAS_PRINTF("\nPRED BLOCK: %p\n", static_cast<void*>(block.get()));
            //      for (const auto &b : blocks) {
            //            LURAMAS_PRINTF("    %p\n", static_cast<void*>(b.get()));
            //      }
            //}

            //  system("cls");
            //for (const auto &o : result.blocks) {
            //     std::cout << "\nBLOCK: " << o << " " << o->get_front() << "  " << o->get_end() << std::endl;
            //      for (auto s = o->get_front(); s < o->get_end(); ++s) {
            //           std::cout << "  " << ir.data[s]->str() << " (" << ir.data[s]->underlying_jump << ") " << std::endl;
            //      }
            //      if (o->fall) {
            //            std::cout << "FALL " << o->fall << " " << (o->fallk == edge_kind::back ? " BACK " : " ") << std::endl;
            //      }
            //      if (o->jump) {
            //            std::cout << "JUMP " << o->jump << " " << (o->jumpk == edge_kind::back ? " BACK " : " ") << std::endl;
            //      }
            //      if (o->then) {
            //            std::cout << "THEN " << o->then << " " << (o->thenk == edge_kind::back ? " BACK " : " ") << std::endl;
            //      }
            //      std::cout << "-----------------------------------------------------" << std::endl;
            //}
            //
            //for (const auto &[block, blocks] : result.predecessors) {
            //      std::cout << "\nPRED BLOCK: " << block << std::endl;
            //      for (const auto &b : blocks) {
            //            std::cout << "    " << b << std::endl;
            //      }
            //}
            //std::cin.get();

            //std::string output("");
            //for (const auto &o : result.blocks) {
            //      output += "\nBLOCK: " + std::format("{} {} {}\n", (void *)o.get(), o->get_front(), o->get_end());
            //
            //      for (auto s = o->get_front(); s < o->get_end(); ++s) {
            //            output += std::format("  {} ({})\n", ir.data[s]->str(), ir.data[s]->underlying_jump);
            //      }
            //
            //      if (o->fall != nullptr) {
            //            output += std::format("FALL {}{}\n", (void *)o->fall.get(), o->fallk == edge_kind::back ? " BACK " : "");
            //      }
            //      if (o->jump != nullptr) {
            //            output += std::format("JUMP {}{}\n", (void *)o->jump.get(), o->jumpk == edge_kind::back ? " BACK " : "");
            //      }
            //      if (o->then != nullptr) {
            //            output += std::format("THEN {}{}\n", (void *)o->then.get(), o->thenk == edge_kind::back ? " BACK " : "");
            //      }
            //
            //      output += "-----------------------------------------------------\n";
            //}
            //printf("DUMPED CFG\n");
            //output += "\n";
            //for (std::size_t idx = 0; idx < ir.data.size(); ++idx) {
            //      output += (!result.interacted_nodes.contains(idx) ? "[E] " : "");
            //      output += ir.data[idx]->str() + "\n";
            //}
            //luramas::debug::copy_to_clipboard(output);
            return result;
      }

      std::shared_ptr<block> cfg::visit(const luramas_address n) const {
            for (const auto &b : this->blocks) {
                  if (n >= b->get_front() && n < b->get_end()) {
                        return b;
                  }
            }
            return nullptr;
      }
      std::size_t cfg::contiguous_firstlast_scopeid(const std::size_t n) const {

            const auto start_iter = std::ranges::find(this->highlevel_scope_ids, n);
            if (start_iter == this->highlevel_scope_ids.end()) {
                  return 0u;
            }

            const auto end_iter = std::ranges::find_if(start_iter, this->highlevel_scope_ids.end(), [n](const auto id) { return id != n; });
            return end_iter != this->highlevel_scope_ids.end() ? std::distance(this->highlevel_scope_ids.begin(), end_iter) - 1u : 0u;
      }
      std::shared_ptr<block> cfg::most_scope_id(const std::vector<std::shared_ptr<block>> &v) const {

            std::pair<std::size_t, std::shared_ptr<block>> result = {0u, nullptr};
            for (const auto &i : v) {
                  if (const auto id = this->highlevel_scope_ids[i->get_end()]; id > result.first || !result.second) {
                        result = std::make_pair(id, i);
                  }
            }
            return result.second;
      }
      boost::unordered_flat_map<std::shared_ptr<block>, luramas_index> cfg::map() const {

            boost::unordered_flat_map<std::shared_ptr<block>, luramas_index> result;
            for (auto i = 0u; i < this->blocks.size(); ++i) {
                  result[this->blocks[i]] = i;
            }
            return result;
      }
} // namespace generation::cfg