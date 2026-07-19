#pragma once
#include "../emit.hpp"
#include "../expression/logical.hpp"

namespace luramas::ir::code::emitter::lua::branch {

      /* Emits if routine */
      inline void emit_if(std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_compare(lua_langkeyword_scope_if);

            std::string ref("");
            luramas::ir::code::emitter::lua::logical::emit_logical_operation(ref, op, lvalue, rvalue, format);

            buffer += format->spacing.format_parenthesis_ref(lua_langkeyword_parenthesis_open, ref, lua_langkeyword_parenthesis_close);
            buffer += format->spacing.format_scope_begin(lua_langkeyword_scope_if_begin);

            return;
      }

      /* Emits if routine too reference (pre compiled compare). */
      inline void emit_if_pre(std::string &buffer, std::string &compiled, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_compare(lua_langkeyword_scope_if);
            buffer += compiled;
            buffer += format->spacing.format_scope_begin(lua_langkeyword_scope_if_begin);

            return;
      }

      /* Emits else if routine */
      inline void emit_elseif(std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_compare(lua_langkeyword_scope_elseif);

            std::string ref("");
            luramas::ir::code::emitter::lua::logical::emit_logical_operation(ref, op, lvalue, rvalue, format);

            buffer += format->spacing.format_parenthesis_ref(lua_langkeyword_parenthesis_open, ref, lua_langkeyword_parenthesis_close);
            buffer += format->spacing.format_scope_begin(lua_langkeyword_scope_elseif_begin);

            return;
      }

      /* Emits else if routine too reference (pre compiled compare). */
      inline void emit_elseif_pre(std::string &buffer, std::string &compiled, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_compare(lua_langkeyword_scope_elseif);
            buffer += compiled;
            buffer += format->spacing.format_scope_begin(lua_langkeyword_scope_elseif_begin);

            return;
      }

      /* Emits else */
      inline void emit_else(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_compare(lua_langkeyword_scope_else);
            buffer += format->spacing.format_scope_begin(lua_langkeyword_scope_else_begin);

            return;
      }

      /* Emits scope end */
      inline void emit_scope_end(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += lua_langkeyword_scope_end;
            return;
      }

      /* Emits goto label */
      inline void emit_goto_label(std::string &buffer, std::string &name, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_goto(lua_langkeyword_scope_goto);
            buffer += name;
            return;
      }

      /* Label */
      inline void emit_label(std::string &buffer, std::string &name, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += lua_langkeyword_scope_label_begin;
            buffer += name;
            buffer += lua_langkeyword_scope_label_end;
            return;
      }

} // namespace luramas::ir::code::emitter::lua::branch