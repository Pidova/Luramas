#pragma once
#include "implements.hpp"
#include <array>

namespace cpu_tracer::arch {

      namespace str {

            namespace data {

                  constexpr std::array<const char *const, 6u> save_types = {
                      "none",
                      "block",
                      "edge_map",
                      "vcpu_states",
                      "interrupts",
                      "MMIO"};
            } // namespace data

            /* To string save type */
            constexpr inline const char *const to_string(const save_type &type) noexcept {
                  if (const auto index = static_cast<std::size_t>(type); index < data::save_types.size()) {
                        return data::save_types[index];
                  }
                  return "unknown";
            }
      } // namespace str

} // namespace cpu_tracer::arch