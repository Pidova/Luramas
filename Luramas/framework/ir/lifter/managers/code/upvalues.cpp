#include "../common.hpp"

namespace luramas::ir::managers::upvalues {

      void manager::define(const luramas_register reg, const std::shared_ptr<ir_stat::ir_expr> &e) {
            this->pre_defined.try_emplace(reg, e);
            this->defined_upvs.try_emplace(e->reg, reg);
            return;
      }
      void manager::define_upvalue(const std::size_t idx, const std::shared_ptr<ir_stat::ir_expr> &e) {
            this->upvalues.try_emplace(idx, e);
            return;
      }
      void manager::init() {
            this->initialized = true;
            return;
      };
      bool manager::inited() const {
            return this->initialized;
      };

      namespace emitter {

            void closure_debug_name(const luramas_register reg, const std::shared_ptr<ir_stat::ir_expr> &expr, const std::shared_ptr<luramas::closures::closure> &closure, const std::shared_ptr<luramas::closures::node> &node) {
                  if (closure->il->debug.has_value()) {
                        if (const auto v = closure->il->debug.value().get(reg, node->address); v) {
                              expr->emit_register_annotation(v);
                        }
                  }
                  return;
            }
      } // namespace emitter
} // namespace luramas::ir::managers::upvalues