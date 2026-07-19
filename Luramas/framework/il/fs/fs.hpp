#pragma once
#include "../il/il.hpp"

namespace luramas::il::fs {

      /* Save IL */
      void save(const std::shared_ptr<ilang> &lang, std::ostream &buffer);
      void save(const std::shared_ptr<ilang> &lang, const std::string &directory, const std::string &name);

      /* Load IL */
      std::shared_ptr<ilang> load(std::istream &is);
      std::shared_ptr<ilang> load(const std::string &directory, const std::string &name);
} // namespace luramas::il::fs