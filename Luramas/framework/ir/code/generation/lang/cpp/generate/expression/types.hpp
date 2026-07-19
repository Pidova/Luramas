#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::cpp::types {

      /* Emits signature type list */
      inline void emit_signature_list(std::string &buffer, const std::vector<luramas::ir::types::signature> &types, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            if (types.empty()) {
                  buffer += cpp_langkeyword_types_no_return;
            } else {
            }
            return;
      }

      /* Emits type */
      inline void emit_type(std::string &buffer, const std::shared_ptr<luramas::ir::types::object::type> &t, const std::shared_ptr<luramas::ir::data::format::format> &format, const luramas_flag fconstant = false) {

            buffer += (fconstant ? "const std::" : "std::") + t->str() + " ";
            return;
      }

      /* Emits cast */
      inline void emit_cast(std::string &buffer, const std::shared_ptr<luramas::ir::types::object::type> &t, const std::string &value, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += cpp_langkeyword_cast_pre + t->str() + cpp_langkeyword_parenthesis_open + value + (cpp_langkeyword_parenthesis_close cpp_langkeyword_cast_post);
            return;
      }

      /* Emits bitread */
      inline void emit_bitread(std::string &buffer, const std::shared_ptr<luramas::ir::types::object::type> &t, const std::string &value, const std::string &min, const std::string &max, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += (cpp_langkeyword_bitread_pre cpp_langkeyword_bitread_Tpre) + t->str() + (cpp_langkeyword_bitread_Tpost cpp_langkeyword_bitread_v_pre) + value + (cpp_langkeyword_bitread_v_post cpp_langkeyword_bitread_min_pre) + min + (cpp_langkeyword_bitread_min_post cpp_langkeyword_bitread_max_pre) + max + cpp_langkeyword_bitread_max_post;
            return;
      }
} // namespace luramas::ir::code::emitter::cpp::types