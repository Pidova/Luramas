#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::cpp::assignment {

      /* Emits dynamic initial assignment */
      inline void initial_assignment(std::string &buffer, const std::vector<std::string> &lvalue, const std::vector<std::string> &rvalue, const luramas_flag fconstant, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            std::string lvalues("");
            std::string rvalues("");

            auto count = lvalue.size();
            for (auto i = 0u; i < count; ++i) {

                  lvalues += lvalue[i];

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        lvalues += format->spacing.format_assignment_initial_lvalue(cpp_langkeyword_list_lvalue);
                  }
            }

            count = rvalue.size();
            for (auto i = 0u; i < count; ++i) {

                  rvalues += rvalue[i];

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        rvalues += format->spacing.format_assignment_initial_rvalue(cpp_langkeyword_list_lvalue);
                  }
            }

            if (fconstant) {
                  buffer += "const ";
            }
            buffer += format->spacing.format_assignment_initial_datatype(cpp_langkeyword_dynamic_datatype);
            buffer += lvalue.size() > 1u ? "[" + lvalues + "]" : lvalues;
            buffer += format->spacing.format_assignment_initial(cpp_langkeyword_assignment);
            buffer += rvalues;
            return;
      }

      /* Emits dynamic assignment */
      inline void assignment(std::string &buffer, const std::vector<std::string> &lvalue, const std::vector<std::string> &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format, const char *const assignment = cpp_langkeyword_assignment) {

            std::string lvalues("");
            std::string rvalues("");

            auto count = lvalue.size();
            for (auto i = 0u; i < count; ++i) {

                  lvalues += lvalue[i];

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        lvalues += format->spacing.format_assignment_lvalue(cpp_langkeyword_list_lvalue);
                  }
            }

            count = rvalue.size();
            for (auto i = 0u; i < count; ++i) {

                  rvalues += rvalue[i];

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        rvalues += format->spacing.format_assignment_rvalue(cpp_langkeyword_list_lvalue);
                  }
            }

            buffer += lvalue.size() > 1u ? "std::tie(" + lvalues + ")" : lvalues;
            buffer += format->spacing.format_assignment(assignment);
            buffer += rvalues;

            return;
      }

      namespace arith {

            /* Emits arith assignment */
            inline void emit_arith_assignment(std::string &buffer, const luramas::il::arch::data::bin_kinds op, const std::vector<std::string> &lvalue, const std::vector<std::string> &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

                  switch (op) {
                        case luramas::il::arch::data::bin_kinds::add_: {
                              luramas::ir::code::emitter::cpp::assignment::assignment(buffer, lvalue, rvalue, format, cpp_langkeyword_arith_assignment_add);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::mod_: {
                              luramas::ir::code::emitter::cpp::assignment::assignment(buffer, lvalue, rvalue, format, cpp_langkeyword_arith_assignment_mod);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::sub_: {
                              luramas::ir::code::emitter::cpp::assignment::assignment(buffer, lvalue, rvalue, format, cpp_langkeyword_arith_assignment_sub);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::div_: {
                              luramas::ir::code::emitter::cpp::assignment::assignment(buffer, lvalue, rvalue, format, cpp_langkeyword_arith_assignment_div);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::mul_: {
                              luramas::ir::code::emitter::cpp::assignment::assignment(buffer, lvalue, rvalue, format, cpp_langkeyword_arith_assignment_mul);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::pow_: {
                              luramas::ir::code::emitter::cpp::assignment::assignment(buffer, lvalue, rvalue, format, cpp_langkeyword_arith_assignment_pow);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::xor_: {
                              luramas::ir::code::emitter::cpp::assignment::assignment(buffer, lvalue, rvalue, format, cpp_langkeyword_arith_assignment_xor);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::or_: {
                              luramas::ir::code::emitter::cpp::assignment::assignment(buffer, lvalue, rvalue, format, cpp_langkeyword_arith_assignment_or);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::and_: {
                              luramas::ir::code::emitter::cpp::assignment::assignment(buffer, lvalue, rvalue, format, cpp_langkeyword_arith_assignment_and);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::shr_: {
                              luramas::ir::code::emitter::cpp::assignment::assignment(buffer, lvalue, rvalue, format, cpp_langkeyword_arith_assignment_shr);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::shl_: {
                              luramas::ir::code::emitter::cpp::assignment::assignment(buffer, lvalue, rvalue, format, cpp_langkeyword_arith_assignment_shl);
                              break;
                        }
                        default: {
                              luramas::error::error("Unknown binkind assignment when trying too emit arithmetic assignment.");
                        }
                  }
                  return;
            }

      } // namespace arith

} // namespace luramas::ir::code::emitter::cpp::assignment