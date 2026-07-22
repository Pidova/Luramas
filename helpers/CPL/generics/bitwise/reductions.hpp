#pragma once
#include <cstdint>

namespace cpl::bitwise::parity {

      inline constexpr auto popcount(auto x) {
            auto res = 0ull;
            while (x) {
                  res += x & 1;
                  x >>= 1;
            }
            return res;
      }
} // namespace cpl::bitwise::parity