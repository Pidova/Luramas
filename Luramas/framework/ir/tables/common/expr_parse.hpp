#pragma once
#include "../../ir.hpp"
#include "../../parser/common.hpp"

namespace luramas::ir::tables {

      struct expr_parse_map {

            expr_parse_map(const parser::flags &f, const char *const key, const char *const value)
                : key_s(key), value_s(value) {

                  parser::manager m(f);
                  /* Key */
                  const auto k = parser::exprs::parse(m, key);
                  if (k) {
                        error::error(k.h.what);
                  }
                  this->key = k.d;

                  /* Value */
                  const auto v = parser::exprs::parse(m, value);
                  if (v) {
                        error::error(v.h.what);
                  }
                  this->val = v.d;
                  return;
            }

            const char *key_s = "";
            const char *value_s = "";
            std::shared_ptr<ir_stat::ir_expr> key = nullptr; /* Key expr */
            std::shared_ptr<ir_stat::ir_expr> val = nullptr; /* Value expr */
      };

} // namespace luramas::ir::tables