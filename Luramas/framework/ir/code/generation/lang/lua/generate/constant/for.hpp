#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::lua::for_ {

      /* Emits for */
      template <bool numeric = false /* Numeric(true) or Generic(false) */>
      inline void emit_for(std::string &buffer, std::vector<std::string> &vars, std::vector<std::string> &iterator, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            /* for?? e.g. "for " */
            buffer += std::string(lua_langkeyword_for + format->spacing.spacing_forloop);

            /* Emit variables */
            /* for{??} e.g. "for " */
            const auto var_count = vars.size();
            for (auto i = 0u; i < var_count; ++i) {

                  buffer += vars[i];

                  if ((i + 1u) != var_count) {
                        buffer += format->spacing.format_parameter_delimiter(lua_langkeyword_for_delimiter);
                  }
            }

            /* Emit in */
            /* for ?? e.g. "for " */
            buffer += (numeric) ? std::string(format->spacing.spacing_forloop_numeric_pre + lua_langkeyword_for_numeric + format->spacing.spacing_forloop_numeric_post) : std::string(format->spacing.spacing_forloop_generic_pre + lua_langkeyword_for_generic + format->spacing.spacing_forloop_generic_post);

            /* Emit iteration */
            const auto iter_count = iterator.size();
            for (auto i = 0u; i < iter_count; ++i) {

                  buffer += iterator[i];

                  if ((i + 1u) != iter_count) {
                        buffer += format->spacing.format_parameter_delimiter(lua_langkeyword_for_delimiter);
                  }
            }

            /* Start new scope */
            buffer += std::string(format->spacing.spacing_forloop_scope_start + lua_langkeyword_for_scope_start);
            return;
      }

} // namespace luramas::ir::code::emitter::lua::for_