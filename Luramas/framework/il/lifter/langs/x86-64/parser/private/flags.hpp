#pragma once
#ifdef LURAMAS_TARGET_X86
#include <cstdint>

/* X86 flags */
enum class xeflags : std::uint32_t {
      AF = 1u << 0,   /* Auxiliary Flag */
      CF = 1u << 1,   /* Carry Flag */
      SF = 1u << 2,   /* Sign Flag */
      ZF = 1u << 3,   /* Zero Flag */
      PF = 1u << 4,   /* Parity Flag */
      OF = 1u << 5,   /* Overflow Flag */
      TF = 1u << 6,   /* Trap Flag */
      IF = 1u << 7,   /* Interrupt Flag */
      DF = 1u << 8,   /* Direction Flag */
      NT = 1u << 9,   /* Nested Task Flag */
      RF = 1u << 10,  /* Resume Flag */
      VM = 1u << 11,  /* Virtual 8086 mode */
      AC = 1u << 12,  /* Alignment Check */
      VIF = 1u << 13, /* Virtual Interrupt Flag */
      VIP = 1u << 14, /* Virtual Interrupt Pending */
      GI = 1u << 15,  /* Global Interrupt */
      ID = 1u << 16,  /* CPUID support */
      AI = 1u << 17,  /* Alternate Instruction Set */
      C0 = 1u << 18,  /* Control Flag 0 */
      C1 = 1u << 19,  /* Control Flag 1 */
      C2 = 1u << 20,  /* Control Flag 2 */
      C3 = 1u << 21,  /* Control Flag 3 */
};
#define getflag(f) static_cast<std::uint32_t>(xeflags::f) /* Get flag as u32 */

/* Helper for packing flags */
inline constexpr xeflags operator|(const xeflags lhs, const xeflags rhs) {
      return static_cast<xeflags>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
}

#endif