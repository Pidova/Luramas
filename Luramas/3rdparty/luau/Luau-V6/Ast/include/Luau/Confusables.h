#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)

// This file is part of the Luau programming language and is licensed under MIT License; see LICENSE.txt for details
#pragma once

#include <stdint.h>

namespace Luau {
      const char *findConfusable(uint32_t codepoint);
}

#endif
