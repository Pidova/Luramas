#pragma once
#include "../ir.hpp"

namespace luramas::ir::fuzzer {

      /* Fuzz random IR space with seed */
      ir_stat::space generate(std::uint64_t seed);
} // namespace luramas::ir::fuzzer