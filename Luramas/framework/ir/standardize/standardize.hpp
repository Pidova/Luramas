#pragma once
#include "../ir.hpp"

namespace luramas::ir::standardize {

      namespace annotations {

            void standardize(const std::shared_ptr<std::vector<std::pair<std::string, std::vector<luramas_address>>>> &data);
      }
} // namespace luramas::ir::standardize