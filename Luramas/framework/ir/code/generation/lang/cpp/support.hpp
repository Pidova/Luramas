#pragma once
#include "generate/emit.hpp"
#include <frozen\unordered_set.h>

namespace luramas::ir::code::emitter::cpp {

      /* Arith instruction that are supported as assignments. (You can leave it empty if every assignment is supported). */
      constexpr frozen::unordered_set<il::arch::data::bin_kinds, 10u> supported_arith_assignment = {
          il::arch::data::bin_kinds::add_,
          il::arch::data::bin_kinds::sub_,
          il::arch::data::bin_kinds::mul_,
          il::arch::data::bin_kinds::div_,
          il::arch::data::bin_kinds::mod_,
          il::arch::data::bin_kinds::xor_,
          il::arch::data::bin_kinds::or_,
          il::arch::data::bin_kinds::and_,
          il::arch::data::bin_kinds::shr_,
          il::arch::data::bin_kinds::shl_};

} // namespace luramas::ir::code::emitter::cpp