#ifdef LURAMAS_TARGET_X86
#include "common.hpp"

/* Instruction handlers: SAHF - UNPCKLPS */
namespace vm {

      void SAHF(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FSF = REG_AH;
            FZF = REG_AH;
            FAF = REG_AH;
            FPF = REG_AH;
            FCF = REG_AH;
            return;
      }

      void SAL(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            return;
      }

      void SALC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_AL = 0x00;
            kif(FCF == 1U) {
                  REG_AL = 0xFF;
            };
            kend;
            return;
      }

      void SAR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            function_handler f(registrar.build);
            const auto result = klura_vtemp;
            const auto &dest = operands.front();
            const auto &count = operands.back();

            const bool is_64bit = (registrar.hw_constants.suggested_bit_set == 64U);
            const auto count_mask = is_64bit ? 0x3F : 0x1F;

            auto temp_count = count & count_mask;

            if (is_64bit) {
                  result = (dest >> temp_count).cast(luramas::types::native::t_uint64);
            } else {
                  result = (dest >> temp_count).cast(luramas::types::native::t_uint32);
            }

            kif(temp_count != 0U) {
                  FCF = (dest >> (temp_count - 1U)) & 1U;
            }
            kend;

            kif(temp_count == 1U) {
                  FOF = 0U;
            }
            kend;

            tools::eflags::mutate<xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, dest, result, count));
            dest = result;
            return;
      }

      void SARX(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SAVEPREVSSP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SBB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto result = dest - src + FCF;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, dest, result, src));
            dest = result;
            return;
      }

      void SCASB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto temp = REG_AL - REG_DIL;

            kif(FDF == 0U);
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

      void SCASD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto temp = REG_EAX - REG_EDI;

            kif(FDF == 0U);
            {
                  REG_EDI += 4U;
            }
            kelse;
            {
                  REG_EDI -= 4U;
            }
            kend;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, REG_EAX, temp, REG_EDI));
            return;
      }

      void SCASQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto temp = REG_RAX - REG_RDI;

            kif(FDF == 0U) {
                  REG_RDI += 8U;
            }
            kelse;
            {
                  REG_RDI -= 8U;
            }
            kend;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, REG_RAX, temp, REG_RDI));
            return;
      }

      void SCASW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            const auto temp = REG_AX - REG_DI;

            kif(FDF == 0U) {
                  REG_EDI += 2U;
            }
            kelse;
            {
                  REG_EDI -= 2U;
            }
            kend;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, REG_AX, temp, REG_DI));
            return;
      }

      void SETAE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FCF == 0U;
            return;
      }

      void SETA(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FCF == 0U && FZF == 0U;
            return;
      }

      void SETBE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FCF == 1U || FZF == 1U;
            return;
      }

      void SETB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FCF == 1U;
            return;
      }

      void SETE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FZF == 1U;
            return;
      }

      void SETGE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FSF == FOF;
            return;
      }

      void SETG(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FZF == 0U && FSF == FOF;
            return;
      }

      void SETLE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FZF == 1U && FSF != FOF;
            return;
      }

      void SETL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FSF != FOF;
            return;
      }

      void SETNE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FZF == 0U;
            return;
      }

      void SETNO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FOF == 0U;
            return;
      }

      void SETNP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FPF == 0U;
            return;
      }

      void SETNS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FSF == 0U;
            return;
      }

      void SETO(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FOF == 1U;
            return;
      }

      void SETP(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FPF == 1U;
            return;
      }

      void SETSSBSY(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SETS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = FSF == 1U;
            return;
      }

      void SFENCE(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::MEMORY::FENCE::SET, {}, {});
            return;
      }

      void SGDT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            auto limit = klura_vtemp;
            auto base = klura_vtemp;
            klura_call(luramas::builtins::DESCRIPTOR::GET, {klura_tint(static_cast<std::uint8_t>(internal::data::table_hierarchy::global))}, {limit, base});
            dest.write(0U, 15U, limit);
            if (dest.bits() == 16U || dest.bits() == 32U) {
                  dest.write(16U, 47U, base);
            } else {
                  dest.write(16U, 79U, base);
            }
            return;
      }

      void SHA1MSG1(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SHA1MSG2(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SHA1NEXTE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SHA1RNDS4(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SHA256MSG1(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SHA256MSG2(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SHA256RNDS2(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SHL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            const auto product = dest << src;

            tools::eflags::mutate<xeflags::CF, xeflags::OF, xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, dest, product, src));
            dest = product;
            return;
      }

      void SHLD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SHLX(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = operands[1U] << operands.back();
            return;
      }

      void SHR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();
            const auto product = dest >> src;

            tools::eflags::mutate<xeflags::CF, xeflags::OF, xeflags::SF, xeflags::ZF, xeflags::PF>(registrar, tools::eflags::flag_data(registrar.inst, dest, product, src));
            dest = product;
            return;
      }

      void SHRD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SHRX(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = operands[1U] >> operands.back();
            return;
      }

      void SHUFPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SHUFPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SIDT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            auto limit = klura_vtemp;
            auto base = klura_vtemp;
            klura_call(luramas::builtins::INTERRUPT::TABLE::GET, {}, {limit, base});
            dest.write(0U, 15U, limit);
            if (dest.bits() == 16U || dest.bits() == 32U) {
                  dest.write(16U, 47U, base);
            } else {
                  dest.write(16U, 79U, base);
            }
            return;
      }

      void FSIN(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SKINIT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SLDT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            klura_call(luramas::builtins::DESCRIPTOR::GET, {klura_tint(static_cast<std::uint8_t>(internal::data::table_hierarchy::local))}, {dest});
            return;
      }

      void SLWPCB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SMSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = REG_CR0.read(0U, 15U);
            return;
      }

      void SQRTPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SQRTPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SQRTSD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SQRTSS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FSQRT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void STAC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FAC = 1U;
            return;
      }

      void STC(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FCF = 1U;
            return;
      }

      void STD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FDF = 1U;
            return;
      }

      void STGI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FGI = 1U;
            return;
      }

      void STI(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            FIF = 1U;
            return;
      }

      void STMXCSR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            registrar.build->load_internal_global(internal::globals::MXCSR, operands.front());
            return;
      }

      void STOSB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_AL.write(REG_AL);
            if (registrar.hw_constants.suggested_bit_set == 64U) {
                  kif(FDF == 0U);
                  {
                        ++REG_RDI;
                  }
                  kelse;
                  {
                        --REG_RDI;
                  }
                  kend;
            } else {
                  kif(FDF == 0U);
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

      void STOSD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_EAX.write(REG_EAX);
            if (registrar.hw_constants.suggested_bit_set == 64U) {
                  kif(FDF == 0U);
                  {
                        REG_RDI += 4U;
                  }
                  kelse;
                  {
                        REG_RDI -= 4U;
                  }
                  kend;
            } else {
                  kif(FDF == 0U);
                  {
                        REG_EDI += 4U;
                  }
                  kelse;
                  {
                        REG_EDI -= 4U;
                  }
                  kend;
            }
            return;
      }

      void STOSQ(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_RAX.write(REG_RAX);
            if (registrar.hw_constants.suggested_bit_set == 64U) {
                  kif(FDF == 0U);
                  {
                        REG_RDI += 8U;
                  }
                  kelse;
                  {
                        REG_RDI -= 8U;
                  }
                  kend;
            } else {

                  kif(FDF == 0U);
                  {
                        REG_EDI += 8U;
                  }
                  kelse;
                  {
                        REG_EDI -= 8U;
                  }
                  kend;
            }

            return;
      }

      void STOSW(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            REG_AX.write(REG_AX);
            if (registrar.hw_constants.suggested_bit_set == 64U) {
                  kif(FDF == 0U);
                  {

                        REG_RDI += 2U;
                  }
                  kelse;
                  {
                        REG_RDI -= 2U;
                  }
                  kend;
            } else {
                  kif(FDF == 0U);
                  {

                        REG_EDI += 2U;
                  }
                  kelse;
                  {
                        REG_EDI -= 2U;
                  }
                  kend;
            }
            return;
      }

      void STR(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            operands.front() = klura_internal_read(registrar, internal::globals::TASK_REGISTER);
            return;
      }

      void FST(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FSTP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SUB(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            const auto temp = dest - src;
            tools::eflags::mutate<F_COMMON>(registrar, tools::eflags::flag_data(registrar.inst, dest, temp, src));
            dest = temp;
            return;
      }

      void SUBPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63U, dest.read(0U, 63U) - src.read(0U, 63U));
            dest.write(64U, 127U, dest.read(64U, 127U) - src.read(64U, 127U));
            return;
      }

      void SUBPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, dest.read(0U, 31) - src.read(0U, 31));
            dest.write(32U, 63U, dest.read(32U, 63U) - src.read(32U, 63U));
            dest.write(64U, 95U, dest.read(64U, 95U) - src.read(64U, 95U));
            dest.write(96U, 127U, dest.read(96U, 127U) - src.read(96U, 127U));
            return;
      }

      void FSUBR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FISUBR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FSUBRP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SUBSD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 63, dest.read(0U, 63) - src.read(0U, 63));
            return;
      }

      void SUBSS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0U, 31U, dest.read(0U, 31) - src.read(0U, 31U));
            return;
      }

      void FSUB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FISUB(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FSUBP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SWAPGS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SYSCALL(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::SYS::CALL, REG_ALL_64_REGS, REG_ALL_64_REGS);
            return;
      }

      void SYSENTER(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::SYS::CALL, REG_ALL_32_REGS, REG_ALL_32_REGS);
            return;
      }

      void SYSEXIT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SYSEXITQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SYSRET(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void SYSRETQ(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void T1MSKC(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void TEST(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &src1 = operands.front();
            const auto &src2 = operands.back();
            function_handler f(registrar.build);

            const auto temp = src1 & src2;
            FSF = luramas::il::lifter::builder::libraries::structure::most_significant_bit(f, temp);
            FZF = temp == 0U;
            FPF = ~(temp.read(0U, 7U));
            FCF = 0U;
            FOF = 0U;
            return;
      }

      void TPAUSE(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FTST(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void TZCNT(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            auto temp = klura_vtemp;

            temp = 0U;
            dest = 0U;
            kwhile((temp < src.bits()) && (src.read(temp) == 0)) {
                  ++temp;
                  ++dest;
            }
            kwhile_end;
            FCF = dest == dest.bits();
            FZF = dest == 0U;
            return;
      }

      void TZMSK(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void UCOMISD(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto l = operands.front().read(0U, 63U);
            const auto r = operands.back().read(0U, 63U);

            const auto unordered = (l != l) | (r != r);
            FCF = (l < r) || unordered;
            FPF = unordered;
            FZF = (l == r) || unordered;
            FOF = 0U;
            FAF = 0U;
            FSF = 0U;
            return;
      }

      void UCOMISS(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

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
                  FCF = 0U;
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

      void FUCOMPI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FUCOMI(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FUCOMPP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FUCOMP(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void FUCOM(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void UD0(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::EXCEPTION::THROW, {klura_tint(static_cast<std::uint8_t>(internal::data::error_kind::undefined_opcode)), klura_tint(0U), operands.front()}, {});
            return;
      }

      void UD1(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            klura_call(luramas::builtins::EXCEPTION::THROW, {klura_tint(static_cast<std::uint8_t>(internal::data::error_kind::undefined_opcode)), klura_tint(1U), operands.front()}, {});
            return;
      }

      void UD2(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {

            klura_call(luramas::builtins::EXCEPTION::THROW, {klura_tint(static_cast<std::uint8_t>(internal::data::error_kind::undefined_opcode)), klura_tint(2U)}, {});
            return;
      }

      void UMONITOR(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void UMWAIT(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> & /*operands*/) {
            return;
      }

      void UNPCKHPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0, 63, src.read(64, 127));
            dest.write(64, 127, src.read(64, 127));
            return;
      }

      void UNPCKHPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            dest.write(0U, 31U, src1.read(64U, 95U));
            dest.write(32U, 63U, src2.read(64U, 95U));
            dest.write(64U, 95U, src1.read(96U, 127U));
            dest.write(96U, 127U, src2.read(96U, 127U));
            return;
      }

      void UNPCKLPD(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src = operands.back();

            dest.write(0, 63, src.read(0, 63));
            dest.write(64, 127, src.read(0, 63));
            return;
      }

      void UNPCKLPS(const registrar & /*registrar*/, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto &dest = operands.front();
            const auto &src1 = operands[1U];
            const auto &src2 = operands.back();

            if (dest.bits() == 128U) {

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
