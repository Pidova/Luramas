#include "../il.hpp"

void luramas::il::ilang::resolve_addresses() {

      luramas_address addr = 0u;
      for (const auto &i : this->dis) {
            i->addr = addr++;
      }
      return;
}

void luramas::il::ilang::resolve_jumps() {

      for (const auto &i : this->dis) {
            for (const auto &operand : i->operands) {
                  if (operand->type == il::arch::operand::operand_kind::jmp) {
                        operand->dis.jmp = i->ref->addr - i->addr;
                        operand->ref_addr = i->ref->addr;
                  }
            }
      }
      return;
}

void luramas::il::ilang::resolve_xrefs() {

      for (auto &i : this->dis) {
            if (i->ref) {
                  i->ref->xrefs.clear();
                  i->ref->xrefs.emplace_back(i);
            }
      }
      return;
}
