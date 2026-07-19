#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::lua::unary {

      /* Emits unary too reference string. */
      inline void emit_unary(std::string &buffer, const luramas::il::arch::data::bin_kinds unary, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (unary) {
                  case luramas::il::arch::data::bin_kinds::not_: {
                        buffer = format->spacing.format_unary_not(lua_langkeyword_not) + buffer;
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::len_: {
                        buffer = format->spacing.format_unary_length(lua_langkeyword_lenght) + buffer;
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::minus_: {
                        buffer = format->spacing.format_unary_minus(lua_langkeyword_minus) + buffer;
                        break;
                  }
                  case luramas::il::arch::data::bin_kinds::bitnot_: {
                        buffer = format->spacing.format_unary_bitnot(lua_langkeyword_bitnot) + buffer;
                        break;
                  }
                  default: {
                        luramas::error::error("Unkown unary for unary IR emitter.");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::lua::unary