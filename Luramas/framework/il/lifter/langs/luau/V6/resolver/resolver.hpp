#pragma once
#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)
#include "../../../../resolver/resolver.hpp"
#include "../Luau-V6.hpp"
#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <functional>
#include <unordered_map>

namespace luau_v6_resolvers {

      /* Resolves instructions operands. */
      void resolve_instruction_operands(luramas::il::lifter::resolver::resolver_manager<Proto *> &rm);

      /* Resolves jump locations operands. */
      void resolve_jump_operands(luramas::il::lifter::resolver::resolver_manager<Proto *> &rm);

      /* Resolves instructions. */
      void resolve_instructions(luramas::il::lifter::resolver::resolver_manager<Proto *> &rm);

} // namespace luau_v6_resolvers

#endif