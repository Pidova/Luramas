#pragma once
#include "../emit.hpp"
#include "../expression/logical.hpp"

namespace luramas::ir::code::emitter::cpp::loop {

      /* Emits do routine */
      inline void emit_do(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += format->spacing.format_while_scope_start(cpp_langkeyword_loop_do);
            return;
      }

      /* Emits repeat routine */
      inline void emit_repeat(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += cpp_langkeyword_loop_repeat;
            emit_do(buffer, format);
            return;
      }

      /* Emits loop break */
      inline void emit_loop_break(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += cpp_langkeyword_loop_break;
            return;
      }

      /* Emits loop continue */
      inline void emit_loop_continue(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += cpp_langkeyword_loop_continue;
            return;
      }

      inline void emit_while(std::string &buffer, const luramas::il::arch::data::bin_kinds op, const std::string &lvalue, const std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_compare(cpp_langkeyword_loop_while);

            std::string ref("");
            luramas::ir::code::emitter::cpp::logical::emit_logical_operation(ref, op, lvalue, rvalue, format);

            buffer += format->spacing.format_parenthesis_ref(cpp_langkeyword_parenthesis_open, ref, cpp_langkeyword_parenthesis_close);
            luramas::ir::code::emitter::cpp::loop::emit_do(buffer, format);
            return;
      }

      /* Emits while routine too reference (pre compiled compare). */
      inline void emit_while_pre(std::string &buffer, const std::string &compiled, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_while(cpp_langkeyword_loop_while);
            buffer += compiled;

            luramas::ir::code::emitter::cpp::loop::emit_do(buffer, format);
            return;
      }

      /* Emits until routine */
      inline void emit_until(std::string &buffer, const luramas::il::arch::data::bin_kinds op, const std::string &lvalue, const std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_until(cpp_langkeyword_loop_until);

            std::string ref("");
            luramas::ir::code::emitter::cpp::logical::emit_logical_operation(ref, op, lvalue, rvalue, format);
            buffer += format->spacing.format_parenthesis_ref(cpp_langkeyword_parenthesis_open, ref, cpp_langkeyword_parenthesis_close);
            return;
      }

      /* Emits until routine too reference (pre compiled compare). */
      inline void emit_until_pre(std::string &buffer, const std::string &compiled, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_until(cpp_langkeyword_loop_until);
            buffer += compiled;
            return;
      }

} // namespace luramas::ir::code::emitter::cpp::loop