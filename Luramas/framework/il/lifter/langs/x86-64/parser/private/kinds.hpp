#pragma once
#ifdef LURAMAS_TARGET_X86

#include "../../../../builder/builder.hpp"
#include "../parser.hpp"

namespace kinds {

      inline constexpr luramas::il::arch::data::bin_kinds arith(const x86_insn r) {
            switch (r) {
                  case x86_insn::X86_INS_ADD:
                  case x86_insn::X86_INS_ADDPD:
                  case x86_insn::X86_INS_ADDPS:
                  case x86_insn::X86_INS_ADDSD:
                  case x86_insn::X86_INS_ADDSS:
                  case x86_insn::X86_INS_ADDSUBPD:
                  case x86_insn::X86_INS_ADDSUBPS:
                  case x86_insn::X86_INS_FADD:
                  case x86_insn::X86_INS_FIADD: {
                        return luramas::il::arch::data::bin_kinds::add_;
                  }
                  case x86_insn::X86_INS_SUB:
                  case x86_insn::X86_INS_SUBPD:
                  case x86_insn::X86_INS_SUBPS:
                  case x86_insn::X86_INS_FSUBR:
                  case x86_insn::X86_INS_FISUBR:
                  case x86_insn::X86_INS_FSUBRP:
                  case x86_insn::X86_INS_SUBSD:
                  case x86_insn::X86_INS_SUBSS:
                  case x86_insn::X86_INS_FSUB:
                  case x86_insn::X86_INS_FISUB:
                  case x86_insn::X86_INS_FSUBP: {
                        return luramas::il::arch::data::bin_kinds::sub_;
                  }
                  case x86_insn::X86_INS_MUL:
                  case x86_insn::X86_INS_MULPD:
                  case x86_insn::X86_INS_MULPS:
                  case x86_insn::X86_INS_MULSD:
                  case x86_insn::X86_INS_MULSS:
                  case x86_insn::X86_INS_MULX:
                  case x86_insn::X86_INS_FMUL:
                  case x86_insn::X86_INS_FIMUL:
                  case x86_insn::X86_INS_FMULP:
                  case x86_insn::X86_INS_IMUL: {
                        return luramas::il::arch::data::bin_kinds::mul_;
                  }
                  case x86_insn::X86_INS_SHL:
                  case x86_insn::X86_INS_SHLD:
                  case x86_insn::X86_INS_SHLX:
                  case x86_insn::X86_INS_SAL:
                  case x86_insn::X86_INS_SALC: {
                        return luramas::il::arch::data::bin_kinds::shl_;
                  }
                  case x86_insn::X86_INS_SHR:
                  case x86_insn::X86_INS_SHRD:
                  case x86_insn::X86_INS_SHRX:
                  case x86_insn::X86_INS_SAR:
                  case x86_insn::X86_INS_SARX: {
                        return luramas::il::arch::data::bin_kinds::shr_;
                  }
                  case x86_insn::X86_INS_AND:
                  case x86_insn::X86_INS_ANDN:
                  case x86_insn::X86_INS_ANDNPD:
                  case x86_insn::X86_INS_ANDNPS:
                  case x86_insn::X86_INS_ANDPD:
                  case x86_insn::X86_INS_ANDPS: {
                        return luramas::il::arch::data::bin_kinds::and_;
                  }
                  case x86_insn::X86_INS_OR:
                  case x86_insn::X86_INS_ORPD:
                  case x86_insn::X86_INS_ORPS: {
                        return luramas::il::arch::data::bin_kinds::or_;
                  }
                  case x86_insn::X86_INS_XOR:
                  case x86_insn::X86_INS_XORPD:
                  case x86_insn::X86_INS_XORPS: {
                        return luramas::il::arch::data::bin_kinds::xor_;
                  }
                  default: {
                        return luramas::il::arch::data::bin_kinds::nothing;
                  }
            }
      }

      inline constexpr bool unsign(const x86_insn r) {
            switch (r) {
                  case x86_insn::X86_INS_MUL:
                  case x86_insn::X86_INS_DIV: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
} // namespace kinds

#endif