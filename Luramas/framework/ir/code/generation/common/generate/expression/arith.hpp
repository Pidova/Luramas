#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::arith {

      /* Emits arith operation */
      inline void emit_arith_operation(const syntax::emitter_syntax syn, std::string &buffer, const luramas::il::arch::data::bin_kinds kind, const std::string &lvalue, const std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::arith::emit_arith_operation(buffer, kind, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::arith::emit_arith_operation(buffer, kind, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::arith::emit_arith_operation(buffer, kind, lvalue, rvalue, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Arith operation");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::arith