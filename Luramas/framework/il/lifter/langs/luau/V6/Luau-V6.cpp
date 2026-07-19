#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)
#include "Luau-V6.hpp"
#include "../../../../../disassembler/luau/V6/disassembler.hpp"
#include "../../../../il/architecture/emitter.hpp"
#include "../../../../il/transformers/transformers.hpp"
#include "parser/parser.hpp"
#include "resolver/resolver.hpp"
#include <iostream>

void luramas::il::lifter::lift(Proto *p, const std::vector<std::shared_ptr<luau_v6_disassembler::disassembly>> &dism, std::shared_ptr<luramas::il::ilang> &buffer) {

      lifter::parser::parser_manager<std::shared_ptr<luau_v6_disassembler::disassembly>> pm(buffer, dism, luau_v6_parsers::parse_instructions, false);
      lifter::resolver::resolver_manager<Proto *> rm(buffer, p);

      auto lift_closure = [](Proto *p) -> std::shared_ptr<luramas::il::ilang> {
            if (!p) {
                  luramas::error::error("Lifter proto is null");
            }
            auto result = std::make_shared<luramas::il::ilang>();
            std::vector<std::shared_ptr<luau_v6_disassembler::disassembly>> vect_dism;
            for (auto pc = 0u; pc < unsigned(p->sizecode);) {
                  auto dism = std::make_shared<luau_v6_disassembler::disassembly>();
                  luau_v6_disassembler::disassemble(pc, p, dism);
                  vect_dism.emplace_back(dism);
                  pc += dism->len;
            }
            luramas::il::lifter::lift(p, vect_dism, result);
            return result;
      };

      /* Parses Kvalues */
      for (auto i = 0; i < p->sizek; ++i) {

            const auto &kval = p->k[i];
            if (p == nullptr) {
                  luramas::error::error("Lifter kvalue is null");
            }

            auto ptr = std::make_shared<luramas::il::ilang::kvalue>();
            switch (kval.tt) {
                  case lua_Type::LUA_TNIL:
                  case lua_Type::LUA_TDEADKEY: {
                        ptr->type = luramas::il::arch::data::kval_kinds::none;
                        break;
                  }
                  case lua_Type::LUA_TBOOLEAN: {
                        ptr->type = luramas::il::arch::data::kval_kinds::boolean;
                        ptr->boolean.b = kval.value.b;
                        break;
                  }
                  case lua_Type::LUA_TLIGHTUSERDATA: {
                        ptr->type = luramas::il::arch::data::kval_kinds::userdata;
                        ptr->userdata.str = "lightuserdata_" + std::to_string(i);
                        break;
                  }
                  case lua_Type::LUA_TNUMBER: {

                        ptr->type = luramas::il::arch::data::kval_kinds::integer;
                        ptr->integer.i = kval.value.n;

                        /* String and remove trailing 0's */
                        ptr->integer.str = std::to_string(ptr->integer.i);
                        luramas_str_integer(ptr->integer.str);
                        break;
                  }
                  case lua_Type::LUA_TVECTOR: {

                        const auto vect = vvalue(&kval);
                        if (!vect) {
                              luramas::error::error("String is nullptr");
                        }
                        for (auto i = 0u; i < LUA_VECTOR_SIZE; ++i) {
                              ptr->vector.vector.emplace_back(vect[i]);
                        }
                        ptr->type = luramas::il::arch::data::kval_kinds::vector;
                        break;
                  }
                  case lua_Type::LUA_TSTRING: {

                        ptr->type = luramas::il::arch::data::kval_kinds::string;
                        const auto data = gco2ts(kval.value.gc);
                        if (!data) {
                              luramas::error::error("String is nullptr");
                        }
                        ptr->string.str.assign(data->data, data->len);
                        luramas_str_escape(ptr->string.str);
                        break;
                  }
                  case lua_Type::LUA_TTABLE: {

                        const auto t = gco2h(kval.value.gc);
                        if (!t) {
                              luramas::error::error("Table is nullptr");
                        }
                        ptr->type = luramas::il::arch::data::kval_kinds::table;
                        ptr->table.array_size = t->sizearray;
                        ptr->table.node_size = t->lsizenode;
                        break;
                  }
                  case lua_Type::LUA_TFUNCTION: {
                        ptr->type = luramas::il::arch::data::kval_kinds::upvalue;
                        ptr->upvalue.str = "closure_" + std::to_string(i);
                        break;
                  }
                  case lua_Type::LUA_TUSERDATA: {
                        ptr->type = luramas::il::arch::data::kval_kinds::userdata;
                        ptr->userdata.str = "userdata_" + std::to_string(i);
                        break;
                  }
                  case lua_Type::LUA_TTHREAD: {
                        ptr->type = luramas::il::arch::data::kval_kinds::none; /* Ignored */
                        break;
                  }
                  case lua_Type::LUA_TPROTO: {
                        const auto p = gco2p(kval.value.gc);
                        if (!p) {
                              luramas::error::error("Proto is nullptr");
                        }
                        ptr->type = luramas::il::arch::data::kval_kinds::function;
                        ptr->closure.id = i;
                        ptr->closure.ilang_closure = lift_closure(p);
                        break;
                  }
                  case lua_Type::LUA_TUPVAL: {
                        ptr->type = luramas::il::arch::data::kval_kinds::upvalue;
                        ptr->upvalue.str = "upval_" + std::to_string(i);
                        break;
                  }
                  default: {
                        luramas::error::error("Unkown kvalue type.");
                  }
            }
            buffer->kval.emplace_back(ptr);
      }

      pm.add(luau_v6_parsers::parse_compares);
      pm.add(luau_v6_parsers::parse_boolean_jumps);
      pm.add(luau_v6_parsers::parse_jumps);
      if (p->sizelocvars) {
            luau_v6_parsers::parse_debug(pm, p);
      }
      pm.run();

      rm.add(luau_v6_resolvers::resolve_instruction_operands);
      rm.add(luau_v6_resolvers::resolve_jump_operands);
      rm.add(luau_v6_resolvers::resolve_instructions);
      rm.run();

      transformers::kinds(buffer);

      /* Protos */
      for (auto i = 0; i < p->sizep; ++i) {
            buffer->closures.emplace_back(lift_closure(p->p[i]));
      }
      return;
}

std::shared_ptr<luramas::il::ilang> luramas::il::lifter::lift(Proto *p) {
      auto buffer = std::make_shared<luramas::il::ilang>();
      std::vector<std::shared_ptr<luau_v6_disassembler::disassembly>> dism;
      luau_v6_disassembler::disassemble(p, dism);
      luramas::il::lifter::lift(p, dism, buffer);
      return buffer;
};

#endif