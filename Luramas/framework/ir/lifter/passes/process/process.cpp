#include "process.hpp"

namespace luramas::ir::pass::process {

      void values(const ir_stat::space &data, boost::unordered_flat_map<std::shared_ptr<ir_stat>, definitions::exprs> &buffer) {

            buffer.reserve(data.size());
            for (auto loc = 0u; loc < data.size(); ++loc) {

                  const auto &i = data[loc];
                  definitions::exprs exprs;

                  exprs.where = loc;
                  exprs.lvalues.reserve(LURAMAS_PREDICTED_EXPRS);
                  exprs.lvalues_regs.reserve(LURAMAS_PREDICTED_REGS);
                  exprs.rvalues.reserve(LURAMAS_PREDICTED_EXPRS);
                  exprs.rvalues_regs.reserve(LURAMAS_PREDICTED_REGS);

                  i->extract_deep_ordered_lvalues(exprs.lvalues);
                  for (const auto &e : exprs.lvalues) {
                        if (e->is_register_reference()) {
                              exprs.lvalues_regs.emplace_back(e->reg);
                        }
                  }

                  i->extract_deep_ordered_rvalues(exprs.rvalues);
                  for (const auto &e : exprs.rvalues) {
                        if (e->is_register_reference()) {
                              exprs.rvalues_regs.emplace_back(e->reg);
                        }
                  }

                  exprs.all.reserve(exprs.lvalues.size() + exprs.rvalues.size());
                  exprs.all.insert(exprs.all.end(), exprs.lvalues.begin(), exprs.lvalues.end());
                  exprs.all.insert(exprs.all.end(), exprs.rvalues.begin(), exprs.rvalues.end());

                  for (const auto &rv : exprs.all) {
                        if (rv && rv->is_k<expr_kinds::flag>()) {
                              exprs.used_flags.emplace_back(rv->r->extract_integral_base());
                        }
                  }
                  if (i->is_k<keywords::set_flag>()) {
                        exprs.edits_flag = true;
                        exprs.edited_flag = i->l->extract_integral_base();
                  }
                  buffer.try_emplace(i, exprs);
            }
            return;
      }

      void values(luramas::ir::passes::pass_manager &pm) {

            if (!pm.processed.values.empty()) {
                  return;
            }

            values(pm.ir.data, pm.processed.values);
            return;
      }
} // namespace luramas::ir::pass::process