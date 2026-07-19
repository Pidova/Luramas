#pragma once
#include "../ir.hpp"

namespace luramas::ir::symbols {

      struct param {

            bool any = false;
            std::shared_ptr<ir_stat::ir_expr> type = nullptr;

            std::string str() const;
      };
      struct symbol {

            std::string name = "";
            std::vector<param> args;
            std::vector<param> returns;

            symbol(const std::string &name)
                : name(name) {
            }

            void emit_name(const std::string &str);
            void emit_arg();
            void emit_arg(const std::shared_ptr<ir_stat::ir_expr> &type);
            void emit_return();
            void emit_return(const std::shared_ptr<ir_stat::ir_expr> &type);
            std::string str() const;
      };

      using table = std::vector<symbol>;
} // namespace luramas::ir::symbols