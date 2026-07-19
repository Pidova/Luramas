#pragma once
#include "generate.hpp"
#include <array>

namespace luramas::ir::code::emitter::common {

      inline bool supported_arith_assignment(const syntax::emitter_syntax syn, const il::arch::data::bin_kinds kind) {

            switch (syn) {

                  case syntax::emitter_syntax::lua: {
                        return lua::supported_arith_assignment.find(kind) != lua::supported_arith_assignment.end();
                  }
                  case syntax::emitter_syntax::luau: {
                        return luau::supported_arith_assignment.find(kind) != luau::supported_arith_assignment.end();
                  }
                  case syntax::emitter_syntax::cpp: {
                        return cpp::supported_arith_assignment.find(kind) != luau::supported_arith_assignment.end();
                  }
                  default: {
                        break;
                  }
            }
            return false;
      }

} // namespace luramas::ir::code::emitter::common