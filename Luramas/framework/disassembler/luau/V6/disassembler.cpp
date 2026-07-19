#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)
#include "disassembler.hpp"
#include <iostream>

enum set_action : std::uint8_t {
      instruction, /* Sets all instruction info, op, mnenomic, hint. */
      operands     /* Sets all operands including details about it. */
};

template <set_action n>
void set_data(std::shared_ptr<luau_v6_disassembler::disassembly> &buffer, const Proto *p, const op_table::optable op_table) {

      switch (n) {

            case set_action::instruction: {

                  buffer->op = op_table.op;
                  switch (buffer->op) {
                        case LuauOpcode::LOP_ADD: {
                              buffer->mnenomic = "add";
                              buffer->hint = "Addition.";
                              break;
                        }
                        case LuauOpcode::LOP_ADDK: {
                              buffer->mnenomic = "addk";
                              buffer->hint = "Addition with constant.";
                              break;
                        }
                        case LuauOpcode::LOP_AND: {
                              buffer->mnenomic = "and";
                              buffer->hint = "And.";
                              break;
                        }
                        case LuauOpcode::LOP_ANDK: {
                              buffer->mnenomic = "andk";
                              buffer->hint = "And with constant.";
                              break;
                        }
                        case LuauOpcode::LOP_BREAK: {
                              buffer->mnenomic = "break";
                              buffer->hint = "Break.";
                              break;
                        }
                        case LuauOpcode::LOP_CALL: {
                              buffer->mnenomic = "call";
                              buffer->hint = "Call routine.";
                              break;
                        }
                        case LuauOpcode::LOP_CAPTURE: {
                              buffer->mnenomic = "capture";
                              buffer->hint = "Capture operation.";
                              break;
                        }
                        case LuauOpcode::LOP_CLOSEUPVALS: {
                              buffer->mnenomic = "closeupvals";
                              buffer->hint = "Close upvalues.";
                              break;
                        }
                        case LuauOpcode::LOP_CONCAT: {
                              buffer->mnenomic = "concat";
                              buffer->hint = "Concat strings.";
                              break;
                        }
                        case LuauOpcode::LOP_FORGPREP_INEXT: {
                              buffer->mnenomic = "forgprep_inext";
                              buffer->hint = "For loop with (i)next.";
                              break;
                        }
                        case LuauOpcode::LOP_FORGPREP_NEXT: {
                              buffer->mnenomic = "forgprep_next";
                              buffer->hint = "For loop prep with next.";
                              break;
                        }
                        case LuauOpcode::LOP_DIV: {
                              buffer->mnenomic = "div";
                              buffer->hint = "Divide.";
                              break;
                        }
                        case LuauOpcode::LOP_DIVK: {
                              buffer->mnenomic = "divk";
                              buffer->hint = "Divide with constant.";
                              break;
                        }
                        case LuauOpcode::LOP_DUPCLOSURE: {
                              buffer->mnenomic = "dupclosure";
                              buffer->hint = "Dupe closure.";
                              break;
                        }
                        case LuauOpcode::LOP_DUPTABLE: {
                              buffer->mnenomic = "duptable";
                              buffer->hint = "Dupe table.";
                              break;
                        }
                        case LuauOpcode::LOP_FASTCALL: {
                              buffer->mnenomic = "fastcall";
                              buffer->hint = "Fastcall.";
                              break;
                        }
                        case LuauOpcode::LOP_FASTCALL1: {
                              buffer->mnenomic = "fastcall1";
                              buffer->hint = "Fastcall.";
                              break;
                        }
                        case LuauOpcode::LOP_FASTCALL2: {
                              buffer->mnenomic = "fastcall2";
                              buffer->hint = "Fastcall.";
                              break;
                        }
                        case LuauOpcode::LOP_FASTCALL3: {
                              buffer->mnenomic = "fastcall3";
                              buffer->hint = "Fastcall.";
                              break;
                        }
                        case LuauOpcode::LOP_FASTCALL2K: {
                              buffer->mnenomic = "fastcall2k";
                              buffer->hint = "Fastcall with constant.";
                              break;
                        }
                        case LuauOpcode::LOP_FORGLOOP: {
                              buffer->mnenomic = "forgloop";
                              buffer->hint = "For generic loop.";
                              break;
                        }
                        case LuauOpcode::LOP_FORGPREP: {
                              buffer->mnenomic = "forgprep";
                              buffer->hint = "For generic prepare.";
                              break;
                        }
                        case LuauOpcode::LOP_FORNLOOP: {
                              buffer->mnenomic = "fornloop";
                              buffer->hint = "For numeric loop.";
                              break;
                        }
                        case LuauOpcode::LOP_FORNPREP: {
                              buffer->mnenomic = "fornprep";
                              buffer->hint = "For numeric loop.";
                              break;
                        }
                        case LuauOpcode::LOP_GETGLOBAL: {
                              buffer->mnenomic = "getglobal";
                              buffer->hint = "Get global.";
                              break;
                        }
                        case LuauOpcode::LOP_GETIMPORT: {
                              buffer->mnenomic = "getimport";
                              buffer->hint = "Get import.";
                              break;
                        }
                        case LuauOpcode::LOP_GETTABLE: {
                              buffer->mnenomic = "gettable";
                              buffer->hint = "Get table.";
                              break;
                        }
                        case LuauOpcode::LOP_GETTABLEKS: {
                              buffer->mnenomic = "gettableks";
                              buffer->hint = "Get table constant.";
                              break;
                        }
                        case LuauOpcode::LOP_GETTABLEN: {
                              buffer->mnenomic = "gettablen";
                              buffer->hint = "Get tabble numeric.";
                              break;
                        }
                        case LuauOpcode::LOP_GETUPVAL: {
                              buffer->mnenomic = "getupval";
                              buffer->hint = "Get upvalue.";
                              break;
                        }
                        case LuauOpcode::LOP_GETVARARGS: {
                              buffer->mnenomic = "getvarargs";
                              buffer->hint = "Get variable args.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMP: {
                              buffer->mnenomic = "jump";
                              buffer->hint = "Jump.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPBACK: {
                              buffer->mnenomic = "jumpback";
                              buffer->hint = "Jumpback.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIF: {
                              buffer->mnenomic = "jumpif";
                              buffer->hint = "Jump if.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFEQ: {
                              buffer->mnenomic = "jumpifeq";
                              buffer->hint = "Jump if equal.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFLE: {
                              buffer->mnenomic = "jumpifle";
                              buffer->hint = "Jump if less then or equal.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFLT: {
                              buffer->mnenomic = "jumpiflt";
                              buffer->hint = "Jump if less then.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFNOT: {
                              buffer->mnenomic = "jumpifnot";
                              buffer->hint = "Jump if not.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFNOTEQ: {
                              buffer->mnenomic = "jumpifnoteq";
                              buffer->hint = "Jump if not equal.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFNOTLE: {
                              buffer->mnenomic = "jumpifnotle";
                              buffer->hint = "Jump if not less then or equal.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPIFNOTLT: {
                              buffer->mnenomic = "jumpifnotlt";
                              buffer->hint = "Jump if not less then.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPX: {
                              buffer->mnenomic = "jumpx";
                              buffer->hint = "Jump long.";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPXEQKB: {
                              buffer->mnenomic = "jumpxeqkb";
                              buffer->hint = "Jump long if equal (constant, bool).";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPXEQKN: {
                              buffer->mnenomic = "jumpxeqkn";
                              buffer->hint = "Jump long if equal (constant, numeric).";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPXEQKNIL: {
                              buffer->mnenomic = "jumpxeqknil";
                              buffer->hint = "Jump long if equal (constant, nil).";
                              break;
                        }
                        case LuauOpcode::LOP_JUMPXEQKS: {
                              buffer->mnenomic = "jumpxeqks";
                              buffer->hint = "Jump long if equal (constant, string).";
                              break;
                        }
                        case LuauOpcode::LOP_LENGTH: {
                              buffer->mnenomic = "lenght";
                              buffer->hint = "Lenght.";
                              break;
                        }
                        case LuauOpcode::LOP_LOADB: {
                              buffer->mnenomic = "loadb";
                              buffer->hint = "Load boolean.";
                              break;
                        }
                        case LuauOpcode::LOP_LOADK: {
                              buffer->mnenomic = "loadk";
                              buffer->hint = "Load constant.";
                              break;
                        }
                        case LuauOpcode::LOP_LOADKX: {
                              buffer->mnenomic = "loadkx";
                              buffer->hint = "Load extra constant.";
                              break;
                        }
                        case LuauOpcode::LOP_LOADN: {
                              buffer->mnenomic = "loadn";
                              buffer->hint = "Load numeric.";
                              break;
                        }
                        case LuauOpcode::LOP_LOADNIL: {
                              buffer->mnenomic = "loadnil";
                              buffer->hint = "Load nil.";
                              break;
                        }
                        case LuauOpcode::LOP_MINUS: {
                              buffer->mnenomic = "minus";
                              buffer->hint = "Minus.";
                              break;
                        }
                        case LuauOpcode::LOP_MOD: {
                              buffer->mnenomic = "mod";
                              buffer->hint = "Mod.";
                              break;
                        }
                        case LuauOpcode::LOP_MODK: {
                              buffer->mnenomic = "modk";
                              buffer->hint = "Mod constant.";
                              break;
                        }
                        case LuauOpcode::LOP_MOVE: {
                              buffer->mnenomic = "move";
                              buffer->hint = "Move.";
                              break;
                        }
                        case LuauOpcode::LOP_NATIVECALL: {
                              buffer->mnenomic = "nativecall";
                              buffer->hint = "Native call.";
                              break;
                        }
                        case LuauOpcode::LOP_SUBRK: {
                              buffer->mnenomic = "subrk";
                              buffer->hint = "Subtraction rvalue.";
                              break;
                        }
                        case LuauOpcode::LOP_DIVRK: {
                              buffer->mnenomic = "divrk";
                              buffer->hint = "Division rvalue.";
                              break;
                        }
                        case LuauOpcode::LOP_IDIV: {
                              buffer->mnenomic = "idiv";
                              buffer->hint = "Floor division.";
                              break;
                        }
                        case LuauOpcode::LOP_IDIVK: {
                              buffer->mnenomic = "idivk";
                              buffer->hint = "Floor division constant.";
                              break;
                        }
                        case LuauOpcode::LOP_MUL: {
                              buffer->mnenomic = "mul";
                              buffer->hint = "Mul.";
                              break;
                        }
                        case LuauOpcode::LOP_MULK: {
                              buffer->mnenomic = "mulk";
                              buffer->hint = "Mul constant.";
                              break;
                        }
                        case LuauOpcode::LOP_NAMECALL: {
                              buffer->mnenomic = "namecall";
                              buffer->hint = "Namecall.";
                              break;
                        }
                        case LuauOpcode::LOP_NEWCLOSURE: {
                              buffer->mnenomic = "newclosure";
                              buffer->hint = "New closure.";
                              break;
                        }
                        case LuauOpcode::LOP_NEWTABLE: {
                              buffer->mnenomic = "newtable";
                              buffer->hint = "New table.";
                              break;
                        }
                        case LuauOpcode::LOP_NOP: {
                              buffer->mnenomic = "nop";
                              buffer->hint = "Nop.";
                              break;
                        }
                        case LuauOpcode::LOP_NOT: {
                              buffer->mnenomic = "not";
                              buffer->hint = "Not.";
                              break;
                        }
                        case LuauOpcode::LOP_OR: {
                              buffer->mnenomic = "or";
                              buffer->hint = "Or.";
                              break;
                        }
                        case LuauOpcode::LOP_ORK: {
                              buffer->mnenomic = "ork";
                              buffer->hint = "Or constant.";
                              break;
                        }
                        case LuauOpcode::LOP_POW: {
                              buffer->mnenomic = "pow";
                              buffer->hint = "Pow.";
                              break;
                        }
                        case LuauOpcode::LOP_POWK: {
                              buffer->mnenomic = "powk";
                              buffer->hint = "Pow constant.";
                              break;
                        }
                        case LuauOpcode::LOP_PREPVARARGS: {
                              buffer->mnenomic = "prepvarargs";
                              buffer->hint = "Prepare variable args.";
                              break;
                        }
                        case LuauOpcode::LOP_RETURN: {
                              buffer->mnenomic = "return";
                              buffer->hint = "Return.";
                              break;
                        }
                        case LuauOpcode::LOP_SETGLOBAL: {
                              buffer->mnenomic = "setglobal";
                              buffer->hint = "Set global.";
                              break;
                        }
                        case LuauOpcode::LOP_SETLIST: {
                              buffer->mnenomic = "setlist";
                              buffer->hint = "Set list table.";
                              break;
                        }
                        case LuauOpcode::LOP_SETTABLE: {
                              buffer->mnenomic = "settable";
                              buffer->hint = "Set table.";
                              break;
                        }
                        case LuauOpcode::LOP_SETTABLEKS: {
                              buffer->mnenomic = "settableks";
                              buffer->hint = "Set table constant.";
                              break;
                        }
                        case LuauOpcode::LOP_SETTABLEN: {
                              buffer->mnenomic = "settablen";
                              buffer->hint = "Settable numeric.";
                              break;
                        }
                        case LuauOpcode::LOP_SETUPVAL: {
                              buffer->mnenomic = "setupval";
                              buffer->hint = "Set upvalue.";
                              break;
                        }
                        case LuauOpcode::LOP_SUB: {
                              buffer->mnenomic = "sub";
                              buffer->hint = "Sub.";
                              break;
                        }
                        case LuauOpcode::LOP_SUBK: {
                              buffer->mnenomic = "subk";
                              buffer->hint = "Sub constant.";
                              break;
                        }
                        default: {
                              luramas::error::error("Unkown opcode in disassembler.");
                        }
                  }
                  break;
            }

            case set_action::operands: {

                  std::intptr_t AUX_CACHE = 0;
                  const auto op_count = op_table.operands.size();

                  for (auto i = 0u; i < op_count; ++i) {

                        auto current_operand = std::make_shared<luau_v6_disassembler::operand>();

                        std::intptr_t operand_value = 0;

                        const auto operand_encoding = op_table.operands[i];
                        const auto type = op_table.types[i];

                        const auto split = ((i + 1u) == op_count) ? " " : ", ";

                        /* Set operand value. */
                        switch (operand_encoding) {
                              case op_table::operands::A: {
                                    operand_value = decode_A(*buffer->code);
                                    break;
                              }
                              case op_table::operands::B: {
                                    operand_value = decode_B(*buffer->code);
                                    break;
                              }
                              case op_table::operands::C: {
                                    operand_value = decode_C(*buffer->code);
                                    break;
                              }
                              case op_table::operands::C_dec: {
                                    const auto c = decode_C(*buffer->code);
                                    operand_value = (c == 0u) ? static_cast<const std::intptr_t>(c) : static_cast<const std::intptr_t>(c - 1);
                                    break;
                              }
                              case op_table::operands::C_inc: {
                                    operand_value = decode_C(*buffer->code) + 1;
                                    break;
                              }
                              case op_table::operands::D: {
                                    operand_value = decode_D(*buffer->code);
                                    break;
                              }
                              case op_table::operands::E: {
                                    operand_value = decode_E(*buffer->code);
                                    break;
                              }
                              case op_table::operands::AUX: {
                                    operand_value = *(++buffer->code);
                                    if (std::int32_t(*buffer->code) < 0) {
                                          operand_value = (buffer->op == LuauOpcode::LOP_FORGLOOP) ? 1 : 0;
                                    }
                                    break;
                              }
                              case op_table::operands::AUX_24: {
                                    operand_value = *(++buffer->code) & 0xffffff;
                                    break;
                              }
                              case op_table::operands::AUX_cache: {
                                    AUX_CACHE = *(++buffer->code);
                                    break;
                              }
                              case op_table::operands::CACHE_LEAST_SIGNIFICANT: {
                                    operand_value = AUX_CACHE & 0xff;
                                    break;
                              }
                              case op_table::operands::CACHE_MOST_SIGNIFICANT: {
                                    operand_value = ((AUX_CACHE >> 8) & 0xff);
                                    break;
                              }
                              default: {
                                    luramas::error::error("Unkown operand type.");
                              }
                        }

                        /* Set type and operand. */
                        current_operand->type = type;
                        current_operand->encoding = operand_encoding;
                        current_operand->code = *buffer->code;

                        /* Set type. */
                        switch (current_operand->type) {
                              case op_table::type::capture_idx: {

                                    const auto on = *buffer->code;
                                    const auto tt = decode_A(on);

                                    current_operand->capture_ref = tt;

                                    buffer->data += std::to_string(tt) + split;
                                    break;
                              }
                              case op_table::type::capture_ref: {

                                    const auto on = *buffer->code;
                                    const auto tt = decode_A(on);
                                    const auto v = decode_B(on);

                                    current_operand->capture_reg = v;
                                    buffer->data += (tt == 2u ? "upvalue_" : "r") + std::to_string(v) + split;
                                    break;
                              }
                              case op_table::type::fastcall_idx: {
                                    buffer->data += std::string(op_table::fastcall_array[operand_value]) + split;
                                    current_operand->fastcall_idx = std::uint8_t(operand_value);
                                    break;
                              }
                              case op_table::type::table_size: {
                                    const auto size = (!operand_value ? 0 : (1 << (operand_value - 1)));
                                    buffer->data += std::to_string(size) + split;
                                    current_operand->table_size = size;
                                    break;
                              }
                              case op_table::type::closure: {
                                    buffer->data += "closure_index_" + std::to_string(operand_value) + split;
                                    current_operand->closure = operand_value;
                                    break;
                              }
                              case op_table::type::upvalue: {
                                    buffer->data += "upvalue_" + std::to_string(operand_value) + split;
                                    current_operand->upvalue = operand_value;
                                    break;
                              }
                              case op_table::type::slot: {
                                    buffer->data += std::to_string(operand_value) + split;
                                    current_operand->slot = operand_value;
                                    break;
                              }
                              case op_table::type::aux: {
                                    buffer->data += std::to_string(operand_value) + split;
                                    current_operand->aux = operand_value;
                                    break;
                              }
                              case op_table::type::jmp: {
                                    buffer->data += std::to_string(operand_value) + split;
                                    current_operand->jmp = operand_value;
                                    current_operand->ref_addr = current_operand->jmp + buffer->addr + 1u;
                                    break;
                              }
                              case op_table::type::reg:
                              case op_table::type::dest: {
                                    buffer->data += 'r' + std::to_string(operand_value) + split;
                                    current_operand->reg = luramas_register(operand_value);
                                    break;
                              }
                              case op_table::type::val: {
                                    buffer->data += std::to_string(operand_value) + split;
                                    current_operand->val = operand_value;
                                    break;
                              }
                              case op_table::type::boolean: {
                                    buffer->data += std::string((operand_value) ? "true" : "false") + split;
                                    current_operand->val = operand_value;
                                    break;
                              }
                              case op_table::type::integer: {
                                    buffer->data += std::to_string(operand_value) + split;
                                    current_operand->integer = static_cast<const double>(operand_value);
                                    break;
                              }
                              case op_table::type::k_idx_aux: {
                                    buffer->data += std::to_string(operand_value) + split;
                                    current_operand->val = operand_value;
                                    current_operand->k_value = std::to_string(current_operand->val);
                                    break;
                              }
                              case op_table::type::val_multret: {
                                    --operand_value;
                                    buffer->data += std::to_string(operand_value) + split;
                                    current_operand->val = operand_value;
                                    break;
                              }
                              case op_table::type::import_idx: {

                                    const auto source = buffer->code[1];
                                    const std::int32_t brco = source >> 30;

                                    const auto id1 = (brco > 0) ? std::int32_t(source >> 20) & 1023 : -1;
                                    const auto id2 = (brco > 1) ? std::int32_t(source >> 10) & 1023 : -1;
                                    const auto id3 = (brco > 2) ? std::int32_t(source) & 1023 : -1;

                                    if (id1 >= 0) {
                                          current_operand->k_value += gco2ts(p->k[id1].value.gc)->data;
                                    }
                                    if (id2 >= 0) {
                                          current_operand->k_value += std::string(".") + std::string(gco2ts(p->k[id2].value.gc)->data);
                                    }
                                    if (id3 >= 0) {
                                          current_operand->k_value += std::string(".") + std::string(gco2ts(p->k[id3].value.gc)->data);
                                    }

                                    buffer->data += current_operand->k_value + split;
                                    current_operand->import_idx = id3;
                                    break;
                              }
                              case op_table::type::k_value_nstr: {

                                    const auto kv = p->k[operand_value];
                                    const auto ts = gco2ts(kv.value.gc);
                                    current_operand->k_value.assign(ts->data, ts->len);
                                    luramas_str_escape(current_operand->k_value);
                                    buffer->data += current_operand->k_value + split;

                                    current_operand->k_idx = operand_value;
                                    break;
                              }
                              case op_table::type::k_idx_pp:
                              case op_table::type::k_idx: {

                                    const auto kv = p->k[operand_value];
                                    current_operand->k_value_type = static_cast<const lua_Type>(kv.tt);
                                    switch (kv.tt) {
                                          case lua_Type::LUA_TVECTOR: {
                                                /* Hack lol */
                                                const auto values = kv.value.v;
                                                const auto v1 = *values;
                                                const auto v2 = values[1];
                                                const auto v3 = values[2];
                                                current_operand->k_value = "Vector3.new(" + std::to_string(v1) + ", " + std::to_string(v2) + ", " + std::to_string(v3) + ")";
                                                break;
                                          }
                                          case lua_Type::LUA_TNIL: {
                                                current_operand->k_value = "nil";
                                                break;
                                          }
                                          case lua_Type::LUA_TBOOLEAN: {
                                                current_operand->k_value = std::to_string(kv.value.b);
                                                break;
                                          }
                                          case lua_Type::LUA_TNUMBER: {
                                                current_operand->k_value = std::to_string(kv.value.n);
                                                break;
                                          }
                                          case lua_Type::LUA_TSTRING: {
                                                const auto ts = gco2ts(kv.value.gc);
                                                current_operand->k_value.assign(ts->data, ts->len);
                                                luramas_str_escape(current_operand->k_value);
                                                current_operand->k_value.insert(0, 1, '\"');
                                                current_operand->k_value.push_back('\"');
                                                break;
                                          }
                                          case lua_Type::LUA_TLIGHTUSERDATA: {
                                                current_operand->k_value = "lightuserdata_" + std::to_string(operand_value);
                                                break;
                                          }
                                          case lua_Type::LUA_TFUNCTION: {

                                                if (type == op_table::type::k_idx_pp) {

                                                      for (auto i = 0; i < p->sizep; i++)
                                                            if (p->p[i] == gco2cl(kv.value.gc)->l.p) {
                                                                  operand_value = i;
                                                                  break;
                                                            }
                                                }
                                                current_operand->k_value = "closure_" + std::to_string(operand_value);
                                                break;
                                          }
                                          case lua_Type::LUA_TTABLE: {
                                                current_operand->k_value = "table_" + std::to_string(operand_value);
                                                break;
                                          }
                                          case lua_Type::LUA_TUSERDATA: {
                                                current_operand->k_value = "userdata_" + std::to_string(operand_value);
                                                break;
                                          }
                                          case lua_Type::LUA_TUPVAL: {
                                                current_operand->k_value = "upval_" + std::to_string(operand_value);
                                                break;
                                          }
                                          default: {
                                                luramas::error::error("Unknown lua type.");
                                          }
                                    }
                                    buffer->data += current_operand->k_value + split;
                                    current_operand->k_idx = operand_value;
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        buffer->operands.emplace_back(current_operand);
                  }
                  break;
            }
      }
      return;
}

void check_op(const std::uint8_t op) {
      if (op >= sizeof(op_table::op_table) / sizeof(op_table::op_table[0])) {
            luramas::error::error("Invalid lifter opcode");
      }
      return;
}

void luau_v6_disassembler::disassemble(const luramas_address addr, const Proto *p, std::shared_ptr<luau_v6_disassembler::disassembly> &buffer) {

      /* Get intruction and set instruction. */
      const auto op = std::uint8_t(decode_opcode(p->code[addr]));

      check_op(op);
      const auto code = op_table::op_table[op];
      set_data<set_action::instruction>(buffer, p, code);

      /* Set code. */
      const auto start_pc = p->code + addr;
      buffer->code = start_pc;
      buffer->addr = addr;

      /* Clear for next. */
      buffer->operands.clear();

      /* Init data. */
      buffer->data = std::string(buffer->mnenomic) + ' ';
      set_data<set_action::operands>(buffer, p, code);

      /* Calculate lenght. */
      buffer->len = (std::uint8_t(reinterpret_cast<const luramas_address>(buffer->code) - reinterpret_cast<const luramas_address>(start_pc)) / sizeof(Instruction)) + 1u;

      /* Bytes */
      for (auto i = 0u; i < buffer->len; ++i) {
            buffer->bytes.emplace_back(p->code[buffer->addr + i]);
      }
      return;
}

void luau_v6_disassembler::disassemble(const Proto *p, std::vector<std::shared_ptr<luau_v6_disassembler::disassembly>> &buffer) {

      for (auto pc = 0u; pc < unsigned(p->sizecode);) {
            auto dism = std::make_shared<luau_v6_disassembler::disassembly>();
            disassemble(pc, p, dism);
            buffer.emplace_back(dism);
            pc += dism->len;
      }
      return;
}
#endif