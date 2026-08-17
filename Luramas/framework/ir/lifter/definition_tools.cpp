#include "../ir.hpp"

namespace luramas::ir::tools {

      namespace exprs {

            std::size_t count(const ir_stat::ir_expr::space &exprs, const luramas_register reg) {
                  std::size_t result = 0U;
                  for (const auto &i : exprs) {
                        result += static_cast<std::size_t>(i->is_register_reference() && i->reg == reg);
                  }
                  return result;
            }
      } // namespace exprs

} // namespace luramas::ir::tools