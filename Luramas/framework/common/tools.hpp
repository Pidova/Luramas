#pragma once
#include "error.hpp"

namespace luramas::tools {

      /* Maps type to index */
      template <typename T>
      boost::unordered_flat_map<T, luramas_address> val_idx(const std::vector<T> &vect) {

            boost::unordered_flat_map<T, luramas_address> result;
            result.reserve(vect.size());
            for (auto i = 0u; i < vect.size(); ++i) {
                  result.try_emplace(vect[i], i);
            }
            return result;
      }

      /* Raw array wirth size to vector*/
      template <typename T>
      std::vector<T> raw_2_vect(const T *dism, const std::size_t size) {

            std::vector<T> result;
            if (!dism || !size) {
                  return result;
            }
            result.reserve(size);
            for (auto i = 0u; i < size; ++i) {
                  result.emplace_back(dism[i]);
            }
            return result;
      }

      template <typename k>
      constexpr bool native_supported_arith() {
            return std::is_integral_v<k> || std::is_same<k, luramas_int>::value;
      }
} // namespace luramas::tools