#include "includes/common.hpp"

namespace luramas::ir::passes {

      void dead_flag_elimination(pass_manager &pm, shared &s, generation::flag_ssa::fssa &fssa) {

            for (const auto &i : pm.iter()) {

                  if (const auto &p = pm[i]; tools::stat::is_set_flag(p)) {

                        if (const auto it = fssa.set.find(i); it == fssa.set.end() || (!fssa.used.contains(it->second) && !fssa.unsafe.contains(it->second))) {
                              pm.remove(p);
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                  }
            }
            return;
      }

      void flag_propagation(pass_manager &pm, shared &s, generation::flag_ssa::fssa &fssa) {

            for (const auto &[loc, ssa] : fssa.set) {

                  const auto &stat = pm[loc];
                  const auto &[refs, refs_loc] = fssa.used[ssa];

                  /* No valid ptr */
                  if (!stat->l || !pm.is_safe(stat)) {
                        continue;
                  }

                  const auto fssa_unsafe = fssa.unsafe.contains(ssa);
                  const auto fssa_phi_complex = fssa.phis.contains(ssa);
                  // &&fssa.used[ssa].first > 1u && tools::stat::future(loc, *fssa.used[ssa].second.begin());

                  /* Not valid */
                  if (fssa_phi_complex || fssa_unsafe) {
                        continue;
                  }

                  /* Propagate if primitive */
                  auto clonable = false;
                  if (stat->r->is_primitive()) {

                        for (const auto &ref : refs_loc) {
                              if (const auto &p = pm[ref]; pm.safe(stat)) {
                                    p->propagate_flag(stat->l->extract_integral(), stat->r, clonable);
                              }
                        }
                        pm.remove(stat);
                        pm.mut(LURAMAS_DEBUG_LINE);
                  } else {

                        if (const auto end = refs_loc.empty() ? loc : std::max(loc, *std::max_element(refs_loc.begin(), refs_loc.end())); !tools::mutates(pm, stat->r, loc, end)) {

                              for (const auto &ref : refs_loc) {
                                    if (const auto &p = pm[ref]; pm.safe(stat)) {
                                          p->propagate_flag(stat->l->extract_integral(), stat->r, clonable);
                                    }
                              }
                              pm.remove(stat);
                              pm.mut(LURAMAS_DEBUG_LINE);
                        }
                  }
            }
            return;
      }
} // namespace luramas::ir::passes