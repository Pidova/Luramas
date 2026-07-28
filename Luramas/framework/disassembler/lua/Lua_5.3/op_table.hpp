#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)
#include "3rdparty/imports.hpp"
#include <array>
#include <cstdint>
#include <vector>

namespace op_table {

      /* Operand encoding */
      enum class operands : std::uint8_t {
            A,  /* Encoding A */
            B,  /* Encoding B */
            C,  /* Encoding C */
            Ax, /* Encoding Ax */
            Bx, /* Encoding Bx */
            sBx /* Encoding sBx */
      };

      /* High level tyypes of operand */
      enum class type : std::uint8_t {
            nothing,     /* No type */
            reg,         /* Register. */
            val,         /* Value. (signed 64 bit integer) */
            boolean,     /* Boolean value */
            jmp,         /* Jump. */
            k_idx,       /* Kvalue index. */
            upvalue,     /* Upvalue. */
            table_size,  /* Table size. */
            val_multret, /* Value that can be a multret. (-1) */
            dest         /* Dest register. */
      };

      struct optable {
            OpCode op = OpCode::OP_MOVE;              /* Opcode */
            std::vector<op_table::operands> operands; /* Operand */
            std::vector<op_table::type> types;        /* Types of operands */
      };
      static optable op_table[] = {

          {OpCode::OP_MOVE, {op_table::operands::A, op_table::operands::B}, {op_table::type::dest, op_table::type::reg}},
          {OpCode::OP_LOADK, {op_table::operands::A, op_table::operands::Bx}, {op_table::type::dest, op_table::type::k_idx}},
          {OpCode::OP_LOADKX, {op_table::operands::Ax}, {op_table::type::dest}},
          {OpCode::OP_LOADBOOL, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::boolean, op_table::type::val}},
          {OpCode::OP_LOADNIL, {op_table::operands::A, op_table::operands::B}, {op_table::type::dest, op_table::type::val}},
          {OpCode::OP_GETUPVAL, {op_table::operands::A, op_table::operands::B}, {op_table::type::dest, op_table::type::upvalue}},

          {OpCode::OP_GETTABUP, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::upvalue, op_table::type::val}},
          {OpCode::OP_GETTABLE, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::val}},

          {OpCode::OP_SETTABUP, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::upvalue, op_table::type::val, op_table::type::val}},
          {OpCode::OP_SETUPVAL, {op_table::operands::A, op_table::operands::B}, {op_table::type::upvalue, op_table::type::reg}},
          {OpCode::OP_SETTABLE, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::reg, op_table::type::val, op_table::type::val}},

          {OpCode::OP_NEWTABLE, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::table_size, op_table::type::table_size}},

          {OpCode::OP_SELF, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::val, op_table::type::val}},

          {OpCode::OP_ADD, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_SUB, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_MUL, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_MOD, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_POW, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_DIV, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_IDIV, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_BAND, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_BOR, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_BXOR, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_SHL, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_SHR, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_UNM, {op_table::operands::A, op_table::operands::B}, {op_table::type::dest, op_table::type::reg}},
          {OpCode::OP_BNOT, {op_table::operands::A, op_table::operands::B}, {op_table::type::dest, op_table::type::reg}},
          {OpCode::OP_NOT, {op_table::operands::A, op_table::operands::B}, {op_table::type::dest, op_table::type::reg}},
          {OpCode::OP_LEN, {op_table::operands::A, op_table::operands::B}, {op_table::type::dest, op_table::type::reg}},

          {OpCode::OP_CONCAT, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::reg, op_table::type::reg}},

          {OpCode::OP_JMP, {op_table::operands::A, op_table::operands::sBx}, {op_table::type::val, op_table::type::jmp}},
          {OpCode::OP_EQ, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::val, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_LT, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::val, op_table::type::reg, op_table::type::reg}},
          {OpCode::OP_LE, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::val, op_table::type::reg, op_table::type::reg}},

          {OpCode::OP_TEST, {op_table::operands::A, op_table::operands::C}, {op_table::type::reg, op_table::type::val}},
          {OpCode::OP_TESTSET, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::reg, op_table::type::reg, op_table::type::val}},

          {OpCode::OP_CALL, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::val_multret, op_table::type::val_multret}},
          {OpCode::OP_TAILCALL, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::dest, op_table::type::val_multret, op_table::type::val_multret}},
          {OpCode::OP_RETURN, {op_table::operands::A, op_table::operands::B}, {op_table::type::reg, op_table::type::val_multret}},

          {OpCode::OP_FORLOOP, {op_table::operands::A, op_table::operands::sBx}, {op_table::type::reg, op_table::type::jmp}},
          {OpCode::OP_FORPREP, {op_table::operands::A, op_table::operands::sBx}, {op_table::type::reg, op_table::type::jmp}},

          {OpCode::OP_TFORCALL, {op_table::operands::A, op_table::operands::C}, {op_table::type::reg, op_table::type::val}},

          {OpCode::OP_TFORLOOP, {op_table::operands::A, op_table::operands::sBx}, {op_table::type::reg, op_table::type::jmp}},

          {OpCode::OP_SETLIST, {op_table::operands::A, op_table::operands::B, op_table::operands::C}, {op_table::type::reg, op_table::type::val_multret, op_table::type::val_multret}},

          {OpCode::OP_CLOSURE, {op_table::operands::A, op_table::operands::Bx}, {op_table::type::reg, op_table::type::val}},
          {OpCode::OP_VARARG, {op_table::operands::A, op_table::operands::B}, {op_table::type::reg, op_table::type::val_multret}},

          {OpCode::OP_EXTRAARG, {op_table::operands::Ax}, {op_table::type::reg}},

      };

} // namespace op_table
#endif