#include "../private.hpp"
#include "repeatables.hpp"

bool luramas::ir::passes::patterns::repeatables::if_condition::pattern_1(pass_manager &pm, shared &s, const luramas_address start, luramas_address &buffer_disp) {

      if (pm.valid_next<4u>(start)) {

            const auto &[n1, n2, n3, n4] = std::tie(pm[start], pm[start + 1u], pm[start + 2u], pm[start + 3u]);
            if (tools::stat::assignment::is_single_assignment(n2) && tools::stat::branch::is_if_end_not_contains(n1, n4, n2->l) && tools::stat::branch::is_cond_goto(n3, n2->l)) {

                  repeatable_manager<4u> rm(pm);
                  if (!rm.init(start, buffer_disp)) {
                        return true;
                  }

                  while (rm.immutable_valid_next(start, buffer_disp)) {

                        const auto &[if_stat, assign, condgoto, end_stat] = std::tie(pm[start + buffer_disp], pm[start + buffer_disp + 1u], pm[start + buffer_disp + 2u], pm[start + buffer_disp + 3u]);

                        if (!tools::stat::branch::is_if_cond(if_stat) ||
                            !tools::stat::is_assignment(assign) ||
                            !tools::stat::branch::is_cond_goto(condgoto) ||
                            !tools::stat::is_end(end_stat)) {
                              return rm.not_valid_kinds(buffer_disp);
                        }
                        if (!tools::stat::assignment::same_single_assignment(n2, assign) ||
                            !tools::stat::branch::is_if_end_not_contains(if_stat, end_stat, n2->l) ||
                            !tools::stat::branch::is_cond_goto_label(condgoto, n3->jlabel, n2->l)) {
                              return false;
                        }
                        rm.displace(buffer_disp);
                        if (!rm.valid_next(start, buffer_disp)) {
                              break;
                        }
                  }
            }
      }
      return false;
}
