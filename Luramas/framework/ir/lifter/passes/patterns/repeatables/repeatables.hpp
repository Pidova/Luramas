#pragma once
#include "../common.hpp"

/* 
	Buffer will always be at the end of the pattern
*/
namespace luramas::ir::passes::patterns::repeatables {

      template <luramas_address disp>
      class repeatable_manager {

          public:
            repeatable_manager(pass_manager &pm)
                : pm(pm) {
            }

            inline bool not_valid_kinds(luramas_address &offset) {
                  return true;
            }
            inline void displace(luramas_address &offset) {
                  offset += disp;
                  return;
            }
            inline bool immutable_valid_next(const luramas_address start, const luramas_address offset) {
                  return pm.valid_next(start, offset + disp);
            }
            inline bool valid_next(const luramas_address start, luramas_address &offset) {

                  if (!this->pm.valid_next(start, offset + disp)) {
                        offset -= disp;
                        return false;
                  }
                  return true;
            }
            inline bool init(const luramas_address start, luramas_address &offset) {
                  offset = disp;
                  return this->pm.valid_next(start, offset + disp);
            }

          private:
            pass_manager &pm;
      };
      namespace if_condition {

            /*
			     if  (??) then [NOT r]
			     	r = ?? [NOT r]
			     	if (r) then goto l end
			     end
		    */
            bool pattern_1(pass_manager &pm, shared &s, const luramas_address start, luramas_address &buffer_disp);

      } // namespace if_condition

      namespace assignments {

            /*
                 r = ?
			     if (r) then goto l end 
		    */
            bool pattern_1(pass_manager &pm, shared &s, const luramas_address start, luramas_address &buffer_disp);
      } // namespace assignments

} // namespace luramas::ir::passes::patterns::repeatables