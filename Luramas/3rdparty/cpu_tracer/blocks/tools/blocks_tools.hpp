#pragma once
#include "../blocks.hpp"
#include <optional>

namespace cpu_tracer::blocks::tools {

      /* Given block it splits it at given index */
      template <std::uint8_t MAX_LEN>
      inline std::optional<block<MAX_LEN>> split_block(block<MAX_LEN> &b, const std::size_t split_index, const std::size_t new_id) {

            if (!split_index || split_index >= b.insts.size()) {
                  return std::nullopt;
            }

            block<MAX_LEN> result;
            result.time = b.time;
            result.id = new_id;
            result.fretranslated = b.fretranslated;
            result.interpretation_id = b.interpretation_id;
            result.vcpu_n = b.vcpu_n;

            /* Move insts */
            const auto split_iter = b.insts.begin() + split_index;
            result.insts.insert(result.insts.end(), std::make_move_iterator(split_iter), std::make_move_iterator(b.insts.end()));
            b.insts.erase(split_iter, b.insts.end());
            b.inst_count = b.insts.size();

            result.inst_count = result.insts.size();
            result.loc = result.inst_count ? result.insts.front().inst.pc : 0u;
            return result;
      }

      /* Find index given real pc */
      template <std::uint8_t MAX_LEN>
      inline std::optional<std::size_t> get_index(const block<MAX_LEN> &b, const address realpc) {

            for (auto idx = 0u; idx < b.insts.size(); ++idx) {
                  if (const auto &i = b.insts[idx]; i.inst.real_pc == realpc) {
                        return idx;
                  }
            }
            return std::nullopt;
      }
} // namespace cpu_tracer::blocks::tools