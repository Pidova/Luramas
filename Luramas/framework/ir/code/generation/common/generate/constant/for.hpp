#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::for_ {

      /* Emits return */
      template <bool numeric = false /* Numeric(true) or Generic(false) */>
      inline void emit_for(const syntax::emitter_syntax syn, std::string &buffer, std::vector<std::string> &vars, std::vector<std::string> &iterator, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::for_::emit_for<numeric>(buffer, vars, iterator, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::for_::emit_for<numeric>(buffer, vars, iterator, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("For");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::for_