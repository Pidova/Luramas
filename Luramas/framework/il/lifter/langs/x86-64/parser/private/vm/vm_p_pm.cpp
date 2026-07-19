#ifdef LURAMAS_TARGET_X86
#include "common.hpp"

/* Instruction handlers: PACKUSDW - PMULLD */
namespace vm {

      void PACKUSDW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PAUSE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::HINTER::CONTEXT_SWITCH, {}, {});
            return;
      }

      void PAVGUSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PBLENDVB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PBLENDW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCLMULQDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPEQQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPESTRI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPESTRM(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPGTQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPISTRI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPISTRM(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCONFIG(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PDEP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto temp = operands[1u];
            const auto mask = operands.back();

            dest = 0u;
            auto m = 0u;
            auto k = 0u;
            while (m < dest.bits()) {
                  kif(mask[m] == 1u);
                  {
                        dest[m] = temp[k];
                        ++k;
                  }
                  kend;
                  ++m;
            }
            return;
      }

      void PEXT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto temp = operands[1u];
            const auto mask = operands.back();
            dest = 0u;
            auto m = 0u;
            auto k = 0u;
            while (m < dest.bits()) {
                  kif(mask[m] == 1u);
                  {
                        dest[k] = temp[m];
                        ++k;
                  }
                  kend;
                  ++m;
            }
            return;
      }

      void PEXTRB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PEXTRD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PEXTRQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PF2ID(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PF2IW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFACC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFADD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest += src;
            return;
      }

      void PFCMPEQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFCMPGE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFCMPGT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFMAX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFMIN(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFMUL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest *= src;
            return;
      }

      void PFNACC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, dest.read(0u, 31u) - dest.read(32u, 63u));
            dest.write(32u, 63u, src.read(0u, 31u) - src.read(32u, 63u));
            return;
      }

      void PFPNACC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, dest.read(0u, 31u) - dest.read(32u, 63u));
            dest.write(32u, 63u, src.read(0u, 31u) + src.read(32u, 63u));
            return;
      }

      void PFRCPIT1(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFRCPIT2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFRCP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFRSQIT1(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFRSQRT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PFSUBR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest = src - dest;
            return;
      }

      void PFSUB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest -= src;
            return;
      }

      void PHMINPOSUW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            auto index = klura_vtemp;
            index = 0u;
            auto min = src.read(0u, 15u);
            kif(src.read(16u, 31u) < min) {
                  index = 1u;
                  min = src.read(16u, 31u);
            }
            kend;
            kif(src.read(32u, 47u) < min) {
                  index = 2u;
                  min = src.read(32u, 47u);
            }
            kend;
            kif(src.read(48u, 63u) < min) {
                  index = 3u;
                  min = src.read(48u, 63u);
            }
            kend;
            kif(src.read(64u, 79u) < min) {
                  index = 4u;
                  min = src.read(64u, 79u);
            }
            kend;
            kif(src.read(80u, 95u) < min) {
                  index = 5u;
                  min = src.read(80u, 95u);
            }
            kend;
            kif(src.read(96u, 111u) < min) {
                  index = 6u;
                  min = src.read(96u, 111u);
            }
            kend;
            kif(src.read(112u, 127u) < min) {
                  index = 7u;
                  min = src.read(112u, 127u);
            }
            kend;
            dest.write(0u, 15u, min);
            dest.write(16u, 18u, index);
            dest.write(19u, 127u, 0u);
            return;
      }

      void PI2FD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PI2FW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PINSRB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PINSRD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PINSRQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMAXSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMAXSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMAXUD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMAXUW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMINSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMINSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMINUD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMINUW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVSXBD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVSXBQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVSXBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVSXDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVSXWD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVSXWQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVZXBD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVZXBQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVZXBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVZXDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVZXWD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVZXWQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMULDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMULHRW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMULLD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

} // namespace vm

#endif // LURAMAS_TARGET_X86
