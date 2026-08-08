#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)
#include "parser.hpp"
#include "../../../../../il/architecture/emitter.hpp"
#include "../helpers.hpp"
#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <unordered_map>
#include <vector>

namespace lua_53_parsers {

      namespace gen {

            /* RK to register */
            luramas_register rk_to_r_reg(const std::intptr_t v, const luramas_address addr, luramas::il::lifter::parser::parser_manager<std::shared_ptr<lua_53_disassembler::disassembly>> &pm) {

                  if (helpers::rk_is_k(v)) {
                        const auto reg = pm.il->get_temp_reg();
                        pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_LOADKVAL>(pm.il, 0u, reg, helpers::rk_idx(v)));
                        return reg;
                  }
                  return v;
            }
      } // namespace gen

      void instructions(luramas::il::lifter::parser::parser_manager<std::shared_ptr<lua_53_disassembler::disassembly>> &pm) {

            luramas_address pc = 0u;
            luramas_register override_top = 0u;
            luramas_register stack_top = 0u;
            luramas_register prev_stack_top = 0u;
            for (auto idx = 0u; idx < pm.dism.size(); ++idx) {

                  const auto i = pm.dism[idx];
                  auto ptr = std::make_shared<luramas::il::disassembly>();
                  auto op = luramas::il::arch::opcodes::OP_NOP;
                  luramas_register append_top = 0u; /* Append top at the end of operands. */
                  const auto val_mulret = override_top ? override_top : (prev_stack_top > stack_top) ? prev_stack_top
                                                                                                     : stack_top;

                  std::vector<std::shared_ptr<lua_53_disassembler::operand>> sorted_operands;

                  /* Parse instructions */
                  switch (i->op) {
                        case OpCode::OP_MOVE: {
                              op = luramas::il::arch::opcodes::OP_MOVE;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_LOADK: {
                              op = luramas::il::arch::opcodes::OP_LOADKVAL;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_LOADKX: {
                              op = luramas::il::arch::opcodes::OP_LOADKVAL;
                              sorted_operands = {i->operands.front(), pm.dism[idx + 1u]->operands.front()};
                              break;
                        }
                        case OpCode::OP_LOADBOOL: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_LOADNIL: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_GETUPVAL: {
                              op = luramas::il::arch::opcodes::OP_GETUPVALUE;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_SETUPVAL: {
                              op = luramas::il::arch::opcodes::OP_SETUPVALUE;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_GETTABUP: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_SETTABUP: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_GETTABLE: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_SETTABLE: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_NEWTABLE: {
                              op = luramas::il::arch::opcodes::OP_NEWTABLEA;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_SELF: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_SETLIST: {
                              auto b = i->operands[1u]->val;
                              if (b == 0u) {
                                    b = val_mulret;
                              }
                              auto c = i->operands.back()->val;
                              if (c == 0u) {
                                    c = pm.dism[idx + 1u]->operands.front()->val;
                              }
                              op = luramas::il::arch::opcodes::OP_SETLIST;
                              sorted_operands = {i->operands.front(),
                                  lua_53_disassembler::make_operand::reg(i->operands.front()->reg + 1u),
                                  lua_53_disassembler::make_operand::val(b + 1u),
                                  lua_53_disassembler::make_operand::val((c - 1u) * LFIELDS_PER_FLUSH + 1u)};
                              break;
                        }
                        case OpCode::OP_ADD: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_SUB: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_MUL: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_DIV: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_IDIV: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_MOD: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_POW: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_BAND: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_BOR: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_BXOR: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_SHL: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_SHR: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_UNM: {
                              op = luramas::il::arch::opcodes::OP_MINUS;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_BNOT: {
                              op = luramas::il::arch::opcodes::OP_BITNOT;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_NOT: {
                              op = luramas::il::arch::opcodes::OP_NOT;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case OpCode::OP_LEN: {
                              op = luramas::il::arch::opcodes::OP_LEN;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case OpCode::OP_CONCAT: {
                              op = luramas::il::arch::opcodes::OP_CONCAT;
                              sorted_operands = {i->operands.front(), i->operands[1u], i->operands.back()};
                              break;
                        }
                        case OpCode::OP_JMP: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands.clear(); /* The jmp could cause problems handle it later */
                              break;
                        }
                        case OpCode::OP_EQ: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_LT: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_LE: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_TEST: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_TESTSET: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_CALL: {
                              op = luramas::il::arch::opcodes::OP_CCALL;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_TAILCALL: {
                              op = luramas::il::arch::opcodes::OP_CCALL;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_RETURN: {
                              op = luramas::il::arch::opcodes::OP_RETURN;
                              sorted_operands = i->operands;
                              break;
                        }
                        case OpCode::OP_FORLOOP: {
                              const auto r = i->operands.front()->reg;
                              const auto limit = lua_53_disassembler::make_operand::reg(r + 1u);
                              const auto step = lua_53_disassembler::make_operand::reg(r + 2u);
                              const auto index = lua_53_disassembler::make_operand::reg(r + 3u);
                              op = luramas::il::arch::opcodes::OP_FORLOOPN;
                              sorted_operands = {index, limit, step, i->operands.back()};
                              break;
                        }
                        case OpCode::OP_TFORLOOP: {
                              std::shared_ptr<lua_53_disassembler::disassembly> call = nullptr;
                              for (auto x = idx; x-- > 0u;) {
                                    if (pm.dism[x]->op == OpCode::OP_TFORCALL) {
                                          call = pm.dism[x];
                                          break;
                                    }
                              }
                              op = luramas::il::arch::opcodes::OP_FORLOOPG;
                              sorted_operands = {call->operands.front(), call->operands.back(), i->operands.back()};
                              break;
                        }
                        case OpCode::OP_CLOSURE: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case OpCode::OP_VARARG: {
                              op = luramas::il::arch::opcodes::OP_GETVARIADIC;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case OpCode::OP_FORPREP:
                        case OpCode::OP_TFORCALL:
                        case OpCode::OP_EXTRAARG: {
                              break;
                        }
                        default: {
                              break;
                        }
                  }

                  /* Data */
                  ptr->op = op;
                  ptr->addr = pc;

                  /* Get temp reg */
                  for (const auto &o : i->operands) {
                        if ((o->type == op_table::type::reg || o->type == op_table::type::dest) && !helpers::rk_is_k(o->reg) && pm.il->ctemp_reg < o->reg) {
                              pm.il->ctemp_reg = o->reg;
                        }
                  }

                  /* Parse operands */
                  for (const auto &oper : sorted_operands) {

                        auto operand_ptr = std::make_shared<luramas::il::arch::operand::operand>();

                        /* Data */
                        switch (oper->type) {
                              case op_table::type::reg: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::reg;
                                    operand_ptr->dis.reg = oper->reg;
                                    break;
                              }
                              case op_table::type::dest: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::reg;
                                    operand_ptr->dis.reg = oper->reg;
                                    append_top = operand_ptr->dis.reg;
                                    break;
                              }
                              case op_table::type::val: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::value;
                                    operand_ptr->dis.val = oper->val;
                                    break;
                              }
                              case op_table::type::boolean: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::boolean;
                                    operand_ptr->dis.boolean = oper->val;
                                    break;
                              }
                              case op_table::type::val_multret: {

                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::value;
                                    operand_ptr->dis.val = oper->val;
                                    if (oper->val == LUA_MULTRET) {
                                          operand_ptr->dis.val = val_mulret;
                                          operand_ptr->multret = true;
                                    }
                                    break;
                              }
                              case op_table::type::upvalue: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::upvalue;
                                    operand_ptr->dis.upvalue_idx = oper->upvalue;
                                    break;
                              }
                              case op_table::type::k_idx: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::kval;
                                    operand_ptr->k_value = oper->k_value;
                                    operand_ptr->dis.kvalue_idx = oper->k_idx;
                                    break;
                              }
                              case op_table::type::table_size: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::table_size;
                                    operand_ptr->dis.table_size = oper->table_size;
                                    break;
                              }
                              case op_table::type::jmp: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::jmp;
                                    operand_ptr->dis.jmp = oper->jmp;
                                    operand_ptr->ref_addr = oper->ref_addr;
                                    break;
                              }
                              default: {
                                    luramas::error::error("Unkown operand type.");
                              }
                        }

                        /* Append */
                        ptr->operands.emplace_back(operand_ptr);
                  }

                  pm.il->insert_back(ptr);

                  /* Ignore for self. */
                  if (append_top) {
                        prev_stack_top = stack_top;
                        stack_top = append_top;
                  }
                  if (sorted_operands.size() >= 2u) {
                        for (auto it = sorted_operands.begin(); it != sorted_operands.end() - 1u; ++it) {
                              if ((*it)->type == op_table::type::val_multret && (*it)->val == LUA_MULTRET) {
                                    override_top = 0u;
                              }
                        }
                        if (sorted_operands.front()->type == op_table::type::dest && sorted_operands.back()->type == op_table::type::val_multret && sorted_operands.back()->val == LUA_MULTRET) {
                              override_top = sorted_operands.front()->reg + 1u;
                        }
                  }
                  pc += LURAMAS_INST_LEN;
            }
            return;
      }

      void pending(luramas::il::lifter::parser::parser_manager<std::shared_ptr<lua_53_disassembler::disassembly>> &pm) {

            boost::unordered_flat_map<std::shared_ptr<lua_53_disassembler::disassembly>, std::shared_ptr<luramas::il::disassembly>> tforcall_to_init;

            /* Go through for inits */
            for (auto i = 0u; i < pm.il->dis.size(); ++i) {

                  auto &dis = pm.il->dis[i];
                  const auto &org = pm.dism[i];
                  pm.il->reset_temp_reg();

                  /* Add loop inits */
                  switch (dis->op) {
                        case luramas::il::arch::opcodes::OP_FORLOOPN: {
                              const auto base = org->operands.front()->reg;
                              const auto start = dis->operands.front()->dis.reg;
                              const auto max = dis->operands[1u]->dis.reg;
                              const auto inc = dis->operands[2u]->dis.reg;
                              const auto jmp = dis->operands.back()->dis.jmp;
                              const auto loc = org->operands.back()->ref_addr;
                              pm.il->insert_front(loc, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_MOVE>(pm.il, loc, start, base));
                              const auto init = luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_INITFORLOOPN>(pm.il, loc, start, max, inc, jmp);
                              pm.il->insert_front(loc, init);
                              tforcall_to_init[org] = init;

                              /* Force linkage */
                              init->ref = dis;
                              dis->ref = init;
                              break;
                        }
                        case luramas::il::arch::opcodes::OP_FORLOOPG: {
                              const auto start = dis->operands.front()->dis.reg;
                              const auto c = dis->operands[1u]->dis.reg;
                              const auto jmp = dis->operands.back()->dis.jmp;
                              const auto loc = org->operands.back()->ref_addr;
                              const auto init = luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_INITFORLOOPG>(pm.il, loc, start, c, jmp);
                              pm.il->insert(loc, init);

                              /* Get tforcall */
                              std::shared_ptr<lua_53_disassembler::disassembly> call = nullptr;
                              for (auto x = i; x-- > 0u;) {
                                    if (pm.dism[x]->op == OpCode::OP_TFORCALL) {
                                          call = pm.dism[x];
                                          break;
                                    }
                              }
                              tforcall_to_init[call] = init;

                              /* Force linkage */
                              init->ref = dis;
                              dis->ref = init;
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            }

            /* Pending */
            for (auto i = 0u; i < pm.il->dis.size(); ++i) {

                  auto &dis = pm.il->dis[i];
                  const auto &org = pm.dism[i];
                  const auto addr = org->addr;

                  /* Now parse pendings */
                  if (dis->op != luramas::il::arch::opcodes::OP_PEND) {
                        continue;
                  }
                  pm.il->reset_temp_reg();

                  /* Change to arith R = RK OP RK */
                  const auto arith = [&]<auto op>() {
                        const auto a = dis->operands.front()->dis.reg;
                        const auto b = gen::rk_to_r_reg(dis->operands[1u]->dis.val, addr, pm);
                        const auto c = gen::rk_to_r_reg(dis->operands.back()->dis.val, addr, pm);
                        pm.il->insert(addr, luramas::il::emitter::generate_opcode<op>(pm.il, addr, a, b, c));
                        return;
                  };

                  switch (org->op) {
                        case OpCode::OP_LOADBOOL: {

                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_LOADBOOL>(pm.il, addr, dis, org->operands.front()->val, bool(org->operands[1u]->val));
                              /* if (C) JMP next instruction */
                              if (org->operands.back()->val) {
                                    pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMP>(pm.il, addr, 2u));
                              }
                              break;
                        }
                        case OpCode::OP_LOADNIL: {
                              auto r = org->operands.front()->val;
                              for (auto j = 0u; j <= org->operands.back()->val; ++j) {
                                    pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_LOADNONE>(pm.il, addr, r++));
                              }
                              break;
                        }
                        case OpCode::OP_GETTABUP: {

                              const auto a = org->operands.front()->reg;
                              const auto b = org->operands[1u]->val;
                              const auto upv = pm.il->get_temp_reg();
                              const auto c = gen::rk_to_r_reg(org->operands.back()->val, addr, pm);
                              pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_GETUPVALUE>(pm.il, addr, upv, b));
                              pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_GETTABLE>(pm.il, addr, a, upv, c));
                              break;
                        }
                        case OpCode::OP_SETTABUP: {

                              const auto a = org->operands.front()->reg;
                              const auto upv = pm.il->get_temp_reg();
                              const auto b = gen::rk_to_r_reg(org->operands[1u]->val, addr, pm);
                              const auto c = gen::rk_to_r_reg(org->operands.back()->val, addr, pm);
                              pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_GETUPVALUE>(pm.il, addr, upv, a));
                              pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_SETTABLE>(pm.il, addr, c, upv, b));
                              break;
                        }
                        case OpCode::OP_GETTABLE: {
                              const auto a = dis->operands.front()->dis.reg;
                              const auto b = dis->operands[1u]->dis.reg;
                              const auto c = gen::rk_to_r_reg(dis->operands.back()->dis.val, addr, pm);
                              pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_GETTABLE>(pm.il, addr, a, b, c));
                              break;
                        }
                        case OpCode::OP_SETTABLE: {
                              const auto a = dis->operands.front()->dis.reg;
                              const auto b = gen::rk_to_r_reg(dis->operands[1u]->dis.val, addr, pm);
                              const auto c = gen::rk_to_r_reg(dis->operands.back()->dis.val, addr, pm);
                              pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_SETTABLE>(pm.il, addr, c, a, b));
                              break;
                        }
                        case OpCode::OP_ADD: {
                              arith.operator()<luramas::il::arch::opcodes::OP_ADD>();
                              break;
                        }
                        case OpCode::OP_SUB: {
                              arith.operator()<luramas::il::arch::opcodes::OP_SUB>();
                              break;
                        }
                        case OpCode::OP_MUL: {
                              arith.operator()<luramas::il::arch::opcodes::OP_MUL>();
                              break;
                        }
                        case OpCode::OP_DIV: {
                              arith.operator()<luramas::il::arch::opcodes::OP_DIV>();
                              break;
                        }
                        case OpCode::OP_IDIV: {
                              arith.operator()<luramas::il::arch::opcodes::OP_IDIV>();
                              break;
                        }
                        case OpCode::OP_MOD: {
                              arith.operator()<luramas::il::arch::opcodes::OP_MOD>();
                              break;
                        }
                        case OpCode::OP_POW: {
                              arith.operator()<luramas::il::arch::opcodes::OP_POW>();
                              break;
                        }
                        case OpCode::OP_BAND: {
                              arith.operator()<luramas::il::arch::opcodes::OP_AND>();
                              break;
                        }
                        case OpCode::OP_BOR: {
                              arith.operator()<luramas::il::arch::opcodes::OP_OR>();
                              break;
                        }
                        case OpCode::OP_BXOR: {
                              arith.operator()<luramas::il::arch::opcodes::OP_XOR>();
                              break;
                        }
                        case OpCode::OP_SHL: {
                              arith.operator()<luramas::il::arch::opcodes::OP_SHL>();
                              break;
                        }
                        case OpCode::OP_SHR: {
                              arith.operator()<luramas::il::arch::opcodes::OP_SHR>();
                              break;
                        }
                        case OpCode::OP_SELF: {
                              const auto a = dis->operands.front()->dis.reg;
                              const auto b = dis->operands[1u]->dis.reg;
                              const auto c = dis->operands.back()->dis.val;
                              pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_MOVE>(pm.il, addr, a + 1u, b));
                              if (helpers::rk_is_k(c)) {
                                    pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_SELF>(pm.il, addr, a, b, helpers::rk_idx(c)));
                              } else {
                                    pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_GETTABLE>(pm.il, addr, a, b, c));
                              }
                              break;
                        }
                        case OpCode::OP_JMP: {
                              const auto a = org->operands.front()->val;
                              const auto bx = org->operands.back()->jmp;
                              if (a) {
                                    pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_DESTROYUPVALUESA>(pm.il, addr, a - 1));
                              }
                              const auto jmp = luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMP>(pm.il, addr, bx + 1);

                              /* Change if jump goes to tfor */
                              const auto &loc = pm.dism[jmp->operands.back()->ref_addr];
                              if (const auto it = tforcall_to_init.find(loc); it != tforcall_to_init.end()) {
                                    jmp->ref = it->second;
                              }
                              pm.il->insert(addr, jmp);
                              break;
                        }
                        case OpCode::OP_EQ:
                        case OpCode::OP_LT:
                        case OpCode::OP_LE: {

                              dis->op = luramas::il::arch::opcodes::OP_CMP;
                              const auto a = org->operands.front()->val;
                              const auto b = gen::rk_to_r_reg(dis->operands[1u]->dis.val, addr, pm);
                              const auto c = gen::rk_to_r_reg(dis->operands.back()->dis.val, addr, pm);
                              pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_CMP>(pm.il, addr, b, c));
                              switch (org->op) {
                                    case OpCode::OP_EQ: {
                                          if (a) {
                                                pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMPIFNOTEQUAL>(pm.il, addr, 2u));
                                          } else {
                                                pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMPIFEQUAL>(pm.il, addr, 2u));
                                          }
                                          break;
                                    }
                                    case OpCode::OP_LT: {
                                          if (a) {
                                                pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMPIFGREATEREQUAL>(pm.il, addr, 2u));
                                          } else {
                                                pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMPIFLESS>(pm.il, addr, 2u));
                                          }
                                          break;
                                    }
                                    case OpCode::OP_LE: {
                                          if (a) {
                                                pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMPIFGREATER>(pm.il, addr, 2u));
                                          } else {
                                                pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMPIFLESSEQUAL>(pm.il, addr, 2u));
                                          }
                                          break;
                                    }
                                    default: {
                                          break;
                                    }
                              }
                              break;
                        }
                        case OpCode::OP_TEST: {

                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMPS>(pm.il, addr, dis, org->operands.front()->reg);
                              if (org->operands.back()->val) {
                                    pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMPIF>(pm.il, addr, 2u));
                              } else {
                                    pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMPIFNOT>(pm.il, addr, 2u));
                              }
                              break;
                        }
                        case OpCode::OP_TESTSET: {

                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMPS>(pm.il, addr, dis, org->operands[1u]->val);
                              if (org->operands.back()->val) {
                                    pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMPIF>(pm.il, addr, 2u));
                              } else {
                                    pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_JUMPIFNOT>(pm.il, addr, 2u));
                              }
                              pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_MOVE>(pm.il, addr, org->operands.front()->val, org->operands[1u]->val));
                              break;
                        }
                        case OpCode::OP_CLOSURE: {

                              const auto bx = dis->operands.back()->dis.val;
                              const auto &cprot = org->p->p[bx];
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_NEWCLOSURE>(pm.il, addr, dis, org->operands.front()->reg, bx);

                              for (auto ci = 0; ci < cprot->sizeupvalues; ++ci) {

                                    const auto upv = cprot->upvalues[ci];
                                    const auto int_k = upv.instack ? luramas::il::arch::operand::upvalue_kind::reference : luramas::il::arch::operand::upvalue_kind::upvalues;
                                    pm.il->insert(addr, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_ADDUPVALUE>(pm.il, addr, static_cast<std::uint8_t>(int_k), upv.idx));
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }
            };
            return;
      }

      void jumps(luramas::il::lifter::parser::parser_manager<std::shared_ptr<lua_53_disassembler::disassembly>> &pm) {

            /* Set ref to disassembly instructions */
            for (const auto &i : pm.il->dis) {
                  for (const auto &o : i->operands) {
                        if (!i->ref && o->type == luramas::il::arch::operand::operand_kind::jmp) {
                              i->ref = pm.il->visit(o->ref_addr);
                              break;
                        }
                  }
            }

            /* Set ref to pending insertions */
            for (const auto &[i, v] : pm.il->insertions) {
                  for (const auto &d : v) {
                        for (const auto &o : d->operands) {
                              if (!d->ref && o->type == luramas::il::arch::operand::operand_kind::jmp) {
                                    d->ref = pm.il->visit(o->ref_addr);
                                    break;
                              }
                        }
                  }
            }
            return;
      }

} // namespace lua_53_parsers
#endif