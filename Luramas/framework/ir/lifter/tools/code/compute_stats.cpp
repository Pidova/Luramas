#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::compute::stats {

      bool simplify(passes::pass_manager &pm, const luramas_address addr, std::shared_ptr<ir_stat> &p, const bool mutate_pm, const std::optional<types::map> &tmap) {

            if (!p || !pm.is_safe(p)) {
                  return false;
            }

            switch (p->k) {
                        // TODO FIX ANY IMPLCIT OUT REPLACE WITH GOTO LABEL BEFORE REMOVING LOOP
                  case keywords::while_: {

                        /* Computationally true */
                        switch (tools::compute::compare(p->l, p->r, p->b, pm.env_flags.fprimitive_object)) {
                              case tools::compute::comparable::true_: {

                                    if (tools::stat::branch::is_while_true(p)) {
                                          break;
                                    }
                                    tools::stat::mutate::replace_cmp(p, tools::exprs::generate::boolean(true));
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }
                              case tools::compute::comparable::false_: {

                                    pm.remove(addr, tools::common::safe_take_jump(pm, addr) + 1u);
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }
                              default: {
                                    break;
                              }
                        }

                        if (const auto cond = tools::compute::exprs::simplify_condition(pm, p->l, p->b, expr_logical::nothing, p->r, mutate_pm, tmap); cond) {
                              p->l = cond->l;
                              p->b = cond->b;
                              p->r = cond->r;
                              return true;
                        }
                        break;
                  }
                  case keywords::until: {

                        /* Computationally true */
                        switch (tools::compute::compare(p->l, p->r, p->b, pm.env_flags.fprimitive_object)) {
                              case tools::compute::comparable::true_: {

                                    if (tools::stat::branch::is_until_true(p)) {
                                          break;
                                    }
                                    tools::stat::mutate::replace_cmp(p, tools::exprs::generate::boolean(true));
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }
                              case tools::compute::comparable::false_: {

                                    pm.remove(p, pm[tools::common::reverse_safe_take_jump(pm, addr)]);
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }
                              default: {
                                    break;
                              }
                        }

                        if (const auto cond = tools::compute::exprs::simplify_condition(pm, p->l, p->b, expr_logical::nothing, p->r, mutate_pm, tmap); cond) {
                              p->l = cond->l;
                              p->b = cond->b;
                              p->r = cond->r;
                              return true;
                        }
                        break;
                  }
                  case keywords::condition: {

                        /* Computationally true */
                        const auto result = tools::compute::compare(p->l, p->r, p->b, pm.env_flags.fprimitive_object);
                        if ((result == tools::compute::comparable::true_ || result == tools::compute::comparable::false_) && tools::mutations::pop_cond(pm, addr, result == tools::compute::comparable::true_)) {
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }

                        if (const auto cond = tools::compute::exprs::simplify_condition(pm, p->l, p->b, expr_logical::nothing, p->r, mutate_pm, tmap); cond) {
                              p->l = cond->l;
                              p->b = cond->b;
                              p->r = cond->r;
                              return true;
                        }
                        break;
                  }
                  case keywords::condition_goto: {

                        if (const auto cond = tools::compute::exprs::simplify_condition(pm, p->l, p->b, expr_logical::nothing, p->r, mutate_pm, tmap); cond) {
                              p->l = cond->l;
                              p->b = cond->b;
                              p->r = cond->r;
                              return true;
                        }

                        /* Computationally true */
                        const auto comparative = tools::compute::compare(p->l, p->r, p->b, pm.env_flags.fprimitive_object);
                        switch (comparative) {
                              case tools::compute::comparable::true_: {
                                    tools::stat::mutate::goto_stat_cleared(p, p->jlabel);
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }
                              case tools::compute::comparable::false_: {
                                    pm.remove(p);
                                    if (mutate_pm) {
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                                    return true;
                              }
                              default: {
                                    break;
                              }
                        }
                        break;
                  }
                  case keywords::memoryset: {

                        /* memset<cast> = cast() */
                        if (tools::exprs::values::is_cast(p->v) && tools::exprs::values::types::is_basic(p->v->non_native) && p->v->non_native->under.compare(p->extra_bits, false)) {
                              p->v = p->v->l;
                              if (mutate_pm) {
                                    pm.mut(LURAMAS_DEBUG_LINE);
                              }
                              return true;
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return false;
      }
} // namespace luramas::ir::tools::compute::stats