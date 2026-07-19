#pragma once
#include "../../generation.hpp"

namespace luramas::ir::cfg::sort {

      /* Sort topologically */
      std::vector<std::shared_ptr<generation::cfg::block>> topological(const generation::cfg::cfg &cfg, const bool ignore_back_edges = false);

      /* Sort by dominance nodes */
      std::vector<std::shared_ptr<generation::cfg::block>> dominant(const generation::cfg::cfg &cfg);

      /* Traversal sort */
      std::vector<std::shared_ptr<generation::cfg::block>> traversal(const generation::cfg::cfg &cfg);
} // namespace luramas::ir::cfg::sort