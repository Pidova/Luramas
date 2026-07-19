#pragma once
#ifdef LURAMAS_TARGET_X86
#include "x86-64.hpp"

inline luramas_bitwidth reg_bits(const x86_reg reg) {
      switch (reg) {

            case x86_reg::X86_REG_AH:
            case x86_reg::X86_REG_AL:
            case x86_reg::X86_REG_BH:
            case x86_reg::X86_REG_BL:
            case x86_reg::X86_REG_CH:
            case x86_reg::X86_REG_CL:
            case x86_reg::X86_REG_DH:
            case x86_reg::X86_REG_DL:
            case x86_reg::X86_REG_BPL:
            case x86_reg::X86_REG_SPL:
            case x86_reg::X86_REG_SIL:
            case x86_reg::X86_REG_DIL:
            case x86_reg::X86_REG_R8B:
            case x86_reg::X86_REG_R9B:
            case x86_reg::X86_REG_R10B:
            case x86_reg::X86_REG_R11B:
            case x86_reg::X86_REG_R12B:
            case x86_reg::X86_REG_R13B:
            case x86_reg::X86_REG_R14B:
            case x86_reg::X86_REG_R15B: {
                  return 8u;
            }
            case x86_reg::X86_REG_BP:
            case x86_reg::X86_REG_AX:
            case x86_reg::X86_REG_BX:
            case x86_reg::X86_REG_CX:
            case x86_reg::X86_REG_DX:
            case x86_reg::X86_REG_SP:
            case x86_reg::X86_REG_SI:
            case x86_reg::X86_REG_IP:
            case x86_reg::X86_REG_DI:
            case x86_reg::X86_REG_R8W:
            case x86_reg::X86_REG_R9W:
            case x86_reg::X86_REG_R10W:
            case x86_reg::X86_REG_R11W:
            case x86_reg::X86_REG_R12W:
            case x86_reg::X86_REG_R13W:
            case x86_reg::X86_REG_R14W:
            case x86_reg::X86_REG_R15W: {
                  return 16u;
            }
            case x86_reg::X86_REG_EAX:
            case x86_reg::X86_REG_EBX:
            case x86_reg::X86_REG_ECX:
            case x86_reg::X86_REG_EDX:
            case x86_reg::X86_REG_ESP:
            case x86_reg::X86_REG_EBP:
            case x86_reg::X86_REG_ESI:
            case x86_reg::X86_REG_EDI:
            case x86_reg::X86_REG_EIP:
            case x86_reg::X86_REG_R8D:
            case x86_reg::X86_REG_R9D:
            case x86_reg::X86_REG_R10D:
            case x86_reg::X86_REG_R11D:
            case x86_reg::X86_REG_R12D:
            case x86_reg::X86_REG_R13D:
            case x86_reg::X86_REG_R14D:
            case x86_reg::X86_REG_R15D: {
                  return 32u;
            }
            case x86_reg::X86_REG_RAX:
            case x86_reg::X86_REG_RBX:
            case x86_reg::X86_REG_RCX:
            case x86_reg::X86_REG_RDX:
            case x86_reg::X86_REG_RSP:
            case x86_reg::X86_REG_RBP:
            case x86_reg::X86_REG_RSI:
            case x86_reg::X86_REG_RDI:
            case x86_reg::X86_REG_RIP:
            case x86_reg::X86_REG_R8:
            case x86_reg::X86_REG_R9:
            case x86_reg::X86_REG_R10:
            case x86_reg::X86_REG_R11:
            case x86_reg::X86_REG_R12:
            case x86_reg::X86_REG_R13:
            case x86_reg::X86_REG_R14:
            case x86_reg::X86_REG_R15: {
                  return 64u;
            }
            case x86_reg::X86_REG_XMM0:
            case x86_reg::X86_REG_XMM1:
            case x86_reg::X86_REG_XMM2:
            case x86_reg::X86_REG_XMM3:
            case x86_reg::X86_REG_XMM4:
            case x86_reg::X86_REG_XMM5:
            case x86_reg::X86_REG_XMM6:
            case x86_reg::X86_REG_XMM7:
            case x86_reg::X86_REG_XMM8:
            case x86_reg::X86_REG_XMM9:
            case x86_reg::X86_REG_XMM10:
            case x86_reg::X86_REG_XMM11:
            case x86_reg::X86_REG_XMM12:
            case x86_reg::X86_REG_XMM13:
            case x86_reg::X86_REG_XMM14:
            case x86_reg::X86_REG_XMM15:
            case x86_reg::X86_REG_XMM16:
            case x86_reg::X86_REG_XMM17:
            case x86_reg::X86_REG_XMM18:
            case x86_reg::X86_REG_XMM19:
            case x86_reg::X86_REG_XMM20:
            case x86_reg::X86_REG_XMM21:
            case x86_reg::X86_REG_XMM22:
            case x86_reg::X86_REG_XMM23:
            case x86_reg::X86_REG_XMM24:
            case x86_reg::X86_REG_XMM25:
            case x86_reg::X86_REG_XMM26:
            case x86_reg::X86_REG_XMM27:
            case x86_reg::X86_REG_XMM28:
            case x86_reg::X86_REG_XMM29:
            case x86_reg::X86_REG_XMM30:
            case x86_reg::X86_REG_XMM31: {
                  return 128u;
            }
            case x86_reg::X86_REG_YMM0:
            case x86_reg::X86_REG_YMM1:
            case x86_reg::X86_REG_YMM2:
            case x86_reg::X86_REG_YMM3:
            case x86_reg::X86_REG_YMM4:
            case x86_reg::X86_REG_YMM5:
            case x86_reg::X86_REG_YMM6:
            case x86_reg::X86_REG_YMM7:
            case x86_reg::X86_REG_YMM8:
            case x86_reg::X86_REG_YMM9:
            case x86_reg::X86_REG_YMM10:
            case x86_reg::X86_REG_YMM11:
            case x86_reg::X86_REG_YMM12:
            case x86_reg::X86_REG_YMM13:
            case x86_reg::X86_REG_YMM14:
            case x86_reg::X86_REG_YMM15:
            case x86_reg::X86_REG_YMM16:
            case x86_reg::X86_REG_YMM17:
            case x86_reg::X86_REG_YMM18:
            case x86_reg::X86_REG_YMM19:
            case x86_reg::X86_REG_YMM20:
            case x86_reg::X86_REG_YMM21:
            case x86_reg::X86_REG_YMM22:
            case x86_reg::X86_REG_YMM23:
            case x86_reg::X86_REG_YMM24:
            case x86_reg::X86_REG_YMM25:
            case x86_reg::X86_REG_YMM26:
            case x86_reg::X86_REG_YMM27:
            case x86_reg::X86_REG_YMM28:
            case x86_reg::X86_REG_YMM29:
            case x86_reg::X86_REG_YMM30:
            case x86_reg::X86_REG_YMM31: {
                  return 256u;
            }
            case x86_reg::X86_REG_ZMM0:
            case x86_reg::X86_REG_ZMM1:
            case x86_reg::X86_REG_ZMM2:
            case x86_reg::X86_REG_ZMM3:
            case x86_reg::X86_REG_ZMM4:
            case x86_reg::X86_REG_ZMM5:
            case x86_reg::X86_REG_ZMM6:
            case x86_reg::X86_REG_ZMM7:
            case x86_reg::X86_REG_ZMM8:
            case x86_reg::X86_REG_ZMM9:
            case x86_reg::X86_REG_ZMM10:
            case x86_reg::X86_REG_ZMM11:
            case x86_reg::X86_REG_ZMM12:
            case x86_reg::X86_REG_ZMM13:
            case x86_reg::X86_REG_ZMM14:
            case x86_reg::X86_REG_ZMM15:
            case x86_reg::X86_REG_ZMM16:
            case x86_reg::X86_REG_ZMM17:
            case x86_reg::X86_REG_ZMM18:
            case x86_reg::X86_REG_ZMM19:
            case x86_reg::X86_REG_ZMM20:
            case x86_reg::X86_REG_ZMM21:
            case x86_reg::X86_REG_ZMM22:
            case x86_reg::X86_REG_ZMM23:
            case x86_reg::X86_REG_ZMM24:
            case x86_reg::X86_REG_ZMM25:
            case x86_reg::X86_REG_ZMM26:
            case x86_reg::X86_REG_ZMM27:
            case x86_reg::X86_REG_ZMM28:
            case x86_reg::X86_REG_ZMM29:
            case x86_reg::X86_REG_ZMM30:
            case x86_reg::X86_REG_ZMM31: {
                  return 512u;
            }
            case x86_reg::X86_REG_ST1:
            case x86_reg::X86_REG_ST2:
            case x86_reg::X86_REG_ST3:
            case x86_reg::X86_REG_ST4:
            case x86_reg::X86_REG_ST5:
            case x86_reg::X86_REG_ST6:
            case x86_reg::X86_REG_ST7: {
                  return 80u;
            }
            default: {
                  return 1u;
            }
      }
}

inline x86_reg highest_reg(const x86_reg reg) {
      switch (reg) {
            case x86_reg::X86_REG_AH:
            case x86_reg::X86_REG_AL:
            case x86_reg::X86_REG_AX:
            case x86_reg::X86_REG_EAX: {
                  return x86_reg::X86_REG_RAX;
            }
            case x86_reg::X86_REG_BH:
            case x86_reg::X86_REG_BL:
            case x86_reg::X86_REG_BX:
            case x86_reg::X86_REG_EBX: {
                  return x86_reg::X86_REG_RBX;
            }
            case x86_reg::X86_REG_CH:
            case x86_reg::X86_REG_CL:
            case x86_reg::X86_REG_CX:
            case x86_reg::X86_REG_ECX: {
                  return x86_reg::X86_REG_RCX;
            }
            case x86_reg::X86_REG_DH:
            case x86_reg::X86_REG_DL:
            case x86_reg::X86_REG_DX:
            case x86_reg::X86_REG_EDX: {
                  return x86_reg::X86_REG_RDX;
            }
            case x86_reg::X86_REG_SI:
            case x86_reg::X86_REG_SIL:
            case x86_reg::X86_REG_ESI: {
                  return x86_reg::X86_REG_RSI;
            }
            case x86_reg::X86_REG_DI:
            case x86_reg::X86_REG_DIL:
            case x86_reg::X86_REG_EDI: {
                  return x86_reg::X86_REG_RDI;
            }
            case x86_reg::X86_REG_SP:
            case x86_reg::X86_REG_SPL:
            case x86_reg::X86_REG_ESP: {
                  return x86_reg::X86_REG_RSP;
            }
            case x86_reg::X86_REG_BP:
            case x86_reg::X86_REG_BPL:
            case x86_reg::X86_REG_EBP: {
                  return x86_reg::X86_REG_RBP;
            }
            case x86_reg::X86_REG_R8B:
            case x86_reg::X86_REG_R8W:
            case x86_reg::X86_REG_R8D: {
                  return x86_reg::X86_REG_R8;
            }
            case x86_reg::X86_REG_R9B:
            case x86_reg::X86_REG_R9W:
            case x86_reg::X86_REG_R9D: {
                  return x86_reg::X86_REG_R9;
            }
            case x86_reg::X86_REG_R10B:
            case x86_reg::X86_REG_R10W:
            case x86_reg::X86_REG_R10D: {
                  return x86_reg::X86_REG_R10;
            }
            case x86_reg::X86_REG_R11B:
            case x86_reg::X86_REG_R11W:
            case x86_reg::X86_REG_R11D: {
                  return x86_reg::X86_REG_R11;
            }
            case x86_reg::X86_REG_R12B:
            case x86_reg::X86_REG_R12W:
            case x86_reg::X86_REG_R12D: {
                  return x86_reg::X86_REG_R12;
            }
            case x86_reg::X86_REG_R13B:
            case x86_reg::X86_REG_R13W:
            case x86_reg::X86_REG_R13D: {
                  return x86_reg::X86_REG_R13;
            }
            case x86_reg::X86_REG_R14B:
            case x86_reg::X86_REG_R14W:
            case x86_reg::X86_REG_R14D: {
                  return x86_reg::X86_REG_R14;
            }
            case x86_reg::X86_REG_R15B:
            case x86_reg::X86_REG_R15W:
            case x86_reg::X86_REG_R15D: {
                  return x86_reg::X86_REG_R15;
            }
            case x86_reg::X86_REG_XMM0:
            case x86_reg::X86_REG_YMM0:
            case x86_reg::X86_REG_ZMM0: {
                  return x86_reg::X86_REG_ZMM0;
            }
            case x86_reg::X86_REG_XMM1:
            case x86_reg::X86_REG_YMM1:
            case x86_reg::X86_REG_ZMM1: {
                  return x86_reg::X86_REG_ZMM1;
            }
            case x86_reg::X86_REG_XMM2:
            case x86_reg::X86_REG_YMM2:
            case x86_reg::X86_REG_ZMM2: {
                  return x86_reg::X86_REG_ZMM2;
            }
            case x86_reg::X86_REG_XMM3:
            case x86_reg::X86_REG_YMM3:
            case x86_reg::X86_REG_ZMM3: {
                  return x86_reg::X86_REG_ZMM3;
            }
            case x86_reg::X86_REG_XMM4:
            case x86_reg::X86_REG_YMM4:
            case x86_reg::X86_REG_ZMM4: {
                  return x86_reg::X86_REG_ZMM4;
            }
            case x86_reg::X86_REG_XMM5:
            case x86_reg::X86_REG_YMM5:
            case x86_reg::X86_REG_ZMM5: {
                  return x86_reg::X86_REG_ZMM5;
            }
            case x86_reg::X86_REG_XMM6:
            case x86_reg::X86_REG_YMM6:
            case x86_reg::X86_REG_ZMM6: {
                  return x86_reg::X86_REG_ZMM6;
            }
            case x86_reg::X86_REG_XMM7:
            case x86_reg::X86_REG_YMM7:
            case x86_reg::X86_REG_ZMM7: {
                  return x86_reg::X86_REG_ZMM7;
            }
            case x86_reg::X86_REG_XMM8:
            case x86_reg::X86_REG_YMM8:
            case x86_reg::X86_REG_ZMM8: {
                  return x86_reg::X86_REG_ZMM8;
            }
            case x86_reg::X86_REG_XMM9:
            case x86_reg::X86_REG_YMM9:
            case x86_reg::X86_REG_ZMM9: {
                  return x86_reg::X86_REG_ZMM9;
            }
            case x86_reg::X86_REG_XMM10:
            case x86_reg::X86_REG_YMM10:
            case x86_reg::X86_REG_ZMM10: {
                  return x86_reg::X86_REG_ZMM10;
            }
            case x86_reg::X86_REG_XMM11:
            case x86_reg::X86_REG_YMM11:
            case x86_reg::X86_REG_ZMM11: {
                  return x86_reg::X86_REG_ZMM11;
            }
            case x86_reg::X86_REG_XMM12:
            case x86_reg::X86_REG_YMM12:
            case x86_reg::X86_REG_ZMM12: {
                  return x86_reg::X86_REG_ZMM12;
            }
            case x86_reg::X86_REG_XMM13:
            case x86_reg::X86_REG_YMM13:
            case x86_reg::X86_REG_ZMM13: {
                  return x86_reg::X86_REG_ZMM13;
            }
            case x86_reg::X86_REG_XMM14:
            case x86_reg::X86_REG_YMM14:
            case x86_reg::X86_REG_ZMM14: {
                  return x86_reg::X86_REG_ZMM14;
            }
            case x86_reg::X86_REG_XMM15:
            case x86_reg::X86_REG_YMM15:
            case x86_reg::X86_REG_ZMM15: {
                  return x86_reg::X86_REG_ZMM15;
            }
            case x86_reg::X86_REG_XMM16:
            case x86_reg::X86_REG_YMM16:
            case x86_reg::X86_REG_ZMM16: {
                  return x86_reg::X86_REG_ZMM16;
            }
            case x86_reg::X86_REG_XMM17:
            case x86_reg::X86_REG_YMM17:
            case x86_reg::X86_REG_ZMM17: {
                  return x86_reg::X86_REG_ZMM17;
            }
            case x86_reg::X86_REG_XMM18:
            case x86_reg::X86_REG_YMM18:
            case x86_reg::X86_REG_ZMM18: {
                  return x86_reg::X86_REG_ZMM18;
            }
            case x86_reg::X86_REG_XMM19:
            case x86_reg::X86_REG_YMM19:
            case x86_reg::X86_REG_ZMM19: {
                  return x86_reg::X86_REG_ZMM19;
            }
            case x86_reg::X86_REG_XMM20:
            case x86_reg::X86_REG_YMM20:
            case x86_reg::X86_REG_ZMM20: {
                  return x86_reg::X86_REG_ZMM20;
            }
            case x86_reg::X86_REG_XMM21:
            case x86_reg::X86_REG_YMM21:
            case x86_reg::X86_REG_ZMM21: {
                  return x86_reg::X86_REG_ZMM21;
            }
            case x86_reg::X86_REG_XMM22:
            case x86_reg::X86_REG_YMM22:
            case x86_reg::X86_REG_ZMM22: {
                  return x86_reg::X86_REG_ZMM22;
            }
            case x86_reg::X86_REG_XMM23:
            case x86_reg::X86_REG_YMM23:
            case x86_reg::X86_REG_ZMM23: {
                  return x86_reg::X86_REG_ZMM23;
            }
            case x86_reg::X86_REG_XMM24:
            case x86_reg::X86_REG_YMM24:
            case x86_reg::X86_REG_ZMM24: {
                  return x86_reg::X86_REG_ZMM24;
            }
            case x86_reg::X86_REG_XMM25:
            case x86_reg::X86_REG_YMM25:
            case x86_reg::X86_REG_ZMM25: {
                  return x86_reg::X86_REG_ZMM25;
            }
            case x86_reg::X86_REG_XMM26:
            case x86_reg::X86_REG_YMM26:
            case x86_reg::X86_REG_ZMM26: {
                  return x86_reg::X86_REG_ZMM26;
            }
            case x86_reg::X86_REG_XMM27:
            case x86_reg::X86_REG_YMM27:
            case x86_reg::X86_REG_ZMM27: {
                  return x86_reg::X86_REG_ZMM27;
            }
            case x86_reg::X86_REG_XMM28:
            case x86_reg::X86_REG_YMM28:
            case x86_reg::X86_REG_ZMM28: {
                  return x86_reg::X86_REG_ZMM28;
            }
            case x86_reg::X86_REG_XMM29:
            case x86_reg::X86_REG_YMM29:
            case x86_reg::X86_REG_ZMM29: {
                  return x86_reg::X86_REG_ZMM29;
            }
            case x86_reg::X86_REG_XMM30:
            case x86_reg::X86_REG_YMM30:
            case x86_reg::X86_REG_ZMM30: {
                  return x86_reg::X86_REG_ZMM30;
            }
            case x86_reg::X86_REG_XMM31:
            case x86_reg::X86_REG_YMM31:
            case x86_reg::X86_REG_ZMM31: {
                  return x86_reg::X86_REG_ZMM31;
            }
            default: {
                  return reg;
            }
      }
}

inline x86_reg adjust_reg(const x86_reg reg, const luramas_bitwidth bits) {
      switch (reg) {
            case x86_reg::X86_REG_AH:
            case x86_reg::X86_REG_AL:
            case x86_reg::X86_REG_AX:
            case x86_reg::X86_REG_EAX:
            case x86_reg::X86_REG_RAX: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_AL;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_AX;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_EAX;
                        }
                        default: {
                              return x86_reg::X86_REG_RAX;
                        }
                  }
            }
            case x86_reg::X86_REG_BH:
            case x86_reg::X86_REG_BL:
            case x86_reg::X86_REG_BX:
            case x86_reg::X86_REG_EBX:
            case x86_reg::X86_REG_RBX: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_BL;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_BX;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_EBX;
                        }
                        default: {
                              return x86_reg::X86_REG_RBX;
                        }
                  }
            }
            case x86_reg::X86_REG_CH:
            case x86_reg::X86_REG_CL:
            case x86_reg::X86_REG_CX:
            case x86_reg::X86_REG_ECX:
            case x86_reg::X86_REG_RCX: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_CL;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_CX;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_ECX;
                        }
                        default: {
                              return x86_reg::X86_REG_RCX;
                        }
                  }
            }
            case x86_reg::X86_REG_DH:
            case x86_reg::X86_REG_DL:
            case x86_reg::X86_REG_DX:
            case x86_reg::X86_REG_EDX:
            case x86_reg::X86_REG_RDX: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_DL;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_DX;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_EDX;
                        }
                        default: {
                              return x86_reg::X86_REG_RDX;
                        }
                  }
            }
            case x86_reg::X86_REG_SI:
            case x86_reg::X86_REG_SIL:
            case x86_reg::X86_REG_ESI:
            case x86_reg::X86_REG_RSI: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_SIL;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_SI;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_ESI;
                        }
                        default: {
                              return x86_reg::X86_REG_RSI;
                        }
                  }
            }
            case x86_reg::X86_REG_DI:
            case x86_reg::X86_REG_DIL:
            case x86_reg::X86_REG_EDI:
            case x86_reg::X86_REG_RDI: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_DIL;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_DI;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_EDI;
                        }
                        default: {
                              return x86_reg::X86_REG_RDI;
                        }
                  }
            }
            case x86_reg::X86_REG_SP:
            case x86_reg::X86_REG_SPL:
            case x86_reg::X86_REG_ESP:
            case x86_reg::X86_REG_RSP: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_SPL;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_SP;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_ESP;
                        }
                        default: {
                              return x86_reg::X86_REG_RSP;
                        }
                  }
            }
            case x86_reg::X86_REG_BP:
            case x86_reg::X86_REG_BPL:
            case x86_reg::X86_REG_EBP:
            case x86_reg::X86_REG_RBP: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_BPL;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_BP;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_EBP;
                        }
                        default: {
                              return x86_reg::X86_REG_RBP;
                        }
                  }
            }
            case x86_reg::X86_REG_R8B:
            case x86_reg::X86_REG_R8W:
            case x86_reg::X86_REG_R8D:
            case x86_reg::X86_REG_R8: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_R8B;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_R8W;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_R8D;
                        }
                        default: {
                              return x86_reg::X86_REG_R8;
                        }
                  }
            }
            case x86_reg::X86_REG_R9B:
            case x86_reg::X86_REG_R9W:
            case x86_reg::X86_REG_R9D:
            case x86_reg::X86_REG_R9: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_R9B;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_R9W;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_R9D;
                        }
                        default: {
                              return x86_reg::X86_REG_R9;
                        }
                  }
            }
            case x86_reg::X86_REG_R10B:
            case x86_reg::X86_REG_R10W:
            case x86_reg::X86_REG_R10D:
            case x86_reg::X86_REG_R10: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_R10B;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_R10W;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_R10D;
                        }
                        default: {
                              return x86_reg::X86_REG_R10;
                        }
                  }
            }
            case x86_reg::X86_REG_R11B:
            case x86_reg::X86_REG_R11W:
            case x86_reg::X86_REG_R11D:
            case x86_reg::X86_REG_R11: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_R11B;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_R11W;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_R11D;
                        }
                        default: {
                              return x86_reg::X86_REG_R11;
                        }
                  }
            }
            case x86_reg::X86_REG_R12B:
            case x86_reg::X86_REG_R12W:
            case x86_reg::X86_REG_R12D:
            case x86_reg::X86_REG_R12: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_R12B;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_R12W;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_R12D;
                        }
                        default: {
                              return x86_reg::X86_REG_R12;
                        }
                  }
            }
            case x86_reg::X86_REG_R13B:
            case x86_reg::X86_REG_R13W:
            case x86_reg::X86_REG_R13D:
            case x86_reg::X86_REG_R13: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_R13B;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_R13W;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_R13D;
                        }
                        default: {
                              return x86_reg::X86_REG_R13;
                        }
                  }
            }
            case x86_reg::X86_REG_R14B:
            case x86_reg::X86_REG_R14W:
            case x86_reg::X86_REG_R14D:
            case x86_reg::X86_REG_R14: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_R14B;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_R14W;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_R14D;
                        }
                        default: {
                              return x86_reg::X86_REG_R14;
                        }
                  }
            }
            case x86_reg::X86_REG_R15B:
            case x86_reg::X86_REG_R15W:
            case x86_reg::X86_REG_R15D:
            case x86_reg::X86_REG_R15: {
                  switch (bits) {
                        case 8u: {
                              return x86_reg::X86_REG_R15B;
                        }
                        case 16u: {
                              return x86_reg::X86_REG_R15W;
                        }
                        case 32u: {
                              return x86_reg::X86_REG_R15D;
                        }
                        default: {
                              return x86_reg::X86_REG_R15;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM0:
            case x86_reg::X86_REG_YMM0:
            case x86_reg::X86_REG_ZMM0: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM0;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM0;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM0;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM0;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM1:
            case x86_reg::X86_REG_YMM1:
            case x86_reg::X86_REG_ZMM1: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM1;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM1;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM1;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM1;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM2:
            case x86_reg::X86_REG_YMM2:
            case x86_reg::X86_REG_ZMM2: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM2;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM2;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM2;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM2;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM3:
            case x86_reg::X86_REG_YMM3:
            case x86_reg::X86_REG_ZMM3: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM3;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM3;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM3;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM3;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM4:
            case x86_reg::X86_REG_YMM4:
            case x86_reg::X86_REG_ZMM4: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM4;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM4;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM4;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM4;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM5:
            case x86_reg::X86_REG_YMM5:
            case x86_reg::X86_REG_ZMM5: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM5;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM5;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM5;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM5;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM6:
            case x86_reg::X86_REG_YMM6:
            case x86_reg::X86_REG_ZMM6: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM6;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM6;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM6;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM6;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM7:
            case x86_reg::X86_REG_YMM7:
            case x86_reg::X86_REG_ZMM7: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM7;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM7;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM7;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM7;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM8:
            case x86_reg::X86_REG_YMM8:
            case x86_reg::X86_REG_ZMM8: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM8;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM8;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM8;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM8;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM9:
            case x86_reg::X86_REG_YMM9:
            case x86_reg::X86_REG_ZMM9: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM9;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM9;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM9;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM9;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM10:
            case x86_reg::X86_REG_YMM10:
            case x86_reg::X86_REG_ZMM10: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM10;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM10;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM10;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM10;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM11:
            case x86_reg::X86_REG_YMM11:
            case x86_reg::X86_REG_ZMM11: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM11;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM11;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM11;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM11;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM12:
            case x86_reg::X86_REG_YMM12:
            case x86_reg::X86_REG_ZMM12: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM12;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM12;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM12;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM12;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM13:
            case x86_reg::X86_REG_YMM13:
            case x86_reg::X86_REG_ZMM13: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM13;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM13;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM13;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM13;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM14:
            case x86_reg::X86_REG_YMM14:
            case x86_reg::X86_REG_ZMM14: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM14;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM14;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM14;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM14;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM15:
            case x86_reg::X86_REG_YMM15:
            case x86_reg::X86_REG_ZMM15: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM15;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM15;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM15;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM15;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM16:
            case x86_reg::X86_REG_YMM16:
            case x86_reg::X86_REG_ZMM16: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM16;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM16;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM16;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM16;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM17:
            case x86_reg::X86_REG_YMM17:
            case x86_reg::X86_REG_ZMM17: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM17;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM17;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM17;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM17;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM18:
            case x86_reg::X86_REG_YMM18:
            case x86_reg::X86_REG_ZMM18: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM18;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM18;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM18;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM18;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM19:
            case x86_reg::X86_REG_YMM19:
            case x86_reg::X86_REG_ZMM19: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM19;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM19;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM19;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM19;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM20:
            case x86_reg::X86_REG_YMM20:
            case x86_reg::X86_REG_ZMM20: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM20;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM20;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM20;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM20;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM21:
            case x86_reg::X86_REG_YMM21:
            case x86_reg::X86_REG_ZMM21: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM21;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM21;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM21;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM21;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM22:
            case x86_reg::X86_REG_YMM22:
            case x86_reg::X86_REG_ZMM22: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM22;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM22;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM22;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM22;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM23:
            case x86_reg::X86_REG_YMM23:
            case x86_reg::X86_REG_ZMM23: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM23;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM23;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM23;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM23;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM24:
            case x86_reg::X86_REG_YMM24:
            case x86_reg::X86_REG_ZMM24: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM24;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM24;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM24;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM24;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM25:
            case x86_reg::X86_REG_YMM25:
            case x86_reg::X86_REG_ZMM25: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM25;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM25;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM25;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM25;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM26:
            case x86_reg::X86_REG_YMM26:
            case x86_reg::X86_REG_ZMM26: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM26;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM26;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM26;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM26;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM27:
            case x86_reg::X86_REG_YMM27:
            case x86_reg::X86_REG_ZMM27: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM27;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM27;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM27;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM27;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM28:
            case x86_reg::X86_REG_YMM28:
            case x86_reg::X86_REG_ZMM28: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM28;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM28;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM28;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM28;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM29:
            case x86_reg::X86_REG_YMM29:
            case x86_reg::X86_REG_ZMM29: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM29;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM29;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM29;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM29;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM30:
            case x86_reg::X86_REG_YMM30:
            case x86_reg::X86_REG_ZMM30: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM30;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM30;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM30;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM30;
                        }
                  }
            }
            case x86_reg::X86_REG_XMM31:
            case x86_reg::X86_REG_YMM31:
            case x86_reg::X86_REG_ZMM31: {
                  switch (bits) {
                        case 128u: {
                              return x86_reg::X86_REG_XMM31;
                        }
                        case 256u: {
                              return x86_reg::X86_REG_YMM31;
                        }
                        case 512u: {
                              return x86_reg::X86_REG_ZMM31;
                        }
                        default: {
                              return x86_reg::X86_REG_XMM31;
                        }
                  }
            }
            default: {
                  return reg;
            }
      }
}

#endif