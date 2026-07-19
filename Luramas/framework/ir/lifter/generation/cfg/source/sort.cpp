#include "../sort.hpp"

namespace luramas::ir::cfg::sort {

      std::vector<std::shared_ptr<generation::cfg::block>> topological(const generation::cfg::cfg &cfg, const bool ignore_back_edges) {

            std::vector<std::shared_ptr<generation::cfg::block>> result;
            boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> visited;

            result.reserve(cfg.blocks.size());
            visited.reserve(cfg.blocks.size());

            const std::function<void(const std::shared_ptr<generation::cfg::block> &)> dfs = [&](const std::shared_ptr<generation::cfg::block> &block) {
                  if (!block || visited.contains(block)) {
                        return;
                  }
                  visited.insert(block);

                  if (const auto pred_it = cfg.predecessors.find(block); pred_it != cfg.predecessors.end()) {

                        /* Organize predecessors */
                        std::vector<std::shared_ptr<generation::cfg::block>> predecessors;
                        predecessors.reserve(pred_it->second.size());
                        if (!ignore_back_edges) {
                              for (const auto &pred : pred_it->second) {
                                    if (pred->dominant_successor_edge(block) == generation::cfg::edge_kind::back) {
                                          predecessors.emplace_back(pred);
                                    }
                              }
                              for (const auto &pred : pred_it->second) {
                                    if (pred->dominant_successor_edge(block) != generation::cfg::edge_kind::back) {
                                          predecessors.emplace_back(pred);
                                    }
                              }
                        } else {
                              std::copy_if(pred_it->second.begin(), pred_it->second.end(), std::back_inserter(predecessors), [&](const auto &pred) { return pred->dominant_successor_edge(block) != generation::cfg::edge_kind::back; });
                        }
                        for (const auto &pred : predecessors) {
                              if (!visited.contains(pred)) {
                                    dfs(pred);
                              }
                        }
                  }

                  result.emplace_back(block);
                  if (block->fall && !visited.contains(block->fall)) {
                        visited.insert(block->fall);
                        result.emplace_back(block->fall);
                  }
                  return;
            };

            if (cfg.entry) {
                  dfs(cfg.entry);
            }
            for (const auto &block : cfg.blocks) {
                  if (!visited.contains(block)) {
                        dfs(block);
                  }
            }
            return result;
      }

      std::vector<std::shared_ptr<generation::cfg::block>> dominant(const generation::cfg::cfg &cfg) {

            std::vector<std::shared_ptr<generation::cfg::block>> result;
            boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> visited, pending;
            result.reserve(cfg.blocks.size());
            visited.reserve(cfg.blocks.size());
            pending.reserve(cfg.blocks.size());

            std::vector<std::pair<std::shared_ptr<generation::cfg::block>, bool>> stack;
            stack.emplace_back(cfg.entry, true);

            while (!stack.empty()) {

                  auto [blk, ignore] = stack.back();
                  stack.pop_back();
                  if (!blk || visited.contains(blk) || (!ignore && pending.contains(blk))) {
                        continue;
                  }

                  visited.insert(blk);
                  result.push_back(blk);

                  if (blk->jump && blk->jumpk != generation::cfg::edge_kind::back) {
                        stack.emplace_back(blk->jump, pending.insert(blk->jump).second);
                  }
                  if (blk->fall && blk->fallk != generation::cfg::edge_kind::back) {
                        stack.emplace_back(blk->fall, pending.insert(blk->fall).second);
                  }
                  if (blk->then && blk->thenk != generation::cfg::edge_kind::back) {
                        stack.emplace_back(blk->then, pending.insert(blk->then).second);
                  }
            }
            return result;
      }

      std::vector<std::shared_ptr<generation::cfg::block>> traversal(const generation::cfg::cfg &cfg) {

            std::vector<std::shared_ptr<generation::cfg::block>> result;
            boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> visited, pending;
            result.reserve(cfg.blocks.size());
            visited.reserve(cfg.blocks.size());
            pending.reserve(cfg.blocks.size());

            std::vector<std::pair<std::shared_ptr<generation::cfg::block>, bool>> stack;
            stack.emplace_back(cfg.entry, true);

            while (!stack.empty()) {

                  auto [blk, ignore] = stack.back();
                  stack.pop_back();
                  if (!blk || visited.contains(blk) || (!ignore && pending.contains(blk))) {
                        continue;
                  }

                  visited.insert(blk);
                  result.push_back(blk);

                  if (blk->jump) {
                        stack.emplace_back(blk->jump, pending.insert(blk->jump).second);
                  }
                  if (blk->fall) {
                        stack.emplace_back(blk->fall, pending.insert(blk->fall).second);
                  }
                  if (blk->then) {
                        stack.emplace_back(blk->then, pending.insert(blk->then).second);
                  }
            }
            return result;
      }
} // namespace luramas::ir::cfg::sort