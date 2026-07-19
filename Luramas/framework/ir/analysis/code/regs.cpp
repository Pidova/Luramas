#include "../../lifter/passes/includes/common.hpp"
#include "../common.hpp"

namespace luramas::ir::analysis::regs {

      boost::unordered_flat_map<luramas_register, luramas_addresses> used(const boost::unordered_flat_map<std::shared_ptr<ir_stat>, luramas::ir::definitions::exprs> &expr_map) {

            boost::unordered_flat_map<luramas_register, luramas_addresses> result;

            for (const auto &[stat, exprs] : expr_map) {
                  for (const auto &r : exprs.rvalues_regs) {
                        auto [it, inserted] = result.try_emplace(r, luramas_addresses());
                        it->second.reserve(it->second.size() + exprs.rvalues_regs.size());
                        it->second.insert(it->second.end(), exprs.rvalues_regs.begin(), exprs.rvalues_regs.end());
                  }
            }
            return result;
      }

      boost::unordered_flat_map<luramas_register, luramas_addresses> edited(const boost::unordered_flat_map<std::shared_ptr<ir_stat>, luramas::ir::definitions::exprs> &expr_map) {

            boost::unordered_flat_map<luramas_register, luramas_addresses> result;

            for (const auto &[stat, exprs] : expr_map) {
                  if (stat->is_defines()) {
                        for (const auto &r : exprs.lvalues_regs) {
                              auto [it, inserted] = result.try_emplace(r, luramas_addresses());
                              it->second.reserve(it->second.size() + exprs.lvalues_regs.size());
                              it->second.insert(it->second.end(), exprs.lvalues_regs.begin(), exprs.lvalues_regs.end());
                        }
                  }
            }
            return result;
      }

      boost::unordered_flat_map<std::shared_ptr<ir_stat>, returning_regs_p> mutated(const ir_stat::space &space) {

            std::vector<std::shared_ptr<ir_stat>> sorted;
            boost::unordered_flat_map<std::shared_ptr<ir_stat>, returning_regs_p> result;

            std::vector<ir_stat::space> spaces;
            spaces.emplace_back(space);
            do {
                  const auto &curr = spaces.front();

                  boost::unordered_flat_map<std::shared_ptr<ir_stat>, definitions::exprs> values;
                  ir::pass::process::values(curr, values);

                  std::vector<std::shared_ptr<ir_stat>> pages;
                  for (const auto &[stat, exprs] : values) {

                        /* Enter or exit page */
                        if (tools::stat::is_page_function_start(stat)) {
                              pages.emplace_back(stat);
                        }
                        if (!pages.empty() && tools::stat::is_page_function_end(stat)) {
                              pages.pop_back();
                        }
                  }
            } while (!spaces.empty());
            return result;
      }
} // namespace luramas::ir::analysis::regs