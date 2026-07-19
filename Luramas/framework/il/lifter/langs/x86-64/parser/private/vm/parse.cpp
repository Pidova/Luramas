#ifdef LURAMAS_TARGET_X86

#include "../vm.hpp"

namespace vm {

      bool parse(const registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            switch (registrar.inst) {
                  case x86_insn::X86_INS_AAA: {
                        vm::AAA(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_AAD: {
                        vm::AAD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_AAM: {
                        vm::AAM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_AAS: {
                        vm::AAS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FABS: {
                        vm::FABS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ADC: {
                        vm::ADC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ADCX: {
                        vm::ADCX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ADD: {
                        vm::ADD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ADDPD: {
                        vm::ADDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ADDPS: {
                        vm::ADDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ADDSD: {
                        vm::ADDSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ADDSS: {
                        vm::ADDSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ADDSUBPD: {
                        vm::ADDSUBPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ADDSUBPS: {
                        vm::ADDSUBPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FADD: {
                        vm::FADD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FIADD: {
                        vm::FIADD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ADOX: {
                        vm::ADOX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_AESDECLAST: {
                        vm::AESDECLAST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_AESDEC: {
                        vm::AESDEC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_AESENCLAST: {
                        vm::AESENCLAST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_AESENC: {
                        vm::AESENC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_AESIMC: {
                        vm::AESIMC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_AESKEYGENASSIST: {
                        vm::AESKEYGENASSIST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_AND: {
                        vm::AND(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ANDN: {
                        vm::ANDN(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ANDNPD: {
                        vm::ANDNPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ANDNPS: {
                        vm::ANDNPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ANDPD: {
                        vm::ANDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ANDPS: {
                        vm::ANDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ARPL: {
                        vm::ARPL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BEXTR: {
                        vm::BEXTR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLCFILL: {
                        vm::BLCFILL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLCI: {
                        vm::BLCI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLCIC: {
                        vm::BLCIC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLCMSK: {
                        vm::BLCMSK(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLCS: {
                        vm::BLCS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLENDPD: {
                        vm::BLENDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLENDPS: {
                        vm::BLENDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLENDVPD: {
                        vm::BLENDVPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLENDVPS: {
                        vm::BLENDVPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLSFILL: {
                        vm::BLSFILL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLSI: {
                        vm::BLSI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLSIC: {
                        vm::BLSIC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLSMSK: {
                        vm::BLSMSK(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BLSR: {
                        vm::BLSR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BNDCL: {
                        vm::BNDCL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BNDCN: {
                        vm::BNDCN(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BNDCU: {
                        vm::BNDCU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BNDLDX: {
                        vm::BNDLDX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BNDMK: {
                        vm::BNDMK(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BNDMOV: {
                        vm::BNDMOV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BNDSTX: {
                        vm::BNDSTX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BOUND: {
                        vm::BOUND(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BSF: {
                        vm::BSF(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BSR: {
                        vm::BSR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BSWAP: {
                        vm::BSWAP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BT: {
                        vm::BT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BTC: {
                        vm::BTC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BTR: {
                        vm::BTR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BTS: {
                        vm::BTS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_BZHI: {
                        vm::BZHI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CALL: {
                        vm::CALL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CBW: {
                        vm::CBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CDQ: {
                        vm::CDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CDQE: {
                        vm::CDQE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCHS: {
                        vm::FCHS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLAC: {
                        vm::CLAC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLC: {
                        vm::CLC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLD: {
                        vm::CLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLDEMOTE: {
                        vm::CLDEMOTE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLFLUSH: {
                        vm::CLFLUSH(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLFLUSHOPT: {
                        vm::CLFLUSHOPT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLGI: {
                        vm::CLGI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLI: {
                        vm::CLI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLRSSBSY: {
                        vm::CLRSSBSY(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLTS: {
                        vm::CLTS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLWB: {
                        vm::CLWB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CLZERO: {
                        vm::CLZERO(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMC: {
                        vm::CMC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVA: {
                        vm::CMOVA(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVAE: {
                        vm::CMOVAE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVB: {
                        vm::CMOVB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVBE: {
                        vm::CMOVBE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCMOVBE: {
                        vm::FCMOVBE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCMOVB: {
                        vm::FCMOVB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVE: {
                        vm::CMOVE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCMOVE: {
                        vm::FCMOVE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVG: {
                        vm::CMOVG(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVGE: {
                        vm::CMOVGE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVL: {
                        vm::CMOVL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVLE: {
                        vm::CMOVLE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCMOVNBE: {
                        vm::FCMOVNBE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCMOVNB: {
                        vm::FCMOVNB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVNE: {
                        vm::CMOVNE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCMOVNE: {
                        vm::FCMOVNE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVNO: {
                        vm::CMOVNO(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVNP: {
                        vm::CMOVNP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCMOVNU: {
                        vm::FCMOVNU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCMOVNP: {
                        vm::FCMOVNP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVNS: {
                        vm::CMOVNS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVO: {
                        vm::CMOVO(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVP: {
                        vm::CMOVP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCMOVU: {
                        vm::FCMOVU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMOVS: {
                        vm::CMOVS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMP: {
                        vm::CMP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMPPD: {
                        vm::CMPPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMPPS: {
                        vm::CMPPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMPSB: {
                        vm::CMPSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMPSD: {
                        vm::CMPSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMPSQ: {
                        vm::CMPSQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMPSS: {
                        vm::CMPSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMPSW: {
                        vm::CMPSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMPXCHG16B: {
                        vm::CMPXCHG16B(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMPXCHG: {
                        vm::CMPXCHG(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CMPXCHG8B: {
                        vm::CMPXCHG8B(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_COMISD: {
                        vm::COMISD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_COMISS: {
                        vm::COMISS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCOMP: {
                        vm::FCOMP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCOMPI: {
                        vm::FCOMPI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCOMI: {
                        vm::FCOMI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCOM: {
                        vm::FCOM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCOS: {
                        vm::FCOS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CPUID: {
                        vm::CPUID(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CQO: {
                        vm::CQO(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CRC32: {
                        vm::CRC32(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTDQ2PD: {
                        vm::CVTDQ2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTDQ2PS: {
                        vm::CVTDQ2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTPD2DQ: {
                        vm::CVTPD2DQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTPD2PS: {
                        vm::CVTPD2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTPS2DQ: {
                        vm::CVTPS2DQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTPS2PD: {
                        vm::CVTPS2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTSD2SI: {
                        vm::CVTSD2SI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTSD2SS: {
                        vm::CVTSD2SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTSI2SD: {
                        vm::CVTSI2SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTSI2SS: {
                        vm::CVTSI2SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTSS2SD: {
                        vm::CVTSS2SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTSS2SI: {
                        vm::CVTSS2SI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTTPD2DQ: {
                        vm::CVTTPD2DQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTTPS2DQ: {
                        vm::CVTTPS2DQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTTSD2SI: {
                        vm::CVTTSD2SI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTTSS2SI: {
                        vm::CVTTSS2SI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CWD: {
                        vm::CWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CWDE: {
                        vm::CWDE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_DAA: {
                        vm::DAA(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_DAS: {
                        vm::DAS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_DATA16: {
                        vm::DATA16(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_DEC: {
                        vm::DEC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_DIV: {
                        vm::DIV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_DIVPD: {
                        vm::DIVPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_DIVPS: {
                        vm::DIVPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FDIVR: {
                        vm::FDIVR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FIDIVR: {
                        vm::FIDIVR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FDIVRP: {
                        vm::FDIVRP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_DIVSD: {
                        vm::DIVSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_DIVSS: {
                        vm::DIVSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FDIV: {
                        vm::FDIV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FIDIV: {
                        vm::FIDIV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FDIVP: {
                        vm::FDIVP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_DPPD: {
                        vm::DPPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_DPPS: {
                        vm::DPPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ENCLS: {
                        vm::ENCLS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ENCLU: {
                        vm::ENCLU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ENCLV: {
                        vm::ENCLV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ENDBR32: {
                        vm::ENDBR32(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ENDBR64: {
                        vm::ENDBR64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ENTER: {
                        vm::ENTER(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_EXTRACTPS: {
                        vm::EXTRACTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_EXTRQ: {
                        vm::EXTRQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_F2XM1: {
                        vm::F2XM1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LCALL: {
                        vm::LCALL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LJMP: {
                        vm::LJMP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JMP: {
                        vm::JMP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FBLD: {
                        vm::FBLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FBSTP: {
                        vm::FBSTP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FCOMPP: {
                        vm::FCOMPP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FDECSTP: {
                        vm::FDECSTP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FDISI8087_NOP: {
                        vm::FDISI8087_NOP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FEMMS: {
                        vm::FEMMS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FENI8087_NOP: {
                        vm::FENI8087_NOP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FFREE: {
                        vm::FFREE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FFREEP: {
                        vm::FFREEP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FICOM: {
                        vm::FICOM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FICOMP: {
                        vm::FICOMP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FINCSTP: {
                        vm::FINCSTP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FLDCW: {
                        vm::FLDCW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FLDENV: {
                        vm::FLDENV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FLDL2E: {
                        vm::FLDL2E(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FLDL2T: {
                        vm::FLDL2T(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FLDLG2: {
                        vm::FLDLG2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FLDLN2: {
                        vm::FLDLN2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FLDPI: {
                        vm::FLDPI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FNCLEX: {
                        vm::FNCLEX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FNINIT: {
                        vm::FNINIT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FNOP: {
                        vm::FNOP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FNSTCW: {
                        vm::FNSTCW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FNSTSW: {
                        vm::FNSTSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FPATAN: {
                        vm::FPATAN(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FSTPNCE: {
                        vm::FSTPNCE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FPREM: {
                        vm::FPREM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FPREM1: {
                        vm::FPREM1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FPTAN: {
                        vm::FPTAN(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FRNDINT: {
                        vm::FRNDINT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FRSTOR: {
                        vm::FRSTOR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FNSAVE: {
                        vm::FNSAVE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FSCALE: {
                        vm::FSCALE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FSETPM: {
                        vm::FSETPM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FSINCOS: {
                        vm::FSINCOS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FNSTENV: {
                        vm::FNSTENV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FXAM: {
                        vm::FXAM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FXRSTOR: {
                        vm::FXRSTOR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FXRSTOR64: {
                        vm::FXRSTOR64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FXSAVE: {
                        vm::FXSAVE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FXSAVE64: {
                        vm::FXSAVE64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FXTRACT: {
                        vm::FXTRACT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FYL2X: {
                        vm::FYL2X(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FYL2XP1: {
                        vm::FYL2XP1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_GETSEC: {
                        vm::GETSEC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_GF2P8AFFINEINVQB: {
                        vm::GF2P8AFFINEINVQB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_GF2P8AFFINEQB: {
                        vm::GF2P8AFFINEQB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_GF2P8MULB: {
                        vm::GF2P8MULB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_HADDPD: {
                        vm::HADDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_HADDPS: {
                        vm::HADDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_HLT: {
                        vm::HLT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_HSUBPD: {
                        vm::HSUBPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_HSUBPS: {
                        vm::HSUBPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_IDIV: {
                        vm::IDIV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FILD: {
                        vm::FILD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_IMUL: {
                        vm::IMUL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_IN: {
                        vm::IN(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INC: {
                        vm::INC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INCSSPD: {
                        vm::INCSSPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INCSSPQ: {
                        vm::INCSSPQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INSB: {
                        vm::INSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INSERTPS: {
                        vm::INSERTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INSERTQ: {
                        vm::INSERTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INSD: {
                        vm::INSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INSW: {
                        vm::INSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INT: {
                        vm::INT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INT1: {
                        vm::INT1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INT3: {
                        vm::INT3(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INTO: {
                        vm::INTO(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INVD: {
                        vm::INVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INVEPT: {
                        vm::INVEPT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INVLPG: {
                        vm::INVLPG(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INVLPGA: {
                        vm::INVLPGA(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INVPCID: {
                        vm::INVPCID(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_INVVPID: {
                        vm::INVVPID(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_IRET: {
                        vm::IRET(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_IRETD: {
                        vm::IRETD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_IRETQ: {
                        vm::IRETQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FISTTP: {
                        vm::FISTTP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FIST: {
                        vm::FIST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FISTP: {
                        vm::FISTP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JAE: {
                        vm::JAE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JA: {
                        vm::JA(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JBE: {
                        vm::JBE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JB: {
                        vm::JB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JCXZ: {
                        vm::JCXZ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JECXZ: {
                        vm::JECXZ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JE: {
                        vm::JE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JGE: {
                        vm::JGE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JG: {
                        vm::JG(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JLE: {
                        vm::JLE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JL: {
                        vm::JL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JNE: {
                        vm::JNE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JNO: {
                        vm::JNO(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JNP: {
                        vm::JNP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JNS: {
                        vm::JNS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JO: {
                        vm::JO(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JP: {
                        vm::JP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JRCXZ: {
                        vm::JRCXZ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_JS: {
                        vm::JS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KADDB: {
                        vm::KADDB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KADDD: {
                        vm::KADDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KADDQ: {
                        vm::KADDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KADDW: {
                        vm::KADDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KANDB: {
                        vm::KANDB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KANDD: {
                        vm::KANDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KANDNB: {
                        vm::KANDNB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KANDND: {
                        vm::KANDND(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KANDNQ: {
                        vm::KANDNQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KANDNW: {
                        vm::KANDNW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KANDQ: {
                        vm::KANDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KANDW: {
                        vm::KANDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KMOVB: {
                        vm::KMOVB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KMOVD: {
                        vm::KMOVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KMOVQ: {
                        vm::KMOVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KMOVW: {
                        vm::KMOVW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KNOTB: {
                        vm::KNOTB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KNOTD: {
                        vm::KNOTD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KNOTQ: {
                        vm::KNOTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KNOTW: {
                        vm::KNOTW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KORB: {
                        vm::KORB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KORD: {
                        vm::KORD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KORQ: {
                        vm::KORQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KORTESTB: {
                        vm::KORTESTB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KORTESTD: {
                        vm::KORTESTD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KORTESTQ: {
                        vm::KORTESTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KORTESTW: {
                        vm::KORTESTW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KORW: {
                        vm::KORW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KSHIFTLB: {
                        vm::KSHIFTLB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KSHIFTLD: {
                        vm::KSHIFTLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KSHIFTLQ: {
                        vm::KSHIFTLQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KSHIFTLW: {
                        vm::KSHIFTLW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KSHIFTRB: {
                        vm::KSHIFTRB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KSHIFTRD: {
                        vm::KSHIFTRD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KSHIFTRQ: {
                        vm::KSHIFTRQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KSHIFTRW: {
                        vm::KSHIFTRW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KTESTB: {
                        vm::KTESTB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KTESTD: {
                        vm::KTESTD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KTESTQ: {
                        vm::KTESTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KTESTW: {
                        vm::KTESTW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KUNPCKBW: {
                        vm::KUNPCKBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KUNPCKDQ: {
                        vm::KUNPCKDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KUNPCKWD: {
                        vm::KUNPCKWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KXNORB: {
                        vm::KXNORB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KXNORD: {
                        vm::KXNORD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KXNORQ: {
                        vm::KXNORQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KXNORW: {
                        vm::KXNORW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KXORB: {
                        vm::KXORB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KXORD: {
                        vm::KXORD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KXORQ: {
                        vm::KXORQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_KXORW: {
                        vm::KXORW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LAHF: {
                        vm::LAHF(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LAR: {
                        vm::LAR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LDDQU: {
                        vm::LDDQU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LDMXCSR: {
                        vm::LDMXCSR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LDS: {
                        vm::LDS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FLDZ: {
                        vm::FLDZ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FLD1: {
                        vm::FLD1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FLD: {
                        vm::FLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LEA: {
                        vm::LEA(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LEAVE: {
                        vm::LEAVE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LES: {
                        vm::LES(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LFENCE: {
                        vm::LFENCE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LFS: {
                        vm::LFS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LGDT: {
                        vm::LGDT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LGS: {
                        vm::LGS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LIDT: {
                        vm::LIDT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LLDT: {
                        vm::LLDT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LLWPCB: {
                        vm::LLWPCB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LMSW: {
                        vm::LMSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LOCK: {
                        vm::LOCK(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LODSB: {
                        vm::LODSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LODSD: {
                        vm::LODSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LODSQ: {
                        vm::LODSQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LODSW: {
                        vm::LODSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LOOP: {
                        vm::LOOP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LOOPE: {
                        vm::LOOPE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LOOPNE: {
                        vm::LOOPNE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RETF: {
                        vm::RETF(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RETFQ: {
                        vm::RETFQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LSL: {
                        vm::LSL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LSS: {
                        vm::LSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LTR: {
                        vm::LTR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LWPINS: {
                        vm::LWPINS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LWPVAL: {
                        vm::LWPVAL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_LZCNT: {
                        vm::LZCNT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MASKMOVDQU: {
                        vm::MASKMOVDQU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MAXPD: {
                        vm::MAXPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MAXPS: {
                        vm::MAXPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MAXSD: {
                        vm::MAXSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MAXSS: {
                        vm::MAXSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MFENCE: {
                        vm::MFENCE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MINPD: {
                        vm::MINPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MINPS: {
                        vm::MINPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MINSD: {
                        vm::MINSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MINSS: {
                        vm::MINSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTPD2PI: {
                        vm::CVTPD2PI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTPI2PD: {
                        vm::CVTPI2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTPI2PS: {
                        vm::CVTPI2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTPS2PI: {
                        vm::CVTPS2PI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTTPD2PI: {
                        vm::CVTTPD2PI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_CVTTPS2PI: {
                        vm::CVTTPS2PI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_EMMS: {
                        vm::EMMS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MASKMOVQ: {
                        vm::MASKMOVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVD: {
                        vm::MOVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVQ: {
                        vm::MOVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVDQ2Q: {
                        vm::MOVDQ2Q(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVNTQ: {
                        vm::MOVNTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVQ2DQ: {
                        vm::MOVQ2DQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PABSB: {
                        vm::PABSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PABSD: {
                        vm::PABSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PABSW: {
                        vm::PABSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PACKSSDW: {
                        vm::PACKSSDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PACKSSWB: {
                        vm::PACKSSWB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PACKUSWB: {
                        vm::PACKUSWB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PADDB: {
                        vm::PADDB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PADDD: {
                        vm::PADDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PADDQ: {
                        vm::PADDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PADDSB: {
                        vm::PADDSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PADDSW: {
                        vm::PADDSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PADDUSB: {
                        vm::PADDUSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PADDUSW: {
                        vm::PADDUSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PADDW: {
                        vm::PADDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PALIGNR: {
                        vm::PALIGNR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PANDN: {
                        vm::PANDN(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PAND: {
                        vm::PAND(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PAVGB: {
                        vm::PAVGB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PAVGW: {
                        vm::PAVGW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPEQB: {
                        vm::PCMPEQB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPEQD: {
                        vm::PCMPEQD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPEQW: {
                        vm::PCMPEQW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPGTB: {
                        vm::PCMPGTB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPGTD: {
                        vm::PCMPGTD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPGTW: {
                        vm::PCMPGTW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PEXTRW: {
                        vm::PEXTRW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PHADDD: {
                        vm::PHADDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PHADDSW: {
                        vm::PHADDSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PHADDW: {
                        vm::PHADDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PHSUBD: {
                        vm::PHSUBD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PHSUBSW: {
                        vm::PHSUBSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PHSUBW: {
                        vm::PHSUBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PINSRW: {
                        vm::PINSRW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMADDUBSW: {
                        vm::PMADDUBSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMADDWD: {
                        vm::PMADDWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMAXSW: {
                        vm::PMAXSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMAXUB: {
                        vm::PMAXUB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMINSW: {
                        vm::PMINSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMINUB: {
                        vm::PMINUB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVMSKB: {
                        vm::PMOVMSKB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMULHRSW: {
                        vm::PMULHRSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMULHUW: {
                        vm::PMULHUW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMULHW: {
                        vm::PMULHW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMULLW: {
                        vm::PMULLW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMULUDQ: {
                        vm::PMULUDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_POR: {
                        vm::POR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSADBW: {
                        vm::PSADBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSHUFB: {
                        vm::PSHUFB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSHUFW: {
                        vm::PSHUFW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSIGNB: {
                        vm::PSIGNB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSIGND: {
                        vm::PSIGND(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSIGNW: {
                        vm::PSIGNW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSLLD: {
                        vm::PSLLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSLLQ: {
                        vm::PSLLQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSLLW: {
                        vm::PSLLW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSRAD: {
                        vm::PSRAD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSRAW: {
                        vm::PSRAW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSRLD: {
                        vm::PSRLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSRLQ: {
                        vm::PSRLQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSRLW: {
                        vm::PSRLW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSUBB: {
                        vm::PSUBB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSUBD: {
                        vm::PSUBD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSUBQ: {
                        vm::PSUBQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSUBSB: {
                        vm::PSUBSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSUBSW: {
                        vm::PSUBSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSUBUSB: {
                        vm::PSUBUSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSUBUSW: {
                        vm::PSUBUSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSUBW: {
                        vm::PSUBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUNPCKHBW: {
                        vm::PUNPCKHBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUNPCKHDQ: {
                        vm::PUNPCKHDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUNPCKHWD: {
                        vm::PUNPCKHWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUNPCKLBW: {
                        vm::PUNPCKLBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUNPCKLDQ: {
                        vm::PUNPCKLDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUNPCKLWD: {
                        vm::PUNPCKLWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PXOR: {
                        vm::PXOR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MONITORX: {
                        vm::MONITORX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MONITOR: {
                        vm::MONITOR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MONTMUL: {
                        vm::MONTMUL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOV: {
                        vm::MOV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVABS: {
                        vm::MOVABS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVAPD: {
                        vm::MOVAPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVAPS: {
                        vm::MOVAPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVBE: {
                        vm::MOVBE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVDDUP: {
                        vm::MOVDDUP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVDIR64B: {
                        vm::MOVDIR64B(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVDIRI: {
                        vm::MOVDIRI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVDQA: {
                        vm::MOVDQA(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVDQU: {
                        vm::MOVDQU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVHLPS: {
                        vm::MOVHLPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVHPD: {
                        vm::MOVHPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVHPS: {
                        vm::MOVHPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVLHPS: {
                        vm::MOVLHPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVLPD: {
                        vm::MOVLPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVLPS: {
                        vm::MOVLPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVMSKPD: {
                        vm::MOVMSKPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVMSKPS: {
                        vm::MOVMSKPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVNTDQA: {
                        vm::MOVNTDQA(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVNTDQ: {
                        vm::MOVNTDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVNTI: {
                        vm::MOVNTI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVNTPD: {
                        vm::MOVNTPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVNTPS: {
                        vm::MOVNTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVNTSD: {
                        vm::MOVNTSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVNTSS: {
                        vm::MOVNTSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVSB: {
                        vm::MOVSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVSD: {
                        vm::MOVSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVSHDUP: {
                        vm::MOVSHDUP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVSLDUP: {
                        vm::MOVSLDUP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVSQ: {
                        vm::MOVSQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVSS: {
                        vm::MOVSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVSW: {
                        vm::MOVSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVSX: {
                        vm::MOVSX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVSXD: {
                        vm::MOVSXD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVUPD: {
                        vm::MOVUPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVUPS: {
                        vm::MOVUPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MOVZX: {
                        vm::MOVZX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MPSADBW: {
                        vm::MPSADBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MUL: {
                        vm::MUL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MULPD: {
                        vm::MULPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MULPS: {
                        vm::MULPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MULSD: {
                        vm::MULSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MULSS: {
                        vm::MULSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MULX: {
                        vm::MULX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FMUL: {
                        vm::FMUL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FIMUL: {
                        vm::FIMUL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FMULP: {
                        vm::FMULP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MWAITX: {
                        vm::MWAITX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_MWAIT: {
                        vm::MWAIT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_NEG: {
                        vm::NEG(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_NOP: {
                        vm::NOP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_NOT: {
                        vm::NOT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_OR: {
                        vm::OR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ORPD: {
                        vm::ORPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ORPS: {
                        vm::ORPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_OUT: {
                        vm::OUT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_OUTSB: {
                        vm::OUTSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_OUTSD: {
                        vm::OUTSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_OUTSW: {
                        vm::OUTSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PACKUSDW: {
                        vm::PACKUSDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PAUSE: {
                        vm::PAUSE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PAVGUSB: {
                        vm::PAVGUSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PBLENDVB: {
                        vm::PBLENDVB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PBLENDW: {
                        vm::PBLENDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCLMULQDQ: {
                        vm::PCLMULQDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPEQQ: {
                        vm::PCMPEQQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPESTRI: {
                        vm::PCMPESTRI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPESTRM: {
                        vm::PCMPESTRM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPGTQ: {
                        vm::PCMPGTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPISTRI: {
                        vm::PCMPISTRI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCMPISTRM: {
                        vm::PCMPISTRM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PCONFIG: {
                        vm::PCONFIG(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PDEP: {
                        vm::PDEP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PEXT: {
                        vm::PEXT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PEXTRB: {
                        vm::PEXTRB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PEXTRD: {
                        vm::PEXTRD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PEXTRQ: {
                        vm::PEXTRQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PF2ID: {
                        vm::PF2ID(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PF2IW: {
                        vm::PF2IW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFACC: {
                        vm::PFACC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFADD: {
                        vm::PFADD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFCMPEQ: {
                        vm::PFCMPEQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFCMPGE: {
                        vm::PFCMPGE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFCMPGT: {
                        vm::PFCMPGT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFMAX: {
                        vm::PFMAX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFMIN: {
                        vm::PFMIN(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFMUL: {
                        vm::PFMUL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFNACC: {
                        vm::PFNACC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFPNACC: {
                        vm::PFPNACC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFRCPIT1: {
                        vm::PFRCPIT1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFRCPIT2: {
                        vm::PFRCPIT2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFRCP: {
                        vm::PFRCP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFRSQIT1: {
                        vm::PFRSQIT1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFRSQRT: {
                        vm::PFRSQRT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFSUBR: {
                        vm::PFSUBR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PFSUB: {
                        vm::PFSUB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PHMINPOSUW: {
                        vm::PHMINPOSUW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PI2FD: {
                        vm::PI2FD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PI2FW: {
                        vm::PI2FW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PINSRB: {
                        vm::PINSRB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PINSRD: {
                        vm::PINSRD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PINSRQ: {
                        vm::PINSRQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMAXSB: {
                        vm::PMAXSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMAXSD: {
                        vm::PMAXSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMAXUD: {
                        vm::PMAXUD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMAXUW: {
                        vm::PMAXUW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMINSB: {
                        vm::PMINSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMINSD: {
                        vm::PMINSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMINUD: {
                        vm::PMINUD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMINUW: {
                        vm::PMINUW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVSXBD: {
                        vm::PMOVSXBD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVSXBQ: {
                        vm::PMOVSXBQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVSXBW: {
                        vm::PMOVSXBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVSXDQ: {
                        vm::PMOVSXDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVSXWD: {
                        vm::PMOVSXWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVSXWQ: {
                        vm::PMOVSXWQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVZXBD: {
                        vm::PMOVZXBD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVZXBQ: {
                        vm::PMOVZXBQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVZXBW: {
                        vm::PMOVZXBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVZXDQ: {
                        vm::PMOVZXDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVZXWD: {
                        vm::PMOVZXWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMOVZXWQ: {
                        vm::PMOVZXWQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMULDQ: {
                        vm::PMULDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMULHRW: {
                        vm::PMULHRW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PMULLD: {
                        vm::PMULLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_POP: {
                        vm::POP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_POPAW: {
                        vm::POPAW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_POPAL: {
                        vm::POPAL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_POPCNT: {
                        vm::POPCNT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_POPF: {
                        vm::POPF(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_POPFD: {
                        vm::POPFD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_POPFQ: {
                        vm::POPFQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PREFETCH: {
                        vm::PREFETCH(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PREFETCHT0: {
                        vm::PREFETCHT0(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PREFETCHT1: {
                        vm::PREFETCHT1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PREFETCHT2: {
                        vm::PREFETCHT2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PREFETCHWT1: {
                        vm::PREFETCHWT1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSHUFD: {
                        vm::PSHUFD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSHUFHW: {
                        vm::PSHUFHW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSHUFLW: {
                        vm::PSHUFLW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSLLDQ: {
                        vm::PSLLDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSRLDQ: {
                        vm::PSRLDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PSWAPD: {
                        vm::PSWAPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PTEST: {
                        vm::PTEST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PTWRITE: {
                        vm::PTWRITE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUNPCKHQDQ: {
                        vm::PUNPCKHQDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUNPCKLQDQ: {
                        vm::PUNPCKLQDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUSH: {
                        vm::PUSH(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUSHAW: {
                        vm::PUSHAW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUSHAL: {
                        vm::PUSHAL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUSHF: {
                        vm::PUSHF(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUSHFD: {
                        vm::PUSHFD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_PUSHFQ: {
                        vm::PUSHFQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RCL: {
                        vm::RCL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RCPPS: {
                        vm::RCPPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RCPSS: {
                        vm::RCPSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RCR: {
                        vm::RCR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RDFSBASE: {
                        vm::RDFSBASE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RDGSBASE: {
                        vm::RDGSBASE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RDMSR: {
                        vm::RDMSR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RDPKRU: {
                        vm::RDPKRU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RDPMC: {
                        vm::RDPMC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RDRAND: {
                        vm::RDRAND(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RDSEED: {
                        vm::RDSEED(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RDSSPD: {
                        vm::RDSSPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RDSSPQ: {
                        vm::RDSSPQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RDTSC: {
                        vm::RDTSC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RDTSCP: {
                        vm::RDTSCP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_REPNE: {
                        vm::REPNE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_REP: {
                        vm::REP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RET: {
                        vm::RET(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_REX64: {
                        vm::REX64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ROL: {
                        vm::ROL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ROR: {
                        vm::ROR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RORX: {
                        vm::RORX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ROUNDPD: {
                        vm::ROUNDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ROUNDPS: {
                        vm::ROUNDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ROUNDSD: {
                        vm::ROUNDSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_ROUNDSS: {
                        vm::ROUNDSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RSM: {
                        vm::RSM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RSQRTPS: {
                        vm::RSQRTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RSQRTSS: {
                        vm::RSQRTSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_RSTORSSP: {
                        vm::RSTORSSP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SAHF: {
                        vm::SAHF(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SAL: {
                        vm::SAL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SALC: {
                        vm::SALC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SAR: {
                        vm::SAR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SARX: {
                        vm::SARX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SAVEPREVSSP: {
                        vm::SAVEPREVSSP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SBB: {
                        vm::SBB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SCASB: {
                        vm::SCASB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SCASD: {
                        vm::SCASD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SCASQ: {
                        vm::SCASQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SCASW: {
                        vm::SCASW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETAE: {
                        vm::SETAE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETA: {
                        vm::SETA(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETBE: {
                        vm::SETBE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETB: {
                        vm::SETB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETE: {
                        vm::SETE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETGE: {
                        vm::SETGE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETG: {
                        vm::SETG(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETLE: {
                        vm::SETLE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETL: {
                        vm::SETL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETNE: {
                        vm::SETNE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETNO: {
                        vm::SETNO(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETNP: {
                        vm::SETNP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETNS: {
                        vm::SETNS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETO: {
                        vm::SETO(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETP: {
                        vm::SETP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETSSBSY: {
                        vm::SETSSBSY(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SETS: {
                        vm::SETS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SFENCE: {
                        vm::SFENCE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SGDT: {
                        vm::SGDT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHA1MSG1: {
                        vm::SHA1MSG1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHA1MSG2: {
                        vm::SHA1MSG2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHA1NEXTE: {
                        vm::SHA1NEXTE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHA1RNDS4: {
                        vm::SHA1RNDS4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHA256MSG1: {
                        vm::SHA256MSG1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHA256MSG2: {
                        vm::SHA256MSG2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHA256RNDS2: {
                        vm::SHA256RNDS2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHL: {
                        vm::SHL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHLD: {
                        vm::SHLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHLX: {
                        vm::SHLX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHR: {
                        vm::SHR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHRD: {
                        vm::SHRD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHRX: {
                        vm::SHRX(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHUFPD: {
                        vm::SHUFPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SHUFPS: {
                        vm::SHUFPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SIDT: {
                        vm::SIDT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FSIN: {
                        vm::FSIN(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SKINIT: {
                        vm::SKINIT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SLDT: {
                        vm::SLDT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SLWPCB: {
                        vm::SLWPCB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SMSW: {
                        vm::SMSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SQRTPD: {
                        vm::SQRTPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SQRTPS: {
                        vm::SQRTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SQRTSD: {
                        vm::SQRTSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SQRTSS: {
                        vm::SQRTSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FSQRT: {
                        vm::FSQRT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_STAC: {
                        vm::STAC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_STC: {
                        vm::STC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_STD: {
                        vm::STD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_STGI: {
                        vm::STGI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_STI: {
                        vm::STI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_STMXCSR: {
                        vm::STMXCSR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_STOSB: {
                        vm::STOSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_STOSD: {
                        vm::STOSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_STOSQ: {
                        vm::STOSQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_STOSW: {
                        vm::STOSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_STR: {
                        vm::STR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FST: {
                        vm::FST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FSTP: {
                        vm::FSTP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SUB: {
                        vm::SUB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SUBPD: {
                        vm::SUBPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SUBPS: {
                        vm::SUBPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FSUBR: {
                        vm::FSUBR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FISUBR: {
                        vm::FISUBR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FSUBRP: {
                        vm::FSUBRP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SUBSD: {
                        vm::SUBSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SUBSS: {
                        vm::SUBSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FSUB: {
                        vm::FSUB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FISUB: {
                        vm::FISUB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FSUBP: {
                        vm::FSUBP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SWAPGS: {
                        vm::SWAPGS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SYSCALL: {
                        vm::SYSCALL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SYSENTER: {
                        vm::SYSENTER(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SYSEXIT: {
                        vm::SYSEXIT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SYSEXITQ: {
                        vm::SYSEXITQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SYSRET: {
                        vm::SYSRET(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_SYSRETQ: {
                        vm::SYSRETQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_T1MSKC: {
                        vm::T1MSKC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_TEST: {
                        vm::TEST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_TPAUSE: {
                        vm::TPAUSE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FTST: {
                        vm::FTST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_TZCNT: {
                        vm::TZCNT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_TZMSK: {
                        vm::TZMSK(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_UCOMISD: {
                        vm::UCOMISD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_UCOMISS: {
                        vm::UCOMISS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FUCOMPI: {
                        vm::FUCOMPI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FUCOMI: {
                        vm::FUCOMI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FUCOMPP: {
                        vm::FUCOMPP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FUCOMP: {
                        vm::FUCOMP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FUCOM: {
                        vm::FUCOM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_UD0: {
                        vm::UD0(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_UD1: {
                        vm::UD1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_UD2: {
                        vm::UD2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_UMONITOR: {
                        vm::UMONITOR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_UMWAIT: {
                        vm::UMWAIT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_UNPCKHPD: {
                        vm::UNPCKHPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_UNPCKHPS: {
                        vm::UNPCKHPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_UNPCKLPD: {
                        vm::UNPCKLPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_V4FMADDPS: {
                        vm::V4FMADDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_V4FMADDSS: {
                        vm::V4FMADDSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_V4FNMADDPS: {
                        vm::V4FNMADDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_V4FNMADDSS: {
                        vm::V4FNMADDSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VADDPD: {
                        vm::VADDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VADDPS: {
                        vm::VADDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VADDSD: {
                        vm::VADDSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VADDSS: {
                        vm::VADDSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VADDSUBPD: {
                        vm::VADDSUBPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VADDSUBPS: {
                        vm::VADDSUBPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VAESDECLAST: {
                        vm::VAESDECLAST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VAESDEC: {
                        vm::VAESDEC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VAESENCLAST: {
                        vm::VAESENCLAST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VAESENC: {
                        vm::VAESENC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VAESIMC: {
                        vm::VAESIMC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VAESKEYGENASSIST: {
                        vm::VAESKEYGENASSIST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VALIGND: {
                        vm::VALIGND(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VALIGNQ: {
                        vm::VALIGNQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VANDNPD: {
                        vm::VANDNPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VANDNPS: {
                        vm::VANDNPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VANDPD: {
                        vm::VANDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VANDPS: {
                        vm::VANDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBLENDMPD: {
                        vm::VBLENDMPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBLENDMPS: {
                        vm::VBLENDMPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBLENDPD: {
                        vm::VBLENDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBLENDPS: {
                        vm::VBLENDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBLENDVPD: {
                        vm::VBLENDVPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBLENDVPS: {
                        vm::VBLENDVPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTF128: {
                        vm::VBROADCASTF128(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTF32X2: {
                        vm::VBROADCASTF32X2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTF32X4: {
                        vm::VBROADCASTF32X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTF32X8: {
                        vm::VBROADCASTF32X8(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTF64X2: {
                        vm::VBROADCASTF64X2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTF64X4: {
                        vm::VBROADCASTF64X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTI128: {
                        vm::VBROADCASTI128(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTI32X2: {
                        vm::VBROADCASTI32X2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTI32X4: {
                        vm::VBROADCASTI32X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTI32X8: {
                        vm::VBROADCASTI32X8(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTI64X2: {
                        vm::VBROADCASTI64X2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTI64X4: {
                        vm::VBROADCASTI64X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTSD: {
                        vm::VBROADCASTSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VBROADCASTSS: {
                        vm::VBROADCASTSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCMP: {
                        vm::VCMP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCMPPD: {
                        vm::VCMPPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCMPPS: {
                        vm::VCMPPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCMPSD: {
                        vm::VCMPSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCMPSS: {
                        vm::VCMPSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCOMISD: {
                        vm::VCOMISD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCOMISS: {
                        vm::VCOMISS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCOMPRESSPD: {
                        vm::VCOMPRESSPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCOMPRESSPS: {
                        vm::VCOMPRESSPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTDQ2PD: {
                        vm::VCVTDQ2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTDQ2PS: {
                        vm::VCVTDQ2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPD2DQ: {
                        vm::VCVTPD2DQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPD2PS: {
                        vm::VCVTPD2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPD2QQ: {
                        vm::VCVTPD2QQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPD2UDQ: {
                        vm::VCVTPD2UDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPD2UQQ: {
                        vm::VCVTPD2UQQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPH2PS: {
                        vm::VCVTPH2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPS2DQ: {
                        vm::VCVTPS2DQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPS2PD: {
                        vm::VCVTPS2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPS2PH: {
                        vm::VCVTPS2PH(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPS2QQ: {
                        vm::VCVTPS2QQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPS2UDQ: {
                        vm::VCVTPS2UDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTPS2UQQ: {
                        vm::VCVTPS2UQQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTQQ2PD: {
                        vm::VCVTQQ2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTQQ2PS: {
                        vm::VCVTQQ2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTSD2SI: {
                        vm::VCVTSD2SI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTSD2SS: {
                        vm::VCVTSD2SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTSD2USI: {
                        vm::VCVTSD2USI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTSI2SD: {
                        vm::VCVTSI2SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTSI2SS: {
                        vm::VCVTSI2SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTSS2SD: {
                        vm::VCVTSS2SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTSS2SI: {
                        vm::VCVTSS2SI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTSS2USI: {
                        vm::VCVTSS2USI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTPD2DQ: {
                        vm::VCVTTPD2DQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTPD2QQ: {
                        vm::VCVTTPD2QQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTPD2UDQ: {
                        vm::VCVTTPD2UDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTPD2UQQ: {
                        vm::VCVTTPD2UQQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTPS2DQ: {
                        vm::VCVTTPS2DQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTPS2QQ: {
                        vm::VCVTTPS2QQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTPS2UDQ: {
                        vm::VCVTTPS2UDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTPS2UQQ: {
                        vm::VCVTTPS2UQQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTSD2SI: {
                        vm::VCVTTSD2SI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTSD2USI: {
                        vm::VCVTTSD2USI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTSS2SI: {
                        vm::VCVTTSS2SI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTTSS2USI: {
                        vm::VCVTTSS2USI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTUDQ2PD: {
                        vm::VCVTUDQ2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTUDQ2PS: {
                        vm::VCVTUDQ2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTUQQ2PD: {
                        vm::VCVTUQQ2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTUQQ2PS: {
                        vm::VCVTUQQ2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTUSI2SD: {
                        vm::VCVTUSI2SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VCVTUSI2SS: {
                        vm::VCVTUSI2SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VDBPSADBW: {
                        vm::VDBPSADBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VDIVPD: {
                        vm::VDIVPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VDIVPS: {
                        vm::VDIVPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VDIVSD: {
                        vm::VDIVSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VDIVSS: {
                        vm::VDIVSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VDPPD: {
                        vm::VDPPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VDPPS: {
                        vm::VDPPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VERR: {
                        vm::VERR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VERW: {
                        vm::VERW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXP2PD: {
                        vm::VEXP2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXP2PS: {
                        vm::VEXP2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXPANDPD: {
                        vm::VEXPANDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXPANDPS: {
                        vm::VEXPANDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXTRACTF128: {
                        vm::VEXTRACTF128(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXTRACTF32X4: {
                        vm::VEXTRACTF32X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXTRACTF32X8: {
                        vm::VEXTRACTF32X8(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXTRACTF64X2: {
                        vm::VEXTRACTF64X2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXTRACTF64X4: {
                        vm::VEXTRACTF64X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXTRACTI128: {
                        vm::VEXTRACTI128(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXTRACTI32X4: {
                        vm::VEXTRACTI32X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXTRACTI32X8: {
                        vm::VEXTRACTI32X8(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXTRACTI64X2: {
                        vm::VEXTRACTI64X2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXTRACTI64X4: {
                        vm::VEXTRACTI64X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VEXTRACTPS: {
                        vm::VEXTRACTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFIXUPIMMPD: {
                        vm::VFIXUPIMMPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFIXUPIMMPS: {
                        vm::VFIXUPIMMPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFIXUPIMMSD: {
                        vm::VFIXUPIMMSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFIXUPIMMSS: {
                        vm::VFIXUPIMMSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD132PD: {
                        vm::VFMADD132PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD132PS: {
                        vm::VFMADD132PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD132SD: {
                        vm::VFMADD132SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD132SS: {
                        vm::VFMADD132SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD213PD: {
                        vm::VFMADD213PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD213PS: {
                        vm::VFMADD213PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD213SD: {
                        vm::VFMADD213SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD213SS: {
                        vm::VFMADD213SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD231PD: {
                        vm::VFMADD231PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD231PS: {
                        vm::VFMADD231PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD231SD: {
                        vm::VFMADD231SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADD231SS: {
                        vm::VFMADD231SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDPD: {
                        vm::VFMADDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDPS: {
                        vm::VFMADDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDSD: {
                        vm::VFMADDSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDSS: {
                        vm::VFMADDSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDSUB132PD: {
                        vm::VFMADDSUB132PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDSUB132PS: {
                        vm::VFMADDSUB132PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDSUB213PD: {
                        vm::VFMADDSUB213PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDSUB213PS: {
                        vm::VFMADDSUB213PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDSUB231PD: {
                        vm::VFMADDSUB231PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDSUB231PS: {
                        vm::VFMADDSUB231PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDSUBPD: {
                        vm::VFMADDSUBPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMADDSUBPS: {
                        vm::VFMADDSUBPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB132PD: {
                        vm::VFMSUB132PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB132PS: {
                        vm::VFMSUB132PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB132SD: {
                        vm::VFMSUB132SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB132SS: {
                        vm::VFMSUB132SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB213PD: {
                        vm::VFMSUB213PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB213PS: {
                        vm::VFMSUB213PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB213SD: {
                        vm::VFMSUB213SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB213SS: {
                        vm::VFMSUB213SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB231PD: {
                        vm::VFMSUB231PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB231PS: {
                        vm::VFMSUB231PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB231SD: {
                        vm::VFMSUB231SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUB231SS: {
                        vm::VFMSUB231SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBADD132PD: {
                        vm::VFMSUBADD132PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBADD132PS: {
                        vm::VFMSUBADD132PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBADD213PD: {
                        vm::VFMSUBADD213PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBADD213PS: {
                        vm::VFMSUBADD213PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBADD231PD: {
                        vm::VFMSUBADD231PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBADD231PS: {
                        vm::VFMSUBADD231PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBADDPD: {
                        vm::VFMSUBADDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBADDPS: {
                        vm::VFMSUBADDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBPD: {
                        vm::VFMSUBPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBPS: {
                        vm::VFMSUBPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBSD: {
                        vm::VFMSUBSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFMSUBSS: {
                        vm::VFMSUBSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD132PD: {
                        vm::VFNMADD132PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD132PS: {
                        vm::VFNMADD132PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD132SD: {
                        vm::VFNMADD132SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD132SS: {
                        vm::VFNMADD132SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD213PD: {
                        vm::VFNMADD213PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD213PS: {
                        vm::VFNMADD213PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD213SD: {
                        vm::VFNMADD213SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD213SS: {
                        vm::VFNMADD213SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD231PD: {
                        vm::VFNMADD231PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD231PS: {
                        vm::VFNMADD231PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD231SD: {
                        vm::VFNMADD231SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADD231SS: {
                        vm::VFNMADD231SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADDPD: {
                        vm::VFNMADDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADDPS: {
                        vm::VFNMADDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADDSD: {
                        vm::VFNMADDSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMADDSS: {
                        vm::VFNMADDSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB132PD: {
                        vm::VFNMSUB132PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB132PS: {
                        vm::VFNMSUB132PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB132SD: {
                        vm::VFNMSUB132SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB132SS: {
                        vm::VFNMSUB132SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB213PD: {
                        vm::VFNMSUB213PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB213PS: {
                        vm::VFNMSUB213PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB213SD: {
                        vm::VFNMSUB213SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB213SS: {
                        vm::VFNMSUB213SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB231PD: {
                        vm::VFNMSUB231PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB231PS: {
                        vm::VFNMSUB231PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB231SD: {
                        vm::VFNMSUB231SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUB231SS: {
                        vm::VFNMSUB231SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUBPD: {
                        vm::VFNMSUBPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUBPS: {
                        vm::VFNMSUBPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUBSD: {
                        vm::VFNMSUBSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFNMSUBSS: {
                        vm::VFNMSUBSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFPCLASSPD: {
                        vm::VFPCLASSPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFPCLASSPS: {
                        vm::VFPCLASSPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFPCLASSSD: {
                        vm::VFPCLASSSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFPCLASSSS: {
                        vm::VFPCLASSSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFRCZPD: {
                        vm::VFRCZPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFRCZPS: {
                        vm::VFRCZPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFRCZSD: {
                        vm::VFRCZSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VFRCZSS: {
                        vm::VFRCZSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERDPD: {
                        vm::VGATHERDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERDPS: {
                        vm::VGATHERDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERPF0DPD: {
                        vm::VGATHERPF0DPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERPF0DPS: {
                        vm::VGATHERPF0DPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERPF0QPD: {
                        vm::VGATHERPF0QPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERPF0QPS: {
                        vm::VGATHERPF0QPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERPF1DPD: {
                        vm::VGATHERPF1DPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERPF1DPS: {
                        vm::VGATHERPF1DPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERPF1QPD: {
                        vm::VGATHERPF1QPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERPF1QPS: {
                        vm::VGATHERPF1QPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERQPD: {
                        vm::VGATHERQPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGATHERQPS: {
                        vm::VGATHERQPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGETEXPPD: {
                        vm::VGETEXPPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGETEXPPS: {
                        vm::VGETEXPPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGETEXPSD: {
                        vm::VGETEXPSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGETEXPSS: {
                        vm::VGETEXPSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGETMANTPD: {
                        vm::VGETMANTPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGETMANTPS: {
                        vm::VGETMANTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGETMANTSD: {
                        vm::VGETMANTSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGETMANTSS: {
                        vm::VGETMANTSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGF2P8AFFINEINVQB: {
                        vm::VGF2P8AFFINEINVQB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGF2P8AFFINEQB: {
                        vm::VGF2P8AFFINEQB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VGF2P8MULB: {
                        vm::VGF2P8MULB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VHADDPD: {
                        vm::VHADDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VHADDPS: {
                        vm::VHADDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VHSUBPD: {
                        vm::VHSUBPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VHSUBPS: {
                        vm::VHSUBPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VINSERTF128: {
                        vm::VINSERTF128(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VINSERTF32X4: {
                        vm::VINSERTF32X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VINSERTF32X8: {
                        vm::VINSERTF32X8(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VINSERTF64X2: {
                        vm::VINSERTF64X2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VINSERTF64X4: {
                        vm::VINSERTF64X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VINSERTI128: {
                        vm::VINSERTI128(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VINSERTI32X4: {
                        vm::VINSERTI32X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VINSERTI32X8: {
                        vm::VINSERTI32X8(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VINSERTI64X2: {
                        vm::VINSERTI64X2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VINSERTI64X4: {
                        vm::VINSERTI64X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VINSERTPS: {
                        vm::VINSERTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VLDDQU: {
                        vm::VLDDQU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VLDMXCSR: {
                        vm::VLDMXCSR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMASKMOVDQU: {
                        vm::VMASKMOVDQU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMASKMOVPD: {
                        vm::VMASKMOVPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMASKMOVPS: {
                        vm::VMASKMOVPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMAXPD: {
                        vm::VMAXPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMAXPS: {
                        vm::VMAXPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMAXSD: {
                        vm::VMAXSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMAXSS: {
                        vm::VMAXSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMCALL: {
                        vm::VMCALL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMCLEAR: {
                        vm::VMCLEAR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMFUNC: {
                        vm::VMFUNC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMINPD: {
                        vm::VMINPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMINPS: {
                        vm::VMINPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMINSD: {
                        vm::VMINSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMINSS: {
                        vm::VMINSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMLAUNCH: {
                        vm::VMLAUNCH(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMLOAD: {
                        vm::VMLOAD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMMCALL: {
                        vm::VMMCALL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVQ: {
                        vm::VMOVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVAPD: {
                        vm::VMOVAPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVAPS: {
                        vm::VMOVAPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVDDUP: {
                        vm::VMOVDDUP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVD: {
                        vm::VMOVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVDQA32: {
                        vm::VMOVDQA32(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVDQA64: {
                        vm::VMOVDQA64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVDQA: {
                        vm::VMOVDQA(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVDQU16: {
                        vm::VMOVDQU16(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVDQU32: {
                        vm::VMOVDQU32(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVDQU64: {
                        vm::VMOVDQU64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVDQU8: {
                        vm::VMOVDQU8(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVDQU: {
                        vm::VMOVDQU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVHLPS: {
                        vm::VMOVHLPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVHPD: {
                        vm::VMOVHPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVHPS: {
                        vm::VMOVHPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVLHPS: {
                        vm::VMOVLHPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVLPD: {
                        vm::VMOVLPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVLPS: {
                        vm::VMOVLPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVMSKPD: {
                        vm::VMOVMSKPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVMSKPS: {
                        vm::VMOVMSKPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVNTDQA: {
                        vm::VMOVNTDQA(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVNTDQ: {
                        vm::VMOVNTDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVNTPD: {
                        vm::VMOVNTPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVNTPS: {
                        vm::VMOVNTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVSD: {
                        vm::VMOVSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVSHDUP: {
                        vm::VMOVSHDUP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVSLDUP: {
                        vm::VMOVSLDUP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVSS: {
                        vm::VMOVSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVUPD: {
                        vm::VMOVUPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMOVUPS: {
                        vm::VMOVUPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMPSADBW: {
                        vm::VMPSADBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMPTRLD: {
                        vm::VMPTRLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMPTRST: {
                        vm::VMPTRST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMREAD: {
                        vm::VMREAD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMRESUME: {
                        vm::VMRESUME(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMRUN: {
                        vm::VMRUN(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMSAVE: {
                        vm::VMSAVE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMULPD: {
                        vm::VMULPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMULPS: {
                        vm::VMULPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMULSD: {
                        vm::VMULSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMULSS: {
                        vm::VMULSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMWRITE: {
                        vm::VMWRITE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMXOFF: {
                        vm::VMXOFF(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VMXON: {
                        vm::VMXON(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VORPD: {
                        vm::VORPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VORPS: {
                        vm::VORPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VP4DPWSSDS: {
                        vm::VP4DPWSSDS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VP4DPWSSD: {
                        vm::VP4DPWSSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPABSB: {
                        vm::VPABSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPABSD: {
                        vm::VPABSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPABSQ: {
                        vm::VPABSQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPABSW: {
                        vm::VPABSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPACKSSDW: {
                        vm::VPACKSSDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPACKSSWB: {
                        vm::VPACKSSWB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPACKUSDW: {
                        vm::VPACKUSDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPACKUSWB: {
                        vm::VPACKUSWB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPADDB: {
                        vm::VPADDB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPADDD: {
                        vm::VPADDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPADDQ: {
                        vm::VPADDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPADDSB: {
                        vm::VPADDSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPADDSW: {
                        vm::VPADDSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPADDUSB: {
                        vm::VPADDUSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPADDUSW: {
                        vm::VPADDUSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPADDW: {
                        vm::VPADDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPALIGNR: {
                        vm::VPALIGNR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPANDD: {
                        vm::VPANDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPANDND: {
                        vm::VPANDND(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPANDNQ: {
                        vm::VPANDNQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPANDN: {
                        vm::VPANDN(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPANDQ: {
                        vm::VPANDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPAND: {
                        vm::VPAND(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPAVGB: {
                        vm::VPAVGB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPAVGW: {
                        vm::VPAVGW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBLENDD: {
                        vm::VPBLENDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBLENDMB: {
                        vm::VPBLENDMB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBLENDMD: {
                        vm::VPBLENDMD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBLENDMQ: {
                        vm::VPBLENDMQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBLENDMW: {
                        vm::VPBLENDMW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBLENDVB: {
                        vm::VPBLENDVB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBLENDW: {
                        vm::VPBLENDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBROADCASTB: {
                        vm::VPBROADCASTB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBROADCASTD: {
                        vm::VPBROADCASTD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBROADCASTMB2Q: {
                        vm::VPBROADCASTMB2Q(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBROADCASTMW2D: {
                        vm::VPBROADCASTMW2D(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBROADCASTQ: {
                        vm::VPBROADCASTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPBROADCASTW: {
                        vm::VPBROADCASTW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCLMULQDQ: {
                        vm::VPCLMULQDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMOV: {
                        vm::VPCMOV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMP: {
                        vm::VPCMP(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPB: {
                        vm::VPCMPB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPD: {
                        vm::VPCMPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPEQB: {
                        vm::VPCMPEQB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPEQD: {
                        vm::VPCMPEQD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPEQQ: {
                        vm::VPCMPEQQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPEQW: {
                        vm::VPCMPEQW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPESTRI: {
                        vm::VPCMPESTRI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPESTRM: {
                        vm::VPCMPESTRM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPGTB: {
                        vm::VPCMPGTB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPGTD: {
                        vm::VPCMPGTD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPGTQ: {
                        vm::VPCMPGTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPGTW: {
                        vm::VPCMPGTW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPISTRI: {
                        vm::VPCMPISTRI(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPISTRM: {
                        vm::VPCMPISTRM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPQ: {
                        vm::VPCMPQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPUB: {
                        vm::VPCMPUB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPUD: {
                        vm::VPCMPUD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPUQ: {
                        vm::VPCMPUQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPUW: {
                        vm::VPCMPUW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCMPW: {
                        vm::VPCMPW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOM: {
                        vm::VPCOM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMB: {
                        vm::VPCOMB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMD: {
                        vm::VPCOMD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMPRESSB: {
                        vm::VPCOMPRESSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMPRESSD: {
                        vm::VPCOMPRESSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMPRESSQ: {
                        vm::VPCOMPRESSQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMPRESSW: {
                        vm::VPCOMPRESSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMQ: {
                        vm::VPCOMQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMUB: {
                        vm::VPCOMUB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMUD: {
                        vm::VPCOMUD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMUQ: {
                        vm::VPCOMUQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMUW: {
                        vm::VPCOMUW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCOMW: {
                        vm::VPCOMW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCONFLICTD: {
                        vm::VPCONFLICTD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPCONFLICTQ: {
                        vm::VPCONFLICTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPDPBUSDS: {
                        vm::VPDPBUSDS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPDPBUSD: {
                        vm::VPDPBUSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPDPWSSDS: {
                        vm::VPDPWSSDS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPDPWSSD: {
                        vm::VPDPWSSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERM2F128: {
                        vm::VPERM2F128(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERM2I128: {
                        vm::VPERM2I128(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMB: {
                        vm::VPERMB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMD: {
                        vm::VPERMD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMI2B: {
                        vm::VPERMI2B(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMI2D: {
                        vm::VPERMI2D(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMI2PD: {
                        vm::VPERMI2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMI2PS: {
                        vm::VPERMI2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMI2Q: {
                        vm::VPERMI2Q(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMI2W: {
                        vm::VPERMI2W(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMIL2PD: {
                        vm::VPERMIL2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMILPD: {
                        vm::VPERMILPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMIL2PS: {
                        vm::VPERMIL2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMILPS: {
                        vm::VPERMILPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMPD: {
                        vm::VPERMPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMPS: {
                        vm::VPERMPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMQ: {
                        vm::VPERMQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMT2B: {
                        vm::VPERMT2B(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMT2D: {
                        vm::VPERMT2D(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMT2PD: {
                        vm::VPERMT2PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMT2PS: {
                        vm::VPERMT2PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMT2Q: {
                        vm::VPERMT2Q(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMT2W: {
                        vm::VPERMT2W(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPERMW: {
                        vm::VPERMW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPEXPANDB: {
                        vm::VPEXPANDB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPEXPANDD: {
                        vm::VPEXPANDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPEXPANDQ: {
                        vm::VPEXPANDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPEXPANDW: {
                        vm::VPEXPANDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPEXTRB: {
                        vm::VPEXTRB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPEXTRD: {
                        vm::VPEXTRD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPEXTRQ: {
                        vm::VPEXTRQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPEXTRW: {
                        vm::VPEXTRW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPGATHERDD: {
                        vm::VPGATHERDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPGATHERDQ: {
                        vm::VPGATHERDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPGATHERQD: {
                        vm::VPGATHERQD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPGATHERQQ: {
                        vm::VPGATHERQQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDBD: {
                        vm::VPHADDBD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDBQ: {
                        vm::VPHADDBQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDBW: {
                        vm::VPHADDBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDDQ: {
                        vm::VPHADDDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDD: {
                        vm::VPHADDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDSW: {
                        vm::VPHADDSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDUBD: {
                        vm::VPHADDUBD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDUBQ: {
                        vm::VPHADDUBQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDUBW: {
                        vm::VPHADDUBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDUDQ: {
                        vm::VPHADDUDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDUWD: {
                        vm::VPHADDUWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDUWQ: {
                        vm::VPHADDUWQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDWD: {
                        vm::VPHADDWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDWQ: {
                        vm::VPHADDWQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHADDW: {
                        vm::VPHADDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHMINPOSUW: {
                        vm::VPHMINPOSUW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHSUBBW: {
                        vm::VPHSUBBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHSUBDQ: {
                        vm::VPHSUBDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHSUBD: {
                        vm::VPHSUBD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHSUBSW: {
                        vm::VPHSUBSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHSUBWD: {
                        vm::VPHSUBWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPHSUBW: {
                        vm::VPHSUBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPINSRB: {
                        vm::VPINSRB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPINSRD: {
                        vm::VPINSRD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPINSRQ: {
                        vm::VPINSRQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPINSRW: {
                        vm::VPINSRW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPLZCNTD: {
                        vm::VPLZCNTD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPLZCNTQ: {
                        vm::VPLZCNTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMACSDD: {
                        vm::VPMACSDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMACSDQH: {
                        vm::VPMACSDQH(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMACSDQL: {
                        vm::VPMACSDQL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMACSSDD: {
                        vm::VPMACSSDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMACSSDQH: {
                        vm::VPMACSSDQH(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMACSSDQL: {
                        vm::VPMACSSDQL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMACSSWD: {
                        vm::VPMACSSWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMACSSWW: {
                        vm::VPMACSSWW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMACSWD: {
                        vm::VPMACSWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMACSWW: {
                        vm::VPMACSWW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMADCSSWD: {
                        vm::VPMADCSSWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMADCSWD: {
                        vm::VPMADCSWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMADD52HUQ: {
                        vm::VPMADD52HUQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMADD52LUQ: {
                        vm::VPMADD52LUQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMADDUBSW: {
                        vm::VPMADDUBSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMADDWD: {
                        vm::VPMADDWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMASKMOVD: {
                        vm::VPMASKMOVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMASKMOVQ: {
                        vm::VPMASKMOVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMAXSB: {
                        vm::VPMAXSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMAXSD: {
                        vm::VPMAXSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMAXSQ: {
                        vm::VPMAXSQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMAXSW: {
                        vm::VPMAXSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMAXUB: {
                        vm::VPMAXUB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMAXUD: {
                        vm::VPMAXUD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMAXUQ: {
                        vm::VPMAXUQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMAXUW: {
                        vm::VPMAXUW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMINSB: {
                        vm::VPMINSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMINSD: {
                        vm::VPMINSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMINSQ: {
                        vm::VPMINSQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMINSW: {
                        vm::VPMINSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMINUB: {
                        vm::VPMINUB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMINUD: {
                        vm::VPMINUD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMINUQ: {
                        vm::VPMINUQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMINUW: {
                        vm::VPMINUW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVB2M: {
                        vm::VPMOVB2M(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVD2M: {
                        vm::VPMOVD2M(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVDB: {
                        vm::VPMOVDB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVDW: {
                        vm::VPMOVDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVM2B: {
                        vm::VPMOVM2B(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVM2D: {
                        vm::VPMOVM2D(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVM2Q: {
                        vm::VPMOVM2Q(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVM2W: {
                        vm::VPMOVM2W(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVMSKB: {
                        vm::VPMOVMSKB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVQ2M: {
                        vm::VPMOVQ2M(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVQB: {
                        vm::VPMOVQB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVQD: {
                        vm::VPMOVQD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVQW: {
                        vm::VPMOVQW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSDB: {
                        vm::VPMOVSDB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSDW: {
                        vm::VPMOVSDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSQB: {
                        vm::VPMOVSQB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSQD: {
                        vm::VPMOVSQD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSQW: {
                        vm::VPMOVSQW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSWB: {
                        vm::VPMOVSWB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSXBD: {
                        vm::VPMOVSXBD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSXBQ: {
                        vm::VPMOVSXBQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSXBW: {
                        vm::VPMOVSXBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSXDQ: {
                        vm::VPMOVSXDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSXWD: {
                        vm::VPMOVSXWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVSXWQ: {
                        vm::VPMOVSXWQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVUSDB: {
                        vm::VPMOVUSDB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVUSDW: {
                        vm::VPMOVUSDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVUSQB: {
                        vm::VPMOVUSQB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVUSQD: {
                        vm::VPMOVUSQD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVUSQW: {
                        vm::VPMOVUSQW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVUSWB: {
                        vm::VPMOVUSWB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVW2M: {
                        vm::VPMOVW2M(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVWB: {
                        vm::VPMOVWB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVZXBD: {
                        vm::VPMOVZXBD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVZXBQ: {
                        vm::VPMOVZXBQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVZXBW: {
                        vm::VPMOVZXBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVZXDQ: {
                        vm::VPMOVZXDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVZXWD: {
                        vm::VPMOVZXWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMOVZXWQ: {
                        vm::VPMOVZXWQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMULDQ: {
                        vm::VPMULDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMULHRSW: {
                        vm::VPMULHRSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMULHUW: {
                        vm::VPMULHUW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMULHW: {
                        vm::VPMULHW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMULLD: {
                        vm::VPMULLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMULLQ: {
                        vm::VPMULLQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMULLW: {
                        vm::VPMULLW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMULTISHIFTQB: {
                        vm::VPMULTISHIFTQB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPMULUDQ: {
                        vm::VPMULUDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPOPCNTB: {
                        vm::VPOPCNTB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPOPCNTD: {
                        vm::VPOPCNTD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPOPCNTQ: {
                        vm::VPOPCNTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPOPCNTW: {
                        vm::VPOPCNTW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPORD: {
                        vm::VPORD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPORQ: {
                        vm::VPORQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPOR: {
                        vm::VPOR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPPERM: {
                        vm::VPPERM(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPROLD: {
                        vm::VPROLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPROLQ: {
                        vm::VPROLQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPROLVD: {
                        vm::VPROLVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPROLVQ: {
                        vm::VPROLVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPRORD: {
                        vm::VPRORD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPRORQ: {
                        vm::VPRORQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPRORVD: {
                        vm::VPRORVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPRORVQ: {
                        vm::VPRORVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPROTB: {
                        vm::VPROTB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPROTD: {
                        vm::VPROTD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPROTQ: {
                        vm::VPROTQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPROTW: {
                        vm::VPROTW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSADBW: {
                        vm::VPSADBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSCATTERDD: {
                        vm::VPSCATTERDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSCATTERDQ: {
                        vm::VPSCATTERDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSCATTERQD: {
                        vm::VPSCATTERQD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSCATTERQQ: {
                        vm::VPSCATTERQQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHAB: {
                        vm::VPSHAB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHAD: {
                        vm::VPSHAD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHAQ: {
                        vm::VPSHAQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHAW: {
                        vm::VPSHAW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHLB: {
                        vm::VPSHLB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHLDD: {
                        vm::VPSHLDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHLDQ: {
                        vm::VPSHLDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHLDVD: {
                        vm::VPSHLDVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHLDVQ: {
                        vm::VPSHLDVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHLDVW: {
                        vm::VPSHLDVW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHLDW: {
                        vm::VPSHLDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHLD: {
                        vm::VPSHLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHLQ: {
                        vm::VPSHLQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHLW: {
                        vm::VPSHLW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHRDD: {
                        vm::VPSHRDD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHRDQ: {
                        vm::VPSHRDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHRDVD: {
                        vm::VPSHRDVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHRDVQ: {
                        vm::VPSHRDVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHRDVW: {
                        vm::VPSHRDVW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHRDW: {
                        vm::VPSHRDW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHUFBITQMB: {
                        vm::VPSHUFBITQMB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHUFB: {
                        vm::VPSHUFB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHUFD: {
                        vm::VPSHUFD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHUFHW: {
                        vm::VPSHUFHW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSHUFLW: {
                        vm::VPSHUFLW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSIGNB: {
                        vm::VPSIGNB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSIGND: {
                        vm::VPSIGND(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSIGNW: {
                        vm::VPSIGNW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSLLDQ: {
                        vm::VPSLLDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSLLD: {
                        vm::VPSLLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSLLQ: {
                        vm::VPSLLQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSLLVD: {
                        vm::VPSLLVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSLLVQ: {
                        vm::VPSLLVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSLLVW: {
                        vm::VPSLLVW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSLLW: {
                        vm::VPSLLW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRAD: {
                        vm::VPSRAD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRAQ: {
                        vm::VPSRAQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRAVD: {
                        vm::VPSRAVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRAVQ: {
                        vm::VPSRAVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRAVW: {
                        vm::VPSRAVW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRAW: {
                        vm::VPSRAW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRLDQ: {
                        vm::VPSRLDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRLD: {
                        vm::VPSRLD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRLQ: {
                        vm::VPSRLQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRLVD: {
                        vm::VPSRLVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRLVQ: {
                        vm::VPSRLVQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRLVW: {
                        vm::VPSRLVW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSRLW: {
                        vm::VPSRLW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSUBB: {
                        vm::VPSUBB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSUBD: {
                        vm::VPSUBD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSUBQ: {
                        vm::VPSUBQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSUBSB: {
                        vm::VPSUBSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSUBSW: {
                        vm::VPSUBSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSUBUSB: {
                        vm::VPSUBUSB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSUBUSW: {
                        vm::VPSUBUSW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPSUBW: {
                        vm::VPSUBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPTERNLOGD: {
                        vm::VPTERNLOGD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPTERNLOGQ: {
                        vm::VPTERNLOGQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPTESTMB: {
                        vm::VPTESTMB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPTESTMD: {
                        vm::VPTESTMD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPTESTMQ: {
                        vm::VPTESTMQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPTESTMW: {
                        vm::VPTESTMW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPTESTNMB: {
                        vm::VPTESTNMB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPTESTNMD: {
                        vm::VPTESTNMD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPTESTNMQ: {
                        vm::VPTESTNMQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPTESTNMW: {
                        vm::VPTESTNMW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPTEST: {
                        vm::VPTEST(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPUNPCKHBW: {
                        vm::VPUNPCKHBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPUNPCKHDQ: {
                        vm::VPUNPCKHDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPUNPCKHQDQ: {
                        vm::VPUNPCKHQDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPUNPCKHWD: {
                        vm::VPUNPCKHWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPUNPCKLBW: {
                        vm::VPUNPCKLBW(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPUNPCKLDQ: {
                        vm::VPUNPCKLDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPUNPCKLQDQ: {
                        vm::VPUNPCKLQDQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPUNPCKLWD: {
                        vm::VPUNPCKLWD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPXORD: {
                        vm::VPXORD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPXORQ: {
                        vm::VPXORQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VPXOR: {
                        vm::VPXOR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRANGEPD: {
                        vm::VRANGEPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRANGEPS: {
                        vm::VRANGEPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRANGESD: {
                        vm::VRANGESD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRANGESS: {
                        vm::VRANGESS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRCP14PD: {
                        vm::VRCP14PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRCP14PS: {
                        vm::VRCP14PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRCP14SD: {
                        vm::VRCP14SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRCP14SS: {
                        vm::VRCP14SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRCP28PD: {
                        vm::VRCP28PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRCP28PS: {
                        vm::VRCP28PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRCP28SD: {
                        vm::VRCP28SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRCP28SS: {
                        vm::VRCP28SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRCPPS: {
                        vm::VRCPPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRCPSS: {
                        vm::VRCPSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VREDUCEPD: {
                        vm::VREDUCEPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VREDUCEPS: {
                        vm::VREDUCEPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VREDUCESD: {
                        vm::VREDUCESD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VREDUCESS: {
                        vm::VREDUCESS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRNDSCALEPD: {
                        vm::VRNDSCALEPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRNDSCALEPS: {
                        vm::VRNDSCALEPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRNDSCALESD: {
                        vm::VRNDSCALESD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRNDSCALESS: {
                        vm::VRNDSCALESS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VROUNDPD: {
                        vm::VROUNDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VROUNDPS: {
                        vm::VROUNDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VROUNDSD: {
                        vm::VROUNDSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VROUNDSS: {
                        vm::VROUNDSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRSQRT14PD: {
                        vm::VRSQRT14PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRSQRT14PS: {
                        vm::VRSQRT14PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRSQRT14SD: {
                        vm::VRSQRT14SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRSQRT14SS: {
                        vm::VRSQRT14SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRSQRT28PD: {
                        vm::VRSQRT28PD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRSQRT28PS: {
                        vm::VRSQRT28PS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRSQRT28SD: {
                        vm::VRSQRT28SD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRSQRT28SS: {
                        vm::VRSQRT28SS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRSQRTPS: {
                        vm::VRSQRTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VRSQRTSS: {
                        vm::VRSQRTSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCALEFPD: {
                        vm::VSCALEFPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCALEFPS: {
                        vm::VSCALEFPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCALEFSD: {
                        vm::VSCALEFSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCALEFSS: {
                        vm::VSCALEFSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERDPD: {
                        vm::VSCATTERDPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERDPS: {
                        vm::VSCATTERDPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERPF0DPD: {
                        vm::VSCATTERPF0DPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERPF0DPS: {
                        vm::VSCATTERPF0DPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERPF0QPD: {
                        vm::VSCATTERPF0QPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERPF0QPS: {
                        vm::VSCATTERPF0QPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERPF1DPD: {
                        vm::VSCATTERPF1DPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERPF1DPS: {
                        vm::VSCATTERPF1DPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERPF1QPD: {
                        vm::VSCATTERPF1QPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERPF1QPS: {
                        vm::VSCATTERPF1QPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERQPD: {
                        vm::VSCATTERQPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSCATTERQPS: {
                        vm::VSCATTERQPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSHUFF32X4: {
                        vm::VSHUFF32X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSHUFF64X2: {
                        vm::VSHUFF64X2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSHUFI32X4: {
                        vm::VSHUFI32X4(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSHUFI64X2: {
                        vm::VSHUFI64X2(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSHUFPD: {
                        vm::VSHUFPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSHUFPS: {
                        vm::VSHUFPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSQRTPD: {
                        vm::VSQRTPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSQRTPS: {
                        vm::VSQRTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSQRTSD: {
                        vm::VSQRTSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSQRTSS: {
                        vm::VSQRTSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSTMXCSR: {
                        vm::VSTMXCSR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSUBPD: {
                        vm::VSUBPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSUBPS: {
                        vm::VSUBPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSUBSD: {
                        vm::VSUBSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VSUBSS: {
                        vm::VSUBSS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VTESTPD: {
                        vm::VTESTPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VTESTPS: {
                        vm::VTESTPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VUCOMISD: {
                        vm::VUCOMISD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VUCOMISS: {
                        vm::VUCOMISS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VUNPCKHPD: {
                        vm::VUNPCKHPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VUNPCKHPS: {
                        vm::VUNPCKHPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VUNPCKLPD: {
                        vm::VUNPCKLPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VUNPCKLPS: {
                        vm::VUNPCKLPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VXORPD: {
                        vm::VXORPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VXORPS: {
                        vm::VXORPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VZEROALL: {
                        vm::VZEROALL(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_VZEROUPPER: {
                        vm::VZEROUPPER(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_WAIT: {
                        vm::WAIT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_WBINVD: {
                        vm::WBINVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_WBNOINVD: {
                        vm::WBNOINVD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_WRFSBASE: {
                        vm::WRFSBASE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_WRGSBASE: {
                        vm::WRGSBASE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_WRMSR: {
                        vm::WRMSR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_WRPKRU: {
                        vm::WRPKRU(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_WRSSD: {
                        vm::WRSSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_WRSSQ: {
                        vm::WRSSQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_WRUSSD: {
                        vm::WRUSSD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_WRUSSQ: {
                        vm::WRUSSQ(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XABORT: {
                        vm::XABORT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XACQUIRE: {
                        vm::XACQUIRE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XADD: {
                        vm::XADD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XBEGIN: {
                        vm::XBEGIN(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XCHG: {
                        vm::XCHG(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_FXCH: {
                        vm::FXCH(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XCRYPTCBC: {
                        vm::XCRYPTCBC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XCRYPTCFB: {
                        vm::XCRYPTCFB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XCRYPTCTR: {
                        vm::XCRYPTCTR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XCRYPTECB: {
                        vm::XCRYPTECB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XCRYPTOFB: {
                        vm::XCRYPTOFB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XEND: {
                        vm::XEND(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XGETBV: {
                        vm::XGETBV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XLATB: {
                        vm::XLATB(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XOR: {
                        vm::XOR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XORPD: {
                        vm::XORPD(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XORPS: {
                        vm::XORPS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XRELEASE: {
                        vm::XRELEASE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XRSTOR: {
                        vm::XRSTOR(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XRSTOR64: {
                        vm::XRSTOR64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XRSTORS: {
                        vm::XRSTORS(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XRSTORS64: {
                        vm::XRSTORS64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSAVE: {
                        vm::XSAVE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSAVE64: {
                        vm::XSAVE64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSAVEC: {
                        vm::XSAVEC(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSAVEC64: {
                        vm::XSAVEC64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSAVEOPT: {
                        vm::XSAVEOPT(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSAVEOPT64: {
                        vm::XSAVEOPT64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSAVES: {
                        vm::XSAVES(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSAVES64: {
                        vm::XSAVES64(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSETBV: {
                        vm::XSETBV(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSHA1: {
                        vm::XSHA1(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSHA256: {
                        vm::XSHA256(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XSTORE: {
                        vm::XSTORE(registrar, operands);
                        break;
                  }
                  case x86_insn::X86_INS_XTEST: {
                        vm::XTEST(registrar, operands);
                        break;
                  }
                  default: {
                        return false;
                  }
            }
            return true;
      }
} // namespace vm
#endif