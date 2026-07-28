#pragma once
#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)
#include "../../../../resolver/resolver.hpp"
#include "../Lua_5.3.hpp"

namespace lua_53_resolvers {

      /* Resolves instructions. */
      void instructions(luramas::il::lifter::resolver::resolver_manager<Proto *> &rm);

      /* Resolves jumps from ref to there relative operand locs */
      void jump_operands(luramas::il::lifter::resolver::resolver_manager<Proto *> &rm);

      /* Removes pending instructions */
      void remove_pending(luramas::il::lifter::resolver::resolver_manager<Proto *> &rm);

} // namespace lua_53_resolvers

#endif