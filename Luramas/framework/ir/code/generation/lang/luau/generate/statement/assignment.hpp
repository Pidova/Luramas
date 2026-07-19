#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::luau::assignment {

      /* Emits dynamic initial assignment */
      inline void initial_assignment(std::string &buffer, const std::vector<std::string> &lvalue, const std::vector<std::string> &rvalue, const luramas_flag fconstant, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            std::string lvalues("");
            std::string rvalues("");

            auto count = lvalue.size();
            for (auto i = 0u; i < count; ++i) {

                  lvalues += lvalue[i];

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        lvalues += format->spacing.format_assignment_initial_lvalue(luau_langkeyword_list_lvalue);
                  }
            }

            count = rvalue.size();
            for (auto i = 0u; i < count; ++i) {

                  rvalues += rvalue[i];

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        rvalues += format->spacing.format_assignment_initial_rvalue(luau_langkeyword_list_lvalue);
                  }
            }

            buffer += format->spacing.format_assignment_initial_datatype(luau_langkeyword_dynamic_datatype);
            buffer += lvalues;
            buffer += format->spacing.format_assignment_initial(luau_langkeyword_assignment);
            buffer += rvalues;
            return;
      }

      /* Emits dynamic assignment */
      inline void assignment(std::string &buffer, const std::vector<std::string> &lvalue, const std::vector<std::string> &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format, const char *const assignment = luau_langkeyword_assignment) {

            std::string lvalues("");
            std::string rvalues("");

            auto count = lvalue.size();
            for (auto i = 0u; i < count; ++i) {

                  lvalues += lvalue[i];

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        lvalues += format->spacing.format_assignment_lvalue(luau_langkeyword_list_lvalue);
                  }
            }

            count = rvalue.size();
            for (auto i = 0u; i < count; ++i) {

                  rvalues += rvalue[i];

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        rvalues += format->spacing.format_assignment_rvalue(luau_langkeyword_list_lvalue);
                  }
            }

            buffer += lvalues;
            buffer += format->spacing.format_assignment(assignment);
            buffer += rvalues;

            return;
      }

      namespace arith {

            /* Emits arith assignment */
            inline void emit_arith_assignment(std::string &buffer, const luramas::il::arch::data::bin_kinds op, const std::vector<std::string> &lvalue, const std::vector<std::string> &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

                  switch (op) {
                        case luramas::il::arch::data::bin_kinds::add_: {
                              luramas::ir::code::emitter::luau::assignment::assignment(buffer, lvalue, rvalue, format, luau_langkeyword_arith_assignment_add);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::mod_: {
                              luramas::ir::code::emitter::luau::assignment::assignment(buffer, lvalue, rvalue, format, luau_langkeyword_arith_assignment_mod);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::idiv_: {
                              luramas::ir::code::emitter::luau::assignment::assignment(buffer, lvalue, rvalue, format, luau_langkeyword_arith_assignment_idiv);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::sub_: {
                              luramas::ir::code::emitter::luau::assignment::assignment(buffer, lvalue, rvalue, format, luau_langkeyword_arith_assignment_sub);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::div_: {
                              luramas::ir::code::emitter::luau::assignment::assignment(buffer, lvalue, rvalue, format, luau_langkeyword_arith_assignment_div);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::mul_: {
                              luramas::ir::code::emitter::luau::assignment::assignment(buffer, lvalue, rvalue, format, luau_langkeyword_arith_assignment_mul);
                              break;
                        }
                        case luramas::il::arch::data::bin_kinds::pow_: {
                              luramas::ir::code::emitter::luau::assignment::assignment(buffer, lvalue, rvalue, format, luau_langkeyword_arith_assignment_pow);
                              break;
                        }
                        default: {
                              luramas::error::error("Unkown binkind assignment when trying too emit arithmetic assignment.");
                        }
                  }
                  return;
            }

      } // namespace arith

} // namespace luramas::ir::code::emitter::luau::assignment