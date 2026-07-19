#include "../tools.hpp"

namespace luramas::ir::tools::count {

      luramas_count is(const ir_stat::ir_expr::space &v, const data::cb_tkind &cb) {
            luramas_count n = 0u;
            for (const auto &i : v) {
                  n += cb(i->tk);
            }
            return n;
      }

      luramas_count is(const ir_stat::ir_expr::space &v, const data::cb_kinds &cb) {
            luramas_count n = 0u;
            for (const auto &i : v) {
                  n += cb(i->k);
            }
            return n;
      }

      luramas_count is(const ir_stat::space &v, const data::cb_keywords &cb) {
            luramas_count n = 0u;
            for (const auto &i : v) {
                  n += cb(i->k);
            }
            return n;
      }

      luramas_count insts(const luramas_blockrange &b) {
            return b.second > b.first ? b.second - b.first : 0u;
      }

      luramas_count definition_parameters(const std::shared_ptr<ir_stat> &definition) {
            return tools::stat::is_definition(definition) ? definition->args.size() : 0u;
      }

      luramas_count refs(luramas::ir::passes::pass_manager &pm, const luramas_address label_loc) {

            luramas_count n = 0u;
            for (auto i = 0u; i < pm.ir.data.size(); ++i) {
                  n += (pm[i]->is_goto_label() && common::safe_take_jump(pm, i) == label_loc);
            }
            return n;
      }
} // namespace luramas::ir::tools::count