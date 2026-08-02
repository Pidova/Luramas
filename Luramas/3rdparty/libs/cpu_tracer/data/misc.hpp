#pragma once
#include "implements.hpp"
#include <array>

namespace cpu_tracer::arch {

      /* Interpretation mode to architecture enum */
      inline constexpr archs::arch interp_mode_to_arch(const archs::interpretation_mode im) {
            switch (im) {
                  /* x86 */
                  case archs::interpretation_mode::x16:
                  case archs::interpretation_mode::x32:
                  case archs::interpretation_mode::x64: {
                        return archs::arch::x86;
                  }
                  /* ARM */
                  case archs::interpretation_mode::arm_thumb:
                  case archs::interpretation_mode::arm32:
                  case archs::interpretation_mode::arm_mclass:
                  case archs::interpretation_mode::arm_v8: {
                        return archs::arch::ARM;
                  }
                  /* MIPS */
                  case archs::interpretation_mode::mips32:
                  case archs::interpretation_mode::mips64:
                  case archs::interpretation_mode::mips_micro:
                  case archs::interpretation_mode::mips32r6: {
                        return archs::arch::mips;
                  }
                  /* PowerPC */
                  case archs::interpretation_mode::ppc32:
                  case archs::interpretation_mode::ppc64: {
                        return archs::arch::ppc;
                  }
                  /* SPARC */
                  case archs::interpretation_mode::sparc32:
                  case archs::interpretation_mode::sparc64: {
                        return archs::arch::sparc;
                  }
                  /* RISC-V */
                  case archs::interpretation_mode::rv32:
                  case archs::interpretation_mode::rv64:
                  case archs::interpretation_mode::rv32c:
                  case archs::interpretation_mode::rv64c: {
                        return archs::arch::riscv;
                  }
                  /* Motorola 68K */
                  case archs::interpretation_mode::m68000:
                  case archs::interpretation_mode::m680x0: {
                        return archs::arch::m68k;
                  }
                  /* SystemZ */
                  case archs::interpretation_mode::s390x: {
                        return archs::arch::systemz;
                  }
                  default: {
                        return archs::arch::none;
                  }
            }
      }

      namespace str {

            namespace data {

                  constexpr std::array<const char *const, 6u> save_types = {
                      "none",
                      "block",
                      "edge_map",
                      "vcpu_states",
                      "interrupts",
                      "MMIO"};
            } // namespace data

            /* To string save type */
            constexpr inline const char *const to_string(const save_type &type) noexcept {
                  if (const auto index = static_cast<std::size_t>(type); index < data::save_types.size()) {
                        return data::save_types[index];
                  }
                  return "unknown";
            }
      } // namespace str

} // namespace cpu_tracer::arch