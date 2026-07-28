#pragma once
#include "../../constants.hpp"
#include "../../ir.hpp"
#include "../generation.hpp"
#include "../passes/setups/setups.hpp"
#include "../tools/extras/exprs.hpp"
#include "../tools/extras/stats.hpp"
#include "../tools/tools.hpp"

namespace luramas::ir::managers {

      namespace upvalues {

            struct manager {
                  boost::unordered_flat_map<std::size_t, std::shared_ptr<ir_stat::ir_expr>> upvalues;         /* Upvalues by index */
                  boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> pre_defined; /* Upvalues by pre-defined registers */
                  boost::unordered_flat_map<luramas_register, luramas_register> defined_upvs;                 /* Register defined in that closure -> Register defined in parent closure */

                  /* Define upvalue by its target register reference */
                  void define(const luramas_register reg, const std::shared_ptr<ir_stat::ir_expr> &e);

                  /* Define upvalue by index of it */
                  void define_upvalue(const std::size_t idx, const std::shared_ptr<ir_stat::ir_expr> &e);

                  void init();
                  bool inited() const;

                private:
                  bool initialized = false;
            };

            namespace emitter {

                  /* Emits a debug name for upvalue in closure */
                  void closure_debug_name(const luramas_register reg, const std::shared_ptr<ir_stat::ir_expr> &expr, const std::shared_ptr<luramas::closures::closure> &closure, const std::shared_ptr<luramas::closures::node> &node);
            } // namespace emitter
      } // namespace upvalues

} // namespace luramas::ir::managers