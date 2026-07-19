#include "../../ir.hpp"

bool ir_stat::is_scoped() const {
      return luramas::ir::data::scoped(this->k);
}
bool ir_stat::is_psuedo() const {
      return luramas::ir::data::psuedo(this->k);
}
bool ir_stat::is_terminator() const {
      return this->flags.fnoreturn || luramas::ir::data::terminator(this->k);
}
bool ir_stat::is_terminal() const {
      return this->flags.fnoreturn || luramas::ir::data::terminal(this->k);
}
bool ir_stat::is_trivial_terminal() const {
      return this->is_terminal() || this->is_terminator();
}
bool ir_stat::is_interrupt() const {
      return this->flags.fnoreturn || luramas::ir::data::interrupt(this->k);
}
bool ir_stat::is_scope_start() const {
      return luramas::ir::data::scope_start(this->k);
}
bool ir_stat::is_paging() const {
      return luramas::ir::data::paging(this->k);
}
bool ir_stat::is_paging_control_flow_transfer() const {
      return (this->k == keywords::retn && !this->smembers.empty()) || luramas::ir::data::paging_control_flow_transfer(this->k);
}
bool ir_stat::is_scopeable() const {
      return luramas::ir::data::scopeable(this->k);
}
bool ir_stat::is_implicit_flow_interrupt() const {
      return luramas::ir::data::implicit_flow_interrupt(this->k);
}
bool ir_stat::is_potential_side_effectable() const {
      return luramas::ir::data::potential_side_effects(this->k);
}
bool ir_stat::is_scope_start_highlevel() const {
      return luramas::ir::data::scope_start_highlevel(this->k, this->c);
}
bool ir_stat::is_control_flow_transfer() const {
      return luramas::ir::data::control_flow_transfer(this->k);
}
bool ir_stat::is_scope_end() const {
      return luramas::ir::data::scope_end(this->k);
}
bool ir_stat::is_loop() const {
      return luramas::ir::data::loop(this->k);
}
bool ir_stat::is_breakable() const {
      return luramas::ir::data::breakable(this->k);
}
bool ir_stat::is_continueable() const {
      return luramas::ir::data::continueable(this->k);
}
bool ir_stat::is_isolation() const {
      return luramas::ir::data::isolation(this->k);
}
bool ir_stat::is_for_loop() const {
      return luramas::ir::data::for_loop(this->k);
}
bool ir_stat::is_defines() const {
      return luramas::ir::data::defines(this->k);
}
bool ir_stat::is_goto_label() const {
      return luramas::ir::data::goto_label(this->k);
}
bool ir_stat::is_primitive_kind_dest_violation() const {
      return luramas::ir::data::primitive_kind_dest_violation(this->k);
}
bool ir_stat::is_assignment() const {
      return luramas::ir::data::assignment(this->k);
}
bool ir_stat::is_data_assignment() const {
      return luramas::ir::data::is_data_assignment(this->k);
}
bool ir_stat::is_meta() const {
      return luramas::ir::data::is_meta(this->k);
}
bool ir_stat::is_flow_interrupt() const {
      return this->flags.fnoreturn || luramas::ir::data::flow_interrupt(this->k) || luramas::ir::data::paging_control_flow_transfer(this->k);
}
bool ir_stat::is_volatile() const {
      return !this->flags.fsafe && luramas::ir::data::volatile_(this->k);
}
bool ir_stat::is_flag_volatile() const {
      return luramas::ir::data::flag_volatile(this->k);
}
bool ir_stat::is_self_referential_assignment() const {
      return luramas::ir::data::self_referential_assignment(this->k);
}