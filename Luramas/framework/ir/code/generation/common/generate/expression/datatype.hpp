#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::datatype {

      /* Emits arguement */
      inline void emit_arg(const syntax::emitter_syntax syn, std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::datatype::emit_arg(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::datatype::emit_arg(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_arg(buffer, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype arguement");
                  }
            }
            return;
      }

      /* Emits variable */
      inline void emit_var(const syntax::emitter_syntax syn, std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::datatype::emit_var(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::datatype::emit_var(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_var(buffer, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype variable");
                  }
            }
            return;
      }

      /* Emits global */
      inline void emit_global(const syntax::emitter_syntax syn, std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::datatype::emit_global(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::datatype::emit_global(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_global(buffer, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype global");
                  }
            }
            return;
      }

      /* Emits upvalue */
      inline void emit_upvalue(const syntax::emitter_syntax syn, std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::datatype::emit_upvalue(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::datatype::emit_upvalue(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_upvalue(buffer, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype upvalue");
                  }
            }
            return;
      }

      /* Emits string */
      inline void emit_string(const syntax::emitter_syntax syn, std::string &buffer, std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::datatype::emit_string(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::datatype::emit_string(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_string(buffer, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype string");
                  }
            }
            return;
      }

      /* Emits variadic */
      inline void emit_variadic(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::datatype::emit_variadic(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::datatype::emit_variadic(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_variadic(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype variadic");
                  }
            }
            return;
      }

      /* Emits boolean */
      inline void emit_boolean(const syntax::emitter_syntax syn, std::string &buffer, const bool data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::datatype::emit_boolean(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::datatype::emit_boolean(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_boolean(buffer, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype boolean");
                  }
            }
            return;
      }

      /* Emits integer */
      inline void emit_integer(const syntax::emitter_syntax syn, std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::datatype::emit_integer(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::datatype::emit_integer(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_integer(buffer, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype integer");
                  }
            }
            return;
      }

      /* Emits kvalue */
      inline void emit_kval(const syntax::emitter_syntax syn, std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::datatype::emit_kval(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::datatype::emit_kval(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_kval(buffer, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype kvalue");
                  }
            }
            return;
      }

      /* Emits none */
      inline void emit_none(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::datatype::emit_none(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::datatype::emit_none(buffer, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_none(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype none");
                  }
            }
            return;
      }

      /* Emits nothing */
      inline void emit_nothing(const syntax::emitter_syntax syn, std::string &buffer) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::datatype::emit_nothing(buffer);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::datatype::emit_nothing(buffer);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_nothing(buffer);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype nothing");
                  }
            }
            return;
      }

      /* Emits stack */
      inline void emit_stack(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_stack(buffer);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype stack");
                  }
            }
            return;
      }

      /* Emits controller */
      inline void emit_controller(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {
                        cpp::datatype::emit_controller(buffer);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Datatype controller");
                  }
            }
            return;
      }
} // namespace luramas::ir::code::emitter::common::datatype