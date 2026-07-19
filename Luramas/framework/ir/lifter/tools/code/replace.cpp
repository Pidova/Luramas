#include "../../passes/process/process.hpp"
#include "../tools.hpp"
#include <stack>

namespace luramas::ir::tools::replace {

      void wild_cards(std::shared_ptr<ir_stat::ir_expr> &value, const boost::unordered_flat_map<std::string, std::shared_ptr<ir_stat::ir_expr>> &exprs) {

            if (!value) {
                  return;
            }

            std::vector<std::shared_ptr<ir_stat::ir_expr>> stack = {value};
            stack.reserve(LURAMAS_PREDICTED_RECURSION);

            const auto add = [&](auto &v) {
                  if (!v) {
                        return false;
                  }
                  if (v->flags.fglobal_wild) {
                        const auto it = exprs.find(v->str());
                        if (it == exprs.end()) {
                              error::error("Wild card not found");
                        }
                        v = it->second;
                        return true;
                  }
                  stack.emplace_back(v);
                  return false;
            };

            if (add(value)) {
                  return;
            }
            while (!stack.empty()) {

                  auto v = stack.back();
                  stack.pop_back();

                  add(v->l);
                  add(v->r);
                  add(v->ev);
                  add(v->xv);
                  for (auto &i : v->members) {
                        add(i);
                  }
                  for (auto &[i, v] : v->tmembers) {
                        add(i);
                        add(v);
                  }
            }
            return;
      }

      std::shared_ptr<ir_stat::ir_expr> match_wild_cards(const std::shared_ptr<ir_stat::ir_expr> &value, const std::shared_ptr<ir_stat::ir_expr> &match, const std::shared_ptr<ir_stat::ir_expr> &dest) {

            if (!value || !match || !dest) {
                  return nullptr;
            }

            const auto [matched, w] = match::wild_cards(value, match);
            if (!matched) {
                  return nullptr;
            }

            auto result = dest->clone();
            wild_cards(result, w);
            return result;
      }
} // namespace luramas::ir::tools::replace