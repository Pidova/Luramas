#include "../../ir.hpp"

void ir_stat::ir_expr::replace(const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &exprs) {
      for (auto *i : {&this->l, &this->r, &this->ev, &this->xv}) {
            if (*i) {
                  if ((*i)->is_register_reference()) {
                        if (auto it = exprs.find((*i)->reg); it != exprs.end()) {
                              *i = it->second;
                        }
                  } else {
                        (*i)->replace(exprs);
                  }
            }
      }
      for (auto &m : this->members) {
            if (m) {
                  if (m->is_register_reference()) {
                        if (auto it = exprs.find(m->reg); it != exprs.end()) {
                              m = it->second;
                        }
                  } else {
                        m->replace(exprs);
                  }
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (auto &[i, v] : this->tmembers) {
                  if (i) {
                        if (i->is_register_reference()) {
                              if (auto it = exprs.find(i->reg); it != exprs.end()) {
                                    i = it->second;
                              }
                        } else {
                              i->replace(exprs);
                        }
                  }
                  if (v) {
                        if (v->is_register_reference()) {
                              if (auto it = exprs.find(v->reg); it != exprs.end()) {
                                    v = it->second;
                              }
                        } else {
                              v->replace(exprs);
                        }
                  }
            }
      }
      return;
}

void ir_stat::ir_expr::shallow_replace(const boost::unordered_flat_map<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat::ir_expr>> &exprs) {
      for (auto *i : {&this->l, &this->r, &this->ev, &this->xv}) {
            if (auto it = exprs.find(*i); it != exprs.end()) {
                  *i = it->second;
            }
      }
      for (auto &m : this->members) {
            if (auto it = exprs.find(m); it != exprs.end()) {
                  m = it->second;
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (auto &[i, v] : this->tmembers) {
                  if (auto it = exprs.find(i); it != exprs.end()) {
                        i = it->second;
                  }
                  if (auto it = exprs.find(v); it != exprs.end()) {
                        v = it->second;
                  }
            }
      }
      return;
}
void ir_stat::ir_expr::shallow_replace(const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &exprs) {
      for (auto *i : {&this->l, &this->r, &this->ev, &this->xv}) {
            if (*i && (*i)->is_register_reference()) {
                  if (auto it = exprs.find((*i)->reg); it != exprs.end()) {
                        *i = it->second;
                  }
            }
      }
      for (auto &m : this->members) {
            if (m && m->is_register_reference()) {
                  if (auto it = exprs.find(m->reg); it != exprs.end()) {
                        m = it->second;
                  }
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (auto &[i, v] : this->tmembers) {
                  if (i && i->is_register_reference()) {
                        if (auto it = exprs.find(i->reg); it != exprs.end()) {
                              i = it->second;
                        }
                  }
                  if (v && v->is_register_reference()) {
                        if (auto it = exprs.find(v->reg); it != exprs.end()) {
                              v = it->second;
                        }
                  }
            }
      }
      return;
}

void ir_stat::ir_expr::curr_replace(const luramas_int &n) {

      if (this->tk == tkind::lura_int) {
            this->n = n;
      }
      return;
}