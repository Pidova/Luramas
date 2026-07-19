#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)
#include "parser.hpp"
#include "../../../../../il/architecture/emitter.hpp"
#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <unordered_map>
#include <vector>

luramas::il::arch::data::kval_kinds kv(lua_Type t) {
      switch (t) {
            case lua_Type::LUA_TNIL: {
                  return luramas::il::arch::data::kval_kinds::none;
            }
            case lua_Type::LUA_TBOOLEAN: {
                  return luramas::il::arch::data::kval_kinds::boolean;
            }
            case lua_Type::LUA_TNUMBER: {
                  return luramas::il::arch::data::kval_kinds::integer;
            }
            case lua_Type::LUA_TVECTOR: {
                  return luramas::il::arch::data::kval_kinds::vector;
            }
            case lua_Type::LUA_TSTRING: {
                  return luramas::il::arch::data::kval_kinds::string;
            }
            case lua_Type::LUA_TTABLE: {
                  return luramas::il::arch::data::kval_kinds::table;
            }
            case lua_Type::LUA_TFUNCTION: {
                  return luramas::il::arch::data::kval_kinds::function;
            }
            case lua_Type::LUA_TLIGHTUSERDATA:
            case lua_Type::LUA_TUSERDATA: {
                  return luramas::il::arch::data::kval_kinds::userdata;
            }
            case lua_Type::LUA_TTHREAD: {
                  return luramas::il::arch::data::kval_kinds::thread;
            }
            case lua_Type::LUA_TBUFFER: {
                  return luramas::il::arch::data::kval_kinds::integer;
            }
            case lua_Type::LUA_TPROTO: {
                  return luramas::il::arch::data::kval_kinds::function;
            }
            case lua_Type::LUA_TUPVAL: {
                  return luramas::il::arch::data::kval_kinds::upvalue;
            }
            default: {
                  return luramas::il::arch::data::kval_kinds::nothing;
            }
      }
}

namespace luau_v6_parsers {

      void parse_instructions(luramas::il::lifter::parser::parser_manager<std::shared_ptr<luau_v6_disassembler::disassembly>> &pm) {

            luramas_address pc = 0u;
            luramas_register override_top = 0u;
            luramas_register stack_top = 0u;
            luramas_register prev_stack_top = 0u;
            std::vector<std::shared_ptr<luau_v6_disassembler::operand>> sorted_operands;
            for (auto idx = 0u; idx < pm.dism.size(); ++idx) {

                  const auto i = pm.dism[idx];
                  auto ptr = std::make_shared<luramas::il::disassembly>();
                  sorted_operands.clear();

                  auto op = luramas::il::arch::opcodes::OP_NOP;

                  luramas_register append_top = 0u; /* Append top at the end of operands. */

                  /* Set data (Can not be optable because some stuff may need too resolved dynamically) */
                  switch (i->op) {

                        case LuauOpcode::LOP_LOADNIL: {
                              op = luramas::il::arch::opcodes::OP_LOADNONE;
                              sorted_operands = {i->operands.front()};
                              break;
                        }
                        case LuauOpcode::LOP_LOADB: {
                              op = luramas::il::arch::opcodes::OP_LOADBOOL;
                              sorted_operands = {i->operands.front(), i->operands[1]};
                              break;
                        }
                        case LuauOpcode::LOP_LOADN: {
                              op = luramas::il::arch::opcodes::OP_LOADINT;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_LOADK: {
                              op = luramas::il::arch::opcodes::OP_LOADKVAL;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_LOADKX: {
                              op = luramas::il::arch::opcodes::OP_LOADKVAL;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_MOVE: {
                              op = luramas::il::arch::opcodes::OP_MOVE;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_GETGLOBAL: {
                              op = luramas::il::arch::opcodes::OP_LOADGLOBAL;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_SETGLOBAL: {
                              op = luramas::il::arch::opcodes::OP_SETGLOBAL;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_GETUPVAL: {
                              op = luramas::il::arch::opcodes::OP_GETUPVALUE;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_SETUPVAL: {
                              op = luramas::il::arch::opcodes::OP_SETUPVALUE;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_GETTABLE: {
                              op = luramas::il::arch::opcodes::OP_GETTABLE;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_SETTABLE: {
                              op = luramas::il::arch::opcodes::OP_SETTABLE;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_GETTABLEN: {
                              op = luramas::il::arch::opcodes::OP_GETTABLEN;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_SETTABLEN: {
                              op = luramas::il::arch::opcodes::OP_SETTABLEN;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_GETTABLEKS: {
                              op = luramas::il::arch::opcodes::OP_GETTABLEK;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_SETTABLEKS: {
                              op = luramas::il::arch::opcodes::OP_SETTABLEK;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_ADD: {
                              op = luramas::il::arch::opcodes::OP_ADD;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_SUB: {
                              op = luramas::il::arch::opcodes::OP_SUB;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_MUL: {
                              op = luramas::il::arch::opcodes::OP_MUL;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_DIV: {
                              op = luramas::il::arch::opcodes::OP_DIV;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_IDIV: {
                              op = luramas::il::arch::opcodes::OP_IDIV;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_MOD: {
                              op = luramas::il::arch::opcodes::OP_MOD;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_POW: {
                              op = luramas::il::arch::opcodes::OP_POW;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_AND: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back(), luau_v6_disassembler::make_operand::make_operand_val(LuauOpcode::LOP_AND)};
                              break;
                        }
                        case LuauOpcode::LOP_OR: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back(), luau_v6_disassembler::make_operand::make_operand_val(LuauOpcode::LOP_OR)};
                              break;
                        }
                        case LuauOpcode::LOP_ADDK: {
                              op = luramas::il::arch::opcodes::OP_ADDK;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_SUBK: {
                              op = luramas::il::arch::opcodes::OP_SUBK;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_MULK: {
                              op = luramas::il::arch::opcodes::OP_MULK;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_DIVRK: {
                              op = luramas::il::arch::opcodes::OP_DIVK;
                              sorted_operands = {i->operands.front(), i->operands.back(), i->operands[1]};
                              break;
                        }
                        case LuauOpcode::LOP_SUBRK: {
                              op = luramas::il::arch::opcodes::OP_SUBK;
                              sorted_operands = {i->operands.front(), i->operands.back(), i->operands[1]};
                              break;
                        }
                        case LuauOpcode::LOP_IDIVK: {
                              op = luramas::il::arch::opcodes::OP_IDIVK;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_DIVK: {
                              op = luramas::il::arch::opcodes::OP_DIVK;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_MODK: {
                              op = luramas::il::arch::opcodes::OP_MODK;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_POWK: {
                              op = luramas::il::arch::opcodes::OP_POWK;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_ANDK: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back(), luau_v6_disassembler::make_operand::make_operand_val(LuauOpcode::LOP_ANDK)};
                              break;
                        }
                        case LuauOpcode::LOP_ORK: {
                              op = luramas::il::arch::opcodes::OP_PEND;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back(), luau_v6_disassembler::make_operand::make_operand_val(LuauOpcode::LOP_ORK)};
                              break;
                        }
                        case LuauOpcode::LOP_CONCAT: {
                              op = luramas::il::arch::opcodes::OP_CONCAT;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_CALL: {
                              op = luramas::il::arch::opcodes::OP_CCALL;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_RETURN: {
                              op = luramas::il::arch::opcodes::OP_RETURN;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_MINUS: {
                              op = luramas::il::arch::opcodes::OP_MINUS;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_LENGTH: {
                              op = luramas::il::arch::opcodes::OP_LEN;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_NOT: {
                              op = luramas::il::arch::opcodes::OP_NOT;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_CAPTURE: {
                              op = luramas::il::arch::opcodes::OP_ADDUPVALUE;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }

                        case LuauOpcode::LOP_CLOSEUPVALS: {
                              op = luramas::il::arch::opcodes::OP_DESTROYUPVALUESA;
                              sorted_operands = {i->operands.front()};
                              break;
                        }
                        case LuauOpcode::LOP_NEWCLOSURE: {
                              op = luramas::il::arch::opcodes::OP_NEWCLOSURE;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_DUPCLOSURE: {
                              op = luramas::il::arch::opcodes::OP_REFCLOSURE;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_NAMECALL: {
                              op = luramas::il::arch::opcodes::OP_SELF;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_NEWTABLE: {
                              op = luramas::il::arch::opcodes::OP_NEWTABLEA;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_DUPTABLE: {
                              op = luramas::il::arch::opcodes::OP_REFTABLEA;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_SETLIST: {
                              op = luramas::il::arch::opcodes::OP_SETLIST;
                              sorted_operands = {i->operands.front(), i->operands[1], i->operands[2], i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_GETVARARGS: {
                              op = luramas::il::arch::opcodes::OP_GETVARIADIC;
                              sorted_operands = {i->operands.front(), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_PREPVARARGS: {
                              op = luramas::il::arch::opcodes::OP_INIT;
                              break;
                        }
                        case LuauOpcode::LOP_FORNPREP: {
                              const auto limit = luau_v6_disassembler::make_operand::make_operand_reg(i->operands.front()->reg);
                              const auto step = luau_v6_disassembler::make_operand::make_operand_reg(i->operands.front()->reg + 1u);
                              const auto start = luau_v6_disassembler::make_operand::make_operand_reg(i->operands.front()->reg + 2u);
                              op = luramas::il::arch::opcodes::OP_INITFORLOOPN;
                              sorted_operands = {start, limit, step, i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_FORGPREP_NEXT: {
                              const auto start = luau_v6_disassembler::make_operand::make_operand_reg(i->operands.front()->reg);
                              const auto end = luau_v6_disassembler::make_operand::make_operand_reg(i->operands.front()->reg + 1u);
                              const auto step = luau_v6_disassembler::make_operand::make_operand_reg(i->operands.front()->reg + 2u);

                              std::shared_ptr<luau_v6_disassembler::disassembly> jb = nullptr;
                              for (auto x = idx; x < pm.dism.size(); ++x) {
                                    const auto &xi = pm.dism[x];
                                    if (xi->op == LuauOpcode::LOP_FORGLOOP && (xi->operands[1u]->ref_addr - 1u) == i->addr) {
                                          jb = xi;
                                          break;
                                    }
                              }
                              if (jb == nullptr) {
                                    luramas::error::error("Could not find forgprep jumpback.");
                              }
                              op = luramas::il::arch::opcodes::OP_INITFORLOOPG;
                              sorted_operands = {i->operands.front(), luau_v6_disassembler::make_operand::make_operand_val(2u), luau_v6_disassembler::make_operand::make_operand_jump(jb->operands[1]->jmp, i->addr)};
                              break;
                        }
                        case LuauOpcode::LOP_FORGPREP_INEXT: {
                              const auto start = luau_v6_disassembler::make_operand::make_operand_reg(i->operands.front()->reg);
                              const auto end = luau_v6_disassembler::make_operand::make_operand_reg(i->operands.front()->reg + 1u);
                              const auto step = luau_v6_disassembler::make_operand::make_operand_reg(i->operands.front()->reg + 2u);

                              std::shared_ptr<luau_v6_disassembler::disassembly> jb = nullptr;
                              for (auto x = idx; x < pm.dism.size(); ++x) {
                                    const auto &xi = pm.dism[x];
                                    if (xi->op == LuauOpcode::LOP_FORGLOOP && (xi->operands[1u]->ref_addr - 1u) == i->addr) {
                                          jb = xi;
                                          break;
                                    }
                              }
                              if (jb == nullptr) {
                                    luramas::error::error("Could not find forgprep jumpback.");
                              }
                              op = luramas::il::arch::opcodes::OP_INITFORLOOPSPECIAL;
                              sorted_operands = {start, end, step, luau_v6_disassembler::make_operand::make_operand_val(2u), luau_v6_disassembler::make_operand::make_operand_jump(jb->operands[1]->jmp, i->addr)};
                              break;
                        }
                        case LuauOpcode::LOP_FORGPREP: {
                              std::shared_ptr<luau_v6_disassembler::operand> amount = nullptr;
                              const auto target = i->addr + i->operands.back()->jmp + 1u;
                              for (auto x = idx; x < pm.dism.size(); ++x) {
                                    const auto &xi = pm.dism[x];
                                    if (xi->addr == target) {
                                          amount = luau_v6_disassembler::make_operand::make_operand_val(xi->operands.back()->val);
                                          break;
                                    }
                              }
                              if (amount == nullptr) {
                                    luramas::error::error("Could not find forgloop jumpback.");
                              }
                              op = luramas::il::arch::opcodes::OP_INITFORLOOPG;
                              sorted_operands = {i->operands.front(), amount, i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_FORNLOOP: {
                              /* CONTAINS STATICALLY TYPED OPERANDS (FOLLOWS FORMAT) */
                              op = luramas::il::arch::opcodes::OP_FORLOOPN;
                              sorted_operands = {luau_v6_disassembler::make_operand::make_operand_reg(i->operands.front()->reg + 2u), i->operands.front(), luau_v6_disassembler::make_operand::make_operand_reg(i->operands.front()->reg + 1u), i->operands.back()};
                              break;
                        }
                        case LuauOpcode::LOP_FORGLOOP: {
                              op = luramas::il::arch::opcodes::OP_FORLOOPG;
                              sorted_operands = {i->operands.front(), i->operands.back(), i->operands[1]};
                              break;
                        }
                        case LuauOpcode::LOP_GETIMPORT: {
                              op = luramas::il::arch::opcodes::OP_GETTABUPVALUE;
                              sorted_operands = {i->operands.front(), i->operands[1]};
                              break;
                        }
                        case LuauOpcode::LOP_JUMPBACK: {
                              op = luramas::il::arch::opcodes::OP_JUMP;
                              sorted_operands = {i->operands.front()};
                              break;
                        }
                        case LuauOpcode::LOP_JUMP:
                        case LuauOpcode::LOP_JUMPX: {
                              op = luramas::il::arch::opcodes::OP_JUMP;
                              sorted_operands = {i->operands.front()};
                              break;
                        }
                        default: {
                              break;
                        }
                  }

                  /* Data */
                  ptr->op = op;
                  ptr->addr = pc;

                  /* Parse operands */
                  for (const auto &oper : sorted_operands) {

                        auto operand_ptr = std::make_shared<luramas::il::arch::operand::operand>();

                        /* Data */
                        switch (oper->type) {
                              case op_table::type::capture_idx: {

                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::upvalue_kind;

                                    /* LuaU capture types. */
                                    switch (oper->capture_ref) {

                                          case LuauCaptureType::LCT_UPVAL: {
                                                operand_ptr->dis.upvalue_kind = luramas::il::arch::operand::upvalue_kind::upvalues;
                                                break;
                                          }
                                          case LuauCaptureType::LCT_VAL: {
                                                operand_ptr->dis.upvalue_kind = luramas::il::arch::operand::upvalue_kind::contents;
                                                break;
                                          }
                                          case LuauCaptureType::LCT_REF: {
                                                operand_ptr->dis.upvalue_kind = luramas::il::arch::operand::upvalue_kind::reference;
                                                break;
                                          }
                                          default: {
                                                break;
                                          }
                                    }
                                    break;
                              }
                              case op_table::type::capture_ref: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::upvalue_capture;
                                    operand_ptr->dis.upvalue_reg = oper->capture_reg;
                                    break;
                              }
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

                                    /* Multret value. */
                                    if (oper->val == LUA_MULTRET) {
                                          operand_ptr->dis.val = override_top ? override_top : (prev_stack_top > stack_top) ? prev_stack_top
                                                                                                                            : stack_top;
                                          operand_ptr->multret = true;
                                    }
                                    break;
                              }
                              case op_table::type::integer: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::integer;
                                    operand_ptr->dis.integer = oper->integer;
                                    break;
                              }
                              case op_table::type::import_idx:
                              case op_table::type::k_value_nstr: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::kval_string;
                                    operand_ptr->k_value = oper->k_value;
                                    operand_ptr->k_value_kind = luramas::il::arch::data::kval_kinds::string;
                                    operand_ptr->dis.kvalue_idx = oper->k_idx;
                                    break;
                              }
                              case op_table::type::closure: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::closure_index;
                                    operand_ptr->dis.closure_idx = oper->closure;
                                    break;
                              }
                              case op_table::type::upvalue: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::upvalue;
                                    operand_ptr->dis.upvalue_idx = oper->upvalue;
                                    break;
                              }
                              case op_table::type::k_idx:
                              case op_table::type::k_idx_pp:
                              case op_table::type::k_idx_aux: {
                                    operand_ptr->type = luramas::il::arch::operand::operand_kind::kval;
                                    operand_ptr->k_value = oper->k_value;
                                    operand_ptr->k_value_kind = kv(oper->k_value_type);
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
                              override_top = sorted_operands.front()->reg;
                        }
                  }
                  pc += i->len;
            }
            return;
      };

      void parse_compares(luramas::il::lifter::parser::parser_manager<std::shared_ptr<luau_v6_disassembler::disassembly>> &pm) {

            for (auto i = 0u; i < pm.dism.size(); ++i) {

                  const auto &curr = pm.dism[i];

                  /* Jump with compare == logical compare. */
                  const auto setcmp = (pm.dism.back() != curr && pm.dism[i + 1u]->op == LuauOpcode::LOP_LOADB && pm.dism[i + 1u]->operands.back()->jmp && pm.dism[i + 2u]->op == LuauOpcode::LOP_LOADB);
                  switch (curr->op) {
                        case LuauOpcode::LOP_JUMPIF: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMPS>(pm.il, curr->addr, ptr, curr->operands.front()->reg);
                              pm.il->insert(i, ptr);

                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIF>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands.back()->ref_addr);
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIF>(pm.il, curr->addr, ptr, ptr->ref->addr);
                                    pm.il->insert(i, ptr);
                              }

                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFNOT: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMPS>(pm.il, curr->addr, ptr, curr->operands.front()->reg);
                              pm.il->insert(i, ptr);

                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFNOT>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands.back()->ref_addr);
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFNOT>(pm.il, curr->addr, ptr, ptr->ref->addr);
                                    pm.il->insert(i, ptr);
                              }
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFEQ: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMP>(pm.il, curr->addr, ptr, curr->operands.front()->reg, curr->operands.back()->reg);
                              pm.il->insert(i, ptr);

                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands[1u]->ref_addr);
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFEQUAL>(pm.il, curr->addr, ptr, ptr->ref->addr);
                                    pm.il->insert(i, ptr);
                              }
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFLE: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMP>(pm.il, curr->addr, ptr, curr->operands.front()->reg, curr->operands.back()->reg);
                              pm.il->insert(i, ptr);

                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFLESSEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands[1u]->ref_addr);
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFLESSEQUAL>(pm.il, curr->addr, ptr, ptr->ref->addr);
                                    pm.il->insert(i, ptr);
                              }
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFLT: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMP>(pm.il, curr->addr, ptr, curr->operands.front()->reg, curr->operands.back()->reg);
                              pm.il->insert(i, ptr);

                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFLESS>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands[1u]->ref_addr);
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFLESS>(pm.il, curr->addr, ptr, ptr->ref->addr);
                                    pm.il->insert(i, ptr);
                              }
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFNOTEQ: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMP>(pm.il, curr->addr, ptr, curr->operands.front()->reg, curr->operands.back()->reg);
                              pm.il->insert(i, ptr);

                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFNOTEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands[1u]->ref_addr);
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFNOTEQUAL>(pm.il, curr->addr, ptr, ptr->ref->addr);
                                    pm.il->insert(i, ptr);
                              }
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFNOTLE: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMP>(pm.il, curr->addr, ptr, curr->operands.front()->reg, curr->operands.back()->reg);
                              pm.il->insert(i, ptr);

                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFGREATEREQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands[1u]->ref_addr);
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFGREATEREQUAL>(pm.il, curr->addr, ptr, ptr->ref->addr);
                                    pm.il->insert(i, ptr);
                              }
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFNOTLT: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMP>(pm.il, curr->addr, ptr, curr->operands.front()->reg, curr->operands.back()->reg);
                              pm.il->insert(i, ptr);

                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFGREATER>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands[1u]->ref_addr);
                                    luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFGREATER>(pm.il, curr->addr, ptr, ptr->ref->addr);
                                    pm.il->insert(i, ptr);
                              }
                              break;
                        }
                        case LuauOpcode::LOP_JUMPXEQKNIL: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMPNONE>(pm.il, curr->addr, ptr, curr->operands.front()->reg);
                              pm.il->insert(i, ptr);

                              const bool opposite = curr->operands.back()->code >> 31;
                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    if (opposite) {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFNOTEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    } else {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    }
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands[1u]->ref_addr);
                                    if (opposite) {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFNOTEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    } else {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    }
                                    pm.il->insert(i, ptr);
                              }
                              break;
                        }
                        case LuauOpcode::LOP_JUMPXEQKB: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMPB>(pm.il, curr->addr, ptr, curr->operands.front()->reg, bool(curr->operands.back()->val));
                              pm.il->insert(i, ptr);

                              const bool opposite = curr->operands.back()->code >> 31;
                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    if (opposite) {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFNOTEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    } else {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    }
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands[1u]->ref_addr);
                                    if (opposite) {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFNOTEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    } else {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    }
                                    pm.il->insert(i, ptr);
                              }
                              break;
                        }
                        case LuauOpcode::LOP_JUMPXEQKN: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMPN>(pm.il, curr->addr, ptr, curr->operands.front()->reg, pm.il->kval[curr->operands.back()->k_idx]->integer.i);
                              pm.il->insert(i, ptr);

                              const bool opposite = curr->operands.back()->code >> 31;
                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    if (opposite) {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFNOTEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    } else {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    }
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands[1u]->ref_addr);
                                    if (opposite) {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFNOTEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    } else {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    }
                                    pm.il->insert(i, ptr);
                              }
                              break;
                        }
                        case LuauOpcode::LOP_JUMPXEQKS: {

                              auto ptr = std::make_shared<luramas::il::disassembly>();
                              luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_CMPK>(pm.il, curr->addr, ptr, curr->operands.front()->reg, curr->operands.back()->k_idx);
                              pm.il->insert(i, ptr);

                              const bool opposite = curr->operands.back()->code >> 31;
                              if (setcmp) {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    if (opposite) {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFNOTEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    } else {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_SETIFEQUAL>(pm.il, curr->addr, ptr, pm.dism[i + 1u]->operands.front()->reg);
                                    }
                                    pm.il->insert(i, ptr);
                                    pm.il->remove(pm.il->dis[i + 1u]);
                                    pm.il->remove(pm.il->dis[i + 2u]);
                              } else {
                                    ptr = std::make_shared<luramas::il::disassembly>();
                                    ptr->ref = pm.il->visit(curr->operands[1u]->ref_addr);
                                    if (opposite) {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFNOTEQUAL>(pm.il, curr->addr, ptr, ptr->ref->addr);
                                    } else {
                                          luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMPIFEQUAL>(pm.il, curr->addr, ptr, ptr->ref->addr);
                                    }
                                    pm.il->insert(i, ptr);
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

      void parse_jumps(luramas::il::lifter::parser::parser_manager<std::shared_ptr<luau_v6_disassembler::disassembly>> &pm) {

            for (const auto &i : pm.il->dis) {
                  for (const auto &o : i->operands) {
                        if (o->type == luramas::il::arch::operand::operand_kind::jmp) {
                              i->ref = pm.il->visit(o->ref_addr);
                              break;
                        }
                  }
            }
            return;
      }

      void parse_boolean_jumps(luramas::il::lifter::parser::parser_manager<std::shared_ptr<luau_v6_disassembler::disassembly>> &pm) {

            for (auto i = 0u; i < pm.dism.size(); ++i) {

                  const auto &curr = pm.dism[i];
                  if (curr->op == LuauOpcode::LOP_LOADB && curr->operands.back()->jmp && !pm.il->is_remove(pm.il->dis[i])) {

                        auto ptr = std::make_shared<luramas::il::disassembly>();
                        ptr->ref = pm.il->visit(curr->operands.back()->ref_addr);
                        luramas::il::emitter::emit_opcode<luramas::il::arch::opcodes::OP_JUMP>(pm.il, curr->addr, ptr, ptr->ref->addr);
                        pm.il->insert(i, ptr);
                  }
            }
            return;
      }

      void parse_debug(luramas::il::lifter::parser::parser_manager<std::shared_ptr<luau_v6_disassembler::disassembly>> &pm, Proto *p) {

            boost::unordered_flat_map<luramas_address, std::shared_ptr<luramas::il::disassembly>> marked_map;
            if (!pm.il->debug.has_value()) {
                  luramas::il::ilang::debug_manager dbg(pm.il);
                  pm.il->debug.emplace(dbg);
            }
            for (auto i = 0u; i < p->sizelocvars; ++i) {
                  const auto &dbg = p->locvars[i];

                  marked_map.try_emplace(dbg.startpc, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_MARK>(pm.il, dbg.startpc));
                  marked_map.try_emplace(dbg.endpc, luramas::il::emitter::generate_opcode<luramas::il::arch::opcodes::OP_MARK>(pm.il, dbg.endpc));

                  const auto &start = marked_map[dbg.startpc];
                  const auto &end = marked_map[dbg.endpc];

                  pm.il->insert_front(pm.il->visit(dbg.startpc), start);
                  pm.il->insert_original_unsafe(dbg.endpc, end);
                  pm.il->debug.value().add(dbg.reg, start, end, dbg.varname->data);
            }
            return;
      }
} // namespace luau_v6_parsers
#endif