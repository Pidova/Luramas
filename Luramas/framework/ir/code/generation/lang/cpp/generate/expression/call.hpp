#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::cpp::call {

      /* Emits call */
      inline void emit_call(std::string &buffer, const std::string &call, const std::vector<std::string> &vect, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            std::string args("");

            buffer += call;
            format->spacing.format_call_spacing(buffer);

            const auto count = vect.size();
            for (auto i = 0u; i < count; ++i) {

                  if (vect[i].empty()) {
                        continue;
                  }
                  args += vect[i];

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        args += format->spacing.format_parameter_delimiter(cpp_langkeyword_call_delimiter);
                  }
            }

            /* ( ?? ) */
            args = format->spacing.format_parameter_open(cpp_langkeyword_call_parenthesis_open) + args;
            args += format->spacing.format_parameter_close(cpp_langkeyword_call_parenthesis_close);

            buffer += args;
            return;
      }

} // namespace luramas::ir::code::emitter::cpp::call