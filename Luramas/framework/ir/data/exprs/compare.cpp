#include "../../ir.hpp"

bool ir_stat::ir_expr::compare(const ir_expr &other, const bool safe, const bool nest) const {

      if (this->flags.fglobal_wild || other.flags.fglobal_wild) {
            return true;
      }
      if (safe) {
            if (this->is_volatile() || other.is_volatile()) {
                  return false;
            }
      }

      if (std::tie(this->u, this->b, this->k, this->tk, this->e, this->rk, this->n, this->bv, this->reg, this->vreg, this->amount, this->v) !=
          std::tie(other.u, other.b, other.k, other.tk, other.e, other.rk, other.n, other.bv, other.reg, other.vreg, other.amount, other.v)) {
            return false;
      }

      if (this->flags != other.flags) {
            return false;
      }

      const auto cmp = [&](const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &r) {
            return (l == r) || (l && r && l->compare(r, safe));
      };
      if (nest && (!cmp(this->l, other.l) || !cmp(this->r, other.r) ||
                      !cmp(this->ev, other.ev) || !cmp(this->xv, other.xv))) {
            return false;
      }

      if (this->members.size() != other.members.size() || (nest &&
                                                              !std::equal(this->members.begin(), this->members.end(), other.members.begin(), cmp))) {
            return false;
      }

      if (nest &&
          !(this->non_native == other.non_native || (this->non_native && other.non_native && this->non_native->compare(*other.non_native))) &&
          !(this->xtype == other.xtype || (this->xtype && other.xtype && this->xtype->compare(*other.xtype)))) {
            return false;
      }
      const auto t_eql = [&](const auto &l, const auto &r) {
            return cmp(l.first, r.first) && cmp(l.second, r.second);
      };
      return this->tmembers.size() == other.tmembers.size() && (!nest || std::equal(this->tmembers.begin(), this->tmembers.end(), other.tmembers.begin(), t_eql));
}
bool ir_stat::ir_expr::compare(const std::shared_ptr<ir_expr> &other, const bool safe, const bool nest) const {
      return other.get() == this || (other && this->compare(*other, safe));
}
bool ir_stat::ir_expr::operator==(const ir_expr &other) const {
      return this->compare(other, true);
}
bool ir_stat::ir_expr::operator!=(const ir_expr &other) const {
      return !(*this == other);
}