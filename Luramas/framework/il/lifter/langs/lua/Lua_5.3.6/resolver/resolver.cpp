#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_536)
#include "resolver.hpp"

void resolver::resolve_instructions(std::shared_ptr<luramas::il::ilang> &buffer) {

      /* Resolve instructions. */
      for (const auto &i : buffer->dis) {

            switch (i->op) {

                  case luramas::il::arch::opcodes::OP_CCALL: {

                        /* Fix multret. */

                        const auto call = i->operands.front();

                        /* Fix args for multret. */
                        if (i->operands[1]->multret) {
                              i->operands[1]->dis.reg = i->operands[1]->dis.reg - call->dis.reg;
                        }

                        /* Fix args for multret. */
                        if (i->operands.back()->multret) {
                              i->operands.back()->dis.reg = i->operands.back()->dis.reg - call->dis.reg;
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

/* Resolves block data. */
void resolver::resolve_blocks(std::shared_ptr<luramas::il::ilang> &buffer) {

      luramas_address pc = 0u;
      for (auto &il : buffer->dis) {

            il->addr = pc++;
      }

      return;
}

/* Resolves jump locations. */
void resolver::resolve_jumps(std::shared_ptr<luramas::il::ilang> &buffer, const std::vector<std::pair<std::shared_ptr<luramas::il::disassembly> /* Jumper */, std::shared_ptr<luramas::il::disassembly> /* Jump location */>> &map) {

      for (const auto &i : map) {

            for (const auto &operand : i.first->operands) {

                  if (operand->type == luramas::il::arch::operand::operand_kind::jmp) {
                        operand->ref_addr = i.second->addr;
                        operand->dis.jmp = signed(operand->ref_addr) - signed(i.first->addr);
                        break;
                  }
            }
      }

      return;
}

#endif