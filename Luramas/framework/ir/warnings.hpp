#pragma once
#include <cstdint>

#define LURAMAS_WARNING_PREFIX "WARNING: "
#define LURAMAS_WARNING_HINT "Please trace with debugger and provided information to IL."

namespace luramas::ir::warnings {

      enum class warnings : std::uint8_t {
            none,
            unkown_callback_params
      };

      inline const char *const str(const warnings reason) {
            switch (reason) {
                  case warnings::unkown_callback_params: {
                        return LURAMAS_WARNING_PREFIX "Complex callback could not be traced. " LURAMAS_WARNING_HINT;
                  }
                  default: {
                        break;
                  }
            }
            return "";
      }
} // namespace luramas::ir::warnings