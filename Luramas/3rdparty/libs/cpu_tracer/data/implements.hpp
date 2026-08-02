#pragma once
#include <cstdint>

namespace cpu_tracer {

      /* Type of data saved */
      enum class save_type : std::uint8_t {
            none = 0u,        /* Nothing*/
            block = 1u,       /* Block */
            edge_map = 2u,    /* Edges */
            vcpu_states = 3u, /* VCPU states */
            interrupts = 4u,  /* Interrupt data */
            MMIO = 5u,        /* MMIO data */
            reg_data = 6u     /* Register data */
      };

      /* List of supported architectures, mainly used for groupings */
      namespace archs {

            /* Supported architectures */
            enum class arch : std::uint8_t {
                  none = 0u,   /* No arch */
                  x86 = 1u,    /* X86 */
                  ARM = 2u,    /* ARM */
                  mips = 3u,   /* MIPS */
                  ppc = 4u,    /* PowerPC */
                  sparc = 5u,  /* SPARC */
                  riscv = 6u,  /* RISC-V */
                  m68k = 7u,   /* Motorola 68K */
                  systemz = 8u /* IBM SystemZ */
            };

            /* Supported interpretation mode for architecture (grouped) */
            enum class interpretation_mode : std::uint8_t {

                  none = 0u, /* No mode */

                  /* x86 */
                  x16 = 1u, /* (x86) X16 */
                  x32 = 2u, /* (x86) X32 */
                  x64 = 3u, /* (x86) X64 */

                  /* ARM */
                  arm_thumb = 4u,  /* (ARM) Thumb */
                  arm32 = 5u,      /* (ARM) 32 bit */
                  arm_mclass = 6u, /* (ARM) Cortex-M */
                  arm_v8 = 7u,     /* (ARM) V8 / AArch64 */

                  /* MIPS */
                  mips32 = 8u,      /* (MIPS) 32 bit */
                  mips64 = 9u,      /* (MIPS) 64 bit */
                  mips_micro = 10u, /* (MIPS) microMIPS */
                  mips32r6 = 11u,   /* (MIPS) 32 bit Release 6 */

                  /* PowerPC */
                  ppc32 = 12u, /* (PPC) 32 bit */
                  ppc64 = 13u, /* (PPC) 64 bit */

                  /* SPARC */
                  sparc32 = 14u, /* (SPARC) 32 bit */
                  sparc64 = 15u, /* (SPARC) 64 bit / V9 */

                  /* RISC-V */
                  rv32 = 16u,  /* (RISC-V) 32 bit */
                  rv64 = 17u,  /* (RISC-V) 64 bit */
                  rv32c = 18u, /* (RISC-V) 32 bit Compressed */
                  rv64c = 19u, /* (RISC-V) 64 bit Compressed */

                  /* Motorola 68K */
                  m68000 = 20u, /* (M68K) 68000 */
                  m680x0 = 21u, /* (M68K) 68010 - 68060 */

                  /* SystemZ */
                  s390x = 22u /* (SystemZ) 64 bit */
            };
      } // namespace archs

      namespace check {

            /* Save types */
            static_assert(std::is_same_v<std::underlying_type_t<save_type>, std::uint8_t>, "save_type must use std::uint8_t as its underlying type.");
            static_assert(static_cast<std::uint8_t>(save_type::none) == 0u);
            static_assert(static_cast<std::uint8_t>(save_type::block) == 1u);
            static_assert(static_cast<std::uint8_t>(save_type::edge_map) == 2u);
            static_assert(static_cast<std::uint8_t>(save_type::vcpu_states) == 3u);
            static_assert(static_cast<std::uint8_t>(save_type::interrupts) == 4u);
            static_assert(static_cast<std::uint8_t>(save_type::MMIO) == 5u);
            static_assert(static_cast<std::uint8_t>(save_type::reg_data) == 6u);

            /* Supported architectures */
            static_assert(std::is_same_v<std::underlying_type_t<archs::arch>, std::uint8_t>, "arch must use std::uint8_t as its underlying type.");
            static_assert(static_cast<std::uint8_t>(archs::arch::none) == 0u);
            static_assert(static_cast<std::uint8_t>(archs::arch::x86) == 1u);
            static_assert(static_cast<std::uint8_t>(archs::arch::ARM) == 2u);
            static_assert(static_cast<std::uint8_t>(archs::arch::mips) == 3u);
            static_assert(static_cast<std::uint8_t>(archs::arch::ppc) == 4u);
            static_assert(static_cast<std::uint8_t>(archs::arch::sparc) == 5u);
            static_assert(static_cast<std::uint8_t>(archs::arch::riscv) == 6u);
            static_assert(static_cast<std::uint8_t>(archs::arch::m68k) == 7u);
            static_assert(static_cast<std::uint8_t>(archs::arch::systemz) == 8u);

            /* Supported interpretation modes */
            static_assert(std::is_same_v<std::underlying_type_t<archs::interpretation_mode>, std::uint8_t>, "interpretation_mode must use std::uint8_t as its underlying type.");
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::none) == 0u);

            /* x86 */
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::x16) == 1u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::x32) == 2u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::x64) == 3u);

            /* ARM */
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::arm_thumb) == 4u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::arm32) == 5u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::arm_mclass) == 6u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::arm_v8) == 7u);

            /* MIPS */
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::mips32) == 8u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::mips64) == 9u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::mips_micro) == 10u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::mips32r6) == 11u);

            /* PowerPC */
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::ppc32) == 12u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::ppc64) == 13u);

            /* SPARC */
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::sparc32) == 14u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::sparc64) == 15u);

            /* RISC-V */
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::rv32) == 16u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::rv64) == 17u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::rv32c) == 18u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::rv64c) == 19u);

            /* Motorola 68K */
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::m68000) == 20u);
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::m680x0) == 21u);

            /* SystemZ */
            static_assert(static_cast<std::uint8_t>(archs::interpretation_mode::s390x) == 22u);
      } // namespace check
} // namespace cpu_tracer