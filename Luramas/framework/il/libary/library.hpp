#pragma once
#include "../il/il.hpp"

namespace luramas::il::library {

      namespace naming_conventions {

            struct library_module {
                  std::string author = ""; /* Author of library */
                  std::string name = "";   /* Name of library */
                  std::string major = "";  /* Major version */
                  std::string minor = "";  /* Minor version */
                  std::string patch = "";  /* Patch version */
                  std::string str() const;
            };

            /* Generate name with library and name */
            std::string generate(const library_module &lib, const std::string &name);
      } // namespace naming_conventions

      struct func {
            std::string real_name = "";
            std::shared_ptr<ilang> lang = nullptr;
      };
      using library = boost::unordered_flat_map<std::string, func>;
} // namespace luramas::il::library