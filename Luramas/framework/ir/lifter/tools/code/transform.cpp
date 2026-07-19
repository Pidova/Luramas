#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::transform {

      luramas_addresses range_to_addresses(const luramas_blockrange &range) {

            luramas_addresses result;
            if (range.second > range.first) {
                  result.reserve(range.second - range.first);
            }
            for (auto i = range.first; i < range.second; ++i) {
                  result.emplace_back(i);
            }
            return result;
      }

      ir_stat::space range_to_space(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {

            ir_stat::space result;
            if (range.second > range.first) {
                  result.reserve(range.second - range.first);
            }
            for (auto i = range.first; i < range.second; ++i) {
                  result.emplace_back(pm[i]);
            }
            return result;
      }

      luramas_blockrange addresses_to_range(const luramas_addresses &addresses) {

            return std::make_pair(addresses.front(), addresses.back() + 1u);
      }

      luramas_blockrange address_to_range(const luramas_address start, const luramas_address inclusive_end) {

            return std::make_pair(start, inclusive_end + 1u);
      }

      namespace isolate {

            void labels(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {

                  return;
            }
      } // namespace isolate
} // namespace luramas::ir::tools::transform