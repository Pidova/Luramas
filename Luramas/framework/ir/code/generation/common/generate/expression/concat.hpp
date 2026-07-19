#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::concat {

      /* Emits concat */
      inline void emit_concat(const syntax::emitter_syntax syn, std::string &buffer, std::vector<std::string> &vect, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::concat::emit_concat(buffer, vect, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::concat::emit_concat(buffer, vect, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Concat");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::concat