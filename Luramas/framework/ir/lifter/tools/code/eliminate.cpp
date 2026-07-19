#include "../tools.hpp"

namespace luramas::ir::tools::eliminate {

      void page(luramas::ir::passes::pass_manager &pm, const paging::details &page_details, const paging::details::page &p) {

            for (const auto &[exp, a_es] : p.references) {

                  for (const auto &a_e : a_es) {

                        if (a_e.stat) {

                              pm.insert(pm[a_e.n], tools::inliner::page(pm, a_e, page_details, p).data);
                              if (const auto &s = pm[a_e.n]; stat::is_page_return(s)) {

                                    boost::unordered_flat_set<std::shared_ptr<ir_stat::ir_expr>> removals;
                                    for (const auto &l : s->smembers) {
                                          if (!l->is_integral(p.id)) {
                                                continue;
                                          }
                                          removals.insert(l);
                                    }
                                    if (s->smembers.erase(std::remove_if(s->smembers.begin(), s->smembers.end(), [&](const std::shared_ptr<ir_stat::ir_expr> &e) { return removals.contains(e); }), s->smembers.end());
                                        s->smembers.empty()) {
                                          pm.remove(s);
                                    }
                              } else {
                                    pm.remove(s);
                              }
                        } else {
                              // TODO: ADD PAGE FUNCTIONS INLINE
                              // pm.insert(pm[a_e.n], tools::inliner::page(pm, a_e, page_details, p).data);
                              // pm.remove(pm[a_e.n]);
                        }
                  }
            }

            if (const auto &def = pm[p.range.first + 1u]; tools::stat::is_definition(def)) {
                  pm.remove(def);
            }
            pm.remove(pm[p.range.first], pm[p.range.second - 1u]);
            pm.mut(LURAMAS_DEBUG_LINE);
            return;
      }

} // namespace luramas::ir::tools::eliminate