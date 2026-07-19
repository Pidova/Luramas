#include "../compute.hpp"
#include "../helpers.hpp"
#include <boost/graph/dominator_tree.hpp>
#include <boost/property_map/property_map.hpp>

namespace luramas::ir::cfg::compute {

      boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>> immediate_dominators(const helpers::boost_graph &graph) {

            boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>> result;
            const auto entry_it = graph.vertex_descriptor.find(graph.entry);
            if (entry_it == graph.vertex_descriptor.end()) {
                  return result;
            }

            boost::unordered_flat_map<helpers::boost_graph::n_t, helpers::boost_graph::n_t> dom_tree;
            boost::lengauer_tarjan_dominator_tree(graph.graph, entry_it->second, boost::make_assoc_property_map(dom_tree));

            boost::unordered_flat_map<helpers::boost_graph::n_t, std::shared_ptr<generation::cfg::block>> desc_to_block;
            for (const auto &p : graph.vertex_descriptor) {
                  desc_to_block[p.second] = p.first;
            }

            for (const auto &[b, v] : graph.vertex_descriptor) {
                  const auto it = dom_tree.find(v);
                  result[b] = (it == dom_tree.end() || it->second == v) ? nullptr : desc_to_block.at(it->second);
            }
            return result;
      }
      boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>> immediate_dominators(const generation::cfg::cfg &cfg) {

            return immediate_dominators(helpers::generate_boost_graph(cfg));
      }

      boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>>> dominance_frontier(const generation::cfg::cfg &cfg, const boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>> &idoms) {

            boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>>> result;

            /* Init */
            {
                  for (const auto &b : cfg.blocks) {
                        result[b] = {};
                  }
            }

            /* Compute */
            {
                  for (const auto &b : cfg.blocks) {

                        if (const auto pred_it = cfg.predecessors.find(b); pred_it != cfg.predecessors.end() && !pred_it->second.empty()) {

                              const auto b_dom_it = idoms.find(b);
                              if (b_dom_it == idoms.end() || !b_dom_it->second)
                                    continue;
                              const auto &b_idom = b_dom_it->second;

                              // For every predecessor 'p' of join point 'b'
                              for (const auto &p : pred_it->second) {
                                    auto runner = p;

                                    // Climb the dominator tree from 'p' up to 'IDom(b)'
                                    // CRITICAL: Compare by ID/Address of the block, not the shared_ptr itself
                                    while (runner && runner != b_idom) {
                                          result[runner].insert(b);

                                          const auto run_dom_it = idoms.find(runner);
                                          if (run_dom_it != idoms.end() && run_dom_it->second) {
                                                // Move to immediate dominator of the runner
                                                auto next_runner = run_dom_it->second;

                                                // Safety break: prevent infinite loop if Entry dominates itself
                                                if (next_runner == runner)
                                                      break;
                                                runner = next_runner;
                                          } else {
                                                break;
                                          }
                                    }
                              }
                        }
                  }
            }

            return result;
      }

      boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::vector<std::shared_ptr<generation::cfg::block>>> dominator_tree(const boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>> &idoms) {

            boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::vector<std::shared_ptr<generation::cfg::block>>> result;
            for (const auto &[b, i] : idoms) {
                  if (b != i && i) {
                        result[i].emplace_back(b);
                  }
            }
            return result;
      }

      boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> find_blocks_between(const generation::cfg::cfg &cfg, const std::shared_ptr<generation::cfg::block> &start, const std::shared_ptr<generation::cfg::block> &end) {

            boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> result(cfg.blocks.size());
            boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> visited(cfg.blocks.size());

            std::vector<std::shared_ptr<generation::cfg::block>> stack(cfg.blocks.size());
            stack.emplace_back(start);
            visited.insert(start);

            while (!stack.empty()) {

                  auto b = stack.back();
                  stack.pop_back();
                  if (!b) {
                        continue;
                  }

                  result.insert(b);
                  if (b == end) {
                        continue;
                  }
                  for (const auto &s : b->get_block_successors()) {
                        if (visited.insert(s).second) {
                              stack.emplace_back(s);
                        }
                  }
            }
            return result;
      }

      std::string graphviz(const se_ir &ir, const generation::cfg::cfg &cfg) {

            return helpers::str(ir, helpers::generate_boost_graph(cfg));
      }
} // namespace luramas::ir::cfg::compute