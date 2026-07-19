#pragma once
#include <frozen\unordered_set.h>

#include "generate/emit.hpp"

namespace luramas::ir::code::emitter::lua {

      /* Arith instruction that are supported as assignments. (You can leave it empty if every assignment is supported). */
      constexpr frozen::unordered_set<il::arch::data::bin_kinds, 1u> supported_arith_assignment = {
          il::arch::data::bin_kinds::nothing};

} // namespace luramas::ir::code::emitter::lua