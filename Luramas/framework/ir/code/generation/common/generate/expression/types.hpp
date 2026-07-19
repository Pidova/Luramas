#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::types {

      /* Emits cast */
      inline void emit_cast(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::types::object::type> &t, const std::string &value, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {
                        cpp::types::emit_cast(buffer, t, value, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Cast");
                  }
            }
            return;
      }

      /* Emits bitread */
      inline void emit_bitread(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::types::object::type> &t, const std::string &value, const std::string &min, const std::string &max, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {
                        cpp::types::emit_bitread(buffer, t, value, min, max, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Bitread");
                  }
            }
            return;
      }
} // namespace luramas::ir::code::emitter::common::types