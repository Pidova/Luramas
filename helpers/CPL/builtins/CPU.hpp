#pragma once
#include "../helpers.hpp"

/* Get timestamp counter */
template <typename R = std::uintptr_t>
inline constexpr R LURA_CPU_GET_TIMESTAMP_COUNTER() {
      return static_cast<R>(__rdtsc());
}

/* CPU Info */
template <typename T1, typename T2>
inline constexpr std::array<std::uintptr_t, 4u> LURA_CPU_INFO(const T1 leaf, const T2 subleaf) {

      std::array<std::uintptr_t, 4u> regs;

#if defined(_MSC_VER)

      std::int32_t cpu_info[4u];
      __cpuidex(cpu_info, static_cast<std::int32_t>(leaf), static_cast<std::int32_t>(subleaf));
      regs[0u] = static_cast<std::uintptr_t>(cpu_info[0u]);
      regs[1u] = static_cast<std::uintptr_t>(cpu_info[1u]);
      regs[2u] = static_cast<std::uintptr_t>(cpu_info[2u]);
      regs[3u] = static_cast<std::uintptr_t>(cpu_info[3u]);
#elif defined(__GNUC__) || defined(__clang__)

      std::uint32_t a, b, c, d;
      __cpuid_count(static_cast<std::uint32_t>(leaf), static_cast<std::uint32_t>(subleaf), a, b, c, d);
      regs[0u] = static_cast<std::uintptr_t>(a);
      regs[1u] = static_cast<std::uintptr_t>(b);
      regs[2u] = static_cast<std::uintptr_t>(c);
      regs[3u] = static_cast<std::uintptr_t>(d);
#else
#error "CPUID not supported"
#endif
      return regs;
}