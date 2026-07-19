#ifdef LURAMAS_TARGET_X86
#include "common.hpp"

/* Instruction handlers: SAHF - UNPCKLPS */
namespace vm {

      void SAHF(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FSF = REG_AH;
            FZF = REG_AH;
            FAF = REG_AH;
            FPF = REG_AH;
            FCF = REG_AH;
            return;
      }

      void SAL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            return;
      }

      void SALC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_AL = 0x00;
            kif(FCF == 1u) {
                  REG_AL = 0xFF;
            };
            kend;
            return;
      }

      void SAR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            const auto result = klura_vtemp;
            const auto DEST = operands.front();
            const auto COUNT = operands.back();

            const bool is_64bit = (registrar.suggested_bit_set == 64u);
            const auto countMASK = is_64bit ? 0x3F : 0x1F;

            auto tempCOUNT = COUNT & countMASK;

            if (is_64bit) {
                  result = (DEST >> tempCOUNT).cast(luramas::types::native::t_uint64);
            } else {
                  result = (DEST >> tempCOUNT).cast(luramas::types::native::t_uint32);
            }

            kif(tempCOUNT != 0u) {
                  FCF = (DEST >> (tempCOUNT - 1u)) & 1u;
            }
            kend;

            kif(tempCOUNT == 1u) {
                  FOF = 0u;
            }
            kend;

            tools::eflags::mutate<xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, DEST, result, COUNT));
            DEST = result;
            return;
      }

      void SARX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SAVEPREVSSP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SBB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            const auto result = dest - src + FCF;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, dest, result, src));
            dest = result;
            return;
      }

      void SCASB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto temp = REG_AL - REG_DIL;

            kif(FDF == 0u);
            {
                  ++REG_EDI;
            }
            kelse;
            {
                  --REG_EDI;
            }
            kend;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, REG_AL, temp, REG_DIL));
            return;
      }

      void SCASD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto temp = REG_EAX - REG_EDI;

            kif(FDF == 0u);
            {
                  REG_EDI += 4u;
            }
            kelse;
            {
                  REG_EDI -= 4u;
            }
            kend;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, REG_EAX, temp, REG_EDI));
            return;
      }

      void SCASQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto temp = REG_RAX - REG_RDI;

            kif(FDF == 0u) {
                  REG_RDI += 8u;
            }
            kelse;
            {
                  REG_RDI -= 8u;
            }
            kend;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, REG_RAX, temp, REG_RDI));
            return;
      }

      void SCASW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto temp = REG_AX - REG_DI;

            kif(FDF == 0u) {
                  REG_EDI += 2u;
            }
            kelse;
            {
                  REG_EDI -= 2u;
            }
            kend;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, REG_AX, temp, REG_DI));
            return;
      }

      void SETAE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FCF == 0u;
            return;
      }

      void SETA(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FCF == 0u && FZF == 0u;
            return;
      }

      void SETBE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FCF == 1u || FZF == 1u;
            return;
      }

      void SETB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FCF == 1u;
            return;
      }

      void SETE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FZF == 1u;
            return;
      }

      void SETGE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FSF == FOF;
            return;
      }

      void SETG(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FZF == 0u && FSF == FOF;
            return;
      }

      void SETLE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FZF == 1u && FSF != FOF;
            return;
      }

      void SETL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FSF != FOF;
            return;
      }

      void SETNE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FZF == 0u;
            return;
      }

      void SETNO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FOF == 0u;
            return;
      }

      void SETNP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FPF == 0u;
            return;
      }

      void SETNS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FSF == 0u;
            return;
      }

      void SETO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FOF == 1u;
            return;
      }

      void SETP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FPF == 1u;
            return;
      }

      void SETSSBSY(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SETS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FSF == 1u;
            return;
      }

      void SFENCE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::MEMORY::FENCE::SET, {}, {});
            return;
      }

      void SGDT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            auto limit = klura_vtemp;
            auto base = klura_vtemp;
            klura_call(luramas::builtins::DESCRIPTOR::GET, {klura_tint(static_cast<std::uint8_t>(internal::data::table_hierarchy::global))}, {limit, base});
            dest.write(0u, 15u, limit);
            if (dest.bits() == 16u || dest.bits() == 32u) {
                  dest.write(16u, 47u, base);
            } else {
                  dest.write(16u, 79u, base);
            }
            return;
      }

      void SHA1MSG1(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SHA1MSG2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SHA1NEXTE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SHA1RNDS4(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SHA256MSG1(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SHA256MSG2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SHA256RNDS2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SHL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            const auto product = dest << src;

            tools::eflags::mutate<xeflags::CF, xeflags::OF, xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, dest, product, src));
            dest = product;
            return;
      }

      void SHLD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SHLX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = operands[1u] << operands.back();
            return;
      }

      void SHR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();
            const auto product = dest >> src;

            tools::eflags::mutate<xeflags::CF, xeflags::OF, xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, dest, product, src));
            dest = product;
            return;
      }

      void SHRD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SHRX(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = operands[1u] >> operands.back();
            return;
      }

      void SHUFPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SHUFPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SIDT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            auto limit = klura_vtemp;
            auto base = klura_vtemp;
            klura_call(luramas::builtins::INTERRUPT::TABLE::GET, {}, {limit, base});
            dest.write(0u, 15u, limit);
            if (dest.bits() == 16u || dest.bits() == 32u) {
                  dest.write(16u, 47u, base);
            } else {
                  dest.write(16u, 79u, base);
            }
            return;
      }

      void FSIN(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SKINIT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SLDT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            klura_call(luramas::builtins::DESCRIPTOR::GET, {klura_tint(static_cast<std::uint8_t>(internal::data::table_hierarchy::local))}, {dest});
            return;
      }

      void SLWPCB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SMSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = REG_CR0.read(0u, 15u);
            return;
      }

      void SQRTPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SQRTPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SQRTSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SQRTSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FSQRT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void STAC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FAC = 1u;
            return;
      }

      void STC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FCF = 1u;
            return;
      }

      void STD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FDF = 1u;
            return;
      }

      void STGI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FGI = 1u;
            return;
      }

      void STI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            FIF = 1u;
            return;
      }

      void STMXCSR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            registrar.build->load_internal_global(internal::globals::MXCSR, operands.front());
            return;
      }

      void STOSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_AL.write(REG_AL);
            if (registrar.suggested_bit_set == 64u) {
                  kif(FDF == 0u);
                  {
                        ++REG_RDI;
                  }
                  kelse;
                  {
                        --REG_RDI;
                  }
                  kend;
            } else {
                  kif(FDF == 0u);
                  {
                        ++REG_EDI;
                  }
                  kelse;
                  {
                        --REG_EDI;
                  }
                  kend;
            }
            return;
      }

      void STOSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_EAX.write(REG_EAX);
            if (registrar.suggested_bit_set == 64u) {
                  kif(FDF == 0u);
                  {
                        REG_RDI += 4u;
                  }
                  kelse;
                  {
                        REG_RDI -= 4u;
                  }
                  kend;
            } else {
                  kif(FDF == 0u);
                  {
                        REG_EDI += 4u;
                  }
                  kelse;
                  {
                        REG_EDI -= 4u;
                  }
                  kend;
            }
            return;
      }

      void STOSQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_RAX.write(REG_RAX);
            if (registrar.suggested_bit_set == 64u) {
                  kif(FDF == 0u);
                  {
                        REG_RDI += 8u;
                  }
                  kelse;
                  {
                        REG_RDI -= 8u;
                  }
                  kend;
            } else {

                  kif(FDF == 0u);
                  {
                        REG_EDI += 8u;
                  }
                  kelse;
                  {
                        REG_EDI -= 8u;
                  }
                  kend;
            }

            return;
      }

      void STOSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            REG_AX.write(REG_AX);
            if (registrar.suggested_bit_set == 64u) {
                  kif(FDF == 0u);
                  {

                        REG_RDI += 2u;
                  }
                  kelse;
                  {
                        REG_RDI -= 2u;
                  }
                  kend;
            } else {
                  kif(FDF == 0u);
                  {

                        REG_EDI += 2u;
                  }
                  kelse;
                  {
                        REG_EDI -= 2u;
                  }
                  kend;
            }
            return;
      }

      void STR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = klura_internal_read(registrar, internal::globals::TASK_REGISTER);
            return;
      }

      void FST(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FSTP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SUB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            const auto temp = dest - src;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            dest = temp;
            return;
      }

      void SUBPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63u, dest.read(0u, 63u) - src.read(0u, 63u));
            dest.write(64u, 127u, dest.read(64u, 127u) - src.read(64u, 127u));
            return;
      }

      void SUBPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, dest.read(0u, 31) - src.read(0u, 31));
            dest.write(32u, 63u, dest.read(32u, 63u) - src.read(32u, 63u));
            dest.write(64u, 95u, dest.read(64u, 95u) - src.read(64u, 95u));
            dest.write(96u, 127u, dest.read(96u, 127u) - src.read(96u, 127u));
            return;
      }

      void FSUBR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FISUBR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FSUBRP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SUBSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 63, dest.read(0u, 63) - src.read(0u, 63));
            return;
      }

      void SUBSS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0u, 31u, dest.read(0u, 31) - src.read(0u, 31u));
            return;
      }

      void FSUB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FISUB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FSUBP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SWAPGS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SYSCALL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::SYS::CALL, REG_ALL_64_REGS, REG_ALL_64_REGS);
            return;
      }

      void SYSENTER(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::SYS::CALL, REG_ALL_32_REGS, REG_ALL_32_REGS);
            return;
      }

      void SYSEXIT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SYSEXITQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SYSRET(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void SYSRETQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void T1MSKC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void TEST(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto src1 = operands.front();
            const auto src2 = operands.back();
            function_handler f(registrar.build);

            const auto temp = src1 & src2;
            FSF = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, temp);
            FZF = temp == 0u;
            FPF = ~(temp.read(0u, 7u));
            FCF = 0u;
            FOF = 0u;
            return;
      }

      void TPAUSE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FTST(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void TZCNT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            auto temp = klura_vtemp;

            temp = 0u;
            dest = 0u;
            kwhile((temp < src.bits()) && (src.read(temp) == 0)) {
                  ++temp;
                  ++dest;
            }
            kwhile_end;
            FCF = dest == dest.bits();
            FZF = dest == 0u;
            return;
      }

      void TZMSK(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void UCOMISD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto l = operands.front().read(0u, 63u);
            const auto r = operands.back().read(0u, 63u);

            const auto unordered = (l != l) | (r != r);
            FCF = (l < r) || unordered;
            FPF = unordered;
            FZF = (l == r) || unordered;
            FOF = 0u;
            FAF = 0u;
            FSF = 0u;
            return;
      }

      void UCOMISS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

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
                  FCF = 0u;
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

      void FUCOMPI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FUCOMI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FUCOMPP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FUCOMP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void FUCOM(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void UD0(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::EXCEPTION::THROW, {klura_tint(static_cast<std::uint8_t>(internal::data::error_kind::undefined_opcode)), klura_tint(0u), operands.front()}, {});
            return;
      }

      void UD1(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::EXCEPTION::THROW, {klura_tint(static_cast<std::uint8_t>(internal::data::error_kind::undefined_opcode)), klura_tint(1u), operands.front()}, {});
            return;
      }

      void UD2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::EXCEPTION::THROW, {klura_tint(static_cast<std::uint8_t>(internal::data::error_kind::undefined_opcode)), klura_tint(2u)}, {});
            return;
      }

      void UMONITOR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void UMWAIT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {
            return;
      }

      void UNPCKHPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0, 63, src.read(64, 127));
            dest.write(64, 127, src.read(64, 127));
            return;
      }

      void UNPCKHPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src1 = operands[1u];
            const auto src2 = operands.back();

            dest.write(0u, 31u, src1.read(64u, 95u));
            dest.write(32u, 63u, src2.read(64u, 95u));
            dest.write(64u, 95u, src1.read(96u, 127u));
            dest.write(96u, 127u, src2.read(96u, 127u));
            return;
      }

      void UNPCKLPD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src = operands.back();

            dest.write(0, 63, src.read(0, 63));
            dest.write(64, 127, src.read(0, 63));
            return;
      }

      void UNPCKLPS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto dest = operands.front();
            const auto src1 = operands[1u];
            const auto src2 = operands.back();

            if (dest.bits() == 128u) {

                  dest.write(0, 31, src1.read(0, 31));
                  dest.write(32, 63, src2.read(0, 31));
                  dest.write(64, 95, src1.read(32, 63));
                  dest.write(96, 127, src2.read(32, 63));
            } else {

                  dest.write(0, 31, src1.read(0, 31));
                  dest.write(32, 63, src2.read(0, 31));
                  dest.write(64, 95, src1.read(32, 63));
                  dest.write(96, 127, src2.read(32, 63));
                  dest.write(128, 159, src1.read(128, 159));
                  dest.write(160, 191, src2.read(128, 159));
                  dest.write(192, 223, src1.read(160, 191));
                  dest.write(224, 225, src2.read(160, 191));
            }
            return;
      }
} // namespace vm

#endif // LURAMAS_TARGET_X86
