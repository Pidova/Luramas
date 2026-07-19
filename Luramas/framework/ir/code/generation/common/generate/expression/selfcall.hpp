#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::selfcall {

      /* Emits selfcall */
      inline void emit_selfcall(const syntax::emitter_syntax syn, std::string &buffer, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::selfcall::emit_selfcall(buffer, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::selfcall::emit_selfcall(buffer, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::selfcall::emit_selfcall(buffer, lvalue, rvalue, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Selfcall");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::selfcall