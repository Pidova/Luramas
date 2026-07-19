#pragma once
#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)
#include "../../../../parser/parser.hpp"
#include "../Luau-V6.hpp"
#include <functional>
#include <vector>

namespace luau_v6_parsers {

      /* Parse compare instruction. */
      void parse_compares(luramas::il::lifter::parser::parser_manager<std::shared_ptr<luau_v6_disassembler::disassembly>> &pm);

      /* Parses debug information to debug manager */
      void parse_debug(luramas::il::lifter::parser::parser_manager<std::shared_ptr<luau_v6_disassembler::disassembly>> &pm, Proto *p);

      /* Inits parser, does not remove or add any new instructions, everything is alligned. */
      void parse_instructions(luramas::il::lifter::parser::parser_manager<std::shared_ptr<luau_v6_disassembler::disassembly>> &pm);

      /* Parse jumps */
      void parse_jumps(luramas::il::lifter::parser::parser_manager<std::shared_ptr<luau_v6_disassembler::disassembly>> &pm);

      /* Parse boolean jumps */
      void parse_boolean_jumps(luramas::il::lifter::parser::parser_manager<std::shared_ptr<luau_v6_disassembler::disassembly>> &pm);

} // namespace luau_v6_parsers

#endif