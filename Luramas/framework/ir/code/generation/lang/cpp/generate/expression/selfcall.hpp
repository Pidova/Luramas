#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::cpp::selfcall {

      /* Emits selfcall */
      inline void emit_selfcall(std::string &buffer, const std::string &lvalue, const std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += lvalue;
            buffer += cpp_langkeyword_selfcall;
            buffer += rvalue;
            return;
      }

} // namespace luramas::ir::code::emitter::cpp::selfcall