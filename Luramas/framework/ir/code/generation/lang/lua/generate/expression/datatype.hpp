#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::lua::datatype {

      /* Emits arguement */
      inline void emit_arg(std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += data;
            return;
      }

      /* Emits variable */
      inline void emit_var(std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += data;
            return;
      }

      /* Emits global */
      inline void emit_global(std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += data;
            return;
      }

      /* Emits upvalue */
      inline void emit_upvalue(std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += data;
            return;
      }

      /* Emits string */
      inline void emit_string(std::string &buffer, std::string data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            /* Fix string */
            if (data.back() != lua_langkeyword_string_end) {
                  data += lua_langkeyword_string_end;
            }
            if (data.front() != lua_langkeyword_string_start) {
                  data = lua_langkeyword_string_start + data;
            }

            buffer += data;
            return;
      }

      /* Emits variadic */
      inline void emit_variadic(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += lua_langkeyword_variadic;
            return;
      }

      /* Emits boolean */
      inline void emit_boolean(std::string &buffer, const bool data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += (data) ? lua_langkeyword_true : lua_langkeyword_false;
            return;
      }

      /* Emits integer */
      inline void emit_integer(std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += data;
            return;
      }

      /* Emits kvalue */
      inline void emit_kval(std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += data;
            return;
      }

      /* Emits none */
      inline void emit_none(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += lua_langkeyword_nil;
            return;
      }

      /* Emits nothing */
      inline void emit_nothing(std::string &buffer) {
            buffer += lua_langkeyword_nothing;
            return;
      }

} // namespace luramas::ir::code::emitter::lua::datatype