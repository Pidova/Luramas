#pragma once
#include "../helpers.hpp"

/* Port input */
template <typename T1, typename T2, typename T3>
inline constexpr void LURA_IO_INPUT(const T1 value, const T2 module, const T3 port) {

      if constexpr (sizeof(T1) == 1u) {
            _outp(port, value);
      } else if constexpr (sizeof(T1) == 2u) {
            _outpw(port, value);
      } else if constexpr (sizeof(T1) == 4u) {
            _outpd(port, value);
      }
      return;
}

/* Port output */
template <typename R, typename T1, typename T2>
inline constexpr R LURA_IO_OUTPUT(const T1 module, const T2 port) {

      if constexpr (sizeof(R) == 1u) {
            return static_cast<R>(_inp(port));
      } else if constexpr (sizeof(R) == 2u) {
            return static_cast<R>(_inpw(port));
      } else if constexpr (sizeof(R) == 4u) {
            return static_cast<R>(_inpd(port));
      }
      return R(0u);
}