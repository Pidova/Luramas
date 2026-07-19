#include "../ir_kinds.hpp"

namespace luramas::ir::execution::ir_kinds {

      bool arithmetic(const tkind k, const environment_flags &f) {

            switch (k) {
                  case tkind::boolean: {
                        return !f.fnative_objects;
                  }
                  case tkind::lura_int: {
                        return true;
                  }
                  default: {
                        break;
                  }
            }
            return false;
      }

      bool condition(const tkind l, const tkind r, const environment_flags &f) {

            if (!f.fcondition_mismatch) {
                  return l == r;
            }
            switch (l) {
                  case tkind::none_obj:
                  case tkind::variadic:
                  case tkind::table:
                  case tkind::string:
                  case tkind::lura_int:
                  case tkind::global:
                  case tkind::boolean:
                  case tkind::kvalue:
                  case tkind::stack:
                  case tkind::object: {
                        switch (r) {
                              case tkind::none_obj:
                              case tkind::variadic:
                              case tkind::table:
                              case tkind::string:
                              case tkind::lura_int:
                              case tkind::global:
                              case tkind::boolean:
                              case tkind::kvalue:
                              case tkind::stack:
                              case tkind::object: {
                                    return true;
                              }
                              default: {
                                    break;
                              }
                        }
                        break;
                  }
                  default: {
                        break;
                  }
            }
            return false;
      }
} // namespace luramas::ir::execution::ir_kinds