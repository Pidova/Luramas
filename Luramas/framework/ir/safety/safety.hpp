#pragma once
#include "../ir.hpp"
#include "../lifter/tools/extras/exprs.hpp"

namespace luramas::ir::safety {

      namespace types {

            static auto place_holder = tools::exprs::generate::nothing();

            template <typename T>
            struct values {
                  T l;
                  T r;
            };
            using expr_kinds_map = boost::unordered_flat_map<expr_kinds, values<std::shared_ptr<ir_stat::ir_expr>>>;
            using type_map = boost::unordered_flat_map<std::shared_ptr<ir_stat> /* Definition */, ir_stat::ir_expr::space>;

            bool same_type(const std::shared_ptr<ir_stat::ir_expr> &expr, const std::shared_ptr<ir_stat::ir_expr> &type);

            namespace generate {

                  std::shared_ptr<ir_stat::ir_expr> make_cast(const std::shared_ptr<ir_stat::ir_expr> &input, const std::shared_ptr<ir_stat::ir_expr> &casting_type);
            } // namespace generate
      } // namespace types

} // namespace luramas::ir::safety