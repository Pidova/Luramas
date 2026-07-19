#pragma once
#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_536)
#include "../Lua_5.3.6.hpp"

namespace resolver {

      /* Resolves instructions. */
      void resolve_instructions(std::shared_ptr<luramas::il::ilang> &buffer);

      /* Resolves block data. */
      void resolve_blocks(std::shared_ptr<luramas::il::ilang> &buffer);

      /* Resolves jump locations. */
      void resolve_jumps(std::shared_ptr<luramas::il::ilang> &buffer, const std::vector<std::pair<std::shared_ptr<luramas::il::disassembly> /* Jumper */, std::shared_ptr<luramas::il::disassembly> /* Jump location */>> &map);

} // namespace resolver

#endif