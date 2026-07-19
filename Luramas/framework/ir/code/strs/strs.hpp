#pragma once
#include "../../ir.hpp"
#include <luramas/formatting/formatting.hpp>

namespace luramas::ir::code::generation::str {

      namespace prefixes {

            /* Flag prefix for vars */
            std::string flag(const std::shared_ptr<ir::data::format::format> &format, const std::shared_ptr<ir_stat::ir_expr> &reg);

            /* Normal var prefix for vars*/
            std::string var(const std::shared_ptr<ir::data::format::format> &format, const std::shared_ptr<ir_stat::ir_expr> &reg);
      } // namespace prefixes

      namespace suffix {

      } // namespace suffix
} // namespace luramas::ir::code::generation::str