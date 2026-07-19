#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::luau::line {

      /* Emits line break */
      inline void emit_linebreak(std::string &buffer, const std::size_t amt, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += std::string(amt, luau_langkeyword_line_break);
            return;
      }

      /* Emits semicolon */
      inline void emit_semicolon(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += format->spacing.format_semicolon(luau_langkeyword_semicolon);
            return;
      }

      /* Emits parenthesize */
      inline void emit_parenthesize(std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += format->spacing.format_parenthesis_ref(luau_langkeyword_parenthesis_open, data, luau_langkeyword_parenthesis_close);
            return;
      }

      /* Emits pre data flags */
      inline void emit_pre_flags(std::string &buffer, const keywords k, const ir::flags::ir_stat &stat_flags, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            return;
      }

      /* Emits post data flags */
      inline void emit_post_flags(std::string &buffer, const keywords k, const ir::flags::ir_stat &stat_flags, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            return;
      }
} // namespace luramas::ir::code::emitter::luau::line