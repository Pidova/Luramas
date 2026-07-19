#pragma once
#include "../../il/il.hpp"

/* Static definitions of builtins */
namespace luramas::il::lifter::builder::builtin {

      struct arg {

            const char *name = "";               /* Argument nme */
            std::int16_t flag = -1;              /* 0 > n = No Flag */
            std::int16_t idx = -1;               /* 0 > n = No IDX */
            types::native::compiler::object obj; /* Internal object */

            inline bool empty() const {
                  return !std::strlen(this->name);
            }
      };

      struct func {

            const char *name = "";   /* Function name */
            std::vector<arg> dests;  /* Destination buffer args */
            std::vector<arg> source; /* Source buffer args */
            inline bool empty() const {
                  return !std::strlen(this->name);
            }
      };

      struct inst {
            std::vector<func> func_defs;
            inline bool empty() const {
                  return this->func_defs.empty();
            }
      };
} // namespace luramas::il::lifter::builder::builtin