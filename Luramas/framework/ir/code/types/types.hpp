#pragma once
#include "private/types.hpp"

namespace luramas::ir::types {

      namespace common {

            static auto i8 = types::generate::basic(8, false);
            static auto i16 = types::generate::basic(16, false);
            static auto i32 = types::generate::basic(32, false);
            static auto i64 = types::generate::basic(64, false);
            static auto ui8 = types::generate::basic(8u, true);
            static auto ui16 = types::generate::basic(16u, true);
            static auto ui32 = types::generate::basic(32u, true);
            static auto ui64 = types::generate::basic(64u, true);

      } // namespace common

} // namespace luramas::ir::types