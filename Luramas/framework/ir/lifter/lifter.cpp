#include "closures/common.hpp"

namespace luramas::ir {

      ir_stat::space lift(std::shared_ptr<luramas::closures::closure> &closure, const passes::environment_flags &env_flags) {

            boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> upvalue_defs;
            boost::unordered_flat_map<std::shared_ptr<luramas::closures::closure>, ir_stat::space> lifted;
            boost::unordered_flat_map<std::shared_ptr<luramas::closures::closure>, std::shared_ptr<managers::upvalues::manager>> upvalues;
            boost::unordered_flat_map<std::shared_ptr<luramas::closures::closure>, std::vector<std::shared_ptr<luramas::closures::closure>>> pending;

            /* Linear */
            std::deque<std::shared_ptr<luramas::closures::closure>> linear = {closure};
            do {
                  const auto on = linear.front();
                  linear.pop_front();
                  pending.try_emplace(on, on->closures);
                  upvalues.try_emplace(on, std::make_shared<managers::upvalues::manager>());
                  linear.insert(linear.end(), on->closures.begin(), on->closures.end());
            } while (!linear.empty());

            /* Construct upvalues */
            auto reg = LURAMAS_REGISTER_NEXT_SPACE;
            linear.emplace_back(closure);
            do {

                  /* Clean-up */
                  const auto on = linear.front();
                  linear.pop_front();
                  upvalue_defs.clear();

                  /* Add upvalues */
                  for (auto o = 0u; o != on->nodes.size(); ++o) {
                        const auto &i = on->nodes[o];
                        switch (i->lex->disassembly->op) {
                              case il::arch::opcodes::OP_NEWCLOSURE:
                              case il::arch::opcodes::OP_REFCLOSURE: {

                                    luramas_index uv_idx = 0u;
                                    const auto idx = (i->lex->has_operand_kind<luramas::il::lexer::operand_kinds::kvalue>()) ? i->lex->operand_kind<luramas::il::lexer::operand_kinds::kvalue>().front()->dis.kvalue_idx : i->lex->operand_kind<luramas::il::lexer::operand_kinds::closure>().front()->dis.closure_idx;
                                    auto n_idx = o + 1u;
                                    auto next = on->nodes[n_idx];
                                    while (next && il::arch::is_op::psuedo(next->lex->disassembly->op)) {
                                          next = on->nodes[++n_idx];
                                    }
                                    while (next && next->lex->disassembly->op == luramas::il::arch::opcodes::OP_ADDUPVALUE && n_idx != on->nodes.size()) {

                                          const auto src = next->lex->operand_kind<luramas::il::lexer::operand_kinds::source>().front()->dis.reg;
                                          switch (next->lex->operand_kind<luramas::il::lexer::operand_kinds::upvalue_kind>().front()->dis.upvalue_kind) {
                                                case il::arch::operand::upvalue_kind::contents:
                                                case il::arch::operand::upvalue_kind::reference: {
                                                      if (!upvalue_defs.contains(src)) {
                                                            const auto ptr = tools::exprs::generate::upval(++reg, src);
                                                            upvalue_defs.try_emplace(src, ptr);
                                                            upvalues[on]->define(src, ptr);
                                                      }
                                                      upvalues[on->closures[idx]]->define_upvalue(uv_idx++, upvalue_defs[src]);
                                                      break;
                                                }
                                                case luramas::il::arch::operand::upvalue_kind::upvalues: {
                                                      upvalues[on->closures[idx]]->define_upvalue(uv_idx++, upvalues[on]->upvalues[src]);
                                                      break;
                                                }
                                                default: {
                                                      break;
                                                }
                                          }
                                          next = on->nodes[++n_idx];
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  }
                  linear.insert(linear.end(), on->closures.begin(), on->closures.end());
            } while (!linear.empty());

            /* Lift */
            while (lifted.size() != pending.size()) {
                  for (auto &[pend_closure, pend_closures] : pending) {

                        /* Check if it has been lifted before */
                        if (lifted.contains(pend_closure) || std::any_of(pend_closures.begin(), pend_closures.end(), [&lifted](const auto &l) { return !lifted.contains(l); })) {
                              continue;
                        }

                        std::vector<ir_stat::space> closures;
                        for (const auto &c : pend_closure->closures) {
                              closures.emplace_back(lifted[c]);
                        }
                        lifted.try_emplace(pend_closure, closures::lifter::lift(const_cast<std::shared_ptr<luramas::closures::closure> &>(pend_closure), upvalues[pend_closure], closures, pend_closure == closure, true, env_flags));
                  }
            }

            return lifted[closure];
      }
} // namespace luramas::ir