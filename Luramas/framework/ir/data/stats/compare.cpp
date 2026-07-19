#include "../../ir.hpp"

bool ir_stat::compare(const ir_stat &other, const bool safe, const bool include_labels) const {

      if (safe) {
            if (this->is_volatile() || other.is_volatile()) {
                  return false;
            }
      }

      if (std::tie(this->k, this->c, this->b, this->table_index, this->extra_bits, this->label) !=
          std::tie(other.k, other.c, other.b, other.table_index, other.extra_bits, other.label)) {
            return false;
      }

      if (this->flags != other.flags) {
            return false;
      }

      if (include_labels) {
            if (std::tie(this->underlying_jump, this->jlabel, this->end_label, this->elif_end_label, this->elif_end_label) !=
                std::tie(other.underlying_jump, other.jlabel, other.end_label, other.elif_end_label, other.elif_end_label)) {
                  return false;
            }
      }

      const auto cmp = [&](const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &r) {
            return (l == r) || (l && r && l->compare(r, safe));
      };

      if (!cmp(this->lba, other.lba) ||
          !cmp(this->l, other.l) ||
          !cmp(this->r, other.r) ||
          !cmp(this->v, other.v)) {
            return false;
      }

      if (this->args.size() != other.args.size()) {
            return false;
      }
      auto t_it = this->args.begin();
      auto o_it = other.args.begin();
      while (t_it != this->args.end() && o_it != other.args.end()) {
            if (t_it->first != o_it->first || !t_it->second->compare(o_it->second, safe)) {
                  return false;
            }
            ++t_it;
            ++o_it;
      }

      for (const auto &[t, o] : {std::make_pair(this->parameters, other.parameters),
               std::make_pair(this->upvalues, other.upvalues),
               std::make_pair(this->members, other.members),
               std::make_pair(this->smembers, other.smembers),
               std::make_pair(this->tmembers, other.tmembers),
               std::make_pair(this->meta, other.meta)}) {
            if (t.size() != o.size() ||
                !std::equal(t.begin(), t.end(), o.begin(), cmp)) {
                  return false;
            }
      }

      return true;
}
bool ir_stat::compare(const std::shared_ptr<ir_stat> &other, const bool safe, const bool include_labels) const {
      return this->compare(*other, safe, include_labels);
}
bool ir_stat::operator==(const ir_stat &other) const {
      return this->compare(other, true);
}
bool ir_stat::operator!=(const ir_stat &other) const {
      return !(*this == other);
}