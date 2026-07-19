#pragma once

#include "../expression/arith.hpp"
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::arith_statement {

      /* Emits arith routine */
      inline void emit_arith(const syntax::emitter_syntax syn, std::string &buffer, const luramas::il::arch::data::bin_kinds kind, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::arith_statement::emit_arith(buffer, kind, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::arith_statement::emit_arith(buffer, kind, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::arith_statement::emit_arith(buffer, kind, lvalue, rvalue, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Arithmetic");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::arith_statement
