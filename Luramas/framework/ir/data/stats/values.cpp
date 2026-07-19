#include "../../ir.hpp"

/* Exprs buffers */
void ir_stat::extract_shallow_ordered_exprs(ir_stat::ir_expr::space &buffer) const {

      if (this->l && this->k != keywords::retn) {
            buffer.emplace_back(this->l);
      }
      if (this->r) {
            buffer.emplace_back(this->r);
      }
      if (this->v) {
            buffer.emplace_back(this->v);
      }
      if (this->lba) {
            buffer.emplace_back(this->lba);
      }
      for (const auto &m : this->members) {
            buffer.emplace_back(m);
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  buffer.emplace_back(m);
            }
      }
      for (const auto &m : this->tmembers) {
            buffer.emplace_back(m);
      }
      return;
}
void ir_stat::extract_ordered_deep_exprs(ir_stat::ir_expr::space &buffer) const {

      if (this->l && this->k != keywords::retn) {
            this->l->extract_ordered_exprs(buffer);
      }
      if (this->r) {
            this->r->extract_ordered_exprs(buffer);
      }
      if (this->v) {
            this->v->extract_ordered_exprs(buffer);
      }
      if (this->lba) {
            this->lba->extract_ordered_exprs(buffer);
      }
      for (const auto &m : this->members) {
            m->extract_ordered_exprs(buffer);
      }
      if (this->k != keywords::page_function_goto) {
            for (const auto &m : this->smembers) {
                  m->extract_ordered_exprs(buffer);
            }
      }
      for (const auto &m : this->tmembers) {
            m->extract_ordered_exprs(buffer);
      }
      return;
}
void ir_stat::extract_ordered_exprs(ir_stat::ir_expr::space &buffer) const {

      if (this->l && this->k != keywords::retn) {
            buffer.emplace_back(this->l);
      }
      if (this->r) {
            buffer.emplace_back(this->r);
      }
      if (this->v) {
            buffer.emplace_back(this->v);
      }
      if (this->lba) {
            buffer.emplace_back(this->lba);
      }
      buffer.insert(buffer.end(), this->members.begin(), this->members.end());
      if (this->k != keywords::page_function_goto) {
            buffer.insert(buffer.end(), this->smembers.begin(), this->smembers.end());
      }
      buffer.insert(buffer.end(), this->tmembers.begin(), this->tmembers.end());
      return;
}
void ir_stat::extract_exprs(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer) const {

      if (this->l && this->k != keywords::retn) {
            buffer.insert(this->l);
      }
      if (this->r) {
            buffer.insert(this->r);
      }
      if (this->v) {
            buffer.insert(this->v);
      }
      buffer.insert(this->members.begin(), this->members.end());
      if (this->k != keywords::page_function_goto) {
            buffer.insert(this->smembers.begin(), this->smembers.end());
      }
      buffer.insert(this->tmembers.begin(), this->tmembers.end());
      return;
}

/* Lists buffers */
void ir_stat::extract_list(std::vector<ir_stat::ir_expr::space> &buffer) {

      if (!this->members.empty()) {
            buffer.emplace_back(this->members);
      }
      for (const auto &m : this->members) {
            m->extract_list(buffer);
      }
      if (this->k != keywords::page_function_goto && !this->smembers.empty()) {
            buffer.insert(buffer.end(), this->smembers);
            for (const auto &m : this->smembers) {
                  m->extract_list(buffer);
            }
      }
      if (this->l && this->k != keywords::retn) {
            this->l->extract_list(buffer);
      }
      if (this->r) {
            this->r->extract_list(buffer);
      }
      if (this->v) {
            this->v->extract_list(buffer);
      }
      std::vector<std::shared_ptr<ir_expr>> segment;
      for (const auto &m : this->tmembers) {
            segment.emplace_back(m);
            m->extract_list(buffer);
      }
      if (!segment.empty()) {
            buffer.emplace_back(std::move(segment));
      }
      return;
}

/* Exprs */
ir_stat::ir_expr::space ir_stat::extract_shallow_ordered_exprs() const {

      ir_stat::ir_expr::space result;
      result.reserve(LURAMAS_PREDICTED_VALUES);
      this->extract_shallow_ordered_exprs(result);
      return result;
}
ir_stat::ir_expr::space ir_stat::extract_ordered_deep_exprs() const {

      ir_stat::ir_expr::space result;
      result.reserve(LURAMAS_PREDICTED_VALUES);
      this->extract_ordered_deep_exprs(result);
      return result;
}
ir_stat::ir_expr::space ir_stat::extract_ordered_exprs() const {

      ir_stat::ir_expr::space result;
      result.reserve(LURAMAS_PREDICTED_VALUES);
      this->extract_ordered_exprs(result);
      return result;
}
boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> ir_stat::extract_exprs() const {

      boost::unordered_flat_multiset<std::shared_ptr<ir_expr>> result;
      result.reserve(LURAMAS_PREDICTED_VALUES);
      this->extract_exprs(result);
      return result;
}

/* List */
std::vector<ir_stat::ir_expr::space> ir_stat::extract_list() {

      std::vector<ir_stat::ir_expr::space> result;
      result.reserve(LURAMAS_PREDICTED_EXPRS);
      this->extract_list(result);
      return result;
}