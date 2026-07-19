#include "../extras/stats.hpp"
#include "../tools.hpp"

namespace luramas::ir::tools {

      bool treshold(const luramas_address target, const luramas_address start, const luramas_address end) {
            return target > start && target < end;
      }
      bool treshold_ie(const luramas_address target, const luramas_address start, const luramas_address end) {
            return target >= start && target < end;
      }
      bool treshold_ei(const luramas_address target, const luramas_address start, const luramas_address end) {
            return target > start && target <= end;
      }
      bool treshold_ii(const luramas_address target, const luramas_address start, const luramas_address end) {
            return target >= start && target <= end;
      }
      bool treshold(const luramas_address target, const luramas_blockrange &block) {
            return treshold_ie(target, block.first, block.second);
      }

      bool safe_page_code_no_loops(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {
            return violations::block_violates(pm, range.first, range.second, violations::block_violates_flags({.finclude_pages = true})).valid && !contains::orphans::pages(pm, range);
      }

      bool safe(luramas::ir::passes::pass_manager &pm, const luramas_blockrange &range) {
            return safe_page_code_no_loops(pm, range) && !contains::orphans::implicit_goto(pm, range);
      }
} // namespace luramas::ir::tools