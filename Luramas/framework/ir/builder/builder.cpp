#include "builder.hpp"

namespace luramas::ir::builder {

      void builder::lassign(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r) {
            this->code.emplace_back(tools::stat::generate::assignment(l, r));
            return;
      }
      void builder::lset_flag(const std::shared_ptr<ir_stat::ir_expr> &flag, const std::shared_ptr<ir_stat::ir_expr> &source) {
            this->code.emplace_back(tools::stat::generate::set_flag(flag, source));
            return;
      }
      void builder::lmemoryset(const std::shared_ptr<ir_stat::ir_expr> &target, const std::shared_ptr<ir_stat::ir_expr> &source, const luramas_address set_bits, const std::shared_ptr<ir_stat::ir_expr> &offset) {
            this->code.emplace_back(tools::stat::generate::memoryset(target, source, set_bits, offset));
            return;
      }
      void builder::lfunc(const std::vector<ebuilder> &args, const std::vector<ebuilder> &upvs, const std::vector<ebuilder> &flags, const std::vector<ebuilder> &casts) {
            const auto res = tools::stat::generate::definition();
            for (const auto &i : args) {
                  if (const auto &reg = i.getr(); reg) {
                        res->args.try_emplace(*reg, i);
                  }
            }
            for (const auto &i : upvs) {
                  res->upvalues.emplace_back(i);
            }
            for (const auto &i : flags) {
                  res->members.emplace_back(i);
            }
            for (const auto &i : casts) {
                  res->meta.emplace_back(i);
            }
            return;
      }
      void builder::lrepeat() {
            this->code.emplace_back(tools::stat::generate::repeat());
            return;
      }
      void builder::lif(const std::shared_ptr<ir_stat::ir_expr> &e) {
            this->code.emplace_back(tools::stat::generate::cond(e, luramas::il::arch::data::bin_kinds::et_));
            return;
      }
      void builder::lwhile(const std::shared_ptr<ir_stat::ir_expr> &e) {
            this->code.emplace_back(tools::stat::generate::while_stat(e, luramas::il::arch::data::bin_kinds::et_));
            return;
      }
      void builder::luntil(const std::shared_ptr<ir_stat::ir_expr> &e) {
            this->code.emplace_back(tools::stat::generate::until(e, luramas::il::arch::data::bin_kinds::et_));
            return;
      }
      void builder::lend() {
            this->code.emplace_back(tools::stat::generate::end());
            return;
      }
      void builder::lelse() {
            this->code.emplace_back(tools::stat::generate::else_stat());
            return;
      }

      ir_stat::space builder::get() const {
            return this->code;
      }

      builder::ebuilder b_reg(const luramas_register &r, const std::shared_ptr<builder> &linked) {
            return builder::ebuilder(r, linked);
      }
      builder::ebuilder b_int(const luramas_int &i, const std::shared_ptr<builder> &linked) {
            return builder::ebuilder(i, linked);
      }

} // namespace luramas::ir::builder