#pragma once
#ifdef LURAMAS_TARGET_X86

#include "../../../../builder/builder.hpp"
#include "../parser.hpp"
#include "flags.hpp"
#include <frozen/unordered_map.h>

/* 
Version: 3.6.9
Intel C/C++ Compiler Intrinsic Equivalents
https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html 

(Script for generating table in scripts folder)
*/
namespace simd {

      using arg = luramas::il::lifter::builder::builtin::arg;
      using builtin = luramas::il::lifter::builder::builtin::inst;
      using func = luramas::il::lifter::builder::builtin::func;
      using object = luramas::types::native::compiler::object;

      /* Get built-in intrinsic based off instruction */
      builtin get(const x86_insn inst);

} // namespace simd

#endif