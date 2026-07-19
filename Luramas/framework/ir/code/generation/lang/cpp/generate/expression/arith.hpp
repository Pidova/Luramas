#pragma once
#include "../emit.hpp"
#include "../expression/call.hpp"

namespace luramas::ir::code::emitter::cpp::arith {

      /* Emits arith operation */
      inline void emit_arith_operation(std::string &buffer, const luramas::il::arch::data::bin_kinds kind, const std::string &lvalue, const std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (kind) {
                  case luramas::il::arch::data::bin_kinds::pow_: {
                        cpp::call::emit_call(buffer, cpp_langkeyword_arith_pow, {lvalue, rvalue}, format);
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::idiv_: {
                        cpp::call::emit_call(buffer, cpp_langkeyword_arith_idiv, {lvalue, rvalue}, format);
                        break;
                  }
                  default: {
                        buffer += lvalue;
                        switch (kind) {
                              case luramas::il::arch::data::bin_kinds::add_: {
                                    buffer += format->spacing.format_arith(cpp_langkeyword_arith_add);
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::mod_: {
                                    buffer += format->spacing.format_arith(cpp_langkeyword_arith_mod);
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::sub_: {
                                    buffer += format->spacing.format_arith(cpp_langkeyword_arith_sub);
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::div_: {
                                    buffer += format->spacing.format_arith(cpp_langkeyword_arith_div);
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::mul_: {
                                    buffer += format->spacing.format_arith(cpp_langkeyword_arith_mul);
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::and_: {
                                    buffer += format->spacing.format_arith(cpp_langkeyword_arith_and);
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::or_: {
                                    buffer += format->spacing.format_arith(cpp_langkeyword_arith_or);
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::xor_: {
                                    buffer += format->spacing.format_arith(cpp_langkeyword_arith_xor);
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::shr_: {
                                    buffer += format->spacing.format_arith(cpp_langkeyword_arith_shr);
                                    break;
                              }
                              case luramas::il::arch::data::bin_kinds::shl_: {
                                    buffer += format->spacing.format_arith(cpp_langkeyword_arith_shl);
                                    break;
                              }
                              default: {
                                    luramas::error::error("Unkown binkind when trying too emit arithmetic.");
                              }
                        }
                        buffer += rvalue;
                        break;
                  }
            }

            return;
      }

} // namespace luramas::ir::code::emitter::cpp::arith