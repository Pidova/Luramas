#ifdef LURAMAS_TARGET_X86
#include "common.hpp"

/* Instruction handlers: MASKMOVDQU - OUTSW */
namespace vm {

      void MASKMOVDQU(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MAXPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            dest.write(0U, 63U, luramas::il::lifter::builder::libraries::math::max(f, dest.read(0U, 63U), src.read(0U, 63U)));
            dest.write(64U, 127U, luramas::il::lifter::builder::libraries::math::max(f, dest.read(64U, 127U), src.read(64U, 127U)));
            return;
      }

      void MAXPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            for (auto i = 0U; i < 128U; i += 32U) {
                  dest.write(i, i + 31U, luramas::il::lifter::builder::libraries::math::max(f, dest.read(i, i + 31U), src.read(i, i + 31U)));
            }
            return;
      }

      void MAXSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            dest.write(0U, 63U, luramas::il::lifter::builder::libraries::math::max(f, dest.read(0U, 63U), src.read(0U, 63U)));
            return;
      }

      void MAXSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            dest.write(0U, 31U, luramas::il::lifter::builder::libraries::math::max(f, dest.read(0U, 31U), src.read(0U, 31U)));
            return;
      }

      void MFENCE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::MEMORY::FENCE::GET, {}, {});
            return;
      }

      void MINPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            dest.write(0U, 63U, luramas::il::lifter::builder::libraries::math::min(f, dest.read(0U, 63U), src.read(0U, 63U)));
            dest.write(64U, 127U, luramas::il::lifter::builder::libraries::math::min(f, dest.read(64U, 127U), src.read(64U, 127U)));
            return;
      }

      void MINPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            for (auto i = 0U; i < 128U; i += 32U) {
                  dest.write(i, i + 31U, luramas::il::lifter::builder::libraries::math::min(f, dest.read(i, i + 31U), src.read(i, i + 31U)));
            }
            return;
      }

      void MINSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            dest.write(0U, 63U, luramas::il::lifter::builder::libraries::math::min(f, dest.read(0U, 63U), src.read(0U, 63U)));
            return;
      }

      void MINSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            dest.write(0U, 31U, luramas::il::lifter::builder::libraries::math::min(f, dest.read(0U, 31U), src.read(0U, 31U)));
            return;
      }

      void CVTPD2PI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CVTPI2PD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CVTPI2PS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CVTPS2PI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CVTTPD2PI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CVTTPS2PI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void EMMS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_internal_set(internal::globals::x87FPUTagWord, klura_tint(0xFFFF));
            return;
      }

      void MASKMOVQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, src.read(0U, 31U));
            dest.fill(32U, 0U);
            return;
      }

      void MOVQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63U, src.read(0U, 63U));
            dest.fill(64U, 0U);
            return;
      }

      void MOVDQ2Q(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVNTQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVQ2DQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PABSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            for (auto i = 0U; i < 128U; i += 8U) {
                  dest.write(i, i + 7U, luramas::il::lifter::builder::libraries::math::abs(f, src.read(i, i + 7U)));
            }
            return;
      }

      void PABSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            for (auto i = 0U; i < 128U; i += 32U) {
                  dest.write(i, i + 31U, luramas::il::lifter::builder::libraries::math::abs(f, src.read(i, i + 31U)));
            }
            return;
      }

      void PABSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            for (auto i = 0U; i < 128U; i += 16U) {
                  dest.write(i, i + 15U, luramas::il::lifter::builder::libraries::math::abs(f, src.read(i, i + 15U)));
            }
            return;
      }

      void PACKSSDW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PACKSSWB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PACKUSWB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PADDB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            for (auto i = 0U; i < dest.bits(); i += 8U) {
                  dest.write(i, i + 7U, dest.read(i, i + 7U) + src.read(i, i + 7U));
            }
            return;
      }

      void PADDD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            for (auto i = 0U; i < dest.bits(); i += 32U) {
                  dest.write(i, i + 31U, dest.read(i, i + 31U) + src.read(i, i + 31U));
            }
            return;
      }

      void PADDQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            for (auto i = 0U; i < dest.bits(); i += 64U) {
                  dest.write(i, i + 63U, dest.read(i, i + 63U) + src.read(i, i + 63U));
            }
            return;
      }

      void PADDSB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PADDSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PADDUSB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PADDUSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PADDW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            for (auto i = 0U; i < dest.bits(); i += 16U) {
                  dest.write(i, i + 15U, dest.read(i, i + 15U) + src.read(i, i + 15U));
            }
            return;
      }

      void PALIGNR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);

            const auto &dest = operands.front();
            const auto &src = operands[1U];
            const auto &imm = operands.back();

            if (registrar.hw_constants.instruction_interp == 64U) {
                  const auto temp = luramas::il::lifter::builder::libraries::structure::concat(f, dest, src) >> (imm * 8U);
                  dest.write(0U, 63U, temp.read(0U, 63));
            } else {
                  const auto temp = (dest.read(0U, 127U) << 128) | src.read(0U, 127U) >> (imm * 8U);
                  dest.write(0U, 127U, temp.read(0U, 127U));
            }
            return;
      }

      void PANDN(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest = (~dest) & src;
            return;
      }

      void PAND(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() &= operands.back();
            return;
      }

      void PAVGB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PAVGW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PCMPEQB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PCMPEQD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PCMPEQW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PCMPGTB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PCMPGTD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PCMPGTW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PEXTRW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PHADDD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PHADDSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PHADDW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PHSUBD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PHSUBSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PHSUBW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PINSRW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PMADDUBSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PMADDWD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto dest = operands.front();
            auto src = operands.back();

            if (dest.bits() == 64) {
                  luramas::il::lifter::builder::cast<64U>(dest, src);
                  dest.write(0U, 31U, (dest.read(0U, 15U) * src.read(0U, 15U)) + (dest.read(16U, 31U) * src.read(16U, 31U)));
                  dest.write(32U, 63U, (dest.read(32U, 47U) * src.read(32U, 47U)) + (dest.read(48U, 63U) * src.read(48U, 63U)));
            } else {
                  luramas::il::lifter::builder::cast<128U>(dest, src);
                  dest.write(0U, 31U, (dest.read(0U, 15U) * src.read(0U, 15U)) + (dest.read(16U, 31U) * src.read(16U, 31U)));
                  dest.write(32U, 63U, (dest.read(32U, 47U) * src.read(32U, 47U)) + (dest.read(48U, 63U) * src.read(48U, 63U)));
                  dest.write(64U, 95U, (dest.read(64U, 79U) * src.read(64U, 79U)) + (dest.read(80U, 95U) * src.read(80U, 95U)));
                  dest.write(96U, 127U, (dest.read(96U, 111U) * src.read(96U, 111U)) + (dest.read(112U, 127U) * src.read(112U, 127U)));
            }
            return;
      }

      void PMAXSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PMAXUB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PMINSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PMINUB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PMOVMSKB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest[0U] = src[7U];
            dest[1U] = src[15U];
            dest[2U] = src[23U];
            dest[3U] = src[31U];
            dest[4U] = src[39U];
            dest[5U] = src[47U];
            dest[6U] = src[55U];
            dest[7U] = src[63U];
            dest.write(8U, dest.bits() == 32U ? 31U : 63U, 0U);
            return;
      }

      void PMULHRSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PMULHUW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PMULHW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PMULLW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PMULUDQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void POR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() |= operands.back();
            return;
      }

      void PSADBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            if (dest.bits() == 64U) {
                  const auto t0 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(0U, 7U) - src.read(0U, 7U));
                  const auto t1 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(8U, 15U) - src.read(8U, 15U));
                  const auto t2 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(16U, 23U) - src.read(16U, 23U));
                  const auto t3 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(24U, 31U) - src.read(24U, 31U));
                  const auto t4 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(32U, 39U) - src.read(32U, 39U));
                  const auto t5 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(40U, 47U) - src.read(40U, 47U));
                  const auto t6 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(48U, 55U) - src.read(48U, 55U));
                  const auto t7 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(56U, 63U) - src.read(56U, 63U));
                  dest.write(0U, 15U, t0 + t1 + t2 + t3 + t4 + t5 + t6 + t7);
                  dest.write(16U, 63U, 0U);
            } else {
                  const auto t0 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(0U, 7U) - src.read(0U, 7U));
                  const auto t1 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(8U, 15U) - src.read(8U, 15U));
                  const auto t2 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(16U, 23U) - src.read(16U, 23U));
                  const auto t3 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(24U, 31U) - src.read(24U, 31U));
                  const auto t4 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(32U, 39U) - src.read(32U, 39U));
                  const auto t5 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(40U, 47U) - src.read(40U, 47U));
                  const auto t6 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(48U, 55U) - src.read(48U, 55U));
                  const auto t7 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(56U, 63U) - src.read(56U, 63U));
                  const auto t8 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(64U, 71U) - src.read(64U, 71U));
                  const auto t9 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(72U, 79U) - src.read(72U, 79U));
                  const auto t10 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(80U, 87U) - src.read(80U, 87U));
                  const auto t11 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(88U, 95U) - src.read(88U, 95U));
                  const auto t12 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(96U, 103U) - src.read(96U, 103U));
                  const auto t13 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(104U, 111U) - src.read(104U, 111U));
                  const auto t14 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(112U, 119U) - src.read(112U, 119U));
                  const auto t15 = luramas::il::lifter::builder::libraries::math::abs(f, dest.read(120U, 127U) - src.read(120U, 127U));
                  dest.write(0U, 15U, t0 + t1 + t2 + t3 + t4 + t5 + t6 + t7);
                  dest.write(16U, 63U, 0U);
                  dest.write(64U, 79U, t8 + t9 + t10 + t11 + t12 + t13 + t14 + t15);
                  dest.write(80U, 127U, 0U);
            }

            return;
      }

      void PSHUFB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            const auto &temp = dest;

            for (auto i = 0U; i < dest.bits() / 8U; ++i) {

                  const auto ctrl = src.read(i * 8U, (i * 8U) + 7U);
                  const auto mask = ctrl[7U];
                  kif(mask == 1U);
                  {
                        dest.write(i * 8U, (i * 8U) + 7U, 0U);
                  }
                  kend;
                  kif(mask == 0U);
                  {
                        const auto idx = ctrl.read(0U, (dest.bits() == 64U ? 3U : 4U) - 1U);
                        dest.write(i * 8U, (i * 8U) + 7U, temp.read(idx * 8U, idx * 8U + 7U));
                  }
                  kend;
            }
            return;
      }

      void PSHUFW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands[1];
            const auto &order = operands.back();

            dest.write(0U, 15U, ((src >> order.read(0U, 1U)) * 16U).read(0U, 15U));
            dest.write(16U, 31U, ((src >> order.read(2U, 3U)) * 16U).read(0U, 15U));
            dest.write(32U, 47U, ((src >> order.read(4U, 5U)) * 16U).read(0U, 15U));
            dest.write(48U, 63U, ((src >> order.read(6U, 7U)) * 16U).read(0U, 15U));
            return;
      }

      void PSIGNB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSIGND(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSIGNW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSLLD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSLLQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSLLW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSRAD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSRAW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSRLD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &count = operands.back();

            kif(count > 31U);
            {
                  dest.write(0, 63, 0U);
            }
            kelse;
            {
                  dest.write(0U, 31U, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(0U, 31U) >> count, 32U));
                  dest.write(32U, 63U, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(31U, 63U) >> count, 32U));
            }
            kend;
            return;
      }

      void PSRLQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSRLW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &count = operands.back();

            kif(count > 15);
            {
                  dest.write(0, 63, 0U);
            }
            kelse;
            {
                  dest.write(0U, 15U, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(0U, 15U) >> count, 16U));
                  dest.write(16U, 31U, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(16U, 31U) >> count, 16U));
                  dest.write(32U, 47U, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(32U, 47U) >> count, 16U));
                  dest.write(48U, 63U, luramas::il::lifter::builder::libraries::structure::zero_extend(dest.read(48U, 63U) >> count, 16U));
            }
            kend;
            return;
      }

      void PSUBB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0, 7, (dest.read(0, 7) - src.read(0, 7)));
            dest.write(56, 63, (dest.read(56, 63) - src.read(56, 63)));
            return;
      }

      void PSUBD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0, 31, (dest.read(0, 31) - src.read(0, 31)));
            dest.write(32, 63, (dest.read(32, 63) - src.read(32, 63)));
            return;
      }

      void PSUBQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63U, dest.read(0U, 63U) - src.read(0U, 63U));
            if (dest.bits() != 64U) {
                  dest.write(64U, 127U, dest.read(64U, 127U) - src.read(64U, 127U));
            }
            return;
      }

      void PSUBSB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSUBSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSUBUSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            if (dest.bits() == 64U) {
                  dest.write(0U, 7U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(0U, 7U) - src.read(0U, 7U)));
                  dest.write(8U, 15U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(8U, 15U) - src.read(8U, 15U)));
                  dest.write(16U, 23U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(16U, 23U) - src.read(16U, 23U)));
                  dest.write(24U, 31U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(24U, 31U) - src.read(24U, 31U)));
                  dest.write(32U, 39U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(32U, 39U) - src.read(32U, 39U)));
                  dest.write(40U, 47U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(40U, 47U) - src.read(40U, 47U)));
                  dest.write(48U, 55U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(48U, 55U) - src.read(48U, 55U)));
                  dest.write(56U, 63U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(56U, 63U) - src.read(56U, 63U)));
            } else {
                  dest.write(0U, 7U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(0U, 7U) - src.read(0U, 7U)));
                  dest.write(8U, 15U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(8U, 15U) - src.read(8U, 15U)));
                  dest.write(16U, 23U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(16U, 23U) - src.read(16U, 23U)));
                  dest.write(24U, 31U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(24U, 31U) - src.read(24U, 31U)));
                  dest.write(32U, 39U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(32U, 39U) - src.read(32U, 39U)));
                  dest.write(40U, 47U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(40U, 47U) - src.read(40U, 47U)));
                  dest.write(48U, 55U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(48U, 55U) - src.read(48U, 55U)));
                  dest.write(56U, 63U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(56U, 63U) - src.read(56U, 63U)));
                  dest.write(64U, 71U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(64U, 71U) - src.read(64U, 71U)));
                  dest.write(72U, 79U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(72U, 79U) - src.read(72U, 79U)));
                  dest.write(80U, 87U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(80U, 87U) - src.read(80U, 87U)));
                  dest.write(88U, 95U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(88U, 95U) - src.read(88U, 95U)));
                  dest.write(96U, 103U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(96U, 103U) - src.read(96U, 103U)));
                  dest.write(104U, 111U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(104U, 111U) - src.read(104U, 111U)));
                  dest.write(112U, 119U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(112U, 119U) - src.read(112U, 119U)));
                  dest.write(120U, 127U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_byte(f, dest.read(120U, 127U) - src.read(120U, 127U)));
            }
            return;
      }

      void PSUBUSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            function_handler f(registrar.build);

            if (dest.bits() == 64U) {
                  dest.write(0U, 7U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(0U, 7U) - src.read(0U, 7U)));
                  dest.write(8U, 15U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(8U, 15U) - src.read(8U, 15U)));
                  dest.write(16U, 23U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(16U, 23U) - src.read(16U, 23U)));
                  dest.write(24U, 31U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(24U, 31U) - src.read(24U, 31U)));
                  dest.write(32U, 39U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(32U, 39U) - src.read(32U, 39U)));
                  dest.write(40U, 47U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(40U, 47U) - src.read(40U, 47U)));
                  dest.write(48U, 55U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(48U, 55U) - src.read(48U, 55U)));
                  dest.write(56U, 63U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(56U, 63U) - src.read(56U, 63U)));
            } else {
                  dest.write(0U, 7U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(0U, 7U) - src.read(0U, 7U)));
                  dest.write(8U, 15U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(8U, 15U) - src.read(8U, 15U)));
                  dest.write(16U, 23U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(16U, 23U) - src.read(16U, 23U)));
                  dest.write(24U, 31U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(24U, 31U) - src.read(24U, 31U)));
                  dest.write(32U, 39U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(32U, 39U) - src.read(32U, 39U)));
                  dest.write(40U, 47U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(40U, 47U) - src.read(40U, 47U)));
                  dest.write(48U, 55U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(48U, 55U) - src.read(48U, 55U)));
                  dest.write(56U, 63U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(56U, 63U) - src.read(56U, 63U)));
                  dest.write(64U, 71U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(64U, 71U) - src.read(64U, 71U)));
                  dest.write(72U, 79U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(72U, 79U) - src.read(72U, 79U)));
                  dest.write(80U, 87U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(80U, 87U) - src.read(80U, 87U)));
                  dest.write(88U, 95U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(88U, 95U) - src.read(88U, 95U)));
                  dest.write(96U, 103U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(96U, 103U) - src.read(96U, 103U)));
                  dest.write(104U, 111U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(104U, 111U) - src.read(104U, 111U)));
                  dest.write(112U, 119U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(112U, 119U) - src.read(112U, 119U)));
                  dest.write(120U, 127U, luramas::il::lifter::builder::libraries::structure::saturate_to_unsigned_word(f, dest.read(120U, 127U) - src.read(120U, 127U)));
            }
            return;
      }

      void PSUBW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0, 15, (dest.read(0, 15) - src.read(0, 15)));
            dest.write(48, 63, (dest.read(48, 63) - src.read(48, 63)));
            return;
      }

      void PUNPCKHBW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto width = dest.bits();
            const auto pairs = (width == 64U) ? 4U : 8U;
            const auto offset = (width == 64U) ? 32U : 64U;

            for (auto i = 0U; i < pairs; ++i) {

                  const auto dest_offset = i * 16U;
                  const auto read_offset = offset + (i * 8U);

                  dest.write(dest_offset + 0U, dest_offset + 7U, dest.read(read_offset, read_offset + 7U));
                  dest.write(dest_offset + 8U, dest_offset + 15U, src.read(read_offset, read_offset + 7U));
            }
            return;
      }

      void PUNPCKHDQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            if (dest.bits() == 64U) {
                  dest.write(0U, 31U, dest.read(32U, 63U));
                  dest.write(32U, 63U, src.read(32U, 63U));
            } else {
                  dest.write(0U, 31U, dest.read(64U, 95U));
                  dest.write(32U, 63U, src.read(64U, 95U));
                  dest.write(64U, 95U, dest.read(96U, 127U));
                  dest.write(96U, 127U, src.read(96U, 127U));
            }
            return;
      }

      void PUNPCKHWD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto width = dest.bits();
            const auto pairs = (width == 64U) ? 2U : 4U;
            const auto offset = (width == 64U) ? 32U : 64U;

            for (auto i = 0U; i < pairs; ++i) {

                  const auto dest_offset = i * 32U;
                  const auto read_offset = offset + (i * 16U);

                  dest.write(dest_offset + 0U, dest_offset + 15U, dest.read(read_offset, read_offset + 15U));
                  dest.write(dest_offset + 16U, dest_offset + 31U, src.read(read_offset, read_offset + 15U));
            }
            return;
      }

      void PUNPCKLBW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PUNPCKLDQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            if (dest.bits() == 64U) {
                  dest.write(32U, 63U, src.read(0U, 31U));
                  dest.write(0U, 31U, dest.read(0U, 31U));
            } else {
                  dest.write(0U, 31U, dest.read(0U, 31U));
                  dest.write(32U, 63U, src.read(0U, 31U));
                  dest.write(64U, 95U, dest.read(32U, 63U));
                  dest.write(96U, 127U, src.read(32U, 63U));
            }
            return;
      }

      void PUNPCKLWD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            if (dest.bits() == 64U) {
                  dest.write(0U, 15U, src.read(0U, 15U));
                  dest.write(16U, 31U, dest.read(0U, 15U));
                  dest.write(32U, 47U, src.read(16U, 31U));
                  dest.write(48U, 63U, dest.read(16U, 31U));
            } else {

                  function_handler f(registrar.build);
                  dest.write(0U, 127U, luramas::il::lifter::builder::libraries::structure::interleave_blocks(f, dest, src, 127U, 16U));
            }
            return;
      }

      void PXOR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() ^= operands.back();
            return;
      }

      void MONITORX(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MONITOR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MONTMUL(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOV(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = operands.back();
            return;
      }

      void MOVABS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = operands.back();
            return;
      }

      void MOVAPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front().write(0U, 127U, operands.back().read(0U, 127U));
            return;
      }

      void MOVAPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest = src;
            return;
      }

      void MOVBE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            if (dest.bits() == 16U) {
                  dest.write(0U, 7U, src.read(8U, 15U));
                  dest.write(8U, 15U, src.read(0U, 7U));
            } else if (dest.bits() == 32U) {
                  dest.write(0U, 7U, src.read(24U, 31U));
                  dest.write(8U, 15U, src.read(16U, 23U));
                  dest.write(16U, 23U, src.read(8U, 15U));
                  dest.write(24U, 31U, src.read(0U, 7U));
            } else if (dest.bits() == 64U) {
                  dest.write(0U, 7U, src.read(56U, 63U));
                  dest.write(8U, 15U, src.read(48U, 55U));
                  dest.write(16U, 23U, src.read(40U, 47U));
                  dest.write(24U, 31U, src.read(32U, 39U));
                  dest.write(32U, 39U, src.read(24U, 31U));
                  dest.write(40U, 47U, src.read(16U, 23U));
                  dest.write(48U, 55U, src.read(8U, 15U));
                  dest.write(56U, 63U, src.read(0U, 7U));
            }
            return;
      }

      void MOVDDUP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63U, src.read(0U, 63U));
            dest.write(64U, 127U, src.read(0U, 63U));
            return;
      }

      void MOVDIR64B(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVDIRI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVDQA(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest = src;
            return;
      }

      void MOVDQU(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0, 127, src.read(0, 127));
            return;
      }

      void MOVHLPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63U, src.read(64U, 127U));
            return;
      }

      void MOVHPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            MOVHLPS(registrar, operands);
            return;
      }

      void MOVHPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(64U, 127U, src.read(0U, 63U));
            return;
      }

      void MOVLHPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            MOVHPS(registrar, operands);
            return;
      }

      void MOVLPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63U, src.read(0U, 63U));
            return;
      }

      void MOVLPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            MOVLPD(registrar, operands);
            return;
      }

      void MOVMSKPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVMSKPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVNTDQA(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVNTDQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVNTI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVNTPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVNTPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest = src;
            return;
      }

      void MOVNTSD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVNTSS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            if (registrar.hw_constants.instruction_interp == 64U) {

                  kif(FDF == 0U);
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

                  kif(FDF == 0U);
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

      void MOVSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            if (registrar.hw_constants.instruction_interp == 64U) {

                  kif(FDF == 0U);
                  {
                        REG_RSI += 4U;
                        REG_RDI += 4U;
                  }
                  kelse;
                  {
                        REG_RSI -= 4U;
                        REG_RDI -= 4U;
                  }
                  kend;
            } else {

                  kif(FDF == 0U);
                  {
                        REG_ESI += 4U;
                        REG_EDI += 4U;
                  }
                  kelse;
                  {
                        REG_ESI -= 4U;
                        REG_EDI -= 4U;
                  }
                  kend;
            }
            return;
      }

      void MOVSHDUP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVSLDUP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MOVSQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            if (registrar.hw_constants.instruction_interp == 64U) {

                  kif(FDF == 0U);
                  {
                        REG_RSI += 8U;
                        REG_RDI += 8U;
                  }
                  kelse;
                  {
                        REG_RSI -= 8U;
                        REG_RDI -= 8U;
                  }
                  kend;
            } else {

                  kif(FDF == 0U);
                  {
                        REG_ESI += 8U;
                        REG_EDI += 8U;
                  }
                  kelse;
                  {
                        REG_ESI -= 8U;
                        REG_EDI -= 8U;
                  }
                  kend;
            }
            return;
      }

      void MOVSS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            if (src.is_reg(EXTENSION_XMM) && dest.is_mem()) {
                  dest.write(0, 31, src.read(0, 31));
                  dest.write(32, 127, 0U);
                  return;
            }
            dest.write(0, 31, src.read(0, 31));
            return;
      }

      void MOVSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            if (registrar.hw_constants.instruction_interp == 64U) {

                  kif(FDF == 0U);
                  {
                        REG_RSI += 2U;
                        REG_RDI += 2U;
                  }
                  kelse;
                  {
                        REG_RSI -= 2U;
                        REG_RDI -= 2U;
                  }
                  kend;
            } else {

                  kif(FDF == 0U);
                  {
                        REG_ESI += 2U;
                        REG_EDI += 2U;
                  }
                  kelse;
                  {
                        REG_ESI -= 2U;
                        REG_EDI -= 2U;
                  }
                  kend;
            }
            return;
      }

      void MOVSX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            operands.front() = luramas::il::lifter::builder::libraries::structure::extend_sign(f, operands.back(), operands.back().bits() == 8U ? luramas::types::native::t_int16 : luramas::types::native::t_int32);
            return;
      }

      void MOVSXD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            operands.front() = luramas::il::lifter::builder::libraries::structure::extend_sign(f, operands.back(), luramas::types::native::t_int64);
            return;
      }

      void MOVUPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front().write(0U, 127U, operands.back().read(0U, 127U));
            return;
      }

      void MOVUPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front().write(0U, 127U, operands.back().read(0U, 127U));
            return;
      }

      void MOVZX(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto dest = operands.front();
            const auto &src = operands.back();
            dest = LURAMAS_FBUILD_ZEROEXTEND(dest, src);
            return;
      }

      void MPSADBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            const auto &dest = operands.front();
            const auto &src = operands[1U];
            const auto &imm = operands.back();

            const auto src_offset = imm.read(0U, 1U) * 32U;
            const auto dest_offset = imm[2U] * 32U;

            const auto dest_byte_0 = dest.read(dest_offset + 0U, dest_offset + 7U);
            const auto dest_byte_1 = dest.read(dest_offset + 8U, dest_offset + 15U);
            const auto dest_byte_2 = dest.read(dest_offset + 16U, dest_offset + 23U);
            const auto dest_byte_3 = dest.read(dest_offset + 24U, dest_offset + 31U);
            const auto dest_byte_4 = dest.read(dest_offset + 32U, dest_offset + 39U);
            const auto dest_byte_5 = dest.read(dest_offset + 40U, dest_offset + 47U);
            const auto dest_byte_6 = dest.read(dest_offset + 48U, dest_offset + 55U);
            const auto dest_byte_7 = dest.read(dest_offset + 56U, dest_offset + 63U);
            const auto dest_byte_8 = dest.read(dest_offset + 64U, dest_offset + 71U);
            const auto dest_byte_9 = dest.read(dest_offset + 72U, dest_offset + 79U);
            const auto dest_byte_10 = dest.read(dest_offset + 80U, dest_offset + 87U);

            const auto src_byte_0 = src.read(src_offset + 0U, src_offset + 7U);
            const auto src_byte_1 = src.read(src_offset + 8U, src_offset + 15U);
            const auto src_byte_2 = src.read(src_offset + 16U, src_offset + 23U);
            const auto src_byte_3 = src.read(src_offset + 24U, src_offset + 31U);

            const auto temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_0 - src_byte_0);
            const auto temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_1 - src_byte_1);
            const auto temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_2 - src_byte_2);
            const auto temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_3 - src_byte_3);
            dest.write(0U, 15U, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_1 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_2 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_3 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_4 - src_byte_3);
            dest.write(16U, 31U, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_2 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_3 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_4 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_5 - src_byte_3);
            dest.write(32U, 47U, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_3 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_4 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_5 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_6 - src_byte_3);
            dest.write(48U, 63U, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_4 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_5 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_6 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_7 - src_byte_3);
            dest.write(64U, 79U, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_5 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_6 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_7 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_8 - src_byte_3);
            dest.write(80U, 95U, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_6 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_7 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_8 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_9 - src_byte_3);
            dest.write(96, 111U, temp0 + temp1 + temp2 + temp3);
            temp0 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_7 - src_byte_0);
            temp1 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_8 - src_byte_1);
            temp2 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_9 - src_byte_2);
            temp3 = luramas::il::lifter::builder::libraries::math::abs(f, dest_byte_10 - src_byte_3);
            dest.write(112U, 127U, temp0 + temp1 + temp2 + temp3);
            return;
      }

      void MUL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &src = operands.front();
            switch (src.bits()) {
                  case 16U: {
                        const auto product = REG_AX * src;
                        REG_DX = LURAMAS_FBUILD_UPPER_BITS(product);
                        REG_AX = LURAMAS_FBUILD_LOWER_BITS(product);
                        FCF = REG_DX;
                        FOF = REG_DX;
                        break;
                  }
                  case 32U: {
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
                        const auto upper = LURAMAS_FBUILD_UPPER_BITS(REG_AX);
                        FCF = upper;
                        FOF = upper;
                        break;
                  }
            }
            return;
      }

      void MULPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MULPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, dest.read(0U, 31) * src.read(0U, 31));
            dest.write(32U, 63U, dest.read(32U, 63U) * src.read(32U, 63U));
            dest.write(64U, 95U, dest.read(64U, 95U) * src.read(64U, 95U));
            dest.write(96U, 127U, dest.read(96U, 127U) * src.read(96U, 127U));
            return;
      }

      void MULSD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63, dest.read(0U, 63) * src.read(0U, 63));
            return;
      }

      void MULSS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, dest.read(0U, 31) * src.read(0U, 31U));
            return;
      }

      void MULX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest1 = operands.front();
            const auto &dest2 = operands[1U];
            const auto &src1 = operands[2U];
            const auto &src2 = operands.back();

            if (registrar.hw_constants.instruction_interp == 32U) {
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

      void FMUL(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FIMUL(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FMULP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MWAITX(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void MWAIT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void NEG(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();

            const auto temp = -dest;
            FCF = dest != 0U;
            tools::eflags::mutate<F_COMMON_NO_CF>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp));
            dest = temp;
            return;
      }

      void NOP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            registrar.build->make<luramas::il::arch::opcodes::OP_NOP>();
            return;
      }

      void NOT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = ~operands.front();
            return;
      }

      void OR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto temp = dest | src;
            tools::eflags::mutate<xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            dest = temp;
            FOF = 0U;
            FCF = 0U;
            return;
      }

      void ORPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0, 63, src1.read(0, 63) | src2.read(0, 63));
            dest.write(64, 127, src1.read(64, 127) | src2.read(64, 127));
            return;
      }

      void ORPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, dest.read(0U, 31) | src.read(0U, 31));
            dest.write(32U, 63U, dest.read(32U, 63U) | src.read(32U, 63U));
            dest.write(64U, 95U, dest.read(64U, 95U) | src.read(64U, 95U));
            dest.write(96U, 127U, dest.read(96U, 127U) | src.read(96U, 127U));
            return;
      }

      void OUT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &port = operands.front();
            const auto &value = operands.back();

            klura_call(luramas::builtins::IO::INPUT, {value, klura_tint(0U), port});
            return;
      }

      void OUTSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::IO::INPUT, {REG_SIL, klura_tint(0U), REG_DX});
            return;
      }

      void OUTSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::IO::INPUT, {REG_ESI, klura_tint(0U), REG_DX});
            return;
      }

      void OUTSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::IO::INPUT, {REG_SI, klura_tint(0U), REG_DX});
            return;
      }
} // namespace vm

#endif // LURAMAS_TARGET_X86
