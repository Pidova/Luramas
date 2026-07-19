#pragma once
#include <stdexcept>

#ifdef DEBUG
#define LURAMAS_ASSERT(condition, message)                                    \
      if (condition) {                                                        \
            std::ostringstream oss;                                           \
            oss << "Assertion failed: (" #condition "), message: " << message \
                << ", in file " << __FILE__ << ", line " << __LINE__;         \
            throw std::runtime_error(oss.str());                              \
      }
#define LURAMAS_ASSERT_DBG(condition, message, debug_code) \
      if (condition) {                                     \
            {debug_code};                                  \
            std::printf(message);                          \
            LURAMAS_ASSERT(condition, message)             \
      }
#else
#define LURAMAS_ASSERT(condition, message) (void(0))
#define LURAMAS_ASSERT_DBG(condition, message, debug_code) (void(0))
#endif