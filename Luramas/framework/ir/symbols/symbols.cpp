#include "symbols.hpp"

std::string luramas::ir::symbols::param::str() const {
      return this->any ? "???" : this->type->str();
}

void luramas::ir::symbols::symbol::emit_name(const std::string &str) {
      this->name = str;
      return;
}
void luramas::ir::symbols::symbol::emit_arg() {
      this->args.emplace_back(param(true));
      return;
}
void luramas::ir::symbols::symbol::emit_arg(const std::shared_ptr<ir_stat::ir_expr> &type) {
      this->args.emplace_back(param(false, type));
      return;
}
void luramas::ir::symbols::symbol::emit_return() {
      this->returns.emplace_back(param(true));
      return;
}
void luramas::ir::symbols::symbol::emit_return(const std::shared_ptr<ir_stat::ir_expr> &type) {
      this->returns.emplace_back(param(false, type));
      return;
}
std::string luramas::ir::symbols::symbol::str() const {

      auto result = this->name + "(";

      for (auto o = 0u; o < this->args.size(); ++o) {
            result += this->args[o].str();
            if (o - 1u != this->args.size()) {
                  result += ", ";
            }
      }
      result += ")";
      if (this->returns.size()) {
            result += " | ";
            for (auto o = 0u; o < this->returns.size(); ++o) {
                  result += this->returns[o].str();
                  if (o - 1u != this->returns.size()) {
                        result += ", ";
                  }
            }
      }
      return result;
}