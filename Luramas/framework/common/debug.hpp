#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

/* DEBUG GLOBALS */
#ifdef DEBUG
#ifdef LURAMAS_TARGET_BIGDATA
extern std::string LURMAS_GLOBAL_PDUMP;
#define LURAMAS_PRINTF(format, ...)                                                              \
      {                                                                                          \
            std::vector<char> buffer(40000u);                                                    \
            const auto len = std::snprintf(buffer.data(), buffer.size(), format, ##__VA_ARGS__); \
            if (len >= static_cast<std::int32_t>(buffer.size())) {                               \
                  buffer.resize(len + 1u);                                                       \
                  std::snprintf(buffer.data(), buffer.size(), format, ##__VA_ARGS__);            \
            }                                                                                    \
            LURMAS_GLOBAL_PDUMP += buffer.data();                                                \
      }
#else
#define LURAMAS_PRINTF(format, ...) std::printf(format, ##__VA_ARGS__);
#endif
#else
#define LURAMAS_PRINTF(format, ...) (void)0
#endif

/* DEBUG */
#define LURAMAS_CSTRINGIFY(x) #x
#define LURAMAS_CSTRING(x) LURAMAS_CSTRINGIFY(x)
#ifdef DEBUG
#define LURAMAS_DEBUG_LINE "FILE: " __FILE__ " AT " LURAMAS_CSTRING(__LINE__)
#else
#define LURAMAS_DEBUG_LINE ""
#endif
#define LURAMAS_DEBUG_HEADER(x, ...) ("========================" x "========================" __VA_ARGS__)

namespace luramas::debug {
#ifdef _WIN32

      /* Copy data to clipboard */
      void copy_to_clipboard(const std::string &str);
#endif

} // namespace luramas::debug
