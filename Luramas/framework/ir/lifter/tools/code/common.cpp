#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::common {

      luramas_address safe_block_end(luramas::ir::passes::pass_manager &pm, const luramas_address start, const std::shared_ptr<ir_stat> &close_on) {
            return tools::truncate::block(pm, start, pm.amount(), false, true, false, close_on);
      }
      luramas_address safe_block_end(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address end, const std::shared_ptr<ir_stat> &close_on) {
            return tools::truncate::block(pm, start, end, false, false, false, close_on);
      }
      bool is_rest_safe_block_end(luramas::ir::passes::pass_manager &pm, const luramas_address start) {
            return tools::truncate::block(pm, start, pm.amount()) == pm.amount();
      }

      luramas_address safe_take_jump(luramas::ir::passes::pass_manager &pm, const luramas_address n) {
            if (!pm.contains(n)) {
                  return 0u;
            }
            auto buff = n;
            tools::stat::safe_jump_end(pm, n, buff);
            if (buff != n) {
                  return buff;
            }
            const auto &e = pm[n];
            const auto jmp = e->jlabel ? pm.processed.labels[e->jlabel] : e->underlying_jump;
            return pm.contains(jmp) ? jmp : 0u;
      }

      luramas_address reverse_safe_take_jump(luramas::ir::passes::pass_manager &pm, const luramas_address n) {
            if (!pm.contains(n)) {
                  return 0u;
            }
            const auto &e = pm[n];
            return e->end_label ? pm.processed.end_labels[e->end_label].first : e->elif_end_label ? pm.processed.end_labels[e->elif_end_label].first
                                                                                                  : n;
      }

      bool fall_loop_end(luramas::ir::passes::pass_manager &pm, const luramas_address start) {
            bool hit = false;
            visitors::last_safe_end(pm, start, hit);
            return hit;
      }

      bool basic_if_stat(luramas::ir::passes::pass_manager &pm, const luramas_address loc) {
            return pm.contains(loc) && stat::branch::is_if_cond(pm[loc]) && !tools::condition_has_else(pm, loc, tools::common::safe_take_jump(pm, loc));
      }

      bool basic_if_end_stat(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {
            if (!pm.valid_range(range)) {
                  return false;
            }
            for (auto i = range.first; i < range.second; ++i) {
                  const auto &stat = pm[i];
                  if (!stat::is_end(stat) || !basic_if_stat(pm, reverse_safe_take_jump(pm, i))) {
                        return false;
                  }
            }
            return true;
      }

      bool interrupt_on_past(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address loc) {
            if (!pm.contains(start)) {
                  return false;
            }
            const auto &e = pm[start];
            return e && e->is_flow_interrupt() && (!e->is_control_flow_transfer() || safe_take_jump(pm, start) >= loc);
      }

      luramas_address safe_take_else(luramas::ir::passes::pass_manager &pm, const luramas_address start) {

            return (pm.contains(start) && tools::stat::branch::is_else_conditional(pm[start])) ? trackers::else_end(pm, start) : start;
      }

      bool continues_to_loop(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &continue_stat, const luramas_address loop) {

            return stat::is_continue(continue_stat) && continue_stat->underlying_jump == loop;
      }
      bool breaks_to_loop(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &break_stat, const luramas_address loop) {

            return stat::is_break(break_stat) && pm.processed.parent_loops[break_stat->underlying_jump - 1u] == loop;
      }

      luramas_address traces_to_loop_end(luramas::ir::passes::pass_manager &pm, const luramas_address on) {

            const auto end = trackers::next_safe_executable(pm, on);
            return stat::branch::is_loop_end(pm, pm[end]) ? end : 0u;
      }

      std::shared_ptr<ir_stat::ir_expr> get_reg_expr_assignment(const std::shared_ptr<ir_stat> &assignment, const luramas_register reg) {
            if (!stat::is_assignment(assignment)) {
                  return nullptr;
            }
            if (exprs::values::is_reg(assignment->l, reg)) {
                  return assignment->l;
            }
            for (const auto &m : assignment->members) {
                  if (exprs::values::is_reg(m, reg)) {
                        return m;
                  }
            }
            return nullptr;
      }

      bool expects_definition(passes::pass_manager &pm, const luramas_address addr) {

            return pm.contains(addr) && stat::is_page_function_start(pm[addr]);
      }
} // namespace luramas::ir::tools::common