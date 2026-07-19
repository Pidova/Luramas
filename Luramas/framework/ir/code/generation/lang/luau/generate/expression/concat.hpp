#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::luau::concat {

      /* Emits concat */
      inline void emit_concat(std::string &buffer, const std::vector<std::string> &vect, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            const auto count = vect.size();
            for (auto i = 0u; i < count; ++i) {

                  buffer += vect[i];
                  if ((i + 1u) != count) {
                        buffer += format->spacing.format_concat(luau_langkeyword_concat);
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::luau::concat