#include "../ssa_builder.hpp"

namespace luramas::ssa_builder::tools {

      void global_version(std::vector<ssa_node> &buffer) {

            luramas_xregister gver = generation::ssa::UNKNOWN_SSA_VERSION + 1u;
            boost::unordered_flat_map<luramas_register, boost::unordered_flat_map<luramas_xregister, luramas_xregister>> global_map;

            /* Lvalues: Populate maps for all explicit definitions */
            for (auto &node : buffer) {
                  for (auto &[reg, v] : node.lvalues) {

                        if (v == generation::ssa::UNKNOWN_SSA_VERSION) {
                              continue;
                        }
                        const auto ver = gver++;
                        global_map[reg][v] = ver;
                        v = ver;
                  }
            }

            /* Rvalues: Map local versions to unique global versions */
            for (auto &node : buffer) {
                  for (auto &[reg, ssa] : node.rvalues) {

                        auto &mapped = global_map[reg];

                        ssa.uv.clear();

                        for (auto &v_local : ssa.v) {

                              if (v_local == generation::ssa::UNKNOWN_SSA_VERSION) {
                                    ssa.uv.insert(v_local);
                                    continue;
                              }

                              auto it = mapped.find(v_local);
                              if (it == mapped.end()) {
                                    const auto ver = gver++;
                                    mapped[v_local] = ver;
                                    v_local = ver;
                              } else {
                                    v_local = it->second;
                              }

                              ssa.uv.insert(v_local);
                        }
                  }
            }
      }
} // namespace luramas::ssa_builder::tools