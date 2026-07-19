#pragma once
#include "../../generation.hpp"

namespace luramas::ir::cfg::compute {

      /* Compute immediate dominators with lengauer tarjan */
      boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>> immediate_dominators(const generation::cfg::cfg &cfg);

      /* Compute dominance frontiers with immediate dominators */
      boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>>> dominance_frontier(const generation::cfg::cfg &cfg, const boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>> &idoms);

      /* Computer dominator tree with immediate dominators */
      boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::vector<std::shared_ptr<generation::cfg::block>>> dominator_tree(const boost::unordered_flat_map<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>> &idoms);

      /* Gets blocks between [start, end] */
      boost::unordered_flat_set<std::shared_ptr<generation::cfg::block>> find_blocks_between(const generation::cfg::cfg &cfg, const std::shared_ptr<generation::cfg::block> &start, const std::shared_ptr<generation::cfg::block> &end);

      /* Compute graphviz str with cfg */
      std::string graphviz(const se_ir &ir, const generation::cfg::cfg &cfg);
} // namespace luramas::ir::cfg::compute