/*
    Used for high-level analysis in IR that contain specific functions.
*/
#pragma once
#include "../lifter/generation.hpp"

namespace luramas::ir::analysis {

      namespace regs {

            /* Maps registers used to there locations */
            boost::unordered_flat_map<luramas_register, luramas_addresses /* Locations */> used(const boost::unordered_flat_map<std::shared_ptr<ir_stat>, luramas::ir::definitions::exprs> &expr_map);

            /* Maps registers edited to there locations */
            boost::unordered_flat_map<luramas_register, luramas_addresses /* Locations */> edited(const boost::unordered_flat_map<std::shared_ptr<ir_stat>, luramas::ir::definitions::exprs> &expr_map);

            struct returning_regs_p {

                  struct usage {
                        luramas_register reg = 0u;
                        bool maybe = false; /* Chance of it not even getting mutated. */
                  };
                  std::vector<usage> used;
                  std::shared_ptr<ir_stat> dependant_on = nullptr;
            };
            /* Details returning regs either from page starts, definitions, global label. */
            boost::unordered_flat_map<std::shared_ptr<ir_stat> /* Start either definition or page start */, returning_regs_p> mutated(const ir_stat::space &space);
      } // namespace regs

      namespace tags {

            namespace hierarchy {

                  /* Identifies tag locations with matching names but differing values but same keys, using a hierarchical structure and a threshold. */
                  boost::unordered_flat_map<std::string, ir_stat::space> same_tags_location_same_keys_different_values(const std::vector<ir_stat::space> &spaces, const std::uint16_t location_threshold = 0u);
            } // namespace hierarchy
      } // namespace tags

} // namespace luramas::ir::analysis