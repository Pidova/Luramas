#pragma once
#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_536)
#include "../Lua_5.3.6.hpp"

/* Maps everything to their relative translation. (Does not add or remove any instructions not relative to the translation) */
namespace lua_53_6_parsers {

      /* Parses instructions. */
      void parse_instruction(std::shared_ptr<luramas::il::ilang> &buffer, const std::vector<std::shared_ptr<lua_53_6_disassembler::disassembly>> &dism, luramas_register &stack_top);

      /* Maps out jumps too be fixed for there relatives. */
      std::vector<std::pair<std::shared_ptr<luramas::il::disassembly> /* Jumper */, std::shared_ptr<luramas::il::disassembly> /* Jump location */>> parse_jumps(std::shared_ptr<luramas::il::ilang> &il);

} // namespace lua_53_6_parsers

#endif