#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::closure {

      namespace space_stat {

            namespace definition {

                  void emit_args(const std::shared_ptr<ir_stat> &buffer, const ir_stat::space &space, const boost::unordered_flat_set<luramas_register> &upvals) {

                        if (!stat::is_definition(buffer)) {
                              return;
                        }
                        const auto casts = buffer->meta;
                        buffer->args.clear();
                        buffer->meta.clear();

                        se_ir ir(space);

                        /* Define args */
                        const auto undefs = tools::extract::ir::lazy_undefined_registers(ir, upvals);
                        boost::unordered_flat_set<luramas_register> defined_arg;
                        if (!undefs.empty()) {
                              for (const auto &n : space) {
                                    for (const auto &u : undefs) {
                                          std::shared_ptr<ir_stat::ir_expr> expr = nullptr;
                                          const auto visits = n->visit(u);
                                          if (!visits.empty()) {
                                                expr = *visits.begin();
                                                if (!expr->is_k<expr_kinds::upvalue>()) {
                                                      expr->clear();
                                                      expr->emit_reg_arg(u);
                                                }
                                          }
                                          if (expr) {
                                                defined_arg.insert(u);
                                                buffer->emit_definition(u, expr);
                                          }
                                    }
                              }
                              for (const auto &r : undefs) {
                                    if (!defined_arg.contains(r)) {
                                          buffer->emit_definition(r, luramas::ir::tools::exprs::generate::reg_arg(r));
                                    }
                              }
                              buffer->emit_parameters();
                        }
                        for (const auto &[r, expr] : buffer->args) {

                              const auto it = std::find_if(casts.begin(), casts.end(), [&](const auto &c) { return tools::exprs::values::is_cast_reg(c, r); });
                              buffer->meta.emplace_back(it != casts.end() ? *it : nullptr);
                        }
                        return;
                  }

                  std::shared_ptr<ir_stat> generate(const ir_stat::space &space, const ir_stat::ir_expr::space &upvalues) {

                        boost::unordered_flat_set<luramas_register> upvals;

                        /* Create definition */
                        auto c = std::make_shared<ir_stat>();
                        c->emit_definition();
                        for (const auto &i : upvalues) {
                              if (i->is_register_reference()) {
                                    upvals.insert(i->reg);
                              }
                              c->emit_upv_definition(i);
                        }

                        emit_args(c, space, upvals);
                        return c;
                  }

                  void update(const ir_stat::space &space) {

                        if (space.empty() || !stat::is_definition(space.front())) {
                              return;
                        }

                        boost::unordered_flat_set<luramas_register> upvals;
                        for (const auto &i : space.front()->upvalues) {
                              upvals.insert(i->reg);
                        }
                        emit_args(space.front(), space, upvals);
                        return;
                  }

                  void add(ir_stat::space &space, const std::shared_ptr<ir_stat> &definition) {

                        if (!stat::is_definition(definition)) {
                              return;
                        }
                        space.insert(space.begin(), definition);
                        return;
                  }
            } // namespace definition
      } // namespace space_stat

      generation_result generate(passes::pass_manager &pm, const luramas_blockrange &range) {

            generation_result result;

            /* Does not contain or not valid */
            if (!pm.contains(range.first) || !pm.contains(range.second) || !violations::block_violates(pm, range.first, range.second - 1u).valid) {
                  return result;
            }

            const auto space = extract::space(pm, range);

            /* Unsafe if it contains returns */
            if (contains::is(space, [](const keywords k) { return k == keywords::retn; })) {
                  return result;
            }

            /* Unresolved */
            result.unresolved_labels = extract::space_stat::unresolved_gotos(space);
            if (!result.unresolved_labels.empty()) {
                  return result;
            }

            result.expr = exprs::generate::closure(space);
            space_stat::definition::add(result.expr->closure, space_stat::definition::generate(result.expr->closure, extract::space_stat::upvalues(space)));
            return result;
      }
} // namespace luramas::ir::tools::closure