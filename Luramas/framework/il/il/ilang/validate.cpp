#include "../il.hpp"

namespace luramas::il {

      [[noreturn]] void throw_error(ilang *il, const errors::error &valid) {
            luramas::error::error(std::format("Uncommitted disassembly contains an error: {}, On address: {}\n", valid.h.what, std::to_string(valid.w->addr)));
      }

      void ilang::validate(const errors::error &valid) {
            if (!this->dis.empty() && valid) {
                  throw_error(this, valid);
            }
            return;
      }

      errors::error ilang::validate_operands() {

            for (const auto &i : this->dis) {

                  for (const auto &operand : i->operands) {

                        /* reference */
                        if (operand->type == arch::operand::operand_kind::jmp && !i->ref) {
                              return errors::error(i, errors::make<errors::kinds::nullptr_jump_ref>());
                        }
                  }
            }
            return errors::error();
      }
} // namespace luramas::il
