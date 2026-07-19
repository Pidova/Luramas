#include "../../ir.hpp"

void ir_stat::ir_expr::propagate_flag(const luramas_int &target, const std::shared_ptr<ir_expr> &e, bool &clone) {
      std::vector<std::size_t> removals;
      if (this->l && (e == nullptr || *this->l != *e)) {
            if (this->l->is_flag(target)) {
                  this->l = (clone) ? e->clone() : e;
                  clone = e != nullptr;
            } else {
                  this->l->propagate_flag(target, e, clone);
            }
      }
      if (this->r && (e == nullptr || *this->r != *e)) {
            if (this->r->is_flag(target)) {
                  this->r = (clone) ? e->clone() : e;
                  clone = e != nullptr;
            } else {
                  this->r->propagate_flag(target, e, clone);
            }
      }
      if (this->ev && (e == nullptr || *this->ev != *e)) {
            if (this->ev->is_flag(target)) {
                  this->ev = (clone) ? e->clone() : e;
                  clone = e != nullptr;
            } else {
                  this->ev->propagate_flag(target, e, clone);
            }
      }
      if (this->xv && (e == nullptr || *this->xv != *e)) {
            if (this->xv->is_flag(target)) {
                  this->xv = (clone) ? e->clone() : e;
                  clone = e != nullptr;
            } else {
                  this->xv->propagate_flag(target, e, clone);
            }
      }
      for (auto idx = 0u; idx < this->members.size(); ++idx) {
            auto &m = this->members[idx];
            if (m != nullptr && (e == nullptr || *m != *e)) {
                  if (m->is_flag(target)) {
                        if (e == nullptr) {
                              removals.emplace_back(idx);
                        } else {
                              m = (clone) ? e->clone() : e;
                              clone = e != nullptr;
                        }
                  } else {
                        m->propagate_flag(target, e, clone);
                  }
            }
      }
      for (const auto &i : removals) {
            this->members.erase(this->members.begin() + i);
      }
      removals.clear();
      if (this->k != expr_kinds::page_function_call) {
            for (auto idx = 0u; idx < this->tmembers.size(); ++idx) {
                  auto &[i, v] = this->tmembers[idx];
                  if (v && (e == nullptr || *v != *e)) {
                        if (v->is_flag(target)) {
                              if (e == nullptr) {
                                    removals.emplace_back(idx);
                                    continue;
                              } else {
                                    v = (clone) ? e->clone() : e;
                                    clone = e != nullptr;
                              }
                        } else {
                              v->propagate_flag(target, e, clone);
                        }
                  }
                  if (i && (e == nullptr || *i != *e)) {
                        if (i->is_flag(target)) {
                              i = (clone) ? e->clone() : e;
                              clone = e != nullptr;
                        } else {
                              i->propagate_flag(target, e, clone);
                        }
                  }
            }
            for (const auto &i : removals) {
                  this->tmembers.erase(this->tmembers.begin() + i);
            }
      }
      return;
}
void ir_stat::ir_expr::propagate(const luramas_register target, const std::shared_ptr<ir_expr> &e, bool &clone) {
      std::vector<std::size_t> removals;
      if (this->l && (e == nullptr || *this->l != *e)) {
            if (this->l->is_reg(target)) {
                  this->l = (clone) ? e->clone(true, false) : e;
                  clone = e != nullptr;
            } else {
                  this->l->propagate(target, e, clone);
            }
      }
      if (this->r && (e == nullptr || *this->r != *e)) {
            if (this->r->is_reg(target)) {
                  this->r = (clone) ? e->clone(true, false) : e;
                  clone = e != nullptr;
            } else {
                  this->r->propagate(target, e, clone);
            }
      }
      if (this->ev && (e == nullptr || *this->ev != *e)) {
            if (this->ev->is_reg(target)) {
                  this->ev = (clone) ? e->clone(true, false) : e;
                  clone = e != nullptr;
            } else {
                  this->ev->propagate(target, e, clone);
            }
      }
      if (this->xv && (e == nullptr || *this->xv != *e)) {
            if (this->xv->is_reg(target)) {
                  this->xv = (clone) ? e->clone(true, false) : e;
                  clone = e != nullptr;
            } else {
                  this->xv->propagate(target, e, clone);
            }
      }
      for (auto idx = 0u; idx < this->members.size(); ++idx) {
            auto &m = this->members[idx];
            if (m && (e == nullptr || *m != *e)) {
                  if (m->is_reg(target)) {
                        if (e == nullptr) {
                              removals.emplace_back(idx);
                        } else {
                              m = (clone) ? e->clone(true, false) : e;
                              clone = e != nullptr;
                        }
                  } else {
                        m->propagate(target, e, clone);
                  }
            }
      }
      for (const auto &i : removals) {
            this->members.erase(this->members.begin() + i);
      }
      removals.clear();
      if (this->k != expr_kinds::page_function_call) {
            for (auto idx = 0u; idx < this->tmembers.size(); ++idx) {
                  auto &[i, v] = this->tmembers[idx];
                  if (v && (e == nullptr || *v != *e)) {
                        if (v->is_reg(target)) {
                              if (e == nullptr) {
                                    removals.emplace_back(idx);
                                    continue;
                              } else {
                                    v = (clone) ? e->clone(true, false) : e;
                                    clone = e != nullptr;
                              }
                        } else {
                              v->propagate(target, e, clone);
                        }
                  }
                  if (i && (e == nullptr || *i != *e)) {
                        if (i->is_reg(target)) {
                              i = (clone) ? e->clone(true, false) : e;
                              clone = e != nullptr;
                        } else {
                              i->propagate(target, e, clone);
                        }
                  }
            }
            for (const auto &i : removals) {
                  this->tmembers.erase(this->tmembers.begin() + i);
            }
      }
      return;
}
bool ir_stat::ir_expr::propagate_violates(const luramas_register target) const {
      if (this->l) {
            if (this->l->is_reg(target)) {
                  return this->is_primitive_kind_dest_violation();
            } else if (this->l->propagate_violates(target)) {
                  return true;
            }
      }
      if (this->r && this->r->propagate_violates(target)) {
            return true;
      }
      if (this->ev && this->ev->propagate_violates(target)) {
            return true;
      }
      if (this->xv && this->xv->propagate_violates(target)) {
            return true;
      }
      for (const auto &m : this->members) {
            if (m->propagate_violates(target)) {
                  return true;
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &m : this->tmembers) {
                  if (m.second && m.second->propagate_violates(target)) {
                        return true;
                  }
                  if (m.first && m.first->propagate_violates(target)) {
                        return true;
                  }
            }
      }
      return false;
}
