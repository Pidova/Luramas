#include "../ariths.hpp"
#include "../../../lifter/tools/tools.hpp"

namespace luramas::ir::tables::data::arith {

      std::shared_ptr<ir_stat::ir_expr> replace(const std::shared_ptr<ir_stat::ir_expr> &target, const expr_parse_map &member) {

            return tools::replace::match_wild_cards(target, member.key, member.val);
      }
} // namespace luramas::ir::tables::data::arith