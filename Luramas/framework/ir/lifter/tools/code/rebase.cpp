#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::rebaser {

      void labels(luramas_address base, ir_stat::space &buffer) {

            ++base;
            for (const auto &i : buffer) {
                  if (i->label) {
                        i->label += base;
                  }
                  if (i->jlabel) {
                        i->jlabel += base;
                  }
            }
            return;
      }
} // namespace luramas::ir::tools::rebaser