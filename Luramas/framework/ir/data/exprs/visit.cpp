#include "../../ir.hpp"

std::shared_ptr<ir_stat::ir_expr> ir_stat::ir_expr::visit_parent(const std::shared_ptr<ir_expr> &e) {

      for (const auto &m : {std::cref(this->l), std::cref(this->r), std::cref(this->ev), std::cref(this->xv)}) {
            if (m.get()) {
                  if (*m.get() == *e) {
                        return shared_from_this();
                  }
                  if (const auto visit = m.get()->visit_parent(e); visit) {
                        return visit;
                  }
            }
      }
      for (const auto &m : this->members) {
            if (m) {
                  if (*m == *e) {
                        return shared_from_this();
                  }
                  if (const auto visit = m->visit_parent(e); visit) {
                        return visit;
                  }
            }
      }
      for (const auto &m : this->captures) {
            if (m) {
                  if (*m == *e) {
                        return shared_from_this();
                  }
                  if (const auto visit = m->visit_parent(e); visit) {
                        return visit;
                  }
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if (i) {
                        if (*i == *e) {
                              return shared_from_this();
                        }
                        if (const auto visit = i->visit_parent(e); visit) {
                              return visit;
                        }
                  }
                  if (v) {
                        if (*v == *e) {
                              return shared_from_this();
                        }
                        if (const auto visit = v->visit_parent(e); visit) {
                              return visit;
                        }
                  }
            }
      }
      return nullptr;
}
