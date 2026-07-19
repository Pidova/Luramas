#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)
#include "resolver.hpp"
#include "../../../../../il/architecture/emitter.hpp"

void luau_v6_resolvers::resolve_instruction_operands(luramas::il::lifter::resolver::resolver_manager<Proto *> &pm) {

      /* Resolve instructions. */
      for (const auto &i : pm.il->dis) {

            switch (i->op) {

                  case luramas::il::arch::opcodes::OP_CCALL: {

                        /* Fix multret. */
                        const auto &call = i->operands.front();
                        const auto reg = call->dis.reg;

                        /* Fix args for multret. */
                        if (i->operands[1]->multret && i->operands[1]->dis.reg >= reg) {
                              i->operands[1]->dis.reg -= reg;
                              if (!i->operands[1]->dis.reg) {
                                    i->operands[1]->dis.reg = 1u;
                              }
                        }

                        /* Fix returns for multret. */
                        if (i->operands.back()->multret && i->operands.back()->dis.reg >= reg) {
                              i->operands.back()->dis.reg -= reg;
                              if (!i->operands.back()->dis.reg) {
                                    i->operands.back()->dis.reg = 1u;
                              }
                        }
                        break;
                  }

                  case luramas::il::arch::opcodes::OP_GETVARIADIC: {

                        const auto ret = i->operands.front()->dis.reg;
                        if (i->operands[1]->multret && i->operands[1]->dis.val >= ret) {
                              i->operands[1]->dis.val -= ret;
                              if (i->operands[1]->dis.val <= 0) {
                                    i->operands[1]->dis.val = 1;
                              }
                        }
                        break;
                  }

                  case luramas::il::arch::opcodes::OP_RETURN: {

                        const auto ret = i->operands.front()->dis.reg;
                        if (i->operands[1]->multret && i->operands[1]->dis.val >= ret) {
                              i->operands[1]->dis.val -= ret - 1u;
                              if (i->operands[1]->dis.val <= 0) {
                                    i->operands[1]->dis.val = 1;
                              }
                        }
                        break;
                  }

                  case luramas::il::arch::opcodes::OP_SETLIST: {

                        const auto ret = i->operands.front()->dis.reg;
                        if (i->operands[2]->multret && i->operands[2]->dis.val >= ret) {
                              i->operands[2]->dis.val -= ret;
                              if (i->operands[2]->dis.val <= 0) {
                                    i->operands[2]->dis.val = 1;
                              }
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
      }
      return;
}

void luau_v6_resolvers::resolve_jump_operands(luramas::il::lifter::resolver::resolver_manager<Proto *> &rm) {

      for (const auto &i : rm.il->dis) {
            for (const auto &operand : i->operands) {
                  if (operand->type == luramas::il::arch::operand::operand_kind::jmp) {
                        operand->ref_addr = i->ref->addr;
                        operand->dis.jmp = signed(operand->ref_addr) - signed(i->addr);
                        break;
                  }
            }
      }
      return;
}

void luau_v6_resolvers::resolve_instructions(luramas::il::lifter::resolver::resolver_manager<Proto *> &rm) {

      /* Emit instruction. */
      for (auto i = 0u; i < rm.il->dis.size(); ++i) {

            auto &il = rm.il->dis[i];
            switch (il->op) {
                  case luramas::il::arch::opcodes::OP_SELF: {
                        rm.il->insert(il, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_POPARG>(rm.il, il->addr, il->operands.front()->dis.reg + 1u));
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_PEND: {
                        rm.il->remove<true>(il);
                        switch (il->operands.back()->dis.val) {
                              case LuauOpcode::LOP_AND: {
                                    rm.il->insert(il, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_CLOGIC_AND>(rm.il, il->addr, il->operands.front()->dis.reg, il->operands[1u]->dis.val, il->operands[2u]->dis.val));
                                    break;
                              }
                              case LuauOpcode::LOP_OR: {
                                    rm.il->insert(il, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_CLOGIC_OR>(rm.il, il->addr, il->operands.front()->dis.reg, il->operands[1u]->dis.val, il->operands[2u]->dis.val));
                                    break;
                              }
                              case LuauOpcode::LOP_ANDK: {
                                    const auto reg = rm.il->temp_reg;
                                    rm.il->insert(il, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_LOADKVAL>(rm.il, il->addr, reg, il->operands[2u]->dis.val));
                                    rm.il->insert(il, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_CLOGIC_AND>(rm.il, il->addr, il->operands.front()->dis.reg, il->operands[1u]->dis.val, reg));
                                    break;
                              }
                              case LuauOpcode::LOP_ORK: {
                                    const auto reg = rm.il->temp_reg;
                                    rm.il->insert(il, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_LOADKVAL>(rm.il, il->addr, reg, il->operands[2u]->dis.val));
                                    rm.il->insert(il, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_CLOGIC_OR>(rm.il, il->addr, il->operands.front()->dis.reg, il->operands[1u]->dis.val, reg));
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }

                        break;
                  }
                  default: {
                        break;
                  }
            }
      }
}
#endif