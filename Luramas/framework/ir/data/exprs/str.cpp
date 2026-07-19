#include "../../ir.hpp"

std::string ir_stat::ir_expr::str(const std::string &prefix, const std::string &stat_prefix) {

      std::string retn(prefix);
      switch (this->k) {
            case expr_kinds::self: {
                  retn += this->l->str("", stat_prefix) + ":" + this->r->str("", stat_prefix);
                  break;
            }
            case expr_kinds::page_function_call: {
                  if (this->flags.fexternal_page_goto) {
                        retn += "[EXTERNAL] ";
                  }
                  retn += "page_function_call<" + this->r->str("", stat_prefix) + ", " + this->ev->str("", stat_prefix) + ", " + this->xv->str("", stat_prefix) + ">(";
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        retn += this->members[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->members.size()) {
                              retn += ", ";
                        }
                  }
                  retn += ")";
                  if (this->l) {
                        retn += " -> " + this->l->str();
                  }
                  break;
            }
            case expr_kinds::unary: {
                  retn += std::string(luramas::il::arch::data::bin_kindstr(this->u)) + this->l->str("", stat_prefix);
                  break;
            }
            case expr_kinds::call: {
                  if (this->flags.fvirtualized) {
                        retn += "[V]";
                  }
                  if (this->flags.fexternal_page_goto) {
                        retn += "[PEX]";
                  }
                  if (!retn.empty()) {
                        retn += " ";
                  }
                  retn += this->l->str("", stat_prefix) + "(";
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        retn += this->members[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->members.size()) {
                              retn += ", ";
                        }
                  }
                  retn += ")";
                  break;
            }
            case expr_kinds::ternary: {
                  retn += "(if (";
                  if (this->b == luramas::il::arch::data::bin_kinds::nt_) {
                        retn += "not ";
                  }
                  retn += this->l->str("", stat_prefix);
                  if (this->e != expr_logical::nothing) {
                        retn += (this->e == expr_logical::or_ ? " or " : " and ") + this->r->str("", stat_prefix);
                  } else if (this->r) {
                        retn += std::string(" ") + luramas::il::arch::data::bin_kindstr(this->b) + " " + this->r->str("", stat_prefix);
                  }
                  retn += ") then " + this->ev->str("", stat_prefix) + " else " + this->xv->str("", stat_prefix) + ")";
                  break;
            }
            case expr_kinds::arith: {
                  retn += "(" + this->l->str("", stat_prefix) + " " + luramas::il::arch::data::bin_kindstr(this->b) + " " + this->r->str("", stat_prefix) + ")";
                  break;
            }
            case expr_kinds::idx: {
                  retn += this->l->str("", stat_prefix) + "[" + this->r->str("", stat_prefix) + "]";
                  break;
            }
            case expr_kinds::flag: {
                  retn += "flag(" + this->r->str("", stat_prefix) + ")";
                  break;
            }
            case expr_kinds::condition: {
                  retn += "(";
                  if (this->b == luramas::il::arch::data::bin_kinds::nt_) {
                        retn += "not ";
                  }
                  retn += this->l->str("", stat_prefix);
                  if (this->e != expr_logical::nothing) {
                        retn += (this->e == expr_logical::or_ ? " or " : " and ") + this->r->str("", stat_prefix);
                  } else if (this->r) {
                        retn += std::string(" ") + luramas::il::arch::data::bin_kindstr(this->b) + " " + this->r->str("", stat_prefix);
                  }
                  retn += ")";
                  break;
            }
            case expr_kinds::concat: {
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        retn += this->members[idx]->str("", stat_prefix);
                        if ((idx + 1u) < this->members.size()) {
                              retn += " .. ";
                        }
                  }
                  break;
            }
            case expr_kinds::closure: {
                  retn += "(function (";
                  // retn += "(";
                  // for (const auto &c : this->captures)
                  //       retn += c->str() + "  ";
                  // retn += ")";
                  const auto def = this->closure.front();
                  for (auto it = def->args.begin(); it != def->args.end(); ++it) {
                        retn += (*it).second->str("", stat_prefix);
                        if (std::next(it) != def->args.end()) {
                              retn += ", ";
                        } else if (def->flags.fvariadic_def) {
                              retn += ", ...";
                        }
                  }
                  if (def->args.empty() && def->flags.fvariadic_def) {
                        retn += "...";
                  }
                  retn += ")\n";
                  for (const auto &s : this->closure) {
                        const auto &str = s->str(stat_prefix);
                        if (!str.empty()) {
                              retn += str + "\n";
                        }
                  }
                  retn += "end)";
                  break;
            }
            case expr_kinds::blank_lvalue: {
                  retn += this->l->str("", stat_prefix);
                  break;
            }
            case expr_kinds::unpack: {
                  retn += this->l->str("", stat_prefix);
                  break;
            }
            case expr_kinds::cast: {
                  retn += this->non_native->str() + "(" + this->l->str("", stat_prefix) + ")";
                  break;
            }
            case expr_kinds::memoryread: {
                  retn += "memread<" + (this->xtype ? this->xtype->str() + ", " : "") + this->non_native->str() + ">(" + this->l->str("", stat_prefix) + (this->r ? " + " + this->r->str("", stat_prefix) : "") + ")";
                  break;
            }
            case expr_kinds::bitread: {
                  retn += "bitread<" + this->non_native->str() + ">(" + this->l->str("", stat_prefix) + ", " + this->r->str("", stat_prefix) + ", " + this->ev->str("", stat_prefix) + ")";
                  break;
            }
            case expr_kinds::bitwrite: {
                  retn += "bitwrite<" + this->non_native->str() + ">(" + this->l->str("", stat_prefix) + ", " + this->r->str("", stat_prefix) + ", " + this->ev->str("", stat_prefix) + ", " + this->xv->str("", stat_prefix) + ")";
                  break;
            }
            default: {
                  retn += this->v_s();
                  break;
            }
      }
      return retn;
}
std::string ir_stat::ir_expr::v_s() const {

      switch (this->tk) {
            case tkind::table: {
                  std::string result("");
                  result += "{ ";
                  for (auto idx = 0u; idx < this->tmembers.size(); ++idx) {
                        const auto &[i, v] = this->tmembers[idx];
                        if (i) {
                              result += "[" + i->str() + "] = ";
                        }
                        result += v->str();
                        if ((idx + 1u) < this->tmembers.size()) {
                              result += ", ";
                        }
                  }
                  result += " }";
                  return result;
            }
            case tkind::variadic: {
                  return "...";
            }
            case tkind::boolean: {
                  return this->bv ? "true" : "false";
            }
            case tkind::lura_int: {
                  auto result = luramas::str::to_string(this->n);
                  luramas_str_integer(result);
                  return result;
            }
            case tkind::stack: {
                  return this->n ? "stack_" + luramas::str::to_string(this->n) : "stack";
            }
            case tkind::none_obj: {
                  return "nil";
            }
            case tkind::controller: {
                  return "controller";
            }
            case tkind::extpr: {
                  auto result = luramas::str::to_string(this->n);
                  luramas_str_integer(result);
                  return "EXTPR[" + result + "]";
            }
            case tkind::object: {
                  return this->non_native->str();
            }
            default: {
                  break;
            }
      }
      switch (this->k) {
            case expr_kinds::upvalue: {
                  return "upv" + std::to_string(this->reg);
            }
            case expr_kinds::reg: {
                  return (!this->v.empty() ? this->v : (this->is_rk<expr_reg_kinds::arg>() ? "a" : "r") + std::to_string(this->reg));
            }
            default: {
                  break;
            }
      }
      return LURAMAS_IR_MAX_STR_RENDER_SIZE && this->v.size() > LURAMAS_IR_MAX_STR_RENDER_SIZE ? "LONG_STR" : this->tk == tkind::string ? "\"" + this->v + "\""
                                                                                                                                        : this->v;
}
void ir_stat::ir_expr::dump(const char *const descriminator) {
      std::printf("%s %s\n", descriminator, this->str().c_str());
      return;
}
