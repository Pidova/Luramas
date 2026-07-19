#pragma once
#include "../il.hpp"
#include <iostream>

namespace luramas::il::emitter {

      /* Emits operand kind to IL disassembly. */
      inline void emit_operand_kind(const std::shared_ptr<luramas::il::ilang> &il, const luramas::il::arch::operand::operand_kind kind, const luramas_address addr, const std::shared_ptr<luramas::il::arch::operand::operand> &operand, const std::int64_t U) {

            operand->type = kind;
            switch (kind) {
                  case luramas::il::arch::operand::operand_kind::value: {
                        operand->dis.val = U;
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::reg: {
                        operand->dis.reg = static_cast<const luramas_register>(U);
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::upvalue_kind: {
                        operand->dis.upvalue_kind = static_cast<const luramas::il::arch::operand::upvalue_kind>(U);
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::table_size: {
                        operand->dis.table_size = U;
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::kval:
                  case luramas::il::arch::operand::operand_kind::kval_string: {
                        if (U < 0 || static_cast<std::size_t>(U) > il->kval.size()) {
                              luramas::error::error("Invalid KVALUE Index");
                        }
                        operand->dis.kvalue_idx = (U && static_cast<std::size_t>(U) == il->kval.size()) ? static_cast<std::intptr_t>(il->kval.size() - 1u) : static_cast<std::intptr_t>(U);
                        const auto &kvalue = il->kval.at(operand->dis.kvalue_idx);
                        operand->k_value = kvalue->str();
                        operand->k_value_kind = kvalue->type;
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::closure_index: {
                        operand->dis.closure_idx = U;
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::upvalue: {
                        operand->dis.upvalue_idx = U;
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::closure: {
                        operand->dis.closure_id = U;
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::jmp: {
                        operand->dis.jmp = U;
                        operand->ref_addr = addr + U;
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::boolean: {
                        operand->dis.boolean = U;
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::integer: {
                        operand->dis.integer = static_cast<const double>(U);
                        break;
                  }
                  case luramas::il::arch::operand::operand_kind::none: {
                        break;
                  }
                  default: {
                        luramas::error::error("Unkown kind to emit.");
                  }
            }
            return;
      }

      /* Emits opcode to IL buffer. */
      template <luramas::il::arch::opcodes op>
      inline void emit_opcode(const std::shared_ptr<luramas::il::ilang> &il, const luramas_address addr, std::shared_ptr<luramas::il::disassembly> &buffer, const std::int64_t A = 0ll, const std::int64_t B = 0ll, const std::int64_t C = 0ll, const std::int64_t D = 0ll, const std::int64_t E = 0ll, const std::int64_t F = 0ll, const std::int64_t G = 0ll) {

            std::size_t idx = 0u;
            const std::vector<std::int64_t> enc_stack = {A, B, C, D, E, F, G};

            const auto opdata = luramas::il::arch::opkinds[std::uint8_t(op)];

            for (const auto &enc : opdata.kinds) {
                  auto ptr = std::make_shared<luramas::il::arch::operand::operand>();
                  emit_operand_kind(il, enc, addr, ptr, enc_stack[idx++]);
                  buffer->operands.emplace_back(ptr);
            }

            buffer->op = opdata.op;
            buffer->addr = addr;
            return;
      }

      template <luramas::il::arch::opcodes op>
      inline std::shared_ptr<luramas::il::disassembly> generate_opcode(const std::shared_ptr<luramas::il::ilang> &il, const luramas_address addr, const std::int64_t A = 0ll, const std::int64_t B = 0ll, const std::int64_t C = 0ll, const std::int64_t D = 0ll, const std::int64_t E = 0ll, const std::int64_t F = 0ll, const std::int64_t G = 0ll) {
            auto ptr = std::make_shared<luramas::il::disassembly>();
            emit_opcode<op>(il, addr, ptr, A, B, C, D, E, F, G);
            return ptr;
      }

} // namespace luramas::il::emitter