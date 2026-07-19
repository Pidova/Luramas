#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools::guarantee {

      namespace exprs {

            std::shared_ptr<ir_stat::ir_expr> cast(const std::shared_ptr<ir_stat::ir_expr> &expr, const luramas::types::underlying_type &t, const bool bits) {

                  if (!expr || tools::exprs::values::is_cast(expr, t, bits)) {
                        return expr;
                  }

                  if (const auto evaluated = tools::types::extract(expr); evaluated.size() == 1u) {
                        if (const auto &f = evaluated.front(); f.type && f.type->basic() && (f.type->under == t || (bits && f.type->under.bits() == t.bits()))) {

                              return expr;
                        }
                  }
                  return tools::exprs::generate::cast(expr, t);
            }
      } // namespace exprs

      namespace stats {

            std::shared_ptr<ir_stat> label(passes::pass_manager &pm, const luramas_address loc) {
                  if (!stat::is_label(pm[loc])) {
                        const auto ptr = stat::generate::label(pm.ir.avaliable_label());
                        pm.insert(pm[loc], ptr);
                        pm.mut(LURAMAS_DEBUG_LINE);
                        return ptr;
                  }
                  return pm[loc];
            }

            std::shared_ptr<ir_stat> definition(passes::pass_manager &pm, const luramas_address loc, const luramas_address where) {
                  if (!pm.contains(loc) || !pm.contains(where)) {
                        return nullptr;
                  }
                  if (!stat::is_definition(pm[where])) {
                        const auto ptr = stat::generate::definition();
                        pm.insert(pm[loc], ptr);
                        pm.mut(LURAMAS_DEBUG_LINE);
                        return ptr;
                  }
                  return pm[where];
            }

            std::shared_ptr<ir_stat> definition(passes::pass_manager &pm, const luramas_address loc, const luramas_address where, const luramas_register reg, const std::shared_ptr<ir_stat::ir_expr> &def_expr) {
                  const auto def = definition(pm, loc, where);
                  auto p = def_expr;
                  if (!p) {
                        p = tools::exprs::generate::reg(reg);
                  }
                  def->args.try_emplace(reg, p);
                  return def;
            }
      } // namespace stats
} // namespace luramas::ir::tools::guarantee