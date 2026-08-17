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

      void POPAW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

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

      void POPAL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

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

            const auto &dest = operands.front();
            const auto &src = operands.back();

            function_handler f(registrar.build);

            dest = luramas::il::lifter::builder::libraries::bitwise::popcount(f, src);
            FOF = 0U;
            FSF = 0U;
            FAF = 0U;
            FCF = 0U;
            FPF = 0U;
            FZF = src == 0U;
            return;
      }

      void POPF(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void POPFD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void POPFQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PREFETCH(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PREFETCHT0(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PREFETCHT1(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PREFETCHT2(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PREFETCHWT1(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PSHUFD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands[1];
            const auto &order = operands.back();

            dest.write(0U, 31U, ((src >> order.read(0U, 1U)) * 32U).read(0U, 31U));
            dest.write(32U, 63U, ((src >> order.read(2U, 3U)) * 32U).read(0U, 31U));
            dest.write(64U, 95U, ((src >> order.read(4U, 5U)) * 32U).read(0U, 31U));
            dest.write(96U, 127U, ((src >> order.read(6U, 7U)) * 32U).read(0U, 31U));
            return;
      }

      void PSHUFHW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands[1U];
            const auto &order = operands.back();

            dest.write(0U, 63U, src.read(0U, 63U));
            dest.write(64U, 79U, (src >> (order.read(0U, 1U) * 16U)).read(64U, 79U));
            dest.write(80U, 95U, (src >> (order.read(2U, 3U) * 16U)).read(64U, 79U));
            dest.write(96U, 111U, (src >> (order.read(4U, 5U) * 16U)).read(64U, 79U));
            dest.write(112U, 127U, (src >> (order.read(6U, 7U) * 16U)).read(64U, 79U));
            return;
      }

      void PSHUFLW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands[1U];
            const auto &order = operands.back();

            dest.write(0U, 15U, (src >> (order.read(0U, 1U) * 16U)).read(0U, 15U));
            dest.write(16U, 31U, (src >> (order.read(2U, 3U) * 16U)).read(0U, 15U));
            dest.write(32U, 47U, (src >> (order.read(4U, 5U) * 16U)).read(0U, 15U));
            dest.write(48U, 63U, (src >> (order.read(6U, 7U) * 16U)).read(0U, 15U));
            dest.write(64U, 127U, src.read(64U, 127U));
            return;
      }

      void PSLLDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &count = operands.back();

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

            const auto &dest = operands.front();
            const auto &count = operands.back();

            auto t = temp(registrar, count);

            kif(t > 15);
            {
                  t = 16;
            }
            kend;
            dest >>= (t * 8);
            return;
      }

      void PSWAPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, src.read(32U, 63U));
            dest.write(32U, 63U, src.read(0U, 31U));
            return;
      }

      void PTEST(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PTWRITE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PUNPCKHQDQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63U, dest.read(64U, 127U));
            dest.write(64U, 127U, src.read(64U, 127U));
            return;
      }

      void PUNPCKLQDQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63U, dest.read(0U, 63));
            dest.write(64U, 127U, src.read(0U, 63U));
            return;
      }

      void PUSH(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (!operands.empty()) {
                  build::stack_push(registrar, operands.front());
            }
            return;
      }

      void PUSHAW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

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

      void PUSHAL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

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

      void PUSHF(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PUSHFD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void PUSHFQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RCL(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RCPPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RCPSS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RCR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            //const auto dest = operands.front();
            //const auto src = operands.back();
            //
            //const auto res = (dest >> src) | (FCF << (dest.bits() - src));
            //tools::eflags::mutate(registrar, tools::eflags::flag_data(registrar.inst, dest, res, src), xeflags::CF, xeflags::OF);
            //dest = res;
            return;
      }

      void RDFSBASE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RDGSBASE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RDMSR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto temp = klura_vtemp;
            registrar.build->load_internal_global(internal::globals::MSR, temp);
            luramas::il::lifter::builder::libraries::structure::assign_pair(REG_EDX, REG_EAX, temp.read(REG_ECX, REG_ECX + (REG_EDX.bits() + REG_EDX.bits())));
            return;
      }

      void RDPKRU(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RDPMC(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RDRAND(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (const auto bint = simd::get(registrar.inst); !bint.empty()) {
                  klura_call(luramas::builtins::RANDOMNESS::RANDOM, {}, operands);
                  FCF = operands.front() != 0U;
                  FOF = 0U;
                  FSF = 0U;
                  FZF = 0U;
                  FAF = 0U;
                  FPF = 0U;
            }
            return;
      }

      void RDSEED(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (const auto bint = simd::get(registrar.inst); !bint.empty()) {
                  klura_call(luramas::builtins::RANDOMNESS::SEED, {}, operands);
                  FCF = operands.front() != 0U;
                  FOF = 0U;
                  FSF = 0U;
                  FZF = 0U;
                  FAF = 0U;
                  FPF = 0U;
            }
            return;
      }

      void RDSSPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RDSSPQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RDTSC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto t = klura_vtemp;
            klura_call(luramas::builtins::CPU::GET_TIMESTAMP_COUNTER, {}, {t});
            REG_EAX = LURAMAS_FBUILD_LOWER_BITS(t);
            REG_EDX = LURAMAS_FBUILD_UPPER_BITS(t);
            return;
      }

      void RDTSCP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void REPNE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void REP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RET(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            if (!operands.empty()) {

                  build::reg_stack(registrar) += operands.front() + (registrar.hw_constants.suggested_bit_set == 32U ? 4U : 8U);
            }

            luramas_flag fgoes_to = false;
            if (registrar.v_inst.edges) {
                  for (const auto &[roa, kind] : *registrar.v_inst.edges) {
                        if (kind != luramas::profile::inst_kind::return_to || !roa.freal_pc) {
                              continue;
                        }
                        fgoes_to = true;
                        registrar.build->page_retn(build::reg_stack(registrar).r.r, roa.real_pc);
                  }
            }
            if (!fgoes_to) {
                  registrar.build->page_retn();
            }
            return;
      }

      void REX64(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void ROL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &count = operands.back();
            function_handler f(registrar.build);

            const auto size = dest.bits();
            const auto countmask = size - 1U;

            const auto temp_cf = klura_vtemp;
            const auto temp_count = (count & countmask) % size;
            kwhile(temp_count != 0);
            {
                  temp_cf = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, dest);
                  dest = (dest * 2U) + temp_cf;
                  --temp_count;
            }
            kwhile_end;

            kif((count & countmask) != 0U);
            {
                  FCF = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, dest);
            }
            kend;

            kif((count & countmask) == 1U);
            {
                  FOF = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, dest) ^ FCF;
            }
            kend;
            return;
      }

      void ROR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &count = operands.back();
            function_handler f(registrar.build);

            const auto size = dest.bits();
            const auto countmask = size - 1U;

            const auto temp_cf = klura_vtemp;
            const auto temp_count = (count & countmask);
            kwhile(temp_count != 0);
            {
                  temp_cf = luramas::il::lifter::builder::libraries::structure::least_significant_bit(f, dest);
                  dest = (dest / 2U) + (temp_cf << (size - 1U));
                  --temp_count;
            }
            kwhile_end;

            kif((count & countmask) != 0U);
            {
                  FCF = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, dest);
            }
            kend;

            kif((count & countmask) != 0U);
            {
                  const auto msb = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, dest);
                  const auto msb_minus_1 = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, dest, 2U);
                  FOF = msb ^ msb_minus_1;
            }
            kend;
            return;
      }

      void RORX(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands[1U];
            const auto &imm = operands.back();

            if (dest.bits() == 32U) {

                  const auto y = imm & 0x1F;
                  dest = (src >> y) | (src << (32U - y));
            } else if (dest.bits() == 64U) {

                  const auto y = imm & 0x3F;
                  dest = (src >> y) | (src << (64U - y));
            }
            return;
      }

      void ROUNDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            operands.front().write(0U, 63U, luramas::il::lifter::builder::libraries::math::round_to_integer(f, operands[1U].read(0U, 63U), operands.back()));
            operands.front().write(64U, 127U, luramas::il::lifter::builder::libraries::math::round_to_integer(f, operands[1U].read(64U, 127U), operands.back()));
            return;
      }

      void ROUNDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            const auto &dest = operands.front();
            const auto &src = operands[1U];
            const auto &round_ctl = operands.back();

            for (std::uint32_t i = 0; i < 128U; i += 32U) {
                  dest.write(i, i + 31U, luramas::il::lifter::builder::libraries::math::round_to_integer(f, src.read(i, i + 31U), round_ctl));
            }
            return;
      }

      void ROUNDSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            operands.front().write(0U, 63U, luramas::il::lifter::builder::libraries::math::round_to_integer(f, operands[1U].read(0U, 63U), operands.back()));
            return;
      }

      void ROUNDSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            operands.front().write(0U, 31U, luramas::il::lifter::builder::libraries::math::round_to_integer(f, operands[1U].read(0U, 31U), operands.back()));
            return;
      }

      void RSM(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RSQRTPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RSQRTSS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void RSTORSSP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }
} // namespace vm

#endif // LURAMAS_TARGET_X86
