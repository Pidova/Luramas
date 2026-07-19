#pragma once
#include "../generate.hpp"
#include "../supported.hpp"
#include <vector>

namespace luramas::ir::code::emitter::common::function::virtual_functions {

      inline void emit_virtual_function(const syntax::emitter_syntax syn, const luramas::il::arch::virtual_functions vt, const std::vector<std::string> &args) {

            switch (syn) {
                  case syntax::emitter_syntax::python: {
                        break;
                  }
                  default: {
                        luramas::error::error_stat_syn_emit("Virtual function");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::function::virtual_functions