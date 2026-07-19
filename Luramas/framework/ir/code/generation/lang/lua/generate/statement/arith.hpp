#pragma once
#include "../emit.hpp"
#include "../expression/arith.hpp"

namespace luramas::ir::code::emitter::lua::arith_statement {

      /* Emits arith routine */
      inline void emit_arith(std::string &buffer, const luramas::il::arch::data::bin_kinds kind, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            std::string ref("");

            luramas::ir::code::emitter::lua::arith::emit_arith_operation(ref, kind, lvalue, rvalue, format);
            buffer += format->spacing.format_parenthesis_ref(lua_langkeyword_parenthesis_open, ref, lua_langkeyword_parenthesis_close);
            return;
      }

} // namespace luramas::ir::code::emitter::lua::arith_statement
