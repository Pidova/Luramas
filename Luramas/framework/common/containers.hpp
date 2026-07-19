#pragma once
#include <boost\unordered\unordered_flat_map.hpp>

namespace luramas::containers {

      namespace map {

            template <typename T>
            struct ptrs {

                  boost::unordered_flat_map<std::uintptr_t, T> map;
                  boost::unordered_flat_map<std::uintptr_t, T *> pend;

                  inline void emit_data(const std::uintptr_t val, const T &data) {
                        this->map[val] = data;
                        return;
                  }
                  inline void emit_pend(const std::uintptr_t val, T *slot) {
                        this->pend[val] = slot;
                        return;
                  }
                  inline void finalize(const T default_val) {
                        for (const auto &pair : this->pend) {
                              const auto ptr = pair.first;
                              T *target = pair.second;
                              const auto it = this->map.find(ptr);
                              *target = (it != this->map.end()) ? it->second : default_val;
                        }
                        this->pend.clear();
                        return;
                  }
            };

      } // namespace map
} // namespace luramas::containers