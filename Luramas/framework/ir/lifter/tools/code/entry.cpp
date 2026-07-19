#include "../tools.hpp"

namespace luramas::ir::tools::entry {

      std::optional<std::vector<se_ir>> unsafe_split(se_ir &ir) {

            std::vector<luramas_index> locs;

            /* Log */
            for (auto i = 0ull; i < ir.data.size(); ++i) {
                  if (stat::is_entry_point(ir.data[i])) {
                        locs.emplace_back(i);
                  }
            }

            /* No entries */
            if (locs.empty()) {
                  return std::nullopt;
            }
            if (locs.size() == 1u && !locs.front()) {
                  ir.data.erase(ir.data.begin());
                  return std::nullopt;
            }

            /* Build */
            std::vector<se_ir> result;
            for (const auto &i : locs) {

                  ir_stat::space built;

                  std::copy_if(ir.data.begin() + i, ir.data.end(), std::back_inserter(built), [](const auto &p) { return !stat::is_entry_point(p); });
                  std::copy_if(ir.data.begin(), ir.data.begin() + i, std::back_inserter(built), [](const auto &p) { return !stat::is_entry_point(p); });

                  result.emplace_back(se_ir(built));
            }
            return result;
      }

} // namespace luramas::ir::tools::entry