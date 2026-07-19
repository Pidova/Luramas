#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::errors {

      void in_range(const luramas_index idx, const luramas_count n) {
            if (idx >= n) {
                  error::error("Index " + std::to_string(idx) + " is not in range of " + std::to_string(n));
            }
            return;
      }
} // namespace luramas::ir::tools::errors