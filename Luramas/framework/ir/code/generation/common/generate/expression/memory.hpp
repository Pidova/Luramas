#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::memory {

      /* Emits memread */
      inline void emit_memread(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::types::object::type> &t, const std::string &value, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {
                        cpp::memory::emit_memread(buffer, t, value, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Memread");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::memory