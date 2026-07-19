#pragma once
#include "../ir.hpp"
namespace luramas::ir::virtual_functions {

      struct flags {
            luramas_flag foptional_cast = true; /* Casts do not have to be explicit only references type? */
      };

      class emanager {

          public:
            emanager(const std::initializer_list<
                std::pair<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat::ir_expr>>> &il)
                : kp(il) {
            }

            /* Add key and value */
            void add(const std::shared_ptr<ir_stat::ir_expr> &k, const std::shared_ptr<ir_stat::ir_expr> &p) {
                  this->kp.emplace_back(k, p);
                  return;
            }

            flags f;

          private:
            std::vector<std::pair<std::shared_ptr<ir_stat::ir_expr>, std::shared_ptr<ir_stat::ir_expr>>> kp;
      };

      extern const emanager etable;
} // namespace luramas::ir::virtual_functions