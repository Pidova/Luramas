#pragma once
#ifdef LURAMAS_TARGET_X86

#include "../../../../../../il/il/architecture/emitter.hpp"
#include "../../../../builder/builder.hpp"
#include "../../common.hpp"
#include "../parser.hpp"
#include "flags.hpp"
#include "kinds.hpp"
#include "vmdef.hpp"
#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <unordered_map>
#include <vector>

namespace tools {

      struct canonicalize_to_reg_results {
            bool mem = false;
            luramas_register reg = 0u;
            luramas_int_base integral = 0;
      };
      struct flags {
            bool effective = false;
            bool unsign = false;
      };

      /* Computes operands to target register if possible or single register if it is (Does not emit write) */
      inline canonicalize_to_reg_results canonicalize_to_reg(const std::shared_ptr<luramas::il::lifter::builder::build> &build, const luramas::profile::inst &inst, const cs_x86_op &op, const flags f = flags()) {

            canonicalize_to_reg_results result;
            switch (op.type) {
                  case x86_op_type::X86_OP_IMM: {
                        const auto t = build->make_temp();
                        build->make_load(t, op.imm);
                        result.reg = t.r.r;
                        result.integral = op.imm;
                        break;
                  }
                  case x86_op_type::X86_OP_REG: {
                        result.reg = highest_reg(op.reg);
                        break;
                  }
                  case x86_op_type::X86_OP_MEM: {

                        bool assigned = false;
                        bool has_sib = false;
                        auto tsib = build->make_temp();
                        if (op.mem.index != x86_reg::X86_REG_INVALID) {

                              /* 
                                   TEMP = CAST(INDEX)
                                   TEMP = TEMP * SCALE
                              */
                              tsib = build->make_reg(highest_reg(op.mem.index));
                              tsib.cast(reg_bits(op.mem.index));
                              tsib *= op.mem.scale;
                              has_sib = true;
                              assigned = true;
                        }

                        auto tres = build->make_temp();
                        if (op.mem.base != x86_reg::X86_REG_INVALID) {

                              switch (op.mem.base) {
                                    case x86_reg::X86_REG_IP:
                                    case x86_reg::X86_REG_RIP:
                                    case x86_reg::X86_REG_EIP: {
                                          tres = build->make_temp();
                                          tres = inst.pc + inst.len();
                                          break;
                                    }
                                    default: {
                                          tres = build->make_reg(highest_reg(op.mem.base));
                                          break;
                                    }
                              }

                              /*  TEMP(+has_sib) = CAST(BASE) */
                              tres.cast(reg_bits(op.mem.base));

                              if (has_sib) {
                                    /*  TEMP = TEMP(+has_sib) + SIB(TEMP) */
                                    tres += tsib;
                              }
                              assigned = true;
                        }

                        if (assigned) {
                              tres += op.mem.disp;
                        } else {
                              tres = op.mem.disp;
                        }
                        result.mem = !f.effective;
                        result.reg = tres.r.r;
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return result;
      }

      inline luramas_register highest(const x86_reg r) {
            return highest_reg(r);
      }
      inline luramas::il::lifter::builder::build::expr make(const std::shared_ptr<luramas::il::lifter::builder::build> &b, const x86_reg r) {
            luramas::il::lifter::builder::build::expr result(b, luramas::il::lifter::builder::reg(highest(r), reg_bits(r)));
            return result;
      }
      inline luramas::il::lifter::builder::build::expr make(const std::shared_ptr<luramas::il::lifter::builder::build> &b, const xeflags f) {
            luramas::il::lifter::builder::build::expr result;
            result.emit_flag(b, static_cast<std::intptr_t>(f));
            return result;
      }

      namespace common {

            inline std::vector<luramas::il::lifter::builder::build::expr> canonicalize_insert(const luramas::profile::inst &inst, const std::shared_ptr<luramas::il::lifter::builder::build> &build, const cs_x86 &dis, const flags f = flags()) {

                  std::vector<luramas::il::lifter::builder::build::expr> result;
                  for (auto i = 0u; i < dis.op_count; ++i) {

                        luramas::il::lifter::builder::build::expr expr;
                        const auto res = tools::canonicalize_to_reg(build, inst, dis.operands[i], f);
                        const auto reg = luramas::il::lifter::builder::reg(res.reg, dis.operands[i].size * 8u, f.unsign);
                        if (res.mem) {
                              expr.emit_mem(build, reg);
                        } else {
                              expr.emit(build, reg);
                              if (res.integral) {
                                    build->constant[res.reg] = luramas_register_contents(inst.lid, res.integral);
                              }
                        }
                        result.emplace_back(expr);
                  }
                  return result;
            }
      } // namespace common

      namespace generate {

            inline void explicit_cast(std::shared_ptr<luramas::il::disassembly> &buffer, const std::shared_ptr<luramas::il::ilang> &il, const x86_reg reg, const luramas_address loc, const bool unsign = false) {

                  luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_BITCAST>(il, loc, buffer, highest(reg), highest(reg), reg_bits(reg), 0u, unsign);
                  return;
            }
            inline std::shared_ptr<luramas::il::disassembly> explicit_cast(const std::shared_ptr<luramas::il::ilang> &il, const x86_reg reg, const luramas_address loc, const bool unsign = false) {

                  auto result = std::make_shared<luramas::il::disassembly>();
                  explicit_cast(result, il, reg, loc, unsign);
                  return result;
            }
            inline std::shared_ptr<luramas::il::disassembly> cast(const std::shared_ptr<luramas::il::ilang> &il, const luramas_register reg, const luramas_bitwidth bits, const luramas_address loc, const bool unsign = false) {

                  auto result = std::make_shared<luramas::il::disassembly>();
                  luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_BITCAST>(il, loc, result, reg, reg, bits, 0u, unsign);
                  return result;
            }
      } // namespace generate

      namespace eflags {

            struct flag_data {

                  x86_insn inst = x86_insn::X86_INS_NOP;

                  luramas::il::lifter::builder::build::expr l;      /*  L-Value */
                  luramas::il::lifter::builder::build::expr result; /* Resulting Value */
                  luramas::il::lifter::builder::build::expr r;      /* R-Value */

                  void emit_result(const luramas::il::lifter::builder::build::expr &expr) {
                        this->result = expr;
                        return;
                  }
            };

            template <xeflags... F>
            inline void mutate(const vm::registrar &registrar, const flag_data &d) {

                  constexpr auto combined = (static_cast<std::uint32_t>(F) | ...);

                  [[maybe_unused]] const auto cf = registrar.getf<xeflags::CF>();
                  [[maybe_unused]] const auto af = registrar.getf<xeflags::AF>();
                  [[maybe_unused]] const auto sf = registrar.getf<xeflags::SF>();
                  [[maybe_unused]] const auto zf = registrar.getf<xeflags::ZF>();
                  [[maybe_unused]] const auto pf = registrar.getf<xeflags::PF>();
                  [[maybe_unused]] const auto of = registrar.getf<xeflags::OF>();
                  [[maybe_unused]] const auto tf = registrar.getf<xeflags::TF>();
                  [[maybe_unused]] const auto fif = registrar.getf<xeflags::IF>();
                  [[maybe_unused]] const auto df = registrar.getf<xeflags::DF>();
                  [[maybe_unused]] const auto nt = registrar.getf<xeflags::NT>();
                  [[maybe_unused]] const auto rf = registrar.getf<xeflags::RF>();
                  [[maybe_unused]] const auto c0 = registrar.getf<xeflags::C0>();
                  [[maybe_unused]] const auto c1 = registrar.getf<xeflags::C1>();
                  [[maybe_unused]] const auto c2 = registrar.getf<xeflags::C2>();
                  [[maybe_unused]] const auto c3 = registrar.getf<xeflags::C3>();

                  auto l = d.l;
                  auto r = d.r;
                  auto res = !d.result.empty() ? d.result : l;

                  /* AF */
                  if constexpr (combined & static_cast<std::uint32_t>(xeflags::AF)) {

                        static constexpr auto mask = 15u;

                        /* AF = (((l & mask) + (r(0 if no r) & mask)) > mask) | ((result & mask) < (l & mask)); */
                        af = (((l & mask) + ((!r.empty() ? r : luramas::il::lifter::builder::build::expr(registrar.build, 0u)) & mask)) > mask) | ((res & mask) < (l & mask));
                  }

                  /* CF */
                  if constexpr (combined & static_cast<std::uint32_t>(xeflags::CF)) {
                        switch (d.inst) {

                              case x86_insn::X86_INS_ADC: {

                                    cf = (res < l) || (res < r);
                                    break;
                              }
                              case x86_insn::X86_INS_ADD: {

                                    cf = res < l;
                                    break;
                              }
                              case x86_insn::X86_INS_CMC: {

                                    cf = res > (luramas::il::lifter::builder::build::expr(registrar.build, 1u) << std::max(std::max(l.bits(), r.bits()), res.bits())) - 1;
                                    break;
                              }
                              case x86_insn::X86_INS_CMP: {

                                    cf = l.cast(true) < r.cast(true);
                                    break;
                              }
                              case x86_insn::X86_INS_CMPSB:
                              case x86_insn::X86_INS_CMPSW:
                              case x86_insn::X86_INS_CMPSD:
                              case x86_insn::X86_INS_CMPSQ: {
                                    break;
                              }
                              case x86_insn::X86_INS_CMPXCHG: {
                                    break;
                              }
                              case x86_insn::X86_INS_COMISD: {
                                    break;
                              }
                              case x86_insn::X86_INS_COMISS: {
                                    break;
                              }
                              case x86_insn::X86_INS_FCOMI: {
                                    break;
                              }
                              case x86_insn::X86_INS_FCOMPI: {
                                    break;
                              }
                              case x86_insn::X86_INS_FUCOMI: {
                                    break;
                              }
                              case x86_insn::X86_INS_FUCOMPI: {
                                    break;
                              }
                              case x86_insn::X86_INS_UCOMISD: {
                                    break;
                              }
                              case x86_insn::X86_INS_UCOMISS: {
                                    break;
                              }
                              case x86_insn::X86_INS_MUL: {

                                    cf = (res >> res.bits()) != 0;
                                    break;
                              }
                              case x86_insn::X86_INS_RSM: {
                                    break;
                              }
                              case x86_insn::X86_INS_SAL: {
                                    break;
                              }
                              case x86_insn::X86_INS_SAR: {
                                    break;
                              }
                              case x86_insn::X86_INS_SHL: {
                                    break;
                              }
                              case x86_insn::X86_INS_SHR: {
                                    break;
                              }
                              case x86_insn::X86_INS_SBB: {
                                    break;
                              }
                              case x86_insn::X86_INS_SCASB:
                              case x86_insn::X86_INS_SCASW:
                              case x86_insn::X86_INS_SCASD:
                              case x86_insn::X86_INS_SCASQ: {
                                    break;
                              }
                              case x86_insn::X86_INS_SHLD: {
                                    break;
                              }
                              case x86_insn::X86_INS_SHRD: {
                                    break;
                              }
                              case x86_insn::X86_INS_SUB: {

                                    cf = (l < r);
                                    break;
                              }
                              case x86_insn::X86_INS_XADD: {

                                    cf = (res < l);
                                    break;
                              }

                              case x86_insn::X86_INS_AND:
                              case x86_insn::X86_INS_BSF:
                              case x86_insn::X86_INS_BSR:
                              case x86_insn::X86_INS_CLC:
                              case x86_insn::X86_INS_OR:
                              case x86_insn::X86_INS_TEST:
                              case x86_insn::X86_INS_XOR: {

                                    cf = false;
                                    break;
                              }
                              case x86_insn::X86_INS_STC: {

                                    cf = true;
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  }

                  /* SF */
                  if constexpr (combined & static_cast<std::uint32_t>(xeflags::SF)) {

                        sf = LURAMAS_FBUILD_SIGNBIT(res);
                  }

                  /* ZF */
                  if constexpr (combined & static_cast<std::uint32_t>(xeflags::ZF)) {
                        zf = res == 0u;
                  }

                  /* PF */
                  if constexpr (combined & static_cast<std::uint32_t>(xeflags::PF)) {

                        auto result = registrar.build->make_temp(res);
                        switch (res.bits()) {
                              case 64u: {
                                    result ^= (result >> 32u);
                                    [[fallthrough]];
                              }
                              case 32u: {
                                    result ^= (result >> 16u);
                                    [[fallthrough]];
                              }
                              case 16u: {
                                    result ^= (result >> 8u);
                                    [[fallthrough]];
                              }
                              case 8u: {

                                    result ^= (result >> 4u);
                                    result ^= (result >> 2u);
                                    result ^= (result >> 1u);

                                    pf = (~(result & 1u)) & 1u;
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  }

                  /* OF */
                  if constexpr (combined & static_cast<std::uint32_t>(xeflags::OF)) {
                        switch (d.inst) {
                              case x86_insn::X86_INS_ADC: {
                                    break;
                              }
                              case x86_insn::X86_INS_ADD: {

                                    of = ((l > 0 && r > 0 && res < 0) || (l < 0 && r < 0 && res >= 0));
                                    break;
                              }
                              case x86_insn::X86_INS_CMP: {

                                    of = (((l ^ r) & (l ^ res)) & LURAMAS_FBUILD_SIGNMASK(res)) != 0;
                                    break;
                              }
                              case x86_insn::X86_INS_CMPSB:
                              case x86_insn::X86_INS_CMPSW:
                              case x86_insn::X86_INS_CMPSD:
                              case x86_insn::X86_INS_CMPSQ: {
                                    break;
                              }
                              case x86_insn::X86_INS_CMPXCHG: {
                                    break;
                              }
                              case x86_insn::X86_INS_DEC: {

                                    of = (l < 0 && res > 0);
                                    break;
                              }
                              case x86_insn::X86_INS_IMUL: {
                                    break;
                              }
                              case x86_insn::X86_INS_INC: {

                                    of = (l > 0 && res < 0);
                                    break;
                              }
                              case x86_insn::X86_INS_MUL: {
                                    break;
                              }
                              case x86_insn::X86_INS_NEG: {
                                    break;
                              }
                              case x86_insn::X86_INS_RCL: {
                                    break;
                              }
                              case x86_insn::X86_INS_RCR: {
                                    break;
                              }
                              case x86_insn::X86_INS_ROL: {
                                    break;
                              }
                              case x86_insn::X86_INS_ROR: {
                                    break;
                              }
                              case x86_insn::X86_INS_RSM: {
                                    break;
                              }
                              case x86_insn::X86_INS_SAL: {
                                    break;
                              }
                              case x86_insn::X86_INS_SAR: {
                                    break;
                              }
                              case x86_insn::X86_INS_SHL: {
                                    break;
                              }
                              case x86_insn::X86_INS_SHR: {
                                    break;
                              }
                              case x86_insn::X86_INS_SBB: {

                                    of = (((l ^ r) & (l ^ res)) & LURAMAS_FBUILD_SIGNMASK(res)) != 0;
                                    break;
                              }
                              case x86_insn::X86_INS_SCASB:
                              case x86_insn::X86_INS_SCASW:
                              case x86_insn::X86_INS_SCASD:
                              case x86_insn::X86_INS_SCASQ: {
                                    break;
                              }
                              case x86_insn::X86_INS_SUB: {
                                    break;
                              }
                              case x86_insn::X86_INS_XADD: {
                                    break;
                              }

                              case x86_insn::X86_INS_AND:
                              case x86_insn::X86_INS_BSF:
                              case x86_insn::X86_INS_BSR:
                              case x86_insn::X86_INS_COMISD:
                              case x86_insn::X86_INS_COMISS:
                              case x86_insn::X86_INS_FCOMI:
                              case x86_insn::X86_INS_FCOMPI:
                              case x86_insn::X86_INS_FUCOMI:
                              case x86_insn::X86_INS_FUCOMPI:
                              case x86_insn::X86_INS_UCOMISD:
                              case x86_insn::X86_INS_UCOMISS:
                              case x86_insn::X86_INS_OR:
                              case x86_insn::X86_INS_TEST:
                              case x86_insn::X86_INS_XOR: {
                                    of = false;
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  }
                  return;
            }
      } // namespace eflags
} // namespace tools

#endif