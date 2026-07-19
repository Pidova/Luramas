#pragma once
#include "functions/args.hpp"
#include "functions/results.hpp"
#include <string>

namespace luramas::ir::code::generation::tools::smart_variables::data::functions {

      enum class kind : std::uint8_t {
            nothing,
            result,
            first_arg
      };

      namespace args {

            inline std::array<const char *, 5u> name(const std::string &func) {

                  for (auto i = 0u; i < sizeof(common) / sizeof(common[0u]); ++i) {
                        if (const auto str = common[i].first; str && func == str) {
                              return common[i].second;
                        }
                  }
                  return {nullptr, nullptr, nullptr, nullptr, nullptr};
            }

      } // namespace args

      inline kind common(std::string &buffer) {

            for (auto i = 0u; i < sizeof(results::common) / sizeof(results::common[0u]); ++i) {
                  const auto &[func, res] = results::common[i];
                  if (func && buffer == func) {
                        buffer = res;
                        return kind::result;
                  }
            }

            for (auto i = 0u; i < sizeof(args::first::common) / sizeof(args::first::common[0u]); ++i) {
                  if (const auto str = args::first::common[i]; str && buffer == str) {
                        return kind::first_arg;
                  }
            }
            return kind::nothing;
      }

      inline std::array<const char *, 5u> common_mulret(const std::string &func) {

            for (auto i = 0u; i < sizeof(results::mulret) / sizeof(results::mulret[0u]); ++i) {
                  if (const auto str = results::mulret[i].first; str && func == str) {
                        return results::mulret[i].second;
                  }
            }
            return {nullptr, nullptr, nullptr, nullptr, nullptr};
      }
} // namespace luramas::ir::code::generation::tools::smart_variables::data::functions