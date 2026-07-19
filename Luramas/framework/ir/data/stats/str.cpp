#include "../../ir.hpp"

std::string ir_stat::str(const std::string &stat_prefix) const {

      std::string result(stat_prefix);
      if (!this->annotation.empty()) {
            result += "-- " + this->annotation + "\n" + stat_prefix;
      }
      if (this->flags.fsynthetic) {
            result += "[SYNTHETIC] ";
      }
      if (this->flags.fdefine) {
            result += "local ";
      }
      switch (this->k) {
            case keywords::label: {
                  result = "::label_" + std::to_string(this->label) + "::";
                  break;
            }
            case keywords::repeat: {
                  result += "repeat";
                  break;
            }
            case keywords::end: {
                  result += "end";
                  break;
            }
            case keywords::break_: {
                  result += "break";
                  break;
            }
            case keywords::continue_: {
                  result += "continue";
                  break;
            }
            case keywords::goto_label: {
                  result = "goto " + std::to_string(this->jlabel);
                  break;
            }
            case keywords::switch_: {
                  result += "switch (" + this->l->str("", stat_prefix) + ") then";
                  break;
            }
            case keywords::switch_case: {
                  result += "case " + this->l->str("", stat_prefix) + " then";
                  break;
            }
            case keywords::switch_default: {
                  result += "default then";
                  break;
            }
            case keywords::table_assign: {
                  result += this->l->str("", stat_prefix) + " = " + this->r->str("", stat_prefix);
                  break;
            }
            case keywords::definition: {
                  result += "DEFINITION([ARGS]{";
                  for (auto it = this->args.begin(); it != this->args.end(); ++it) {
                        result += it->second->str("", stat_prefix);
                        if (std::next(it) != this->args.end()) {
                              result += ", ";
                        }
                  }
                  result += "}, [UPVALUES]{";
                  for (auto idx = 0u; idx < this->upvalues.size(); ++idx) {
                        result += this->upvalues[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->upvalues.size()) {
                              result += ", ";
                        }
                  }
                  result += "}, [FLAGS]{";
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        result += this->members[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->members.size()) {
                              result += ", ";
                        }
                  }
                  result += "}, [CASTS]{";
                  for (auto idx = 0u; idx < this->meta.size(); ++idx) {
                        const auto p = this->meta[idx];
                        result += p ? p->str("", stat_prefix) : "nil";
                        if ((idx + 1u) < this->meta.size()) {
                              result += ", ";
                        }
                  }
                  result += "}, [RESULTS]{";
                  for (auto idx = 0u; idx < this->smembers.size(); ++idx) {
                        const auto p = this->smembers[idx];
                        result += p ? p->str("", stat_prefix) : "nil";
                        if ((idx + 1u) < this->smembers.size()) {
                              result += ", ";
                        }
                  }
                  result += "})";
                  break;
            }
            case keywords::table_setlist: {
                  result += "SETLIST([" + this->l->str("", stat_prefix) + ", " + std::to_string(this->table_index) + "], {";
                  for (auto idx = 0u; idx < this->tmembers.size(); ++idx) {
                        result += this->tmembers[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->tmembers.size()) {
                              result += ", ";
                        }
                  }
                  result += "})";
                  break;
            }
            case keywords::stack_push: {
                  result += "SPUSH([" + this->v->str("", stat_prefix) + "], {";
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        result += this->members[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->members.size()) {
                              result += ", ";
                        }
                  }
                  result += "})";
                  break;
            }
            case keywords::stack_pop: {
                  result += "SPOP([" + this->v->str("", stat_prefix) + "], {";
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        result += this->members[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->members.size()) {
                              result += ", ";
                        }
                  }
                  result += "})";
                  break;
            }
            case keywords::forloop_numeric: {
                  result += "for " + this->lba->str("", stat_prefix) + " = " + this->l->str("", stat_prefix) + ", " + this->r->str("", stat_prefix) + ", " + this->v->str("", stat_prefix) + " do";
                  break;
            }
            case keywords::forloop_generic: {
                  result += "for ";
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        result += this->members[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->members.size()) {
                              result += ", ";
                        }
                  }
                  result += " in ";
                  for (auto idx = 0u; idx < this->smembers.size(); ++idx) {
                        result += this->smembers[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->smembers.size()) {
                              result += ", ";
                        }
                  }
                  result += " do";
                  break;
            }
            case keywords::call: {
                  if (this->flags.fexternal_page_goto) {
                        result += "[PEX]";
                  }
                  if (!result.empty()) {
                        result += " ";
                  }
                  result += this->l->str("", stat_prefix) + "(";
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        result += this->members[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->members.size()) {
                              result += ", ";
                        }
                  }
                  result += ")";
                  break;
            }
            case keywords::retn: {
                  if (this->l) {
                        result += "[RT=" + this->l->str() + "] ";
                  }
                  result += "return ";
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        result += this->members[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->members.size()) {
                              result += ", ";
                        }
                  }
                  result += "; ";
                  for (auto idx = 0u; idx < this->smembers.size(); ++idx) {
                        result += this->smembers[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->smembers.size()) {
                              result += ", ";
                        }
                  }
                  break;
            }
            case keywords::assignment: {
                  if (this->l) {
                        result += this->l->str("", stat_prefix);
                  } else {
                        for (auto idx = 0u; idx < this->members.size(); ++idx) {
                              result += this->members[idx]->str("", stat_prefix);
                              if ((idx + 1u) < this->members.size()) {
                                    result += ", ";
                              }
                        }
                  }
                  result += " = " + this->r->str("", stat_prefix);
                  break;
            }
            case keywords::condition: {
                  switch (this->c) {
                        case condition_kind::else_: {
                              result += "else ";
                              break;
                        }
                        case condition_kind::elseif_: {
                              result += "elseif ";
                              break;
                        }
                        case condition_kind::if_:
                        default: {
                              result += "if ";
                              break;
                        }
                  }
                  if (this->c != condition_kind::else_) {
                        result += " (";
                        if (this->b == luramas::il::arch::data::bin_kinds::nt_) {
                              result += "not ";
                        }
                        result += this->l->str("", stat_prefix);
                        if (this->r) {
                              result += std::string(" ") + luramas::il::arch::data::bin_kindstr(this->b) + " " + this->r->str("", stat_prefix);
                        }
                        result += ") then";
                  }
                  break;
            }
            case keywords::condition_goto: {
                  result += "if (";
                  if (this->b == luramas::il::arch::data::bin_kinds::nt_) {
                        result += "not ";
                  }
                  result += this->l->str("", stat_prefix);
                  if (this->r) {
                        result += std::string(" ") + luramas::il::arch::data::bin_kindstr(this->b) + " " + this->r->str("", stat_prefix);
                  }
                  result += ") then goto label_" + std::to_string(this->jlabel) + " end";
                  break;
            }
            case keywords::while_: {
                  result += "while (" + this->l->str("", stat_prefix);
                  if (this->r) {
                        result += std::string(" ") + luramas::il::arch::data::bin_kindstr(this->b) + " " + this->r->str("", stat_prefix);
                  }
                  result += ") do";
                  break;
            }
            case keywords::until: {
                  result += "until (" + this->l->str("", stat_prefix);
                  if (this->r != nullptr) {
                        result += std::string(" ") + luramas::il::arch::data::bin_kindstr(this->b) + " " + this->r->str("", stat_prefix);
                  }
                  result += ")";
                  break;
            }
            case keywords::memoryset: {
                  result += "memset<" + this->str_type() + ">(" + this->l->str("", stat_prefix) + (this->v ? " + " + this->v->str("", stat_prefix) : "") + ") = " + this->r->str("", stat_prefix);
                  break;
            }
            case keywords::bitwrite: {
                  result += "bitwrite(" + this->l->str("", stat_prefix) + ", " + this->r->str("", stat_prefix) + ", [" + this->v->str("", stat_prefix) + ", " + this->lba->str("", stat_prefix) + "])";
                  break;
            }
            case keywords::set_flag: {
                  result += "setflag(" + this->l->str("", stat_prefix) + ", " + this->r->str("", stat_prefix) + ")";
                  break;
            }
            case keywords::page_function_closure: {
                  result += "function PAGEFUNC[";
                  result += this->r->str("", stat_prefix);
                  result += "](";
                  // retn += "(";
                  // for (const auto &c : this->captures)
                  //       retn += c->str() + "  ";
                  // retn += ")";
                  const auto def = this->v->closure.front();
                  for (auto it = def->args.begin(); it != def->args.end(); ++it) {
                        result += (*it).second->str("", stat_prefix);
                        if (std::next(it) != def->args.end()) {
                              result += ", ";
                        } else if (def->flags.fvariadic_def) {
                              result += ", ...";
                        }
                  }
                  if (def->args.empty() && def->flags.fvariadic_def) {
                        result += "...";
                  }
                  result += ")\n";
                  for (const auto &s : this->v->closure) {
                        if (const auto &str = s->str(stat_prefix); !str.empty()) {
                              result += str + "\n";
                        }
                  }
                  result += "end";
                  break;
            }
            case keywords::page_function_start: {
                  result += "page_function_start (" + this->r->str("", stat_prefix) + ") {";
                  break;
            }
            case keywords::page_function_end: {
                  result += "} page_function_end(" + this->r->str("", stat_prefix) + ")";
                  break;
            }
            case keywords::page_function_goto: {
                  if (this->flags.fexternal_page_goto) {
                        result += "[EXTERNAL] ";
                  }
                  std::string t("");
                  switch (this->pfk) {
                        case page_function_goto_kind::call: {
                              t = "page_function_call";
                              break;
                        }
                        default: {
                              t = "page_function_goto";
                              break;
                        }
                  }
                  result += t + "<" + this->r->str("", stat_prefix) + ">(";
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        result += this->members[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->members.size()) {
                              result += ", ";
                        }
                  }
                  result += ")";
                  if (this->v) {
                        result += " -> " + this->v->str("", stat_prefix);
                  }
                  if (this->l) {
                        result += "[" + this->l->str("", stat_prefix);
                  }
                  if (this->lba) {
                        result += ", " + this->lba->str("", stat_prefix) + "]";
                  }
                  break;
            }
            case keywords::page_function_pass: {
                  result += "page_function_pass(";
                  for (auto it = this->members.begin(); it != this->members.end(); ++it) {
                        result += (*it)->str("", stat_prefix);
                        if (std::next(it) != this->members.end()) {
                              result += ", ";
                        }
                  }
                  result += ")";
                  break;
            }
            case keywords::create_stack: {
                  result += "create_stack(" + this->l->str("", stat_prefix) + ")";
                  break;
            }
            case keywords::globals_preset: {
                  result += "globals_preset(";
                  for (auto it = this->meta.begin(); it != this->meta.end(); ++it) {
                        result += (*it)->str("", stat_prefix);
                        if (std::next(it) != this->meta.end()) {
                              result += "; ";
                        }
                  }
                  result += ")";
                  break;
            }
            case keywords::metadata: {
                  result += "metadata(" + this->r->str("", stat_prefix) + ", " + this->v->str("", stat_prefix) + ")";
                  break;
            }
            case keywords::tag_start: {
                  result += "tag_start(" + this->r->str("", stat_prefix) + ", " + this->v->str("", stat_prefix) + ")";
                  break;
            }
            case keywords::tag_end: {
                  result += "tag_end";
                  break;
            }
            case keywords::command: {
                  result += "command(";
                  if (this->r) {
                        result += this->r->str("", stat_prefix);
                  }
                  result += !this->members.empty() ? "," : "";
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        result += this->members[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->members.size()) {
                              result += ", ";
                        }
                  }
                  result += ")";
                  break;
            }
            default: {
                  break;
            }
      }
      return result;
}
std::string ir_stat::str_type() const {
      return std::string(this->flags.funsigned ? "u" : "") + "int" + std::to_string(this->extra_bits) + "_t";
}
void ir_stat::dump(const char *const descriminator) const {
      LURAMAS_PRINTF("%s %s\n", descriminator, this->str().c_str());
      return;
}
