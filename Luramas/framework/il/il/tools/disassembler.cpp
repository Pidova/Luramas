#include "disassembler.hpp"

namespace luramas::il::disassembler {

      const char *const mnemonic_string(const luramas::il::arch::opcodes op) {

            if (const auto it = arch::opcode_to_str.find(op); it != arch::opcode_to_str.end()) {
                  return it->second;
            }
            return "";
      }

      const char *const mnemonic_hint_string(const luramas::il::arch::opcodes op) {

            switch (op) {
                  case luramas::il::arch::opcodes::OP_NOP: {
                        return "Nothing";
                  }
                  case luramas::il::arch::opcodes::OP_LOADBOOL: {
                        return "Loads a boolean to a register.";
                  }
                  case luramas::il::arch::opcodes::OP_LOADINT: {
                        return "Loads a integer to a register.";
                  }
                  case luramas::il::arch::opcodes::OP_LOADNONE: {
                        return "Loads a none object to a register.";
                  }
                  case luramas::il::arch::opcodes::OP_LOADKVAL: {
                        return "Loads a kvalue to a register.";
                  }
                  case luramas::il::arch::opcodes::OP_LOADGLOBAL: {
                        return "Loads a global to a register.";
                  }
                  case luramas::il::arch::opcodes::OP_GETTABUPVALUE: {
                        return "Loads an embeded kvalue to a register.";
                  }
                  case luramas::il::arch::opcodes::OP_SETGLOBAL: {
                        return "Sets global with a register value.";
                  }
                  case luramas::il::arch::opcodes::OP_MOVE: {
                        return "Copys register contents into another register.";
                  }
                  case luramas::il::arch::opcodes::OP_ADD: {
                        return "Arithmetic add with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_SUB: {
                        return "Arithmetic sub with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_MUL: {
                        return "Arithmetic mul with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_DIV: {
                        return "Arithmetic div with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_MOD: {
                        return "Arithmetic mod with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_POW: {
                        return "Arithmetic pow with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_XOR: {
                        return "Bitwise xor with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_AND: {
                        return "Bitwise and with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_SHL: {
                        return "Bitwise shift left with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_SHR: {
                        return "Bitwise shift right with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_IDIV: {
                        return "Floor division shift right with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_OR: {
                        return "Bitwise or with a destination register and two source operands.";
                  }
                  case luramas::il::arch::opcodes::OP_ADDK: {
                        return "Arithmetic add with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_SUBK: {
                        return "Arithmetic sub with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_MULK: {
                        return "Arithmetic mul with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_DIVK: {
                        return "Arithmetic div with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_MODK: {
                        return "Arithmetic mod with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_POWK: {
                        return "Arithmetic pow with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_XORK: {
                        return "Bitwise xor with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_ANDK: {
                        return "Bitwise and with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_SHLK: {
                        return "Bitwise shift left with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_SHRK: {
                        return "Bitwise shift right with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_IDIVK: {
                        return "Floor division with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_ORK: {
                        return "Bitwise or with a destination register, a source register, and a source kvalue operand.";
                  }
                  case luramas::il::arch::opcodes::OP_ADDN: {
                        return "Arithmetic add with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_SUBN: {
                        return "Arithmetic sub with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_MULN: {
                        return "Arithmetic mul with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_DIVN: {
                        return "Arithmetic div with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_MODN: {
                        return "Arithmetic mod with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_POWN: {
                        return "Arithmetic pow with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_XORN: {
                        return "Bitwise xor with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_ANDN: {
                        return "Bitwise and with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_SHLN: {
                        return "Bitwise shift left with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_SHRN: {
                        return "Bitwise shift right with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_IDIVN: {
                        return "Floor division right with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_ORN: {
                        return "Bitwise or with a destination register, a source register, and a source integer operand.";
                  }
                  case luramas::il::arch::opcodes::OP_LEN: {
                        return "Unary table lenght.";
                  }
                  case luramas::il::arch::opcodes::OP_NOT: {
                        return "Unary not.";
                  }
                  case luramas::il::arch::opcodes::OP_MINUS: {
                        return "Unary minus.";
                  }
                  case luramas::il::arch::opcodes::OP_BITNOT: {
                        return "Unary bitwise not.";
                  }
                  case luramas::il::arch::opcodes::OP_PLUS: {
                        return "Unary plus.";
                  }
                  case luramas::il::arch::opcodes::OP_REF: {
                        return "Basic register or memory reference.";
                  }
                  case luramas::il::arch::opcodes::OP_CCALL: {
                        return "C function call instruction that uses arguement stack for its Arguments.";
                  }
                  case luramas::il::arch::opcodes::OP_VCALL: {
                        return "Virtual function call instruction that uses isolated arguement stack for its Arguments.";
                  }
                  case luramas::il::arch::opcodes::OP_VPUSH: {
                        return "Pushes register to virtual arguement call stack.";
                  }
                  case luramas::il::arch::opcodes::OP_SELF: {
                        return "Loads table function too register.";
                  }
                  case luramas::il::arch::opcodes::OP_RETURN: {
                        return "Return instruction.";
                  }
                  case luramas::il::arch::opcodes::OP_CONCAT: {
                        return "String concat instruction.";
                  }
                  case luramas::il::arch::opcodes::OP_JUMP: {
                        return "Jump too address.";
                  }
                  case luramas::il::arch::opcodes::OP_CMP: {
                        return "Sets cmp flag with two compare registers.";
                  }
                  case luramas::il::arch::opcodes::OP_CMPK: {
                        return "Sets cmp flag with a compare register and a kvalue.";
                  }
                  case luramas::il::arch::opcodes::OP_CMPN: {
                        return "Sets cmp flag with a compare register and integer.";
                  }
                  case luramas::il::arch::opcodes::OP_CMPB: {
                        return "Sets cmp flag with a compare register and boolean.";
                  }
                  case luramas::il::arch::opcodes::OP_CMPNONE: {
                        return "Sets cmp flag with a compare register and a none object.";
                  }
                  case luramas::il::arch::opcodes::OP_CMPS: {
                        return "Sets cmp flag with a compare register.";
                  }
                  case luramas::il::arch::opcodes::OP_CMPSK: {
                        return "Sets cmp flag with a compare kvalue.";
                  }
                  case luramas::il::arch::opcodes::OP_CMPSN: {
                        return "Sets cmp flag with a compare integer.";
                  }
                  case luramas::il::arch::opcodes::OP_CMPSNONE: {
                        return "Sets cmp flag with a compare none object.";
                  }
                  case luramas::il::arch::opcodes::OP_JUMPIF: {
                        return "Jump if register compare with register is true.";
                  }
                  case luramas::il::arch::opcodes::OP_JUMPIFNOT: {
                        return "Jump if register compare with register is not true.";
                  }
                  case luramas::il::arch::opcodes::OP_JUMPIFEQUAL: {
                        return "Jump if register compare with register is equal.";
                  }
                  case luramas::il::arch::opcodes::OP_JUMPIFNOTEQUAL: {
                        return "Jump if register compare with register is not equal.";
                  }
                  case luramas::il::arch::opcodes::OP_JUMPIFLESS: {
                        return "Jump if register compare with register is less than.";
                  }
                  case luramas::il::arch::opcodes::OP_JUMPIFLESSEQUAL: {
                        return "Jump if register compare with register is less than or equal too.";
                  }
                  case luramas::il::arch::opcodes::OP_JUMPIFGREATER: {
                        return "Jump if register compare with register is greater than.";
                  }
                  case luramas::il::arch::opcodes::OP_JUMPIFGREATEREQUAL: {
                        return "Jump if register compare with register is greater than or equal too.";
                  }
                  case luramas::il::arch::opcodes::OP_SETIF: {
                        return "Sets register with true or false if cmp flag is true.";
                  }
                  case luramas::il::arch::opcodes::OP_SETIFNOT: {
                        return "Sets register with true or false if cmp flag is not true.";
                  }
                  case luramas::il::arch::opcodes::OP_SETIFEQUAL: {
                        return "Sets register with true or false if cmp flag if equal too.";
                  }
                  case luramas::il::arch::opcodes::OP_SETIFNOTEQUAL: {
                        return "Sets register with true or false if cmp flag if not equal too.";
                  }
                  case luramas::il::arch::opcodes::OP_SETIFLESS: {
                        return "Sets register with true or false if cmp flag if less than.";
                  }
                  case luramas::il::arch::opcodes::OP_SETIFLESSEQUAL: {
                        return "Sets register with true or false if cmp flag if less than or equal too.";
                  }
                  case luramas::il::arch::opcodes::OP_SETIFGREATER: {
                        return "Sets register with true or false if cmp flag if greater than.";
                  }
                  case luramas::il::arch::opcodes::OP_SETIFGREATEREQUAL: {
                        return "Sets register with true or false if cmp flag if greater than or equal too.";
                  }
                  case luramas::il::arch::opcodes::OP_SETUPVALUE: {
                        return "Set upvalue with an register as the value.";
                  }
                  case luramas::il::arch::opcodes::OP_GETUPVALUE: {
                        return "Gets upvalue and sets it too a register.";
                  }
                  case luramas::il::arch::opcodes::OP_DESTROYUPVALUES: {
                        return "Destroys all upvalue in current closure.";
                  }
                  case luramas::il::arch::opcodes::OP_DESTROYUPVALUESA: {
                        return "Destroys all upvalue with target in current closure.";
                  }
                  case luramas::il::arch::opcodes::OP_ADDUPVALUE: {
                        return "Adds upvalue too next closure in following code.";
                  }
                  case luramas::il::arch::opcodes::OP_POPTOP: {
                        return "Pops register from top of the stack.";
                  }
                  case luramas::il::arch::opcodes::OP_INIT: {
                        return "Initiates code.";
                  }
                  case luramas::il::arch::opcodes::OP_BITCAST: {
                        return "Bitcast source register to n bits.";
                  }
                  case luramas::il::arch::opcodes::OP_GETVARIADIC: {
                        return "Gets variadic and sets it a register.";
                  }
                  case luramas::il::arch::opcodes::OP_SETTABLE: {
                        return "Sets value in table with a register index.";
                  }
                  case luramas::il::arch::opcodes::OP_GETTABLE: {
                        return "Gets value in table with a register index.";
                  }
                  case luramas::il::arch::opcodes::OP_SETTABLEN: {
                        return "Sets value in table with a integer index.";
                  }
                  case luramas::il::arch::opcodes::OP_GETTABLEN: {
                        return "Gets value in table with a integer index.";
                  }
                  case luramas::il::arch::opcodes::OP_SETTABLEK: {
                        return "Sets value in table with a kvalue index.";
                  }
                  case luramas::il::arch::opcodes::OP_GETTABLEK: {
                        return "Gets value in table with a kvalue index.";
                  }
                  case luramas::il::arch::opcodes::OP_INITFORLOOPN: {
                        return "Initiates numeric for loop.";
                  }
                  case luramas::il::arch::opcodes::OP_INITFORLOOPG: {
                        return "Initiates generic for loop.";
                  }
                  case luramas::il::arch::opcodes::OP_INITFORLOOPSPECIAL: {
                        return "Initiates special generic for loop.";
                  }
                  case luramas::il::arch::opcodes::OP_NEWCLOSURE: {
                        return "Creates a new closure for register.";
                  }
                  case luramas::il::arch::opcodes::OP_REFCLOSURE: {
                        return "Loads register with kvalue closure. ";
                  }
                  case luramas::il::arch::opcodes::OP_NEWTABLE: {
                        return "Creates new table for register with exact sizes.";
                  }
                  case luramas::il::arch::opcodes::OP_REFTABLE: {
                        return "Loads register with kvalue table that has approximate sizes.";
                  }
                  case luramas::il::arch::opcodes::OP_NEWTABLEA: {
                        return "Creates new table for register with approximate sizes.";
                  }
                  case luramas::il::arch::opcodes::OP_REFTABLEA: {
                        return "Loads register with kvalue table that has approximate sizes.";
                  }
                  case luramas::il::arch::opcodes::OP_SETLIST: {
                        return "Appends elements in table.";
                  }
                  case luramas::il::arch::opcodes::OP_POPARG: {
                        return "Adds register too pop arguement flag.";
                  }
                  case luramas::il::arch::opcodes::OP_MEMSET: {
                        return "Memory set.";
                  }
                  case luramas::il::arch::opcodes::OP_MEMREAD: {
                        return "Memory read.";
                  }
                  case luramas::il::arch::opcodes::OP_SETFLAG: {
                        return "Appends flag to flag stack.";
                  }
                  case luramas::il::arch::opcodes::OP_SALLOC: {
                        return "Stack allocates n bytes.";
                  }
                  case luramas::il::arch::opcodes::OP_STACKPOP: {
                        return " Pops register contents from the given stack.";
                  }
                  case luramas::il::arch::opcodes::OP_POPTOPSTACK: {
                        return " Pops top item off given stack.";
                  }
                  case luramas::il::arch::opcodes::OP_STACKPUSH: {
                        return "Pushes register contents onto given stack.";
                  }
                  case luramas::il::arch::opcodes::OP_GETSTACK: {
                        return "Gets stack object from source register to dest.";
                  }
                  case luramas::il::arch::opcodes::OP_SETSTACK: {
                        return "Sets stack object pointer from source to ID.";
                  }
                  case luramas::il::arch::opcodes::OP_FORLOOPG: {
                        return "For generic loop.";
                  }
                  case luramas::il::arch::opcodes::OP_FORLOOPN: {
                        return "For numeric loop.";
                  }
                  case luramas::il::arch::opcodes::OP_CLOGIC_AND: {
                        return "Condition logical AND.";
                  }
                  case luramas::il::arch::opcodes::OP_CLOGIC_OR: {
                        return "Condition logical OR.";
                  }
                  case luramas::il::arch::opcodes::OP_PEND: {
                        return "Psuedo-Instruction, pending analysis.";
                  }
                  case luramas::il::arch::opcodes::OP_MARK: {
                        return "Psuedo-Instruction, marks spot in code doesnt do anything.";
                  }
                  case luramas::il::arch::opcodes::OP_MOBJ_CAST: {
                        return "Casts register to an object in object map.";
                  }
                  case luramas::il::arch::opcodes::OP_NCTOR_MOBJ: {
                        return "See if source is object from object map if not construct.";
                  }
                  case luramas::il::arch::opcodes::OP_SCALL: {
                        return "Call to symbol table.";
                  }
                  case luramas::il::arch::opcodes::OP_FLAGSET: {
                        return "Set flag with source";
                  }
                  case luramas::il::arch::opcodes::OP_FLAGREAD: {
                        return "Read flag to dest";
                  }
                  case luramas::il::arch::opcodes::OP_CREATE_STACK: {
                        return "Psuedo-instruction, Indicates that dest register could be a stack if its safe";
                  }
                  case luramas::il::arch::opcodes::OP_PRETURN: {
                        return "Unkown return count (Closure will be mapped)";
                  }
                  case luramas::il::arch::opcodes::OP_STARTPAGEFUNC: {
                        return "Start of page function";
                  }
                  case luramas::il::arch::opcodes::OP_ENDPAGEFUNC: {
                        return "End of page function";
                  }
                  case luramas::il::arch::opcodes::OP_PCALL: {
                        return "Call to page function";
                  }
                  case luramas::il::arch::opcodes::OP_PJUMP: {
                        return "Jump to page";
                  }
                  case luramas::il::arch::opcodes::OP_SEGREGATE: {
                        return "Next instruction any native flags set will be offset.";
                  }
                  case luramas::il::arch::opcodes::OP_COMBINE: {
                        return "Flag to combine data from previous instruction to next.";
                  }
                  case luramas::il::arch::opcodes::OP_FLAGJUMP: {
                        return "If flag is true jump to page.";
                  }
                  case luramas::il::arch::opcodes::OP_ICALL: {
                        return "If register(reg) == ID(Val) call (Follows same schema as OP_CCALL if condition is true).";
                  }
                  case luramas::il::arch::opcodes::OP_TAG_START: {
                        return "Start of tag.";
                  }
                  case luramas::il::arch::opcodes::OP_TAG_KV: {
                        return "Set next tag key value pair.";
                  }
                  case luramas::il::arch::opcodes::OP_TAG_END: {
                        return "End tag.";
                  }
                  case luramas::il::arch::opcodes::OP_METADATA: {
                        return "Metadata, User handled instruction.";
                  }
                  case luramas::il::arch::opcodes::OP_ENTRY_POINT: {
                        return "Entry point.";
                  }
                  case luramas::il::arch::opcodes::OP_COMMAND: {
                        return "Internal command.";
                  }
                  case luramas::il::arch::opcodes::OP_BITREAD: {
                        return "Read bits and interpret them.";
                  }
                  case luramas::il::arch::opcodes::OP_BITWRITE: {
                        return "Writes bits to the first source but it incs from start to end of second source ending either at end or bitwidth and Interpret result same as bit cast.";
                  }
                  case luramas::il::arch::opcodes::OP_BITWRITEA: {
                        return "Writes bits [MIN, MAX] to dest from source.";
                  }
                  case luramas::il::arch::opcodes::OP_ANNOTATE_PREV: {
                        return "Implement annotation to previous instruction.";
                  }
                  default: {
                        luramas::error::error("Unkown IL opcode.");
                  }
            }
            return NULL;
      }

      std::string operand_string(const std::shared_ptr<luramas::il::arch::operand::operand> &operand) {

            std::string result("");

            switch (operand->type) {
                  case luramas::il::arch::operand::operand_kind::none: {
                        result = "none";
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::reg: {
                        result = "r" + std::to_string(operand->dis.reg);
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::kval:
                  case luramas::il::arch::operand::operand_kind::kval_string: {
                        result = operand->k_value;
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::table_size: {
                        result = std::to_string(operand->dis.table_size);
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::jmp: {
                        result = std::to_string(operand->ref_addr);
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::closure_index: {
                        result = std::to_string(operand->dis.closure_idx);
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::upvalue: {
                        result = std::to_string(operand->dis.upvalue_idx);
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::integer: {
                        result = std::to_string(operand->dis.integer);
                        luramas_str_integer(result);
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::value: {
                        result = std::to_string(operand->dis.val);
                        luramas_str_integer(result);
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::boolean: {
                        result = (operand->dis.boolean) ? "true" : "false";
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::upvalue_kind: {

                        switch (operand->dis.upvalue_kind) {
                              case luramas::il::arch::operand::upvalue_kind::upvalues: {
                                    result = "upvalue";
                                    break;
                              }
                              case luramas::il::arch::operand::upvalue_kind::contents: {
                                    result = "content";
                                    break;
                              }
                              case luramas::il::arch::operand::upvalue_kind::reference: {
                                    result = "reference";
                                    break;
                              }
                              default: {
                                    luramas::error::error("Unkown upvalue kind.");
                              }
                        }
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::upvalue_capture: {
                        result = "r" + std::to_string(operand->dis.reg);
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::closure: {
                        result = "cls_" + std::to_string(operand->dis.closure_id);
                        break;
                  }
                  default: {
                        luramas::error::error("Unkown IL operand type.");
                  }
            }
            return result;
      }
} // namespace luramas::il::disassembler