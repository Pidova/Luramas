#include "includes/common.hpp"

namespace luramas::ir::passes {

      void memory_inference(pass_manager &pm, shared &s) {

            for (auto i = 0u; i < pm.amount(); ++i) {

                  auto &p = pm[i];
                  switch (p->k) {
                        default: {
                              break;
                        }
                  }
            }
            return;
      }
} // namespace luramas::ir::passes