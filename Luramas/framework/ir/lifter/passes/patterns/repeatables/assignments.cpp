#include "../private.hpp"
#include "repeatables.hpp"

bool luramas::ir::passes::patterns::repeatables::assignments::pattern_1(pass_manager &pm, shared &s, const luramas_address start, luramas_address &buffer_disp) {

      if (pm.valid_next<2u>(start)) {

            const auto &[p, n1] = std::tie(pm[start], pm[start + 1u]);
            if (tools::stat::assignment::is_single_assignment(p) && tools::stat::branch::is_cond_goto(n1, p->l)) {

                  repeatable_manager<2u> rm(pm);
                  if (!rm.init(start, buffer_disp)) {
                        return true;
                  }

                  while (rm.immutable_valid_next(start, buffer_disp)) {

                        const auto &[assignment, cond_goto] = std::tie(pm[start + buffer_disp], pm[start + buffer_disp + 1u]);

                        if (!tools::stat::is_assignment(assignment) ||
                            !tools::stat::branch::is_cond_goto(cond_goto)) {
                              return rm.not_valid_kinds(buffer_disp);
                        }
                        if (!tools::stat::assignment::same_single_assignment(p, assignment) ||
                            !tools::stat::branch::same_cond_goto_lr(n1, cond_goto)) {
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
