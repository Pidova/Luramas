#ifdef LURAMAS_TARGET_X86
#include "common.hpp"

/* Instruction handlers: DAA - LZCNT */
namespace vm {

      void DAA(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto add6 = (REG_AL & 0x0F) > 9U;
            const auto add60 = REG_AL > 0x99;

            const auto adj6 = add6 << 1U;
            const auto adj60 = add60 << 6U;

            FAF = add6;
            FCF = add60;
            REG_AL += adj6 | adj60;
            tools::eflags::mutate<xeflags::OF, xeflags::SF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, REG_AL));
            return;
      }

      void DAS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto old_al = registrar.build->make_temp(REG_AL);
            const auto old_cf = registrar.build->make_temp(FCF);

            FCF = 0U;

            const auto low_nibble = REG_AL & 0x0FU;
            kif((low_nibble > 9U) || (FAF == 1U)) {
                  const auto borrow = (REG_AL < 6U);
                  REG_AL -= 6U;
                  FCF |= borrow;
                  FAF = 1U;
            }
            kelse;
            {
                  FAF = 0U;
            }
            kend;

            kif((old_al > 0x99U) || (old_cf == 1U)) {
                  REG_AL -= 0x60U;
                  FCF = 1U;
            }
            kend;

            tools::eflags::mutate<xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, old_al, REG_AL));
            return;
      }

      void DATA16(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void DEC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();

            const auto temp = dest - 1U;
            tools::eflags::mutate<F_COMMON_NO_CF>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp));
            dest = temp;
            return;
      }

      void DIV(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto v = operands.front();
            auto src = v.cast(true);
            switch (src.bits()) {
                  case 8U: {

                        const auto temp = REG_AX / src;
                        REG_AL = temp;
                        REG_AH = REG_AX % src;
                        break;
                  }
                  case 16U: {

                        const auto temp = LURAMAS_FBUILD_UPAIR(REG_DX, REG_AX) / src;
                        REG_AX = temp;
                        REG_DX = LURAMAS_FBUILD_UPAIR(REG_DX, REG_AX) % src;
                        break;
                  }
                  case 32U: {

                        const auto temp = LURAMAS_FBUILD_UPAIR(REG_EDX, REG_EAX) / src;
                        REG_EAX = temp;
                        REG_EDX = LURAMAS_FBUILD_UPAIR(REG_EDX, REG_EAX) % src;
                        break;
                  }
                  default: {

                        const auto temp = LURAMAS_FBUILD_UPAIR(REG_RDX, REG_RAX) / src;
                        REG_RAX = temp;
                        REG_RDX = LURAMAS_FBUILD_UPAIR(REG_RDX, REG_RAX) % src;
                        break;
                  }
            }
            return;
      }

      void DIVPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0, 63, src1.read(0, 63) / src2.read(0, 63));
            dest.write(64, 127, src1.read(64, 127) / src2.read(64, 127));
            return;
      }

      void DIVPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0, 31, src1.read(0, 31) / src2.read(0, 31));
            dest.write(32, 63, src1.read(32, 63) / src2.read(32, 63));
            dest.write(64, 95, src1.read(64, 95) / src2.read(64, 95));
            dest.write(96, 127, src1.read(96, 127) / src2.read(96, 127));
            return;
      }

      void FDIVR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FIDIVR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FDIVRP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void DIVSD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0, 63, dest.read(0, 63) / src.read(0, 63));
            return;
      }

      void DIVSS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0, 31, dest.read(0, 31) / src.read(0, 31));
            return;
      }

      void FDIV(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FIDIV(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FDIVP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void DPPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void DPPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void ENCLS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void ENCLU(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void ENCLV(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void ENDBR32(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::CONTROL_FLOW::INDIRECT_BR_PAD, {klura_tint(32U)});
            return;
      }

      void ENDBR64(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::CONTROL_FLOW::INDIRECT_BR_PAD, {klura_tint(64U)});
            return;
      }

      void ENTER(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void EXTRACTPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void EXTRQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void F2XM1(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LCALL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            vm::CALL(registrar, operands);
            return;
      }

      void LJMP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            vm::JMP(registrar, operands);
            return;
      }

      void JMP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            build::page_gotos(registrar, operands);
            return;
      }

      void FBLD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FBSTP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FCOMPP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FDECSTP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FDISI8087_NOP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FEMMS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FENI8087_NOP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FFREE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FFREEP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FICOM(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FICOMP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FINCSTP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FLDCW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FLDENV(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FLDL2E(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FLDL2T(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FLDLG2(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FLDLN2(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FLDPI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FNCLEX(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FNINIT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FNOP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FNSTCW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FNSTSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FPATAN(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FSTPNCE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FPREM(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FPREM1(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FPTAN(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FRNDINT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FRSTOR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FNSAVE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FSCALE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FSETPM(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FSINCOS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FNSTENV(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FXAM(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FXRSTOR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FXRSTOR64(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FXSAVE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FXSAVE64(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FXTRACT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FYL2X(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FYL2XP1(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void GETSEC(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void GF2P8AFFINEINVQB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void GF2P8AFFINEQB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &srcdest = operands.front();
            const auto &sr_c1 = operands[1U];
            const auto &im_m8 = operands.back();

            function_handler f(registrar.build);
            for (auto j = 0U; j < 2U; ++j) {

                  const auto qword_offset = j * 64U;
                  const auto tsrc1_qw = sr_c1.read(qword_offset, qword_offset + 63U);
                  for (auto b = 0U; b < 8U; ++b) {

                        const auto byte_low = qword_offset + (b * 8U);
                        const auto byte_high = byte_low + 7U;
                        srcdest.write(byte_low, byte_high, luramas::il::lifter::builder::libraries::math::affine_byte(f, tsrc1_qw, srcdest.read(byte_low, byte_high), im_m8));
                  }
            }
            return;
      }

      void GF2P8MULB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void HADDPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void HADDPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void HLT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void HSUBPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void HSUBPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void IDIV(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto v = operands.front();
            const auto src = v.cast(false);
            switch (src.bits()) {
                  case 8U: {

                        const auto temp = REG_AX / src;
                        REG_AL = temp;
                        REG_AH = REG_AX % src;
                        break;
                  }
                  case 16U: {

                        const auto temp = LURAMAS_FBUILD_UPAIR(REG_DX, REG_AX) / src;
                        REG_AX = temp;
                        REG_DX = LURAMAS_FBUILD_UPAIR(REG_DX, REG_AX) % src;
                        break;
                  }
                  case 32U: {

                        const auto temp = LURAMAS_FBUILD_UPAIR(REG_EDX, REG_EAX) / src;
                        REG_EAX = temp;
                        REG_EDX = LURAMAS_FBUILD_UPAIR(REG_EDX, REG_EAX) % src;
                        break;
                  }
                  default: {

                        const auto temp = LURAMAS_FBUILD_UPAIR(REG_RDX, REG_RAX) / src;
                        REG_RAX = temp;
                        REG_RDX = LURAMAS_FBUILD_UPAIR(REG_RDX, REG_RAX) % src;
                        break;
                  }
            }
            return;
      }

      void FILD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void IMUL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            switch (operands.size()) {
                  case 2U: {

                        const auto &dest = operands.front();
                        const auto &src = operands.back();

                        const auto tmp = (dest * src).cast(true);
                        dest = tmp;
                        kif(LURAMAS_FBUILD_SIGNEXTEND(dest) != tmp) {
                              FCF = 1U;
                              FOF = 1U;
                        }
                        kelse;
                        {
                              FCF = 0U;
                              FOF = 0U;
                        }
                        kend;
                        break;
                  }
                  case 3U: {

                        const auto &dest = operands.front();
                        const auto &src1 = operands[1U];
                        const auto &src2 = operands.back();

                        const auto tmp = (src1 * src2).cast(true);
                        dest = tmp;
                        kif(LURAMAS_FBUILD_SIGNEXTEND(dest) != tmp) {
                              FCF = 1U;
                              FOF = 1U;
                        }
                        kelse;
                        {
                              FCF = 0U;
                              FOF = 0U;
                        }
                        kend;
                        break;
                  }
                  default: {

                        const auto &src = operands.front();
                        switch (src.bits()) {
                              case 8U: {

                                    const auto tmp = LURAMAS_FBUILD_EXTEND_U16(REG_AL * src);
                                    REG_AX = tmp;

                                    kif(LURAMAS_FBUILD_SIGNEXTEND(tmp.read(0, 7)) == tmp);
                                    {
                                          FCF = 0U;
                                          FOF = 0U;
                                    }
                                    kelse;
                                    {
                                          FCF = 1U;
                                          FOF = 1U;
                                    }
                                    kend;
                                    break;
                              }
                              case 16U: {

                                    const auto tmp = LURAMAS_FBUILD_EXTEND_U32(REG_AX * src);
                                    REG_DX = LURAMAS_FBUILD_LOWER_BITS(tmp);
                                    REG_AX = LURAMAS_FBUILD_UPPER_BITS(tmp);

                                    kif(LURAMAS_FBUILD_SIGNEXTEND(tmp.read(0, 15)) == tmp);
                                    {
                                          FCF = 0U;
                                          FOF = 0U;
                                    }
                                    kelse;
                                    {
                                          FCF = 1U;
                                          FOF = 1U;
                                    }
                                    kend;
                                    break;
                              }
                              case 32U: {

                                    const auto tmp = LURAMAS_FBUILD_EXTEND_U64(REG_EAX * src);
                                    REG_EDX = LURAMAS_FBUILD_LOWER_BITS(tmp);
                                    REG_EAX = LURAMAS_FBUILD_UPPER_BITS(tmp);

                                    kif(LURAMAS_FBUILD_SIGNEXTEND(tmp.read(0, 63)) == tmp);
                                    {
                                          FCF = 0U;
                                          FOF = 0U;
                                    }
                                    kelse;
                                    {
                                          FCF = 1U;
                                          FOF = 1U;
                                    }
                                    kend;
                                    break;
                              }
                              default: {

                                    const auto tmp = LURAMAS_FBUILD_EXTEND_U128(REG_RAX * src);
                                    REG_EDX = LURAMAS_FBUILD_LOWER_BITS(tmp);
                                    REG_EAX = LURAMAS_FBUILD_UPPER_BITS(tmp);

                                    kif(LURAMAS_FBUILD_SIGNEXTEND(tmp.read(0, 127)) == tmp);
                                    {
                                          FCF = 0U;
                                          FOF = 0U;
                                    }
                                    kelse;
                                    {
                                          FCF = 1U;
                                          FOF = 1U;
                                    }
                                    kend;
                                    break;
                              }
                        }
                        break;
                  }
            }
            return;
      }

      void IN(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &port = operands.back();

            klura_call(luramas::builtins::IO::OUTPUT, {klura_tint(0U), port}, {dest});
            return;
      }

      void INC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();

            const auto temp = dest + 1U;
            tools::eflags::mutate<F_COMMON_NO_CF>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp));
            dest = temp;
            return;
      }

      void INCSSPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void INCSSPQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void INSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::IO::OUTPUT, {klura_tint(0U), REG_DX}, {REG_DIL});
            return;
      }

      void INSERTPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void INSERTQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void INSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::IO::OUTPUT, {klura_tint(0U), REG_DX}, {REG_EDI});
            return;
      }

      void INSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::IO::OUTPUT, {klura_tint(0U), REG_DX}, {REG_DI});
            return;
      }

      void INT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &v = operands.front();
            klura_call(luramas::builtins::INTERRUPT::INVOKE, {v});
            return;
      }

      void INT1(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::INTERRUPT::INVOKE, {klura_tint(1U)});
            return;
      }

      void INT3(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::INTERRUPT::INVOKE, {klura_tint(3U)});
            return;
      }

      void INTO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &v = operands.front();
            klura_call(luramas::builtins::INTERRUPT::ADD, {v});
            return;
      }

      void INVD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void INVEPT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void INVLPG(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void INVLPGA(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void INVPCID(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void INVVPID(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void IRET(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void IRETD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void IRETQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FISTTP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FIST(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FISTP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void JAE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 0U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JA(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 0U && FZF == 0U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JBE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 1U || FZF == 1U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 1U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JCXZ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(REG_CX == 0U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JECXZ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(REG_ECX == 0U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FZF == 1U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JGE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FSF == FOF) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JG(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FZF == 0U && FOF == FSF) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JLE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FZF == 1U || FSF != FOF) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FSF != FOF) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JNE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FZF == 0U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JNO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FOF == 0U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JNP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FPF == 0U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JNS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FSF == 0U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FOF == 1U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FPF == 1U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JRCXZ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(REG_RCX == 0U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void JS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FSF == 1U) {
                  build::page_gotos(registrar, operands);
            }
            kend;
            return;
      }

      void KADDB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 7U, src1.read(0U, 7U) + src2.read(0U, 7U));
            dest.write(8U, dest.bits() - 1U, 0U);
            return;
      }

      void KADDD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 31U, src1.read(0U, 31U) + src2.read(0U, 31U));
            dest.write(32U, dest.bits() - 1U, 0U);
            return;
      }

      void KADDQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 63U, src1.read(0U, 63U) + src2.read(0U, 63U));
            dest.write(64U, dest.bits() - 1U, 0U);
            return;
      }

      void KADDW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 15U, src1.read(0U, 15U) + src2.read(0U, 15U));
            dest.write(16U, dest.bits() - 1U, 0U);
            return;
      }

      void KANDB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 7U, src1.read(0U, 7U) & src2.read(0U, 7U));
            dest.write(8U, dest.bits() - 1U, 0U);
            return;
      }

      void KANDD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 31U, src1.read(0U, 31U) & src2.read(0U, 31U));
            dest.write(32U, dest.bits() - 1U, 0U);
            return;
      }

      void KANDNB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 7U, ~src1.read(0U, 7U) & src2.read(0U, 7U));
            dest.write(8U, dest.bits() - 1U, 0U);
            return;
      }

      void KANDND(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 31U, ~src1.read(0U, 31U) & src2.read(0U, 31U));
            dest.write(32U, dest.bits() - 1U, 0U);
            return;
      }

      void KANDNQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 63U, ~src1.read(0U, 63U) & src2.read(0U, 63U));
            dest.write(64U, dest.bits() - 1U, 0U);
            return;
      }

      void KANDNW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 15U, ~src1.read(0U, 15U) & src2.read(0U, 15U));
            dest.write(16U, dest.bits() - 1U, 0U);
            return;
      }

      void KANDQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 63U, src1.read(0U, 63U) & src2.read(0U, 63U));
            dest.write(64U, dest.bits() - 1U, 0U);
            return;
      }

      void KANDW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 15U, src1.read(0U, 15U) & src2.read(0U, 15U));
            dest.write(16U, dest.bits() - 1U, 0U);
            return;
      }

      void KMOVB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void KMOVD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void KMOVQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void KMOVW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void KNOTB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 7U, ~src.read(0U, 7U));
            dest.write(8U, dest.bits() - 1U, 0U);
            return;
      }

      void KNOTD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, ~src.read(0U, 31U));
            dest.write(32U, dest.bits() - 1U, 0U);
            return;
      }

      void KNOTQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63U, ~src.read(0U, 63U));
            dest.write(64U, dest.bits() - 1U, 0U);
            return;
      }

      void KNOTW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 15U, ~src.read(0U, 15U));
            dest.write(16U, dest.bits() - 1U, 0U);
            return;
      }

      void KORB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 7U, src1.read(0U, 7U) | src2.read(0U, 7U));
            dest.write(8U, dest.bits() - 1U, 0U);
            return;
      }

      void KORD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 31U, src1.read(0U, 31U) | src2.read(0U, 31U));
            dest.write(32U, dest.bits() - 1U, 0U);
            return;
      }

      void KORQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 63U, src1.read(0U, 63U) | src2.read(0U, 63U));
            dest.write(64U, dest.bits() - 1U, 0U);
            return;
      }

      void KORTESTB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void KORTESTD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void KORTESTQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void KORTESTW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void KORW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 15U, src1.read(0U, 15U) | src2.read(0U, 15U));
            dest.write(16U, dest.bits() - 1U, 0U);
            return;
      }

      void KSHIFTLB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 7U, src1.read(0U, 7U) << src2.read(0U, 7U));
            dest.write(8U, dest.bits() - 1U, 0U);
            return;
      }

      void KSHIFTLD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 31U, src1.read(0U, 31U) << src2.read(0U, 31U));
            dest.write(32U, dest.bits() - 1U, 0U);
            return;
      }

      void KSHIFTLQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 63U, src1.read(0U, 63U) << src2.read(0U, 63U));
            dest.write(64U, dest.bits() - 1U, 0U);
            return;
      }

      void KSHIFTLW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 15U, src1.read(0U, 15U) << src2.read(0U, 15U));
            dest.write(16U, dest.bits() - 1U, 0U);
            return;
      }

      void KSHIFTRB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 7U, src1.read(0U, 7U) >> src2.read(0U, 7U));
            dest.write(8U, dest.bits() - 1U, 0U);
            return;
      }

      void KSHIFTRD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 31U, src1.read(0U, 31U) >> src2.read(0U, 31U));
            dest.write(32U, dest.bits() - 1U, 0U);
            return;
      }

      void KSHIFTRQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 63U, src1.read(0U, 63U) >> src2.read(0U, 63U));
            dest.write(64U, dest.bits() - 1U, 0U);
            return;
      }

      void KSHIFTRW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 15U, src1.read(0U, 15U) >> src2.read(0U, 15U));
            dest.write(16U, dest.bits() - 1U, 0U);
            return;
      }

      void KTESTB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &src1 = operands.front();
            const auto &src2 = operands.back();

            const auto temp = src1.read(0U, 7U) & src2.read(0U, 7U);
            FZF = (temp == 0U);

            FCF = ((src2.read(0U, 7U) & ~src1.read(0U, 7U)) == 0U);
            FAF = 0U;
            FOF = 0U;
            FPF = 0U;
            FSF = 0U;
            return;
      }

      void KTESTD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &src1 = operands.front();
            const auto &src2 = operands.back();

            const auto temp = src1.read(0U, 31U) & src2.read(0U, 31U);
            FZF = (temp == 0U);

            FCF = ((src2.read(0U, 31U) & ~src1.read(0U, 31U)) == 0U);
            FAF = 0U;
            FOF = 0U;
            FPF = 0U;
            FSF = 0U;
            return;
      }

      void KTESTQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &src1 = operands.front();
            const auto &src2 = operands.back();

            const auto temp = src1.read(0U, 63U) & src2.read(0U, 63U);
            FZF = (temp == 0U);

            FCF = ((src2.read(0U, 63U) & ~src1.read(0U, 63U)) == 0U);
            FAF = 0U;
            FOF = 0U;
            FPF = 0U;
            FSF = 0U;
            return;
      }

      void KTESTW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &src1 = operands.front();
            const auto &src2 = operands.back();

            const auto temp = src1.read(0U, 15U) & src2.read(0U, 15U);
            FZF = (temp == 0U);

            FCF = ((src2.read(0U, 15U) & ~src1.read(0U, 15U)) == 0U);
            FAF = 0U;
            FOF = 0U;
            FPF = 0U;
            FSF = 0U;
            return;
      }

      void KUNPCKBW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 7U, src2.read(0U, 7U));
            dest.write(8U, 15U, src1.read(0U, 7U));
            return;
      }

      void KUNPCKDQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 31U, src2.read(0U, 31U));
            dest.write(32U, 63U, src1.read(0U, 31U));
            return;
      }

      void KUNPCKWD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 15U, src2.read(0U, 15U));
            dest.write(16U, 31U, src1.read(0U, 15U));
            return;
      }

      void KXNORB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 7U, ~(src1.read(0U, 7U) ^ src2.read(0U, 7U)));
            dest.write(8U, dest.bits() - 1U, 0U);
            return;
      }

      void KXNORD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 31U, ~(src1.read(0, 31U) ^ src2.read(0U, 31U)));
            dest.write(32U, dest.bits() - 1U, 0U);
            return;
      }

      void KXNORQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 63U, ~(src1.read(0U, 63U) ^ src2.read(0U, 63U)));
            dest.write(64U, dest.bits() - 1U, 0U);
            return;
      }

      void KXNORW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 15U, ~(src1.read(0U, 15U) ^ src2.read(0U, 15U)));
            dest.write(16U, dest.bits() - 1U, 0U);
            return;
      }

      void KXORB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 7U, src1.read(0U, 7U) ^ src2.read(0U, 7U));
            dest.write(8U, dest.bits() - 1U, 0U);
            return;
      }

      void KXORD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 31U, src1.read(0U, 31U) ^ src2.read(0U, 31U));
            dest.write(32U, dest.bits() - 1U, 0U);
            return;
      }

      void KXORQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 63U, src1.read(0U, 63U) ^ src2.read(0U, 63U));
            dest.write(64U, dest.bits() - 1U, 0U);
            return;
      }

      void KXORW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 15U, src1.read(0U, 15U) ^ src2.read(0U, 15U));
            dest.write(16U, dest.bits() - 1U, 0U);
            return;
      }

      void LAHF(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_AH = (FSF << 7) | (FZF << 6) | (0 << 5) | (FAF << 4) | (0 << 3) | (FPF << 2) | (1 << 1) | FCF;
            return;
      }

      void LAR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LDDQU(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 127U, src.read(0U, 127U));
            return;
      }

      void LDMXCSR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_internal_set(internal::globals::MXCSR, operands.front());
            return;
      }

      void LDS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FLDZ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FLD1(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FLD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LEA(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = operands.back();
            return;
      }

      void LEAVE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LES(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LFENCE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::MEMORY::FENCE::GET, {}, {});
            return;
      }

      void LFS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LGDT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &src = operands.front();
            klura_call(luramas::builtins::DESCRIPTOR::LOAD, {klura_tint(static_cast<std::uint8_t>(internal::data::table_hierarchy::global)), src.read(0U, 15U), src.bits() == 16U ? src.read(16U, 47U) & 0xFFFFFF : src.read(16U, 47U)}, {});
            return;
      }

      void LGS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LIDT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &src = operands.front();
            klura_call(luramas::builtins::INTERRUPT::TABLE::LOAD, {src.read(0U, 15U), src.bits() == 16U ? src.read(16U, 47U) & 0xFFFFFF : src.read(16U, 47U)}, {});
            return;
      }

      void LLDT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::DESCRIPTOR::LOAD, {klura_tint(static_cast<std::uint8_t>(internal::data::table_hierarchy::local)), operands.front()}, {});
            return;
      }

      void LLWPCB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LMSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LOCK(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LODSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            kif(FDF == 0U);
            {
                  REG_RSI += 1U;
            }
            kelse;
            {
                  REG_RSI -= 1U;
            }
            kend;
            return;
      }

      void LODSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            kif(FDF == 0U);
            {
                  REG_RSI += 4U;
            }
            kelse;
            {
                  REG_RSI -= 4U;
            }
            kend;
            return;
      }

      void LODSQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            kif(FDF == 0U);
            {
                  REG_RSI += 8U;
            }
            kelse;
            {
                  REG_RSI -= 8U;
            }
            kend;
            return;
      }

      void LODSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            kif(FDF == 0U);
            {
                  REG_RSI += 2U;
            }
            kelse;
            {
                  REG_RSI -= 2U;
            }
            kend;
            return;
      }

      void LOOP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LOOPE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LOOPNE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RETF(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RETFQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LSL(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LSS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LTR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_internal_set(internal::globals::TASK_REGISTER, operands.front());
            return;
      }

      void LWPINS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LWPVAL(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void LZCNT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            if (const auto bint = simd::get(registrar.inst); !bint.empty()) {
                  registrar.build->make_built_in(bint, operands, F_BUILD_FLAGS);
                  FCF = dest == operands.size();
                  FZF = dest == 0U;
            }
            return;
      }
} // namespace vm

#endif // LURAMAS_TARGET_X86
