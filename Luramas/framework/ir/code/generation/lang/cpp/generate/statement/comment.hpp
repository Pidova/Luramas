#pragma once
#include "../emit.hpp"
#include "../line/line.hpp"

namespace luramas::ir::code::emitter::cpp::comment {

      /* Emit expandable comment. */
      inline void expandable_comment(std::string &buffer, const std::string &src, const std::shared_ptr<luramas::ir::data::format::format> &format, const std::size_t current_amt = 0u, const std::size_t pre_amt = 0u, const std::size_t post_amt = 0u, const bool linebreak = true) {

            std::string line_break_pre("");
            if (linebreak) {
                  luramas::ir::code::emitter::cpp::line::emit_linebreak(line_break_pre, pre_amt, format);
            }

            std::string line_break_post("");
            if (linebreak) {
                  luramas::ir::code::emitter::cpp::line::emit_linebreak(line_break_post, post_amt, format);
            }

            std::string line_break_end("");
            if (src.back() != '\n' && linebreak) {
                  luramas::ir::code::emitter::cpp::line::emit_linebreak(line_break_end, current_amt, format);
            }

            buffer += std::string(cpp_langkeyword_comment_expandable_start) + line_break_pre + src + line_break_post + std::string(cpp_langkeyword_comment_expandable_end) + line_break_end;
            return;
      }

      /* Emit comment. */
      inline void comment(std::string &buffer, const std::string &src, const std::shared_ptr<luramas::ir::data::format::format> &format, const std::size_t current_amt = 0u, const bool linebreak = true) {

            std::string line_break_end("");
            if (src.back() != '\n' && linebreak) {
                  luramas::ir::code::emitter::cpp::line::emit_linebreak(line_break_end, current_amt, format);
            }

            buffer += std::string(cpp_langkeyword_comment) + std::string(" ") + src + line_break_end;
            return;
      }

} // namespace luramas::ir::code::emitter::cpp::comment