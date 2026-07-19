#include "../iterate.hpp"

namespace luramas::ir::cfg::iterate {

      namespace visit {

            std::shared_ptr<generation::cfg::block> visit(const std::vector<std::shared_ptr<generation::cfg::block>> &blocks, const luramas_address target) {

                  for (const auto &i : blocks) {
                        if (target >= i->get_front() && target <= i->get_end()) {
                              return i;
                        }
                  }
                  return nullptr;
            }
            std::shared_ptr<generation::cfg::block> visit_fall(const std::vector<std::shared_ptr<generation::cfg::block>> &blocks, const std::shared_ptr<generation::cfg::block> &target) {

                  for (const auto &i : blocks) {
                        if (i->fall == target) {
                              return i;
                        }
                  }
                  return nullptr;
            }
      } // namespace visit

      namespace extract {

            std::vector<std::pair<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>>> edge(const std::vector<std::shared_ptr<generation::cfg::block>> &blocks, const generation::cfg::edge_kind target) {

                  std::vector<std::pair<std::shared_ptr<generation::cfg::block>, std::shared_ptr<generation::cfg::block>>> result;

                  for (const auto &curr : blocks) {

                        for (const auto &[k, b] : curr->get_successors()) {

                              if (k == target) {
                                    result.emplace_back(std::make_pair(b, curr));
                              }
                        }
                  }
                  return result;
            }
      } // namespace extract

      namespace is {

            bool scope_visible(const luramas_addresses &highlevel_scope_id, const luramas_address current, const luramas_address target, const bool skip_current_scope) {

                  if (target > current) {
                        return false;
                  }

                  auto curr_id = highlevel_scope_id[current];
                  if (curr_id && skip_current_scope) {
                        --curr_id;
                  }
                  for (auto i = static_cast<signed>(target); i < current; ++i) {

                        const auto on_id = highlevel_scope_id[i];
                        if (curr_id > on_id) {
                              return false;
                        }
                        curr_id = on_id;
                  }
                  return true;
            }
      } // namespace is
} // namespace luramas::ir::cfg::iterate