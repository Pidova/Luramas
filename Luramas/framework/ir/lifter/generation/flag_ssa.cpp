#include "../generation.hpp"
#include "ssa\ssa_builder.hpp"

namespace luramas::ir::generation::flag_ssa {

      fssa generate(se_ir &ir, const boost::unordered_flat_map<std::shared_ptr<ir_stat>, luramas::ir::definitions::exprs> &exprs) {

            fssa result(ir);

            auto cfg = cfg::generate(ir, LURAMAS_IR_ENTRY, ir.fhas_pages);

            /* Values */
            std::vector<ssa_builder::node> ssa_nodes;
            ssa_nodes.reserve(ir.data.size());
            {
                  for (const auto &p : ir.data) {

                        ssa_builder::node ssa_node;
                        switch (p->k) {
                              case keywords::set_flag: {

                                    if (p->l && p->l->is_integral()) {
                                          ssa_node.lvalues.emplace_back(p->l->extract_integral_base());
                                    }
                                    break;
                              }
                              case keywords::definition: {

                                    for (const auto &i : p->members) {
                                          if (i && i->is_integral()) {
                                                ssa_node.lvalues.emplace_back(i->extract_integral_base());
                                          }
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                        if (const auto expr = exprs.find(p); expr != exprs.end()) {
                              for (const auto &e : expr->second.all) {
                                    if (e && e->is_k<expr_kinds::flag>() && e->r->is_integral()) {
                                          ssa_node.rvalues.emplace_back(e->r->extract_integral_base());
                                    }
                              }
                        }
                        ssa_nodes.emplace_back(ssa_node);
                  }
            }

            auto ssa = ssa_builder::generate(ssa_nodes, cfg);
            ssa_builder::tools::global_version(ssa);

            /* Translate */
            for (auto i = 0U; i < ssa.size(); ++i) {
                  const auto &vssa = ssa[i];
                  for (const auto &[_, v] : vssa.lvalues) {
                        result.set[i] = v;
                  }
                  if (ssa_nodes[i].rvalues.empty()) {
                        continue;
                  }
                  for (const auto &[_, v] : vssa.rvalues) {
                        for (const auto &x : v.uv) {
                              auto [it, inserted] = result.used.try_emplace(x, std::make_pair(0U, boost::unordered_flat_set<luramas_address>()));
                              ++it->second.first;
                              it->second.second.insert(i);
                              if (v.k == ssa_builder::kind::phi) {
                                    result.phis.insert(x);
                              }
                        }
                  }
            }

            //LURAMAS_PRINTF("FSSA:\n");
            //for (auto i = 0u; i < ir.data.size(); ++i) {
            //
            //      const auto &str = ir.data[i]->str();
            //      LURAMAS_PRINTF("%s\n", str.c_str());
            //
            //      if (const auto it = result.set.find(i); it != result.set.end()) {
            //            LURAMAS_PRINTF("FFSA(%llu) ", it->second);
            //            LURAMAS_PRINTF("USED:\n");
            //
            //            if (const auto sit = result.used.find(it->second); sit != result.used.end()) {
            //                  for (const auto &u : sit->second.second) {
            //                        LURAMAS_PRINTF("     %s\n", ir.data[u]->str().c_str());
            //                  }
            //            }
            //      }
            //}
            //LURAMAS_PRINTF("============\n");
            //std::cin.get();
            //
            //std::printf("FSSA:\n");
            //for (auto i = 0u; i < ir.data.size(); ++i) {
            //
            //      const auto &str = ir.data[i]->str();
            //      std::printf("%s\n", str.c_str());
            //
            //      if (const auto it = result.set.find(i); it != result.set.end()) {
            //            std::printf("FFSA(%llu) ", it->second);
            //            std::printf("USED:\n");
            //
            //            if (const auto sit = result.used.find(it->second); sit != result.used.end()) {
            //                  for (const auto &u : sit->second.second) {
            //                        std::printf("     %s\n", ir.data[u]->str().c_str());
            //                  }
            //            }
            //      }
            //}
            //std::printf("============\n");
            return result;
      }
} // namespace luramas::ir::generation::flag_ssa