#pragma once
#include <cstdint>
#include <string>

/* Ref  */
namespace luramas::disassembler::PY::optable {

      namespace data {

            enum class instructions : std::uint8_t {

                  OP_AMT /* Amount. */
            };
      }

      struct opcode {
            data::instructions inst;
            std::uint32_t op = 0u;
      };
} // namespace luramas::disassembler::PY::optable