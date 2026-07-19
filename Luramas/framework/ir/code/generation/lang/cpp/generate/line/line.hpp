#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::cpp::line {

      /* Emits line break */
      inline void emit_linebreak(std::string &buffer, const std::size_t amt, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += std::string(amt, cpp_langkeyword_line_break);
            return;
      }

      /* Emits semicolon */
      inline void emit_semicolon(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += format->spacing.format_semicolon(cpp_langkeyword_semicolon);
            return;
      }

      /* Emits parenthesize */
      inline void emit_parenthesize(std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += format->spacing.format_parenthesis_ref(cpp_langkeyword_parenthesis_open, data, cpp_langkeyword_parenthesis_close);
            return;
      }

      /* Emits pre data flags */
      inline void emit_pre_flags(std::string &buffer, const keywords k, const ir::flags::ir_stat &stat_flags, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (k) {
                  case keywords::assignment: {

                        if (stat_flags.fdead_sideeffects) {
                              buffer += stat_flags.fdefine ? cpp_langkeyword_dynamic_deadv_sideeffects_pre : cpp_langkeyword_dynamic_dead_sideeffects_pre;
                        }
                        break;
                  }
                  default: {

                        if (stat_flags.fdead_sideeffects) {
                              buffer += cpp_langkeyword_dynamic_dead_sideeffects_pre;
                        }
                        break;
                  }
            }
            return;
      }

      /* Emits post data flags */
      inline void emit_post_flags(std::string &buffer, const keywords k, const ir::flags::ir_stat &stat_flags, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (k) {
                  case keywords::assignment: {

                        if (stat_flags.fdead_sideeffects) {
                              buffer += cpp_langkeyword_dynamic_deadv_sideeffects_post;
                        }
                        break;
                  }
                  default: {

                        if (stat_flags.fdead_sideeffects) {
                              buffer += cpp_langkeyword_dynamic_dead_sideeffects_post;
                        }
                        break;
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::cpp::line