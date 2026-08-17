#include "includes/common.hpp"

namespace luramas::ir::passes {

      void variadic_function(pass_manager &pm, shared & /*s*/) {

            if (pm.ir.data.empty() || !pm.ir.data.front()->is_k<keywords::definition>()) {
                  return;
            }

            boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> processed;
            for (const auto &i : pm.ir.data) {

                  if (pm.ir.data.front()->flags.fvariadic_def) {
                        return;
                  }
                  std::function<void(const std::shared_ptr<ir_stat::ir_expr> &)> search = [&](const auto &expr) {
                        if (!expr || processed.contains(expr) || pm.ir.data.front()->flags.fvariadic_def) {
                              return;
                        }
                        if (expr->template is_tk<tkind::variadic>()) {
                              pm.ir.data.front()->flags.fvariadic_def = true;
                              return;
                        }
                        processed.insert(expr);
                        search(expr->l);
                        search(expr->r);
                        search(expr->ev);
                        search(expr->xv);
                        for (const auto &m : expr->members) {
                              search(m);
                        }
                        for (const auto &m : expr->captures) {
                              search(m);
                        }
                        for (const auto &[i, v] : expr->tmembers) {
                              if (i) {
                                    search(i);
                              }
                              if (v) {
                                    search(v);
                              }
                        }
                        return;
                  };

                  search(i->l);
                  search(i->r);
                  search(i->v);
                  for (const auto &v : i->members) {
                        search(v);
                  }
                  for (const auto &v : i->smembers) {
                        search(v);
                  }
                  for (const auto &v : i->tmembers) {
                        search(v);
                  }
            }
            return;
      }

      void inline_functions(pass_manager &pm, shared & /*s*/) {

            pass::process::values(pm);

            for (const auto &[stat, values] : pm.processed.values) {

                  for (const auto &rs : values.rvalues) {

                        /* 
                            (function (..)
                                return ?;
                            end)() [INDEPENDENT]
                        */
                        if (tools::exprs::values::is_anonfunction_call(rs)) {

                              if (const auto closure = rs->l; closure->closure.size() == 2U && tools::stat::is_return(closure->closure.back(), 1U) && tools::block::independent(closure->closure)) {

                                    if (const auto data = tools::inliner::inline_data(pm, closure->closure, {rs}, rs->members); !data.empty()) {

                                          pm.insert(pm[values.where - 1U], data);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }
                  }
            }
            return;
      }

      static void native_inline_function_reconstruction(pass_manager &pm, shared & /*s*/) {

            pass::process::values(pm);

            for (const auto &[stat, values] : pm.processed.values) {

                  for (const auto &rs : values.rvalues) {

                        /* 
                            (function (..)
                                return ?;
                            end)() [INDEPENDENT]
                        */
                        if (tools::exprs::values::is_anonfunction_call(rs)) {

                              if (const auto closure = rs->l; closure->closure.size() == 2U && tools::stat::is_return(closure->closure.back(), 1U) && tools::block::independent(closure->closure)) {

                                    if (const auto data = tools::inliner::inline_data(pm, closure->closure, {rs}, rs->members); !data.empty()) {

                                          pm.insert(pm[values.where - 1U], data);
                                          pm.mut(LURAMAS_DEBUG_LINE);
                                    }
                              }
                        }
                  }
            }
            return;
      }
} // namespace luramas::ir::passes