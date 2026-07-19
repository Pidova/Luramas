#include "../../lifter/passes/includes/common.hpp"
#include "../common.hpp"

namespace luramas::ir::analysis::tags {

      namespace hierarchy {

            boost::unordered_flat_map<std::string, ir_stat::space> same_tags_location_same_keys_different_values(const std::vector<ir_stat::space> &spaces, const std::uint16_t location_threshold) {

                  boost::unordered_flat_map<std::string, ir_stat::space> result;

                  struct tag_data {
                        luramas_index vect_index = 0u;
                        luramas_address addr = 0u;
                        luramas_count depth = 0u;
                  };
                  // boost::unordered_flat_map<std::string, tag_data> grouped;

                  return result;
            }
      } // namespace hierarchy

} // namespace luramas::ir::analysis::tags