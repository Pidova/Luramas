#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)
#include "resolver.hpp"
#include "../../../../../il/architecture/emitter.hpp"

namespace lua_53_resolvers {

      void instructions(luramas::il::lifter::resolver::resolver_manager<Proto *> &rm) {

            /* Resolve instructions. */
            for (const auto &i : rm.il->dis) {

                  switch (i->op) {
                        case luramas::il::arch::opcodes::OP_CCALL: {

                              /* Fix multret. */
                              const auto &call = i->operands.front();
                              const auto reg = call->dis.reg;

                              /* Fix args for multret. */
                              if (i->operands[1]->multret && i->operands[1]->dis.reg >= reg) {
                                    i->operands[1]->dis.reg -= reg;
                                    if (!i->operands[1]->dis.reg) {
                                          i->operands[1]->dis.reg = 1U;
                                    }
                              }

                              /* Fix returns for multret. */
                              if (i->operands.back()->multret && i->operands.back()->dis.reg >= reg) {
                                    i->operands.back()->dis.reg -= reg;
                                    if (!i->operands.back()->dis.reg) {
                                          i->operands.back()->dis.reg = 1U;
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

      void jump_operands(luramas::il::lifter::resolver::resolver_manager<Proto *> &rm) {

            for (const auto &i : rm.il->dis) {
                  for (const auto &operand : i->operands) {
                        if (operand->type == luramas::il::arch::operand::operand_kind::jmp) {
                              operand->ref_addr = i->ref->addr;
                              operand->dis.jmp = static_cast<signed>(operand->ref_addr) - static_cast<signed>(i->addr);
                              break;
                        }
                  }
            }
            return;
      }

      void remove_pending(luramas::il::lifter::resolver::resolver_manager<Proto *> &rm) {

            for (auto &i : rm.il->dis) {
                  if (i->op == luramas::il::arch::opcodes::OP_PEND) {
                        luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_NOP>(rm.il, i->addr, i);
                  }
            }
            return;
      }

} // namespace lua_53_resolvers
#endif