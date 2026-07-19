#include "transformers.hpp"

void luramas::il::transformers::kinds(const std::shared_ptr<luramas::il::ilang> &il) {

      for (auto &i : il->dis) {
            switch (i->op) {
                  case arch::opcodes::OP_ADD:
                  case arch::opcodes::OP_ADDK:
                  case arch::opcodes::OP_ADDN: {
                        i->bin_kind = arch::data::bin_kinds::add_;
                        break;
                  }
                  case arch::opcodes::OP_SUB:
                  case arch::opcodes::OP_SUBK:
                  case arch::opcodes::OP_SUBN: {
                        i->bin_kind = arch::data::bin_kinds::sub_;
                        break;
                  }
                  case arch::opcodes::OP_MUL:
                  case arch::opcodes::OP_MULK:
                  case arch::opcodes::OP_MULN: {
                        i->bin_kind = arch::data::bin_kinds::mul_;
                        break;
                  }
                  case arch::opcodes::OP_DIV:
                  case arch::opcodes::OP_DIVK:
                  case arch::opcodes::OP_DIVN: {
                        i->bin_kind = arch::data::bin_kinds::div_;
                        break;
                  }
                  case arch::opcodes::OP_MOD:
                  case arch::opcodes::OP_MODK:
                  case arch::opcodes::OP_MODN: {
                        i->bin_kind = arch::data::bin_kinds::mod_;
                        break;
                  }
                  case arch::opcodes::OP_POW:
                  case arch::opcodes::OP_POWK:
                  case arch::opcodes::OP_POWN: {
                        i->bin_kind = arch::data::bin_kinds::pow_;
                        break;
                  }
                  case arch::opcodes::OP_AND:
                  case arch::opcodes::OP_ANDK:
                  case arch::opcodes::OP_ANDN: {
                        i->bin_kind = arch::data::bin_kinds::and_;
                        break;
                  }
                  case arch::opcodes::OP_XOR:
                  case arch::opcodes::OP_XORK:
                  case arch::opcodes::OP_XORN: {
                        i->bin_kind = arch::data::bin_kinds::xor_;
                        break;
                  }
                  case arch::opcodes::OP_SHL:
                  case arch::opcodes::OP_SHLK:
                  case arch::opcodes::OP_SHLN: {
                        i->bin_kind = arch::data::bin_kinds::shl_;
                        break;
                  }
                  case arch::opcodes::OP_SHR:
                  case arch::opcodes::OP_SHRK:
                  case arch::opcodes::OP_SHRN: {
                        i->bin_kind = arch::data::bin_kinds::shr_;
                        break;
                  }
                  case arch::opcodes::OP_IDIV:
                  case arch::opcodes::OP_IDIVK:
                  case arch::opcodes::OP_IDIVN: {
                        i->bin_kind = arch::data::bin_kinds::idiv_;
                        break;
                  }
                  case arch::opcodes::OP_OR:
                  case arch::opcodes::OP_ORK:
                  case arch::opcodes::OP_ORN: {
                        i->bin_kind = arch::data::bin_kinds::or_;
                        break;
                  }
                  case arch::opcodes::OP_LEN: {
                        i->bin_kind = arch::data::bin_kinds::len_;
                        break;
                  }
                  case arch::opcodes::OP_NOT: {
                        i->bin_kind = arch::data::bin_kinds::not_;
                        break;
                  }
                  case arch::opcodes::OP_MINUS: {
                        i->bin_kind = arch::data::bin_kinds::minus_;
                        break;
                  }
                  case arch::opcodes::OP_BITNOT: {
                        i->bin_kind = arch::data::bin_kinds::bitnot_;
                        break;
                  }
                  case arch::opcodes::OP_PLUS: {
                        i->bin_kind = arch::data::bin_kinds::plus_;
                        break;
                  }
                  case arch::opcodes::OP_REF: {
                        i->bin_kind = arch::data::bin_kinds::ref_;
                        break;
                  }
                  case arch::opcodes::OP_JUMPIFEQUAL:
                  case arch::opcodes::OP_SETIFEQUAL: {
                        i->bin_kind = arch::data::bin_kinds::eq_;
                        break;
                  }
                  case arch::opcodes::OP_JUMPIFNOTEQUAL:
                  case arch::opcodes::OP_SETIFNOTEQUAL: {
                        i->bin_kind = arch::data::bin_kinds::ne_;
                        break;
                  }
                  case arch::opcodes::OP_JUMPIFNOT:
                  case arch::opcodes::OP_SETIFNOT: {
                        i->bin_kind = arch::data::bin_kinds::nt_;
                        break;
                  }
                  case arch::opcodes::OP_JUMPIF:
                  case arch::opcodes::OP_SETIF: {
                        i->bin_kind = arch::data::bin_kinds::et_;
                        break;
                  }
                  case arch::opcodes::OP_JUMPIFLESS:
                  case arch::opcodes::OP_SETIFLESS: {
                        i->bin_kind = arch::data::bin_kinds::lt_;
                        break;
                  }
                  case arch::opcodes::OP_JUMPIFLESSEQUAL:
                  case arch::opcodes::OP_SETIFLESSEQUAL: {
                        i->bin_kind = arch::data::bin_kinds::lte_;
                        break;
                  }
                  case arch::opcodes::OP_JUMPIFGREATER:
                  case arch::opcodes::OP_SETIFGREATER: {
                        i->bin_kind = arch::data::bin_kinds::gt_;
                        break;
                  }
                  case arch::opcodes::OP_JUMPIFGREATEREQUAL:
                  case arch::opcodes::OP_SETIFGREATEREQUAL: {
                        i->bin_kind = arch::data::bin_kinds::gte_;
                        break;
                  }
                  default: {
                        break;
                  }
            }
      }
      return;
}
