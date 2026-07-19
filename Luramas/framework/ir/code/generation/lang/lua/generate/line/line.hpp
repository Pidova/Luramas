#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::lua::line {

      /* Emits line break */
      inline void emit_linebreak(std::string &buffer, const std::size_t amt, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += std::string(amt, lua_langkeyword_line_break);
            return;
      }

      /* Emits semicolon */
      inline void emit_semicolon(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += format->spacing.format_semicolon(lua_langkeyword_semicolon);
            return;
      }

      /* Emits parenthesize */
      inline void emit_parenthesize(std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += format->spacing.format_parenthesis_ref(lua_langkeyword_parenthesis_open, data, lua_langkeyword_parenthesis_close);
            return;
      }

} // namespace luramas::ir::code::emitter::lua::line