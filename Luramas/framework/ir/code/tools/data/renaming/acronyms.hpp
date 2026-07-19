#pragma once
#include "../../../../lifter/tools/extras/exprs.hpp"

namespace luramas::ir::code::generation::tools::smart_variables::data::acronyms {

      static constexpr std::pair<const char *, const char *> common[] = {
          {"string", "str"},
          {"index", "idx"}};

      void str(std::string &buffer) {

            for (const auto &[key, replacement] : common) {

                  std::string lower_key = key;
                  luramas_str_lowercase(lower_key);
                  auto lower_res = buffer;
                  luramas_str_lowercase(lower_res);

                  std::size_t pos = 0u;
                  while ((pos = lower_res.find(lower_key, pos)) != std::string::npos) {
                        buffer.replace(pos, std::strlen(key), replacement);
                        lower_res.replace(pos, std::strlen(key), replacement);
                        pos += std::strlen(replacement);
                  }
            }
            return;
      }

} // namespace luramas::ir::code::generation::tools::smart_variables::data::acronyms