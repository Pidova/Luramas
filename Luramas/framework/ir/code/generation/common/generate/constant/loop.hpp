#pragma once
#include "../expression/logical.hpp"
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::loop {

      /* Emits do routine */
      inline void emit_do(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::loop::emit_do(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::loop::emit_do(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::loop::emit_do(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Do");
                  }
            }
            return;
      }

      /* Emits repeat routine */
      inline void emit_repeat(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::loop::emit_repeat(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::loop::emit_repeat(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::loop::emit_repeat(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Repeat");
                  }
            }
            return;
      }

      /* Emits loop break */
      inline void emit_loop_break(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::loop::emit_loop_break(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::loop::emit_loop_break(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::loop::emit_loop_break(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Loop break");
                  }
            }
            return;
      }

      /* Emits loop continue */
      inline void emit_loop_continue(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::loop::emit_loop_continue(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::loop::emit_loop_continue(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::loop::emit_loop_continue(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Loop continue");
                  }
            }
            return;
      }

      inline void emit_while(const syntax::emitter_syntax syn, std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::loop::emit_while(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::loop::emit_while(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::loop::emit_while(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Loop while");
                  }
            }
            return;
      }

      /* Emits while routine too reference (pre compiled compare). */
      inline void emit_while_pre(const syntax::emitter_syntax syn, std::string &buffer, std::string &compiled, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::loop::emit_while_pre(buffer, compiled, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::loop::emit_while_pre(buffer, compiled, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::loop::emit_while_pre(buffer, compiled, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Pre-compiled while");
                  }
            }
            return;
      }

      /* Emits until routine */
      inline void emit_until(const syntax::emitter_syntax syn, std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::loop::emit_until(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::loop::emit_until(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::loop::emit_until(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Until");
                  }
            }
            return;
      }

      /* Emits until routine too reference (pre compiled compare). */
      inline void emit_until_pre(const syntax::emitter_syntax syn, std::string &buffer, std::string &compiled, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::loop::emit_until_pre(buffer, compiled, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::loop::emit_until_pre(buffer, compiled, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::loop::emit_until_pre(buffer, compiled, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Pre-compiled until");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::loop