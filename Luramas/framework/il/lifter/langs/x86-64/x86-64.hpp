#pragma once
#ifdef LURAMAS_TARGET_X86

#include "../../../il/il.hpp"
#include "defs.hpp"

namespace luramas::il::X86::lifter {

      /* Hardware constants CPU use */
      struct hardware_constants {
            std::uint8_t instruction_interp = 0u; /* Abstract interpretation mode */
            std::uint16_t MAXVL = 0u;             /* Max vector length */
      };

      /* Lifts x86 disassembly to IL disassembly */
      void lift(std::shared_ptr<ilang> &buffer, const std::vector<vinst_cs> &insts, const hardware_constants &hw_constants, const profile::externals::data<x86_reg> &externals, const profile::details &details);

} // namespace luramas::il::X86::lifter

#endif