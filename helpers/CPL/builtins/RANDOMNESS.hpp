#pragma once
#include "../helpers.hpp"

template <typename T = std::uint64_t>
inline bool LURA_CPU_RDSEED(const T &value) {
#if defined(_MSC_VER)
      if constexpr (sizeof(T) == 2u) {
            return _rdseed16_step(reinterpret_cast<std::uint16_t *>(&value));
      } else if constexpr (sizeof(T) == 4u) {
            return _rdseed32_step(reinterpret_cast<std::uint32_t *>(&value));
      } else if constexpr (sizeof(T) == 8u) {
            return _rdseed64_step(reinterpret_cast<std::uint64_t *>(&value));
      }
#elif defined(__GNUC__) || defined(__clang__)
      if constexpr (sizeof(T) == 2u) {
            return __builtin_ia32_rdseed_hi(reinterpret_cast<std::uint16_t *>(&value));
      } else if constexpr (sizeof(T) == 4u) {
            return __builtin_ia32_rdseed_si(reinterpret_cast<std::uint32_t *>(&value));
      } else if constexpr (sizeof(T) == 8u) {
            return __builtin_ia32_rdseed_di(reinterpret_cast<std::uint64_t *>(&value));
      }
#else
#error "Not supported"
#endif
      return false;
}

template <typename T = std::uint64_t>
inline bool LURA_CPU_RDRAND(const T &value) {
#if defined(_MSC_VER)
      if constexpr (sizeof(T) == 2u) {
            return _rdrand16_step(reinterpret_cast<std::uint16_t *>(&value));
      } else if constexpr (sizeof(T) == 4u) {
            return _rdrand32_step(reinterpret_cast<std::uint32_t *>(&value));
      } else if constexpr (sizeof(T) == 8u) {
            return _rdrand64_step(reinterpret_cast<std::uint64_t *>(&value));
      }
#elif defined(__GNUC__) || defined(__clang__)
      if constexpr (sizeof(T) == 2u) {
            return __builtin_ia32_rdrand_hi(reinterpret_cast<std::uint16_t *>(&value));
      } else if constexpr (sizeof(T) == 4u) {
            return __builtin_ia32_rdrand_si(reinterpret_cast<std::uint32_t *>(&value));
      } else if constexpr (sizeof(T) == 8u) {
            return __builtin_ia32_rdrand_di(reinterpret_cast<std::uint64_t *>(&value));
      }
#else
#error "Not supported"
#endif
      return false;
}