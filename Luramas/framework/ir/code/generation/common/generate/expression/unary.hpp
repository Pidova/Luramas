#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::unary {

      /* Emits unary too reference string. */
      inline void emit_unary(const syntax::emitter_syntax syn, std::string &buffer, const luramas::il::arch::data::bin_kinds unary, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::unary::emit_unary(buffer, unary, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::unary::emit_unary(buffer, unary, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::unary::emit_unary(buffer, unary, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Unary");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::unary