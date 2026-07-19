#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::flags {

      /* Emits flag */
      inline void emit_flag(const syntax::emitter_syntax syn, std::string &buffer, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {
                        cpp::flags::emit_flag(buffer, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Flags");
                  }
            }
            return;
      }
} // namespace luramas::ir::code::emitter::common::flags