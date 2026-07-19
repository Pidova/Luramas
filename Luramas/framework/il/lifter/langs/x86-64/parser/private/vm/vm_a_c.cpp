#ifdef LURAMAS_TARGET_X86
#include "common.hpp"

/* Instruction handlers: AAA - CWDE */
namespace vm {

      void AAA(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(((REG_AL & 0x0F) + (FAF << 3)) > 1u) {
                  REG_AX += 0x106;
                  FAF = 1u;
                  FCF = 1u;
            }
            kelse;
            {
                  FAF = 0u;
                  FCF = 0u;
            }
            kend;
            REG_AL &= 0x0F;
            return;
      }

      void AAD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto temp = (REG_AL + (REG_AH * 0x0A)) & 0xFF;
            tools::eflags::mutate<xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, REG_AL, temp, REG_AH));
            REG_AL = temp;
            REG_AH = 0u;
            return;
      }

      void AAM(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto temp_ah = temp(registrar, REG_AH);
            const auto temp_al = temp(registrar, REG_AL);

            REG_AH = REG_AL / 0x0A;
            REG_AL = REG_AL % 0x0A;

            tools::eflags::mutate<xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, temp_al, REG_AL, temp_ah));
            return;
      }

      void AAS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto cond = ((REG_AL & 0x0F) - 10u) >> 7u;
            cond |= FAF;

            REG_AL -= cond * 6u;
            REG_AH -= cond;
            FCF = cond;
            FAF = cond;

            REG_AL &= 0x0F;
            return;
      }

      void FABS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto t = temp(registrar, REG_ST0);
            t.cmp(0u);
            registrar.build->make_scope<luramas::il::arch::data::bin_kinds::lt_>(1u);
            {
                  t = !t;
            }
            registrar.build->close_scope();

            REG_ST0 = t;
            FC1 = 0u;
            return;
      }

      void ADC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

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

            const auto dest = operands.front();
            const auto src = operands.back();

            const auto temp = dest + src;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            dest = temp;
            return;
      }

      void ADDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63u, dest.read(0u, 63u) + src.read(0u, 63u));
            dest.write(64u, 127u, dest.read(64u, 127u) + src.read(64u, 127u));
            return;
      }

      void ADDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, dest.read(0u, 31) + src.read(0u, 31));
            dest.write(32u, 63u, dest.read(32u, 63u) + src.read(32u, 63u));
            dest.write(64u, 95u, dest.read(64u, 95u) + src.read(64u, 95u));
            dest.write(96u, 127u, dest.read(96u, 127u) + src.read(96u, 127u));
            return;
      }

      void ADDSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63, dest.read(0u, 63) + src.read(0u, 63));
            return;
      }

      void ADDSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, dest.read(0u, 31) + src.read(0u, 31u));
            return;
      }

      void ADDSUBPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            auto dest_lower = dest.read(0u, 63u);
            auto dest_upper = dest.read(64u, 127u);
            auto src_lower = src.read(0u, 63u);
            auto src_upper = src.read(64u, 127u);

            auto result_lower = dest_lower + src_lower;
            auto result_upper = dest_upper - src_upper;

            dest.write(0u, 63u, result_lower);
            dest.write(64u, 127u, result_upper);
            return;
      }

      void ADDSUBPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            const auto d0 = dest.read(0u, 31u);
            const auto d1 = dest.read(32u, 63u);
            const auto d2 = dest.read(64u, 95u);
            const auto d3 = dest.read(96u, 127u);

            const auto s0 = src.read(0u, 31u);
            const auto s1 = src.read(32u, 63u);
            const auto s2 = src.read(64u, 95u);
            const auto s3 = src.read(96u, 127u);

            dest.write(0u, 31u, d0 + s0);
            dest.write(32u, 63u, d1 - s1);
            dest.write(64u, 95u, d2 + s2);
            dest.write(96u, 127u, d3 - s3);
            return;
      }

      void FADD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FIADD(registrar, operands);
            return;
      }

      void FIADD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto dest = operands.front();
            auto src = operands.back();
            function_handler f(registrar.build);

            dest += LURAMAS_FBUILD_EXTEND_FLOAT(src);
            FC1 = (luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, dest) == 0u) && (dest != 0u);
            return;
      }

      void ADOX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            const auto temp = dest + src + registrar.getf<xeflags::OF>();
            tools::eflags::mutate<xeflags::OF>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            dest = temp;
            return;
      }

      void AESDECLAST(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void AESDEC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void AESENCLAST(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void AESENC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void AESIMC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void AESKEYGENASSIST(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void AND(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            const auto temp = dest & src;
            tools::eflags::mutate<xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            dest = temp;
            FOF = 0u;
            FCF = 0u;
            return;
      }

      void ANDN(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src1 = operands[1u];
            const auto src2 = operands.back();

            const auto temp = (~src1) & src2;
            tools::eflags::mutate<xeflags::SF, xeflags::ZF>(registrar, tools::eflags::flag_data(registrar.inst, src1, temp, src2));
            dest = temp;
            FOF = 0u;
            FCF = 0u;
            return;
      }

      void ANDNPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63u, (~dest.read(0u, 63u)) & src.read(0u, 63u));
            dest.write(64u, 127u, (~dest.read(64u, 127u)) & src.read(64u, 127u));
            return;
      }

      void ANDNPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, (~dest.read(0u, 31u)) & src.read(0u, 31u));
            dest.write(32u, 63u, (~dest.read(32u, 63u)) & src.read(32u, 63u));
            dest.write(64u, 95u, (~dest.read(64u, 95u)) & src.read(64u, 95u));
            dest.write(96u, 127u, (~dest.read(96u, 127u)) & src.read(96u, 127u));
            return;
      }

      void ANDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src1 = operands[1u];
            const auto src2 = operands.back();

            dest.write(0, 63, src1.read(0, 63) & src2.read(0, 63));
            dest.write(64, 127, src1.read(64, 127) & src2.read(64, 127));
            return;
      }

      void ANDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, dest.read(0u, 31) & src.read(0u, 31));
            dest.write(32u, 63u, dest.read(32u, 63u) & src.read(32u, 63u));
            dest.write(64u, 95u, dest.read(64u, 95u) & src.read(64u, 95u));
            dest.write(96u, 127u, dest.read(96u, 127u) & src.read(96u, 127u));
            return;
      }

      void ARPL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            if (registrar.suggested_bit_set == 64u) {

                  MOVSXD(registrar, operands);
            } else {

                  const auto dest_rpl = dest & 0x3;
                  const auto src_rpl = src & 0x3;
                  kif(dest_rpl < src_rpl) {
                        FZF = 1u;
                        dest = (dest & ~0x3) | src_rpl;
                  }
                  kelse;
                  {
                        FZF = 0u;
                  }
                  kend;
            }
            return;
      }

      void BEXTR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto dest = operands.front();
            auto src1 = operands[1u];
            auto src2 = operands.back();

            const auto start = src2.read(0u, 7u);
            auto t = LURAMAS_FBUILD_EXTEND_512(src1).read(start, start + src2.read(8u, 15u) - 1u);
            dest = LURAMAS_FBUILD_ZEROEXTEND(t, t);
            FZF = 0u;
            FCF = 0u;
            FOF = 0u;
            return;
      }

      void BLCFILL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BLCI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BLCIC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BLCMSK(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BLCS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BLENDPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BLENDPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BLENDVPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BLENDVPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BLSFILL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BLSI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            const auto temp = -src & src;
            FSF = temp.read(temp.bits() - 1u);
            FZF = temp == 0;
            FCF = src != 0u;
            FOF = 0u;
            dest = temp;
            return;
      }

      void BLSIC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BLSMSK(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            const auto temp = (src - 1u) ^ src;
            FSF = temp.read(temp.bits() - 1u);
            FZF = 0u;
            FOF = 0u;
            FCF = src == 0u;
            dest = temp;
            return;
      }

      void BLSR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            const auto temp = (src - 1u) & src;

            FSF = temp < 0;
            FZF = temp == 0;
            FCF = src == 0;
            dest = temp;
            return;
      }

      void BNDCL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BNDCN(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BNDCU(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BNDLDX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BNDMK(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BNDMOV(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BNDSTX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BOUND(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void BSF(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            kif(src == 0u) {
                  FZF = 1u;
            }
            kelse;
            {
                  FZF = 0u;
                  auto temp = klura_vtemp;
                  temp.cast(dest.r.r);
                  temp = 0u;
                  kwhile(src[temp] == 0u) {
                        ++temp;
                  }
                  kend;
                  dest = temp;
            }
            kend;
            return;
      }

      void BSR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            kif(src == 0u) {
                  FZF = 1u;
            }
            kelse;
            {
                  FZF = 0u;
                  auto temp = klura_vtemp;
                  temp = dest.bits() - 1u;
                  kwhile(src[temp] == 0u) {
                        temp -= 1u;
                  }
                  kend;
                  dest = temp;
            }
            kend;
            return;
      }

      void BSWAP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            auto dest = operands.front();
            auto temp = dest;

            if (dest.bits() == 64u) {
                  luramas::il::lifter::builder::cast<64u>(dest, temp);
                  dest.write(0u, 7u, temp.read(56u, 63u));
                  dest.write(8u, 15u, temp.read(48u, 55u));
                  dest.write(16u, 23u, temp.read(40u, 47u));
                  dest.write(24u, 31u, temp.read(32u, 39u));
                  dest.write(32u, 39u, temp.read(24u, 31u));
                  dest.write(40u, 47u, temp.read(16u, 23u));
                  dest.write(48u, 55u, temp.read(8u, 15u));
                  dest.write(56u, 63u, temp.read(0u, 7u));
            } else {
                  luramas::il::lifter::builder::cast<32u>(dest, temp);
                  dest.write(0u, 7u, temp.read(24u, 31u));
                  dest.write(8u, 15u, temp.read(16u, 23u));
                  dest.write(16u, 23u, temp.read(8u, 15u));
                  dest.write(24u, 31u, temp.read(0u, 7u));
            };
            return;
      }

      void BT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto offset = operands.back();

            FCF = dest.read(dest, offset);
            return;
      }

      void BTC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto offset = operands.back();

            FCF = dest.read(dest, offset);
            dest.write(dest, offset, ~dest.read(dest, offset));
            return;
      }

      void BTR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto offset = operands.back();

            FCF = dest.read(dest, offset);
            dest.write(dest, offset, 0u);
            return;
      }

      void BTS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto offset = operands.back();

            FCF = dest.read(dest, offset);
            dest.write(dest, offset, 1u);
            return;
      }

      void BZHI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src1 = operands[1u];
            const auto src2 = operands.back();

            const auto n = src2.read(0, 7);
            dest = src1;
            kif(n < dest.bits()) {
                  dest.write(n, dest.bits() - 1u, 0);
            }
            kend;

            FCF = (n > dest.bits() - 1u);
            FOF = 0u;

            tools::eflags::mutate<xeflags::SF, xeflags::ZF>(registrar, tools::eflags::flag_data(registrar.inst, src1, dest, src2));
            return;
      }

      void CALL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            build::page_calls(registrar, operands, registrar.suggested_bit_set == 64u ? REG_RSP : registrar.suggested_bit_set == 32u ? REG_ESP
                                                                                                                                     : REG_SP);
            return;
      }

      void CBW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_AX = REG_AL << 8u;
            return;
      }

      void CDQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_EDX = REG_EAX >> 31u;
            return;
      }

      void CDQE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_RAX = REG_EAX;
            return;
      }

      void FCHS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_ST0 = -REG_ST0;
            return;
      }

      void CLAC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FAF = 0u;
            return;
      }

      void CLC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FCF = 0u;
            return;
      }

      void CLD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FDF = 0u;
            return;
      }

      void CLDEMOTE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CLFLUSH(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CLFLUSHOPT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CLGI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FGI = 0u;
            return;
      }

      void CLI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FIF = 0u;
            return;
      }

      void CLRSSBSY(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CLTS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CLWB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CLZERO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FCF = ~FCF;
            return;
      }

      void CMOVA(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 0u || FZF == 0u) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVAE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 0u) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 1u) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVBE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FCF == 1u || FZF == 1u) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVBE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FCMOVB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMOVE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FZF == 1u) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMOVG(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FZF == 0u || FSF == FOF) {
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

            kif(FZF == 1u || FSF != FOF) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVNBE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FCMOVNB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMOVNE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FZF == 0u);
            {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVNE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMOVNO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FOF == 0u) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVNP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FPF == 0u) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVNU(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FCMOVNP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMOVNS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FSF == 0u) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FOF == 1u) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMOVP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FPF == 1u) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void FCMOVU(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMOVS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            kif(FSF == 1u) {
                  operands.front() = operands.back();
            }
            kend;
            return;
      }

      void CMP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto src1 = operands.front();
            const auto src2 = operands.back();
            function_handler f(registrar.build);

            const auto result = src1 - luramas::il::lifter::builder::libraries::structure::extend_sign(f, src2, src2.type());

            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, src1, result, src2));
            return;
      }

      void CMPPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMPPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMPSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMPSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMPSQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMPSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMPSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CMPXCHG16B(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            const auto accumulator = REG_AX;

            kif(accumulator == dest) {
                  FZF = 1u;
                  dest = src;
            }
            kelse;
            {
                  FZF = 1u;
                  accumulator = dest;
            }
            kend;
            tools::eflags::mutate<xeflags::CF, xeflags::PF, xeflags::AF, xeflags::SF, xeflags::OF>(registrar, tools::eflags::flag_data(registrar.inst, dest, dest, src));
            return;
      }

      void CMPXCHG(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            const auto accumulator = registrar.suggested_bit_set == 64u ? REG_RAX : REG_EAX;

            FZF = 1u;
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

            const auto dest = operands.front();
            const auto src = operands.back();
            const auto accumulator = REG_AL;

            FZF = 1u;
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
                  FZF = 1u;
                  FPF = 1u;
                  FCF = 1u;
            }
            kelseif(l > r);
            {
                  FZF = 0u;
                  FPF = 0u;
                  FCF = 0u;
            }
            kelseif(l < r);
            {
                  FZF = 0u;
                  FPF = 0u;
                  FCF = 1u;
            }
            kelseif(l == r);
            {
                  FZF = 1u;
                  FPF = 0u;
                  FCF = 1u;
            }
            kend;
            kend;
            kend;
            kend;
            FOF = 0u;
            FAF = 0u;
            FSF = 0u;
            return;
      }

      void COMISS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto l = operands.front().read(0, 31);
            const auto r = operands.back().read(0, 31);

            kif(l != r);
            {
                  FZF = 1u;
                  FPF = 1u;
                  FCF = 1u;
            }
            kelseif(l > r);
            {
                  FZF = 0u;
                  FPF = 0u;
                  FCF = 0u;
            }
            kelseif(l < r);
            {
                  FZF = 0u;
                  FPF = 0u;
                  FCF = 1u;
            }
            kelseif(l == r);
            {
                  FZF = 1u;
                  FPF = 0u;
                  FCF = 1u;
            }
            kend;
            kend;
            kend;
            kend;
            FOF = 0u;
            FAF = 0u;
            FSF = 0u;
            return;
      }

      void FCOMP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FCOMPI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FCOMI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FCOM(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FCOS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CPUID(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::CPU::INFO, {REG_EAX, REG_ECX}, {REG_EAX, REG_EBX, REG_ECX, REG_EDX});
            return;
      }

      void CQO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_RDX = (REG_RAX >> 63u) & 0xFFFFFFFFFFFFFFFF;
            return;
      }

      void CRC32(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CVTDQ2PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest.write(0, 63, LURAMAS_FBUILD_EXTEND_DOUBLE(src.read(0, 31)));
            dest.write(64, 127, LURAMAS_FBUILD_EXTEND_DOUBLE(src.read(32, 63)));
            return;
      }

      void CVTDQ2PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest.write(0, 31, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(0, 31)));
            dest.write(32, 63, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(32, 63)));
            dest.write(64, 95, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(64, 95)));
            dest.write(96, 127, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(96, 127)));
            return;
      }

      void CVTPD2DQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest.write(0u, 31u, LURAMAS_FBUILD_EXTEND_32(src.read(0u, 63u)));
            dest.write(32u, 63u, LURAMAS_FBUILD_EXTEND_32(src.read(64u, 127u)));
            dest.write(64u, 127u, 0u);
            return;
      }

      void CVTPD2PS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest.write(0u, 31u, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(0u, 63u)));
            dest.write(32u, 63u, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(64u, 127u)));
            dest.write(64u, 127u, 0u);
            return;
      }

      void CVTPS2DQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest.write(0u, 31u, LURAMAS_FBUILD_EXTEND_32(src.read(0u, 31u)));
            dest.write(32u, 63u, LURAMAS_FBUILD_EXTEND_32(src.read(32u, 63u)));
            dest.write(64u, 95u, LURAMAS_FBUILD_EXTEND_32(src.read(64u, 95u)));
            dest.write(96u, 127u, LURAMAS_FBUILD_EXTEND_32(src.read(96u, 127u)));
            return;
      }

      void CVTPS2PD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest.write(0u, 63u, LURAMAS_FBUILD_EXTEND_DOUBLE(src.read(0u, 31u)));
            dest.write(64u, 127u, LURAMAS_FBUILD_EXTEND_DOUBLE(src.read(32u, 63u)));
            return;
      }

      void CVTSD2SI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest = LURAMAS_FBUILD_EXTEND_64(src.read(0u, 63u));
            return;
      }

      void CVTSD2SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest.write(0, 31, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(0, 63)));
            return;
      }

      void CVTSI2SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            auto src = operands.back();
            dest.write(0u, 63u, LURAMAS_FBUILD_EXTEND_DOUBLE(src));
            return;
      }

      void CVTSI2SS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            auto src = operands.back();
            dest.write(0u, 31u, LURAMAS_FBUILD_EXTEND_FLOAT(src));
            return;
      }

      void CVTSS2SD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            dest.write(0u, 63u, LURAMAS_FBUILD_EXTEND_DOUBLE(src.read(0u, 31u)));
            return;
      }

      void CVTSS2SI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            if (registrar.suggested_bit_set == 64u) {
                  dest.write(0u, 63u, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(0u, 31u)));
            } else {
                  dest.write(0u, 31u, LURAMAS_FBUILD_EXTEND_FLOAT(src.read(0u, 31u)));
            }
            return;
      }

      void CVTTPD2DQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CVTTPS2DQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CVTTSD2SI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CVTTSS2SI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void CWD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_DX = REG_AX >> 15u;
            return;
      }

      void CWDE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_EAX = REG_AX >> 15u;
            return;
      }

} // namespace vm

#endif // LURAMAS_TARGET_X86
