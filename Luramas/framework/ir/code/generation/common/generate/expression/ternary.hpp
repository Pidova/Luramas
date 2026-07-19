#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::ternary {

      /* Emits tenary */
      inline void emit_ternary(const syntax::emitter_syntax syn, std::string &buffer, const std::string &cond, const std::string &thenv, const std::string &elsev, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::luau: {
                        luau::ternary::emit_ternary(buffer, cond, thenv, elsev, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::ternary::emit_ternary(buffer, cond, thenv, elsev, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Ternary");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::ternary
