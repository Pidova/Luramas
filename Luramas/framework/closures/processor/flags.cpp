#include "../closures.hpp"

void luramas::closures::closure::set_flags() {

      boost::unordered_flat_set<luramas_register> append_regs;
      for (auto &i : this->nodes) {

            switch (i->lex->disassembly->op) {

                  case luramas::il::arch::opcodes::OP_POPARG: {
                        append_regs.insert(i->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>().front()->dis.reg);
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CCALL: {
                        i->flags.poparg_flag.call_pop = std::move(append_regs);
                        i->flags.poparg_flag.pop_call_dest = true;
                        append_regs.clear();
                        break;
                  }
                  default: {
                        break;
                  }
            }
      }
      return;
}