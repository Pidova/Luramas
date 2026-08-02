#pragma once
#ifdef LURAMAS_TARGET_X86
#include <capstone/capstone.h>
#include <cstdint>

namespace luramas::il::X86::lifter {

      static constexpr auto MAX_LEN = 15u; /* Maximum X86 instruction length */

      using vinst_cs = std::pair<luramas::il::vinst<MAX_LEN>, cs_insn>; /* {Virtual instruction , disassembly} pair */
} // namespace luramas::il::X86::lifter
#endif