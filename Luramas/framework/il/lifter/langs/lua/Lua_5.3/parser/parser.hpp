#pragma once
#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)
#include "../../../../parser/parser.hpp"
#include "../Lua_5.3.hpp"

/* Maps everything to their relative translation. (Does not add or remove any instructions not relative to the translation) */
namespace lua_53_parsers {

      /* First pass parses instructions */
      void instructions(luramas::il::lifter::parser::parser_manager<std::shared_ptr<lua_53_disassembler::disassembly>> &pm);

      /* Second pass to change pending add stuff */
      void pending(luramas::il::lifter::parser::parser_manager<std::shared_ptr<lua_53_disassembler::disassembly>> &pm);

      /* Map jumps to disassembly */
      void jumps(luramas::il::lifter::parser::parser_manager<std::shared_ptr<lua_53_disassembler::disassembly>> &pm);
} // namespace lua_53_parsers

#endif