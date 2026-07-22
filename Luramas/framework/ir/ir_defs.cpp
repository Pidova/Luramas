#include "ir_defs.hpp"

luramas_address se_ir::avaliable_page(const ir_stat::space &data) {

      luramas_address result = 0u;
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
      return result + 1u;
}
luramas_address se_ir::avaliable_page() {
      if (this->ava_page) {
            return ++ava_page;
      }
      if (const auto ava = this->avaliable_page(this->data); this->ava_page < ava) {
            this->ava_page = ava;
      }
      return (++this->ava_page);
}

luramas_address se_ir::avaliable_label(const ir_stat::space &data) {
      luramas_address result = 0u;
      for (const auto &i : data) {
            if (i->label > result) {
                  result = i->label;
            }
      }
      return result + 1u;
}
luramas_address se_ir::avaliable_label() {
      if (const auto ava = this->avaliable_label(this->data); this->ava_label < ava) {
            this->ava_label = ava;
      }
      return (++this->ava_label);
}

luramas_address se_ir::avaliable_end_label(const ir_stat::space &data) {
      luramas_address result = 0u;
      for (const auto &i : data) {
            if (i->end_label > result) {
                  result = i->end_label;
            }
      }
      return result + 1u;
}
luramas_address se_ir::avaliable_end_label() const {
      return this->avaliable_end_label(this->data);
}

luramas_register se_ir::avaliable_register(const ir_stat::space &data) {
      luramas_register result = 0u;
      for (const auto &i : data) {
            for (const auto &i : i->extract_ordered_deep_exprs()) {
                  if (i->is_register_reference() && i->reg > result) {
                        result = i->reg;
                  }
            }
      }
      return result + 1u;
}
luramas_register se_ir::avaliable_register() const {
      return this->avaliable_register(this->data);
}

luramas_count se_ir::ref_count(const ir_stat::space &data, const luramas_address label) {
      luramas_count result = 0u;
      for (const auto &i : data) {
            result += (i->jlabel == label);
      }
      return result;
}
luramas_count se_ir::ref_count(const luramas_address label) const {
      return this->ref_count(this->data, label);
}