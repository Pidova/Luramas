#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::cpp::flags {

      /* Emits call */
      inline void emit_flag(std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            cpp::call::emit_call(buffer, cpp_langkeyword_flags_get, {data}, format);
            return;
      }

} // namespace luramas::ir::code::emitter::cpp::flags