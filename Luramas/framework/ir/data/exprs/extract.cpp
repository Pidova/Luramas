#include "../../ir.hpp"

void ir_stat::ir_expr::extract_ordered_regs(luramas_registers &buffer, const bool ignore_upvalues) const {

      luramas::recursion::manager m(shared_from_this(), LURAMAS_PREDICTED_RECURSION);
      while (m) {

            const auto curr = m.curr();
            if (curr->is_k<expr_kinds::reg>() || (!ignore_upvalues && curr->is_k<expr_kinds::upvalue>())) {
                  buffer.emplace_back(curr->reg);
            }

            if (curr->l) {
                  m.push(curr->l);
            }
            if (curr->r) {
                  m.push(curr->r);
            }
            if (curr->ev) {
                  m.push(curr->ev);
            }
            if (curr->xv) {
                  m.push(curr->xv);
            }
            for (const auto &p : curr->members) {
                  m.push(p);
            }
            for (const auto &p : curr->captures) {
                  m.push(p);
            }
            for (const auto &[i, v] : curr->tmembers) {
                  if (i && curr->k != expr_kinds::page_function_call) {
                        m.push(i);
                  }
                  if (v) {
                        m.push(v);
                  }
            }
      }
      return;
}
void ir_stat::ir_expr::extract_captures(ir_stat::ir_expr::space &buffer) const {

      if (this->l) {
            this->l->extract_captures(buffer);
      }
      if (this->r) {
            this->r->extract_captures(buffer);
      }
      if (this->ev) {
            this->ev->extract_captures(buffer);
      }
      if (this->xv) {
            this->xv->extract_captures(buffer);
      }
      for (const auto &m : this->members) {
            m->extract_captures(buffer);
      }
      if (!this->captures.empty()) {
            buffer.reserve(this->captures.size());
            for (const auto &i : this->captures) {
                  buffer.emplace_back(i);
            }
      }
      for (const auto &m : this->captures) {
            m->extract_captures(buffer);
      }
      for (const auto &[i, v] : this->tmembers) {
            if (i && this->k != expr_kinds::page_function_call) {
                  i->extract_captures(buffer);
            }
            if (v) {
                  v->extract_captures(buffer);
            }
      }
      return;
}
void ir_stat::ir_expr::extract_reg_exprs(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer) {

      if (this->is_k<expr_kinds::reg>() || this->is_k<expr_kinds::upvalue>()) {
            buffer.insert(shared_from_this());
      }
      if (this->l) {
            this->l->extract_reg_exprs(buffer);
      }
      if (this->r) {
            this->r->extract_reg_exprs(buffer);
      }
      if (this->ev) {
            this->ev->extract_reg_exprs(buffer);
      }
      if (this->xv) {
            this->xv->extract_reg_exprs(buffer);
      }
      for (const auto &m : this->members) {
            m->extract_reg_exprs(buffer);
      }
      for (const auto &m : this->captures) {
            m->extract_reg_exprs(buffer);
      }
      for (const auto &[i, v] : this->tmembers) {
            if (i && this->k != expr_kinds::page_function_call) {
                  i->extract_reg_exprs(buffer);
            }
            if (v) {
                  v->extract_reg_exprs(buffer);
            }
      }
      return;
}
void ir_stat::ir_expr::extract_exprs(boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> &buffer) {

      buffer.insert(shared_from_this());
      if (this->l) {
            this->l->extract_exprs(buffer);
      }
      if (this->r) {
            this->r->extract_exprs(buffer);
      }
      if (this->ev) {
            this->ev->extract_exprs(buffer);
      }
      if (this->xv) {
            this->xv->extract_exprs(buffer);
      }
      for (const auto &m : this->members) {
            m->extract_exprs(buffer);
      }
      for (const auto &m : this->captures) {
            m->extract_exprs(buffer);
      }
      for (const auto &[i, v] : this->tmembers) {
            if (i && this->k != expr_kinds::page_function_call) {
                  i->extract_exprs(buffer);
            }
            if (v) {
                  v->extract_exprs(buffer);
            }
      }
      return;
}
void ir_stat::ir_expr::extract_exprs(boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> &buffer) {

      buffer.insert(shared_from_this());
      if (this->l) {
            this->l->extract_exprs(buffer);
      }
      if (this->r) {
            this->r->extract_exprs(buffer);
      }
      if (this->ev) {
            this->ev->extract_exprs(buffer);
      }
      if (this->xv) {
            this->xv->extract_exprs(buffer);
      }
      for (const auto &m : this->members) {
            m->extract_exprs(buffer);
      }
      for (const auto &m : this->captures) {
            m->extract_exprs(buffer);
      }
      for (const auto &[i, v] : this->tmembers) {
            if (i && this->k != expr_kinds::page_function_call) {
                  i->extract_exprs(buffer);
            }
            if (v) {
                  v->extract_exprs(buffer);
            }
      }
      return;
}
void ir_stat::ir_expr::extract_ordered_exprs(ir_stat::ir_expr::space &buffer) {

      std::vector<std::shared_ptr<ir_expr>> stack({shared_from_this()});
      stack.reserve(LURAMAS_PREDICTED_VALUES);
      while (!stack.empty()) {

            const auto node = stack.back();
            stack.pop_back();
            buffer.emplace_back(node);

            if (this->k != expr_kinds::page_function_call) {
                  for (auto it = node->tmembers.rbegin(); it != node->tmembers.rend(); ++it) {
                        if (const auto &v = it->second; v) {
                              stack.emplace_back(v);
                        }
                        if (const auto &i = it->first; i) {
                              stack.emplace_back(i);
                        }
                  }
            }
            for (auto it = node->captures.rbegin(); it != node->captures.rend(); ++it) {
                  if (const auto &v = *it; v) {
                        stack.emplace_back(v);
                  }
            }
            for (auto it = node->members.rbegin(); it != node->members.rend(); ++it) {
                  if (const auto &v = *it; v) {
                        stack.emplace_back(v);
                  }
            }
            for (const auto &v : {node->xv, node->ev, node->r, node->l}) {
                  if (v) {
                        stack.emplace_back(v);
                  }
            }
      }
      return;
}
void ir_stat::ir_expr::extract_order_of_operation_exprs(ir_stat::ir_expr::space &buffer) {

      if (this->l) {
            this->l->extract_order_of_operation_exprs(buffer);
      }
      if (this->r) {
            this->r->extract_order_of_operation_exprs(buffer);
      }
      if (this->ev) {
            this->ev->extract_order_of_operation_exprs(buffer);
      }
      if (this->xv) {
            this->xv->extract_order_of_operation_exprs(buffer);
      }
      for (const auto &m : this->members) {
            m->extract_order_of_operation_exprs(buffer);
      }
      for (const auto &m : this->captures) {
            m->extract_order_of_operation_exprs(buffer);
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if (i) {
                        i->extract_order_of_operation_exprs(buffer);
                  }
                  if (v) {
                        v->extract_order_of_operation_exprs(buffer);
                  }
            }
      }
      buffer.emplace_back(shared_from_this());
      return;
}
void ir_stat::ir_expr::extract_list(std::vector<ir_stat::ir_expr::space> &buffer) {

      if (!this->members.empty()) {
            buffer.emplace_back(this->members);
      }
      for (const auto &m : this->members) {
            m->extract_list(buffer);
      }
      if (this->l) {
            this->l->extract_list(buffer);
      }
      if (this->r) {
            this->r->extract_list(buffer);
      }
      if (this->ev) {
            this->ev->extract_list(buffer);
      }
      if (this->xv) {
            this->xv->extract_list(buffer);
      }
      if (this->k != expr_kinds::page_function_call) {
            if (!this->tmembers.empty()) {
                  std::vector<std::shared_ptr<ir_expr>> segments;
                  for (const auto &[i, v] : this->tmembers) {
                        if (i && this->k != expr_kinds::page_function_call) {
                              if (!segments.empty()) {
                                    buffer.emplace_back(std::move(segments));
                                    segments.clear();
                              }
                              i->extract_list(buffer);
                        }
                        if (v) {
                              segments.emplace_back(v);
                              v->extract_list(buffer);
                        }
                  }
                  if (!segments.empty()) {
                        buffer.emplace_back(std::move(segments));
                  }
            }
      }
      return;
}
void ir_stat::ir_expr::extract(boost::unordered_flat_multiset<std::shared_ptr<ir_expr>> &buffer, const expr_kinds k) {

      if (this->k == k) {
            buffer.insert(shared_from_this());
      }
      if (this->l) {
            this->l->extract(buffer, k);
      }
      if (this->r) {
            this->r->extract(buffer, k);
      }
      if (this->ev) {
            this->ev->extract(buffer, k);
      }
      if (this->xv) {
            this->xv->extract(buffer, k);
      }
      for (const auto &m : this->members) {
            m->extract(buffer, k);
      }
      for (const auto &m : this->captures) {
            m->extract(buffer, k);
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if (i) {
                        i->extract(buffer, k);
                  }
                  if (v) {
                        v->extract(buffer, k);
                  }
            }
      }
      return;
}
void ir_stat::ir_expr::extract_regs(boost::unordered_flat_multiset<luramas_register> &buffer, const bool ignore_upvalues) const {

      if (this->is_k<expr_kinds::reg>() || (!ignore_upvalues && this->is_k<expr_kinds::upvalue>())) {
            buffer.insert(this->reg);
      }
      if (this->l) {
            this->l->extract_regs(buffer, ignore_upvalues);
      }
      if (this->r) {
            this->r->extract_regs(buffer, ignore_upvalues);
      }
      if (this->ev) {
            this->ev->extract_regs(buffer, ignore_upvalues);
      }
      if (this->xv) {
            this->xv->extract_regs(buffer, ignore_upvalues);
      }
      for (const auto &m : this->members) {
            m->extract_regs(buffer, ignore_upvalues);
      }
      for (const auto &m : this->captures) {
            m->extract_regs(buffer, ignore_upvalues);
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if (i) {
                        i->extract_regs(buffer, ignore_upvalues);
                  }
                  if (v) {
                        v->extract_regs(buffer, ignore_upvalues);
                  }
            }
      }
      return;
}
void ir_stat::ir_expr::extract_regs(boost::unordered_flat_set<luramas_register> &buffer, const bool ignore_upvalues) const {

      if (this->is_k<expr_kinds::reg>() || (!ignore_upvalues && this->is_k<expr_kinds::upvalue>())) {
            buffer.insert(this->reg);
      }
      if (this->l) {
            this->l->extract_regs(buffer, ignore_upvalues);
      }
      if (this->r) {
            this->r->extract_regs(buffer, ignore_upvalues);
      }
      if (this->ev) {
            this->ev->extract_regs(buffer, ignore_upvalues);
      }
      if (this->xv) {
            this->xv->extract_regs(buffer, ignore_upvalues);
      }
      for (const auto &m : this->members) {
            m->extract_regs(buffer, ignore_upvalues);
      }
      for (const auto &m : this->captures) {
            m->extract_regs(buffer, ignore_upvalues);
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if (i) {
                        i->extract_regs(buffer, ignore_upvalues);
                  }
                  if (v) {
                        v->extract_regs(buffer, ignore_upvalues);
                  }
            }
      }
      return;
}
void ir_stat::ir_expr::extract(boost::unordered_flat_set<std::shared_ptr<ir_expr>> &buffer, const luramas_register target, const bool all) {

      if (this->is_reg(target) || all) {
            buffer.insert(shared_from_this());
      }
      if (this->l) {
            this->l->extract(buffer, target, all);
      }
      if (this->r) {
            this->r->extract(buffer, target, all);
      }
      if (this->ev) {
            this->ev->extract(buffer, target, all);
      }
      if (this->xv) {
            this->xv->extract(buffer, target, all);
      }
      for (const auto &m : this->captures) {
            m->extract(buffer, target, all);
      }
      for (const auto &m : this->members) {
            m->extract(buffer, target, all);
      }
      if (this->k != expr_kinds::page_function_call) {
            for (const auto &[i, v] : this->tmembers) {
                  if (i) {
                        i->extract(buffer, target, all);
                  }
                  if (v) {
                        v->extract(buffer, target, all);
                  }
            }
      }
      return;
}
void ir_stat::ir_expr::extract_shallow_ordered_exprs(ir_stat::ir_expr::space &buffer) const {

      if (this->l) {
            buffer.emplace_back(this->l);
      }
      if (this->r) {
            buffer.emplace_back(this->r);
      }
      if (this->ev) {
            buffer.emplace_back(this->ev);
      }
      if (this->xv) {
            buffer.emplace_back(this->xv);
      }
      for (const auto &p : this->members) {
            buffer.emplace_back(p);
      }
      for (const auto &p : this->captures) {
            buffer.emplace_back(p);
      }
      for (const auto &[i, v] : this->tmembers) {
            if (i && this->k != expr_kinds::page_function_call) {
                  buffer.emplace_back(i);
            }
            if (v) {
                  buffer.emplace_back(v);
            }
      }
      return;
}

luramas_registers ir_stat::ir_expr::extract_ordered_regs() const {

      luramas_registers result;
      result.reserve(LURAMAS_PREDICTED_REGS);
      this->extract_ordered_regs(result);
      return result;
}
ir_stat::ir_expr::space ir_stat::ir_expr::extract_shallow_ordered_exprs() const {

      ir_stat::ir_expr::space result;
      result.reserve(LURAMAS_PREDICTED_ALL_EXPRS);
      this->extract_shallow_ordered_exprs(result);
      return result;
}
boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> ir_stat::ir_expr::extract_reg_exprs() {

      boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> result;
      result.reserve(LURAMAS_PREDICTED_REGS);
      this->extract_reg_exprs(result);
      return result;
}
boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> ir_stat::ir_expr::extract_exprs() {

      boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> result;
      result.reserve(LURAMAS_PREDICTED_EXPRS);
      this->extract_exprs(result);
      return result;
}
ir_stat::ir_expr::space ir_stat::ir_expr::extract_ordered_exprs() {

      ir_stat::ir_expr::space result;
      result.reserve(LURAMAS_PREDICTED_EXPRS);
      this->extract_ordered_exprs(result);
      return result;
}
ir_stat::ir_expr::space ir_stat::ir_expr::extract_order_of_operation_exprs() {

      ir_stat::ir_expr::space result;
      result.reserve(LURAMAS_PREDICTED_EXPRS);
      this->extract_order_of_operation_exprs(result);
      return result;
}
std::vector<ir_stat::ir_expr::space> ir_stat::ir_expr::extract_list() {

      std::vector<std::vector<std::shared_ptr<ir_expr>>> result;
      result.reserve(LURAMAS_PREDICTED_EXPRS);
      this->extract_list(result);
      return result;
}
boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> ir_stat::ir_expr::extract(const expr_kinds k) {

      boost::unordered_flat_multiset<std::shared_ptr<ir_stat::ir_expr>> result;
      result.reserve(LURAMAS_PREDICTED_EXPRS);
      this->extract(result, k);
      return result;
}
boost::unordered_flat_multiset<luramas_register> ir_stat::ir_expr::extract_regs(const bool ignore_upvalues) const {

      boost::unordered_flat_multiset<luramas_register> result;
      result.reserve(LURAMAS_PREDICTED_REGS);
      this->extract_regs(result, ignore_upvalues);
      return result;
}
boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> ir_stat::ir_expr::extract(const luramas_register target, const bool all) {

      boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> result;
      result.reserve(LURAMAS_PREDICTED_EXPRS);
      this->extract(result, target, all);
      return result;
}
luramas_int ir_stat::ir_expr::extract_integral() const {

      return this->n;
}
luramas_int_base ir_stat::ir_expr::extract_integral_base() const {

      return this->n.extract_base();
}