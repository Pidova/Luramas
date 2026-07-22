#pragma once
#include <cstdint>

namespace cpl::bitwise::parity {

      /* Absolute value */
      inline constexpr auto abs(const auto a, const auto b) {
            return (a > b) ? (a - b) : (b - a);
      }

} // namespace cpl::bitwise::parity