#pragma once
#include "../lifter/tools/extras/exprs.hpp"
#include "../lifter/tools/extras/stats.hpp"

namespace luramas::ir::builder {

      struct builder {

            struct ebuilder {

                  ebuilder(const std::shared_ptr<ir_stat::ir_expr> &e, const std::shared_ptr<builder> &linked = nullptr)
                      : expr(e), linked(linked) {
                  }
                  ebuilder(const std::string &s, const std::shared_ptr<builder> &linked = nullptr)
                      : expr(tools::exprs::generate::global(s)), linked(linked) {
                  }
                  ebuilder(const luramas_int &i, const std::shared_ptr<builder> &linked = nullptr)
                      : expr(tools::exprs::generate::integral(i)), linked(linked) {
                  }
                  ebuilder(const luramas_register &r, const std::shared_ptr<builder> &linked = nullptr)
                      : expr(tools::exprs::generate::reg(r)), linked(linked) {
                  }
                  ebuilder(const ebuilder &other)
                      : expr(other.get()), linked(other.getl()) {
                  }
                  ebuilder() = default;

                  /* Assignment */
                  void operator=(const ebuilder &other) const;
                  void operator=(const std::shared_ptr<ir_stat::ir_expr> &other) const;

                  /* Arith */
                  ebuilder operator+(const ebuilder &other) const;
                  ebuilder operator-(const ebuilder &other) const;
                  ebuilder operator*(const ebuilder &other) const;
                  ebuilder operator/(const ebuilder &other) const;
                  ebuilder operator%(const ebuilder &other) const;
                  ebuilder operator+(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator-(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator*(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator/(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator%(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  void operator+=(const ebuilder &other) const;
                  void operator-=(const ebuilder &other) const;
                  void operator*=(const ebuilder &other) const;
                  void operator/=(const ebuilder &other) const;
                  void operator%=(const ebuilder &other) const;
                  void operator+=(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  void operator-=(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  void operator*=(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  void operator/=(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  void operator%=(const std::shared_ptr<ir_stat::ir_expr> &other) const;

                  /* Bitwise */
                  ebuilder operator&(const ebuilder &other) const;
                  ebuilder operator|(const ebuilder &other) const;
                  ebuilder operator^(const ebuilder &other) const;
                  ebuilder operator~() const;
                  ebuilder operator&(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator|(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator^(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  void operator&=(const ebuilder &other) const;
                  void operator|=(const ebuilder &other) const;
                  void operator^=(const ebuilder &other) const;
                  void operator&=(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  void operator|=(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  void operator^=(const std::shared_ptr<ir_stat::ir_expr> &other) const;

                  /* Shift */
                  ebuilder operator<<(const ebuilder &other) const;
                  ebuilder operator>>(const ebuilder &other) const;
                  ebuilder operator<<(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator>>(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  void operator<<=(const ebuilder &other) const;
                  void operator>>=(const ebuilder &other) const;
                  void operator<<=(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  void operator>>=(const std::shared_ptr<ir_stat::ir_expr> &other) const;

                  /* Compare */
                  ebuilder operator==(const ebuilder &other) const;
                  ebuilder operator!=(const ebuilder &other) const;
                  ebuilder operator<(const ebuilder &other) const;
                  ebuilder operator<=(const ebuilder &other) const;
                  ebuilder operator>(const ebuilder &other) const;
                  ebuilder operator>=(const ebuilder &other) const;
                  ebuilder operator==(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator!=(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator<(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator<=(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator>(const std::shared_ptr<ir_stat::ir_expr> &other) const;
                  ebuilder operator>=(const std::shared_ptr<ir_stat::ir_expr> &other) const;

                  /* Unary */
                  ebuilder operator+() const;
                  ebuilder operator-() const;

                  /* Types */
                  ebuilder t_none() const;
                  ebuilder t_flag() const;
                  ebuilder t_uint8() const;
                  ebuilder t_int8() const;
                  ebuilder t_uint16() const;
                  ebuilder t_int16() const;
                  ebuilder t_uint32() const;
                  ebuilder t_int32() const;
                  ebuilder t_uint64() const;
                  ebuilder t_int64() const;
                  ebuilder t_uint128() const;
                  ebuilder t_int128() const;
                  ebuilder t_uint256() const;
                  ebuilder t_int256() const;
                  ebuilder t_uint512() const;
                  ebuilder t_int512() const;
                  ebuilder t_uint1024() const;
                  ebuilder t_int1024() const;
                  ebuilder t_uint2048() const;
                  ebuilder t_int2048() const;
                  ebuilder t_uint4096() const;
                  ebuilder t_int4096() const;
                  ebuilder t_uint8192() const;
                  ebuilder t_int8192() const;
                  ebuilder t_uint16384() const;
                  ebuilder t_int16384() const;
                  ebuilder t_float() const;
                  ebuilder t_double() const;
                  ebuilder t_ldouble() const;
                  ebuilder t_lldouble() const;
                  ebuilder t_m128f() const;
                  ebuilder t_m128d() const;
                  ebuilder t_m128i() const;
                  ebuilder t_m256f() const;
                  ebuilder t_m256d() const;
                  ebuilder t_m256i() const;
                  ebuilder t_m512f() const;
                  ebuilder t_m512d() const;
                  ebuilder t_m512i() const;
                  ebuilder t_mmask8() const;
                  ebuilder t_mmask16() const;
                  ebuilder t_mmask32() const;
                  ebuilder t_mmask64() const;
                  ebuilder t_mmask128() const;
                  ebuilder t_mmask256() const;
                  ebuilder t_mmask512() const;

                  /* Virtual function */
                  ebuilder vf_call(const std::vector<ebuilder> &args, const luramas_int &id, const luramas_flag fsafe = false) const;
                  ebuilder vf_call(const std::vector<ebuilder> &args, const luramas::types::underlying_type t, const luramas_int &id, const luramas_flag fsafe = false) const;

                  /* Read memory */
                  ebuilder memread(const luramas_bitwidth &bits, const builder::ebuilder &offset) const;
                  ebuilder memread(const luramas_bitwidth &bits, const std::shared_ptr<ir_stat::ir_expr> &other = nullptr) const;

                  /* Ternary */
                  ebuilder ternary(const ebuilder &then, const ebuilder &else_) const;

                  /* Get */
                  std::shared_ptr<ir_stat::ir_expr> get() const;
                  std::optional<luramas_register> getr() const;
                  std::shared_ptr<builder> getl() const;
                  operator std::shared_ptr<ir_stat::ir_expr>() const {
                        return this->expr;
                  }

                  /* Cast */
                  template <luramas::types::underlying_type T>
                  inline ebuilder cast() const {
                        return ebuilder(tools::exprs::generate::cast(this->expr, T));
                  }

                  void link(const std::shared_ptr<builder> &b);

                private:
                  std::optional<luramas_register> reg = std::nullopt; /* Containing register if any */
                  std::shared_ptr<ir_stat::ir_expr> expr = nullptr;   /* Container expr if any */
                  std::shared_ptr<builder> linked = nullptr;          /* Parent builder linked to */
            };

            void lfunc(const std::vector<ebuilder> &args, const std::vector<ebuilder> &upvs, const std::vector<ebuilder> &flags, const std::vector<ebuilder> &casts);

            void lrepeat();
            void lif(const std::shared_ptr<ir_stat::ir_expr> &e);
            void lwhile(const std::shared_ptr<ir_stat::ir_expr> &e);
            void luntil(const std::shared_ptr<ir_stat::ir_expr> &e);
            void lend();
            void lelse();
            void lassign(const std::shared_ptr<ir_stat::ir_expr> &l, const std::shared_ptr<ir_stat::ir_expr> &r);
            void lset_flag(const std::shared_ptr<ir_stat::ir_expr> &flag, const std::shared_ptr<ir_stat::ir_expr> &source);
            void lmemoryset(const std::shared_ptr<ir_stat::ir_expr> &target, const std::shared_ptr<ir_stat::ir_expr> &source, const luramas_address set_bits, const std::shared_ptr<ir_stat::ir_expr> &offset = nullptr);

            operator ir_stat::space() const {
                  return this->code;
            }
            ir_stat::space get() const;

          private:
            ir_stat::space code;
      };

      builder::ebuilder b_reg(const luramas_register &r, const std::shared_ptr<builder> &linked = nullptr);
      builder::ebuilder b_int(const luramas_int &i, const std::shared_ptr<builder> &linked = nullptr);
} // namespace luramas::ir::builder