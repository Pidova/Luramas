#pragma once
#include "optable.hpp"
#include <cstdint>
#include <memory>
#include <string>

namespace luramas::disassembler::CIL {

      struct disassembly {

            optable::data::instructions op;
            const char *mnenomic = "";
            const char *hint = "";
      };

} // namespace luramas::disassembler::CIL