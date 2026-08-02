#ifdef LURAMAS_TARGET_X86
#include "x86-64.hpp"
#include "../../../il/architecture/emitter.hpp"
#include "../../../il/transformers/transformers.hpp"
#include "parser/parser.hpp"
#include <iostream>

namespace luramas::il::X86::lifter {

      void lift(std::shared_ptr<ilang> &buffer, const std::vector<vinst_cs> &insts, const hardware_constants &hw_constants, const profile::externals::data<x86_reg> &externals, const profile::details &details) {

            helpers::low::disassembly_manager<MAX_LEN, cs_insn> dm(insts, buffer, details, x86_reg::X86_REG_ENDING + 1u, true);

            /* Parse instructions. */
            parser::parse_instruction(dm, externals, hw_constants);
            transformers::kinds(buffer);
            return;
      }
} // namespace luramas::il::X86::lifter

#endif