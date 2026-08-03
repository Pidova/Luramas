#pragma once
#include "../ir.hpp"

namespace luramas::ir::fuzzer {

      /* Lower a libprotobuf-mutator provided program into IR space */
      ir_stat::space generate(std::uint64_t seed);
} // namespace luramas::ir::fuzzer
