#pragma once
#include "../generate.hpp"
#include "../line/line.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::comment {

      /* Emit expandable comment. */
      inline void expandable_comment(const syntax::emitter_syntax syn, std::string &buffer, const std::string &src, const std::shared_ptr<luramas::ir::data::format::format> &format, const std::size_t current_amt = 0u, const std::size_t pre_amt = 0u, const std::size_t post_amt = 0u, const bool linebreak = true) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::comment::expandable_comment(buffer, src, format, current_amt, pre_amt, post_amt, linebreak);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::comment::expandable_comment(buffer, src, format, current_amt, pre_amt, post_amt, linebreak);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::comment::expandable_comment(buffer, src, format, current_amt, pre_amt, post_amt, linebreak);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Expandable comment");
                  }
            }
            return;
      }

      /* Emit comment. */
      inline void comment(const syntax::emitter_syntax syn, std::string &buffer, const std::string &src, const std::shared_ptr<luramas::ir::data::format::format> &format, const std::size_t current_amt = 0u, const bool linebreak = true) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::comment::comment(buffer, src, format, current_amt, linebreak);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::comment::comment(buffer, src, format, current_amt, linebreak);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::comment::comment(buffer, src, format, current_amt, linebreak);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Comments");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::comment