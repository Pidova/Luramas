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
                  boost::unordered_flat_map<std::size_t, std::shared_ptr<ir_stat::ir_expr>> upvalues;
                  boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> pre_defined;
                  boost::unordered_flat_map<luramas_register, luramas_register> defined_upvs;

                  void define(const luramas_register reg, const std::shared_ptr<ir_stat::ir_expr> &e);
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