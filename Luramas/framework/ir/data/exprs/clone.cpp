#include "../../ir.hpp"

/* Cloning */
void ir_stat::ir_expr::clone(std::shared_ptr<ir_expr> &buffer, const bool deep, const bool regs) const {

      buffer->flags.clone(this->flags);

      /* Identifiers */
      buffer->u = this->u;
      buffer->b = this->b;
      buffer->k = this->k;
      buffer->tk = this->tk;
      buffer->e = this->e;
      buffer->rk = this->rk;

      /* Values */
      buffer->v = this->v;
      buffer->n = this->n;
      buffer->bv = this->bv;
      buffer->reg = this->reg;
      buffer->amount = this->amount;
      if (this->non_native) {
            buffer->non_native = this->non_native->clone();
      }
      if (this->xtype) {
            buffer->xtype = this->xtype->clone();
      }

      if (const auto &m = this->l; m) {
            buffer->l = deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m;
      }
      if (const auto &m = this->r; m) {
            buffer->r = deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m;
      }
      if (const auto &m = this->ev; m) {
            buffer->ev = deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m;
      }
      if (const auto &m = this->xv; m) {
            buffer->xv = deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m;
      }

      for (const auto &m : this->members) {
            buffer->members.emplace_back(deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m);
      }
      for (const auto &m : this->captures) {
            buffer->captures.emplace_back(deep && (regs || !m->is_register_reference()) ? m->clone(deep, regs) : m);
      }
      for (const auto &[i, v] : this->tmembers) {
            buffer->tmembers.emplace_back(std::make_pair(i ? (deep && (regs || !i->is_register_reference()) ? i->clone(deep, regs) : i) : nullptr, v ? (deep && (regs || !v->is_register_reference()) ? v->clone(deep, regs) : v) : nullptr));
      }
      for (const auto &c : this->closure) {
            buffer->closure.emplace_back(deep ? c->clone(deep, regs) : c);
      }
      return;
}
std::shared_ptr<ir_stat::ir_expr> ir_stat::ir_expr::clone(const bool deep, const bool regs) const {
      if (deep && !regs && this->is_register_reference()) {
            return const_cast<ir_expr *>(this)->shared_from_this();
      }
      auto result = std::make_shared<ir_expr>();
      this->clone(result, deep, regs);
      return result;
}