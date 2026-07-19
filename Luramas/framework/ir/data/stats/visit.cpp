#include "../../ir.hpp"

boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> ir_stat::visit(const luramas_register target, const bool all) {

      boost::unordered_flat_set<std::shared_ptr<ir_expr>> result;
      if (this->lba) {
            this->lba->extract(result, target, all);
      }
      if (this->l) {
            this->l->extract(result, target, all);
      }
      if (this->r) {
            this->r->extract(result, target, all);
      }
      if (this->v) {
            this->v->extract(result, target, all);
      }
      for (const auto &m : this->members) {
            m->extract(result, target, all);
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  m->extract(result, target, all);
            }
      }
      for (const auto &m : this->tmembers) {
            m->extract(result, target, all);
      }
      return result;
}
boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> ir_stat::visit_sources(const luramas_register target, const bool all) {

      boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> result;
      switch (this->k) {
            case keywords::call:
            case keywords::stack_pop:
            case keywords::stack_push:
            case keywords::retn: {
                  if (this->l) {
                        this->l->extract(result, target, all);
                  }
                  for (const auto &m : this->members) {
                        m->extract(result, target, all);
                  }
                  break;
            }
            case keywords::condition:
            case keywords::condition_goto:
            case keywords::memoryset:
            case keywords::until:
            case keywords::while_:
            case keywords::table_assign: {
                  if (this->l) {
                        this->l->extract(result, target, all);
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      if (this->r) {
            this->r->extract(result, target, all);
      }
      if (this->v) {
            this->v->extract(result, target, all);
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  m->extract(result, target, all);
            }
      }
      for (const auto &m : this->tmembers) {
            m->extract(result, target, all);
      }
      return result;
}
std::pair<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat>> ir_stat::visit_parent(const std::shared_ptr<ir_stat::ir_expr> &expr) {

      std::pair<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat>> result = std::make_pair(nullptr, nullptr);
      if (this->lba) {
            if (*this->lba == *expr) {
                  result.second = shared_from_this();
                  return result;
            }
            if (const auto parent = this->lba->visit_parent(expr); parent) {
                  result.first = parent;
                  return result;
            }
      }
      if (this->l) {
            if (*this->l == *expr) {
                  result.second = shared_from_this();
                  return result;
            }
            if (const auto parent = this->l->visit_parent(expr); parent) {
                  result.first = parent;
                  return result;
            }
      }
      if (this->r) {
            if (*this->r == *expr) {
                  result.second = shared_from_this();
                  return result;
            }
            if (const auto parent = this->r->visit_parent(expr); parent) {
                  result.first = parent;
                  return result;
            }
      }
      if (this->v) {
            if (*this->v == *expr) {
                  result.second = shared_from_this();
                  return result;
            }
            if (const auto parent = this->v->visit_parent(expr); parent) {
                  result.first = parent;
                  return result;
            }
      }
      for (const auto &m : this->members) {
            if (m) {
                  if (*m == *expr) {
                        result.second = shared_from_this();
                        return result;
                  }
                  if (const auto parent = m->visit_parent(expr); parent) {
                        result.first = parent;
                        return result;
                  }
            }
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  if (m) {
                        if (*m == *expr) {
                              result.second = shared_from_this();
                              return result;
                        }
                        if (const auto parent = m->visit_parent(expr); parent) {
                              result.first = parent;
                              return result;
                        }
                  }
            }
      }
      for (const auto &m : this->tmembers) {
            if (m) {
                  if (*m == *expr) {
                        result.second = shared_from_this();
                        return result;
                  }

                  if (const auto parent = m->visit_parent(expr); parent) {
                        result.first = parent;
                        return result;
                  }
            }
      }
      return result;
}
std::shared_ptr<ir_stat::ir_expr> ir_stat::visit_lvalue(const luramas_register reg) const {
      if (this->l && this->l->is_reg(reg)) {
            return this->l;
      }
      if (this->lba && this->lba->is_reg(reg)) {
            return this->lba;
      }
      for (const auto &m : this->members) {
            if (m && m->is_reg(reg)) {
                  return m;
            }
      }
      return nullptr;
}