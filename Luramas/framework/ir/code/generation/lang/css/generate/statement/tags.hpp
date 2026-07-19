#pragma once
#include "../emit.hpp"
#include "../line/line.hpp"

namespace luramas::ir::code::emitter::css::tags {

      /* Emits tag start */
      inline void start(std::string &buffer, const std::string &name, const std::vector<std::pair<std::string, std::string>> &ids, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            /* Pre */
            buffer += name;
            format->spacing.format_tag_spacing(buffer);
            buffer += css_langkeyword_new_tag_pre;

            if (format->linebreak.enabled) {
                  line::emit_linebreak(buffer, format->linebreak.tag_start_post, format);
            }

            for (const auto &[k, v] : ids) {

                  buffer += (!k.empty() ? k + css_langkeyword_new_key_eq : "") + v + css_langkeyword_new_key_end;
                  if (format->linebreak.enabled) {
                        line::emit_linebreak(buffer, format->linebreak.tag_start_post, format);
                  }
            }

            /* Post */
            buffer += css_langkeyword_new_tag_post;
            return;
      }

      inline void end(std::string &buffer, const std::string &name, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += css_langkeyword_end_tag_pre;
            buffer += css_langkeyword_end_tag_post;
            return;
      }
} // namespace luramas::ir::code::emitter::css::tags