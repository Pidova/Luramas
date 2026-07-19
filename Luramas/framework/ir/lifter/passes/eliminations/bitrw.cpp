#include "../../../../common/string.hpp"
#include "../includes/common.hpp"

namespace luramas::ir::passes {

      void dead_type_dependant_elimination(pass_manager &pm, shared &s, generation::ssa::ssa &ssa, const boost::unordered_flat_map<luramas_xregister, std::shared_ptr<ir::types::object::type>> &types) {

            luramas::ir::pass::process::values(pm);

            for (const auto &[stat, data] : pm.processed.values) {

                  switch (stat->k) {
                        case keywords::bitwrite: {

                              if (stat->l && stat->l->is_register_reference()) {
                                    if (const auto t = ssa.nodes[stat].r.assigns[stat->l->reg]; t.second.size() == 1u) {

                                          if (const auto it = types.find(*t.second.begin()); it != types.end() && it->second->basic() && luramas_int(it->second->under.bits()) == tools::stat::bitwise::extract_bitwrite_bits(stat)) {

                                                pm.insert(stat, tools::stat::generate::assignment(stat->l, stat->r));
                                                pm.remove(stat);
                                                pm.mut(LURAMAS_DEBUG_LINE);
                                          }
                                    }
                              }
                              break;
                        }
                        default: {
                              break;
                        }
                  }

                  for (const auto &expr : data.all) {
                        switch (expr->k) {
                              case expr_kinds::bitread: {

                                    if (expr->l && expr->l->is_register_reference()) {
                                          if (const auto t = ssa.nodes[stat].r.assigns[expr->l->reg]; t.second.size() == 1u) {

                                                if (const auto it = types.find(*t.second.begin()); it != types.end() && it->second->basic() && luramas_int(it->second->under.bits()) == tools::exprs::values::bitwise::extract_bitread_bits(expr)) {

                                                      expr->k = expr_kinds::blank_lvalue;
                                                      pm.mut(LURAMAS_DEBUG_LINE);
                                                }
                                          }
                                    }
                                    break;
                              }
                              default: {
                                    break;
                              }
                        }
                  }
            }
            return;
      }
} // namespace luramas::ir::passes