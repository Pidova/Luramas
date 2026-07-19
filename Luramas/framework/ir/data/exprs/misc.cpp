#include "../../ir.hpp"

/* Transform */
std::shared_ptr<ir_stat> ir_stat::ir_expr::transform() const {

      auto result = std::make_shared<ir_stat>();
      switch (this->k) {
            case expr_kinds::call: {

                  result->emit_call(this->l);
                  for (const auto &m : this->members) {
                        result->emit_arg(m);
                  }
                  break;
            }
            case expr_kinds::page_function_call: {

                  result->emit_page_function_call(this->r, this->ev, this->xv, this->l);
                  for (const auto &m : this->members) {
                        result->emit_arg(m);
                  }
                  break;
            }
            default: {
                  return nullptr;
            }
      }
      return result;
}

/* Count */
luramas_count ir_stat::ir_expr::count(const std::shared_ptr<ir_stat::ir_expr> &expr) const {

      luramas_count result = 0u;
      result += (*this == *expr);
      if (this->l) {
            result += this->l->count(expr);
      }
      if (this->r) {
            result += this->r->count(expr);
      }
      if (this->ev) {
            result += this->ev->count(expr);
      }
      if (this->xv) {
            result += this->xv->count(expr);
      }
      for (const auto &m : this->captures) {
            if (m) {
                  result += m->count(expr);
            }
      }
      for (const auto &m : this->members) {
            if (m) {
                  result += m->count(expr);
            }
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if (i) {
                        result += i->count(expr);
                  }
                  if (v) {
                        result += v->count(expr);
                  }
            }
      }
      return result;
}

void ir_stat::ir_expr::clear() {
      *this = ir_expr();
      return;
}