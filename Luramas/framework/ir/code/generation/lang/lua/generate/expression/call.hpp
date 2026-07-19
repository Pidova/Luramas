#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::lua::call {

      /* Emits call */
      inline void emit_call(std::string &buffer, const std::string &call, const std::vector<std::string> &vect, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            std::string args("");

            buffer += call;
            format->spacing.format_call_spacing(buffer);

            const auto count = vect.size();
            for (auto i = 0ull; i < count; ++i) {

                  args += vect[i];

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        args += format->spacing.format_parameter_delimiter(lua_langkeyword_call_delimiter);
                  }
            }

            /* ( ?? ) */
            args = format->spacing.format_parameter_open(lua_langkeyword_call_parenthesis_open) + args;
            args += format->spacing.format_parameter_close(lua_langkeyword_call_parenthesis_close);

            buffer += args;
            return;
      }

} // namespace luramas::ir::code::emitter::lua::call