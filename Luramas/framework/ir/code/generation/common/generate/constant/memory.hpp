#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::memory {

      /* Emits memwrite */
      inline void emit_memwrite(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::types::object::type> &t, const std::string &l, const std::string &r, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::cpp: {
                        cpp::memory::emit_memwrite(buffer, t, l, r, format);
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Memwrite");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::memory