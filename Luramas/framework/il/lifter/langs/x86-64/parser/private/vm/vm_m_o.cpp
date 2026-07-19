#ifdef LURAMAS_TARGET_X86
#include "common.hpp"

/* Instruction handlers: MASKMOVDQU - OUTSW */
namespace vm {

      void MASKMOVDQU(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MAXPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            dest.write(0u, 63u, luramas::il::lifter::builder::libraries::math::max(f, dest.read(0u, 63u), src.read(0u, 63u)));
            dest.write(64u, 127u, luramas::il::lifter::builder::libraries::math::max(f, dest.read(64u, 127u), src.read(64u, 127u)));
            return;
      }

      void MAXPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            for (auto i = 0u; i < 128u; i += 32u) {
                  dest.write(i, i + 31u, luramas::il::lifter::builder::libraries::math::max(f, dest.read(i, i + 31u), src.read(i, i + 31u)));
            }
            return;
      }

      void MAXSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            dest.write(0u, 63u, luramas::il::lifter::builder::libraries::math::max(f, dest.read(0u, 63u), src.read(0u, 63u)));
            return;
      }

      void MAXSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            dest.write(0u, 31u, luramas::il::lifter::builder::libraries::math::max(f, dest.read(0u, 31u), src.read(0u, 31u)));
            return;
      }

      void MFENCE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::MEMORY::FENCE::GET, {}, {});
            return;
      }

      void MINPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            dest.write(0u, 63u, luramas::il::lifter::builder::libraries::math::min(f, dest.read(0u, 63u), src.read(0u, 63u)));
            dest.write(64u, 127u, luramas::il::lifter::builder::libraries::math::min(f, dest.read(64u, 127u), src.read(64u, 127u)));
            return;
      }

      void MINPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            for (auto i = 0u; i < 128u; i += 32u) {
                  dest.write(i, i + 31u, luramas::il::lifter::builder::libraries::math::min(f, dest.read(i, i + 31u), src.read(i, i + 31u)));
            }
            return;
      }

      void MINSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            dest.write(0u, 63u, luramas::il::lifter::builder::libraries::math::min(f, dest.read(0u, 63u), src.read(0u, 63u)));
            return;
      }

      void MINSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            dest.write(0u, 31u, luramas::il::lifter::builder::libraries::math::min(f, dest.read(0u, 31u), src.read(0u, 31u)));
            return;
      }

      void CVTPD2PI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CVTPI2PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CVTPI2PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CVTPS2PI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CVTTPD2PI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CVTTPS2PI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void EMMS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_internal_set(internal::globals::x87FPUTagWord, klura_tint(0xFFFF));
            return;
      }

      void MASKMOVQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, src.read(0u, 31u));
            dest.fill(32u, 0u);
            return;
      }

      void MOVQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63u, src.read(0u, 63u));
            dest.fill(64u, 0u);
            return;
      }

      void MOVDQ2Q(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVNTQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVQ2DQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PABSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            for (auto i = 0u; i < 128u; i += 8u) {
                  dest.write(i, i + 7u, luramas::il::lifter::builder::libraries::math::abs(f, src.read(i, i + 7u)));
            }
            return;
      }

      void PABSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            for (auto i = 0u; i < 128u; i += 32u) {
                  dest.write(i, i + 31u, luramas::il::lifter::builder::libraries::math::abs(f, src.read(i, i + 31u)));
            }
            return;
      }

      void PABSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            for (auto i = 0u; i < 128u; i += 16u) {
                  dest.write(i, i + 15u, luramas::il::lifter::builder::libraries::math::abs(f, src.read(i, i + 15u)));
            }
            return;
      }

      void PACKSSDW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PACKSSWB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PACKUSWB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PADDB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            for (auto i = 0u; i < dest.bits(); i += 8u) {
                  dest.write(i, i + 7u, dest.read(i, i + 7u) + src.read(i, i + 7u));
            }
            return;
      }

      void PADDD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            for (auto i = 0u; i < dest.bits(); i += 32u) {
                  dest.write(i, i + 31u, dest.read(i, i + 31u) + src.read(i, i + 31u));
            }
            return;
      }

      void PADDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            for (auto i = 0u; i < dest.bits(); i += 64u) {
                  dest.write(i, i + 63u, dest.read(i, i + 63u) + src.read(i, i + 63u));
            }
            return;
      }

      void PADDSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PADDSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PADDUSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PADDUSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PADDW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            for (auto i = 0u; i < dest.bits(); i += 16u) {
                  dest.write(i, i + 15u, dest.read(i, i + 15u) + src.read(i, i + 15u));
            }
            return;
      }

      void PALIGNR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);

            const auto dest = operands.front();
            const auto src = operands[1u];
            const auto imm = operands.back();

            if (registrar.suggested_bit_set == 64u) {
                  const auto temp = luramas::il::lifter::builder::libraries::structure::concat(f, dest, src) >> (imm * 8u);
                  dest.write(0u, 63u, temp.read(0u, 63));
            } else {
                  const auto temp = (dest.read(0u, 127u) << 128) | src.read(0u, 127u) >> (imm * 8u);
                  dest.write(0u, 127u, temp.read(0u, 127u));
            }
            return;
      }

      void PANDN(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest = (~dest) & src;
            return;
      }

      void PAND(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() &= operands.back();
            return;
      }

      void PAVGB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PAVGW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPEQB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPEQD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPEQW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPGTB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPGTD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PCMPGTW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PEXTRW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PHADDD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PHADDSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PHADDW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PHSUBD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PHSUBSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PHSUBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PINSRW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMADDUBSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMADDWD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto dest = operands.front();
            auto src = operands.back();

            if (dest.bits() == 64) {
                  luramas::il::lifter::builder::cast<64u>(dest, src);
                  dest.write(0u, 31u, (dest.read(0u, 15u) * src.read(0u, 15u)) + (dest.read(16u, 31u) * src.read(16u, 31u)));
                  dest.write(32u, 63u, (dest.read(32u, 47u) * src.read(32u, 47u)) + (dest.read(48u, 63u) * src.read(48u, 63u)));
            } else {
                  luramas::il::lifter::builder::cast<128u>(dest, src);
                  dest.write(0u, 31u, (dest.read(0u, 15u) * src.read(0u, 15u)) + (dest.read(16u, 31u) * src.read(16u, 31u)));
                  dest.write(32u, 63u, (dest.read(32u, 47u) * src.read(32u, 47u)) + (dest.read(48u, 63u) * src.read(48u, 63u)));
                  dest.write(64u, 95u, (dest.read(64u, 79u) * src.read(64u, 79u)) + (dest.read(80u, 95u) * src.read(80u, 95u)));
                  dest.write(96u, 127u, (dest.read(96u, 111u) * src.read(96u, 111u)) + (dest.read(112u, 127u) * src.read(112u, 127u)));
            }
            return;
      }

      void PMAXSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMAXUB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMINSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMINUB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMOVMSKB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest[0u] = src[7u];
            dest[1u] = src[15u];
            dest[2u] = src[23u];
            dest[3u] = src[31u];
            dest[4u] = src[39u];
            dest[5u] = src[47u];
            dest[6u] = src[55u];
            dest[7u] = src[63u];
            dest.write(8u, dest.bits() == 32u ? 31u : 63u, 0u);
            return;
      }

      void PMULHRSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMULHUW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMULHW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMULLW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PMULUDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void POR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() |= operands.back();
            return;
      }

      void PSADBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            if (dest.bits() == 64u) {
                  const auto t0 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(0u, 7u) - src.read(0u, 7u));
                  const auto t1 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(8u, 15u) - src.read(8u, 15u));
                  const auto t2 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(16u, 23u) - src.read(16u, 23u));
                  const auto t3 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(24u, 31u) - src.read(24u, 31u));
                  const auto t4 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(32u, 39u) - src.read(32u, 39u));
                  const auto t5 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(40u, 47u) - src.read(40u, 47u));
                  const auto t6 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(48u, 55u) - src.read(48u, 55u));
                  const auto t7 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(56u, 63u) - src.read(56u, 63u));
                  dest.write(0u, 15u, t0 + t1 + t2 + t3 + t4 + t5 + t6 + t7);
                  dest.write(16u, 63u, 0u);
            } else {
                  const auto t0 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(0u, 7u) - src.read(0u, 7u));
                  const auto t1 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(8u, 15u) - src.read(8u, 15u));
                  const auto t2 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(16u, 23u) - src.read(16u, 23u));
                  const auto t3 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(24u, 31u) - src.read(24u, 31u));
                  const auto t4 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(32u, 39u) - src.read(32u, 39u));
                  const auto t5 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(40u, 47u) - src.read(40u, 47u));
                  const auto t6 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(48u, 55u) - src.read(48u, 55u));
                  const auto t7 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(56u, 63u) - src.read(56u, 63u));
                  const auto t8 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(64u, 71u) - src.read(64u, 71u));
                  const auto t9 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(72u, 79u) - src.read(72u, 79u));
                  const auto t10 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(80u, 87u) - src.read(80u, 87u));
                  const auto t11 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(88u, 95u) - src.read(88u, 95u));
                  const auto t12 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(96u, 103u) - src.read(96u, 103u));
                  const auto t13 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(104u, 111u) - src.read(104u, 111u));
                  const auto t14 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(112u, 119u) - src.read(112u, 119u));
                  const auto t15 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(120u, 127u) - src.read(120u, 127u));
                  dest.write(0u, 15u, t0 + t1 + t2 + t3 + t4 + t5 + t6 + t7);
                  dest.write(16u, 63u, 0u);
                  dest.write(64u, 79u, t8 + t9 + t10 + t11 + t12 + t13 + t14 + t15);
                  dest.write(80u, 127u, 0u);
            }

            return;
      }

      void PSHUFB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            const auto temp = dest;

            for (auto i = 0u; i < dest.bits() / 8u; ++i) {

                  const auto ctrl = src.read(i * 8u, i * 8u + 7u);
                  const auto mask = ctrl[7u];
                  kif(mask == 1u);
                  {
                        dest.write(i * 8u, i * 8u + 7u, 0u);
                  }
                  kend;
                  kif(mask == 0u);
                  {
                        const auto idx = ctrl.read(0u, (dest.bits() == 64u ? 3u : 4u) - 1u);
                        dest.write(i * 8u, i * 8u + 7u, temp.read(idx * 8u, idx * 8u + 7u));
                  }
                  kend;
            }
            return;
      }

      void PSHUFW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands[1];
            const auto order = operands.back();

            dest.write(0u, 15u, ((src >> order.read(0u, 1u)) * 16u).read(0u, 15u));
            dest.write(16u, 31u, ((src >> order.read(2u, 3u)) * 16u).read(0u, 15u));
            dest.write(32u, 47u, ((src >> order.read(4u, 5u)) * 16u).read(0u, 15u));
            dest.write(48u, 63u, ((src >> order.read(6u, 7u)) * 16u).read(0u, 15u));
            return;
      }

      void PSIGNB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSIGND(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSIGNW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSLLD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSLLQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSLLW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSRAD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSRAW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSRLD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto count = operands.back();

            kif(count > 31u);
            {
                  dest.write(0, 63, 0u);
            }
            kelse;
            {
                  dest.write(0u, 31u, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(0u, 31u) >> count, 32u));
                  dest.write(32u, 63u, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(31u, 63u) >> count, 32u));
            }
            kend;
            return;
      }

      void PSRLQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSRLW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto count = operands.back();

            kif(count > 15);
            {
                  dest.write(0, 63, 0u);
            }
            kelse;
            {
                  dest.write(0u, 15u, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(0u, 15u) >> count, 16u));
                  dest.write(16u, 31u, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(16u, 31u) >> count, 16u));
                  dest.write(32u, 47u, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(32u, 47u) >> count, 16u));
                  dest.write(48u, 63u, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(48u, 63u) >> count, 16u));
            }
            kend;
            return;
      }

      void PSUBB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0, 7, (dest.read(0, 7) - src.read(0, 7)));
            dest.write(56, 63, (dest.read(56, 63) - src.read(56, 63)));
            return;
      }

      void PSUBD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0, 31, (dest.read(0, 31) - src.read(0, 31)));
            dest.write(32, 63, (dest.read(32, 63) - src.read(32, 63)));
            return;
      }

      void PSUBQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63u, dest.read(0u, 63u) - src.read(0u, 63u));
            if (dest.bits() != 64u) {
                  dest.write(64u, 127u, dest.read(64u, 127u) - src.read(64u, 127u));
            }
            return;
      }

      void PSUBSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSUBSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSUBUSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            if (dest.bits() == 64u) {
                  dest.write(0u, 7u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(0u, 7u) - src.read(0u, 7u)));
                  dest.write(8u, 15u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(8u, 15u) - src.read(8u, 15u)));
                  dest.write(16u, 23u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(16u, 23u) - src.read(16u, 23u)));
                  dest.write(24u, 31u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(24u, 31u) - src.read(24u, 31u)));
                  dest.write(32u, 39u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(32u, 39u) - src.read(32u, 39u)));
                  dest.write(40u, 47u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(40u, 47u) - src.read(40u, 47u)));
                  dest.write(48u, 55u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(48u, 55u) - src.read(48u, 55u)));
                  dest.write(56u, 63u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(56u, 63u) - src.read(56u, 63u)));
            } else {
                  dest.write(0u, 7u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(0u, 7u) - src.read(0u, 7u)));
                  dest.write(8u, 15u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(8u, 15u) - src.read(8u, 15u)));
                  dest.write(16u, 23u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(16u, 23u) - src.read(16u, 23u)));
                  dest.write(24u, 31u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(24u, 31u) - src.read(24u, 31u)));
                  dest.write(32u, 39u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(32u, 39u) - src.read(32u, 39u)));
                  dest.write(40u, 47u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(40u, 47u) - src.read(40u, 47u)));
                  dest.write(48u, 55u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(48u, 55u) - src.read(48u, 55u)));
                  dest.write(56u, 63u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(56u, 63u) - src.read(56u, 63u)));
                  dest.write(64u, 71u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(64u, 71u) - src.read(64u, 71u)));
                  dest.write(72u, 79u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(72u, 79u) - src.read(72u, 79u)));
                  dest.write(80u, 87u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(80u, 87u) - src.read(80u, 87u)));
                  dest.write(88u, 95u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(88u, 95u) - src.read(88u, 95u)));
                  dest.write(96u, 103u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(96u, 103u) - src.read(96u, 103u)));
                  dest.write(104u, 111u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(104u, 111u) - src.read(104u, 111u)));
                  dest.write(112u, 119u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(112u, 119u) - src.read(112u, 119u)));
                  dest.write(120u, 127u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(120u, 127u) - src.read(120u, 127u)));
            }
            return;
      }

      void PSUBUSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            function_handler f(registrar.build);

            if (dest.bits() == 64u) {
                  dest.write(0u, 7u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(0u, 7u) - src.read(0u, 7u)));
                  dest.write(8u, 15u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(8u, 15u) - src.read(8u, 15u)));
                  dest.write(16u, 23u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(16u, 23u) - src.read(16u, 23u)));
                  dest.write(24u, 31u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(24u, 31u) - src.read(24u, 31u)));
                  dest.write(32u, 39u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(32u, 39u) - src.read(32u, 39u)));
                  dest.write(40u, 47u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(40u, 47u) - src.read(40u, 47u)));
                  dest.write(48u, 55u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(48u, 55u) - src.read(48u, 55u)));
                  dest.write(56u, 63u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(56u, 63u) - src.read(56u, 63u)));
            } else {
                  dest.write(0u, 7u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(0u, 7u) - src.read(0u, 7u)));
                  dest.write(8u, 15u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(8u, 15u) - src.read(8u, 15u)));
                  dest.write(16u, 23u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(16u, 23u) - src.read(16u, 23u)));
                  dest.write(24u, 31u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(24u, 31u) - src.read(24u, 31u)));
                  dest.write(32u, 39u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(32u, 39u) - src.read(32u, 39u)));
                  dest.write(40u, 47u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(40u, 47u) - src.read(40u, 47u)));
                  dest.write(48u, 55u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(48u, 55u) - src.read(48u, 55u)));
                  dest.write(56u, 63u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(56u, 63u) - src.read(56u, 63u)));
                  dest.write(64u, 71u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(64u, 71u) - src.read(64u, 71u)));
                  dest.write(72u, 79u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(72u, 79u) - src.read(72u, 79u)));
                  dest.write(80u, 87u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(80u, 87u) - src.read(80u, 87u)));
                  dest.write(88u, 95u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(88u, 95u) - src.read(88u, 95u)));
                  dest.write(96u, 103u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(96u, 103u) - src.read(96u, 103u)));
                  dest.write(104u, 111u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(104u, 111u) - src.read(104u, 111u)));
                  dest.write(112u, 119u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(112u, 119u) - src.read(112u, 119u)));
                  dest.write(120u, 127u, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(120u, 127u) - src.read(120u, 127u)));
            }
            return;
      }

      void PSUBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0, 15, (dest.read(0, 15) - src.read(0, 15)));
            dest.write(48, 63, (dest.read(48, 63) - src.read(48, 63)));
            return;
      }

      void PUNPCKHBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            const auto width = dest.bits();
            const auto pairs = (width == 64u) ? 4u : 8u;
            const auto offset = (width == 64u) ? 32u : 64u;

            for (auto i = 0u; i < pairs; ++i) {

                  const auto dest_offset = i * 16u;
                  const auto read_offset = offset + i * 8u;

                  dest.write(dest_offset + 0u, dest_offset + 7u, dest.read(read_offset, read_offset + 7u));
                  dest.write(dest_offset + 8u, dest_offset + 15u, src.read(read_offset, read_offset + 7u));
            }
            return;
      }

      void PUNPCKHDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            if (dest.bits() == 64u) {
                  dest.write(0u, 31u, dest.read(32u, 63u));
                  dest.write(32u, 63u, src.read(32u, 63u));
            } else {
                  dest.write(0u, 31u, dest.read(64u, 95u));
                  dest.write(32u, 63u, src.read(64u, 95u));
                  dest.write(64u, 95u, dest.read(96u, 127u));
                  dest.write(96u, 127u, src.read(96u, 127u));
            }
            return;
      }

      void PUNPCKHWD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            const auto width = dest.bits();
            const auto pairs = (width == 64u) ? 2u : 4u;
            const auto offset = (width == 64u) ? 32u : 64u;

            for (auto i = 0u; i < pairs; ++i) {

                  const auto dest_offset = i * 32u;
                  const auto read_offset = offset + i * 16u;

                  dest.write(dest_offset + 0u, dest_offset + 15u, dest.read(read_offset, read_offset + 15u));
                  dest.write(dest_offset + 16u, dest_offset + 31u, src.read(read_offset, read_offset + 15u));
            }
            return;
      }

      void PUNPCKLBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PUNPCKLDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            if (dest.bits() == 64u) {
                  dest.write(32u, 63u, src.read(0u, 31u));
                  dest.write(0u, 31u, dest.read(0u, 31u));
            } else {
                  dest.write(0u, 31u, dest.read(0u, 31u));
                  dest.write(32u, 63u, src.read(0u, 31u));
                  dest.write(64u, 95u, dest.read(32u, 63u));
                  dest.write(96u, 127u, src.read(32u, 63u));
            }
            return;
      }

      void PUNPCKLWD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            if (dest.bits() == 64u) {
                  dest.write(0u, 15u, src.read(0u, 15u));
                  dest.write(16u, 31u, dest.read(0u, 15u));
                  dest.write(32u, 47u, src.read(16u, 31u));
                  dest.write(48u, 63u, dest.read(16u, 31u));
            } else {

                  function_handler f(registrar.build);
                  dest.write(0u, 127u, luramas::il::lifter::builder::libraries::structure::interleave_blocks(f, dest, src, 127u, 16u));
            }
            return;
      }

      void PXOR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() ^= operands.back();
            return;
      }

      void MONITORX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MONITOR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MONTMUL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOV(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = operands.back();
            return;
      }

      void MOVABS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = operands.back();
            return;
      }

      void MOVAPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front().write(0u, 127u, operands.back().read(0u, 127u));
            return;
      }

      void MOVAPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest = src;
            return;
      }

      void MOVBE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            if (dest.bits() == 16u) {
                  dest.write(0u, 7u, src.read(8u, 15u));
                  dest.write(8u, 15u, src.read(0u, 7u));
            } else if (dest.bits() == 32u) {
                  dest.write(0u, 7u, src.read(24u, 31u));
                  dest.write(8u, 15u, src.read(16u, 23u));
                  dest.write(16u, 23u, src.read(8u, 15u));
                  dest.write(24u, 31u, src.read(0u, 7u));
            } else if (dest.bits() == 64u) {
                  dest.write(0u, 7u, src.read(56u, 63u));
                  dest.write(8u, 15u, src.read(48u, 55u));
                  dest.write(16u, 23u, src.read(40u, 47u));
                  dest.write(24u, 31u, src.read(32u, 39u));
                  dest.write(32u, 39u, src.read(24u, 31u));
                  dest.write(40u, 47u, src.read(16u, 23u));
                  dest.write(48u, 55u, src.read(8u, 15u));
                  dest.write(56u, 63u, src.read(0u, 7u));
            }
            return;
      }

      void MOVDDUP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63u, src.read(0u, 63u));
            dest.write(64u, 127u, src.read(0u, 63u));
            return;
      }

      void MOVDIR64B(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVDIRI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVDQA(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest = src;
            return;
      }

      void MOVDQU(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0, 127, src.read(0, 127));
            return;
      }

      void MOVHLPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63u, src.read(64u, 127u));
            return;
      }

      void MOVHPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            MOVHLPS(registrar, operands);
            return;
      }

      void MOVHPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(64u, 127u, src.read(0u, 63u));
            return;
      }

      void MOVLHPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            MOVHPS(registrar, operands);
            return;
      }

      void MOVLPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63u, src.read(0u, 63u));
            return;
      }

      void MOVLPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            MOVLPD(registrar, operands);
            return;
      }

      void MOVMSKPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVMSKPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVNTDQA(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVNTDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVNTI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVNTPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVNTPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest = src;
            return;
      }

      void MOVNTSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVNTSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (registrar.suggested_bit_set == 64u) {

                  kif(FDF == 0u);
                  {
                        ++REG_RSI;
                        ++REG_RDI;
                  }
                  kelse;
                  {
                        --REG_RSI;
                        --REG_RDI;
                  }
                  kend;
            } else {

                  kif(FDF == 0u);
                  {
                        ++REG_ESI;
                        ++REG_EDI;
                  }
                  kelse;
                  {
                        --REG_ESI;
                        --REG_EDI;
                  }
                  kend;
            }
            return;
      }

      void MOVSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (registrar.suggested_bit_set == 64u) {

                  kif(FDF == 0u);
                  {
                        REG_RSI += 4u;
                        REG_RDI += 4u;
                  }
                  kelse;
                  {
                        REG_RSI -= 4u;
                        REG_RDI -= 4u;
                  }
                  kend;
            } else {

                  kif(FDF == 0u);
                  {
                        REG_ESI += 4u;
                        REG_EDI += 4u;
                  }
                  kelse;
                  {
                        REG_ESI -= 4u;
                        REG_EDI -= 4u;
                  }
                  kend;
            }
            return;
      }

      void MOVSHDUP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVSLDUP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MOVSQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (registrar.suggested_bit_set == 64u) {

                  kif(FDF == 0u);
                  {
                        REG_RSI += 8u;
                        REG_RDI += 8u;
                  }
                  kelse;
                  {
                        REG_RSI -= 8u;
                        REG_RDI -= 8u;
                  }
                  kend;
            } else {

                  kif(FDF == 0u);
                  {
                        REG_ESI += 8u;
                        REG_EDI += 8u;
                  }
                  kelse;
                  {
                        REG_ESI -= 8u;
                        REG_EDI -= 8u;
                  }
                  kend;
            }
            return;
      }

      void MOVSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            if (src.is_reg(EXTENSION_XMM) && dest.is_mem()) {
                  dest.write(0, 31, src.read(0, 31));
                  dest.write(32, 127, 0u);
                  return;
            }
            dest.write(0, 31, src.read(0, 31));
            return;
      }

      void MOVSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (registrar.suggested_bit_set == 64u) {

                  kif(FDF == 0u);
                  {
                        REG_RSI += 2u;
                        REG_RDI += 2u;
                  }
                  kelse;
                  {
                        REG_RSI -= 2u;
                        REG_RDI -= 2u;
                  }
                  kend;
            } else {

                  kif(FDF == 0u);
                  {
                        REG_ESI += 2u;
                        REG_EDI += 2u;
                  }
                  kelse;
                  {
                        REG_ESI -= 2u;
                        REG_EDI -= 2u;
                  }
                  kend;
            }
            return;
      }

      void MOVSX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            operands.front() = luramas::il::lifter::builder::libraries::structure::extend_sign(f, operands.back(), operands.back().bits() == 8u ? luramas::types::native::t_int16 : luramas::types::native::t_int32);
            return;
      }

      void MOVSXD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            operands.front() = luramas::il::lifter::builder::libraries::structure::extend_sign(f, operands.back(), luramas::types::native::t_int64);
            return;
      }

      void MOVUPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front().write(0u, 127u, operands.back().read(0u, 127u));
            return;
      }

      void MOVUPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front().write(0u, 127u, operands.back().read(0u, 127u));
            return;
      }

      void MOVZX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto dest = operands.front();
            auto src = operands.back();
            dest = LURAMAS_FBUILD_ZEROEXTEND(dest, src);
            return;
      }

      void MPSADBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            const auto dest = operands.front();
            const auto src = operands[1u];
            const auto imm = operands.back();

            const auto src_offset = imm.read(0u, 1u) * 32u;
            const auto dest_offset = imm[2u] * 32u;

            const auto dest_byte_0 = dest.read(dest_offset + 0u, dest_offset + 7u);
            const auto dest_byte_1 = dest.read(dest_offset + 8u, dest_offset + 15u);
            const auto dest_byte_2 = dest.read(dest_offset + 16u, dest_offset + 23u);
            const auto dest_byte_3 = dest.read(dest_offset + 24u, dest_offset + 31u);
            const auto dest_byte_4 = dest.read(dest_offset + 32u, dest_offset + 39u);
            const auto dest_byte_5 = dest.read(dest_offset + 40u, dest_offset + 47u);
            const auto dest_byte_6 = dest.read(dest_offset + 48u, dest_offset + 55u);
            const auto dest_byte_7 = dest.read(dest_offset + 56u, dest_offset + 63u);
            const auto dest_byte_8 = dest.read(dest_offset + 64u, dest_offset + 71u);
            const auto dest_byte_9 = dest.read(dest_offset + 72u, dest_offset + 79u);
            const auto dest_byte_10 = dest.read(dest_offset + 80u, dest_offset + 87u);

            const auto src_byte_0 = src.read(src_offset + 0u, src_offset + 7u);
            const auto src_byte_1 = src.read(src_offset + 8u, src_offset + 15u);
            const auto src_byte_2 = src.read(src_offset + 16u, src_offset + 23u);
            const auto src_byte_3 = src.read(src_offset + 24u, src_offset + 31u);

            const auto temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_0 - src_byte_0);
            const auto temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_1 - src_byte_1);
            const auto temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_2 - src_byte_2);
            const auto temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_3 - src_byte_3);
            dest.write(0u, 15u, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_1 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_2 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_3 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_4 - src_byte_3);
            dest.write(16u, 31u, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_2 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_3 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_4 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_5 - src_byte_3);
            dest.write(32u, 47u, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_3 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_4 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_5 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_6 - src_byte_3);
            dest.write(48u, 63u, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_4 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_5 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_6 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_7 - src_byte_3);
            dest.write(64u, 79u, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_5 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_6 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_7 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_8 - src_byte_3);
            dest.write(80u, 95u, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_6 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_7 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_8 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_9 - src_byte_3);
            dest.write(96, 111u, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_7 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_8 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_9 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_10 - src_byte_3);
            dest.write(112u, 127u, temp0 + temp1 + temp2 + temp3);
            return;
      }

      void MUL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto src = operands.front();
            switch (src.bits()) {
                  case 16u: {
                        const auto product = REG_AX * src;
                        REG_DX = LURAMAS_FBUILD_UPPER_BITS(product);
                        REG_AX = LURAMAS_FBUILD_LOWER_BITS(product);
                        FCF = REG_DX;
                        FOF = REG_DX;
                        break;
                  }
                  case 32u: {
                        const auto product = REG_EAX * src;
                        REG_EDX = LURAMAS_FBUILD_UPPER_BITS(product);
                        REG_EAX = LURAMAS_FBUILD_LOWER_BITS(product);
                        FCF = REG_EDX;
                        FOF = REG_EDX;
                        break;
                  }
                  case 64: {
                        const auto product = REG_RDX * src;
                        REG_RDX = LURAMAS_FBUILD_UPPER_BITS(product);
                        REG_RAX = LURAMAS_FBUILD_LOWER_BITS(product);
                        FCF = REG_RDX;
                        FOF = REG_RDX;
                        break;
                  }
                  default: {
                        REG_AX = REG_AL * src;
                        const auto UPPER = LURAMAS_FBUILD_UPPER_BITS(REG_AX);
                        FCF = UPPER;
                        FOF = UPPER;
                        break;
                  }
            }
            return;
      }

      void MULPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MULPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, dest.read(0u, 31) * src.read(0u, 31));
            dest.write(32u, 63u, dest.read(32u, 63u) * src.read(32u, 63u));
            dest.write(64u, 95u, dest.read(64u, 95u) * src.read(64u, 95u));
            dest.write(96u, 127u, dest.read(96u, 127u) * src.read(96u, 127u));
            return;
      }

      void MULSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63, dest.read(0u, 63) * src.read(0u, 63));
            return;
      }

      void MULSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, dest.read(0u, 31) * src.read(0u, 31u));
            return;
      }

      void MULX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest1 = operands.front();
            const auto dest2 = operands[1u];
            const auto src1 = operands[2u];
            const auto src2 = operands.back();

            if (registrar.suggested_bit_set == 32u) {
                  src1 = REG_EDX;
                  const auto product = src1 * src2;
                  dest1 = product.read(0, 31);
                  dest2 = product.read(32, 63);
            } else {
                  src1 = REG_RDX;
                  const auto product = src1 * src2;
                  dest1 = product.read(0, 63);
                  dest2 = product.read(64, 127);
            }
            return;
      }

      void FMUL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FIMUL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FMULP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MWAITX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void MWAIT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void NEG(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();

            const auto temp = -dest;
            FCF = dest != 0u;
            tools::eflags::mutate<F_COMMON_NO_CF>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp));
            dest = temp;
            return;
      }

      void NOP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            registrar.build->make<luramas::il::arch::opcodes::OP_NOP>();
            return;
      }

      void NOT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = ~operands.front();
            return;
      }

      void OR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            const auto temp = dest | src;
            tools::eflags::mutate<xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            dest = temp;
            FOF = 0u;
            FCF = 0u;
            return;
      }

      void ORPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src1 = operands[1u];
            const auto src2 = operands.back();

            dest.write(0, 63, src1.read(0, 63) | src2.read(0, 63));
            dest.write(64, 127, src1.read(64, 127) | src2.read(64, 127));
            return;
      }

      void ORPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, dest.read(0u, 31) | src.read(0u, 31));
            dest.write(32u, 63u, dest.read(32u, 63u) | src.read(32u, 63u));
            dest.write(64u, 95u, dest.read(64u, 95u) | src.read(64u, 95u));
            dest.write(96u, 127u, dest.read(96u, 127u) | src.read(96u, 127u));
            return;
      }

      void OUT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto port = operands.front();
            const auto value = operands.back();

            klura_call(luramas::builtins::IO::INPUT, {value, klura_tint(0u), port});
            return;
      }

      void OUTSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::IO::INPUT, {REG_SIL, klura_tint(0u), REG_DX});
            return;
      }

      void OUTSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::IO::INPUT, {REG_ESI, klura_tint(0u), REG_DX});
            return;
      }

      void OUTSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::IO::INPUT, {REG_SI, klura_tint(0u), REG_DX});
            return;
      }
} // namespace vm

#endif // LURAMAS_TARGET_X86
