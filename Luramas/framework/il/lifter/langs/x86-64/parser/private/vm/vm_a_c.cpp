#ifdef LURAMAS_TARGET_X86
#include "common.hpp"

/* Instruction handlers: AAA - CWDE */
namespace vm {

      void AAA(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            kif(((REG_AL & 0x0F) + (FAF << 3)) > 1U) {
                  REG_AX += 0x106;
                  FAF = 1U;
                  FCF = 1U;
            }
            kelse;
            {
                  FAF = 0U;
                  FCF = 0U;
            }
            kend;
            REG_AL &= 0x0F;
            return;
      }

      void AAD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto temp = (REG_AL + (REG_AH * 0x0A)) & 0xFF;
            tools::eflags::mutate<xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, REG_AL, temp, REG_AH));
            REG_AL = temp;
            REG_AH = 0U;
            return;
      }

      void AAM(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto temp_ah = temp(registrar, REG_AH);
            const auto temp_al = temp(registrar, REG_AL);

            REG_AH = REG_AL / 0x0A;
            REG_AL = REG_AL % 0x0A;

            tools::eflags::mutate<xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, temp_al, REG_AL, temp_ah));
            return;
      }

      void AAS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto cond = ((REG_AL & 0x0F) - 10U) >> 7U;
            cond |= FAF;

            REG_AL -= cond * 6U;
            REG_AH -= cond;
            FCF = cond;
            FAF = cond;

            REG_AL &= 0x0F;
            return;
      }

      void FABS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto t = temp(registrar, REG_ST0);
            t.cmp(0U);
            registrar.build->make_scope<luramas::il::arch::data::bin_kinds::lt_>(1U);
            {
                  t = !t;
            }
            registrar.build->close_scope();

            REG_ST0 = t;
            FC1 = 0U;
            return;
      }

      void ADC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto temp = dest + src + FCF;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            return;
      }

      void ADCX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto dest = operands.front();
            auto src = operands.back();

            dest.cast(true);
            src.cast(true);

            const auto temp = dest + src + FCF;
            tools::eflags::mutate<xeflags::CF>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            dest = temp;
            return;
      }

      void ADD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto temp = dest + src;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            dest = temp;
            return;
      }

      void ADDPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63U, dest.read(0U, 63U) + src.read(0U, 63U));
            dest.write(64U, 127U, dest.read(64U, 127U) + src.read(64U, 127U));
            return;
      }

      void ADDPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, dest.read(0U, 31) + src.read(0U, 31));
            dest.write(32U, 63U, dest.read(32U, 63U) + src.read(32U, 63U));
            dest.write(64U, 95U, dest.read(64U, 95U) + src.read(64U, 95U));
            dest.write(96U, 127U, dest.read(96U, 127U) + src.read(96U, 127U));
            return;
      }

      void ADDSD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63, dest.read(0U, 63) + src.read(0U, 63));
            return;
      }

      void ADDSS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, dest.read(0U, 31) + src.read(0U, 31U));
            return;
      }

      void ADDSUBPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            auto dest_lower = dest.read(0U, 63U);
            auto dest_upper = dest.read(64U, 127U);
            auto src_lower = src.read(0U, 63U);
            auto src_upper = src.read(64U, 127U);

            auto result_lower = dest_lower + src_lower;
            auto result_upper = dest_upper - src_upper;

            dest.write(0U, 63U, result_lower);
            dest.write(64U, 127U, result_upper);
            return;
      }

      void ADDSUBPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto d0 = dest.read(0U, 31U);
            const auto d1 = dest.read(32U, 63U);
            const auto d2 = dest.read(64U, 95U);
            const auto d3 = dest.read(96U, 127U);

            const auto s0 = src.read(0U, 31U);
            const auto s1 = src.read(32U, 63U);
            const auto s2 = src.read(64U, 95U);
            const auto s3 = src.read(96U, 127U);

            dest.write(0U, 31U, d0 + s0);
            dest.write(32U, 63U, d1 - s1);
            dest.write(64U, 95U, d2 + s2);
            dest.write(96U, 127U, d3 - s3);
            return;
      }

      void FADD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FIADD(registrar, operands);
            return;
      }

      void FIADD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            auto src = operands.back();
            function_handler f(registrar.build);

            dest += LURAMAS_FBUILD_EXTEND_FLOAT(src);
            FC1 = (luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, dest) == 0U) && (dest != 0U);
            return;
      }

      void ADOX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto temp = dest + src + registrar.getf<xeflags::OF>();
            tools::eflags::mutate<xeflags::OF>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            dest = temp;
            return;
      }

      void AESDECLAST(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void AESDEC(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void AESENCLAST(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void AESENC(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void AESIMC(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void AESKEYGENASSIST(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void AND(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto temp = dest & src;
            tools::eflags::mutate<xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            dest = temp;
            FOF = 0U;
            FCF = 0U;
            return;
      }

      void ANDN(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            const auto temp = (~src1) & src2;
            tools::eflags::mutate<xeflags::SF, xeflags::ZF>(registrar, tools::eflags::flag_data(registrar.inst, src1, temp, src2));
            dest = temp;
            FOF = 0U;
            FCF = 0U;
            return;
      }

      void ANDNPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63U, (~dest.read(0U, 63U)) & src.read(0U, 63U));
            dest.write(64U, 127U, (~dest.read(64U, 127U)) & src.read(64U, 127U));
            return;
      }

      void ANDNPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, (~dest.read(0U, 31U)) & src.read(0U, 31U));
            dest.write(32U, 63U, (~dest.read(32U, 63U)) & src.read(32U, 63U));
            dest.write(64U, 95U, (~dest.read(64U, 95U)) & src.read(64U, 95U));
            dest.write(96U, 127U, (~dest.read(96U, 127U)) & src.read(96U, 127U));
            return;
      }

      void ANDPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0, 63, src1.read(0, 63) & src2.read(0, 63));
            dest.write(64, 127, src1.read(64, 127) & src2.read(64, 127));
            return;
      }

      void ANDPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, dest.read(0U, 31) & src.read(0U, 31));
            dest.write(32U, 63U, dest.read(32U, 63U) & src.read(32U, 63U));
            dest.write(64U, 95U, dest.read(64U, 95U) & src.read(64U, 95U));
            dest.write(96U, 127U, dest.read(96U, 127U) & src.read(96U, 127U));
            return;
      }

      void ARPL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            if (registrar.hw_constants.instruction_interp == 64U) {

                  MOVSXD(registrar, operands);
            } else {

                  const auto dest_rpl = dest & 0x3;
                  const auto src_rpl = src & 0x3;
                  kif(dest_rpl < src_rpl) {
                        FZF = 1U;
                        dest = (dest & ~0x3) | src_rpl;
                  }
                  kelse;
                  {
                        FZF = 0U;
                  }
                  kend;
            }
            return;
      }

      void BEXTR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            auto src1 = operands[1U];
            const auto &src2 = operands.back();

            const auto start = src2.read(0U, 7U);
            auto t = LURAMAS_FBUILD_EXTEND_512(src1).read(start, start + src2.read(8U, 15U) - 1U);
            dest = LURAMAS_FBUILD_ZEROEXTEND(t, t);
            FZF = 0U;
            FCF = 0U;
            FOF = 0U;
            return;
      }

      void BLCFILL(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BLCI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BLCIC(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BLCMSK(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BLCS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BLENDPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BLENDPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BLENDVPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BLENDVPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BLSFILL(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BLSI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto temp = -src & src;
            FSF = temp.read(temp.bits() - 1U);
            FZF = temp == 0;
            FCF = src != 0U;
            FOF = 0U;
            dest = temp;
            return;
      }

      void BLSIC(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BLSMSK(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto temp = (src - 1U) ^ src;
            FSF = temp.read(temp.bits() - 1U);
            FZF = 0U;
            FOF = 0U;
            FCF = src == 0U;
            dest = temp;
            return;
      }

      void BLSR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            const auto temp = (src - 1U) & src;

            FSF = temp < 0;
            FZF = temp == 0;
            FCF = src == 0;
            dest = temp;
            return;
      }

      void BNDCL(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BNDCN(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BNDCU(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BNDLDX(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BNDMK(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BNDMOV(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BNDSTX(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BOUND(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void BSF(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            kif(src == 0U) {
                  FZF = 1U;
            }
            kelse;
            {
                  FZF = 0U;
                  auto temp = klura_vtemp;
                  temp.cast(dest.r.r);
                  temp = 0U;
                  kwhile(src[temp] == 0U) {
                        ++temp;
                  }
                  kend;
                  dest = temp;
            }
            kend;
            return;
      }

      void BSR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            kif(src == 0U) {
                  FZF = 1U;
            }
            kelse;
            {
                  FZF = 0U;
                  auto temp = klura_vtemp;
                  temp = dest.bits() - 1U;
                  kwhile(src[temp] == 0U) {
                        temp -= 1U;
                  }
                  kend;
                  dest = temp;
            }
            kend;
            return;
      }

      void BSWAP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto dest = operands.front();
            auto temp = dest;

            if (dest.bits() == 64U) {
                  luramas::il::lifter::builder::cast<64U>(dest, temp);
                  dest.write(0U, 7U, temp.read(56U, 63U));
                  dest.write(8U, 15U, temp.read(48U, 55U));
                  dest.write(16U, 23U, temp.read(40U, 47U));
                  dest.write(24U, 31U, temp.read(32U, 39U));
                  dest.write(32U, 39U, temp.read(24U, 31U));
                  dest.write(40U, 47U, temp.read(16U, 23U));
                  dest.write(48U, 55U, temp.read(8U, 15U));
                  dest.write(56U, 63U, temp.read(0U, 7U));
            } else {
                  luramas::il::lifter::builder::cast<32U>(dest, temp);
                  dest.write(0U, 7U, temp.read(24U, 31U));
                  dest.write(8U, 15U, temp.read(16U, 23U));
                  dest.write(16U, 23U, temp.read(8U, 15U));
                  dest.write(24U, 31U, temp.read(0U, 7U));
            };
            return;
      }

      void BT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &offset = operands.back();

            FCF = dest.read(dest, offset);
            return;
      }

      void BTC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &offset = operands.back();

            FCF = dest.read(dest, offset);
            dest.write(dest, offset, ~dest.read(dest, offset));
            return;
      }

      void BTR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &offset = operands.back();

            FCF = dest.read(dest, offset);
            dest.write(dest, offset, 0U);
            return;
      }

      void BTS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &offset = operands.back();

            FCF = dest.read(dest, offset);
            dest.write(dest, offset, 1U);
            return;
      }

      void BZHI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            const auto n = src2.read(0, 7);
            dest = src1;
            kif(n < dest.bits()) {
                  dest.write(n, dest.bits() - 1U, 0);
            }
            kend;

            FCF = (n > dest.bits() - 1U);
            FOF = 0U;

            tools::eflags::mutate<xeflags::SF, xeflags::ZF>(registrar, tools::eflags::flag_data(registrar.inst, src1, dest, src2));
            return;
      }

      void CALL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            build::page_calls(registrar, operands, registrar.hw_constants.instruction_interp == 64U ? REG_RSP : registrar.hw_constants.instruction_interp == 32U ? REG_ESP
                                                                                                                                                                 : REG_SP);
            return;
      }

      void CBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_AX = REG_AL << 8U;
            return;
      }

      void CDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_EDX = REG_EAX >> 31U;
            return;
      }

      void CDQE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_RAX = REG_EAX;
            return;
      }

      void FCHS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_ST0 = -REG_ST0;
            return;
      }

      void CLAC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FAF = 0U;
            return;
      }

      void CLC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FCF = 0U;
            return;
      }

      void CLD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FDF = 0U;
            return;
      }

      void CLDEMOTE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CLFLUSH(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CLFLUSHOPT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CLGI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FGI = 0U;
            return;
      }

      void CLI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FIF = 0U;
            return;
      }

      void CLRSSBSY(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CLTS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CLWB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CLZERO(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FCF = ~FCF;
            return;
      }

      void CMOVA(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 0U || FZF == 0U) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVAE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 0U) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 1U) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVBE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 1U || FZF == 1U) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVBE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FCMOVB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMOVE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FZF == 1U) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMOVG(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FZF == 0U || FSF == FOF) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVGE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FSF == FOF) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FSF != FOF);
            {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVLE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FZF == 1U || FSF != FOF) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVNBE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FCMOVNB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMOVNE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FZF == 0U);
            {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVNE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMOVNO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FOF == 0U) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVNP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FPF == 0U) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVNU(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FCMOVNP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMOVNS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FSF == 0U) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FOF == 1U) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FPF == 1U) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVU(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMOVS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FSF == 1U) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &src1 = operands.front();
            const auto &src2 = operands.back();
            function_handler f(registrar.build);

            const auto result = src1 - luramas::il::lifter::builder::libraries::structure::extend_sign(f, src2, src2.type());

            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, src1, result, src2));
            return;
      }

      void CMPPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMPPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMPSB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMPSD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMPSQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMPSS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMPSW(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CMPXCHG16B(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            const auto accumulator = REG_AX;

            kif(accumulator == dest) {
                  FZF = 1U;
                  dest = src;
            }
            kelse;
            {
                  FZF = 1U;
                  accumulator = dest;
            }
            kend;
            tools::eflags::mutate<xeflags::CF, xeflags::PF, xeflags::AF, xeflags::SF, xeflags::OF>(registrar, tools::eflags::flag_data(registrar.inst, dest, dest, src));
            return;
      }

      void CMPXCHG(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            const auto accumulator = registrar.hw_constants.instruction_interp == 64U ? REG_RAX : REG_EAX;

            FZF = 1U;
            kif(accumulator == dest) {
                  dest = src;
            }
            kelse;
            {
                  accumulator = dest;
            }
            kend;
            tools::eflags::mutate<xeflags::CF, xeflags::PF, xeflags::AF, xeflags::SF, xeflags::OF>(registrar, tools::eflags::flag_data(registrar.inst, dest, dest, src));
            return;
      }

      void CMPXCHG8B(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            const auto accumulator = REG_AL;

            FZF = 1U;
            kif(accumulator == dest);
            {
                  dest = src;
            }
            kelse;
            {
                  accumulator = dest;
            }
            kend;
            tools::eflags::mutate<xeflags::CF, xeflags::PF, xeflags::AF, xeflags::SF, xeflags::OF>(registrar, tools::eflags::flag_data(registrar.inst, dest, dest, src));
            return;
      }

      void COMISD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto l = operands.front().read(0, 63);
            const auto r = operands.back().read(0, 63);

            kif(l != r);
            {
                  FZF = 1U;
                  FPF = 1U;
                  FCF = 1U;
            }
            kelseif(l > r);
            {
                  FZF = 0U;
                  FPF = 0U;
                  FCF = 0U;
            }
            kelseif(l < r);
            {
                  FZF = 0U;
                  FPF = 0U;
                  FCF = 1U;
            }
            kelseif(l == r);
            {
                  FZF = 1U;
                  FPF = 0U;
                  FCF = 1U;
            }
            kend;
            kend;
            kend;
            kend;
            FOF = 0U;
            FAF = 0U;
            FSF = 0U;
            return;
      }

      void COMISS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto l = operands.front().read(0, 31);
            const auto r = operands.back().read(0, 31);

            kif(l != r);
            {
                  FZF = 1U;
                  FPF = 1U;
                  FCF = 1U;
            }
            kelseif(l > r);
            {
                  FZF = 0U;
                  FPF = 0U;
                  FCF = 0U;
            }
            kelseif(l < r);
            {
                  FZF = 0U;
                  FPF = 0U;
                  FCF = 1U;
            }
            kelseif(l == r);
            {
                  FZF = 1U;
                  FPF = 0U;
                  FCF = 1U;
            }
            kend;
            kend;
            kend;
            kend;
            FOF = 0U;
            FAF = 0U;
            FSF = 0U;
            return;
      }

      void FCOMP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FCOMPI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FCOMI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FCOM(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FCOS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CPUID(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::CPU::INFO, {REG_EAX, REG_ECX}, {REG_EAX, REG_EBX, REG_ECX, REG_EDX});
            return;
      }

      void CQO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_RDX = (REG_RAX >> 63U) & 0xFFFFFFFFFFFFFFFF;
            return;
      }

      void CRC32(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CVTDQ2PD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            dest.write(0, 63, LURAMAS_FBUILD_EXTEND_DOUBLE(src.read(0, 31)));
            dest.write(64, 127, LURAMAS_FBUILD_EXTEND_DOUBLE(src.read(32, 63)));
            return;
      }

      void CVTDQ2PS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            dest.write(0, 31, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(0, 31)));
            dest.write(32, 63, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(32, 63)));
            dest.write(64, 95, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(64, 95)));
            dest.write(96, 127, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(96, 127)));
            return;
      }

      void CVTPD2DQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            dest.write(0U, 31U, LURAMAS_FBUILD_EXTEND_32(src.read(0U, 63U)));
            dest.write(32U, 63U, LURAMAS_FBUILD_EXTEND_32(src.read(64U, 127U)));
            dest.write(64U, 127U, 0U);
            return;
      }

      void CVTPD2PS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            dest.write(0U, 31U, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(0U, 63U)));
            dest.write(32U, 63U, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(64U, 127U)));
            dest.write(64U, 127U, 0U);
            return;
      }

      void CVTPS2DQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            dest.write(0U, 31U, LURAMAS_FBUILD_EXTEND_32(src.read(0U, 31U)));
            dest.write(32U, 63U, LURAMAS_FBUILD_EXTEND_32(src.read(32U, 63U)));
            dest.write(64U, 95U, LURAMAS_FBUILD_EXTEND_32(src.read(64U, 95U)));
            dest.write(96U, 127U, LURAMAS_FBUILD_EXTEND_32(src.read(96U, 127U)));
            return;
      }

      void CVTPS2PD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            dest.write(0U, 63U, LURAMAS_FBUILD_EXTEND_DOUBLE(src.read(0U, 31U)));
            dest.write(64U, 127U, LURAMAS_FBUILD_EXTEND_DOUBLE(src.read(32U, 63U)));
            return;
      }

      void CVTSD2SI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            dest = LURAMAS_FBUILD_EXTEND_64(src.read(0U, 63U));
            return;
      }

      void CVTSD2SS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            dest.write(0, 31, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(0, 63)));
            return;
      }

      void CVTSI2SD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            auto src = operands.back();
            dest.write(0U, 63U, LURAMAS_FBUILD_EXTEND_DOUBLE(src));
            return;
      }

      void CVTSI2SS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            auto src = operands.back();
            dest.write(0U, 31U, LURAMAS_FBUILD_EXTEND_FLOAT(src));
            return;
      }

      void CVTSS2SD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            dest.write(0U, 63U, LURAMAS_FBUILD_EXTEND_DOUBLE(src.read(0U, 31U)));
            return;
      }

      void CVTSS2SI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            if (registrar.hw_constants.instruction_interp == 64U) {
                  dest.write(0U, 63U, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(0U, 31U)));
            } else {
                  dest.write(0U, 31U, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(0U, 31U)));
            }
            return;
      }

      void CVTTPD2DQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CVTTPS2DQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CVTTSD2SI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CVTTSS2SI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void CWD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_DX = REG_AX >> 15U;
            return;
      }

      void CWDE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_EAX = REG_AX >> 15U;
            return;
      }

} // namespace vm

#endif // LURAMAS_TARGET_X86
