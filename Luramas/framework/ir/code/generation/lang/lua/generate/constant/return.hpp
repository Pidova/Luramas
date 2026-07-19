#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::lua::return_ {

      /* Emits return */
      inline void emit_return(std::string &buffer, std::vector<std::string> &vect, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            const auto count = vect.size();
            buffer += (count) ? format->spacing.format_return(lua_langkeyword_return) : lua_langkeyword_return;

            for (auto i = 0u; i < count; ++i) {

                  buffer += vect[i];
                  if ((i + 1u) != count) {
                        buffer += format->spacing.format_parameter_delimiter(lua_langkeyword_return_seprator);
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::lua::return_