#pragma once
#include "error.hpp"
#include <algorithm>
#include <iomanip>
#include <regex>
#include <sstream>

namespace luramas::str {

      std::string to_string(const luramas_int &i);

      /* Match substring and return length */
      luramas_length match_substr(const std::string &str, const luramas_index idx, const char *const match);
} // namespace luramas::str

inline bool luramas_is_escape_specifier(const char c) {
      switch (c) {
            case '\'':
            case '\"':
            case '\\':
            case '\?':
            case 'a':
            case 'b':
            case 'f':
            case 'n':
            case 'r':
            case 't':
            case 'v':
            case '0':
            case 'x': {
                  return true;
            }
            default: {
                  return false;
            }
      }
}
inline bool luramas_is_visible_char(const std::int8_t c) {
      return c >= static_cast<const std::int8_t>(32) && c <= static_cast<const std::int8_t>(126);
}
inline void luramas_str_escape(std::string &buffer) {

      if (buffer.empty()) {
            return;
      }
      std::string result("");
      result.reserve(buffer.size());
      for (auto i = 0u; i < buffer.size(); ++i) {

            const auto &c = buffer[i];
            switch (c) {
                  case '\n': {
                        result.append("\\n");
                        break;
                  }
                  case '\t': {
                        result.append("\\t");
                        break;
                  }
                  case '\\': {
                        result.append("\\\\");
                        break;
                  }
                  case '\'': {
                        result.append("\\'");
                        break;
                  }
                  case '\"': {
                        result.append("\\\"");
                        break;
                  }
                  default: {
                        if (!luramas_is_visible_char(c)) {
                              std::ostringstream hs;
                              hs << "\\x" << std::hex << std::uppercase << std::setw(2u) << std::setfill('0') << static_cast<const std::int32_t>(static_cast<const std::uint8_t>(c));
                              result.append(hs.str());
                        } else {
                              result.push_back(c);
                        }
                        break;
                  }
            }
      }
      buffer = std::move(result);
      return;
}
inline void luramas_str_integer(std::string &buffer) {
      if (!buffer.empty()) {
            auto pos = buffer.find('.');
            if (pos != std::string::npos) {
                  while (!buffer.empty() && buffer.back() == '0') {
                        buffer.pop_back();
                  }
                  if (!buffer.empty() && buffer.back() == '.') {
                        buffer.pop_back();
                  }
            }
      }
      return;
}
inline void luramas_str_sanitize(std::string &buffer) {
      buffer.erase(std::remove_if(buffer.begin(), buffer.end(), [](const char c) {
            return c == '\'' || c == '\"';
      }),
          buffer.end());
      return;
}
inline bool luramas_str_clean(const std::string &str) {
      return std::all_of(str.begin(), str.end(), [](const auto c) {
            return std::isalpha(c);
      });
}
inline bool luramas_str_number(const std::string &str) {
      return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}
inline bool luramas_str_decimal(const std::string &str) {
      if (str.empty()) {
            return false;
      }

      bool has_decimal_point = false;
      bool has_digit = false;

      for (std::size_t i = (str.front() == '+' || str.front() == '-'); i < str.size(); ++i) {
            if (std::isdigit(str[i])) {
                  has_digit = true;
            } else if (str[i] == '.') {
                  if (has_decimal_point) {
                        return false;
                  }
                  has_decimal_point = true;
            } else {
                  return false;
            }
      }
      return has_digit && has_decimal_point;
}
inline bool luramas_str_qoutes(const std::string &str) {
      if (str.size() < 2u) {
            return false;
      }
      const auto front = str.front();
      const auto back = str.back();
      return (front == '\'' || front == '\"') && front == back;
}
inline bool luramas_str_chars(const std::string &str) {
      return std::any_of(str.begin(), str.end(), [](const auto c) { return std::isalpha(c); });
}
inline void luramas_str_uppercase(std::string &buffer) {
      std::transform(buffer.begin(), buffer.end(), buffer.begin(), [](const auto c) { return std::toupper(c); });
      return;
}
inline void luramas_str_lowercase(std::string &buffer) {
      std::transform(buffer.begin(), buffer.end(), buffer.begin(), [](const auto c) { return std::tolower(c); });
      return;
}
inline bool luramas_str_valid_index(const std::string &str) {
      static const std::regex regex("^[A-Za-z_][A-Za-z0-9_]*$");
      return std::regex_match(str, regex);
}
inline std::string luramas_str_concat_qouted(std::string l, std::string r) {

      std::string result("");
      result.reserve(l.size() + r.size());

      bool qouted = false;
      if (luramas_str_qoutes(l)) {
            l.erase(l.begin());
            l.pop_back();
            qouted = true;
      }
      if (luramas_str_qoutes(r)) {
            r.erase(r.begin());
            r.pop_back();
            qouted = true;
      }
      if (qouted) {
            result += "\"";
      }
      result += l + r;
      if (qouted) {
            result += "\"";
      }
      return result;
}

/* STRING CASES */
inline void luramas_str_case_snakify(std::string &buffer) {
      if (std::all_of(buffer.begin(), buffer.end(), [](const auto c) { return c == '_'; })) {
            return;
      }
      std::string result("");
      result.reserve(buffer.size());

      bool last = false;
      bool upper_seq = false;
      for (const auto c : buffer) {

            if (std::isupper(c)) {
                  if (!result.empty() && !last && !upper_seq) {
                        result += '_';
                  }
                  result += std::tolower(c);
                  last = false;
                  upper_seq = true;
            } else if (!std::isalnum(c)) {
                  if (!last) {
                        result += '_';
                        last = true;
                  }
            } else {
                  result += std::tolower(c);
                  last = false;
                  upper_seq = false;
            }
      }
      if (!result.empty() && result.back() == '_') {
            result.pop_back();
      }
      buffer = std::move(result);
      return;
}
inline void luramas_str_case_camelify(std::string &buffer) {
      if (std::all_of(buffer.begin(), buffer.end(), [](const auto c) { return c == '_'; })) {
            return;
      }
      std::string result("");
      result.reserve(buffer.size());

      bool next = false;
      for (const char i : buffer) {

            if (i == '_') {
                  next = true;
            } else {
                  result += next ? std::toupper(i) : i;
                  next = false;
            }
      }
      buffer = std::move(result);
      return;
}
inline void luramas_str_case_pascalify(std::string &buffer) {
      if (std::all_of(buffer.begin(), buffer.end(), [](const auto c) { return c == '_'; })) {
            return;
      }
      std::string result("");
      result.reserve(buffer.size());

      bool next = true;
      for (const char i : buffer) {
            if (i == '_') {
                  next = true;
            } else {
                  result += next ? std::toupper(i) : i;
                  next = false;
            }
      }
      buffer = std::move(result);
      return;
}
inline void luramas_str_case_flatify(std::string &buffer) {
      if (std::all_of(buffer.begin(), buffer.end(), [](const auto c) { return c == '_'; })) {
            return;
      }
      buffer.erase(std::remove(buffer.begin(), buffer.end(), '_'), buffer.end());
      return;
}
inline void luramas_str_case_screaming_snakify(std::string &buffer) {
      luramas_str_uppercase(buffer);
      return;
}

inline void luramas_str_remove_trailing(std::string &str, const std::string &suffix) {
      while (str.length() >= suffix.length() && !str.compare(str.length() - suffix.length(), suffix.length(), suffix)) {
            str.erase(str.length() - suffix.length());
      }
      return;
}
