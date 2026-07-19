#include "../../ir.hpp"

/* Is kinds */
bool ir_stat::ir_expr::is_register_reference() const {
      return luramas::ir::data::register_reference(this->k);
}
bool ir_stat::ir_expr::is_name_qualifier() const {
      return luramas::ir::data::is_name_qualifier(this->tk);
}
bool ir_stat::ir_expr::is_reg(const luramas_register r) const {
      return this->is_register_reference() && this->reg == r;
}
bool ir_stat::ir_expr::is_flag(const luramas_int &r) const {
      return this->is_k<expr_kinds::flag>() && this->r && this->r->is_integral(r);
}
bool ir_stat::ir_expr::is_paging() const {
      return luramas::ir::data::paging(this->k);
}
bool ir_stat::ir_expr::is_primitive() const {
      return luramas::ir::data::primitive(this->tk);
}
bool ir_stat::ir_expr::is_mutable_basic_tk() const {
      return luramas::ir::data::mutable_basic(this->tk);
}
bool ir_stat::ir_expr::is_volatile() const {
      return !this->flags.fsafe && luramas::ir::data::volatile_(this->k);
}
bool ir_stat::ir_expr::is_closure_sensitive() const {
      return luramas::ir::data::closure_sensitive(this->k);
}
bool ir_stat::ir_expr::is_control_flow_dependant() const {
      return luramas::ir::data::control_flow_dependant(this->k);
}
bool ir_stat::ir_expr::is_primitive_kind_dest_violation() const {
      return luramas::ir::data::primitive_expr_kind_dest_violation(this->k);
}
bool ir_stat::ir_expr::is_mutable_tk() const {
      return !this->flags.fsafe && luramas::ir::data::mutable_(this->tk);
}
bool ir_stat::ir_expr::is_global_tk() const {
      return luramas::ir::data::global(this->tk);
}
bool ir_stat::ir_expr::is_integral() const {
      return luramas::ir::data::integral(this->tk);
}
bool ir_stat::ir_expr::is_unsafe_k() const {
      return !this->flags.fsafe && luramas::ir::data::unsafe(this->k);
}
bool ir_stat::ir_expr::is_concatable_tk() const {
      return luramas::ir::data::concatable(this->tk);
}
bool ir_stat::ir_expr::is_complex_k() const {
      return luramas::ir::data::is_complex(this->k);
}
bool ir_stat::ir_expr::is_complex_tk() const {
      return luramas::ir::data::is_complex(this->tk);
}
bool ir_stat::ir_expr::is_unsafe() const {
      return !this->flags.fsafe && (this->is_unsafe_k() || this->is_volatile() || this->is_mutable_tk());
}
bool ir_stat::ir_expr::is_flag() const {
      return luramas::ir::data::flag(this->k);
}
bool ir_stat::ir_expr::is_precise() const {
      return this->tk == tkind::lura_int ? this->n.precise() : false;
}
bool ir_stat::ir_expr::is_integral(const luramas_int &n) const {
      return this->tk == tkind::lura_int ? this->n == n : false;
}

bool ir_stat::ir_expr::implicit() const {
      switch (this->k) {
            case expr_kinds::concat: {
                  return true;
            }
            case expr_kinds::ternary: {
                  if (this->ev->implicit() && this->xv->implicit()) {
                        return true;
                  }
                  break;
            }
            default: {
                  break;
            }
      }
      switch (this->tk) {
            case tkind::string: {
                  return true;
            }
            case tkind::lura_int: {
                  return static_cast<bool>(this->n);
            }
            case tkind::boolean: {
                  return this->bv;
            }
            default: {
                  break;
            }
      }
      return false;
}

/* Is integrals */
bool ir_stat::ir_expr::is_min_integral() const {
      return this->tk == tkind::lura_int ? this->n.is_min_integral() : false;
}
bool ir_stat::ir_expr::is_max_integral() const {
      return this->tk == tkind::lura_int ? this->n.is_max_integral() : false;
}
bool ir_stat::ir_expr::safe_arith() const {
      return this->flags.fimplicit_type;
}