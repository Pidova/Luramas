#pragma once
#include "optable.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace luramas::disassembler::JVM {

      struct operand {
      };
      struct disassembly {

            optable::data::instructions op;
            const char *mnenomic = "";
            const char *hint = "";
            std::vector<operand> operands;
      };

} // namespace luramas::disassembler::JVM