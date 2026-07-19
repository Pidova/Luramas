#pragma once
#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)
#include "../../../common.hpp"
#include "op_table.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace luau_v6_disassembler {

      struct operand {

            op_table::operands encoding = op_table::operands::A; /* (A) default, Operand encoding type */
            op_table::type type = op_table::type::nothing;       /* Operand kind */

            union {
                  luramas_register reg;       /* Register */
                  std::intptr_t val;          /* Signed value */
                  std::intptr_t jmp;          /* Jump, not address */
                  std::size_t k_idx;          /* Kvalue index */
                  std::intptr_t aux;          /* Aux */
                  luramas_address slot;       /* Slot */
                  luramas_address upvalue;    /* Upvalue index */
                  luramas_address table;      /* Table value*/
                  luramas_address closure;    /* Closure index */
                  luramas_address table_size; /* Table size */
                  std::uint8_t fastcall_idx;  /* Fastcall index */
                  std::uint8_t capture_ref;   /* Caputure reference kind */
                  std::uint8_t capture_reg;   /* Capture register */
                  std::size_t import_idx;     /* Import index */
                  double integer;             /* Integer */
            };
            std::uint32_t code = 0;                     /* Raw code value */
            luramas_address ref_addr = 0u;              /* reference address */
            std::string k_value = "";                   /* Seperate value to represent as a string and idx. Will also serve as import str. */
            lua_Type k_value_type = lua_Type::LUA_TNIL; /* If operand references kvalue index this will be its type. */
      };

      struct disassembly {

            luramas_address addr = 0u;

            LuauOpcode op;

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
      void disassemble(const luramas_address addr, const Proto *p, std::shared_ptr<disassembly> &buffer);

      /* Disassemble everything */
      void disassemble(const Proto *p, std::vector<std::shared_ptr<disassembly>> &buffer);

      namespace make_operand {

            inline std::shared_ptr<luau_v6_disassembler::operand> make_operand_integer(const double v) {
                  auto operand = std::make_shared<luau_v6_disassembler::operand>();
                  operand->type = op_table::type::integer;
                  operand->integer = v;
                  return operand;
            }

            inline std::shared_ptr<luau_v6_disassembler::operand> make_operand_val(const std::intptr_t v) {
                  auto operand = std::make_shared<luau_v6_disassembler::operand>();
                  operand->type = op_table::type::val;
                  operand->val = v;
                  return operand;
            }

            inline std::shared_ptr<luau_v6_disassembler::operand> make_operand_reg(const luramas_register v) {
                  auto operand = std::make_shared<luau_v6_disassembler::operand>();
                  operand->type = op_table::type::reg;
                  operand->reg = v;
                  return operand;
            }

            inline std::shared_ptr<luau_v6_disassembler::operand> make_operand_jump(luramas_vaddress jmp, const luramas_address on) {
                  auto operand = std::make_shared<luau_v6_disassembler::operand>();
                  operand->type = op_table::type::jmp;
                  if (jmp < 0) {
                        jmp = -jmp;
                  }
                  operand->jmp = jmp;
                  operand->ref_addr = jmp + on;
                  return operand;
            }

      } // namespace make_operand

} // namespace luau_v6_disassembler
#endif