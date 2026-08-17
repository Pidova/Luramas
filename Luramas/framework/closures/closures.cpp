#include "closures.hpp"

#include <algorithm>

#include <print>

inline static void set_nodes(std::shared_ptr<luramas::closures::closure> &closure) {

      for (const auto &i : closure->il->dis) {
            auto node = std::make_shared<luramas::closures::node>();
            node->address = i->addr;
            node->lex = luramas::il::lexer::lexer(i);
            closure->nodes.emplace_back(node);
      }
      return;
}

namespace luramas::closures {

      void node::error(const std::string &what) const {
            luramas::error::error("Error on " + this->lex->disassembly->disassemble() + " Error " + what);
      }
      luramas_registers node::extract_dest_regs() const {

            luramas_registers result;

            switch (this->lex->disassembly->op) {

                  case luramas::il::arch::opcodes::OP_RETURN: {

                        /* Get kinds */
                        const auto regs = this->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>();
                        const auto vals = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>();
                        if (regs.empty() || vals.empty()) {
                              return result;
                        }

                        const auto dest = regs.front()->dis.reg;
                        if (auto amt = static_cast<luramas_register>(vals.front()->dis.val); amt) {
                              for (auto a = dest; a < (dest + amt); ++a) {
                                    result.emplace_back(a);
                              }
                        }
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_GETVARIADIC: {

                        const auto dest = this->lex->operand_kind<luramas::il::lexer::operand_kinds::dest>().front()->dis.reg;
                        auto amt = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val;

                        if (amt == 0) {
                              amt = 1U;
                        }
                        for (auto a = 0U; a < amt; ++a) {
                              result.emplace_back(dest + a);
                        }
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_CCALL: {

                        auto call_result = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().back()->dis.val;
                        const auto call = this->lex->disassembly->operands.front()->dis.reg;

                        /* Append to dest. (Fill for multiple result) */
                        for (auto i = 0; i < call_result; ++i) {

                              const auto reg = call + i;
                              if (std::ranges::find(result, reg) == result.end()) {
                                    result.emplace_back(reg);
                              }
                        }

                        if (std::ranges::find(result, call) == result.end()) {
                              if (this->lex->has_operand_kind<luramas::il::lexer::operand_kinds::dest>()) {
                                    result.emplace_back(call);
                              }
                        } else if (this->lex->has_operand_kind<luramas::il::lexer::operand_kinds::reg>()) {
                              result.erase(std::ranges::remove(result, call).begin(), result.end());
                        }
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_INITFORLOOPG: {
                        const auto start = this->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>().front()->dis.reg;
                        const auto amt = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val;

                        for (auto i = 0U; i < amt; ++i) {
                              result.emplace_back(start + i + 3U);
                        }
                        break;
                  }
                  case luramas::il::arch::opcodes::OP_INITFORLOOPSPECIAL: {
                        const auto start = this->lex->operand_kind<luramas::il::lexer::operand_kinds::source>().back()->dis.reg;
                        for (auto i = 0U; i < this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().back()->dis.val; ++i) {
                              result.emplace_back(start + i + 1U);
                        }
                        break;
                  }
                  default: {

                        /* Append dest */
                        if (this->lex->has_operand_kind<luramas::il::lexer::operand_kinds::dest>()) {
                              result.emplace_back(this->lex->operand_kind<luramas::il::lexer::operand_kinds::dest>().front()->dis.reg);
                        }
                        break;
                  }
            }
            return result;
      }
      luramas_registers node::extract_source_regs() const {

            luramas_registers result;

            /* Skip loop */
            if (this->lex->kind == luramas::il::lexer::inst_kinds::for_ || this->lex->kind == luramas::il::lexer::inst_kinds::special_flag) {
                  return result;
            }

            switch (this->lex->disassembly->op) {
                  case luramas::il::arch::opcodes::OP_RETURN: {

                        /* Get kinds */
                        const auto regs = this->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>();
                        const auto vals = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>();
                        if (regs.empty() || vals.empty()) {
                              return result;
                        }

                        /* Get results */
                        const auto dest = regs.front()->dis.reg;
                        if (const auto amt = vals.front()->dis.val; amt) {
                              for (auto i = dest; i < (dest + amt); ++i) {
                                    result.emplace_back(i);
                              }
                        }
                        return result;
                  }
                  case luramas::il::arch::opcodes::OP_COMMAND: {

                        if (const auto amt = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val; amt) {
                              for (auto i = 0U; i < amt; ++i) {
                                    result.emplace_back(i);
                              }
                        }
                        return result;
                  }
                  case luramas::il::arch::opcodes::OP_CCALL: {

                        auto args = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val;
                        const auto start = this->lex->disassembly->operands.front()->dis.reg;

                        /* Call loc */
                        if (this->lex->has_operand_kind<luramas::il::lexer::operand_kinds::reg>()) {
                              result.emplace_back(this->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>().front()->dis.reg);
                        } else {
                              result.emplace_back(this->lex->operand_kind<luramas::il::lexer::operand_kinds::dest>().front()->dis.reg);
                        }

                        /* Go through arg count */
                        for (auto i = 0; i < args; ++i) {

                              /* Skip pop */
                              const auto arg = i + start + 1U;
                              if (!this->flags.poparg_flag.call_pop.contains(arg)) {
                                    result.emplace_back(arg);
                              }
                        }

                        /* Skip this */
                        if (this->flags.poparg_flag.pop_call_dest) {
                              result.erase(std::ranges::remove(result, start).begin(), result.end());
                        }
                        return result;
                  }
                  case luramas::il::arch::opcodes::OP_CONCAT: {

                        const auto start = this->lex->operand_kind<luramas::il::lexer::operand_kinds::source>().front()->dis.reg;
                        const auto vals = this->lex->operand_kind<luramas::il::lexer::operand_kinds::source>().back()->dis.reg;

                        for (auto i = start; i <= vals; ++i) {
                              result.emplace_back(i);
                        }
                        return result;
                  }
                  case luramas::il::arch::opcodes::OP_SETLIST: {

                        const auto start = this->lex->operand_kind<luramas::il::lexer::operand_kinds::source>().front()->dis.reg;
                        const auto vals = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val;

                        for (auto i = 0U; i < vals; ++i) {
                              result.emplace_back(start + i);
                        }
                        return result;
                  }
                  case luramas::il::arch::opcodes::OP_INITFORLOOPG: {

                        const auto start = this->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>().front()->dis.reg;
                        for (auto i = start; i <= start + 2U; ++i) {
                              result.emplace_back(i);
                        }
                        return result;
                  }
                  case luramas::il::arch::opcodes::OP_INITFORLOOPSPECIAL: {
                        result.emplace_back(this->lex->operand_kind<luramas::il::lexer::operand_kinds::source>().front()->dis.reg);
                        return result;
                  }
                  default: {
                        break;
                  }
            }

            /* Append source */
            if (this->lex->has_operand_kind<luramas::il::lexer::operand_kinds::source>()) {
                  for (const auto &operand : this->lex->operand_kind<luramas::il::lexer::operand_kinds::source>()) {
                        result.emplace_back(operand->dis.reg);
                  }
            }

            /* Append reg */
            if (this->lex->has_operand_kind<luramas::il::lexer::operand_kinds::reg>()) {
                  for (const auto &operand : this->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>()) {
                        result.emplace_back(operand->dis.reg);
                  }
            }

            /* Append compare */
            if (this->lex->has_operand_kind<luramas::il::lexer::operand_kinds::compare>()) {
                  for (const auto &operand : this->lex->operand_kind<luramas::il::lexer::operand_kinds::compare>()) {
                        result.emplace_back(operand->dis.reg);
                  }
            }

            /* Append table reg */
            if (this->lex->has_operand_kind<luramas::il::lexer::operand_kinds::table_reg>()) {
                  for (const auto &operand : this->lex->operand_kind<luramas::il::lexer::operand_kinds::table_reg>()) {
                        result.emplace_back(operand->dis.reg);
                  }
            }
            return result;
      }
      void node::dump(const char *const comment) const {
            std::println("{}", this->lex->disassembly->disassemble(comment));
            return;
      }

      std::string closure::str() const {

            std::string result;
            for (const auto &node : this->nodes) {
                  result += node->lex->disassembly->disassemble() + "\n";
            }
            return result;
      }
      void closure::dump() const {

            std::println("Main Closure:");
            for (const auto &i : this->nodes) {
                  i->lex->disassembly->dump();
            }

            boost::unordered_flat_set<std::shared_ptr<closure>> seen;
            auto closures = this->closures;
            while (!closures.empty()) {

                  const auto on = closures.back();
                  closures.pop_back();
                  if (seen.contains(on)) {
                        continue;
                  }

                  std::println("Closure ({}):", static_cast<const void *>(on.get()));
                  for (const auto &i : on->nodes) {
                        i->lex->disassembly->dump();
                  }
                  closures.insert(closures.end(), on->closures.begin(), on->closures.end());
                  seen.insert(on);
            }
            return;
      }
      void closure::extract(const boost::unordered_flat_map<luramas_register, std::string> &reg) const {

            for (const auto &i : this->nodes) {
                  if (il::arch::is_op::psuedo(i->lex->disassembly->op)) {
                        continue;
                  }
                  std::string mnemonic = il::disassembler::mnemonic_string(i->lex->disassembly->op);
                  luramas_str_uppercase(mnemonic);

                  std::string operands;
                  const auto op_count = i->lex->disassembly->operands.size();
                  for (auto j = 0U; j < op_count; ++j) {
                        const auto oper = i->lex->disassembly->operands[j];
                        if (const auto it = reg.find(oper->dis.reg); it != reg.end() && oper->type == luramas::il::arch::operand::operand_kind::reg) {
                              operands += it->second;
                        } else {
                              operands += luramas::il::disassembler::operand_string(oper);
                        }
                        operands += ((j + 1U) == op_count) ? "" : ", ";
                  }

                  std::println("luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_{}>(il, pc, {});", mnemonic, operands);
            }
            return;
      }
      void closure::set_flags() {

            boost::unordered_flat_set<luramas_register> append_regs;
            for (auto &i : this->nodes) {

                  switch (i->lex->disassembly->op) {

                        case luramas::il::arch::opcodes::OP_POPARG: {
                              append_regs.insert(i->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>().front()->dis.reg);
                              break;
                        }
                        case luramas::il::arch::opcodes::OP_CCALL: {
                              i->flags.poparg_flag.call_pop = append_regs;
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

      std::shared_ptr<closure> gen_closure(std::shared_ptr<luramas::il::ilang> &il_data) {

            auto result = std::make_shared<closure>();
            std::deque<std::shared_ptr<closure>> closures = {result};

            /* Set closure and closure. */
            result->il = il_data;
            result->nodes.reserve(result->il->dis.size());
            set_nodes(result);

            do {
                  auto current_closure = closures.back();
                  closures.pop_back();

                  for (const auto &i : current_closure->il->closures) {

                        auto child = std::make_shared<closure>();
                        child->il = i;
                        child->nodes.reserve(child->il->dis.size());
                        set_nodes(child);

                        current_closure->closures.emplace_back(child);
                        closures.emplace_back(child);
                  }
                  current_closure->set_flags();
            } while (!closures.empty());
            return result;
      }
} // namespace luramas::closures