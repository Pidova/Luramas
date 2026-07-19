#include "../../ir.hpp"

/* Sources buffers */
void ir_stat::extract_ordered_source_regs(luramas_registers &buffer, const bool ignore_upvalues) const {

      switch (this->k) {
            case keywords::stack_pop:
            case keywords::stack_push:
            case keywords::retn:
            case keywords::call:
            case keywords::page_function_goto: {
                  if (this->l && this->k != keywords::retn) {
                        this->l->extract_ordered_regs(buffer, ignore_upvalues);
                  }
                  for (const auto &m : this->members) {
                        m->extract_ordered_regs(buffer, ignore_upvalues);
                  }
                  return;
            }
            case keywords::condition:
            case keywords::condition_goto:
            case keywords::table_setlist:
            case keywords::table_assign:
            case keywords::until:
            case keywords::while_:
            case keywords::memoryset:
            case keywords::forloop_numeric: {
                  if (this->l) {
                        this->l->extract_ordered_regs(buffer, ignore_upvalues);
                  }
                  break;
            }
            case keywords::definition: {
                  if (this->flags.flink_regs) {
                        for (const auto &[_, expr] : this->args) {
                              expr->extract_ordered_regs(buffer, ignore_upvalues);
                        }
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      if (this->r) {
            this->r->extract_ordered_regs(buffer, ignore_upvalues);
      }
      if (this->v) {
            this->v->extract_ordered_regs(buffer, ignore_upvalues);
      }
      if (this->k == keywords::bitwrite && this->lba) {
            this->lba->extract_ordered_regs(buffer, ignore_upvalues);
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  m->extract_ordered_regs(buffer, ignore_upvalues);
            }
      }
      for (const auto &m : this->tmembers) {
            m->extract_ordered_regs(buffer, ignore_upvalues);
      }
      return;
}
void ir_stat::extract_source_captures(ir_stat::ir_expr::space &buffer) const {

      switch (this->k) {
            case keywords::call:
            case keywords::stack_pop:
            case keywords::stack_push:
            case keywords::retn:
            case keywords::page_function_goto: {
                  if (this->l && this->k != keywords::retn) {
                        this->l->extract_captures(buffer);
                  }
                  for (const auto &m : this->members) {
                        m->extract_captures(buffer);
                  }
                  return;
            }
            case keywords::condition:
            case keywords::condition_goto:
            case keywords::table_setlist:
            case keywords::table_assign:
            case keywords::until:
            case keywords::while_:
            case keywords::memoryset:
            case keywords::forloop_numeric: {
                  if (this->l) {
                        this->l->extract_captures(buffer);
                  }
                  break;
            }
            case keywords::definition: {
                  if (this->flags.flink_regs) {
                        for (const auto &[_, expr] : this->args) {
                              expr->extract_captures(buffer);
                        }
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      if (this->r) {
            this->r->extract_captures(buffer);
      }
      if (this->v) {
            this->v->extract_captures(buffer);
      }
      if (this->k == keywords::bitwrite && this->lba) {
            this->lba->extract_captures(buffer);
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  m->extract_captures(buffer);
            }
      }
      for (const auto &m : this->tmembers) {
            m->extract_captures(buffer);
      }
      return;
}
void ir_stat::extract_source_regs(boost::unordered_flat_multiset<luramas_register> &buffer, const bool ignore_upvalues) const {

      switch (this->k) {
            case keywords::call:
            case keywords::stack_pop:
            case keywords::stack_push:
            case keywords::retn:
            case keywords::page_function_goto: {
                  if (this->l && this->k != keywords::retn) {
                        this->l->extract_regs(buffer, ignore_upvalues);
                  }
                  for (const auto &m : this->members) {
                        m->extract_regs(buffer, ignore_upvalues);
                  }
                  return;
            }
            case keywords::condition:
            case keywords::condition_goto:
            case keywords::table_setlist:
            case keywords::table_assign:
            case keywords::until:
            case keywords::while_:
            case keywords::memoryset:
            case keywords::forloop_numeric: {
                  if (this->l) {
                        this->l->extract_regs(buffer, ignore_upvalues);
                  }
                  break;
            }
            case keywords::definition: {
                  if (this->flags.flink_regs) {
                        for (const auto &[_, expr] : this->args) {
                              expr->extract_regs(buffer, ignore_upvalues);
                        }
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      if (this->r) {
            this->r->extract_regs(buffer, ignore_upvalues);
      }
      if (this->v) {
            this->v->extract_regs(buffer, ignore_upvalues);
      }
      if (this->k == keywords::bitwrite && this->lba) {
            this->lba->extract_regs(buffer, ignore_upvalues);
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  m->extract_regs(buffer, ignore_upvalues);
            }
      }
      for (const auto &m : this->tmembers) {
            m->extract_regs(buffer, ignore_upvalues);
      }
      return;
}

/* Rvalues buffers */
void ir_stat::extract_rvalues(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer) const {

      switch (this->k) {
            case keywords::call:
            case keywords::stack_pop:
            case keywords::stack_push:
            case keywords::retn:
            case keywords::page_function_goto: {
                  if (this->l && this->k != keywords::retn) {
                        buffer.insert(this->l);
                  }
                  for (const auto &m : this->members) {
                        buffer.insert(m);
                  }
                  return;
            }
            case keywords::condition:
            case keywords::condition_goto:
            case keywords::table_setlist:
            case keywords::table_assign:
            case keywords::until:
            case keywords::while_:
            case keywords::memoryset:
            case keywords::forloop_numeric: {
                  if (this->l) {
                        buffer.insert(this->l);
                  }
                  break;
            }
            case keywords::definition: {
                  if (this->flags.flink_regs) {
                        for (const auto &[_, expr] : this->args) {
                              buffer.insert(expr);
                        }
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      if (this->r) {
            buffer.insert(this->r);
      }
      if (this->v) {
            buffer.insert(this->v);
      }
      if (this->k == keywords::bitwrite && this->lba) {
            buffer.insert(this->lba);
      }
      if (this->k != keywords::page_function_goto) {
            buffer.insert(this->smembers.begin(), this->smembers.end());
      }
      buffer.insert(this->tmembers.begin(), this->tmembers.end());
      return;
}
void ir_stat::extract_set_rvalues(boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &buffer) const {

      switch (this->k) {
            case keywords::call:
            case keywords::stack_pop:
            case keywords::stack_push:
            case keywords::retn:
            case keywords::page_function_goto: {
                  if (this->l && this->k != keywords::retn) {
                        buffer.insert(this->l);
                  }
                  for (const auto &m : this->members) {
                        buffer.insert(m);
                  }
                  return;
            }
            case keywords::condition:
            case keywords::condition_goto:
            case keywords::table_setlist:
            case keywords::table_assign:
            case keywords::until:
            case keywords::while_:
            case keywords::memoryset:
            case keywords::forloop_numeric: {
                  if (this->l) {
                        buffer.insert(this->l);
                  }
                  break;
            }
            case keywords::definition: {
                  if (this->flags.flink_regs) {
                        for (const auto &[_, expr] : this->args) {
                              buffer.insert(expr);
                        }
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      if (this->r) {
            buffer.insert(this->r);
      }
      if (this->v) {
            buffer.insert(this->v);
      }
      if (this->k == keywords::bitwrite && this->lba) {
            buffer.insert(this->lba);
      }
      if (this->k != keywords::page_function_goto) {
            buffer.insert(this->smembers.begin(), this->smembers.end());
      }
      buffer.insert(this->tmembers.begin(), this->tmembers.end());
      return;
}
void ir_stat::extract_ordered_rvalues(ir_stat::ir_expr::space &buffer) const {

      switch (this->k) {
            case keywords::call:
            case keywords::stack_pop:
            case keywords::stack_push:
            case keywords::retn:
            case keywords::page_function_goto: {
                  if (this->l && this->k != keywords::retn) {
                        buffer.emplace_back(this->l);
                  }
                  buffer.reserve(this->members.size());
                  buffer.insert(buffer.end(), this->members.begin(), this->members.end());
                  return;
            }
            case keywords::condition:
            case keywords::condition_goto:
            case keywords::table_setlist:
            case keywords::table_assign:
            case keywords::until:
            case keywords::while_:
            case keywords::memoryset:
            case keywords::forloop_numeric: {
                  if (this->l) {
                        buffer.emplace_back(this->l);
                  }
                  break;
            }
            case keywords::definition: {
                  if (this->flags.flink_regs) {
                        buffer.reserve(this->args.size());
                        for (const auto &[_, expr] : this->args) {
                              buffer.emplace_back(expr);
                        }
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      if (this->r) {
            buffer.emplace_back(this->r);
      }
      if (this->v) {
            buffer.emplace_back(this->v);
      }
      if (this->k == keywords::bitwrite && this->lba) {
            buffer.emplace_back(this->lba);
      }
      if (this->k != keywords::page_function_goto) {
            buffer.reserve(buffer.size() + this->smembers.size());
            buffer.insert(buffer.end(), this->smembers.begin(), this->smembers.end());
      }
      buffer.reserve(buffer.size() + this->tmembers.size());
      buffer.insert(buffer.end(), this->tmembers.begin(), this->tmembers.end());
      return;
}
void ir_stat::extract_deep_set_rvalues(boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &buffer) const {

      for (const auto &i : this->extract_set_rvalues()) {
            i->extract_exprs(buffer);
      }
      return;
}
void ir_stat::extract_deep_ordered_rvalues(ir_stat::ir_expr::space &buffer) const {

      for (const auto &i : this->extract_ordered_rvalues()) {
            i->extract_ordered_exprs(buffer);
      }
      return;
}

/* Source */
ir_stat::ir_expr::space ir_stat::extract_ordered_source_captures() const {

      ir_stat::ir_expr::space result;
      result.reserve(LURAMAS_PREDICTED_REGS);
      this->extract_source_captures(result);
      return result;
}
luramas_registers ir_stat::extract_ordered_source_regs(const bool ignore_upvalues) const {

      luramas_registers result;
      result.reserve(LURAMAS_PREDICTED_REGS);
      this->extract_ordered_source_regs(result, ignore_upvalues);
      return result;
}
boost::unordered_flat_multiset<luramas_register> ir_stat::extract_source_regs(const bool ignore_upvalues) const {

      boost::unordered_flat_multiset<luramas_register> result;
      result.reserve(LURAMAS_PREDICTED_REGS);
      this->extract_source_regs(result, ignore_upvalues);
      return result;
}

/* Rvalues */
boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> ir_stat::extract_rvalues() const {

      boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> result;
      this->extract_rvalues(result);
      return result;
}
boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> ir_stat::extract_set_rvalues() const {

      boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> result;
      this->extract_set_rvalues(result);
      return result;
}
ir_stat::ir_expr::space ir_stat::extract_ordered_rvalues() const {

      ir_stat::ir_expr::space result;
      this->extract_ordered_rvalues(result);
      return result;
}
boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> ir_stat::extract_deep_set_rvalues() const {

      boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> result;
      this->extract_deep_set_rvalues(result);
      return result;
}
ir_stat::ir_expr::space ir_stat::extract_deep_ordered_rvalues() const {

      ir_stat::ir_expr::space result;
      this->extract_deep_ordered_rvalues(result);
      return result;
}