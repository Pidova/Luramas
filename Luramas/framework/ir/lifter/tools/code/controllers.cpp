#include "../../passes/process/process.hpp"
#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::controllers {

      boost::unordered_flat_map<luramas_id, std::pair<luramas_address, std::optional<luramas_address>>> get(luramas::ir::passes::pass_manager &pm, const std::vector<std::optional<luramas_address>> &parent_pages, const paging::details::page &page, const flags &f) {

            boost::unordered_flat_map<luramas_id, std::pair<luramas_address, std::optional<luramas_address>>> result;

            /* Invalid */
            if (!page.fvalid) {
                  return result;
            }

            luramas_addresses addrs;
            for (auto i = LURAMAS_IR_ENTRY; i < parent_pages.size(); ++i) {
                  if (parent_pages[i] == page.range.first) {
                        addrs.emplace_back(i);
                  }
            }
            for (const auto &i : addrs) {
                  const auto &p = pm[i];
                  if (f.fcond_gotos && stat::branch::is_controller_if_cond_goto(p)) {
                        result[p->r->extract_integral_base()] = {i, p->jlabel};
                  }
                  if (f.fcond && stat::branch::is_controller_if_cond(p)) {
                        result[p->r->extract_integral_base()] = {i, std::nullopt};
                  }
            }
            return result;
      }

      boost::unordered_flat_map<luramas_id, boost::unordered_flat_set<luramas_id>> set(luramas::ir::passes::pass_manager &pm) {

            luramas::ir::pass::process::values(pm);

            boost::unordered_flat_map<luramas_id, boost::unordered_flat_set<luramas_id>> result;
            for (const auto &addr : luramas_iter(pm.range())) {

                  const auto &i = pm[addr];
                  if (stat::is_page_function_goto(i) && i->v) {
                        result[i->r->extract_integral_base()].insert(i->v->extract_integral_base());
                  }
                  for (const auto &e : pm.processed.values.find(i)->second.all) {
                        if (exprs::values::is_page_function_call(e) && e->l) {
                              result[e->r->extract_integral_base()].insert(e->l->extract_integral_base());
                        }
                  }
            }
            return result;
      }
} // namespace luramas::ir::tools::controllers