#pragma once
#include "../architecture/architecture.hpp"
#include <iostream>

namespace luramas::il::disassembler {

      /* Returns mnemonic string for IL opcode. */
      const char *const mnemonic_string(const luramas::il::arch::opcodes op);

      /* Returns mnemonic hint string for IL opcode. */
      const char *const mnemonic_hint_string(const luramas::il::arch::opcodes op);

      /* Returns operand string for IL operand. */
      std::string operand_string(const std::shared_ptr<luramas::il::arch::operand::operand> &operand);

} // namespace luramas::il::disassembler
