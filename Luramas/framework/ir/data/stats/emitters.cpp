#include "../../ir.hpp"

void ir_stat::emit_label(const luramas_address &l) {
      this->k = keywords::label;
      this->label = l;
      return;
}
void ir_stat::emit_end() {
      this->k = keywords::end;
      return;
}
void ir_stat::emit_definition() {
      this->k = keywords::definition;
      return;
}
void ir_stat::emit_parameters() {
      switch (this->k) {
            case keywords::definition: {

                  for (const auto &i : this->args) {
                        this->parameters.emplace_back(i.second);
                  }
                  std::sort(this->parameters.begin(), this->parameters.end(), [](const auto &l, const auto &r) {
                        if (l->vreg != -1 && r->vreg != -1) {
                              return l->vreg < r->vreg;
                        }
                        if (l->vreg == -1) {
                              return l->reg < r->reg;
                        }
                        if (r->vreg == -1) {
                              return l->vreg < r->reg;
                        }
                        return l->vreg < r->vreg;
                  });
                  break;
            }
            default: {
                  break;
            }
      }
      return;
}
void ir_stat::emit_definition(const luramas_register reg, const std::shared_ptr<ir_expr> &arg) {
      this->k = keywords::definition;
      if (arg) {
            this->args.try_emplace(reg, arg);
      }
      this->flags.funsafe = true;
      return;
}
void ir_stat::emit_upv_definition(const std::shared_ptr<ir_expr> &upv) {
      this->k = keywords::definition;
      if (upv) {
            this->upvalues.emplace_back(upv);
      }
      return;
}
void ir_stat::emit_repeat() {
      this->k = keywords::repeat;
      return;
}
void ir_stat::emit_create_stack(const std::shared_ptr<ir_expr> &l) {
      this->k = keywords::create_stack;
      this->l = l;
      return;
}
void ir_stat::emit_until(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds b, const std::shared_ptr<ir_expr> &r) {
      if (!l) {
            return;
      }
      this->k = keywords::until;
      this->l = l;
      this->r = r;
      this->b = b;
      return;
}
void ir_stat::emit_while(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds b, const std::shared_ptr<ir_expr> &r) {
      if (!l) {
            return;
      }
      this->k = keywords::while_;
      this->l = l;
      this->r = r;
      this->b = b;
      return;
}
void ir_stat::emit_break() {
      this->k = keywords::break_;
      return;
}
void ir_stat::emit_continue() {
      this->k = keywords::continue_;
      return;
}
void ir_stat::emit_call(const std::shared_ptr<ir_expr> &c) {
      if (!c) {
            return;
      }
      this->k = keywords::call;
      this->l = c;
      return;
}
void ir_stat::emit_page_function_call(const std::shared_ptr<ir_expr> &id, const std::shared_ptr<ir_expr> &insertion_where, const std::shared_ptr<ir_expr> &value, const std::shared_ptr<ir_expr> &controller) {
      if (!id) {
            return;
      }
      this->k = keywords::page_function_goto;
      this->pfk = page_function_goto_kind::call;
      this->r = id;
      this->l = insertion_where;
      this->lba = value;
      this->v = controller;
      return;
}
void ir_stat::emit_page_function_jump(const std::shared_ptr<ir_expr> &id) {
      if (!id) {
            return;
      }
      this->k = keywords::page_function_goto;
      this->pfk = page_function_goto_kind::jump;
      this->r = id;
      return;
}
void ir_stat::emit_virtual_function_call(const luramas_id key) {
      this->k = keywords::call;
      this->flags.fsynthetic = true;
      auto call = std::make_shared<ir_expr>();
      call->emit_int(key);
      this->l = call;
      return;
}
void ir_stat::emit_arg(const std::shared_ptr<ir_expr> &c) {
      if (c == nullptr) {
            return;
      }
      this->members.emplace_back(c);
      return;
}
void ir_stat::emit_assignment(const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &r) {
      this->k = keywords::assignment;
      this->l = l;
      this->r = r;
      return;
}
void ir_stat::emit_page_function_closure(const std::shared_ptr<ir_expr> &id, const std::shared_ptr<ir_expr> &closure) {
      this->k = keywords::page_function_closure;
      this->r = id;
      closure->flags.flegacy_page = true;
      this->v = closure;
      return;
}
void ir_stat::emit_page_function_start(const std::shared_ptr<ir_expr> &id) {
      this->k = keywords::page_function_start;
      this->r = id;
      return;
}
void ir_stat::emit_page_function_end(const std::shared_ptr<ir_expr> &id) {
      this->k = keywords::page_function_end;
      this->r = id;
      return;
}
void ir_stat::emit_page_function_pass() {
      this->k = keywords::page_function_pass;
      this->flags.funsafe = true;
      return;
}
void ir_stat::emit_isolate() {
      this->k = keywords::isolate;
      return;
}
void ir_stat::emit_setflag(const std::shared_ptr<ir_stat::ir_expr> &flag, const std::shared_ptr<ir_stat::ir_expr> &source) {
      if (flag && !flag->is_integral()) {
            luramas::error::error("Flag should be an ID");
      }
      this->k = keywords::set_flag;
      this->l = flag;
      this->r = source;
      return;
}
void ir_stat::emit_memoryset(const std::shared_ptr<ir_expr> &target, const std::shared_ptr<ir_expr> &source, const luramas_address set_bits, const std::shared_ptr<ir_expr> &offset) {
      this->k = keywords::memoryset;
      this->l = target;
      this->v = offset;
      this->r = source;
      this->extra_bits = set_bits;
      return;
}
void ir_stat::emit_switch(const std::shared_ptr<ir_expr> &cmp) {
      this->k = keywords::switch_;
      this->l = cmp;
      return;
}
void ir_stat::emit_switch_case(const std::shared_ptr<ir_expr> &switch_case) {
      this->k = keywords::switch_case;
      this->l = switch_case;
      return;
}
void ir_stat::emit_switch_default_case() {
      this->k = keywords::switch_default;
      return;
}
void ir_stat::emit_for_loop_init() {
      this->k = keywords::for_loop_init;
      return;
}
void ir_stat::emit_tab_assign(const std::shared_ptr<ir_expr> &t, const std::shared_ptr<ir_expr> &idx, const std::shared_ptr<ir_expr> &v) {
      this->k = keywords::table_assign;
      this->l = std::make_shared<ir_stat::ir_expr>();
      this->l->emit_idx(t, idx);
      this->r = v;
      return;
}
void ir_stat::emit_tab_setlist(const std::shared_ptr<ir_expr> &t, const std::shared_ptr<ir_expr> &v) {
      this->k = keywords::table_setlist;
      this->l = t;
      if (v) {
            this->tmembers.emplace_back(v);
      }
      return;
}
void ir_stat::emit_mul_lv(const std::shared_ptr<ir_expr> &l) {
      if (l == nullptr) {
            return;
      }
      this->k = keywords::assignment;
      this->members.emplace_back(l);
      return;
}
void ir_stat::emit_return(const std::shared_ptr<ir_expr> &c) {
      this->k = keywords::retn;
      if (c) {
            this->members.emplace_back(c);
      }
      return;
}
void ir_stat::emit_return(const ir_stat::ir_expr::space &v) {
      this->k = keywords::retn;
      this->members = v;
      return;
}
void ir_stat::emit_return(const std::shared_ptr<ir_expr> &read_loc, const ir_stat::ir_expr::space &v) {
      this->k = keywords::retn;
      this->members = v;
      this->l = read_loc;
      return;
}
void ir_stat::emit_return(const std::shared_ptr<ir_expr> &read_loc, const std::shared_ptr<ir_stat::ir_expr> &c) {
      this->k = keywords::retn;
      if (c) {
            this->members.emplace_back(c);
      }
      this->l = read_loc;
      return;
}
void ir_stat::emit_forloop_numeric(const std::shared_ptr<ir_expr> &lr, const std::shared_ptr<ir_expr> &init, const std::shared_ptr<ir_expr> &max, const std::shared_ptr<ir_expr> &step) {
      this->k = keywords::forloop_numeric;
      this->l = init;
      this->r = max;
      this->v = step;
      this->lba = lr;
      return;
}
void ir_stat::emit_forloop_generic(const std::shared_ptr<ir_expr> &var, const std::shared_ptr<ir_expr> &v) {
      this->k = keywords::forloop_generic;
      if (var != nullptr) {
            this->members.emplace_back(var);
      }
      if (v != nullptr) {
            this->smembers.emplace_back(v);
      }
      return;
}
void ir_stat::emit_forloop_meta(const std::shared_ptr<ir_expr> &min, const std::shared_ptr<ir_expr> &max, const std::shared_ptr<ir_expr> &step) {
      this->k = keywords::forloop_generic;
      this->meta.emplace_back(min);
      this->meta.emplace_back(max);
      this->meta.emplace_back(step);
      return;
}
void ir_stat::emit_cond(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds b, const std::shared_ptr<ir_expr> &r) {
      this->k = keywords::condition;
      this->c = condition_kind::if_;
      this->l = l;
      this->r = r;
      this->b = b;
      return;
}
void ir_stat::emit_else() {
      this->k = keywords::condition;
      this->c = condition_kind::else_;
      return;
}
void ir_stat::emit_cond_goto(const luramas_address &loc) {
      if (this->l == nullptr && (this->r == nullptr || this->b != luramas::il::arch::data::bin_kinds::nothing)) {
            return;
      }
      const auto l = this->l;
      const auto r = this->r;
      const auto b = this->b;
      this->clear();
      this->emit_cond_goto(l, b, loc, r);
      return;
}
void ir_stat::emit_cond_goto(const std::shared_ptr<ir_expr> &l, const luramas::il::arch::data::bin_kinds b, const luramas_address &loc, const std::shared_ptr<ir_expr> &r) {
      this->k = keywords::condition_goto;
      this->l = l;
      this->jlabel = loc;
      this->r = r;
      this->b = b;
      return;
}
void ir_stat::emit_stack_push(const std::shared_ptr<ir_expr> &v, const std::shared_ptr<ir_expr> &id) {
      this->k = keywords::stack_push;
      this->members.emplace_back(v);
      this->v = id;
      return;
}
void ir_stat::emit_stack_read(const std::shared_ptr<ir_expr> &l, const std::shared_ptr<ir_expr> &amt, const std::shared_ptr<ir_expr> &id) {
      this->k = keywords::stack_read;
      this->l = l;
      this->r = amt;
      this->v = id;
      return;
}
void ir_stat::emit_stack_pop(const std::shared_ptr<ir_expr> &v, const std::shared_ptr<ir_expr> &id) {
      this->k = keywords::stack_pop;
      this->members.emplace_back(v);
      this->v = id;
      return;
}
void ir_stat::emit_goto(const luramas_address &loc) {
      this->k = keywords::goto_label;
      this->jlabel = loc;
      return;
}
void ir_stat::emit_bitwrite(const std::shared_ptr<ir_expr> &dest, const std::shared_ptr<ir_expr> &src, const std::shared_ptr<ir_expr> &min, const std::shared_ptr<ir_expr> &max) {
      this->k = keywords::bitwrite;
      this->l = dest;
      this->r = src;
      this->v = min;
      this->lba = max;
      return;
}
void ir_stat::emit_annotation(const std::string &annotation) {
      this->annotation = annotation;
      return;
}
void ir_stat::emit_metadata(const std::shared_ptr<ir_expr> &name, const std::shared_ptr<ir_expr> &data) {
      this->k = keywords::metadata;
      this->r = name;
      this->v = data;
      return;
}
void ir_stat::emit_tag_start(const std::shared_ptr<ir_expr> &name, const std::shared_ptr<ir_expr> &table) {
      this->k = keywords::tag_start;
      this->r = name;
      this->v = table;
      return;
}
void ir_stat::emit_tag_end() {
      this->k = keywords::tag_end;
      return;
}
void ir_stat::emit_entry_point() {
      this->k = keywords::entry_point;
      return;
}
void ir_stat::emit_command(const std::shared_ptr<ir_expr> &name) {
      this->k = keywords::command;
      this->r = name;
      return;
}
