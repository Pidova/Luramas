#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::lua::arith {

      /* Emits arith operation */
      inline void emit_arith_operation(std::string &buffer, const luramas::il::arch::data::bin_kinds kind, const std::string &lvalue, const std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += lvalue;
            switch (kind) {
                  case luramas::il::arch::data::bin_kinds::add_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_add);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::mod_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_mod);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::sub_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_sub);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::div_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_div);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::mul_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_mul);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::pow_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_pow);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::and_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_and);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::or_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_or);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::shl_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_shl);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::shr_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_shr);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::idiv_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_idiv);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::xor_: {
                        buffer += format->spacing.format_arith(lua_langkeyword_arith_xor);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Unkown binkind when trying too emit arithmetic.");
                  }
            }
            buffer += rvalue;
            return;
      }

} // namespace luramas::ir::code::emitter::lua::arith