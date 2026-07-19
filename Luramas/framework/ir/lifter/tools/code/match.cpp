#include "../../passes/process/process.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::match {

      std::pair<bool, boost::unordered_flat_map<std::string, std::shared_ptr<ir_stat::ir_expr>>> wild_cards(const std::shared_ptr<ir_stat::ir_expr> &value, const std::shared_ptr<ir_stat::ir_expr> &match) {

            auto result = std::make_pair(false, boost::unordered_flat_map<std::string, std::shared_ptr<ir_stat::ir_expr>>());

            /* Invoke early exit */
            if (!value || !match || !value->compare(match, true, false)) {
                  return result;
            }

            std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat::ir_expr>>> stack = {{value, match}};
            stack.reserve(LURAMAS_PREDICTED_RECURSION);

            while (!stack.empty()) {

                  const auto [v, m] = stack.back();
                  stack.pop_back();

                  if (!v || !m) {
                        if (v || m) {
                              return result;
                        }
                        continue;
                  }
                  if (v->flags.fglobal_wild) {
                        if (const auto [it, inserted] = result.second.try_emplace(v->str(), m); !inserted && *it->second != *m) {
                              return result;
                        }
                        continue;
                  } else if (m->flags.fglobal_wild) {
                        if (const auto [it, inserted] = result.second.try_emplace(m->str(), v); !inserted && *it->second != *v) {
                              return result;
                        }
                        continue;
                  }

                  if (!v->compare(m, true, false)) {
                        return result;
                  }

                  stack.emplace_back(v->l, m->l);
                  stack.emplace_back(v->r, m->r);
                  stack.emplace_back(v->ev, m->ev);
                  stack.emplace_back(v->xv, m->xv);

                  for (auto i = 0u; i < v->members.size(); ++i) {
                        stack.emplace_back(v->members[i], m->members[i]);
                  }
                  for (auto i = 0u; i < v->tmembers.size(); ++i) {
                        stack.emplace_back(v->tmembers[i].first, m->tmembers[i].first);
                        stack.emplace_back(v->tmembers[i].second, m->tmembers[i].second);
                  }
            }
            result.first = true;
            return result;
      }

} // namespace luramas::ir::tools::match