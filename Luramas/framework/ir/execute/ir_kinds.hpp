#pragma once
#include "definitions.hpp"

namespace luramas::ir::execution::ir_kinds {

      /* Tkind able to perform arithmetic? */
      bool arithmetic(const tkind k, const environment_flags &f);

      /* Tkinds are able to be compared against one another? */
      bool condition(const tkind l, const tkind r, const environment_flags &f);
} // namespace luramas::ir::execution::ir_kinds
