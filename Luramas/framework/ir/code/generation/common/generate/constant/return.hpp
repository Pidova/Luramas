#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::return_ {

      /* Emits return */
      inline void emit_return(const syntax::emitter_syntax syn, std::string &buffer, std::vector<std::string> &vect, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::return_::emit_return(buffer, vect, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::return_::emit_return(buffer, vect, format);
                        break;
                  }
                  case syntax::emitter_syntax::cpp: {
                        cpp::return_::emit_return(buffer, vect, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Return");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::return_