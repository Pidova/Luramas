#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::simulate {

      std::vector<loop_threading_results> loop_threading(luramas::ir::passes::pass_manager &pm, const luramas_address start, const luramas_address target) {

            std::vector<loop_threading_results> result;

            return result;
      }

      basic_block_results basic_block(luramas::ir::passes::pass_manager &pm, const boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> &input, const luramas_blockrange &range, const std::uint32_t limit, const bool undefine_zero, const bool include_order_of_operations) {

            basic_block_results result;

            {
                  const auto amt = tools::count::insts(range);
                  result.hit_count.reserve(amt);
                  if (include_order_of_operations) {
                        result.order_of_operations.value() = luramas_addresses();
                        result.order_of_operations.value().reserve((amt * (std::ceil(limit / 350u) + 1u)));
                  }
            }

            /* Propagate count */
            for (auto i = range.first; i < range.second; ++i) {
                  result.hit_count.try_emplace(i, 0u);
            }

            auto regs = input;
            for (auto i = range.first; i < range.second; ++i) {

                  const auto cached = i;
                  if (result.hit_count[i]++ >= limit) {
                        break;
                  }
                  if (include_order_of_operations) {
                        result.order_of_operations.value().emplace_back(i);
                  }

                  const auto &p = pm[i];
                  if (p->is_terminal()) {
                        break;
                  }
                  if (p->is_control_flow_transfer()) {
                        i = tools::common::safe_take_jump(pm, i);
                        if (!tools::contains::address(range, i)) {
                              result.make_exception<basic_block_exit_reason::out_of_range>(cached);
                              break;
                        }
                        continue;
                  }
                  switch (p->k) {
                        case keywords::assignment: {
                              if (p->l && p->r && p->l->is_register_reference()) {
                                    if (const auto computed = tools::compute::constant_evaluation(pm, p->r, regs); computed) {
                                          regs[p->l->reg] = computed;
                                    }
                              }
                              break;
                        }
                        case keywords::end: {
                              if (tools::stat::branch::is_loop_end(pm, p)) {
                                    i = tools::common::reverse_safe_take_jump(pm, i);
                              }
                              break;
                        }
                        case keywords::while_:
                        case keywords::condition:
                        case keywords::condition_goto: {
                              if (tools::stat::branch::is_else_cond(p)) {
                                    i = tools::common::safe_take_jump(pm, i);
                              } else {
                                    const auto computed = tools::compute::constant_evaluation(pm, tools::exprs::mutate::cmp_extract(p), regs);
                                    if (!computed || !computed->implicit()) {
                                          i = tools::common::safe_take_jump(pm, i);
                                    }
                              }
                              break;
                        }
                        case keywords::until: {
                              const auto computed = tools::compute::constant_evaluation(pm, tools::exprs::mutate::cmp_extract(p), regs);
                              if (computed && computed->implicit()) {
                                    i = tools::common::reverse_safe_take_jump(pm, i);
                              }
                              break;
                        }
                        case keywords::for_loop_init: {

                              break;
                        }
                        case keywords::forloop_numeric: {

                              if (tools::exprs::values::is_reg(p->lba)) {
                                    if (pm.env_flags.fforloop_iterator_cmps) {
                                    }
                                    const auto init = tools::compute::constant_evaluation(pm, p->l, regs);
                                    const auto limit = tools::compute::constant_evaluation(pm, p->r, regs);
                                    const auto step = tools::compute::constant_evaluation(pm, p->v, regs);
                                    if (!init || !limit || !step) {
                                          i = tools::common::safe_take_jump(pm, i);
                                    } else {
                                    }
                              } else {
                                    i = tools::common::safe_take_jump(pm, i);
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  if (!tools::contains::address(range, i)) {
                        result.make_exception<basic_block_exit_reason::out_of_range>(cached);
                        break;
                  }
            }
            return result;
      }

} // namespace luramas::ir::tools::simulate