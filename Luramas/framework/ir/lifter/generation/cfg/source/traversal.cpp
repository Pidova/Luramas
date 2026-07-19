#include "../traversal.hpp"
#include <queue>
#include <stack>

namespace luramas::ir::cfg::traverse {

      namespace visit {

            std::shared_ptr<generation::cfg::block> visit(const std::shared_ptr<generation::cfg::block> &entry, const luramas_address target) {

                  std::deque<std::shared_ptr<generation::cfg::block>> to_visit = {entry};
                  boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> processed;
                  while (!to_visit.empty()) {

                        const auto block = to_visit.back();
                        to_visit.pop_back();
                        if (!block || processed.find(block) != processed.end()) {
                              continue;
                        }
                        processed.insert(block);

                        if (target >= block->get_front() && target <= block->get_end()) {
                              return block;
                        }
                        if (block->jump) {
                              to_visit.emplace_back(block->jump);
                        }
                        if (block->fall) {
                              to_visit.emplace_back(block->fall);
                        }
                        if (block->then) {
                              to_visit.emplace_back(block->then);
                        }
                  }
                  return nullptr;
            }
            std::shared_ptr<generation::cfg::block> visit_fall(const std::shared_ptr<generation::cfg::block> &entry, const std::shared_ptr<generation::cfg::block> &target) {

                  auto prev = entry;
                  auto current = entry;
                  while (current->fall != target) {

                        prev = current;
                        if (current->then && current->thenk == generation::cfg::edge_kind::jump) {
                              current = current->then;
                        } else if (current->fall && current->fallk == generation::cfg::edge_kind::jump) {
                              current = current->fall;
                        } else if (current->jump && current->jumpk == generation::cfg::edge_kind::jump) {
                              current = current->jump;
                        }
                        if (prev == current) {
                              return nullptr;
                        }
                  }
                  return current;
            }
      } // namespace visit

      namespace extract {

            std::shared_ptr<generation::cfg::block> jump_block(const std::shared_ptr<generation::cfg::block> &start, const std::size_t node_limit) {

                  auto prev = start;
                  auto current = start;
                  while (current && current->get_end() <= node_limit) {

                        prev = current;
                        if (current->then && current->thenk == generation::cfg::edge_kind::jump) {
                              current = current->then;
                        } else if (current->fall && current->fallk == generation::cfg::edge_kind::jump) {
                              current = current->fall;
                        } else if (current->jump && current->jumpk == generation::cfg::edge_kind::jump) {
                              current = current->jump;
                        }
                        if (prev == current) {
                              break;
                        }
                  }
                  return current;
            }

            std::shared_ptr<generation::cfg::block> scope_switch(const std::shared_ptr<generation::cfg::block> &curr, const std::shared_ptr<generation::cfg::block> &target, const generation::cfg::cfg &cfg) {

                  if (!target || !curr) {
                        return nullptr;
                  }

                  const auto target_it = std::find(cfg.blocks.begin(), cfg.blocks.end(), target);
                  const auto input_it = std::find(cfg.blocks.begin(), cfg.blocks.end(), curr);

                  if (target_it == cfg.blocks.end() || input_it == cfg.blocks.end()) {
                        return nullptr;
                  }

                  const auto target_index = static_cast<std::size_t>(std::distance(cfg.blocks.begin(), target_it));
                  const auto input_index = static_cast<std::size_t>(std::distance(cfg.blocks.begin(), input_it));

                  const auto target_scope = cfg.highlevel_scope_ids[target_index];
                  const auto forward = target_index < input_index;

                  auto result = target_index;
                  for (auto i = target_index; forward ? (i <= input_index) : (i >= input_index); i += forward ? 1 : -1) {

                        if (cfg.highlevel_scope_ids[i] != target_scope) {
                              result = i;
                              break;
                        }
                        result = i;
                  }
                  return (result < cfg.blocks.size()) ? cfg.blocks[result] : nullptr;
            }
      } // namespace extract
      namespace pathing {

            struct path_entry {

                  std::shared_ptr<generation::cfg::block> current = nullptr;
                  std::size_t cost = 0u;

                  bool operator>(const path_entry &other) const {
                        return cost > other.cost;
                  }
            };

            std::vector<std::shared_ptr<generation::cfg::block>> path(const std::shared_ptr<generation::cfg::block> &start, const std::shared_ptr<generation::cfg::block> &target) {

                  std::vector<std::shared_ptr<generation::cfg::block>> path;
                  if (!start || !target) {
                        return path;
                  }

                  std::priority_queue<path_entry, std::vector<path_entry>, std::greater<>> pq;
                  boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::size_t> dist;
                  boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>> prev;

                  dist[start] = 0u;
                  pq.push({start, 0u});

                  while (!pq.empty()) {

                        auto [current, current_cost] = pq.top();
                        pq.pop();

                        if (current == target) {
                              break;
                        }

                        const auto process_edge = [&](const auto &next) {
                              if (!next) {
                                    return;
                              }
                              if (const auto new_cost = current_cost + 1u; dist.find(next) == dist.end() || new_cost < dist[next]) {
                                    dist[next] = new_cost;
                                    prev[next] = current;
                                    pq.push({next, new_cost});
                              }
                              return;
                        };

                        process_edge(current->jump);
                        process_edge(current->then);
                        process_edge(current->fall);
                  }

                  std::stack<std::shared_ptr<generation::cfg::block>> s;
                  for (auto i = target; i; i = prev[i]) {

                        s.push(i);
                        if (i == start) {
                              break;
                        }
                  }
                  while (!s.empty()) {
                        path.push_back(s.top());
                        s.pop();
                  }
                  return path;
            }

            std::vector<std::pair<bool, std::shared_ptr<generation::cfg::block>>> path_with_loop(const std::shared_ptr<generation::cfg::block> &curr, const std::shared_ptr<generation::cfg::block> &target, const generation::cfg::cfg &cfg) {

                  std::vector<std::pair<bool, std::shared_ptr<generation::cfg::block>>> result;

                  if (const auto natural_path = path(curr, target); !natural_path.empty() && natural_path.back() == target) {
                        for (const auto &i : natural_path) {
                              result.emplace_back(false, i);
                        }
                  } else {

                        result.emplace_back(false, curr);
                        if (const auto simulated = extract::scope_switch(curr, target, cfg); simulated) {
                              result.emplace_back(true, simulated);
                              result.emplace_back(false, target);
                        } else {
                              result.emplace_back(true, target);
                        }
                  }
                  return result;
            }

            std::vector<std::pair<keywords, std::shared_ptr<generation::cfg::block>>> optimize(se_ir &ir, const std::vector<std::shared_ptr<generation::cfg::block>> &path, const generation::cfg::cfg &cfg) {

                  boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> loop_ends;
                  std::vector<std::pair<keywords, std::shared_ptr<generation::cfg::block>>> result;

                  const auto pmap = luramas::tools::val_idx(path);
                  for (auto i = 0ull; i < path.size(); ++i) {

                        auto curr = path[i];
                        if (const auto next = (i + 1u < path.size()) ? path[i + 1u] : nullptr; next && curr->dominant_successor_edge(next) == generation::cfg::edge_kind::back && !ir.data[curr->get_end() - 1u]->is_goto_label()) {

                              /* Remove */
                              {
                                    auto cut = result.end();
                                    while (cut != result.begin()) {
                                          --cut;
                                          if (loop_ends.contains(cut->second)) {
                                                ++cut;
                                                break;
                                          }
                                    }
                                    result.erase(cut, result.end());
                              }

                              /* Add */
                              {
                                    const auto end = cfg.visit(curr->get_end() + 1u);

                                    /* Should not really happen just incase */
                                    if (!end) {
                                          result.clear();
                                          return result;
                                    }

                                    loop_ends.insert(end);
                                    if (const auto it = pmap.find(end); it != pmap.end() && it->second != i) {

                                          /* Error probably looping */
                                          if (it->second < i) {
                                                result.clear();
                                                return result;
                                          }
                                          i = it->second;
                                          result.emplace_back(keywords::break_, result.empty() ? path.front() : result.back().second);
                                          curr = path[i];
                                    } else {
                                          result.emplace_back(keywords::continue_, curr);
                                          continue;
                                    }
                              }
                        }
                        result.emplace_back(keywords::nothing, curr);
                  }
                  return result;
            }
      } // namespace pathing

} // namespace luramas::ir::cfg::traverse