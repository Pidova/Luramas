#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::assignment {

      /* Emits dynamic initial assignment */
      inline void initial_assignment(const syntax::emitter_syntax syn, std::string &buffer, const std::vector<std::string> &lvalue, const std::vector<std::string> &rvalue, const luramas_flag fconstant, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::assignment::initial_assignment(buffer, lvalue, rvalue, fconstant, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::assignment::initial_assignment(buffer, lvalue, rvalue, fconstant, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::assignment::initial_assignment(buffer, lvalue, rvalue, fconstant, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Initial dynamic assignment");
                  }
            }
            return;
      }

      /* Emits dynamic assignment */
      inline void assignment(const syntax::emitter_syntax syn, std::string &buffer, const std::vector<std::string> &lvalue, const std::vector<std::string> &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format, const char *const assignment = NULL /* Default syntax specific. */) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {

                        if (assignment) {
                              lua::assignment::assignment(buffer, lvalue, rvalue, format, assignment);
                        } else {
                              lua::assignment::assignment(buffer, lvalue, rvalue, format);
                        }
                        break;
                  }
                  case syntax::emitter_syntax::luau: {

                        if (assignment) {
                              luau::assignment::assignment(buffer, lvalue, rvalue, format, assignment);
                        } else {
                              luau::assignment::assignment(buffer, lvalue, rvalue, format);
                        }
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {

                        if (assignment) {
                              cpp::assignment::assignment(buffer, lvalue, rvalue, format, assignment);
                        } else {
                              cpp::assignment::assignment(buffer, lvalue, rvalue, format);
                        }
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Assignment");
                  }
            }
            return;
      }

      namespace arith {

            /* Emits arith assignment */
            inline void emit_arith_assignment(const syntax::emitter_syntax syn, std::string &buffer, const luramas::il::arch::data::bin_kinds op, const std::vector<std::string> &lvalue, const std::vector<std::string> &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

                  switch (syn) {
                        case syntax::emitter_syntax::luau: {
                              luau::assignment::arith::emit_arith_assignment(buffer, op, lvalue, rvalue, format);
                              break;
                        }
                        case syntax::emitter_syntax::cpp: {
                              cpp::assignment::arith::emit_arith_assignment(buffer, op, lvalue, rvalue, format);
                              break;
                        }
                        default: {
                              luramas::error::error_stat_syn_emit("Arithmetic assignment");
                        }
                  }
                  return;
            }

      } // namespace arith

} // namespace luramas::ir::code::emitter::common::assignment