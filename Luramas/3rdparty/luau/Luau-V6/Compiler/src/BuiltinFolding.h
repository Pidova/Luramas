#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)

// This file is part of the Luau programming language and is licensed under MIT License; see LICENSE.txt for details
#pragma once

#include "ConstantFolding.h"

namespace Luau {
      namespace Compile {

            Constant foldBuiltin(int bfid, const Constant *args, size_t count);
            Constant foldBuiltinMath(AstName index);

      } // namespace Compile
} // namespace Luau

#endif
