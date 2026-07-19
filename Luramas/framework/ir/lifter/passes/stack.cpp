#include "includes/common.hpp"

struct stack {

      void push(const std::shared_ptr<ir_stat::ir_expr> &expr) {
            this->internal_stack.emplace_back(expr);
            return;
      }
      void pop(const std::size_t amt) {
            if (this->internal_stack.size() < amt) {
                  return;
            }
            for (auto i = 0u; i < amt; ++i) {
                  this->internal_stack.pop_back();
            }
            return;
      }
      void pop(const std::shared_ptr<ir_stat::ir_expr> &expr) {
            if (const auto it = std::find_if(this->internal_stack.rbegin(), this->internal_stack.rend(), [&](const auto &m) { return *m == *expr; }); it != this->internal_stack.rend()) {
                  this->internal_stack.erase(std::next(it).base());
            }
            return;
      }
      std::shared_ptr<ir_stat::ir_expr> index(const luramas_vaddress idx = -1) const {
            return (idx < 0) ? (this->internal_stack.empty() ? nullptr : this->internal_stack.back())
                             : (static_cast<std::size_t>(idx) >= this->internal_stack.size() ? nullptr : this->internal_stack[idx]);
      }

      std::vector<std::shared_ptr<ir_stat::ir_expr>> internal_stack;
};

namespace luramas::ir::passes {

      void stack_to_register_promote(pass_manager &pm, shared &s) {

            if (!pm.env_flags.fsafe_stack) {
                  return;
            }
            boost::unordered_flat_map<std::size_t, stack> map;

            for (const auto &i : pm.iter()) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::stack_pop: {

                              break;
                        }
                        case keywords::stack_push: {

                              break;
                        }
                        case keywords::stack_read: {

                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
            return;
      }
} // namespace luramas::ir::passes