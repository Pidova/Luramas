#include "../tools.hpp"

namespace luramas::ir::tools::loops {

      bool infitely(luramas::ir::passes::pass_manager &pm, luramas_address start) {

            if (stat::is_end(pm[start])) {
                  start = common::reverse_safe_take_jump(pm, start);
            }
            return stat::branch::is_while_true(pm[start]);
      }

} // namespace luramas::ir::tools::loops