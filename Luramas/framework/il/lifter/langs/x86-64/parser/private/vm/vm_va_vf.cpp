#ifdef LURAMAS_TARGET_X86
#include "common.hpp"

/* Instruction handlers: V4FMADDPS - VFRCZSS */
namespace vm {

      void V4FMADDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void V4FMADDSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void V4FNMADDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void V4FNMADDSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VADDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VADDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VADDSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VADDSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VADDSUBPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto DEST = operands.front();
            const auto SRC1 = operands[1u];
            const auto SRC2 = operands.back();
            switch (DEST.bits()) {
                  case 128u: {
                        DEST.write(0u, 63u, SRC1.read(0u, 63u) - SRC2.read(0u, 63u));
                        DEST.write(64u, 127u, SRC1.read(64u, 127u) + SRC2.read(64u, 127u));
                        DEST.write(128u, registrar.hw_constants.MAXVL - 1u, 0u);
                        break;
                  }
                  case 256u: {
                        DEST.write(0u, 63u, SRC1.read(0u, 63u) - SRC2.read(0u, 63u));
                        DEST.write(64u, 127u, SRC1.read(64u, 127u) + SRC2.read(64u, 127u));
                        DEST.write(128u, 191u, SRC1.read(128u, 191u) - SRC2.read(128u, 191u));
                        DEST.write(192u, 255u, SRC1.read(192u, 255u) + SRC2.read(192u, 255u));
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return;
      }

      void VADDSUBPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto DEST = operands.front();
            const auto SRC1 = operands[1u];
            const auto SRC2 = operands.back();
            switch (DEST.bits()) {
                  case 128u: {
                        DEST.write(0u, 31u, SRC1.read(0u, 31u) - SRC2.read(0u, 31u));
                        DEST.write(32u, 63u, SRC1.read(32u, 63u) + SRC2.read(32u, 63u));
                        DEST.write(64u, 95u, SRC1.read(64u, 95u) - SRC2.read(64u, 95u));
                        DEST.write(96u, 127u, SRC1.read(96u, 127u) + SRC2.read(96u, 127u));
                        DEST.write(128u, registrar.hw_constants.MAXVL - 1u, 0u);
                        break;
                  }
                  case 256u: {
                        DEST.write(0u, 31u, SRC1.read(0u, 31u) - SRC2.read(0u, 31u));
                        DEST.write(32u, 63u, SRC1.read(32u, 63u) + SRC2.read(32u, 63u));
                        DEST.write(64u, 95u, SRC1.read(64u, 95u) - SRC2.read(64u, 95u));
                        DEST.write(96u, 127u, SRC1.read(96u, 127u) + SRC2.read(96u, 127u));
                        DEST.write(128u, 159u, SRC1.read(128u, 159u) - SRC2.read(128u, 159u));
                        DEST.write(160u, 191u, SRC1.read(160u, 191u) + SRC2.read(160u, 191u));
                        DEST.write(192u, 223u, SRC1.read(192u, 223u) - SRC2.read(192u, 223u));
                        DEST.write(224u, 255u, SRC1.read(224u, 255u) + SRC2.read(224u, 255u));
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return;
      }

      void VAESDECLAST(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VAESDEC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VAESENCLAST(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VAESENC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VAESIMC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VAESKEYGENASSIST(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VALIGND(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VALIGNQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VANDNPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VANDNPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VANDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VANDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBLENDMPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBLENDMPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBLENDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBLENDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBLENDVPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBLENDVPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTF128(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto DEST = operands.front();
            const auto SRC = operands.back();
            const auto temp = SRC.read(0u, 127u);
            DEST.write(0u, 127u, temp);
            DEST.write(128u, 255u, temp);
            DEST.write(256u, registrar.hw_constants.MAXVL - 1u, 0u);
            return;
      }

      void VBROADCASTF32X2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTF32X4(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTF32X8(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTF64X2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTF64X4(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTI128(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTI32X2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTI32X4(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTI32X8(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTI64X2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTI64X4(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VBROADCASTSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCMP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCMPPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCMPPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCMPSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCMPSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCOMISD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCOMISS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCOMPRESSPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCOMPRESSPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTDQ2PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTDQ2PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPD2DQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPD2PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPD2QQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPD2UDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPD2UQQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPH2PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPS2DQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPS2PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPS2PH(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPS2QQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPS2UDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTPS2UQQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTQQ2PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTQQ2PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTSD2SI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTSD2SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTSD2USI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTSI2SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTSI2SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTSS2SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTSS2SI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTSS2USI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTPD2DQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTPD2QQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTPD2UDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTPD2UQQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTPS2DQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTPS2QQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTPS2UDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTPS2UQQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTSD2SI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTSD2USI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTSS2SI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTTSS2USI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTUDQ2PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTUDQ2PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTUQQ2PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTUQQ2PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTUSI2SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VCVTUSI2SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VDBPSADBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VDIVPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VDIVPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VDIVSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VDIVSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VDPPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VDPPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VERR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VERW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXP2PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXP2PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXPANDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXPANDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXTRACTF128(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXTRACTF32X4(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXTRACTF32X8(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXTRACTF64X2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXTRACTF64X4(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXTRACTI128(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXTRACTI32X4(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXTRACTI32X8(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXTRACTI64X2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXTRACTI64X4(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VEXTRACTPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFIXUPIMMPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFIXUPIMMPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFIXUPIMMSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFIXUPIMMSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD132PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD132PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD132SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD132SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD213PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD213PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD213SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD213SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD231PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD231PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD231SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADD231SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDSUB132PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDSUB132PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDSUB213PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDSUB213PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDSUB231PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDSUB231PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDSUBPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMADDSUBPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB132PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB132PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB132SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB132SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB213PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB213PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB213SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB213SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB231PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB231PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB231SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUB231SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBADD132PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBADD132PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBADD213PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBADD213PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBADD231PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBADD231PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBADDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBADDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFMSUBSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD132PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD132PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD132SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD132SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD213PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD213PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD213SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD213SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD231PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD231PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD231SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADD231SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADDSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMADDSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB132PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB132PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB132SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB132SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB213PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB213PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB213SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB213SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB231PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB231PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB231SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUB231SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUBPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUBPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUBSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFNMSUBSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFPCLASSPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFPCLASSPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFPCLASSSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFPCLASSSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFRCZPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFRCZPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFRCZSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void VFRCZSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }
} // namespace vm

#endif // LURAMAS_TARGET_X86
