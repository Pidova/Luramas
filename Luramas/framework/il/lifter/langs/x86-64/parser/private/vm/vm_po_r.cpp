#ifdef LURAMAS_TARGET_X86
#include "common.hpp"

/* Instruction handlers: POP - RSTORSSP */
namespace vm {

      void POP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (!operands.empty()) {
                  build::stack_pop(registrar, operands.front());
            }
            return;
      }

      void POPAW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto temp = registrar.build->make_temp(REG_SP);
            registrar.build->make_pop(REG_AX);
            registrar.build->make_pop(REG_CX);
            registrar.build->make_pop(REG_DX);
            registrar.build->make_pop(REG_BX);
            registrar.build->make_pop(temp);
            registrar.build->make_pop(REG_BP);
            registrar.build->make_pop(REG_SI);
            registrar.build->make_pop(REG_DI);
            return;
      }

      void POPAL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto temp = registrar.build->make_temp(REG_ESP);
            registrar.build->make_pop(REG_EAX);
            registrar.build->make_pop(REG_ECX);
            registrar.build->make_pop(REG_EDX);
            registrar.build->make_pop(REG_EBX);
            registrar.build->make_pop(temp);
            registrar.build->make_pop(REG_EBP);
            registrar.build->make_pop(REG_ESI);
            registrar.build->make_pop(REG_EDI);
            return;
      }

      void POPCNT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            function_handler f(registrar.build);

            dest = luramas::il::lifter::builder::libraries::bitwise::popcount(f, src);
            FOF = 0u;
            FSF = 0u;
            FAF = 0u;
            FCF = 0u;
            FPF = 0u;
            FZF = src == 0u;
            return;
      }

      void POPF(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void POPFD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void POPFQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PREFETCH(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PREFETCHT0(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PREFETCHT1(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PREFETCHT2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PREFETCHWT1(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PSHUFD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands[1];
            const auto order = operands.back();

            dest.write(0u, 31u, ((src >> order.read(0u, 1u)) * 32u).read(0u, 31u));
            dest.write(32u, 63u, ((src >> order.read(2u, 3u)) * 32u).read(0u, 31u));
            dest.write(64u, 95u, ((src >> order.read(4u, 5u)) * 32u).read(0u, 31u));
            dest.write(96u, 127u, ((src >> order.read(6u, 7u)) * 32u).read(0u, 31u));
            return;
      }

      void PSHUFHW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands[1u];
            const auto order = operands.back();

            dest.write(0u, 63u, src.read(0u, 63u));
            dest.write(64u, 79u, (src >> (order.read(0u, 1u) * 16u)).read(64u, 79u));
            dest.write(80u, 95u, (src >> (order.read(2u, 3u) * 16u)).read(64u, 79u));
            dest.write(96u, 111u, (src >> (order.read(4u, 5u) * 16u)).read(64u, 79u));
            dest.write(112u, 127u, (src >> (order.read(6u, 7u) * 16u)).read(64u, 79u));
            return;
      }

      void PSHUFLW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands[1u];
            const auto order = operands.back();

            dest.write(0u, 15u, (src >> (order.read(0u, 1u) * 16u)).read(0u, 15u));
            dest.write(16u, 31u, (src >> (order.read(2u, 3u) * 16u)).read(0u, 15u));
            dest.write(32u, 47u, (src >> (order.read(4u, 5u) * 16u)).read(0u, 15u));
            dest.write(48u, 63u, (src >> (order.read(6u, 7u) * 16u)).read(0u, 15u));
            dest.write(64u, 127u, src.read(64u, 127u));
            return;
      }

      void PSLLDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto count = operands.back();

            auto t = temp(registrar, count);

            kif(t > 15);
            {
                  t = 16;
            }
            kend;
            dest <<= (t * 8);
            return;
      }

      void PSRLDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto count = operands.back();

            auto t = temp(registrar, count);

            kif(t > 15);
            {
                  t = 16;
            }
            kend;
            dest >>= (t * 8);
            return;
      }

      void PSWAPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, src.read(32u, 63u));
            dest.write(32u, 63u, src.read(0u, 31u));
            return;
      }

      void PTEST(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PTWRITE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PUNPCKHQDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63u, dest.read(64u, 127u));
            dest.write(64u, 127u, src.read(64u, 127u));
            return;
      }

      void PUNPCKLQDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63u, dest.read(0u, 63));
            dest.write(64u, 127u, src.read(0u, 63u));
            return;
      }

      void PUSH(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (!operands.empty()) {
                  build::stack_push(registrar, operands.front());
            }
            return;
      }

      void PUSHAW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto temp = registrar.build->make_temp(REG_SP);
            registrar.build->make_push(REG_AX);
            registrar.build->make_push(REG_CX);
            registrar.build->make_push(REG_DX);
            registrar.build->make_push(REG_BX);
            registrar.build->make_push(temp);
            registrar.build->make_push(REG_BP);
            registrar.build->make_push(REG_SI);
            registrar.build->make_push(REG_DI);
            return;
      }

      void PUSHAL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto temp = registrar.build->make_temp(REG_ESP);
            registrar.build->make_push(REG_EAX);
            registrar.build->make_push(REG_ECX);
            registrar.build->make_push(REG_EDX);
            registrar.build->make_push(REG_EBX);
            registrar.build->make_push(temp);
            registrar.build->make_push(REG_EBP);
            registrar.build->make_push(REG_ESI);
            registrar.build->make_push(REG_EDI);
            return;
      }

      void PUSHF(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PUSHFD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void PUSHFQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RCL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RCPPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RCPSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RCR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            //const auto dest = operands.front();
            //const auto src = operands.back();
            //
            //const auto res = (dest >> src) | (FCF << (dest.bits() - src));
            //tools::eflags::mutate(registrar, tools::eflags::flag_data(registrar.inst, dest, res, src), xeflags::CF, xeflags::OF);
            //dest = res;
            return;
      }

      void RDFSBASE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RDGSBASE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RDMSR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto temp = klura_vtemp;
            registrar.build->load_internal_global(internal::globals::MSR, temp);
            luramas::il::lifter::builder::libraries::structure::assign_pair(REG_EDX, REG_EAX, temp.read(REG_ECX, REG_ECX + (REG_EDX.bits() + REG_EDX.bits())));
            return;
      }

      void RDPKRU(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RDPMC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RDRAND(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (const auto bint = simd::get(registrar.inst); !bint.empty()) {
                  klura_call(luramas::builtins::RANDOMNESS::RANDOM, {}, operands);
                  FCF = operands.front() != 0u;
                  FOF = 0u;
                  FSF = 0u;
                  FZF = 0u;
                  FAF = 0u;
                  FPF = 0u;
            }
            return;
      }

      void RDSEED(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (const auto bint = simd::get(registrar.inst); !bint.empty()) {
                  klura_call(luramas::builtins::RANDOMNESS::SEED, {}, operands);
                  FCF = operands.front() != 0u;
                  FOF = 0u;
                  FSF = 0u;
                  FZF = 0u;
                  FAF = 0u;
                  FPF = 0u;
            }
            return;
      }

      void RDSSPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RDSSPQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RDTSC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto t = klura_vtemp;
            klura_call(luramas::builtins::CPU::GET_TIMESTAMP_COUNTER, {}, {t});
            REG_EAX = LURAMAS_FBUILD_LOWER_BITS(t);
            REG_EDX = LURAMAS_FBUILD_UPPER_BITS(t);
            return;
      }

      void RDTSCP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void REPNE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void REP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RET(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (!operands.empty()) {

                  build::reg_stack(registrar) += operands.front() + (registrar.hw_constants.suggested_bit_set == 32u ? 4u : 8u);
            }

            luramas_flag fgoes_to = false;
            for (const auto &inst : registrar.get_details()) {
                  if (inst.goes_to()) {
                        fgoes_to = true;
                        registrar.build->page_retn(build::reg_stack(registrar).r.r, inst.loc);
                  }
            }
            if (!fgoes_to) {
                  registrar.build->page_retn();
            }
            return;
      }

      void REX64(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void ROL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto DEST = operands.front();
            const auto COUNT = operands.back();
            function_handler f(registrar.build);

            const auto SIZE = DEST.bits();
            const auto COUNTMASK = SIZE - 1u;

            const auto tempCF = klura_vtemp;
            const auto tempCOUNT = (COUNT & COUNTMASK) % SIZE;
            kwhile(tempCOUNT != 0);
            {
                  tempCF = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, DEST);
                  DEST = (DEST * 2u) + tempCF;
                  --tempCOUNT;
            }
            kwhile_end;

            kif((COUNT & COUNTMASK) != 0u);
            {
                  FCF = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, DEST);
            }
            kend;

            kif((COUNT & COUNTMASK) == 1u);
            {
                  FOF = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, DEST) ^ FCF;
            }
            kend;
            return;
      }

      void ROR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto DEST = operands.front();
            const auto COUNT = operands.back();
            function_handler f(registrar.build);

            const auto SIZE = DEST.bits();
            const auto COUNTMASK = SIZE - 1u;

            const auto tempCF = klura_vtemp;
            const auto tempCOUNT = (COUNT & COUNTMASK);
            kwhile(tempCOUNT != 0);
            {
                  tempCF = luramas::il::lifter::builder::libraries::structure::least_significant_bit(f, DEST);
                  DEST = (DEST / 2u) + (tempCF << (SIZE - 1u));
                  --tempCOUNT;
            }
            kwhile_end;

            kif((COUNT & COUNTMASK) != 0u);
            {
                  FCF = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, DEST);
            }
            kend;

            kif((COUNT & COUNTMASK) != 0u);
            {
                  const auto msb = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, DEST);
                  const auto msb_minus_1 = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, DEST, 2u);
                  FOF = msb ^ msb_minus_1;
            }
            kend;
            return;
      }

      void RORX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands[1u];
            const auto imm = operands.back();

            if (dest.bits() == 32u) {

                  const auto y = imm & 0x1F;
                  dest = (src >> y) | (src << (32u - y));
            } else if (dest.bits() == 64u) {

                  const auto y = imm & 0x3F;
                  dest = (src >> y) | (src << (64u - y));
            }
            return;
      }

      void ROUNDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            operands.front().write(0u, 63u, luramas::il::lifter::builder::libraries::math::round_to_integer(f, operands[1u].read(0u, 63u), operands.back()));
            operands.front().write(64u, 127u, luramas::il::lifter::builder::libraries::math::round_to_integer(f, operands[1u].read(64u, 127u), operands.back()));
            return;
      }

      void ROUNDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            const auto &dest = operands.front();
            const auto &src = operands[1u];
            const auto &round_ctl = operands.back();

            for (std::uint32_t i = 0; i < 128u; i += 32u) {
                  dest.write(i, i + 31u, luramas::il::lifter::builder::libraries::math::round_to_integer(f, src.read(i, i + 31u), round_ctl));
            }
            return;
      }

      void ROUNDSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            operands.front().write(0u, 63u, luramas::il::lifter::builder::libraries::math::round_to_integer(f, operands[1u].read(0u, 63u), operands.back()));
            return;
      }

      void ROUNDSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            operands.front().write(0u, 31u, luramas::il::lifter::builder::libraries::math::round_to_integer(f, operands[1u].read(0u, 31u), operands.back()));
            return;
      }

      void RSM(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RSQRTPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RSQRTSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void RSTORSSP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }
} // namespace vm

#endif // LURAMAS_TARGET_X86
