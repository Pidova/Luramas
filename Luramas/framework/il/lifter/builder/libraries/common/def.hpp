#pragma once
#include "../../builder.hpp"

struct function_handler {

      function_handler(const std::shared_ptr<luramas::il::lifter::builder::build> &b)
          : b(b) {
      }
      function_handler(const std::shared_ptr<luramas::il::lifter::builder::build> &b, const luramas_flag fglobalize, const luramas::il::lifter::builder::expr_flags &f)
          : b(b), fglobalize(fglobalize), f(f) {
      }

      inline luramas::il::lifter::builder::build::expr temp() {
            auto t = this->b->make_temp();
            if (this->fglobalize) {
                  t.emit_global(this->b, this->new_global());
            }
            t.f = this->f;
            return t;
      }
      inline luramas::il::lifter::builder::build::expr temp(const luramas::il::lifter::builder::build::expr &e) {
            auto t = this->b->make_temp();
            t = e;
            return t;
      }

      std::shared_ptr<luramas::il::lifter::builder::build> b = nullptr;

    private:
      inline std::string new_global() {
            return "r" + std::to_string(++counter);
      }
      luramas_count counter = 0u;
      luramas_flag fglobalize = false;
      luramas::il::lifter::builder::expr_flags f;
};