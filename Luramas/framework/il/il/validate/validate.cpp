#include "../il.hpp"

[[noreturn]] void throw_error(luramas::il::ilang *il, const luramas::il::commit_error &valid) {
      luramas::error::error(std::format("Uncommitted disassembly contains an error: {}, On address: {}\n", valid.error, std::to_string(valid.il->addr)));
}

void luramas::il::ilang::validate(const luramas::il::commit_error &valid) {
      if (!this->dis.empty() && valid.is_error) {
            throw_error(this, valid);
      }
      return;
}

luramas::il::commit_error luramas::il::ilang::validate_operands() {

      luramas::il::commit_error result;
      for (const auto &i : this->dis) {

            for (const auto &operand : i->operands) {

                  /* reference */
                  if (operand->type == il::arch::operand::operand_kind::jmp && i->ref == nullptr /* Jmp and ref is nullptr. */) {
                        result.commit(i, "Nullptr reference for jump.");
                  }
            }
      }
      return result;
}
