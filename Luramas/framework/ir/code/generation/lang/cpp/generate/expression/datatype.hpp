#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::cpp::datatype {

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
            if (data.back() != cpp_langkeyword_string_end) {
                  data += cpp_langkeyword_string_end;
            }
            if (data.front() != cpp_langkeyword_string_start) {
                  data = cpp_langkeyword_string_start + data;
            }
            buffer += data;
            return;
      }

      /* Emits variadic */
      inline void emit_variadic(std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += cpp_langkeyword_variadic;
            return;
      }

      /* Emits boolean */
      inline void emit_boolean(std::string &buffer, const bool data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += (data) ? cpp_langkeyword_true : cpp_langkeyword_false;
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
            buffer += cpp_langkeyword_nil;
            return;
      }

      /* Emits nothing */
      inline void emit_nothing(std::string &buffer) {
            buffer += cpp_langkeyword_nothing;
            return;
      }

      /* Emits stack */
      inline void emit_stack(std::string &buffer) {
            buffer += cpp_langkeyword_stack;
            return;
      }

      /* Emits controller */
      inline void emit_controller(std::string &buffer) {
            buffer += cpp_langkeyword_controller;
            return;
      }

} // namespace luramas::ir::code::emitter::cpp::datatype