#include "../../ir.hpp"

/* Misc */
void ir_stat::clear_underlying_labels() {
      this->jlabel = 0u;
      this->end_label = 0u;
      this->underlying_jump = 0u;
      return;
}
void ir_stat::clear() {
      *this = ir_stat();
      return;
}

/* Count */
luramas_count ir_stat::count(const std::shared_ptr<ir_stat::ir_expr> &expr) const {

      luramas_count result = 0u;
      if (this->lba) {
            result += this->lba->count(expr);
      }
      if (this->l) {
            result += this->l->count(expr);
      }
      if (this->r) {
            result += this->r->count(expr);
      }
      if (this->v) {
            result += this->v->count(expr);
      }
      for (const auto &m : this->members) {
            if (m) {
                  result += m->count(expr);
            }
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  if (m) {
                        result += m->count(expr);
                  }
            }
      }
      for (const auto &m : this->tmembers) {
            if (m) {
                  result += m->count(expr);
            }
      }
      return result;
}
