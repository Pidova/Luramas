#pragma once
#include "../../../common.hpp"
#include "op_table.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace lua_53_6_disassembler {

      struct operand {

            op_table::operands operand;
            op_table::type type;

            union {
                  luramas_register reg;
                  std::intptr_t val;
                  std::intptr_t jmp;
                  luramas_address upvalue;
                  luramas_address table_size;
                  std::size_t k_idx;
            };

            luramas_address ref_addr = 0u;
            std::string k_value = ""; /* Seperate value to represent as a string and idx. Will also serve as import str. */
            std::uint8_t k_value_type = LUA_TNIL;
      };

      struct disassembly {

            luramas_address addr = 0u;

            OpCode op;

            const char *mnenomic = "";
            const char *hint = "";

            std::string data = "";
            std::uint8_t len = 0u;

            Instruction *code;

            std::vector<std::shared_ptr<operand>> operands;
            std::vector<std::uint8_t> bytes;

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
      void disassemble(const luramas_address pc, const Proto *p, std::shared_ptr<disassembly> &buffer);

      /* Disassemble address */
      void disassemble(const Proto *p, std::vector<std::shared_ptr<disassembly>> &buffer);

      namespace make_operand {

            inline std::shared_ptr<lua_53_6_disassembler::operand> make_operand_reg(const luramas_register v) {
                  auto operand = std::make_shared<lua_53_6_disassembler::operand>();
                  operand->type = op_table::type::reg;
                  operand->reg = v;
                  return operand;
            }

      } // namespace make_operand

} // namespace lua_53_6_disassembler