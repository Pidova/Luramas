#include "../../ir.hpp"

/* Dest values buffers */
void ir_stat::extract_ordered_dest_regs(luramas_registers &buffer, const bool ignore_upvalues) const {

      switch (this->k) {
            case keywords::assignment:
            case keywords::forloop_generic:
            case keywords::table_setlist:
            case keywords::page_function_pass:
            case keywords::bitwrite: {
                  if (this->l) {
                        this->l->extract_ordered_regs(buffer, ignore_upvalues);
                  }
                  switch (this->k) {
                        case keywords::assignment:
                        case keywords::forloop_generic:
                        case keywords::page_function_pass: {
                              for (const auto &m : this->members) {
                                    m->extract_ordered_regs(buffer, ignore_upvalues);
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  break;
            }
            case keywords::forloop_numeric: {
                  this->lba->extract_ordered_regs(buffer, ignore_upvalues);
                  break;
            }
            case keywords::definition: {
                  for (const auto &a : this->args) {
                        buffer.emplace_back(a.first);
                  }
                  for (const auto &a : this->upvalues) {
                        a->extract_ordered_regs(buffer, ignore_upvalues);
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      return;
}
void ir_stat::extract_dests(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer) const {

      switch (this->k) {
            case keywords::assignment:
            case keywords::forloop_generic:
            case keywords::table_setlist:
            case keywords::page_function_pass:
            case keywords::bitwrite: {
                  if (this->l) {
                        this->l->extract_reg_exprs(buffer);
                  }
                  switch (this->k) {
                        case keywords::assignment:
                        case keywords::forloop_generic:
                        case keywords::page_function_pass: {
                              for (const auto &m : this->members) {
                                    m->extract_reg_exprs(buffer);
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  break;
            }
            case keywords::forloop_numeric: {
                  this->lba->extract_reg_exprs(buffer);
                  break;
            }
            case keywords::definition: {
                  for (const auto &a : this->args) {
                        a.second->extract_reg_exprs(buffer);
                  }
                  for (const auto &a : this->upvalues) {
                        a->extract_reg_exprs(buffer);
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      return;
}
void ir_stat::extract_dest_regs(boost::unordered_flat_multiset<luramas_register> &buffer, const bool ignore_upvalues) const {

      switch (this->k) {
            case keywords::assignment:
            case keywords::forloop_generic:
            case keywords::table_setlist:
            case keywords::page_function_pass:
            case keywords::bitwrite: {
                  if (this->l) {
                        this->l->extract_regs(buffer, ignore_upvalues);
                  }
                  switch (this->k) {
                        case keywords::assignment:
                        case keywords::forloop_generic:
                        case keywords::page_function_pass: {
                              for (const auto &m : this->members) {
                                    m->extract_regs(buffer, ignore_upvalues);
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  break;
            }
            case keywords::forloop_numeric: {
                  this->lba->extract_regs(buffer, ignore_upvalues);
                  break;
            }
            case keywords::definition: {
                  for (const auto &a : this->args) {
                        buffer.insert(a.second->reg);
                  }
                  for (const auto &a : this->upvalues) {
                        buffer.insert(a->reg);
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      return;
}
void ir_stat::extract_set_dest_regs(boost::unordered_flat_set<luramas_register> &buffer, const bool ignore_upvalues) const {

      switch (this->k) {
            case keywords::assignment:
            case keywords::forloop_generic:
            case keywords::table_setlist:
            case keywords::page_function_pass:
            case keywords::bitwrite: {
                  if (this->l) {
                        this->l->extract_regs(buffer, ignore_upvalues);
                  }
                  switch (this->k) {
                        case keywords::assignment:
                        case keywords::forloop_generic:
                        case keywords::page_function_pass: {
                              for (const auto &m : this->members) {
                                    m->extract_regs(buffer, ignore_upvalues);
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  break;
            }
            case keywords::forloop_numeric: {
                  this->lba->extract_regs(buffer, ignore_upvalues);
                  break;
            }
            case keywords::definition: {
                  for (const auto &a : this->args) {
                        buffer.insert(a.second->reg);
                  }
                  for (const auto &a : this->upvalues) {
                        buffer.insert(a->reg);
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      return;
}

/* Lvalues buffers */
void ir_stat::extract_lvalues(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer) const {

      switch (this->k) {
            case keywords::assignment:
            case keywords::forloop_generic:
            case keywords::table_setlist:
            case keywords::page_function_pass:
            case keywords::bitwrite: {
                  if (this->l) {
                        buffer.insert(this->l);
                  }
                  switch (this->k) {
                        case keywords::assignment:
                        case keywords::forloop_generic:
                        case keywords::page_function_pass: {
                              buffer.reserve(buffer.size() + this->members.size());
                              buffer.insert(this->members.begin(), this->members.end());
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  break;
            }
            case keywords::forloop_numeric: {
                  buffer.insert(this->lba);
                  break;
            }
            default: {
                  break;
            }
      }
      return;
}
void ir_stat::extract_set_lvalues(boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &buffer) const {

      switch (this->k) {
            case keywords::assignment:
            case keywords::forloop_generic:
            case keywords::table_setlist:
            case keywords::page_function_pass:
            case keywords::bitwrite: {
                  if (this->l) {
                        buffer.insert(this->l);
                  }
                  switch (this->k) {
                        case keywords::assignment:
                        case keywords::forloop_generic:
                        case keywords::page_function_pass: {
                              buffer.reserve(buffer.size() + this->members.size());
                              buffer.insert(this->members.begin(), this->members.end());
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  break;
            }
            case keywords::forloop_numeric: {
                  buffer.insert(this->lba);
                  break;
            }
            default: {
                  break;
            }
      }
      return;
}
void ir_stat::extract_ordered_lvalues(ir_stat::ir_expr::space &buffer) const {

      switch (this->k) {
            case keywords::assignment:
            case keywords::forloop_generic:
            case keywords::table_setlist:
            case keywords::page_function_pass:
            case keywords::bitwrite: {
                  if (this->l) {
                        buffer.emplace_back(this->l);
                  }
                  switch (this->k) {
                        case keywords::assignment:
                        case keywords::forloop_generic:
                        case keywords::page_function_pass: {
                              buffer.reserve(buffer.size() + this->members.size());
                              buffer.insert(buffer.end(), this->members.begin(), this->members.end());
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  break;
            }
            case keywords::forloop_numeric: {
                  buffer.emplace_back(this->lba);
                  break;
            }
            default: {
                  break;
            }
      }
      return;
}
void ir_stat::extract_deep_set_lvalues(boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &buffer) const {

      for (const auto &i : this->extract_set_lvalues()) {
            i->extract_exprs(buffer);
      }
      return;
}
void ir_stat::extract_deep_ordered_lvalues(ir_stat::ir_expr::space &buffer) const {

      for (const auto &i : this->extract_ordered_lvalues()) {
            i->extract_ordered_exprs(buffer);
      }
      return;
}

/* Dest values */
luramas_registers ir_stat::extract_ordered_dest_regs(const bool ignore_upvalues) const {

      luramas_registers result;
      result.reserve(LURAMAS_PREDICTED_REGS);
      this->extract_ordered_dest_regs(result, ignore_upvalues);
      return result;
}
boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> ir_stat::extract_dests() const {

      boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> result;
      result.reserve(LURAMAS_PREDICTED_REGS);
      this->extract_dests(result);
      return result;
}
boost::unordered_flat_multiset<luramas_register> ir_stat::extract_dest_regs(const bool ignore_upvalues) const {

      boost::unordered_flat_multiset<luramas_register> result;
      result.reserve(LURAMAS_PREDICTED_REGS);
      this->extract_dest_regs(result, ignore_upvalues);
      return result;
}
boost::unordered_flat_set<luramas_register> ir_stat::extract_set_dest_regs(const bool ignore_upvalues) const {

      boost::unordered_flat_set<luramas_register> result;
      result.reserve(LURAMAS_PREDICTED_REGS);
      this->extract_set_dest_regs(result, ignore_upvalues);
      return result;
}

/* Lvalues */
boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> ir_stat::extract_lvalues() const {

      boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> result;
      result.reserve(LURAMAS_PREDICTED_VALUES);
      this->extract_lvalues(result);
      return result;
}
boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> ir_stat::extract_set_lvalues() const {

      boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> result;
      result.reserve(LURAMAS_PREDICTED_VALUES);
      this->extract_set_lvalues(result);
      return result;
}
boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> ir_stat::extract_deep_set_lvalues() const {

      boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> result;
      this->extract_deep_set_lvalues(result);
      return result;
}
ir_stat::ir_expr::space ir_stat::extract_ordered_lvalues() const {

      ir_stat::ir_expr::space result;
      this->extract_ordered_lvalues(result);
      return result;
}
ir_stat::ir_expr::space ir_stat::extract_deep_ordered_lvalues() const {

      ir_stat::ir_expr::space result;
      this->extract_deep_ordered_lvalues(result);
      return result;
}