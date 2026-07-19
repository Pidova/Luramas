#include "../../ir.hpp"

void ir_stat::propagate_flag(const luramas_int &target, const std::shared_ptr<ir_expr> &e, bool &clone) {

      std::vector<luramas_address> removals;
      if (this->r && (e == nullptr || *this->r != *e)) {
            if (this->r->is_flag(target)) {
                  this->r = (clone) ? e->clone() : e;
                  clone = e != nullptr;
            } else {
                  this->r->propagate_flag(target, e, clone);
            }
      }
      if (this->v && (e == nullptr || *this->v != *e)) {
            if (this->v->is_flag(target)) {
                  this->v = (clone) ? e->clone() : e;
                  clone = e != nullptr;
            } else {
                  this->v->propagate_flag(target, e, clone);
            }
      }
      switch (this->k) {
            case keywords::call:
            case keywords::stack_pop:
            case keywords::stack_push:
            case keywords::retn: {
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        auto &m = this->members[idx];
                        if (m != nullptr && (e == nullptr || *m != *e)) {
                              if (m->is_flag(target)) {
                                    if (e == nullptr) {
                                          removals.emplace_back(idx);
                                    } else {
                                          this->members[idx] = (clone) ? e->clone() : e;
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
                  if (this->l && (e == nullptr || *this->l != *e)) {
                        if (this->l->is_flag(target)) {
                              this->l = (clone) ? e->clone() : e;
                              clone = e != nullptr;
                        } else {
                              this->l->propagate_flag(target, e, clone);
                        }
                  }
                  break;
            }
            case keywords::condition:
            case keywords::condition_goto:
            case keywords::table_assign:
            case keywords::memoryset:
            case keywords::until:
            case keywords::while_: {
                  if (this->l && (!e || *this->l != *e)) {
                        if (this->l->is_flag(target)) {
                              this->l = (clone) ? e->clone() : e;
                              clone = e != nullptr;
                        } else {
                              this->l->propagate_flag(target, e, clone);
                        }
                  }
                  break;
            }
            case keywords::forloop_numeric: {
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
                  if (this->v && (e == nullptr || *this->v != *e)) {
                        if (this->v->is_flag(target)) {
                              this->v = (clone) ? e->clone() : e;
                              clone = e != nullptr;
                        } else {
                              this->v->propagate_flag(target, e, clone);
                        }
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      removals.clear();
      if (this->k != keywords::page_function_goto) {
            for (auto idx = 0u; idx < this->smembers.size(); ++idx) {
                  auto &m = this->smembers[idx];
                  if (m != nullptr && (e == nullptr || *m != *e)) {
                        if (m->is_flag(target)) {
                              if (e == nullptr) {
                                    removals.emplace_back(idx);
                              } else {
                                    this->smembers[idx] = (clone) ? e->clone() : e;
                                    clone = e != nullptr;
                              }
                        } else {
                              m->propagate_flag(target, e, clone);
                        }
                  }
            }
            for (const auto &i : removals) {
                  this->smembers.erase(this->smembers.begin() + i);
            }
            removals.clear();
      }
      for (auto idx = 0u; idx < this->tmembers.size(); ++idx) {
            auto &m = this->tmembers[idx];
            if (m != nullptr && (e == nullptr || *m != *e)) {
                  if (m->is_flag(target)) {
                        if (e == nullptr) {
                              removals.emplace_back(idx);
                        } else {
                              this->tmembers[idx] = (clone) ? e->clone() : e;
                              clone = e != nullptr;
                        }
                  } else {
                        m->propagate_flag(target, e, clone);
                  }
            }
      }
      for (const auto &i : removals) {
            this->tmembers.erase(this->tmembers.begin() + i);
      }
      return;
}
void ir_stat::propagate(const luramas_register target, const std::shared_ptr<ir_expr> &e, bool &clone) {

      std::vector<luramas_address> removals;
      if (this->r && (!e || *this->r != *e)) {
            if (this->r->is_reg(target)) {
                  this->r = (clone) ? e->clone(true, false) : e;
                  clone = e != nullptr;
            } else {
                  this->r->propagate(target, e, clone);
            }
      }
      if (this->v && (!e || *this->v != *e)) {
            if (this->v->is_reg(target)) {
                  this->v = (clone) ? e->clone(true, false) : e;
                  clone = e != nullptr;
            } else {
                  this->v->propagate(target, e, clone);
            }
      }
      switch (this->k) {
            case keywords::call:
            case keywords::stack_pop:
            case keywords::stack_push:
            case keywords::retn:
            case keywords::page_function_goto: {
                  for (auto idx = 0u; idx < this->members.size(); ++idx) {
                        if (auto &m = this->members[idx]; m && (!e || *m != *e)) {
                              if (m->is_reg(target)) {
                                    if (!e) {
                                          removals.emplace_back(idx);
                                    } else {
                                          this->members[idx] = (clone) ? e->clone(true, false) : e;
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
                  if (this->l && (!e || *this->l != *e)) {
                        if (this->l->is_reg(target)) {
                              this->l = (clone) ? e->clone(true, false) : e;
                              clone = e != nullptr;
                        } else {
                              this->l->propagate(target, e, clone);
                        }
                  }
                  break;
            }
            case keywords::condition:
            case keywords::condition_goto:
            case keywords::table_assign:
            case keywords::memoryset:
            case keywords::until:
            case keywords::while_: {
                  if (this->l && (!e || *this->l != *e)) {
                        if (this->l->is_reg(target)) {
                              this->l = (clone) ? e->clone(true, false) : e;
                              clone = e != nullptr;
                        } else {
                              this->l->propagate(target, e, clone);
                        }
                  }
                  break;
            }
            case keywords::forloop_numeric: {
                  if (this->l && (!e || *this->l != *e)) {
                        if (this->l->is_reg(target)) {
                              this->l = (clone) ? e->clone(true, false) : e;
                              clone = e != nullptr;
                        } else {
                              this->l->propagate(target, e, clone);
                        }
                  }
                  break;
            }
            case keywords::bitwrite: {
                  if (this->lba && (!e || *this->lba != *e)) {
                        if (this->lba->is_reg(target)) {
                              this->lba = (clone) ? e->clone(true, false) : e;
                              clone = e != nullptr;
                        } else {
                              this->lba->propagate(target, e, clone);
                        }
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      removals.clear();
      if (this->k != keywords::page_function_goto) {
            for (auto idx = 0u; idx < this->smembers.size(); ++idx) {
                  if (auto &m = this->smembers[idx]; m && (!e || *m != *e)) {
                        if (m->is_reg(target)) {
                              if (!e) {
                                    removals.emplace_back(idx);
                              } else {
                                    this->smembers[idx] = (clone) ? e->clone(true, false) : e;
                                    clone = e != nullptr;
                              }
                        } else {
                              m->propagate(target, e, clone);
                        }
                  }
            }
            for (const auto &i : removals) {
                  this->smembers.erase(this->smembers.begin() + i);
            }
            removals.clear();
      }
      for (auto idx = 0u; idx < this->tmembers.size(); ++idx) {
            if (auto &m = this->tmembers[idx]; m && (!e || *m != *e)) {
                  if (m->is_reg(target)) {
                        if (!e) {
                              removals.emplace_back(idx);
                        } else {
                              this->tmembers[idx] = (clone) ? e->clone(true, false) : e;
                              clone = e != nullptr;
                        }
                  } else {
                        m->propagate(target, e, clone);
                  }
            }
      }
      for (const auto &i : removals) {
            this->tmembers.erase(this->tmembers.begin() + i);
      }
      return;
}
bool ir_stat::propagate_violates(const luramas_register target) const {

      std::vector<luramas_address> removals;
      if (this->r && this->r->propagate_violates(target)) {
            return true;
      }
      if (this->v && this->v->propagate_violates(target)) {
            return true;
      }
      for (const auto &m : this->members) {
            if (m->propagate_violates(target)) {
                  return true;
            }
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  if (m->propagate_violates(target)) {
                        return true;
                  }
            }
      }
      for (const auto &m : this->tmembers) {
            if (m->propagate_violates(target)) {
                  return true;
            }
      }
      return false;
}