#include "../tools.hpp"

namespace tools {

      /* Computes operands to target register if possible or single register if it is (Does not emit write) */
      canonicalize_to_reg_results canonicalize_to_reg(const std::shared_ptr<luramas::il::lifter::builder::build> &build, const luramas::profile::inst &inst, const cs_x86_op &op, const flags &f) {

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

      luramas_register highest(const x86_reg r) {
            return highest_reg(r);
      }
      luramas::il::lifter::builder::build::expr make(const std::shared_ptr<luramas::il::lifter::builder::build> &b, const x86_reg r) {
            luramas::il::lifter::builder::build::expr result(b, luramas::il::lifter::builder::reg(highest(r), reg_bits(r)));
            return result;
      }
      luramas::il::lifter::builder::build::expr make(const std::shared_ptr<luramas::il::lifter::builder::build> &b, const xeflags f) {
            luramas::il::lifter::builder::build::expr result;
            result.emit_flag(b, static_cast<std::intptr_t>(f));
            return result;
      }

      namespace common {

            std::vector<luramas::il::lifter::builder::build::expr> canonicalize_insert(const luramas::profile::inst &inst, const std::shared_ptr<luramas::il::lifter::builder::build> &build, const cs_x86 &dis, const flags &f) {

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

            void explicit_cast(std::shared_ptr<luramas::il::disassembly> &buffer, const std::shared_ptr<luramas::il::ilang> &il, const x86_reg reg, const luramas_address loc, const bool unsign) {

                  luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_BITCAST>(il, loc, buffer, highest(reg), highest(reg), reg_bits(reg), 0u, unsign);
                  return;
            }
            std::shared_ptr<luramas::il::disassembly> explicit_cast(const std::shared_ptr<luramas::il::ilang> &il, const x86_reg reg, const luramas_address loc, const bool unsign) {

                  auto result = std::make_shared<luramas::il::disassembly>();
                  explicit_cast(result, il, reg, loc, unsign);
                  return result;
            }
            std::shared_ptr<luramas::il::disassembly> cast(const std::shared_ptr<luramas::il::ilang> &il, const luramas_register reg, const luramas_bitwidth bits, const luramas_address loc, const bool unsign) {

                  auto result = std::make_shared<luramas::il::disassembly>();
                  luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_BITCAST>(il, loc, result, reg, reg, bits, 0u, unsign);
                  return result;
            }
      } // namespace generate
} // namespace tools
