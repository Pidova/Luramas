#pragma once
#include "types.hpp"

namespace cfg_tools {

      namespace detail {

            enum class color : std::uint8_t {
                  white, /* Unvisited */
                  gray,  /* On stack */
                  black  /* Processed */
            };

            /* Traverses backwards from the loop's back-edge source to find all blocks inside the loop. */
            template <typename Graph>
            inline void flood_loop_body(const basic_block<Graph> &currs, const basic_block<Graph> &header, const Graph &g, boost::unordered_flat_set<basic_block<Graph>> &loop_blocks) {

                  boost::container::vector<basic_block<Graph>> stack;
                  stack.emplace_back(currs);

                  while (!stack.empty()) {

                        const auto curr = stack.back();
                        stack.pop_back();

                        if (curr == header || loop_blocks.contains(curr)) {
                              continue;
                        }
                        loop_blocks.insert(curr);

                        auto vertex_range = boost::vertices(g);
                        for (auto it = vertex_range.first; it != vertex_range.second; ++it) {

                              auto [ei, ee] = boost::out_edges(*it, g);
                              for (auto e_it = ei; e_it != ee; ++e_it) {
                                    if (boost::target(*e_it, g) != curr) {
                                          continue;
                                    }
                                    stack.emplace_back(*it);
                              }
                        }
                  }
                  return;
            }

            /* Find exits for a region and add them into the map */
            template <typename Graph>
            inline void extract_and_register_exits(const Graph &g, const basic_block<Graph> &entry, const boost::unordered_flat_set<basic_block<Graph>> &region_blocks, SEME<Graph> &registry) {

                  boost::container::vector<basic_block<Graph>> exits;
                  boost::unordered_flat_set<basic_block<Graph>> recorded_exits;

                  for (const auto &node : region_blocks) {

                        const auto [edge_it, edge_end] = boost::out_edges(node, g);
                        for (auto it = edge_it; it != edge_end; ++it) {

                              if (const auto target = boost::target(*it, g); !region_blocks.contains(target) && target != entry) {
                                    if (recorded_exits.contains(node)) {
                                          continue;
                                    }
                                    recorded_exits.insert(node);
                                    exits.emplace_back(node);
                              }
                        }
                  }

                  /* If this entry already exists, merge exits; create a new entry */
                  auto &existing_exits = registry[entry];
                  for (const auto &ex : exits) {
                        if (std::find(existing_exits.begin(), existing_exits.end(), ex) != existing_exits.end()) {
                              continue;
                        }
                        existing_exits.emplace_back(ex);
                  }
                  return;
            }

      } // namespace detail

      /* Analyzes all blocks in the CFG to find and register every SEME region */
      template <typename Graph>
      inline SEME<Graph> modularize(const Graph &g) {

            /* Check graph */
            static_assert(check::is_adjacency_list_v<Graph>, "Error: only accepts a boost::adjacency_list");

            SEME<Graph> registry;

            /* Propagate colors white */
            boost::unordered_flat_map<basic_block<Graph>, detail::color> colors;
            auto vertices = boost::vertices(g);
            for (auto it = vertices.first; it != vertices.second; ++it) {
                  colors[*it] = detail::color::white;
            }

            /* Iterative DFS stack tracking */
            boost::container::vector<std::pair<basic_block<Graph>, typename boost::graph_traits<Graph>::out_edge_iterator>> stack;

            for (auto root_it = vertices.first; root_it != vertices.second; ++root_it) {

                  if (colors[*root_it] != detail::color::white) {
                        continue;
                  }
                  auto [ei, ee] = boost::out_edges(*root_it, g);
                  colors[*root_it] = detail::color::gray;
                  stack.emplace_back(*root_it, ei);

                  while (!stack.empty()) {

                        auto &[curr, edge_it] = stack.back();
                        if (auto [_, current_ee] = boost::out_edges(curr, g); edge_it != current_ee) {

                              const auto edge = *edge_it;
                              ++edge_it;

                              const auto target = boost::target(edge, g);
                              switch (colors[target]) {
                                    case detail::color::gray: {

                                          boost::unordered_flat_set<basic_block<Graph>> region_blocks;

                                          /* Trace the exact extent of this specific SEME block grouping */
                                          detail::flood_loop_body(curr, target, g, region_blocks);
                                          detail::extract_and_register_exits(g, target, region_blocks, registry);
                                          break;
                                    }
                                    case detail::color::white: {
                                          colors[target] = detail::color::gray;
                                          auto [next_ei, next_ee] = boost::out_edges(target, g);
                                          stack.emplace_back(target, next_ei);
                                          break;
                                    }
                                    default: {
                                          break;
                                    }
                              }
                        } else {
                              colors[curr] = detail::color::black;
                              stack.pop_back();
                        }
                  }
            }
            return registry;
      }
} // namespace cfg_tools
