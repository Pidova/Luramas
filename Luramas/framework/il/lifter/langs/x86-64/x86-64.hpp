#pragma once
#ifdef LURAMAS_TARGET_X86

#include "../../../il/il.hpp"
#include <capstone/capstone.h>

namespace luramas::il::X86::lifter {

      enum class bit_mode : std::uint8_t {
            x32 = 32u,
            x64 = 64u
      };

     struct hardware_constants {
            std::uint8_t suggested_bit_set = 0u;
            std::uint16_t MAXVL = 0u;
      };

      /* Lifts x86 disassembly to IL disassembly. */
      void lift(const std::vector<std::pair<luramas::il::vinst, cs_insn>> &insts, const hardware_constants& hw_constants, std::shared_ptr<luramas::il::ilang> &buffer, const boost::unordered_flat_map<profile::module_id, profile::analyze::details> &details, const profile::externals::data<x86_reg> &external);

} // namespace luramas::il::X86::lifter

#endif