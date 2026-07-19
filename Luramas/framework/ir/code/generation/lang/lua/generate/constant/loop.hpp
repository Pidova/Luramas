#pragma once
#include "../emit.hpp"
#include "../expression/logical.hpp"

namespace luramas::ir::code::emitter::lua::loop {

      /* Emits do routine */
      inline void emit_do(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += format->spacing.format_while_scope_start(lua_langkeyword_loop_do);
            buffer += lua_langkeyword_loop_do_begin;
            return;
      }

      /* Emits repeat routine */
      inline void emit_repeat(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += lua_langkeyword_loop_repeat;
            buffer += lua_langkeyword_loop_repeat_begin;
            return;
      }

      /* Emits loop break */
      inline void emit_loop_break(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += lua_langkeyword_loop_break;
            return;
      }

      /* Emits loop continue */
      inline void emit_loop_continue(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += lua_langkeyword_loop_continue;
            return;
      }

      inline void emit_while(std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_compare(lua_langkeyword_loop_while);

            std::string ref("");
            luramas::ir::code::emitter::lua::logical::emit_logical_operation(ref, op, lvalue, rvalue, format);

            buffer += format->spacing.format_parenthesis_ref(lua_langkeyword_parenthesis_open, ref, lua_langkeyword_parenthesis_close);
            buffer += format->spacing.format_scope_begin(lua_langkeyword_loop_while_begin);
            return;
      }

      /* Emits while routine too reference (pre compiled compare). */
      inline void emit_while_pre(std::string &buffer, std::string &compiled, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_while(lua_langkeyword_loop_while);
            buffer += compiled;

            luramas::ir::code::emitter::lua::loop::emit_do(buffer, format);

            buffer += format->spacing.format_scope_begin(lua_langkeyword_loop_while_begin);
            return;
      }

      /* Emits until routine */
      inline void emit_until(std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_until(lua_langkeyword_loop_until);

            std::string ref("");
            luramas::ir::code::emitter::lua::logical::emit_logical_operation(ref, op, lvalue, rvalue, format);
            buffer += format->spacing.format_parenthesis_ref(lua_langkeyword_parenthesis_open, ref, lua_langkeyword_parenthesis_close);
            return;
      }

      /* Emits until routine too reference (pre compiled compare). */
      inline void emit_until_pre(std::string &buffer, std::string &compiled, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += format->spacing.format_until(lua_langkeyword_loop_until);
            buffer += compiled;
            return;
      }

} // namespace luramas::ir::code::emitter::lua::loop