#pragma once
#include "../il/il.hpp"
#include <functional>

namespace luramas::il::lexer {

      /* Operand kinds */
      enum class operand_kinds : std::uint8_t {
            reg,            /* [REGISTER] Generic register not a dest. */
            dest,           /* [REGISTER] Reg dest. */
            source,         /* [REGISTER] Reg source. */
            integer,        /* [DOUBLE] Double type source. */
            value,          /* [INTEGER] Intptr type source. */
            compare,        /* [REGISTER] Compare register. */
            jmpaddr,        /* [ADDRESS] Jump location. */
            closure,        /* [ClOSURE INDEX] Closure index for closure stack. */
            kvalue,         /* [KVALUE INDEX] Kvalue index for kvalue stack. */
            kvalue_embeded, /* [KVALUE] Pre-processes kvalue source. */
            upvalue,        /* [UPVALUE INDEX] Upvalue index for upvalue stack. */
            table_idx,      /* [INTEGER] Table idx. */
            table_reg,      /* [REGISTER] Table idx reg. */
            upvalue_kind,   /* [UPVALUE KIND] Upvalue capture kind. */
            boolean         /* [BOOLEAN] Basic boolean value. */
      };

      /* Instruction kinds */
      enum class inst_kinds : std::uint8_t {
            nothing,          /* Nop and Break opcodes. */
            arith,            /* Arith opcodes add, sub, and, or, etc. */
            branch_condition, /* Condition branching opcodes. */
            branch,           /* Branching opcodes. */
            compare,          /* Instruction writes too cmp flag. */
            compare_dest,     /* Instruction writes compares cmp flag and writes too dest. */
            load,             /* Load opcodes. */
            for_,             /* For loop opcodes. */
            forinit,          /* For init loop opcodes. */
            unary,            /* Minus, Not, and Lenght. */
            table_get,        /* Table get. */
            table_set,        /* Table set. */
            set_table,        /* Set table opcodes. (Not init) */
            upvalue_gs,       /* Upvalue get/set. */
            expression,       /* Everything else. */
            ccall,            /* C function call */
            vcall,            /* Virtual function Call */
            set_global,       /* Set global */
            get_global,       /* Get global */
            set_attr,         /* Set attribute */
            new_table,        /* Creates/reference table */
            capture,          /* Capture */
            return_,          /* Return */
            special_flag      /* Special instruction that porpose is too modify a flag. */
      };

      /* Lexeme */
      struct lexeme {

            luramas::il::lexer::inst_kinds kind = inst_kinds::expression;                                     /* Instruction kind */
            boost::fixed_vector<luramas::il::lexer::operand_kinds, arch::operand::OPERAND_MAX_SIZE> operands; /* Operand kinds */
            std::shared_ptr<luramas::il::disassembly> disassembly = nullptr;                                  /* IL disassembly */

            /* Returns if opcode starts a scope (Does not indicate start of a jmp) */
            bool scope_start() const;

            /* Kind is guaranteed to be a statement */
            bool kind_stat() const;

            bool jumps() const;
            luramas_address jump() const;
            bool jump_forward() const;
            bool jump_backwards() const;

            /* Returns if given kind exists. */
            template <luramas::il::lexer::operand_kinds kind>
            bool has_operand_kind() const {
                  return this->operands.size() == this->disassembly->operands.size() && std::find(this->operands.begin(), this->operands.end(), kind) != this->operands.end();
            }

            /* Gets first operand target if there is multiple. */
            template <luramas::il::lexer::operand_kinds kind>
            std::vector<std::shared_ptr<luramas::il::arch::operand::operand>> operand_kind() const {

                  std::vector<std::shared_ptr<luramas::il::arch::operand::operand>> result;
                  if (this->operands.size() != this->disassembly->operands.size()) {
                        return result;
                  }
                  for (auto i = 0u; i < this->operands.size(); ++i) {
                        if (this->operands[i] == kind) {
                              result.emplace_back(this->disassembly->operands[i]);
                        }
                  }
                  return result;
            }
      };

      std::shared_ptr<lexeme> lexer(const std::shared_ptr<luramas::il::disassembly> &disassembly);

} // namespace luramas::il::lexer