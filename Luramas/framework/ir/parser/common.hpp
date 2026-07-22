#pragma once
#include "../ir.hpp"

namespace luramas::ir::parser {

      struct flags {
            luramas_flag fglobal_wild = false; /* Globals are in representation of a non-global i.e. x data */
      };
      class manager {

          public:
            explicit constexpr manager() {
                  this->var_scope.emplace_back(boost::unordered_flat_map<std::string, std::shared_ptr<ir_stat::ir_expr>>());
                  return;
            }
            constexpr manager(const flags &f)
                : flags(f) {
                  this->var_scope.emplace_back(boost::unordered_flat_map<std::string, std::shared_ptr<ir_stat::ir_expr>>());
                  return;
            }

            std::shared_ptr<ir_stat::ir_expr> set(const std::string &name, const std::shared_ptr<ir_stat::ir_expr> &expr);
            std::shared_ptr<ir_stat::ir_expr> get(const std::string &name) const;

            /* Get avaliable register */
            luramas_register get_reg();

            flags flags;
            std::vector<boost::unordered_flat_map<std::string, std::shared_ptr<ir_stat::ir_expr>>> var_scope; /* Variable scope */

          private:
            luramas_register avaliable_reg = 0u;
      };

      enum class errors : std::uint8_t {
            none,                   /* No error */
            invalid_keyword,        /* Invalid use of keyword */
            encapsulation_close,    /* Followed close of encapsulation with no start */
            encapsulation_unclosed, /* Followed start of encapsulation with no end */
            no_lvalue,              /* No left value */
            no_rvalue,              /* No right value */
            unclosed_string,        /* Unclosed string */
            assignment_mismatch,    /* Mismatch in assignment size */
      };
      const char *const str(const errors &err);

      namespace exprs {

            /* Parse expr as string (Review psuedo keywords) */
            error::result<std::shared_ptr<ir_stat::ir_expr>, errors> parse(manager &m, const std::string &str);
      } // namespace exprs

      namespace stats {

            /* Parse stat as string (Review psuedo keywords) */
            error::result<std::vector<std::shared_ptr<ir_stat>>, errors> parse(manager &m, const std::string &str);
      } // namespace stats

} // namespace luramas::ir::parser