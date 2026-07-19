#pragma once
#include "ir_defs.hpp"

namespace luramas::ir {

      /* Lift and optimize IR */
      ir_stat::space lift(std::shared_ptr<luramas::closures::closure> &closure, const passes::environment_flags &env_flags = passes::environment_flags());

      /* Just dbg stuff */
      void print_stat(const std::shared_ptr<ir_stat> &stat, std::size_t &indenter, const char *const prefix, const bool indent, const bool mark = false, const bool force = false);
      void dump(const char *const prefix, const ir_stat::space &space, const bool indent, const bool force = false);
      void dump(const ir_stat::space &space);

      namespace tools {

            namespace exprs {
                  std::size_t count(const ir_stat::ir_expr::space &exprs, const luramas_register reg);
            }
      } // namespace tools
} // namespace luramas::ir
