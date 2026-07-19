#pragma once
#include "generate/emit.hpp"
#include <frozen\unordered_set.h>

namespace luramas::ir::code::emitter::luau {

      /* Arith instruction that are supported as assignments. (You can leave it empty if every assignment is supported). */
      constexpr frozen::unordered_set<il::arch::data::bin_kinds, 7u> supported_arith_assignment = {
          il::arch::data::bin_kinds::add_,
          il::arch::data::bin_kinds::sub_,
          il::arch::data::bin_kinds::mod_,
          il::arch::data::bin_kinds::div_,
          il::arch::data::bin_kinds::mul_,
          il::arch::data::bin_kinds::pow_,
          il::arch::data::bin_kinds::idiv_};

} // namespace luramas::ir::code::emitter::luau