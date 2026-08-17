#include "../tools.hpp"

namespace luramas::ir::tools::count {

      luramas_count is(const ir_stat::ir_expr::space &v, const data::cb_tkind &cb) {
            luramas_count n = 0U;
            for (const auto &i : v) {
                  n += static_cast<luramas_count>(cb(i->tk));
            }
            return n;
      }

      luramas_count is(const ir_stat::ir_expr::space &v, const data::cb_kinds &cb) {
            luramas_count n = 0U;
            for (const auto &i : v) {
                  n += static_cast<luramas_count>(cb(i->k));
            }
            return n;
      }

      luramas_count is(const ir_stat::space &v, const data::cb_keywords &cb) {
            luramas_count n = 0U;
            for (const auto &i : v) {
                  n += static_cast<luramas_count>(cb(i->k));
            }
            return n;
      }

      luramas_count insts(const luramas_blockrange &b) {
            return b.second > b.first ? b.second - b.first : 0U;
      }

      luramas_count definition_parameters(const std::shared_ptr<ir_stat> &definition) {
            return tools::stat::is_definition(definition) ? definition->args.size() : 0U;
      }

      luramas_count refs(luramas::ir::passes::pass_manager &pm, const luramas_address label_loc) {

            luramas_count n = 0U;
            for (auto i = 0U; i < pm.ir.data.size(); ++i) {
                  n += static_cast<luramas_count>(pm[i]->is_goto_label() && common::safe_take_jump(pm, i) == label_loc);
            }
            return n;
      }
} // namespace luramas::ir::tools::count