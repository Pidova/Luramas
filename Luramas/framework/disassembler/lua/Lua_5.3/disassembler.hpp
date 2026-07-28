#pragma once
#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)
#include "../../../common.hpp"
#include "op_table.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace lua_53_disassembler {

      struct operand {

            op_table::operands encoding = op_table::operands::A; /* Operand encoding kind */
            op_table::type type = op_table::type::nothing;       /* Operand encoding */

            union {
                  luramas_register reg;       /* Register */
                  std::intptr_t val;          /* Value */
                  std::intptr_t jmp;          /* Jump offset */
                  luramas_address upvalue;    /* Upvalue index */
                  luramas_address table_size; /* Table size */
                  std::size_t k_idx;          /* KValue index */
            };

            luramas_address ref_addr = 0u;        /* Reference address */
            std::string k_value = "";             /* Seperate value to represent as a string and idx. Will also serve as import str. */
            std::uint8_t k_value_type = LUA_TNIL; /* Lua Type */
      };

      struct disassembly {

            luramas_address addr = 0u; /* Address of instruction */

            OpCode op; /* Instruction opcode */

            const char *mnenomic = ""; /* Mnenomic of instruction */
            const char *hint = "";     /* Hint of what instruction does */

            std::string data = ""; /* Full disassembled string */
            std::uint8_t len = 0u; /* Length of instruction */

            Instruction *code; /* Code Ptr */

            std::vector<std::shared_ptr<operand>> operands; /* Instruction Operands */
            std::vector<std::uint8_t> bytes;                /* Instruction bytes */
            Proto *p = nullptr;                             /* Linked proto */
            /* Returns disassembly string. */
            template <bool include_hint = false>
            std::string disassemble() {

                  std::string result = std::to_string(this->addr) + " " + this->data;
                  if (include_hint) {
                        result += " " + std::string(this->hint);
                  }
                  return result;
            }
      };

      /* Disassemble address */
      void disassemble(const luramas_address pc, Proto *p, std::shared_ptr<disassembly> &buffer);

      /* Disassemble address */
      void disassemble(Proto *p, std::vector<std::shared_ptr<disassembly>> &buffer);

      namespace make_operand {

            inline std::shared_ptr<lua_53_disassembler::operand> val(const std::intptr_t v) {
                  auto operand = std::make_shared<lua_53_disassembler::operand>();
                  operand->type = op_table::type::val;
                  operand->val = v;
                  return operand;
            }

            inline std::shared_ptr<lua_53_disassembler::operand> reg(const luramas_register v) {
                  auto operand = std::make_shared<lua_53_disassembler::operand>();
                  operand->type = op_table::type::reg;
                  operand->reg = v;
                  return operand;
            }

      } // namespace make_operand

} // namespace lua_53_disassembler
#endif