#pragma once
#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)

#include "../../../../../disassembler/luau/V6/disassembler.hpp"
#include "../../../../il/il.hpp"

namespace luramas::il::lifter {

      /* Lifts current closure and child closures too IL disassembly. */
      void lift(Proto *p, const std::vector<std::shared_ptr<luau_v6_disassembler::disassembly>> &dism, std::shared_ptr<luramas::il::ilang> &buffer);

      /* Lifts proto and child closures too IL disassembly. */
      std::shared_ptr<luramas::il::ilang> lift(Proto *p);
} // namespace luramas::il::lifter

#endif