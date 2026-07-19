#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::html::line {

      /* Emits line break */
      inline void emit_linebreak(std::string &buffer, const std::size_t amt, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += std::string(amt, html_langkeyword_line_break);
            return;
      }

} // namespace luramas::ir::code::emitter::html::line