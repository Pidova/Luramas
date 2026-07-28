#pragma once
#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)

#include "../../../../../disassembler/lua/Lua_5.3/disassembler.hpp"
#include "../../../../il/il.hpp"

namespace luramas::il::lifter {

      /* Lifts current closure and child closures too IL disassembly. */
      void lift(Proto *p, const std::vector<std::shared_ptr<lua_53_disassembler::disassembly>> &dism, std::shared_ptr<luramas::il::ilang> &buffer, const luramas_register start_tempreg);

      /* Lifts proto and child closures too IL disassembly. */
      std::shared_ptr<luramas::il::ilang> lift_proto(Proto *p, const luramas_register start_tempreg);

} // namespace luramas::il::lifter

#endif