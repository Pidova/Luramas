#pragma once
#include "../../../common.hpp"
#include "../tools/disassembler.hpp"

namespace luramas::il {

      /* IL disassembly */
      struct disassembly {

            luramas_address addr = 0u;                                                  /* Address  */
            arch::opcodes op = arch::opcodes::OP_NOP;                                   /* Opcode */
            arch::data::bin_kinds bin_kind = arch::data::bin_kinds::nothing;            /* Binary kind */
            std::vector<std::shared_ptr<luramas::il::arch::operand::operand>> operands; /* Operands */
            std::vector<std::shared_ptr<disassembly>> xrefs;                            /* Cross references */
            std::shared_ptr<disassembly> ref = nullptr;                                 /* Reference to the disassembly which one of the operands reference i.e. jump/memory reference. (Once referenced is linked all jumps locs will change to the addr relatively, DOMINANT TO JUMP)  */

            /* Returns disassembly of IL instruction. */
            template <bool include_hint = false /* Includes mnemonic hint */,
                bool case_mnemonic = true /* Uppercase mnemonic? */,
                bool include_address = true /* Includes address */,
                bool include_mnemonic = true /* Includes mnemonic */,
                bool include_operands = true /* Includes mnemonic */>
            std::string disassemble(const char *const comment = NULL) {

                  std::string result = "";

                  /* Address */
                  if constexpr (include_address) {
                        result += std::to_string(this->addr) + " ";
                  }

                  /* Mnemonic */
                  if constexpr (include_mnemonic) {
                        std::string mnemonic = luramas::il::disassembler::mnemonic_string(this->op); /* Mnemonic string */

                        /* Uppercase? */
                        if constexpr (case_mnemonic) {
                              std::ranges::transform(mnemonic, mnemonic.begin(), [](const char c) { return std::toupper(c); });
                        }

                        /* Append */
                        result += mnemonic + " ";
                  }

                  /* Operands */
                  if constexpr (include_operands) {
                        const auto op_count = this->operands.size();
                        for (auto i = 0u; i < op_count; ++i) {
                              result += luramas::il::disassembler::operand_string(this->operands[i]);
                              result += ((i + 1u) == op_count) ? " " : ", ";
                        }
                  }

                  /* Comment */
                  if (comment != NULL) {
                        result += std::string("; ") + comment;
                  }

                  /* Hint */
                  if constexpr (include_hint) {
                        result += ((comment == NULL) ? std::string("; ") : std::string("  ")) + luramas::il::disassembler::mnemonic_hint_string(this->op);
                  }

                  return result;
            }

#if defined(_WIN32) || defined(_WIN64)

#include "../../color.hpp"

            /* Prints disassembly in color of IL instruction. */
            template <bool include_hint = false /* Includes mnemonic hint */,
                bool case_mnemonic = true /* Uppercase mnemonic? */,
                bool include_address = true /* Includes address */,
                bool include_mnemonic = true /* Includes mnemonic */,
                bool include_operands = true /* Includes mnemonic */>
            void dump(const char *const comment = NULL) {

                  /* Address */
                  if constexpr (include_address) {
                        luramas_color_print(luramas_color_fontcolor_green, luramas_color_background_black, std::string(std::to_string(this->addr) + " ").c_str());
                  }

                  /* Mnemonic */
                  if constexpr (include_mnemonic) {

                        std::string mnemonic = luramas::il::disassembler::mnemonic_string(this->op);
                        if (case_mnemonic) {
                              std::ranges::transform(mnemonic, mnemonic.begin(), [](const char c) { return std::toupper(c); });
                        }

                        luramas_color_print(luramas_color_fontcolor_brightblue, luramas_color_background_black, std::string(mnemonic + " ").c_str());
                  }

                  /* Operands */
                  if constexpr (include_operands) {
                        const auto op_count = this->operands.size();
                        for (auto i = 0u; i < op_count; ++i) {
                              luramas_color_print(luramas_color_fontcolor_yellow, luramas_color_background_black, luramas::il::disassembler::operand_string(this->operands[i]).c_str());
                              luramas_color_print(luramas_color_fontcolor_nothing, luramas_color_background_nothing, ((i + 1u) == op_count) ? " " : ", ");
                        }
                  }

                  /* Comment */
                  if (comment != NULL) {
                        luramas_color_print(luramas_color_fontcolor_magenta, luramas_color_background_black, std::string(std::string("; ") + comment).c_str());
                  }

                  /* Hint */
                  if constexpr (include_hint) {
                        luramas_color_print(luramas_color_fontcolor_magenta, luramas_color_background_black, std::string(((comment == NULL) ? std::string("; ") : std::string("  ")) + luramas::il::disassembler::mnemonic_hint_string(this->op)).c_str());
                  }

                  /* Line end */
                  if constexpr (include_address || include_mnemonic || include_operands || include_hint || comment != NULL) {
                        luramas_color_print(luramas_color_fontcolor_nothing, luramas_color_background_nothing, "\n");
                  }
                  return;
            }
#endif

            /* Clears struct */
            void clear() {
                  *this = disassembly();
                  return;
            }
      };

      namespace errors {

            /* Kinds or errors */
            enum class kinds : std::uint8_t {
                  none,            /* No error */
                  nullptr_jump_ref /* Referenced jump contains a nullptr */
            };

            /* Error kind -> String */
            constexpr frozen::unordered_map<kinds, const char *const, 2u> strs = {
                {kinds::none, "No error"},
                {kinds::nullptr_jump_ref, "Referenced jump contains a nullptr"},
            };

            /* Error handler for luramas */
            using handler = error::handler<kinds>;

            /* Makes IL error */
            template <kinds k>
            constexpr handler make() {
                  return handler(k, strs.at(k));
            }

            /* Error linked to disassembly */
            using error = luramas::error::linked<std::shared_ptr<disassembly>, errors::kinds>;

      } // namespace errors
} // namespace luramas::il