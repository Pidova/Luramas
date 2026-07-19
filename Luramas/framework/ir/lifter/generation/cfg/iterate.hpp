#pragma once
#include "../../generation.hpp"

namespace luramas::ir::cfg::iterate {

      namespace visit {

            std::shared_ptr<generation::cfg::block> visit(const std::vector<std::shared_ptr<generation::cfg::block>> &blocks, const luramas_address target);
            std::shared_ptr<generation::cfg::block> visit_fall(const std::vector<std::shared_ptr<generation::cfg::block>> &blocks, const std::shared_ptr<generation::cfg::block> &target);
      } // namespace visit

      namespace extract {

            /* Extract by edges {target, curr} */
            std::vector<std::pair<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>>> edge(const std::vector<std::shared_ptr<generation::cfg::block>> &blocks, const generation::cfg::edge_kind target);
      } // namespace extract

      namespace is {

            /* Is target visible to current? */
            bool scope_visible(const luramas_addresses &highlevel_scope_id, const luramas_address current, const luramas_address target, const bool skip_current_scope = false);
      } // namespace is
} // namespace luramas::ir::cfg::iterate