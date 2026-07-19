#pragma once
#include "../../../../../common.hpp"

namespace luramas::ir::code::generation::tools::smart_variables::data::words {

      static constexpr std::array common_prefixes = {
          "get",
          "set",
          "is",
          "has",
          "can",
          "should",
          "will",
          "create",
          "fetch"};

      inline bool common_prefix(std::string &str) {

            auto copy = str;
            luramas_str_lowercase(copy);
            for (const auto &prefix : common_prefixes) {
                  if (!copy.compare(0u, std::strlen(prefix), prefix)) {
                        str.erase(0u, std::strlen(prefix));
                        return true;
                  }
            }
            return false;
      }
} // namespace luramas::ir::code::generation::tools::smart_variables::data::words