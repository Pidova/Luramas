#include "../common.hpp"

namespace luramas::ir::parser {

      std::shared_ptr<ir_stat::ir_expr> manager::set(const std::string &name, const std::shared_ptr<ir_stat::ir_expr> &expr) {

            if (this->var_scope.empty()) {
                  return nullptr;
            }
            this->var_scope.back()[name] = expr;
            return expr;
      }
      std::shared_ptr<ir_stat::ir_expr> manager::get(const std::string &name) const {

            if (this->var_scope.empty()) {
                  return nullptr;
            }
            if (const auto it = this->var_scope.back().find(name); it != this->var_scope.back().end()) {
                  return it->second;
            }
            return nullptr;
      }
      luramas_register manager::get_reg() {

            return this->avaliable_reg++;
      }

      const char *const str(const errors &err) {
            switch (err) {
                  case errors::none: {
                        return "none";
                  }
                  case errors::invalid_keyword: {
                        return "invalid keyword";
                  }
                  case errors::encapsulation_close: {
                        return "extra encapsulation close was emmitted";
                  }
                  case errors::encapsulation_unclosed: {
                        return "unclosed encapsulation";
                  }
                  case errors::no_lvalue: {
                        return "no lvalue";
                  }
                  case errors::no_rvalue: {
                        return "no rvalue";
                  }
                  case errors::unclosed_string: {
                        return "unclosed string";
                  }
                  case errors::assignment_mismatch: {
                        return "assignment size mismatch";
                  }
                  default: {
                        break;
                  }
            }
            return "unknown error";
      }
} // namespace luramas::ir::parser