#pragma once
#include "../boostpp/vector.hpp"

namespace cpu_tracer {

      template <std::uint8_t MAX_LEN>
      using inst_bytes = boost::fixed_vector<std::uint8_t, MAX_LEN, std::uint8_t>; /* Instruction bytes */
      using address = std::uintptr_t;                                              /* Address container */

      using flag = bool;                  /* Flag */
      using flag_storage = std::uint32_t; /* Packed flag storage */

} // namespace cpu_tracer