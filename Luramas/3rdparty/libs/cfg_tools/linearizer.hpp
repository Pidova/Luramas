#pragma once
#include "types.hpp"
#include <boost/graph/exception.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/unordered/unordered_flat_set.hpp>

namespace cfg_tools {

      namespace detail {

            /* Recursive helper function for Depth-First Search Post-Order traversal */
            template <typename Graph>
            inline void dfs_post_order(const basic_block<Graph> &vs, const Graph &g, boost::unordered_flat_set<basic_block<Graph>> &visited, boost::container::vector<basic_block<Graph>> &order) {

                  boost::container::vector<std::pair<basic_block<Graph>, bool>> stack;
                  stack.emplace_back(std::make_pair(vs, false));

                  while (!stack.empty()) {

                        auto &[v, neighbors_visited] = stack.back();
                        if (!neighbors_visited) {

                              if (visited.contains(v)) {
                                    stack.pop_back();
                                    continue;
                              }

                              neighbors_visited = true;
                              visited.insert(v);

                              const auto [edge_it, edge_end] = boost::out_edges(v, g);
                              boost::container::vector<basic_edge<Graph>> edges(edge_it, edge_end);
                              for (auto it = edges.rbegin(); it != edges.rend(); ++it) {

                                    const auto target = boost::target(*it, g);
                                    if (visited.contains(target)) {
                                          continue;
                                    }
                                    stack.emplace_back(std::make_pair(target, false));
                              }
                        } else {
                              stack.pop_back();
                              order.emplace_back(v);
                        }
                  }
                  return;
            }
      } // namespace detail

      /* Linearizes input graph (CFG) to a linearized string output */
      template <typename Graph>
      inline boost::container::vector<basic_block<Graph>> linearize(const Graph &g) {

            /* Make sure input is graph */
            static_assert(check::is_adjacency_list_v<Graph>, "Error: only accepts a boost::adjacency_list");

            /* Sort */
            boost::container::vector<basic_block<Graph>> order;
            try {
                  boost::topological_sort(g, std::back_inserter(order));
                  std::reverse(order.begin(), order.end());
            } catch (const boost::not_a_dag &) {

                  order.clear();
                  boost::unordered_flat_set<basic_block<Graph>> visited;

                  const auto vertex_range = boost::vertices(g);
                  for (auto it = vertex_range.first; it != vertex_range.second; ++it) {
                        if (visited.contains(*it)) {
                              continue;
                        }
                        detail::dfs_post_order(*it, g, visited, order);
                  }
                  std::reverse(order.begin(), order.end());
            }
            return order;
      }
} // namespace cfg_tools
