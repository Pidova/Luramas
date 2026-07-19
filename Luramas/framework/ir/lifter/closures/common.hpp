#pragma once
#include "../managers/common.hpp"

namespace luramas::ir::closures {

      namespace generate {

            /* Generate definition and debug values for closure and pass manager */
            void definition(passes::pass_manager &pm, const std::shared_ptr<luramas::closures::closure> &closure, const std::shared_ptr<managers::upvalues::manager> &upvalues);
      } // namespace generate

      namespace lifter {

            /* Lift closure to IR and run generic optimization passes */
            ir_stat::space lift(std::shared_ptr<luramas::closures::closure> &closure, const std::shared_ptr<luramas::ir::managers::upvalues::manager> &upvalues = nullptr, const std::vector<ir_stat::space> &closures = {}, const bool main_closure = false, const luramas_flag fgenerate_main_definition = true, const passes::environment_flags &env_flags = passes::environment_flags());
      } // namespace lifter
} // namespace luramas::ir::closures