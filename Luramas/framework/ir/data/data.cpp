#include "../ir.hpp"

namespace luramas::ir::data {

      bool reference(const tkind k) {
            switch (k) {
                  case tkind::global:
                  case tkind::kvalue: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool primitive(const tkind k) {
            switch (k) {
                  case tkind::none_obj:
                  case tkind::lura_int:
                  case tkind::boolean:
                  case tkind::string: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool mutable_basic(const tkind k) {
            switch (k) {
                  case tkind::stack: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool concatable(const tkind k) {
            switch (k) {
                  case tkind::string:
                  case tkind::lura_int: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }

      bool primitive_expr_kind_dest_violation(const expr_kinds k) {
            switch (k) {
                  case expr_kinds::call:
                  case expr_kinds::idx:
                  case expr_kinds::page_function_call: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool closure_sensitive(const expr_kinds k) {
            switch (k) {
                  case expr_kinds::upvalue: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool flag(const expr_kinds k) {
            switch (k) {
                  case expr_kinds::flag: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool register_reference(const expr_kinds k) {
            switch (k) {
                  case expr_kinds::reg:
                  case expr_kinds::upvalue: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool is_complex(const expr_kinds k) {
            switch (k) {
                  case expr_kinds::arith: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool is_name_qualifier(const tkind k) {
            switch (k) {
                  case tkind::global:
                  case tkind::kvalue:
                  case tkind::string: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool is_complex(const tkind k) {
            switch (k) {
                  case tkind::string:
                  case tkind::none_obj:
                  case tkind::variadic:
                  case tkind::table: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool global(const tkind k) {
            switch (k) {
                  case tkind::global:
                  case tkind::kvalue: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool integral(const tkind k) {
            switch (k) {
                  case tkind::lura_int: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool mutable_(const tkind k) {
            switch (k) {
                  case tkind::global:
                  case tkind::kvalue: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool paging(const expr_kinds k) {
            switch (k) {
                  case expr_kinds::page_function_call: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool unsafe(const expr_kinds k) {
            switch (k) {
                  case expr_kinds::upvalue:
                  case expr_kinds::memoryread: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool volatile_(const expr_kinds k) {
            switch (k) {
                  case expr_kinds::call:
                  case expr_kinds::page_function_call: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool control_flow_dependant(const expr_kinds k) {
            switch (k) {
                  case expr_kinds::call:
                  case expr_kinds::page_function_call: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }

      bool defines(const keywords k) {
            if (for_loop(k)) {
                  return true;
            }
            switch (k) {
                  case keywords::assignment: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool assignment(const keywords k) {
            switch (k) {
                  case keywords::assignment:
                  case keywords::table_assign: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool is_data_assignment(const keywords k) {
            switch (k) {
                  case keywords::assignment: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool is_meta(const keywords k) {
            switch (k) {
                  case keywords::definition: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool volatile_(const keywords k) {
            switch (k) {
                  case keywords::call:
                  case keywords::page_function_goto:
                  case keywords::stack_push:
                  case keywords::stack_pop:
                  case keywords::memoryset: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool flag_volatile(const keywords k) {
            switch (k) {
                  case keywords::set_flag: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool terminator(const keywords k) {
            switch (k) {
                  case keywords::break_:
                  case keywords::continue_:
                  case keywords::retn: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool terminal(const keywords k) {
            switch (k) {
                  case keywords::retn: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool interrupt(const keywords k) {
            switch (k) {
                  case keywords::break_:
                  case keywords::continue_:
                  case keywords::goto_label:
                  case keywords::end:
                  case keywords::retn: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool flow_interrupt(const keywords k) {
            switch (k) {
                  case keywords::break_:
                  case keywords::continue_:
                  case keywords::goto_label:
                  case keywords::retn: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool primitive_kind_dest_violation(const keywords k) {
            switch (k) {
                  case keywords::call:
                  case keywords::table_assign:
                  case keywords::assignment:
                  case keywords::table_setlist: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool self_referential_assignment(const keywords k) {
            switch (k) {
                  case keywords::table_assign: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool scoped(const keywords k) {
            if (loop(k)) {
                  return true;
            }
            switch (k) {
                  case keywords::condition:
                  case keywords::condition_goto:
                  case keywords::until:
                  case keywords::goto_label:
                  case keywords::end:
                  case keywords::label: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool psuedo(const keywords k) {
            switch (k) {
                  case keywords::page_function_pass: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool scope_start(const keywords k) {
            if (loop(k)) {
                  return true;
            }
            switch (k) {
                  case keywords::condition:
                  case keywords::condition_goto:
                  case keywords::goto_label: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool paging(const keywords k) {
            switch (k) {
                  case keywords::page_function_goto:
                  case keywords::page_function_start:
                  case keywords::page_function_end: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool paging_control_flow_transfer(const keywords k) {
            switch (k) {
                  case keywords::page_function_goto: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool scopeable(const keywords k) {
            if (loop(k)) {
                  return true;
            }
            switch (k) {
                  case keywords::condition: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool implicit_flow_interrupt(const keywords k) {
            switch (k) {
                  case keywords::break_:
                  case keywords::continue_: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool potential_side_effects(const keywords k) {
            switch (k) {
                  case keywords::label: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool control_flow_transfer(const keywords k) {
            switch (k) {
                  case keywords::break_:
                  case keywords::continue_:
                  case keywords::goto_label: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool scope_start_highlevel(const keywords k, const condition_kind c) {
            if (loop(k)) {
                  return true;
            }
            switch (k) {
                  case keywords::condition: {
                        return c == condition_kind::if_ || c == condition_kind::nothing;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool scope_end(const keywords k) {
            switch (k) {
                  case keywords::end:
                  case keywords::until: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool loop(const keywords k) {
            if (for_loop(k)) {
                  return true;
            }
            switch (k) {
                  case keywords::repeat:
                  case keywords::while_: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool for_loop(const keywords k) {
            switch (k) {
                  case keywords::forloop_generic:
                  case keywords::forloop_numeric: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool breakable(const keywords k) {
            if (for_loop(k)) {
                  return true;
            }
            switch (k) {
                  case keywords::repeat:
                  case keywords::while_:
                  case keywords::switch_: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool continueable(const keywords k) {
            if (for_loop(k)) {
                  return true;
            }
            switch (k) {
                  case keywords::repeat:
                  case keywords::while_: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool isolation(const keywords k) {
            switch (k) {
                  case keywords::isolate: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
      bool goto_label(const keywords k) {
            switch (k) {
                  case keywords::condition_goto:
                  case keywords::goto_label: {
                        return true;
                  }
                  default: {
                        return false;
                  }
            }
      }
} // namespace luramas::ir::data