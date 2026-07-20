#pragma once
#ifdef LURAMAS_TARGET_X86
#include "../x86-64.hpp"

/* Maps everything to their relative translation. (Does not add or remove any instructions not relative to the translation) */
namespace parser {

      /* Parses instructions. */
      void parse_instruction(const luramas::il::helpers::low::disassembly_manager<cs_insn> &dism, const luramas::il::X86::lifter::hardware_constants &hw_constants, const luramas::profile::externals::data<x86_reg> &external);

} // namespace parser

#endif