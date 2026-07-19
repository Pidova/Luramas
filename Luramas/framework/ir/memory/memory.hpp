#pragma once
#include "../ir.hpp"

namespace luramas::ir::memory {

      /* Memory region of bytes */
      struct region {

            luramas_address base = 0u;
            std::vector<std::uint8_t> data;
            boost::unordered_flat_map<luramas_address, std::string> annotate_names; /* Insert strings into specific regions */

            region(const std::vector<std::uint8_t> &data, const luramas_address base = 0u)
                : base(base), data(data) {
            }

            void emit_annotation(const std::string &str, const luramas_address idx);
            std::string str() const;
      };

} // namespace luramas::ir::memory
