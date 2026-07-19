#pragma once
#include "../../common.hpp"
#include "../common.hpp"

namespace luramas::ir::passes::patterns::constant_folding::compilables {

      namespace if_condition {

            /*
				if  (??) then 
				    r = ??
				    if (r) then goto l end
				end
			*/
            std::shared_ptr<ir_stat::ir_expr> pattern_1(pass_manager &pm, shared &s, const luramas_address start, const luramas_address end);
      } // namespace if_condition

      namespace assignments {

            /*
                 r = ?
				 if (r) then goto l end
			*/
            std::shared_ptr<ir_stat::ir_expr> pattern_1(pass_manager &pm, shared &s, const luramas_address start, const luramas_address end);
      } // namespace assignments

} // namespace luramas::ir::passes::patterns::constant_folding::compilables