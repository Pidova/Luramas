#include "../../../builder/builder.hpp"
#include "../common.hpp"

namespace luramas::ir::closures::lifter {

      ir_stat::space lift(std::shared_ptr<luramas::closures::closure> &closure, const std::shared_ptr<luramas::ir::managers::upvalues::manager> &upvalues, const std::vector<ir_stat::space> &closures, const bool main_closure, const luramas_flag fgenerate_main_definition, const passes::environment_flags &env_flags) {

            auto regs = upvalues ? upvalues->pre_defined : boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>>();
            ir_stat::space code;

            struct scope_stack_s {
                  bool loop = false;
                  bool close = false;
                  boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>> regs;
            };
            std::vector<scope_stack_s> scope_stack;
            const auto exit_scope = [&]() {
                  if (!scope_stack.empty()) {
                        regs = std::move(scope_stack.back().regs);
                        scope_stack.pop_back();
                  }
                  return;
            };
            const auto enter_scope = [&](const bool loop, const bool close) {
                  scope_stack.emplace_back(scope_stack_s(loop, close, regs));
                  regs = boost::unordered_flat_map<luramas_register, std::shared_ptr<ir_stat::ir_expr>>(regs);
                  return;
            };

            const auto getr = [&](const luramas_register r) {
                  if (!regs.contains(r)) {
                        regs.try_emplace(r, luramas::ir::tools::exprs::generate::reg(r));
                  }
                  return regs[r];
            };
            const auto getl = [&](const std::shared_ptr<luramas::closures::node> &node, const luramas_register r) {
                  if (!regs.contains(r)) {
                        regs.try_emplace(r, luramas::ir::tools::exprs::generate::reg(r));
                  }
                  auto &result = regs[r];
                  if (closure->flags.finclude_annotations) {
                        luramas::ir::managers::upvalues::emitter::closure_debug_name(r, result, closure, node);
                  }
                  return result;
            };
            const auto extract_v = [&](const std::shared_ptr<luramas::closures::node> &n, const bool sanitize = false) {
                  const auto b = n->lex->disassembly->operands.back();
                  auto expr = std::make_shared<ir_stat::ir_expr>();
                  switch (n->lex->disassembly->op) {
                        case luramas::il::arch::opcodes::OP_LOADNONE:
                        case luramas::il::arch::opcodes::OP_CMPNONE:
                        case luramas::il::arch::opcodes::OP_CMPSNONE: {
                              expr->emit_none();
                              return expr;
                        }
                        case luramas::il::arch::opcodes::OP_GETTABUPVALUE: {
                              expr->emit_global(b->k_value);
                              return expr;
                        }
                        default: {
                              break;
                        }
                  }
                  switch (b->type) {
                        case luramas::il::arch::operand::operand_kind::none: {
                              expr->emit_none();
                              break;
                        }
                        case luramas::il::arch::operand::operand_kind::kval:
                        case luramas::il::arch::operand::operand_kind::kval_string: {
                              auto k = b->k_value;
                              if (sanitize) {
                                    luramas_str_sanitize(k);
                              }
                              if (n->lex->kind == luramas::il::lexer::inst_kinds::get_global || n->lex->kind == luramas::il::lexer::inst_kinds::set_global) {
                                    expr->emit_global(k);
                              } else {
                                    switch (b->k_value_kind) {
                                          case luramas::il::arch::data::kval_kinds::none: {
                                                expr->emit_none();
                                                break;
                                          }
                                          case luramas::il::arch::data::kval_kinds::boolean: {
                                                expr->emit_boolean(!k.empty() && (k.front() == 'T' || k.front() == 't'));
                                                break;
                                          }
                                          case luramas::il::arch::data::kval_kinds::integer: {
                                                expr->emit_int(std::stod(k));
                                                break;
                                          }
                                          case luramas::il::arch::data::kval_kinds::string: {
                                                expr->emit_str(k);
                                                break;
                                          }
                                          default: {
                                                if (luramas_str_qoutes(k)) {
                                                      expr->emit_str(k);
                                                } else if (luramas_str_number(k)) {
                                                      expr->emit_int(std::stoll(k));
                                                } else if (luramas_str_decimal(k)) {
                                                      expr->emit_int(std::stod(k));
                                                } else {
                                                      expr->emit_kvalue(k);
                                                }
                                                break;
                                          }
                                    }
                              }
                              break;
                        }
                        case luramas::il::arch::operand::operand_kind::integer: {
                              expr->emit_int(luramas::math::is_decimal(b->dis.integer) ? luramas_int(b->dis.integer) : luramas_int(static_cast<luramas_int_base>(b->dis.integer)));
                              break;
                        }
                        case luramas::il::arch::operand::operand_kind::boolean: {
                              expr->emit_boolean(b->dis.boolean);
                              break;
                        }
                        case luramas::il::arch::operand::operand_kind::value: {
                              expr->emit_int(b->dis.val);
                              break;
                        }
                        case luramas::il::arch::operand::operand_kind::reg: {
                              return getr(b->dis.reg);
                        }
                        default: {
                              expr->emit_global("UNK");
                              break;
                        }
                  }
                  return expr;
            };

            /* Map out lables and ends */
            std::vector<std::pair<luramas_id, std::shared_ptr<ir_stat::ir_expr>>> retn_pages;
            std::vector<std::intptr_t> page_stack;
            boost::unordered_flat_map<luramas_address, std::size_t> ends;
            boost::unordered_flat_map<luramas_address, luramas_address> label_map;
            std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, luramas::il::arch::operand::upvalue_kind>> captures;

            {
                  std::vector<luramas_address> on = {0u};
                  for (const auto &i : closure->nodes) {

                        if (i->lex->jumps()) {

                              const auto jmp = i->lex->jump();
                              while (on.back() <= i->address) {
                                    if (on.size() > 1u) {
                                          on.pop_back();
                                    } else {
                                          break;
                                    }
                              }

                              const auto jmp_loc = jmp + 1u;

                              /* Label Map */
                              if (on.size() > 1u && on.back() < jmp) {
                                    label_map.try_emplace(jmp, jmp_loc);
                                    continue;
                              }

                              /* For INIT */
                              if (i->lex->jump_forward() && i->lex->kind == luramas::il::lexer::inst_kinds::forinit) {
                                    on.emplace_back(jmp - (closure->nodes[jmp]->lex->kind != luramas::il::lexer::inst_kinds::for_));
                                    continue;
                              }

                              /* End for loops */
                              if (i->lex->kind == luramas::il::lexer::inst_kinds::for_) {
                                    ++ends[i->address];
                                    continue;
                              }
                              label_map.try_emplace(jmp, jmp_loc);
                        }
                  }
            }

            std::uint16_t segregated = 0u;
            std::shared_ptr<ir_stat::ir_expr> cached_closure = nullptr;
            std::vector<luramas::il::arch::data::flags> flags;
            std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat::ir_expr>>> tag_kv;
            boost::unordered_flat_map<std::uint16_t, std::pair<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat::ir_expr>>> cmp_flag;

            const auto generate_page_return = [&]() {
                  const auto c = luramas::ir::tools::stat::generate::retn();
                  c->flags.funknown_paging = true;
                  c->flags.fpage_keyword = true;
                  std::shared_ptr<ir_stat::ir_expr> r = nullptr;
                  for (const auto &[id, e] : retn_pages) {
                        r = e;
                        c->smembers.emplace_back(tools::exprs::generate::integral(id));
                  }
                  c->l = r;
                  code.emplace_back(c);
                  retn_pages.clear();
            };
            for (const auto &i : closure->nodes) {

                  if (!retn_pages.empty() && i->lex->disassembly->op != luramas::il::arch::opcodes::OP_PRETURN) {
                        generate_page_return();
                  }

                  {
                        const auto label = label_map.find(i->address);
                        const auto end = ends.find(i->address);

                        if (label != label_map.end() && end == ends.end()) { /* Label no ends */

                              code.emplace_back(luramas::ir::tools::stat::generate::label(label->second));
                        } else if (label == label_map.end() && end != ends.end()) { /* No label and ends */

                              for (auto idx = 0u; idx < end->second; ++idx) {
                                    code.emplace_back(luramas::ir::tools::stat::generate::end());
                                    exit_scope();
                              }
                        } else if (label != label_map.end() && end != ends.end()) { /* Label and ends */

                              /* Do non-loops first */
                              auto idx = 0u;
                              while (idx < end->second) {
                                    if (!scope_stack.empty()) {
                                          if (!scope_stack.back().close) {
                                                exit_scope();
                                                continue;
                                          }
                                          if (scope_stack.back().loop) {
                                                break;
                                          }
                                    }
                                    code.emplace_back(luramas::ir::tools::stat::generate::end());
                                    exit_scope();
                                    ++idx;
                              }

                              /* Ensure remaining ends are properly counted */
                              end->second -= idx;

                              /* Any labels after non-loop */
                              code.emplace_back(luramas::ir::tools::stat::generate::label(label->second));

                              /* Finish the rest of the ends */
                              while (end->second > 0) {
                                    code.emplace_back(luramas::ir::tools::stat::generate::end());
                                    exit_scope();
                                    --end->second;
                              }
                        }
                  }

                  /* Add captures */
                  if (cached_closure && i->lex->kind != luramas::il::lexer::inst_kinds::capture) {
                        for (const auto &[expr, ref] : captures) {
                              cached_closure->emit_capture(expr, ref);
                        }
                        captures.clear();
                        cached_closure = nullptr;
                  }

                  const auto &dests = i->extract_dest_regs();
                  const auto &sources = i->extract_source_regs();
                  switch (i->lex->kind) {

                        case luramas::il::lexer::inst_kinds::expression: {

                              switch (i->lex->disassembly->op) {

                                    case luramas::il::arch::opcodes::OP_CONCAT: {

                                          auto r = std::make_shared<ir_stat::ir_expr>();
                                          for (const auto &s : sources) {
                                                r->emit_concat(getr(s));
                                          }
                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), r));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_NEWCLOSURE:
                                    case luramas::il::arch::opcodes::OP_REFCLOSURE: {

                                          cached_closure = std::make_shared<ir_stat::ir_expr>();

                                          /* Get idx */
                                          const auto idx = (i->lex->has_operand_kind<luramas::il::lexer::operand_kinds::kvalue>()) ? i->lex->operand_kind<luramas::il::lexer::operand_kinds::kvalue>().front()->dis.kvalue_idx : i->lex->operand_kind<luramas::il::lexer::operand_kinds::closure>().front()->dis.closure_idx;
                                          cached_closure->emit_closure(closures[idx]);

                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), cached_closure));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_SELF: {

                                          const auto r = luramas::ir::tools::exprs::generate::self(getr(sources.front()), extract_v(i, true));
                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), r));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_GETVARIADIC: {

                                          auto variadic = luramas::ir::tools::exprs::generate::variadic();
                                          for (const auto &d : dests) {
                                                code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, d), variadic));
                                          }
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_MOVE: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), getr(sources.back())));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_BITCAST: {

                                          const auto obj = luramas::ir::tools::exprs::generate::non_native(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val, i->lex->operand_kind<luramas::il::lexer::operand_kinds::boolean>().front()->dis.boolean, i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().back()->dis.val);
                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), luramas::ir::tools::exprs::generate::cast(obj, getr(sources.back()))));
                                          break;
                                    }

                                    /* Logicals */
                                    case luramas::il::arch::opcodes::OP_CLOGIC_OR: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), luramas::ir::tools::exprs::generate::logical<expr_logical::or_>(getr(sources.front()), getr(sources.back()))));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_CLOGIC_AND: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), luramas::ir::tools::exprs::generate::logical<expr_logical::and_>(getr(sources.front()), getr(sources.back()))));
                                          break;
                                    }

                                    /* Memory */
                                    case luramas::il::arch::opcodes::OP_MEMSET: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::memoryset(getr(sources.front()), getr(sources[1u]), i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_MEMREAD: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), luramas::ir::tools::exprs::generate::memoryread(getr(sources.front()), i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val)));
                                          break;
                                    }

                                    /* Stack */
                                    case luramas::il::arch::opcodes::OP_STACKPUSH: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::stack_push(getl(i, sources.back()), luramas::ir::tools::exprs::generate::integral(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val)));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_STACKPOP: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::stack_pop(getl(i, sources.back()), luramas::ir::tools::exprs::generate::integral(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val)));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_GETSTACK: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), luramas::ir::tools::exprs::generate::stack(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val)));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_SETSTACK: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(luramas::ir::tools::exprs::generate::stack(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val), getl(i, sources.back())));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_CREATE_STACK: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::create_stack(getl(i, dests.back())));
                                          break;
                                    }

                                    /* Internal/Inst flags */
                                    case luramas::il::arch::opcodes::OP_SETFLAG: {

                                          flags.emplace_back(static_cast<luramas::il::arch::data::flags>(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_FLAGSET: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::set_flag(luramas::ir::tools::exprs::generate::integral(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val), getr(sources.front())));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_FLAGREAD: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), luramas::ir::tools::exprs::generate::flag(luramas::ir::tools::exprs::generate::integral(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val))));
                                          break;
                                    }

                                    /* Paging */
                                    case luramas::il::arch::opcodes::OP_STARTPAGEFUNC: {

                                          const auto id = i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val;
                                          page_stack.emplace_back(id);
                                          code.emplace_back(luramas::ir::tools::stat::generate::page_function_start(luramas::ir::tools::exprs::generate::integral(id)));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_ENDPAGEFUNC: {

                                          if (page_stack.empty()) {
                                                luramas::error::error("Page stack is empty");
                                          }
                                          page_stack.pop_back();
                                          code.emplace_back(luramas::ir::tools::stat::generate::page_function_end(luramas::ir::tools::exprs::generate::integral(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val)));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_PRETURN: {

                                          const auto values = i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>();
                                          if (!values.front()->dis.val) {
                                                auto c = luramas::ir::tools::stat::generate::retn();
                                                c->flags.funknown_paging = true;
                                                c->flags.fpage_keyword = true;
                                                code.emplace_back(c);
                                          } else {
                                                retn_pages.emplace_back(values.back()->dis.val, getr(i->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>().back()->dis.reg));
                                          }
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_PJUMP: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::page_function_jump(luramas::ir::tools::exprs::generate::integral(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val)));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_PCALL: {

                                          const auto loc = i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val;
                                          const auto val = i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().back()->dis.val;

                                          code.emplace_back(luramas::ir::tools::stat::generate::page_function_call(luramas::ir::tools::exprs::generate::integral(loc), getr(sources.front()), luramas::ir::tools::exprs::generate::integral(val)));
                                          break;
                                    }

                                    /* Metadata */
                                    case luramas::il::arch::opcodes::OP_METADATA: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::metadata(tools::exprs::generate::string(i->lex->disassembly->operands.front()->k_value), tools::exprs::generate::string(i->lex->disassembly->operands.back()->k_value)));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_TAG_START: {

                                          auto tab = std::make_shared<ir_stat::ir_expr>();
                                          for (const auto &[k, v] : tag_kv) {
                                                tab->emit_table_set(k, v);
                                          }
                                          tag_kv.clear();
                                          code.emplace_back(luramas::ir::tools::stat::generate::tag_start(tools::exprs::generate::string(i->lex->disassembly->operands.back()->k_value), tab));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_TAG_KV: {

                                          tag_kv.emplace_back(tools::exprs::generate::string(i->lex->disassembly->operands.front()->k_value), tools::exprs::generate::string(i->lex->disassembly->operands.back()->k_value));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_TAG_END: {

                                          code.emplace_back(tools::stat::generate::tag_end());
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_ENTRY_POINT: {

                                          code.emplace_back(tools::stat::generate::entry_point());
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_COMMAND: {

                                          const auto command = tools::stat::generate::command(tools::exprs::generate::string(i->lex->disassembly->operands.front()->k_value));
                                          for (const auto &s : sources) {
                                                command->members.emplace_back(getl(i, s));
                                          }
                                          code.emplace_back(command);
                                          break;
                                    }

                                    /* Bit */
                                    case luramas::il::arch::opcodes::OP_BITREAD: {

                                          const auto obj = luramas::ir::tools::exprs::generate::non_native(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val, i->lex->operand_kind<luramas::il::lexer::operand_kinds::boolean>().front()->dis.boolean, 0u);
                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), luramas::ir::tools::exprs::generate::bitread(getr(sources.front()), getr(sources[1u]), getr(sources[2u]), obj)));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_BITWRITE: {

                                          const auto obj = luramas::ir::tools::exprs::generate::non_native(i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val, i->lex->operand_kind<luramas::il::lexer::operand_kinds::boolean>().front()->dis.boolean, 0u);
                                          code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), luramas::ir::tools::exprs::generate::bitwrite(getr(sources.front()), getr(sources[1u]), getr(sources[2u]), getr(sources[3u]), obj)));
                                          break;
                                    }
                                    case luramas::il::arch::opcodes::OP_BITWRITEA: {

                                          code.emplace_back(luramas::ir::tools::stat::generate::bitwrite(getl(i, dests.back()), getr(sources.front()), getr(sources[1u]), getr(sources.back())));
                                          break;
                                    }

                                    case luramas::il::arch::opcodes::OP_ANNOTATE_PREV: {

                                          if (!code.empty()) {
                                                code.back()->annotation = i->lex->disassembly->operands.front()->k_value;
                                          }
                                          break;
                                    }

                                    default: {
                                          break;
                                    }
                              }
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::arith: {
                              code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()),
                                  luramas::ir::tools::exprs::generate::arith(getr(sources.front()), sources.size() == 1u ? extract_v(i) : getr(sources.back()), i->lex->disassembly->bin_kind)));
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::capture: {

                              if (const auto kind = i->lex->operand_kind<luramas::il::lexer::operand_kinds::upvalue_kind>().front()->dis.upvalue_kind; kind != luramas::il::arch::operand::upvalue_kind::upvalues) {
                                    captures.emplace_back(std::make_pair(getr(sources.back()), kind));
                              }
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::branch_condition: {

                              const auto c = std::make_shared<ir_stat>();
                              const auto jmp_loc = i->lex->jump() + 1u;
                              c->emit_cond_goto(cmp_flag[segregated].first, i->lex->disassembly->bin_kind, jmp_loc, cmp_flag[segregated].second);
                              code.emplace_back(c);
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::branch: {

                              enter_scope(false, false);
                              code.emplace_back(luramas::ir::tools::stat::generate::goto_label(i->lex->jump() + 1u));
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::compare_dest: {

                              const auto cmp = luramas::ir::tools::exprs::generate::cond(cmp_flag[segregated].first, i->lex->disassembly->bin_kind, cmp_flag[segregated].second);
                              code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), cmp));
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::compare: {

                              const auto l = (!sources.empty()) ? getl(i, sources.front()) : extract_v(i);

                              std::shared_ptr<ir_stat::ir_expr> r = nullptr;
                              if (sources.size() > 1u) {
                                    r = getl(i, sources.back());
                              } else if (i->lex->operands.size() > 1u || i->lex->disassembly->op == luramas::il::arch::opcodes::OP_CMPNONE) {
                                    r = extract_v(i);
                              }
                              cmp_flag[segregated] = std::make_pair(l, r);
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::load:
                        case luramas::il::lexer::inst_kinds::get_global: {

                              const auto rvalue = sources.empty() ? extract_v(i) : getr(sources.front());
                              if (std::find(flags.begin(), flags.end(), luramas::il::arch::data::flags::fnative_global) != flags.end()) {
                                    rvalue->flags.fnative_global = true;
                              }
                              code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), rvalue));
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::set_global: {

                              const auto lvalue = extract_v(i);
                              if (std::find(flags.begin(), flags.end(), luramas::il::arch::data::flags::fnative_global) != flags.end()) {
                                    lvalue->flags.fnative_global = true;
                              }
                              code.emplace_back(luramas::ir::tools::stat::generate::assignment(lvalue, getr(sources.front())));
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::upvalue_gs: {

                              auto c = std::make_shared<ir_stat>();
                              const auto id = i->lex->operand_kind<luramas::il::lexer::operand_kinds::upvalue>().front()->dis.upvalue_idx;
                              if (i->lex->has_operand_kind<luramas::il::lexer::operand_kinds::source>()) {
                                    c->emit_assignment(upvalues->upvalues[id], getr(sources.back()));
                                    c->flags.fvolatile = true;
                              } else {
                                    c->emit_assignment(getr(dests.back()), upvalues->upvalues[id]);
                              }
                              code.emplace_back(c);
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::unary: {

                              const auto r = luramas::ir::tools::exprs::generate::unary(extract_v(i), i->lex->disassembly->bin_kind);
                              code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), r));
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::return_: {

                              const auto regs = i->lex->operand_kind<luramas::il::lexer::operand_kinds::reg>();
                              auto c = std::make_shared<ir_stat>();
                              for (const auto &s : sources) {
                                    c->emit_return(getl(i, s));
                              }
                              c->emit_return();
                              code.emplace_back(c);
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::ccall: {

                              auto r = std::make_shared<ir_stat::ir_expr>();
                              const auto callr = i->lex->disassembly->operands.front()->dis.reg;
                              const auto no_ret = dests.empty();

                              const auto call = getr(callr);
                              auto c = std::make_shared<ir_stat>();
                              bool ignore = false;
                              for (const auto &i : sources) {
                                    if (!ignore && i == callr) {
                                          ignore = true;
                                          continue;
                                    }
                                    const auto a = getr(i);
                                    if (no_ret) {
                                          c->emit_arg(a);
                                    } else {
                                          r->emit_arg(a);
                                    }
                              }
                              for (const auto &d : dests) {
                                    const auto l = getl(i, d);
                                    const auto r = l;
                                    if (dests.size() == 1u) {
                                          c->l = r;
                                    } else {
                                          c->emit_mul_lv(r);
                                    }
                              }
                              if (no_ret) {
                                    c->emit_call(call);
                              } else {
                                    r->emit_call(call);
                                    if (std::find(flags.begin(), flags.end(), luramas::il::arch::data::flags::ffunc) != flags.end()) {
                                          r->flags.fbuiltin = true;
                                    }
                                    c->emit_assignment(c->l, r);
                              }
                              code.emplace_back(c);
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::table_get: {

                              code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), luramas::ir::tools::exprs::generate::table_index(getr(sources.front()), extract_v(i))));
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::table_set: {

                              code.emplace_back(luramas::ir::tools::stat::generate::table_assignment(getl(i, sources[1]), extract_v(i), getr(sources.front())));
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::new_table: {

                              code.emplace_back(luramas::ir::tools::stat::generate::assignment(getl(i, dests.back()), luramas::ir::tools::exprs::generate::table()));
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::set_table: {

                              /* SETLIST ([?], ?)*/
                              auto c = std::make_shared<ir_stat>();
                              for (const auto &i : sources) {
                                    c->emit_tab_setlist(getr(dests.back()), getr(i));
                              }
                              c->table_index = i->lex->disassembly->operands[3]->dis.val;
                              code.emplace_back(c);
                              break;
                        }
                        case luramas::il::lexer::inst_kinds::forinit: {

                              enter_scope(true, true);
                              auto c = std::make_shared<ir_stat>();
                              if (i->lex->disassembly->op == luramas::il::arch::opcodes::OP_INITFORLOOPN) {
                                    const auto l = getl(i, dests.back());
                                    c->emit_forloop_numeric(l, l, getr(sources.front()), getr(sources.back()));
                              } else {
                                    if (i->lex->disassembly->op == luramas::il::arch::opcodes::OP_INITFORLOOPSPECIAL) {
                                          const auto raw_dests = i->lex->operand_kind<luramas::il::lexer::operand_kinds::dest>();
                                          c->emit_forloop_meta(getr(raw_dests.front()->dis.reg), getr(raw_dests.back()->dis.reg), getr(i->lex->operand_kind<luramas::il::lexer::operand_kinds::source>().front()->dis.reg));
                                    }
                                    for (const auto &d : dests) {
                                          c->emit_forloop_generic(getl(i, d));
                                    }
                                    for (const auto &s : sources) {
                                          c->emit_forloop_generic(nullptr, getr(s));
                                    }
                              }
                              code.emplace_back(c);
                              code.emplace_back(luramas::ir::tools::stat::generate::for_loop_init());
                              break;
                        }
                        default: {
                              break;
                        }
                  }
                  if (i->lex->disassembly->op != luramas::il::arch::opcodes::OP_SETFLAG &&
                      i->lex->disassembly->op != luramas::il::arch::opcodes::OP_SEGREGATE) {
                        for (const auto &f : flags) {
                              switch (f) {
                                    case luramas::il::arch::data::flags::fexternal_page_goto: {
                                          code.back()->flags.fexternal_page_goto = true;
                                          break;
                                    }
                                    case luramas::il::arch::data::flags::fvolatile: {
                                          code.back()->flags.fvolatile = true;
                                          break;
                                    }
                                    case luramas::il::arch::data::flags::fno_return: {
                                          code.back()->flags.fnoreturn = true;
                                          break;
                                    }
                                    case luramas::il::arch::data::flags::fexpanded_non_direct_cft: {
                                          code.back()->flags.fexpanded_non_direct_cft = true;
                                          break;
                                    }
                                    case luramas::il::arch::data::flags::fatomic: {
                                          code.back()->flags.fatomic = true;
                                          break;
                                    }
                                    case luramas::il::arch::data::flags::ffunc: {
                                          code.back()->flags.fbuiltin = true;
                                          break;
                                    }
                                    case luramas::il::arch::data::flags::funknown_paging: {
                                          code.back()->flags.funknown_paging = true;
                                          break;
                                    }
                                    case luramas::il::arch::data::flags::finternal_store: {
                                          code.back()->flags.finternal_store = true;
                                          break;
                                    }
                                    case luramas::il::arch::data::flags::fglobal_user_defined: {
                                          if (tools::stat::is_assignment(code.back())) {
                                                for (const auto &v : {code.back()->l, code.back()->r}) {
                                                      if (tools::exprs::values::is_global(v)) {
                                                            v->flags.fglobal_user_defined = true;
                                                      }
                                                }
                                          }
                                          break;
                                    }
                                    case luramas::il::arch::data::flags::fwild_global: {
                                          if (tools::stat::is_assignment(code.back())) {
                                                for (const auto &v : {code.back()->l, code.back()->r}) {
                                                      if (tools::exprs::values::is_global(v)) {
                                                            v->flags.fglobal_wild = true;
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
                        flags.clear();
                  }

                  segregated = (i->lex->disassembly->op == luramas::il::arch::opcodes::OP_SEGREGATE) ? i->lex->operand_kind<luramas::il::lexer::operand_kinds::value>().front()->dis.val : 0u;
            }

            /* Add return if not */
            if (!retn_pages.empty()) {
                  generate_page_return();
            }
            if (code.empty() || !luramas::ir::tools::stat::is_return(code.back())) {
                  code.emplace_back(luramas::ir::tools::stat::generate::retn());
            }

            se_ir ir(code);

            /* Parse multiple entries */
            if (const auto entries = tools::entry::unsafe_split(ir); entries.has_value()) {
                  if (!main_closure) {
                        luramas::error::error("Entries can only be used in main closure");
                  }
                  ir = entries->front();
            }

            luramas::ir::passes::pass_manager pm(ir, env_flags);
            pm.det_flags.fmain_closure = main_closure;
            pm.ir.fhas_pages = env_flags.fhas_pages;
            if (fgenerate_main_definition) {
                  luramas::ir::closures::generate::definition(pm, closure, upvalues);
                  pm.run();
            }
            luramas::ir::passes::setups::normal(pm);
            return pm.ir.data;
      }

} // namespace luramas::ir::closures::lifter