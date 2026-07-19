#include "strs.hpp"

namespace luramas::ir::code::generation::str {

      namespace prefixes {

            std::string flag(const std::shared_ptr<ir::data::format::format> &format, const std::shared_ptr<ir_stat::ir_expr> &reg) {

                  if (reg && format->vars.naming_conventions.prefixes.flags.enabled) {
                        if (reg->flags.funsigned) {
                              return format->vars.naming_conventions.prefixes.flags.unsign;
                        }
                        if (reg->flags.fsynthetic) {
                              return format->vars.naming_conventions.prefixes.flags.synthetic;
                        }
                  }
                  return "";
            }

            std::string var(const std::shared_ptr<ir::data::format::format> &format, const std::shared_ptr<ir_stat::ir_expr> &reg) {

                  if (reg) {
                        switch (reg->k) {
                              case expr_kinds::upvalue: {
                                    return format->vars.naming_conventions.prefixes.upvalue;
                              }
                              default: {
                                    switch (reg->rk) {
                                          case expr_reg_kinds::arg: {
                                                return format->vars.naming_conventions.prefixes.arg;
                                          }
                                          default: {
                                                return format->vars.naming_conventions.prefixes.var;
                                          }
                                    }
                              }
                        }
                  }
                  return "";
            }
      } // namespace prefixes

      namespace suffix {

      }
} // namespace luramas::ir::code::generation::str