#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::lua::selfcall {

      /* Emits selfcall */
      inline void emit_selfcall(std::string &buffer, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += lvalue;
            buffer += lua_langkeyword_selfcall;
            buffer += rvalue;
            return;
      }

} // namespace luramas::ir::code::emitter::lua::selfcall