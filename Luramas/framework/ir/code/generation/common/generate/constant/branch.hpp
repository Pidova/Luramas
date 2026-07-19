#pragma once
#include "../expression/logical.hpp"
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::branch {

      /* Emits if routine */
      inline void emit_if(const emitter::syntax::emitter_syntax syn, std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::branch::emit_if(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::branch::emit_if(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::branch::emit_if(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  default: {
                        luramas::error::error("Brach if statement emissions are not supported by current target syntax.");
                  }
            }
            return;
      }

      /* Emits if routine too reference (pre compiled compare). */
      inline void emit_if_pre(const syntax::emitter_syntax syn, std::string &buffer, std::string &compiled, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::branch::emit_if_pre(buffer, compiled, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::branch::emit_if_pre(buffer, compiled, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::branch::emit_if_pre(buffer, compiled, format);
                        break;
                  }
                  default: {
                        luramas::error::error("Branch if pre statement emissions are not supported by current target syntax.");
                  }
            }
            return;
      }

      /* Emits else if routine */
      inline void emit_elseif(const syntax::emitter_syntax syn, std::string &buffer, const luramas::il::arch::data::bin_kinds op, std::string &lvalue, std::string &rvalue, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::branch::emit_elseif(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::branch::emit_elseif(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::branch::emit_elseif(buffer, op, lvalue, rvalue, format);
                        break;
                  }
                  default: {
                        luramas::error::error("Branch elseif statement emissions are not supported by current target syntax.");
                  }
            }
            return;
      }

      /* Emits else if routine too reference (pre compiled compare). */
      inline void emit_elseif_pre(const syntax::emitter_syntax syn, std::string &buffer, std::string &compiled, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::branch::emit_elseif_pre(buffer, compiled, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::branch::emit_elseif_pre(buffer, compiled, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::branch::emit_elseif_pre(buffer, compiled, format);
                        break;
                  }
                  default: {
                        luramas::error::error("Branch elseif pre statement emissions are not supported by current target syntax.");
                  }
            }
            return;
      }

      /* Emits else */
      inline void emit_else(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::branch::emit_else(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::branch::emit_else(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::branch::emit_else(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error("Branch else statement emissions are not supported by current target syntax.");
                  }
            }
            return;
      }

      /* Emits scope end */
      inline void emit_scope_end(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::branch::emit_scope_end(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::branch::emit_scope_end(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::branch::emit_scope_end(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error("Branch scope end statement emissions are not supported by current target syntax.");
                  }
            }
            return;
      }

      /* Emits goto label */
      inline void emit_goto_label(const syntax::emitter_syntax syn, std::string &buffer, std::string &name, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::branch::emit_goto_label(buffer, name, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::branch::emit_goto_label(buffer, name, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::branch::emit_goto_label(buffer, name, format);
                        break;
                  }
                  default: {
                        luramas::error::error("Goto labels emissions are not supported by current target syntax.");
                  }
            }
            return;
      }

      /* Emits label */
      inline void emit_label(const syntax::emitter_syntax syn, std::string &buffer, std::string &name, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::branch::emit_label(buffer, name, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::branch::emit_label(buffer, name, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::branch::emit_label(buffer, name, format);
                        break;
                  }
                  default: {
                        luramas::error::error("Label emissions are not supported by current target syntax.");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::branch