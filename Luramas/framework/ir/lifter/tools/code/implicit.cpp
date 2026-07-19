#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::implicit {

      luramas_addresses continous_break(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address target) {

            luramas_addresses result;
            if (!pm.contains(start) || !pm.contains(target)) {
                  return result;
            }

            auto curr = start;
            while (curr < target) {

                  curr = tools::trackers::next_safe_executable(pm, curr);

                  const auto [loop_start, loop_end] = tools::trackers::parent_loop(pm, curr);
                  if (!loop_end) {
                        break;
                  }
                  curr = loop_end + 1u;
            }
            result.clear();
            return result;
      }
} // namespace luramas::ir::tools::implicit