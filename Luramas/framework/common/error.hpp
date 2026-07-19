#pragma once
#include "constants.hpp"
#include <string>

#define LURAMAS_ERROR_REMINDER "Check env flags (for IR or IL passes)"

namespace luramas::error {

      /* Error handler */
      template <typename err_code>
      struct handler {
            err_code ec;           /* Error code */
            bool err = false;      /* Errored? */
            std::string what = ""; /* What string */

            constexpr void emit(const err_code ec, const std::string &what) {
                  this->err = true;
                  this->ec = ec;
                  this->what = what;
                  return;
            }
            constexpr operator bool() const {
                  return this->err;
            }
      };

      /* Contains result with any errors that may be thrown */
      template <typename data, typename err_code>
      struct result {

            explicit result() = default;
            constexpr result(const data &d)
                : d(d) {
            }
            constexpr result(std::nullptr_t)
                : d(nullptr) {
            }

            constexpr void emit(const err_code ec, const std::string &what) {
                  this->h.emit(ec, what);
                  return;
            }
            template <err_code ec>
            constexpr void emit(const std::string &what) {
                  this->h.emit(ec, what);
                  return;
            }
            template <err_code ec>
            constexpr void emit(const data &d, const std::string &what) {
                  this->d = d;
                  this->h.emit(ec, what);
                  return;
            }
            constexpr void emit(const data &d) {
                  this->d = d;
                  return;
            }
            constexpr void emit(const handler<err_code> &h) {
                  this->h = h;
                  return;
            }
            std::string str() const {
                  return this->h.what;
            }

            /* Return if theres a error */
            constexpr operator bool() const {
                  return this->h;
            }
            constexpr result &operator=(const data &d) {
                  this->d = d;
                  return *this;
            }

            data d;              /* Data */
            handler<err_code> h; /* Error handler */
      };

      /* General errors */
      [[noreturn]] void error(const std::string &what);
      void error_dump(const std::string &what);

      /* Unexpected errors/debug */
      void unexpected_error(const std::string &what);
      void unexpected_error(const std::string &what, const luramas_address line);
      void debug_print(const char *const str);
      void debug_callstack(const std::vector<std::string> &v);

      /* Syntax errors */
      [[noreturn]] void error_stat_syn_emit(const std::string &stat_kind);
      [[noreturn]] void error_expr_syn_emit(const std::string &expr_kind);

      namespace generation {

            /* Index string error generations */
            std::string index(const luramas_index idx, const std::string &what);
            std::string index(const luramas_index idx, const std::string &str, const std::string &what, const std::uint16_t window_threshold = 5u);
      } // namespace generation
} // namespace luramas::error
