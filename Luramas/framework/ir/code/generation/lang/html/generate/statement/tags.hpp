#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::html::tags {

      /* Emits tag start */
      inline void start(std::string &buffer, const std::string &name, const std::vector<std::pair<std::string, std::string>> &ids, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            /* Pre */
            buffer += html_langkeyword_new_tag_pre;
            format->spacing.format_tag_spacing(buffer);
            buffer += name;

            const auto count = ids.size();
            if (count) {
                  buffer += html_langkeyword_new_key_delimiter;
            }
            for (auto i = 0u; i < count; ++i) {

                  const auto &[k, v] = ids[i];
                  buffer += (!k.empty() ? k + html_langkeyword_new_key_equal : "") + v;

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        buffer += html_langkeyword_new_key_delimiter;
                  }
            }

            /* Post */
            buffer += html_langkeyword_new_tag_post;
            return;
      }

      /* Emits tag end */
      inline void end(std::string &buffer, const std::string &name, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += html_langkeyword_end_tag_pre;
            buffer += name;
            buffer += html_langkeyword_end_tag_post;
            return;
      }

} // namespace luramas::ir::code::emitter::html::tags