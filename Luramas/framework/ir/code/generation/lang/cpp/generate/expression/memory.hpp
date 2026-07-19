#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::cpp::memory {

      /* Emits memread */
      inline void emit_memread(std::string &buffer, const std::shared_ptr<luramas::ir::types::object::type> &t, const std::string &value, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += (cpp_langkeyword_memread_pre cpp_langkeyword_memread_Tpre) + t->str() + cpp_langkeyword_memread_Tpost + value + cpp_langkeyword_memread_post;
            return;
      }
} // namespace luramas::ir::code::emitter::cpp::memory