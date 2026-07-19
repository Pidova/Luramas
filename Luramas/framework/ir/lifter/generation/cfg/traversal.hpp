#pragma once
#include "../../generation.hpp"

namespace luramas::ir::cfg::traverse {

      namespace visit {

            /* Visit block that contains target */
            std::shared_ptr<generation::cfg::block> visit(const std::shared_ptr<generation::cfg::block> &entry, const luramas_address target);

            /* Visit block that is jumped to */
            std::shared_ptr<generation::cfg::block> visit_fall(const std::shared_ptr<generation::cfg::block> &entry, const std::shared_ptr<generation::cfg::block> &target);
      } // namespace visit

      namespace extract {

            /* Extract block that is jumped to */
            std::shared_ptr<generation::cfg::block> jump_block(const std::shared_ptr<generation::cfg::block> &start, const std::size_t node_limit);

            /* Finds the first block that changes scope between target and curr */
            std::shared_ptr<generation::cfg::block> scope_switch(const std::shared_ptr<generation::cfg::block> &curr, const std::shared_ptr<generation::cfg::block> &target, const generation::cfg::cfg &cfg);
      } // namespace extract

      namespace pathing {

            /* Find optimal path to start -> target */
            std::vector<std::shared_ptr<generation::cfg::block>> path(const std::shared_ptr<generation::cfg::block> &start, const std::shared_ptr<generation::cfg::block> &target);

            /* Find optimal path to start -> target with loop to help thread out */
            std::vector<std::pair<bool, std::shared_ptr<generation::cfg::block>>> path_with_loop(const std::shared_ptr<generation::cfg::block> &curr, const std::shared_ptr<generation::cfg::block> &target, const generation::cfg::cfg &cfg);

            /* Tries to optimize given path with keywords it can thread out with. Will still map to the original just keyword being nothing if it does not find anything. */
            std::vector<std::pair<keywords, std::shared_ptr<generation::cfg::block>>> optimize(se_ir &ir, const std::vector<std::shared_ptr<generation::cfg::block>> &path, const generation::cfg::cfg &cfg);
      } // namespace pathing
} // namespace luramas::ir::cfg::traverse