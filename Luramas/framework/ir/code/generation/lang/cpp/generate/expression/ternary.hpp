#pragma once
#include "../emit.hpp"
#include "unary.hpp"

namespace luramas::ir::code::emitter::cpp::ternary {

      /* Emits tenary */
      inline void emit_ternary(std::string &buffer, const std::string &cond, const std::string &thenv, const std::string &elsev, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer = format->spacing.format_ternary_start(cpp_langkeyword_ternary_start);

            /* (??) */
            buffer += cond;

            /* then else */
            buffer += format->spacing.format_ternary_then(cpp_langkeyword_ternary_then);
            buffer += thenv;
            buffer += format->spacing.format_ternary_else(cpp_langkeyword_ternary_else);
            buffer += elsev;
            return;
      }

} // namespace luramas::ir::code::emitter::cpp::ternary
