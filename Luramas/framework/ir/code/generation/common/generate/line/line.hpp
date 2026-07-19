#pragma once
#include "../../../../../flags.hpp"
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::line {

      /* Emits line break */
      inline void emit_linebreak(const syntax::emitter_syntax syn, std::string &buffer, const std::size_t amt, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::line::emit_linebreak(buffer, amt, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::line::emit_linebreak(buffer, amt, format);
                        break;
                  }
                  case syntax::emitter_syntax::html: {
                        html::line::emit_linebreak(buffer, amt, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::line::emit_linebreak(buffer, amt, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Line break");
                  }
            }
            return;
      }

      /* Emits semicolon */
      inline void emit_semicolon(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::line::emit_semicolon(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::line::emit_semicolon(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::line::emit_semicolon(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Semicolon statement");
                  }
            }
            return;
      }

      /* Emits parenthesize */
      inline void emit_parenthesize(const syntax::emitter_syntax syn, std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::line::emit_parenthesize(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::line::emit_parenthesize(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::line::emit_parenthesize(buffer, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Semicolon statement");
                  }
            }
            return;
      }

      /* Emits pre data flags */
      inline void emit_pre_flags(const syntax::emitter_syntax syn, std::string &buffer, const keywords k, const ir::flags::ir_stat &stat_flags, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {
                        cpp::line::emit_pre_flags(buffer, k, stat_flags, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::line::emit_pre_flags(buffer, k, stat_flags, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Line break");
                  }
            }
            return;
      }

      /* Emits post data flags */
      inline void emit_post_flags(const syntax::emitter_syntax syn, std::string &buffer, const keywords k, const ir::flags::ir_stat &stat_flags, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {
                        cpp::line::emit_post_flags(buffer, k, stat_flags, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::line::emit_post_flags(buffer, k, stat_flags, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Line break");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::line