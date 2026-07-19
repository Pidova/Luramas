#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::cpp::memory {

      /* Emits memwrite */
      inline void emit_memwrite(std::string &buffer, const std::shared_ptr<luramas::ir::types::object::type> &t, const std::string &l, const std::string &r, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += (cpp_langkeyword_memwrite_pre cpp_langkeyword_memwrite_Tpre) + t->str() + (cpp_langkeyword_memwrite_Tpost cpp_langkeyword_memwrite_v_pre) + l + (cpp_langkeyword_memwrite_v_post cpp_langkeyword_memwrite_asgn_pre) + r + cpp_langkeyword_memwrite_asgn_post;
            return;
      }

} // namespace luramas::ir::code::emitter::cpp::memory