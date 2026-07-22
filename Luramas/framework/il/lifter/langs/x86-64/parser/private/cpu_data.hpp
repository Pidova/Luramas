#pragma once
#ifdef LURAMAS_TARGET_X86

#include "simd.hpp"
#include "tools.hpp"
#include "vm.hpp"

namespace internal {

      namespace globals {

            /* Registers */
            static constexpr auto XCR = "XCR";
            static constexpr auto MXCSR = "MXCSR";
            static constexpr auto TASK_REGISTER = "TASK_REGISTER";
            static constexpr auto x87FPUTagWord = "x87FPUTagWord";
            static constexpr auto MSR = "MSR";
      } // namespace globals

      namespace data {

            /* Visibility of internal tables */
            enum class table_hierarchy : std::uint8_t {
                  global, /* Global table */
                  local,  /* Lobal table */
            };

            /* Types of errors an instruction can throw */
            enum class error_kind : std::uint8_t {
                  none,            /* No error */
                  undefined_opcode /* Unknown OP */
            };
      } // namespace data
} // namespace internal

/* 8-bits */
#define REG_AH registrar.getr<x86_reg::X86_REG_AH>()
#define REG_AL registrar.getr<x86_reg::X86_REG_AL>()
#define REG_AX registrar.getr<x86_reg::X86_REG_AX>()
#define REG_BH registrar.getr<x86_reg::X86_REG_BH>()
#define REG_BL registrar.getr<x86_reg::X86_REG_BL>()
#define REG_BP registrar.getr<x86_reg::X86_REG_BP>()
#define REG_BX registrar.getr<x86_reg::X86_REG_BX>()
#define REG_CH registrar.getr<x86_reg::X86_REG_CH>()
#define REG_R8B registrar.getr<x86_reg::X86_REG_R8B>()
#define REG_R9B registrar.getr<x86_reg::X86_REG_R9B>()
#define REG_R10B registrar.getr<x86_reg::X86_REG_R10B>()
#define REG_R11B registrar.getr<x86_reg::X86_REG_R11B>()
#define REG_R12B registrar.getr<x86_reg::X86_REG_R12B>()
#define REG_R13B registrar.getr<x86_reg::X86_REG_R13B>()
#define REG_R14B registrar.getr<x86_reg::X86_REG_R14B>()
#define REG_R15B registrar.getr<x86_reg::X86_REG_R15B>()

/* 16-bits */
#define REG_SI registrar.getr<x86_reg::X86_REG_SI>()
#define REG_CL registrar.getr<x86_reg::X86_REG_CL>()
#define REG_CX registrar.getr<x86_reg::X86_REG_CX>()
#define REG_DH registrar.getr<x86_reg::X86_REG_DH>()
#define REG_DI registrar.getr<x86_reg::X86_REG_DI>()
#define REG_DL registrar.getr<x86_reg::X86_REG_DL>()
#define REG_DX registrar.getr<x86_reg::X86_REG_DX>()
#define REG_SP registrar.getr<x86_reg::X86_REG_SP>()
#define REG_R8W registrar.getr<x86_reg::X86_REG_R8W>()
#define REG_R9W registrar.getr<x86_reg::X86_REG_R9W>()
#define REG_R10W registrar.getr<x86_reg::X86_REG_R10W>()
#define REG_R11W registrar.getr<x86_reg::X86_REG_R11W>()
#define REG_R12W registrar.getr<x86_reg::X86_REG_R12W>()
#define REG_R13W registrar.getr<x86_reg::X86_REG_R13W>()
#define REG_R14W registrar.getr<x86_reg::X86_REG_R14W>()
#define REG_R15W registrar.getr<x86_reg::X86_REG_R15W>()

/* 32-bits */
#define REG_SIL registrar.getr<x86_reg::X86_REG_SIL>()
#define REG_DIL registrar.getr<x86_reg::X86_REG_DIL>()
#define REG_EAX registrar.getr<x86_reg::X86_REG_EAX>()
#define REG_EBP registrar.getr<x86_reg::X86_REG_EBP>()
#define REG_EBX registrar.getr<x86_reg::X86_REG_EBX>()
#define REG_ECX registrar.getr<x86_reg::X86_REG_ECX>()
#define REG_EDI registrar.getr<x86_reg::X86_REG_EDI>()
#define REG_EDX registrar.getr<x86_reg::X86_REG_EDX>()
#define REG_ESI registrar.getr<x86_reg::X86_REG_ESI>()
#define REG_ESP registrar.getr<x86_reg::X86_REG_ESP>()
#define REG_R8D registrar.getr<x86_reg::X86_REG_R8D>()
#define REG_R9D registrar.getr<x86_reg::X86_REG_R9D>()
#define REG_R10D registrar.getr<x86_reg::X86_REG_R10D>()
#define REG_R11D registrar.getr<x86_reg::X86_REG_R11D>()
#define REG_R12D registrar.getr<x86_reg::X86_REG_R12D>()
#define REG_R13D registrar.getr<x86_reg::X86_REG_R13D>()
#define REG_R14D registrar.getr<x86_reg::X86_REG_R14D>()
#define REG_R15D registrar.getr<x86_reg::X86_REG_R15D>()
#define REG_ALL_32_REGS {REG_EAX, REG_EBP, REG_EBX, REG_ECX, REG_EDI, REG_EDX, REG_ESI, REG_ESP, REG_R8D, REG_R9D, REG_R10D, REG_R11D, REG_R12D, REG_R13D, REG_R14D, REG_R15D}

/* 64-bits */
#define REG_RAX registrar.getr<x86_reg::X86_REG_RAX>()
#define REG_RBP registrar.getr<x86_reg::X86_REG_RBP>()
#define REG_RBX registrar.getr<x86_reg::X86_REG_RBX>()
#define REG_RCX registrar.getr<x86_reg::X86_REG_RCX>()
#define REG_RDI registrar.getr<x86_reg::X86_REG_RDI>()
#define REG_RDX registrar.getr<x86_reg::X86_REG_RDX>()
#define REG_RSI registrar.getr<x86_reg::X86_REG_RSI>()
#define REG_RSP registrar.getr<x86_reg::X86_REG_RSP>()
#define REG_R8 registrar.getr<x86_reg::X86_REG_R8>()
#define REG_R9 registrar.getr<x86_reg::X86_REG_R9>()
#define REG_R10 registrar.getr<x86_reg::X86_REG_R10>()
#define REG_R11 registrar.getr<x86_reg::X86_REG_R11>()
#define REG_R12 registrar.getr<x86_reg::X86_REG_R12>()
#define REG_R13 registrar.getr<x86_reg::X86_REG_R13>()
#define REG_R14 registrar.getr<x86_reg::X86_REG_R14>()
#define REG_R15 registrar.getr<x86_reg::X86_REG_R15>()
#define REG_ALL_64_REGS {REG_RAX, REG_RBP, REG_RBX, REG_RCX, REG_RDI, REG_RDX, REG_RSI, REG_RSP, REG_R8, REG_R9, REG_R10, REG_R11, REG_R12, REG_R13, REG_R14, REG_R15}

/* AVX-128 */
#define REG_XMM0 registrar.getr<x86_reg::X86_REG_XMM0>()
#define REG_XMM1 registrar.getr<x86_reg::X86_REG_XMM1>()
#define REG_XMM2 registrar.getr<x86_reg::X86_REG_XMM2>()
#define REG_XMM3 registrar.getr<x86_reg::X86_REG_XMM3>()
#define REG_XMM4 registrar.getr<x86_reg::X86_REG_XMM4>()
#define REG_XMM5 registrar.getr<x86_reg::X86_REG_XMM5>()
#define REG_XMM6 registrar.getr<x86_reg::X86_REG_XMM6>()
#define REG_XMM7 registrar.getr<x86_reg::X86_REG_XMM7>()
#define REG_XMM8 registrar.getr<x86_reg::X86_REG_XMM8>()
#define REG_XMM9 registrar.getr<x86_reg::X86_REG_XMM9>()
#define REG_XMM10 registrar.getr<x86_reg::X86_REG_XMM10>()
#define REG_XMM11 registrar.getr<x86_reg::X86_REG_XMM11>()
#define REG_XMM12 registrar.getr<x86_reg::X86_REG_XMM12>()
#define REG_XMM13 registrar.getr<x86_reg::X86_REG_XMM13>()
#define REG_XMM14 registrar.getr<x86_reg::X86_REG_XMM14>()
#define REG_XMM15 registrar.getr<x86_reg::X86_REG_XMM15>()
#define REG_XMM16 registrar.getr<x86_reg::X86_REG_XMM16>()
#define REG_XMM17 registrar.getr<x86_reg::X86_REG_XMM17>()
#define REG_XMM18 registrar.getr<x86_reg::X86_REG_XMM18>()
#define REG_XMM19 registrar.getr<x86_reg::X86_REG_XMM19>()

/* AVX-256 */
#define REG_YMM0 registrar.getr<x86_reg::X86_REG_YMM0>()
#define REG_YMM1 registrar.getr<x86_reg::X86_REG_YMM1>()
#define REG_YMM2 registrar.getr<x86_reg::X86_REG_YMM2>()
#define REG_YMM3 registrar.getr<x86_reg::X86_REG_YMM3>()
#define REG_YMM4 registrar.getr<x86_reg::X86_REG_YMM4>()
#define REG_YMM5 registrar.getr<x86_reg::X86_REG_YMM5>()
#define REG_YMM6 registrar.getr<x86_reg::X86_REG_YMM6>()
#define REG_YMM7 registrar.getr<x86_reg::X86_REG_YMM7>()
#define REG_YMM8 registrar.getr<x86_reg::X86_REG_YMM8>()
#define REG_YMM9 registrar.getr<x86_reg::X86_REG_YMM9>()
#define REG_YMM10 registrar.getr<x86_reg::X86_REG_YMM10>()
#define REG_YMM11 registrar.getr<x86_reg::X86_REG_YMM11>()
#define REG_YMM12 registrar.getr<x86_reg::X86_REG_YMM12>()
#define REG_YMM13 registrar.getr<x86_reg::X86_REG_YMM13>()
#define REG_YMM14 registrar.getr<x86_reg::X86_REG_YMM14>()
#define REG_YMM15 registrar.getr<x86_reg::X86_REG_YMM15>()
#define REG_YMM16 registrar.getr<x86_reg::X86_REG_YMM16>()
#define REG_YMM17 registrar.getr<x86_reg::X86_REG_YMM17>()
#define REG_YMM18 registrar.getr<x86_reg::X86_REG_YMM18>()
#define REG_YMM19 registrar.getr<x86_reg::X86_REG_YMM19>()

/* AVX-512 */
#define REG_ZMM0 registrar.getr<x86_reg::X86_REG_ZMM0>()
#define REG_ZMM1 registrar.getr<x86_reg::X86_REG_ZMM1>()
#define REG_ZMM2 registrar.getr<x86_reg::X86_REG_ZMM2>()
#define REG_ZMM3 registrar.getr<x86_reg::X86_REG_ZMM3>()
#define REG_ZMM4 registrar.getr<x86_reg::X86_REG_ZMM4>()
#define REG_ZMM5 registrar.getr<x86_reg::X86_REG_ZMM5>()
#define REG_ZMM6 registrar.getr<x86_reg::X86_REG_ZMM6>()
#define REG_ZMM7 registrar.getr<x86_reg::X86_REG_ZMM7>()
#define REG_ZMM8 registrar.getr<x86_reg::X86_REG_ZMM8>()
#define REG_ZMM9 registrar.getr<x86_reg::X86_REG_ZMM9>()
#define REG_ZMM10 registrar.getr<x86_reg::X86_REG_ZMM10>()
#define REG_ZMM11 registrar.getr<x86_reg::X86_REG_ZMM11>()
#define REG_ZMM12 registrar.getr<x86_reg::X86_REG_ZMM12>()
#define REG_ZMM13 registrar.getr<x86_reg::X86_REG_ZMM13>()
#define REG_ZMM14 registrar.getr<x86_reg::X86_REG_ZMM14>()
#define REG_ZMM15 registrar.getr<x86_reg::X86_REG_ZMM15>()
#define REG_ZMM16 registrar.getr<x86_reg::X86_REG_ZMM16>()
#define REG_ZMM17 registrar.getr<x86_reg::X86_REG_ZMM17>()
#define REG_ZMM18 registrar.getr<x86_reg::X86_REG_ZMM18>()
#define REG_ZMM19 registrar.getr<x86_reg::X86_REG_ZMM19>()

/* Control Registers */
#define REG_CR0 registrar.getr<x86_reg::X86_REG_CR0>()
#define REG_CR1 registrar.getr<x86_reg::X86_REG_CR1>()
#define REG_CR2 registrar.getr<x86_reg::X86_REG_CR2>()
#define REG_CR3 registrar.getr<x86_reg::X86_REG_CR3>()
#define REG_CR4 registrar.getr<x86_reg::X86_REG_CR4>()
#define REG_CR5 registrar.getr<x86_reg::X86_REG_CR5>()
#define REG_CR6 registrar.getr<x86_reg::X86_REG_CR6>()
#define REG_CR7 registrar.getr<x86_reg::X86_REG_CR7>()
#define REG_CR8 registrar.getr<x86_reg::X86_REG_CR8>()
#define REG_CR9 registrar.getr<x86_reg::X86_REG_CR9>()
#define REG_CR10 registrar.getr<x86_reg::X86_REG_CR10>()
#define REG_CR11 registrar.getr<x86_reg::X86_REG_CR11>()
#define REG_CR12 registrar.getr<x86_reg::X86_REG_CR12>()
#define REG_CR13 registrar.getr<x86_reg::X86_REG_CR13>()
#define REG_CR14 registrar.getr<x86_reg::X86_REG_CR14>()
#define REG_CR15 registrar.getr<x86_reg::X86_REG_CR15>()
#define REG_ALL_CONTROL_REGS {REG_CR0, REG_CR1, REG_CR2, REG_CR3, REG_CR4, REG_CR5, REG_CR6, REG_CR7, REG_CR8, REG_CR9, REG_CR10, REG_CR11, REG_CR12, REG_CR13, REG_CR14, REG_CR15}

/* Float stack */
#define REG_ST0 registrar.getr<x86_reg::X86_REG_ST0>()
#define REG_ST1 registrar.getr<x86_reg::X86_REG_ST1>()
#define REG_ST2 registrar.getr<x86_reg::X86_REG_ST2>()
#define REG_ST3 registrar.getr<x86_reg::X86_REG_ST3>()
#define REG_ST4 registrar.getr<x86_reg::X86_REG_ST4>()
#define REG_ST5 registrar.getr<x86_reg::X86_REG_ST5>()
#define REG_ST6 registrar.getr<x86_reg::X86_REG_ST6>()
#define REG_ST7 registrar.getr<x86_reg::X86_REG_ST7>()

/* General flags */
#define FCF registrar.getf<xeflags::CF>()
#define FAF registrar.getf<xeflags::AF>()
#define FSF registrar.getf<xeflags::SF>()
#define FZF registrar.getf<xeflags::ZF>()
#define FPF registrar.getf<xeflags::PF>()
#define FOF registrar.getf<xeflags::OF>()
/* Non-general flags */
#define FTF registrar.getf<xeflags::TF>()
#define FIF registrar.getf<xeflags::IF>()
#define FDF registrar.getf<xeflags::DF>()
#define FNT registrar.getf<xeflags::NT>()
#define FRF registrar.getf<xeflags::RF>()
#define FVM registrar.getf<xeflags::VM>()
#define FAC registrar.getf<xeflags::AC>()
#define FVIF registrar.getf<xeflags::VIF>()
#define FVIP registrar.getf<xeflags::VIP>()
#define FGI registrar.getf<xeflags::GI>()
#define FID registrar.getf<xeflags::ID>()
#define FAI registrar.getf<xeflags::AI>()
#define FC0 registrar.getf<xeflags::C0>()
#define FC1 registrar.getf<xeflags::C1>()
#define FC2 registrar.getf<xeflags::C2>()
#define FC3 registrar.getf<xeflags::C3>()

#define F_BUILD_FLAGS {FCF, FAF, FSF, FZF, FPF, FOF, FTF, FIF, FDF, FNT, FRF, FC0, FC1, FC2, FC3}
#define F_COMMON xeflags::OF, xeflags::SF, xeflags::ZF, xeflags::AF, xeflags::CF, xeflags::PF
#define F_COMMON_NO_CF xeflags::OF, xeflags::SF, xeflags::ZF, xeflags::AF, xeflags::PF

[[maybe_unused]] static constexpr auto EXTENSION_XMM = 128u;    /* Bitwidth of XMMs */
[[maybe_unused]] static constexpr auto EXTENSION_YMM = 256u;    /* Bitwidth of YMMs */
[[maybe_unused]] static constexpr auto EXTENSION_ZMM = 512u;    /* Bitwidth of ZMMs */
[[maybe_unused]] static constexpr auto EXTENSION_ZMM16 = 512u;  /* Bitwidth of ZMM16s */
[[maybe_unused]] static constexpr auto EXTENSION_ZMM32 = 1024u; /* Bitwidth of ZMM32s */
[[maybe_unused]] static constexpr auto EXTENSION_MMX = 64u;     /* Bitwidth of MMX */

#endif