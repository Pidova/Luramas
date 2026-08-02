#pragma once
#ifdef LURAMAS_TARGET_X86
#include "../x86-64.hpp"

/* Maps everything to their relative translation. (Does not add or remove any instructions not relative to the translation) */
namespace parser {

      /* Parses instructions */
      void parse_instruction(const luramas::il::helpers::low::disassembly_manager<luramas::il::X86::lifter::MAX_LEN, cs_insn> &dism, const luramas::profile::externals::data<x86_reg> &externals, const luramas::il::X86::lifter::hardware_constants &hw_constants);

} // namespace parser

#endif