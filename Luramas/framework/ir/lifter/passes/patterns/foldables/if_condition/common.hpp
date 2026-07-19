#pragma once
#include "../../common.hpp"
#include "../common.hpp"

namespace luramas::ir::passes::patterns::constant_folding::if_condition {

      namespace internals {

            /*
            
            */
            void pattern1(pass_manager &pm, shared &s, const luramas_address i);

      } // namespace internals

      static constexpr pattern_cb cbs[] = {
          internals::pattern1};

      inline constexpr void run(pass_manager &pm, shared &s, const luramas_address i) {
            for (const auto &cb : cbs) {
                  cb(pm, s, i);
            }
            return;
      }
} // namespace luramas::ir::passes::patterns::constant_folding::if_condition