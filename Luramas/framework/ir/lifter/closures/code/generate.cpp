#include "../common.hpp"

namespace luramas::ir::closures::generate {

      void definition(luramas::ir::passes::pass_manager &pm, const std::shared_ptr<luramas::closures::closure> &closure, const std::shared_ptr<luramas::ir::managers::upvalues::manager> &upvalues) {

            boost::unordered_flat_set<luramas_register> upvals;

            /* Create definition */
            auto c = std::make_shared<ir_stat>();
            c->emit_definition();
            if (upvalues) {
                  for (const auto &[reg, expr] : upvalues->upvalues) {
                        if (expr->is_register_reference()) {
                              upvals.insert(expr->reg);
                        }
                        c->emit_upv_definition(expr);
                  }
            }

            /* Define args */
            const auto undefs = tools::extract::ir::lazy_undefined_registers(pm.ir, upvals);
            boost::unordered_flat_set<luramas_register> defined_arg;
            if (!undefs.empty()) {
                  for (const auto &n : pm.ir.data) {
                        for (const auto &u : undefs) {
                              std::shared_ptr<ir_stat::ir_expr> expr = nullptr;
                              const auto visits = n->visit(u);
                              if (!visits.empty()) {
                                    expr = *visits.begin();
                                    if (!expr->is_k<expr_kinds::upvalue>()) {
                                          expr->clear();
                                          expr->emit_reg_arg(u);
                                    }
                                    if (closure->flags.finclude_annotations) {
                                          managers::upvalues::emitter::closure_debug_name(u, expr, closure, closure->nodes[closure->nodes.size() / 2u]);
                                    }
                              }
                              if (expr) {
                                    defined_arg.insert(u);
                                    c->emit_definition(u, expr);
                              }
                        }
                  }
                  if (closure->flags.fassociated_args) {
                        for (const auto &r : undefs) {
                              if (!upvalues->pre_defined.contains(r) && !defined_arg.contains(r)) {
                                    auto result = luramas::ir::tools::exprs::generate::reg_arg(r);
                                    if (closure->flags.finclude_annotations) {
                                          managers::upvalues::emitter::closure_debug_name(r, result, closure, closure->nodes[closure->nodes.size() / 2u]);
                                    }
                                    c->emit_definition(r, result);
                              }
                        }
                  } else {
                        std::size_t max_arg = 0u;
                        for (const auto &u : undefs) {
                              const auto it = upvalues->defined_upvs.find(u);
                              if (it != upvalues->defined_upvs.end()) {
                                    if (it->second > max_arg) {
                                          max_arg = it->second;
                                    }
                              } else if (u > max_arg) {
                                    max_arg = u;
                              }
                        }
                        for (auto arg = 0u; arg < max_arg; ++arg) {
                              if (!upvalues->pre_defined.contains(arg) && !defined_arg.contains(arg)) {
                                    auto result = luramas::ir::tools::exprs::generate::reg_arg(arg);
                                    if (closure->flags.finclude_annotations) {
                                          managers::upvalues::emitter::closure_debug_name(arg, result, closure, closure->nodes[closure->nodes.size() / 2u]);
                                    }
                                    c->emit_definition(arg, result);
                              }
                        }
                  }
                  c->emit_parameters();
            }
            c->flags.flink_regs = pm.det_flags.fmain_closure;

            /* Propagate with placeholders */
            for (const auto &_ : c->args) {
                  c->meta.emplace_back(nullptr);
            }
            pm.push_front(c);
            pm.mut(LURAMAS_DEBUG_LINE);
            return;
      }

} // namespace luramas::ir::closures::generate