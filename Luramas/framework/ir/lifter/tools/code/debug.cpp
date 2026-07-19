#include "../../generation/cfg/compute.hpp"
#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::debug {

      std::string graph(luramas::ir::passes::pass_manager &pm) {

            std::string result(LURAMAS_DEBUG_HEADER("Graph", "\n"));
            const auto cfg = generation::cfg::generate(pm.ir, LURAMAS_IR_ENTRY, pm.env_flags.fhas_pages);

            /* Graph */
            {
                  for (const auto &o : cfg.blocks) {
                        result += "BLOCK: " + std::to_string(reinterpret_cast<const luramas_address>(o.get())) + " " + std::to_string(o->get_front()) + " " + std::to_string(o->get_end()) + "\n";
                        for (auto s = o->get_front(); s < o->get_end(); ++s) {
                              result += pm[s]->str() + "\n";
                        }
                        if (o->fall) {
                              result += "FALL " + std::to_string(reinterpret_cast<const luramas_address>(o->fall.get())) + "\n";
                        }
                        if (o->jump) {
                              result += "JUMP " + std::to_string(reinterpret_cast<const luramas_address>(o->jump.get())) + "\n";
                        }
                        if (o->then) {
                              result += "THEN " + std::to_string(reinterpret_cast<const luramas_address>(o->then.get())) + "\n";
                        }
                        result += "-----------------------------------------------------\n";
                  }
            }

            /* Alive nodes */
            {
                  result += LURAMAS_DEBUG_HEADER("Alive", "\n");
                  for (auto idx = 0u; idx < pm.ir.data.size(); ++idx) {
                        result += (!cfg.interacted_nodes.contains(idx) ? "   [E] " : "   ") + pm[idx]->str() + "\n";
                  }
            }

            /* Graphviz */
            {
                  result += LURAMAS_DEBUG_HEADER("Graphviz", "\n");
                  result += cfg::compute::graphviz(pm.ir, cfg);
            }

            /* Statistics */
            {
                  result += LURAMAS_DEBUG_HEADER("Coverage", "\n");
                  result += "Inst: " + std::to_string((static_cast<std::double_t>(cfg.interacted_nodes.size()) / pm.ir.data.size()) * 100.0) + "%\n";
            }
            return result;
      }
} // namespace luramas::ir::tools::debug