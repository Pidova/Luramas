#pragma once
#include "../common.hpp"
#include "../debug.hpp"
#include "../il/lexer/lexer.hpp"
#include "closures.hpp"
#include <algorithm>
#include <boost/pool/object_pool.hpp>
#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boostpp/flat_sets.hpp>
#include <inttypes.h>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <ostream>
#include <ranges>
#include <set>
#include <tuple>
#include <variant>
#include <vector>

namespace luramas::closures {

      enum class element : std::uint8_t {
            front,
            back
      };

      struct node : std::enable_shared_from_this<node> {

            luramas_address address = 0u;
            std::shared_ptr<il::lexer::lexeme> lex;

            /* Extra information for flag instructions. */
            struct flags {

                  struct poparg_flag {

                        /* Pops args from stack for OP_CCALL. */
                        boost::unordered_flat_set<luramas_register> call_pop;
                        bool pop_call_dest = false;
                  } poparg_flag;

            } flags;

            /* Extract all dest registers. (All registers that get overwritten, not only from "dest" operand) */
            luramas_registers extract_dest_regs() {

                  luramas_registers result;

                  switch (this->lex->disassembly->op) {

                        case luramas::il::arch::opcodes::OP_RETURN: {

                              const auto dest = this->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>().front()->dis.reg;
                              auto amt = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val;

                              if (amt) {
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
                                    amt = 1u;
                              }
                              for (auto a = 0u; a < amt; ++a) {
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
                                    if (std::find(result.begin(), result.end(), reg) == result.end()) {
                                          result.emplace_back(reg);
                                    }
                              }

                              if (std::find(result.begin(), result.end(), call) == result.end()) {
                                    if (this->lex->has_operand_kind<luramas::il::lexer::operand_kinds::dest>()) {
                                          result.emplace_back(call);
                                    }
                              } else if (this->lex->has_operand_kind<luramas::il::lexer::operand_kinds::reg>()) {
                                    result.erase(std::remove(result.begin(), result.end(), call));
                              }
                              break;
                        }
                        case luramas::il::arch::opcodes::OP_INITFORLOOPG: {
                              const auto start = this->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>().front()->dis.reg;
                              const auto amt = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val;

                              for (auto i = 0u; i < amt; ++i) {
                                    result.emplace_back(start + i + 3u);
                              }
                              break;
                        }
                        case luramas::il::arch::opcodes::OP_INITFORLOOPSPECIAL: {
                              const auto start = this->lex->operand_kind<luramas::il::lexer::operand_kinds::source>().back()->dis.reg;
                              for (auto i = 0u; i < this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().back()->dis.val; ++i) {
                                    result.emplace_back(start + i + 1u);
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

            /* Extract all source registers. (All registers that get read but not overwritten, not only from "source" operand) */
            luramas_registers extract_source_regs() {

                  luramas_registers result;

                  /* Skip loop */
                  if (this->lex->kind == luramas::il::lexer::inst_kinds::for_ || this->lex->kind == luramas::il::lexer::inst_kinds::special_flag) {
                        return result;
                  }

                  switch (this->lex->disassembly->op) {
                        case luramas::il::arch::opcodes::OP_RETURN: {

                              const auto dest = this->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>().front()->dis.reg;

                              if (const auto amt = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val; amt) {
                                    for (auto i = dest; i < (dest + amt); ++i) {
                                          result.emplace_back(i);
                                    }
                              }
                              return result;
                        }
                        case luramas::il::arch::opcodes::OP_COMMAND: {

                              if (const auto amt = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val; amt) {
                                    for (auto i = 0u; i < amt; ++i) {
                                          result.emplace_back(i);
                                    }
                              }
                              return result;
                        }
                        case luramas::il::arch::opcodes::OP_CCALL: {

                              auto args = this->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val;
                              const auto start = this->lex->disassembly->operands.front()->dis.reg;

                              if (this->lex->has_operand_kind<luramas::il::lexer::operand_kinds::reg>()) {
                                    result.emplace_back(this->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>().front()->dis.reg);
                              } else {
                                    result.emplace_back(this->lex->operand_kind<luramas::il::lexer::operand_kinds::dest>().front()->dis.reg);
                              }

                              for (auto i = 0; i < args; ++i) {

                                    /* Skip pop */
                                    const auto arg = i + start + 1u;
                                    if (!this->flags.poparg_flag.call_pop.contains(arg)) {
                                          result.emplace_back(arg);
                                    }
                              }

                              /* Skip this */
                              if (this->flags.poparg_flag.pop_call_dest) {
                                    result.erase(std::remove(result.begin(), result.end(), start));
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

                              for (auto i = 0u; i < vals; ++i) {
                                    result.emplace_back(start + i);
                              }
                              return result;
                        }
                        case luramas::il::arch::opcodes::OP_INITFORLOOPG: {

                              const auto start = this->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>().front()->dis.reg;
                              for (auto i = start; i <= start + 2u; ++i) {
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

            void dump(const char *const comment = nullptr) const {
                  std::printf("%s\n", this->lex->disassembly->disassemble(comment).c_str());
                  return;
            }
      };

      struct flags {
            luramas_flag fcarry_args = false;         /* Args are implicitly carried over to callee function? */
            luramas_flag fassociated_args = false;    /* Args are guaranteed to be in the registers of the callee?  */
            luramas_flag funknown_args = false;       /* Args need to be analyzed? */
            luramas_flag funknown_returns = false;    /* Returns need to be analyzed? */
            luramas_flag finclude_annotations = true; /* Includes annotations if avaliable? */
      };
      class closure {

          public:
            flags flags;

            std::shared_ptr<luramas::il::ilang> il = nullptr;
            std::shared_ptr<luramas::il::program_memory> shared_memory = nullptr;

            std::vector<std::shared_ptr<node>> nodes;
            std::vector<std::shared_ptr<closure>> closures;

            std::string str() const {

                  std::string result("");
                  for (const auto &node : this->nodes) {
                        result += node->lex->disassembly->disassemble() + "\n";
                  }
                  return result;
            }
            void dump() const {

                  std::printf("Main Closure:\n");
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

                        std::printf("Closure (%p):\n", on.get());
                        for (const auto &i : on->nodes) {
                              i->lex->disassembly->dump();
                        }
                        closures.insert(closures.end(), on->closures.begin(), on->closures.end());
                        seen.insert(on);
                  }
                  return;
            }
            void extract(const boost::unordered_flat_map<luramas_register, std::string> &reg = boost::unordered_flat_map<luramas_register, std::string>()) const {

                  for (const auto &i : this->nodes) {
                        if (il::arch::is_op::psuedo(i->lex->disassembly->op)) {
                              continue;
                        }
                        std::string mnemonic = il::disassembler::mnemonic_string(i->lex->disassembly->op);
                        luramas_str_uppercase(mnemonic);

                        std::string operands("");
                        const auto op_count = i->lex->disassembly->operands.size();
                        for (auto j = 0u; j < op_count; ++j) {
                              const auto oper = i->lex->disassembly->operands[j];
                              if (const auto it = reg.find(oper->dis.reg); it != reg.end() && oper->type == luramas::il::arch::operand::operand_kind::reg) {
                                    operands += it->second;
                              } else {
                                    operands += luramas::il::disassembler::operand_string(oper);
                              }
                              operands += ((j + 1u) == op_count) ? "" : ", ";
                        }

                        std::printf("luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_%s>(il, pc, %s);\n", mnemonic.c_str(), operands.c_str());
                  }
                  return;
            }
            void set_flags();
      };

      std::shared_ptr<closure> gen_closure(std::shared_ptr<luramas::il::ilang> &il_data);

} // namespace luramas::closures