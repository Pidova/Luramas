/*
   Itemized evaluation of stats and exprs
*/
#pragma once
#include "../../execution.hpp"

namespace luramas::ir::execution::evaluate {

      namespace stats {

            enum class action_kind : std::uint8_t {
                  none,
                  jump_loc,
                  jump_label
            };
            struct action {

                  action_kind k = action_kind::none;
                  union {
                        luramas_address jump;
                  };

                  void emit_jump_loc(const luramas_address loc);
                  void emit_jump_label(const luramas_address label);
            };

            /* Execute */
            error::result<action, errors::kinds> execute(environment &env, const std::shared_ptr<ir_stat> &stat);
      } // namespace stats

      namespace exprs {

            /* Evaluate unary */
            error::result<types::object, errors::kinds> unary(const types::object &obj, const luramas::il::arch::data::bin_kinds b, const environment_flags &f);

            /* Evaluate condition */
            error::result<types::object, errors::kinds> condition(const types::object &l, const types::object &r, const luramas::il::arch::data::bin_kinds b, const environment_flags &f);

            /* Evaluate arithmetic */
            error::result<types::object, errors::kinds> arithmetic(const types::object &l, const types::object &r, const luramas::il::arch::data::bin_kinds b, const environment_flags &f);

            /* Execute */
            types::object execute(environment &env, const std::shared_ptr<ir_stat::ir_expr> &expr);
      } // namespace exprs
} // namespace luramas::ir::execution::evaluate