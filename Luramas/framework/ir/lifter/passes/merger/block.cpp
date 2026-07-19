#include "../../generation/cfg/iterate.hpp"
#include "../../generation/cfg/traversal.hpp"
#include "../includes/common.hpp"

namespace luramas::ir::passes {

      void block_merger(pass_manager &pm, shared &s) {

            const auto cfg = generation::cfg::generate(pm.ir, LURAMAS_IR_ENTRY, pm.env_flags.fhas_pages);
            for (const auto &i : pm.iter()) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::goto_label: {

                              if (pm.valid_prev<1u>(i)) {

                                    /*
                                            \l:\
                                            \[VALID]\
                                            \goto 1(2)\
                                            \...\
                                            goto l;
                                            ...
                                            l(2);
                                    */
                                    const auto label = tools::common::safe_take_jump(pm, i);
                                    if (tools::stat::past(i, label)) {

                                          if (const auto &block = cfg::iterate::visit::visit(cfg.blocks, label); block) {

                                                if (const auto &jump = cfg::traverse::extract::jump_block(block, i); jump->get_end() - 1u != i && jump->get_end() - 1u != label && tools::violations::block_violates(pm, label, jump->get_end() - 1u).valid && pm.is_safe(label + 1u, jump->get_end())) {

                                                      const auto loc = pm.ir.avaliable_end_label();

                                                      pm.remove(p);
                                                      pm.insert(pm[label], tools::stat::generate::goto_label(loc));
                                                      pm.insert(pm[i - 1u], tools::stat::generate::label(loc));
                                                      pm.move(pm[i - 1u], {label + 1u, jump->get_end()});
                                                      pm.set_safe(label + 1u, jump->get_end());
                                                      pm.mut(LURAMAS_DEBUG_LINE);
                                                }
                                          }
                                    }
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
            return;
      }

      void label_flatten(pass_manager &pm, shared &s) {

            for (const auto &i : pm.iter()) {

                  auto &p = pm[i];
                  switch (p->k) {
                        case keywords::label: {

                              if (auto next = tools::trackers::next_safe_executable(pm, i); next > i + 1u) {
                                    if (!tools::stat::branch::is_loop_end(pm, pm[next]) && tools::stat::is_end(pm[next])) {
                                          ++next;
                                    }
                                    if (const auto prev = tools::visitors::prev_loc(pm, next); prev != i && next != i) {
                                          pm.move(pm[prev], p);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }
            return;
      }
} // namespace luramas::ir::passes