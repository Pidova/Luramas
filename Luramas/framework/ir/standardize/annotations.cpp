#include "standardize.hpp"
#include <hunspell/hunspell.hxx>

namespace luramas::ir::standardize::annotations {

      std::string standardize(const std::string &input, Hunspell &checker) {

            auto result = input;
            if (!checker.spell(result)) {
                  for (const auto &i : checker.suggest(result)) {
                        if (i.find(' ') != std::string::npos) {

                              const auto pos = i.find(' ');
                              if (pos + 2u >= i.length() || (pos + 1u < i.length() && !std::isalnum(i[pos + 1]))) {
                                    continue;
                              }
                              result = i;
                              break;
                        }
                  }
            }

            std::string compiled("");
            bool punder = false;
            for (const auto &i : result) {
                  if (std::isalnum(i)) {
                        compiled += std::tolower(i);
                        punder = false;
                  } else {
                        if (!punder) {
                              compiled += '_';
                              punder = true;
                        }
                  }
            }

            while (!compiled.empty() && compiled.back() == '_') {
                  compiled.pop_back();
            }
            return compiled;
      }

      void standardize(const std::shared_ptr<std::vector<std::pair<std::string, std::vector<luramas_address>>>> &data) {

            Hunspell checker("C:\\dict\\en_US.aff", "C:\\dict\\en_US.dic");

            boost::unordered_flat_set<std::string> seen;
            seen.reserve(data->size());

            for (auto &[str, _] : *data) {
                  str = standardize(str, checker);
                  while (!seen.emplace(str).second) {
                        str += '_';
                  }
            }
            return;
      }

} // namespace luramas::ir::standardize::annotations