#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::call {

      /* Emits call */
      inline void emit_call(const syntax::emitter_syntax syn, std::string &buffer, const std::string &call, const std::vector<std::string> &vect, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::call::emit_call(buffer, call, vect, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::call::emit_call(buffer, call, vect, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::call::emit_call(buffer, call, vect, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Call operation");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::call