#include "../../ir.hpp"

bool ir_stat::ir_expr::contains(const expr_kinds k) const {
      if (this->k == k) {
            return true;
      }
      if (this->l && this->l->contains(k)) {
            return true;
      }
      if (this->r && this->r->contains(k)) {
            return true;
      }
      if (this->ev && this->ev->contains(k)) {
            return true;
      }
      if (this->xv && this->xv->contains(k)) {
            return true;
      }
      for (const auto &m : this->members) {
            if (m->contains(k)) {
                  return true;
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if ((i && i->contains(k)) || (v && v->contains(k))) {
                        return true;
                  }
            }
      }
      return false;
}
bool ir_stat::ir_expr::contains(const tkind tk) const {
      if (this->tk == tk) {
            return true;
      }
      if (this->l && this->l->contains(tk)) {
            return true;
      }
      if (this->r && this->r->contains(tk)) {
            return true;
      }
      if (this->ev && this->ev->contains(tk)) {
            return true;
      }
      if (this->xv && this->xv->contains(tk)) {
            return true;
      }
      for (const auto &m : this->members) {
            if (m->contains(tk)) {
                  return true;
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if ((i && i->contains(tk)) || (v && v->contains(tk))) {
                        return true;
                  }
            }
      }
      return false;
}
bool ir_stat::ir_expr::contains(const luramas_register r) const {
      if (this->is_reg(r)) {
            return true;
      }
      if (this->l && this->l->contains(r)) {
            return true;
      }
      if (this->r && this->r->contains(r)) {
            return true;
      }
      if (this->ev && this->ev->contains(r)) {
            return true;
      }
      if (this->xv && this->xv->contains(r)) {
            return true;
      }
      for (const auto &m : this->members) {
            if (m->contains(r)) {
                  return true;
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if ((i && i->contains(r)) || (v && v->contains(r))) {
                        return true;
                  }
            }
      }
      return false;
}
bool ir_stat::ir_expr::contains(const std::shared_ptr<ir_stat::ir_expr> &expr) const {
      if (*this == *expr) {
            return true;
      }
      if (this->l && this->l->contains(expr)) {
            return true;
      }
      if (this->r && this->r->contains(expr)) {
            return true;
      }
      if (this->ev && this->ev->contains(expr)) {
            return true;
      }
      if (this->xv && this->xv->contains(expr)) {
            return true;
      }
      for (const auto &m : this->captures) {
            if (m && m->contains(expr)) {
                  return true;
            }
      }
      for (const auto &m : this->members) {
            if (m && m->contains(expr)) {
                  return true;
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if ((i && i->contains(expr)) || (v && v->contains(expr))) {
                        return true;
                  }
            }
      }
      return false;
}
bool ir_stat::ir_expr::contains_volatile() const {
      if (this->is_volatile()) {
            return true;
      }
      if (this->l && this->l->contains_volatile()) {
            return true;
      }
      if (this->r && this->r->contains_volatile()) {
            return true;
      }
      if (this->ev && this->ev->contains_volatile()) {
            return true;
      }
      if (this->xv && this->xv->contains_volatile()) {
            return true;
      }
      for (const auto &m : this->members) {
            if (m->contains_volatile()) {
                  return true;
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if ((i && i->contains_volatile()) || (v && v->contains_volatile())) {
                        return true;
                  }
            }
      }
      return false;
}
bool ir_stat::ir_expr::contains_upvalue() const {
      if (this->is_k<expr_kinds::upvalue>()) {
            return true;
      }
      if (this->l && this->l->contains_upvalue()) {
            return true;
      }
      if (this->r && this->r->contains_upvalue()) {
            return true;
      }
      if (this->ev && this->ev->contains_upvalue()) {
            return true;
      }
      if (this->xv && this->xv->contains_upvalue()) {
            return true;
      }
      for (const auto &m : this->members) {
            if (m->contains_upvalue()) {
                  return true;
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if ((i && i->contains_upvalue()) || (v && v->contains_upvalue())) {
                        return true;
                  }
            }
      }
      return false;
}