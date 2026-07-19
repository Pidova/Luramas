#pragma once
#include "../emit.hpp"
#include "unary.hpp"

namespace luramas::ir::code::emitter::lua::logical {

      inline void emit_operator(std::string &buffer, const luramas::il::arch::data::bin_kinds op, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (op) {
                  case luramas::il::arch::data::bin_kinds::and_: {
                        buffer += format->spacing.format_logical_operation(lua_langkeyword_compare_and);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::or_: {
                        buffer += format->spacing.format_logical_operation(lua_langkeyword_compare_or);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::lt_: {
                        buffer += format->spacing.format_logical_operation(lua_langkeyword_compare_lessthan);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::lte_: {
                        buffer += format->spacing.format_logical_operation(lua_langkeyword_compare_lessthanequal);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::eq_: {
                        buffer += format->spacing.format_logical_operation(lua_langkeyword_compare_equal);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::ne_: {
                        buffer += format->spacing.format_logical_operation(lua_langkeyword_compare_notequal);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::gt_: {
                        buffer += format->spacing.format_logical_operation(lua_langkeyword_compare_greaterthan);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::gte_: {
                        buffer += format->spacing.format_logical_operation(lua_langkeyword_compare_greaterthanequal);
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return;
      }

      /* Emits logical operation */
      inline void emit_logical_operation(std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            if (op == il::arch::data::bin_kinds::nt_) {
                  unary::emit_unary(buffer, op, format);
            }
            buffer += lvalue;
            logical::emit_operator(buffer, op, format);
            buffer += rvalue;
            return;
      }

      /* Emits logical compare e.g. (?? ?? ??) */
      inline void emit_logical_compare(std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format, const bool open, const bool close) {

            if (open) {
                  buffer += format->spacing.format_parenthesis_open(lua_langkeyword_parenthesis_open);
            }

            luramas::ir::code::emitter::lua::logical::emit_logical_operation(buffer, op, lvalue, rvalue, format);

            if (close) {
                  buffer += format->spacing.format_parenthesis_open(lua_langkeyword_parenthesis_close);
            }
            return;
      }

} // namespace luramas::ir::code::emitter::lua::logical