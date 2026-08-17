#include "ir_defs.hpp"

#include <algorithm>
namespace luramas::ir {

      luramas_address se_ir::avaliable_page(const ir_stat::space &data) {

            luramas_address result = 0U;
            std::vector<ir_stat::space> spaces = {data};
            spaces.reserve(LURAMAS_PREDICTED_RECURSION);

            while (!spaces.empty()) {

                  const auto curr = spaces.back();
                  spaces.pop_back();
                  for (const auto &i : curr) {

                        if (i->is_k<keywords::page_function_start>() && i->r) {
                              if (const auto &n = i->r->extract_integral_base(); n && result < static_cast<luramas_address>(n)) {
                                    result = static_cast<luramas_address>(n);
                              }
                        }
                        for (const auto &e : i->extract_ordered_deep_exprs()) {
                              if (e && e->is_k<expr_kinds::closure>()) {
                                    spaces.emplace_back(e->closure);
                              }
                        }
                  }
            }
            return result + 1U;
      }
      luramas_address se_ir::avaliable_page() {
            if (this->ava_page) {
                  return ++ava_page;
            }
            this->ava_page = std::max(this->ava_page, this->avaliable_page(this->data));
            return (++this->ava_page);
      }

      luramas_address se_ir::avaliable_label(const ir_stat::space &data) {
            luramas_address result = 0U;
            for (const auto &i : data) {
                  result = std::max(i->label, result);
            }
            return result + 1U;
      }
      luramas_address se_ir::avaliable_label() {
            this->ava_label = std::max(this->ava_label, this->avaliable_label(this->data));
            return (++this->ava_label);
      }

      luramas_address se_ir::avaliable_end_label(const ir_stat::space &data) {
            luramas_address result = 0U;
            for (const auto &i : data) {
                  result = std::max(i->end_label, result);
            }
            return result + 1U;
      }
      luramas_address se_ir::avaliable_end_label() const {
            return luramas::ir::se_ir::avaliable_end_label(this->data);
      }

      luramas_register se_ir::avaliable_register(const ir_stat::space &data) {
            luramas_register result = 0U;
            for (const auto &i : data) {
                  for (const auto &e : i->extract_ordered_deep_exprs()) {
                        if (e->is_register_reference() && e->reg > result) {
                              result = e->reg;
                        }
                  }
            }
            return result + 1U;
      }
      luramas_register se_ir::avaliable_register() const {
            return luramas::ir::se_ir::avaliable_register(this->data);
      }

      luramas_count se_ir::ref_count(const ir_stat::space &data, const luramas_address label) {
            luramas_count result = 0U;
            for (const auto &i : data) {
                  result += static_cast<luramas_count>(i->jlabel == label);
            }
            return result;
      }
      luramas_count se_ir::ref_count(const luramas_address label) const {
            return luramas::ir::se_ir::ref_count(this->data, label);
      }
} // namespace luramas::ir