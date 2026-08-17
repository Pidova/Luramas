#include "../string.hpp"

namespace luramas::str {

      std::string to_string(const luramas_int &i) {

            return i.precise() ? std::to_string(i.extract_double()) : i.cast_b().str();
      }

      luramas_length match_substr(const std::string &str, const luramas_index idx, const char *const match) {

            if (!match) {
                  return 0U;
            }
            const auto len = std::strlen(match);
            return (idx + len > str.size()) ? 0U : (!std::memcmp(str.data() + idx, match, len) ? len : 0U);
      }
} // namespace luramas::str