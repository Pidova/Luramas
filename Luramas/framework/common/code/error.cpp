#include "../error.hpp"
#include "../debug.hpp"

namespace luramas::error {

      void error(const std::string &what) {
#if defined(DEBUG) && defined(LURAMAS_TARGET_BIGDATA) && defined(LURAMAS_DEBUG_ERROR_CLIPBOARD)
            debug::copy_to_clipboard(LURMAS_GLOBAL_PDUMP);
#endif
            std::printf("%s, " LURAMAS_ERROR_REMINDER "\n", what.c_str());
            throw std::runtime_error(what);
      }
      void error_dump(const std::string &what) {
            std::printf("%s\n", what.c_str());
            return;
      }

      void unexpected_error(const std::string &what) {
            error("Unexpected: " + what);
      }
      void unexpected_error(const std::string &what, const luramas_address line) {
            error("Unexpected: " + what + " on line: " + std::to_string(line));
      }
      void debug_print(const char *const str) {
            if (std::strlen(str)) {
                  std::printf("%s\n", str);
            }
            return;
      }
      void debug_callstack(const std::vector<std::string> &v) {
            std::printf("CALLSTACK:\n");
            for (const auto &i : v) {
                  std::printf("     %s\n", i.c_str());
            }
            return;
      }

      void error_stat_syn_emit(const std::string &stat_kind) {
            error(stat_kind + " statement emissions are not supported by current target syntax.");
      }
      void error_expr_syn_emit(const std::string &expr_kind) {
            error(expr_kind + " expression emissions are not supported by current target syntax.");
      }

      namespace generation {

            std::string index(const luramas_index idx, const std::string &what) {
                  return "Index: " + std::to_string(idx) + " errored: " + what;
            }
            std::string index(const luramas_index idx, const std::string &str, const std::string &what, const std::uint16_t window_threshold) {

                  std::string result("String Index (" + std::to_string(idx) + ") with: '" + what + "'\n");
                  if (idx < str.size()) {

                        result += "   Error on char '" + std::string(1u, str[idx]) + "'\n";

                        const auto start = (idx > window_threshold) ? idx - window_threshold : 0u;
                        const auto end = std::min(str.size(), idx + window_threshold);
                        result += "   '" + str.substr(start, end > start ? end - start : 0u) + "'\n";
                        result += "    " + std::string((idx >= start && idx < end) ? (idx - start) : 0u, ' ') + "~\n";
                  }
                  return result;
            }
      } // namespace generation
} // namespace luramas::error