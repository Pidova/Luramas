#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)

#include "Lua_5.3.hpp"
#include "../../../../il/architecture/emitter.hpp"
#include "../../../../il/transformers/transformers.hpp"
#include "parser/parser.hpp"
#include "resolver/resolver.hpp"
#include <iostream>

namespace luramas::il::lifter {

      void lift(Proto *p, const std::vector<std::shared_ptr<lua_53_disassembler::disassembly>> &dism, std::shared_ptr<luramas::il::ilang> &buffer, const luramas_register start_tempreg) {

            buffer->ctemp_reg = start_tempreg;
            lifter::parser::parser_manager<std::shared_ptr<lua_53_disassembler::disassembly>> pm(buffer, dism, lua_53_parsers::instructions, false);
            lifter::resolver::resolver_manager<Proto *> rm(buffer, p);

            auto lift_closure = [](Proto *p, const luramas_register start_tempreg) -> std::shared_ptr<luramas::il::ilang> {
                  if (!p) {
                        luramas::error::error("Lifter proto is null");
                  }
                  auto result = std::make_shared<luramas::il::ilang>();
                  std::vector<std::shared_ptr<lua_53_disassembler::disassembly>> vect_dism;
                  for (auto pc = 0u; pc < unsigned(p->sizecode);) {
                        auto dism = std::make_shared<lua_53_disassembler::disassembly>();
                        lua_53_disassembler::disassemble(pc, p, dism);
                        vect_dism.emplace_back(dism);
                        pc += LURAMAS_INST_LEN;
                  }
                  luramas::il::lifter::lift(p, vect_dism, result, start_tempreg);
                  return result;
            };

            /* Parses Kvalues */
            for (auto i = 0; i < p->sizek; ++i) {

                  const auto &kval = p->k[i];
                  auto ptr = std::make_shared<ilang::kvalue>();
                  switch (kval.tt_ & 0x0F) {
                        case LUA_TNIL:
                        case LUA_TDEADKEY: {
                              ptr->type = arch::data::kval_kinds::none;
                              break;
                        }
                        case LUA_TBOOLEAN: {
                              ptr->type = arch::data::kval_kinds::boolean;
                              ptr->boolean.b = kval.value_.b;
                              break;
                        }
                        case LUA_TLIGHTUSERDATA: {
                              ptr->type = arch::data::kval_kinds::userdata;
                              ptr->userdata.str = "lightuserdata_" + std::to_string(i);
                              break;
                        }
                        case LUA_TNUMBER: {

                              ptr->type = arch::data::kval_kinds::integer;
                              ptr->integer.i = ttisinteger(&kval) ? static_cast<double>(kval.value_.i) : kval.value_.n;

                              /* String and remove trailing 0's */
                              ptr->integer.str = std::to_string(ptr->integer.i);
                              luramas_str_integer(ptr->integer.str);
                              break;
                        }
                        case LUA_TSTRING: {

                              ptr->type = arch::data::kval_kinds::string;
                              const auto data = getstr(gco2ts(kval.value_.gc));
                              if (!data) {
                                    luramas::error::error("String is nullptr");
                              }
                              ptr->string.str = data;
                              luramas_str_escape(ptr->string.str);
                              break;
                        }
                        case LUA_TTABLE: {
                              const auto t = gco2t(kval.value_.gc);
                              ptr->type = arch::data::kval_kinds::table;
                              ptr->table.array_size = t->sizearray;
                              ptr->table.node_size = t->lsizenode;
                              break;
                        }
                        case LUA_TFUNCTION: {
                              ptr->type = arch::data::kval_kinds::upvalue;
                              ptr->upvalue.str = "closure_" + std::to_string(i);
                              break;
                        }
                        case LUA_TUSERDATA: {
                              ptr->type = arch::data::kval_kinds::userdata;
                              ptr->userdata.str = "userdata_" + std::to_string(i);
                              break;
                        }
                        case LUA_TTHREAD: {
                              ptr->type = arch::data::kval_kinds::none; /* Ignored */
                              break;
                        }
                        case LUA_TPROTO: {
                              ptr->closure.id = i;
                              ptr->closure.ilang_closure = lift_closure(gco2p(kval.value_.gc), start_tempreg);
                              break;
                        }
                        default: {
                              luramas::error::error("Unkown kvalue type.");
                        }
                  }
                  buffer->kval.emplace_back(ptr);
            }

            /* Parse instructions */
            pm.add(lua_53_parsers::pending);
            pm.add(lua_53_parsers::jumps);
            pm.run();

            /* Resolve instructions */
            rm.add(lua_53_resolvers::instructions);
            rm.add(lua_53_resolvers::jump_operands);
            rm.add(lua_53_resolvers::remove_pending);
            rm.run();

            transformers::kinds(buffer);

            /* Protos */
            for (auto i = 0; i < p->sizep; ++i) {
                  buffer->closures.emplace_back(lift_closure(p->p[i], start_tempreg));
            }
            return;
      }

      std::shared_ptr<luramas::il::ilang> lift_proto(Proto *p, const luramas_register start_tempreg) {

            auto buffer = std::make_shared<luramas::il::ilang>();
            std::vector<std::shared_ptr<lua_53_disassembler::disassembly>> dism;
            lua_53_disassembler::disassemble(p, dism);
            luramas::il::lifter::lift(p, dism, buffer, start_tempreg);
            return buffer;
      };
} // namespace luramas::il::lifter
#endif