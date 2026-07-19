#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::visitors {

      luramas_address last_end(luramas::ir::passes::pass_manager &pm, luramas_address start) {

            if (pm[start]->is_k<keywords::end>()) {
                  while (pm.valid_next<1u>(start) && stat::is_end(pm[start + 1u])) {
                        ++start;
                  }
            }
            return start;
      }

      luramas_address prev_last_end(luramas::ir::passes::pass_manager &pm, luramas_address start) {

            if (pm[start]->is_k<keywords::end>()) {
                  while (pm.valid_prev<1u>(start) && stat::is_end(pm[start - 1u])) {
                        --start;
                  }
            }
            return start;
      }

      luramas_address last_safe_end(luramas::ir::passes::pass_manager &pm, luramas_address start, bool &hit) {

            hit = false;
            while (pm.valid_next<1u>(start) && stat::is_end(pm[start])) {
                  if (pm[pm.processed.end_labels[pm[start]->end_label].first]->is_loop()) {
                        hit = true;
                        break;
                  }
                  if (!stat::is_end(pm[start + 1u])) {
                        break;
                  }
                  ++start;
            }
            if (stat::is_until(pm[start])) {
                  hit = true;
            }
            return start;
      }

      luramas_address prev_safe_end(luramas::ir::passes::pass_manager &pm, luramas_address start, bool &hit) {

            hit = false;
            while (pm.valid_prev<1u>(start) && stat::is_end(pm[start - 1u])) {
                  if (stat::is_end(pm[start]) && pm[pm.processed.end_labels[pm[start]->end_label].first]->is_loop()) {
                        hit = true;
                        break;
                  }
                  --start;
            }
            return start;
      }

      luramas_address prev_cond(luramas::ir::passes::pass_manager &pm, luramas_address start) {

            while (pm.valid_prev<1u>(start) && !stat::branch::is_cond(pm[start])) {
                  --start;
            }
            return start;
      }

      luramas_address next_continuous_loop_end(luramas::ir::passes::pass_manager &pm, luramas_address start) {

            while (pm.valid_next<1u>(start)) {
                  const auto &p = pm[start];
                  if (!stat::is_end(p) || pm[pm.processed.end_labels[p->end_label].first]->is_loop()) {
                        break;
                  }
                  ++start;
            }
            return start;
      }

      luramas_address prev_loc(luramas::ir::passes::pass_manager &pm, const luramas_address on) {
            return on - pm.valid_prev<1u>(on);
      }
      luramas_address next_loc(luramas::ir::passes::pass_manager &pm, const luramas_address on) {
            return on + pm.valid_next<1u>(on);
      }
      std::shared_ptr<ir_stat> prev(luramas::ir::passes::pass_manager &pm, const luramas_address on) {
            return pm[prev_loc(pm, on)];
      }
      std::shared_ptr<ir_stat> next(luramas::ir::passes::pass_manager &pm, const luramas_address on) {
            return pm[next_loc(pm, on)];
      }

      std::shared_ptr<ir_stat> next_executable_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on) {

            const auto end = last_end(pm, on);
            return stat::is_end(pm[end]) ? next(pm, end) : pm[on];
      }
      std::shared_ptr<ir_stat> prev_executable_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on) {

            const auto end = prev_last_end(pm, on);
            return stat::is_end(pm[end]) ? prev(pm, end) : pm[end];
      }

      std::shared_ptr<ir_stat> last_safe_end_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on) {

            bool hit = false;
            return pm[last_safe_end(pm, on, hit)];
      }
      std::shared_ptr<ir_stat> prev_safe_end_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on) {

            bool hit = false;
            return pm[prev_safe_end(pm, on, hit)];
      }

      luramas_address next_executable(luramas::ir::passes::pass_manager &pm, const luramas_address on) {

            const auto end = last_end(pm, on);
            return stat::is_end(pm[end]) ? next_loc(pm, end) : end;
      }
      luramas_address prev_executable(luramas::ir::passes::pass_manager &pm, const luramas_address on) {

            const auto end = prev_last_end(pm, on);
            return stat::is_end(pm[end]) ? prev_loc(pm, end) : end;
      }

      luramas_address next_safe_executable(luramas::ir::passes::pass_manager &pm, const luramas_address on) {

            bool hit = false;
            const auto end = last_safe_end(pm, on, hit);
            return (!hit && stat::is_end(pm[end])) ? next_loc(pm, end) : on;
      }
      luramas_address prev_safe_executable(luramas::ir::passes::pass_manager &pm, const luramas_address on) {

            bool hit = false;
            const auto end = prev_safe_end(pm, on, hit);
            return (!hit && stat::is_end(pm[end])) ? prev_loc(pm, end) : on;
      }

      std::shared_ptr<ir_stat> next_safe_executable_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on) {

            return pm[next_safe_executable(pm, on)];
      }
      std::shared_ptr<ir_stat> prev_safe_executable_stat(luramas::ir::passes::pass_manager &pm, const luramas_address on) {

            return pm[prev_safe_executable(pm, on)];
      }

      std::shared_ptr<ir_stat> end_label_stat(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &stat) {

            return (stat == nullptr || !stat->end_label) ? nullptr : pm[pm.processed.end_labels[stat->end_label].second];
      }

      luramas_address explicit_cond_end(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<ir_stat> &stat) {

            if (stat != nullptr) {

                  const auto label = stat->end_label ? stat->end_label : stat->elif_end_label;
                  return (!label || !stat::branch::is_explicit_cond(stat)) ? 0u : pm.processed.end_labels[label].second;
            }
            return 0u;
      }

      bool parent_ifcond(luramas::ir::passes::pass_manager &pm, const luramas_address loc, luramas_address &buffer) {

            const auto block = violations::block_violates(pm, loc, pm.amount());
            if (block.reason == violations::block_violation_exceptions::invalid_end || block.reason == violations::block_violation_exceptions::invalid_else_conditional) {

                  const auto loc = tools::common::reverse_safe_take_jump(pm, block.ending_loc);
                  if (!tools::stat::branch::is_if_cond(pm[loc])) {
                        return false;
                  }

                  buffer = loc;
                  return true;
            }
            return false;
      }
      bool parent_loop(luramas::ir::passes::pass_manager &pm, const luramas_address loc, luramas_address &buffer) {

            auto block = violations::block_violates(pm, loc, pm.amount());
            while (!block.valid && pm.contains(block.ending_loc) && ((block.reason != violations::block_violation_exceptions::invalid_end || !pm[tools::common::reverse_safe_take_jump(pm, block.ending_loc)]->is_loop()) && block.reason != violations::block_violation_exceptions::invalid_until)) {
                  block = violations::block_violates(pm, block.ending_loc + 1u, pm.amount());
            }
            if (!pm.contains(block.ending_loc)) {
                  return false;
            }

            const auto reverse_jmp = tools::common::reverse_safe_take_jump(pm, block.ending_loc);
            if (!block.valid && reverse_jmp != block.ending_loc && pm[reverse_jmp]->is_loop()) {
                  buffer = reverse_jmp;
                  return true;
            }
            return false;
      }

      luramas_address first_orphaned_address_from_page(luramas::ir::passes::pass_manager &pm) {

            auto curr = LURAMAS_IR_ENTRY;
            while (pm.contains(curr)) {

                  const auto &s = pm[curr];

                  /* Definition */
                  if (tools::stat::is_definition(s)) {
                        ++curr;
                        continue;
                  }

                  /* Goto */
                  if (tools::stat::branch::is_goto(s) && s->flags.fpage_seperator) {
                        curr = common::safe_take_jump(pm, curr);
                  }
                  break;
            }
            return curr;
      }
} // namespace luramas::ir::tools::visitors