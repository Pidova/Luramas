#pragma once
#include "../ir.hpp"

namespace luramas::ir::definitions {

      struct exprs {

            luramas_address where = 0u;
            ir_stat::ir_expr::space lvalues;
            luramas_registers lvalues_regs;
            ir_stat::ir_expr::space rvalues;
            luramas_registers rvalues_regs;

            ir_stat::ir_expr::space all;

            bool edits_flag = false;
            std::intptr_t edited_flag = 0u;
            std::vector<std::intptr_t> used_flags;

            using space = std::vector<std::pair<std::shared_ptr<ir_stat>, exprs>>;
      };

      struct global_space {
            exprs::space space;
            std::vector<std::shared_ptr<global_space>> closures;
      };
} // namespace luramas::ir::definitions