#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::logical {

      inline void emit_operator(const syntax::emitter_syntax syn, std::string &buffer, const luramas::il::arch::data::bin_kinds op, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::logical::emit_operator(buffer, op, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::logical::emit_operator(buffer, op, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::logical::emit_operator(buffer, op, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Logical operator");
                  }
            }
            return;
      }

      /* Emits logical operation */
      inline void emit_logical_operation(const syntax::emitter_syntax syn, std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::logical::emit_logical_operation(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::logical::emit_logical_operation(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::logical::emit_logical_operation(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Logical operation");
                  }
            }
            return;
      }

      /* Emits logical compare e.g. (?? ?? ??) */
      inline void emit_logical_compare(const syntax::emitter_syntax syn, std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format, const bool open = true, const bool close = true) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::logical::emit_logical_compare(buffer, op, lvalue, rvalue, format, open, close);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::logical::emit_logical_compare(buffer, op, lvalue, rvalue, format, open, close);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::logical::emit_logical_compare(buffer, op, lvalue, rvalue, format, open, close);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Logical compare");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::logical