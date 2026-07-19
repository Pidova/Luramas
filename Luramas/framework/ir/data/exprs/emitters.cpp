#include "../../ir.hpp"

void ir_stat::ir_expr::emit_upvalue(const luramas_register r, const luramas_vregister vreg) {
      this->k = expr_kinds::upvalue;
      this->reg = r;
      this->vreg = vreg;
      return;
}
void ir_stat::ir_expr::emit_reg(const luramas_register r) {
      this->k = expr_kinds::reg;
      this->reg = r;
      return;
}
void ir_stat::ir_expr::emit_closure(const ir_stat::space &closure) {
      this->k = expr_kinds::closure;
      this->closure = closure;
      return;
}
void ir_stat::ir_expr::emit_capture(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::operand::upvalue_kind kind) {
      l->flags.fcapture_kind = kind;
      l->flags.fcaptured = true;
      this->k = expr_kinds::closure;
      this->captures.emplace_back(l);
      return;
}
void ir_stat::ir_expr::emit_reg_arg(const luramas_register r) {
      this->k = expr_kinds::reg;
      this->rk = expr_reg_kinds::arg;
      this->reg = r;
      return;
}
void ir_stat::ir_expr::emit_global(const std::string &g) {
      this->k = expr_kinds::nothing;
      this->tk = tkind::global;
      this->v = g;
      return;
}
void ir_stat::ir_expr::emit_object(const std::shared_ptr<luramas::ir::types::object::type> &obj) {
      this->k = expr_kinds::nothing;
      this->tk = tkind::object;
      this->non_native = obj;
      return;
}
void ir_stat::ir_expr::emit_kvalue(const std::string &k) {
      this->k = expr_kinds::nothing;
      this->tk = tkind::kvalue;
      this->v = k;
      return;
}
void ir_stat::ir_expr::emit_flag(const std::shared_ptr<ir_expr> &id) {
      this->k = expr_kinds::flag;
      this->r = id;
      return;
}
void ir_stat::ir_expr::emit_str(const std::string &s) {
      this->k = expr_kinds::nothing;
      this->tk = tkind::string;
      this->v = s;
      return;
}
void ir_stat::ir_expr::emit_boolean(const bool b) {
      this->k = expr_kinds::nothing;
      this->tk = tkind::boolean;
      this->bv = b;
      return;
}
void ir_stat::ir_expr::emit_blank_lvalue() {
      this->k = expr_kinds::blank_lvalue;
      return;
}
void ir_stat::ir_expr::emit_int(const luramas_int &i) {
      this->k = expr_kinds::nothing;
      this->tk = tkind::lura_int;
      this->n = i;
      return;
}
void ir_stat::ir_expr::emit_extpr(const luramas_int &i) {
      this->k = expr_kinds::nothing;
      this->tk = tkind::extpr;
      this->n = i;
      return;
}
void ir_stat::ir_expr::emit_stack(const std::intptr_t i) {
      this->k = expr_kinds::nothing;
      this->tk = tkind::stack;
      this->n = i;
      return;
}
void ir_stat::ir_expr::emit_controller() {
      this->k = expr_kinds::nothing;
      this->tk = tkind::controller;
      return;
}
void ir_stat::ir_expr::emit_none() {
      this->k = expr_kinds::nothing;
      this->tk = tkind::none_obj;
      return;
}
void ir_stat::ir_expr::emit_call(const std::shared_ptr<ir_expr> &call) {
      this->k = expr_kinds::call;
      this->l = call;
      return;
}
void ir_stat::ir_expr::emit_arg(const std::shared_ptr<ir_expr> &arg) {
      this->k = expr_kinds::call;
      this->members.emplace_back(arg);
      return;
}
void ir_stat::ir_expr::emit_vcall(const std::shared_ptr<ir_expr> &vcall) {
      this->flags.fvcall = true;
      this->k = expr_kinds::call;
      this->l = vcall;
      return;
}
void ir_stat::ir_expr::emit_varg(const std::shared_ptr<ir_expr> &varg) {
      this->flags.fvcall = true;
      this->k = expr_kinds::call;
      this->members.emplace_back(varg);
      return;
}
void ir_stat::ir_expr::emit_variadic() {
      this->tk = tkind::variadic;
      return;
}
void ir_stat::ir_expr::emit_arith(const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &r, luramas::il::arch::data::bin_kinds b) {
      this->k = expr_kinds::arith;
      this->l = l;
      this->r = r;
      this->b = b;
      return;
}
void ir_stat::ir_expr::emit_self(const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &r) {
      this->k = expr_kinds::self;
      this->l = l;
      this->r = r;
      return;
}
void ir_stat::ir_expr::emit_ternary(const std::shared_ptr<ir_expr> &cond_l, const std::shared_ptr<ir_expr> &cond_r, luramas::il::arch::data::bin_kinds b, const std::shared_ptr<ir_expr> &then_v, const std::shared_ptr<ir_expr> &else_v) {
      this->k = expr_kinds::ternary;
      this->l = cond_l;
      this->r = cond_r;
      this->b = b;
      this->ev = then_v;
      this->xv = else_v;
      return;
}
void ir_stat::ir_expr::emit_ternary(const std::shared_ptr<ir_expr> &cond, const std::shared_ptr<ir_expr> &then_v, const std::shared_ptr<ir_expr> &else_v) {
      this->k = expr_kinds::ternary;
      this->l = cond;
      this->ev = then_v;
      this->xv = else_v;
      return;
}
void ir_stat::ir_expr::emit_idx(const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &r) {
      this->k = expr_kinds::idx;
      this->l = l;
      this->r = r;
      return;
}
void ir_stat::ir_expr::emit_cond(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds b, const std::shared_ptr<ir_expr> &r) {
      this->k = expr_kinds::condition;
      this->l = l;
      this->r = r;
      this->b = b;
      return;
}
void ir_stat::ir_expr::emit_concat(const std::shared_ptr<ir_expr> &v) {
      this->k = expr_kinds::concat;
      this->members.emplace_back(v);
      return;
}
void ir_stat::ir_expr::emit_unpack(const std::shared_ptr<ir_expr> &v, const luramas_address amount) {
      this->k = expr_kinds::unpack;
      this->l = v;
      this->amount = amount;
      return;
}
void ir_stat::ir_expr::emit_table_set(const std::shared_ptr<ir_expr> &v, const std::shared_ptr<ir_expr> &i) {
      this->tk = tkind::table;
      this->tmembers.emplace_back(std::make_pair(i, v));
      return;
}
void ir_stat::ir_expr::emit_table_get(const std::shared_ptr<ir_expr> &v, const std::shared_ptr<ir_expr> &i) {
      this->k = expr_kinds::idx;
      this->tmembers.emplace_back(std::make_pair(i, v));
      return;
}
void ir_stat::ir_expr::emit_table() {
      this->tk = tkind::table;
      return;
}
void ir_stat::ir_expr::emit_unary(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds u) {
#ifdef LURAMAS_ECC
      if (!luramas::il::arch::data::is_kinds::unary(u)) {
            luramas::error::unexpected_error("Unary");
      }
#endif // LURAMAS_ECC
      this->k = expr_kinds::unary;
      this->u = u;
      this->l = l;
      return;
}
void ir_stat::ir_expr::emit_cond(const std::shared_ptr<ir_expr> &l, const expr_logical e, const luramas::il::arch::data::bin_kinds b, const std::shared_ptr<ir_expr> &r) {
      this->k = expr_kinds::condition;
      this->b = b;
      this->e = e;
      this->l = l;
      this->r = r;
      return;
}
void ir_stat::ir_expr::emit_bitread(const std::shared_ptr<ir_expr> &value, const std::shared_ptr<ir_expr> &min, const std::shared_ptr<ir_expr> &max, const std::shared_ptr<luramas::ir::types::object::type> &non_native) {
      this->k = expr_kinds::bitread;
      this->l = value;
      this->r = min;
      this->ev = max;
      this->non_native = non_native;
      return;
}
void ir_stat::ir_expr::emit_bitwrite(const std::shared_ptr<ir_expr> &value, const std::shared_ptr<ir_expr> &lvalue, const std::shared_ptr<ir_expr> &min, const std::shared_ptr<ir_expr> &max, const std::shared_ptr<luramas::ir::types::object::type> &non_native) {
      this->k = expr_kinds::bitwrite;
      this->l = value;
      this->r = lvalue;
      this->ev = min;
      this->xv = max;
      this->non_native = non_native;
      return;
}
void ir_stat::ir_expr::emit_memoryread(const std::shared_ptr<ir_expr> &target, const luramas_bitwidth set_bits, const std::shared_ptr<ir_expr> &offset) {
      this->k = expr_kinds::memoryread;
      this->l = target;
      this->r = offset;
      this->non_native = luramas::ir::types::generate::basic(set_bits, false, 0u);
      return;
}
void ir_stat::ir_expr::emit_cast(const std::shared_ptr<luramas::ir::types::object::type> &object, const std::shared_ptr<ir_expr> &value) {
      this->k = expr_kinds::cast;
      this->non_native = object;
      this->l = value;
      return;
}
void ir_stat::ir_expr::emit_page_function_call(const std::shared_ptr<ir_expr> &id, const std::shared_ptr<ir_expr> &insertion_where, const std::shared_ptr<ir_expr> &value) {
      this->k = expr_kinds::page_function_call;
      this->r = id;
      this->ev = insertion_where;
      this->xv = value;
      return;
}
void ir_stat::ir_expr::emit_register_annotation(const std::string &str) {
      this->k = expr_kinds::reg;
      this->v = str;
      return;
}
void ir_stat::ir_expr::emit_nothing() {
      this->k = expr_kinds::nothing;
      return;
}
