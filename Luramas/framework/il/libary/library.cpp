#include "library.hpp"

namespace luramas::il::library {

      namespace naming_conventions {

            std::string library_module::str() const {
                  auto result = (!this->author.empty() ? "[" + this->author + "] " : "") + this->name;
                  if (!this->major.empty()) {
                        result += "  " + this->major;
                  }
                  if (!this->minor.empty()) {
                        result += "." + this->minor;
                  }
                  if (!this->patch.empty()) {
                        result += "." + this->patch;
                  }
                  return result;
            }

            std::string generate(const library_module &lib, const std::string &name) {
                  return lib.str() + " " + name;
            }
      } // namespace naming_conventions
} // namespace luramas::il::library