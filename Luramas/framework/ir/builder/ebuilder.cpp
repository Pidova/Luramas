#include "builder.hpp"

namespace luramas::ir::builder {

      ir_stat::ir_expr::space v(const std::vector<builder::ebuilder> &b) {

            ir_stat::ir_expr::space result;
            result.reserve(b.size());
            for (const auto &i : b) {
                  result.emplace_back(i.get());
            }
            return result;
      }

      void builder::ebuilder::operator=(const builder::ebuilder &other) const {
            *this = other.get();
            return;
      }
      void builder::ebuilder::operator=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            this->getl()->lassign(this->get(), other);
            return;
      }

      builder::ebuilder builder::ebuilder::operator+(const builder::ebuilder &other) const {
            return *this + other.get();
      }
      builder::ebuilder builder::ebuilder::operator-(const builder::ebuilder &other) const {
            return *this - other.get();
      }
      builder::ebuilder builder::ebuilder::operator*(const builder::ebuilder &other) const {
            return *this * other.get();
      }
      builder::ebuilder builder::ebuilder::operator/(const builder::ebuilder &other) const {
            return *this / other.get();
      }
      builder::ebuilder builder::ebuilder::operator%(const builder::ebuilder &other) const {
            return *this % other.get();
      }
      builder::ebuilder builder::ebuilder::operator+(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::arith(this->expr, other, il::arch::data::bin_kinds::add_), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator-(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::arith(this->expr, other, il::arch::data::bin_kinds::sub_), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator*(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::arith(this->expr, other, il::arch::data::bin_kinds::mul_), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator/(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::arith(this->expr, other, il::arch::data::bin_kinds::div_), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator%(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::arith(this->expr, other, il::arch::data::bin_kinds::mod_), this->getl());
      }
      void builder::ebuilder::operator+=(const ebuilder &other) const {
            *this = *this + other;
            return;
      }
      void builder::ebuilder::operator-=(const ebuilder &other) const {
            *this = *this - other;
            return;
      }
      void builder::ebuilder::operator*=(const ebuilder &other) const {
            *this = *this * other;
            return;
      }
      void builder::ebuilder::operator/=(const ebuilder &other) const {
            *this = *this / other;
            return;
      }
      void builder::ebuilder::operator%=(const ebuilder &other) const {
            *this = *this % other;
            return;
      }
      void builder::ebuilder::operator+=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            *this = *this + other;
            return;
      }
      void builder::ebuilder::operator-=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            *this = *this - other;
            return;
      }
      void builder::ebuilder::operator*=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            *this = *this * other;
            return;
      }
      void builder::ebuilder::operator/=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            *this = *this / other;
            return;
      }
      void builder::ebuilder::operator%=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            *this = *this % other;
            return;
      }

      builder::ebuilder builder::ebuilder::operator&(const builder::ebuilder &other) const {
            return *this & other.get();
      }
      builder::ebuilder builder::ebuilder::operator|(const builder::ebuilder &other) const {
            return *this | other.get();
      }
      builder::ebuilder builder::ebuilder::operator^(const builder::ebuilder &other) const {
            return *this ^ other.get();
      }
      builder::ebuilder builder::ebuilder::operator~() const {
            return ebuilder(tools::exprs::generate::unary(this->expr, il::arch::data::bin_kinds::bitnot_), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator&(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::arith(this->expr, other, il::arch::data::bin_kinds::and_), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator|(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::arith(this->expr, other, il::arch::data::bin_kinds::or_), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator^(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::arith(this->expr, other, il::arch::data::bin_kinds::xor_), this->getl());
      }
      void builder::ebuilder::operator&=(const ebuilder &other) const {
            *this = *this & other;
            return;
      }
      void builder::ebuilder::operator|=(const ebuilder &other) const {
            *this = *this | other;
            return;
      }
      void builder::ebuilder::operator^=(const ebuilder &other) const {
            *this = *this ^ other;
            return;
      }
      void builder::ebuilder::operator&=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            *this = *this & other;
            return;
      }
      void builder::ebuilder::operator|=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            *this = *this | other;
      }
      void builder::ebuilder::operator^=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            *this = *this ^ other;
            return;
      }

      builder::ebuilder builder::ebuilder::operator<<(const builder::ebuilder &other) const {
            return *this << other.get();
      }
      builder::ebuilder builder::ebuilder::operator>>(const builder::ebuilder &other) const {
            return *this >> other.get();
      }
      builder::ebuilder builder::ebuilder::operator<<(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::arith(this->expr, other, il::arch::data::bin_kinds::shl_), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator>>(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::arith(this->expr, other, il::arch::data::bin_kinds::shr_), this->getl());
      }
      void builder::ebuilder::operator<<=(const ebuilder &other) const {
            *this = *this << other;
            return;
      }
      void builder::ebuilder::operator>>=(const ebuilder &other) const {
            *this = *this >> other;
            return;
      }
      void builder::ebuilder::operator<<=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            *this = *this << other;
            return;
      }
      void builder::ebuilder::operator>>=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            *this = *this >> other;
            return;
      }

      builder::ebuilder builder::ebuilder::operator==(const builder::ebuilder &other) const {
            return *this == other.get();
      }
      builder::ebuilder builder::ebuilder::operator!=(const builder::ebuilder &other) const {
            return *this != other.get();
      }
      builder::ebuilder builder::ebuilder::operator<(const builder::ebuilder &other) const {
            return *this < other.get();
      }
      builder::ebuilder builder::ebuilder::operator<=(const builder::ebuilder &other) const {
            return *this <= other.get();
      }
      builder::ebuilder builder::ebuilder::operator>(const builder::ebuilder &other) const {
            return *this > other.get();
      }
      builder::ebuilder builder::ebuilder::operator>=(const builder::ebuilder &other) const {
            return *this >= other.get();
      }
      builder::ebuilder builder::ebuilder::operator==(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::cond(this->expr, il::arch::data::bin_kinds::eq_, other), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator!=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::cond(this->expr, il::arch::data::bin_kinds::ne_, other), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator<(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::cond(this->expr, il::arch::data::bin_kinds::lt_, other), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator<=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::cond(this->expr, il::arch::data::bin_kinds::lte_, other), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator>(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::cond(this->expr, il::arch::data::bin_kinds::gt_, other), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator>=(const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::cond(this->expr, il::arch::data::bin_kinds::gte_, other), this->getl());
      }

      builder::ebuilder builder::ebuilder::operator+() const {
            return ebuilder(tools::exprs::generate::unary(this->expr, il::arch::data::bin_kinds::plus_), this->getl());
      }
      builder::ebuilder builder::ebuilder::operator-() const {
            return ebuilder(tools::exprs::generate::unary(this->expr, il::arch::data::bin_kinds::minus_), this->getl());
      }

      builder::ebuilder builder::ebuilder::t_none() const {
            return this->cast<luramas::types::native::t_none>();
      }
      builder::ebuilder builder::ebuilder::t_flag() const {
            return this->cast<luramas::types::native::t_flag>();
      }
      builder::ebuilder builder::ebuilder::t_uint8() const {
            return this->cast<luramas::types::native::t_uint8>();
      }
      builder::ebuilder builder::ebuilder::t_int8() const {
            return this->cast<luramas::types::native::t_int8>();
      }
      builder::ebuilder builder::ebuilder::t_uint16() const {
            return this->cast<luramas::types::native::t_uint16>();
      }
      builder::ebuilder builder::ebuilder::t_int16() const {
            return this->cast<luramas::types::native::t_int16>();
      }
      builder::ebuilder builder::ebuilder::t_uint32() const {
            return this->cast<luramas::types::native::t_uint32>();
      }
      builder::ebuilder builder::ebuilder::t_int32() const {
            return this->cast<luramas::types::native::t_int32>();
      }
      builder::ebuilder builder::ebuilder::t_uint64() const {
            return this->cast<luramas::types::native::t_uint64>();
      }
      builder::ebuilder builder::ebuilder::t_int64() const {
            return this->cast<luramas::types::native::t_int64>();
      }
      builder::ebuilder builder::ebuilder::t_uint128() const {
            return this->cast<luramas::types::native::t_uint128>();
      }
      builder::ebuilder builder::ebuilder::t_int128() const {
            return this->cast<luramas::types::native::t_int128>();
      }
      builder::ebuilder builder::ebuilder::t_uint256() const {
            return this->cast<luramas::types::native::t_uint256>();
      }
      builder::ebuilder builder::ebuilder::t_int256() const {
            return this->cast<luramas::types::native::t_int256>();
      }
      builder::ebuilder builder::ebuilder::t_uint512() const {
            return this->cast<luramas::types::native::t_uint512>();
      }
      builder::ebuilder builder::ebuilder::t_int512() const {
            return this->cast<luramas::types::native::t_int512>();
      }
      builder::ebuilder builder::ebuilder::t_uint1024() const {
            return this->cast<luramas::types::native::t_uint1024>();
      }
      builder::ebuilder builder::ebuilder::t_int1024() const {
            return this->cast<luramas::types::native::t_int1024>();
      }
      builder::ebuilder builder::ebuilder::t_uint2048() const {
            return this->cast<luramas::types::native::t_uint2048>();
      }
      builder::ebuilder builder::ebuilder::t_int2048() const {
            return this->cast<luramas::types::native::t_int2048>();
      }
      builder::ebuilder builder::ebuilder::t_uint4096() const {
            return this->cast<luramas::types::native::t_uint4096>();
      }
      builder::ebuilder builder::ebuilder::t_int4096() const {
            return this->cast<luramas::types::native::t_int4096>();
      }
      builder::ebuilder builder::ebuilder::t_uint8192() const {
            return this->cast<luramas::types::native::t_uint8192>();
      }
      builder::ebuilder builder::ebuilder::t_int8192() const {
            return this->cast<luramas::types::native::t_int8192>();
      }
      builder::ebuilder builder::ebuilder::t_uint16384() const {
            return this->cast<luramas::types::native::t_uint16384>();
      }
      builder::ebuilder builder::ebuilder::t_int16384() const {
            return this->cast<luramas::types::native::t_int16384>();
      }
      builder::ebuilder builder::ebuilder::t_float() const {
            return this->cast<luramas::types::native::t_float>();
      }
      builder::ebuilder builder::ebuilder::t_double() const {
            return this->cast<luramas::types::native::t_double>();
      }
      builder::ebuilder builder::ebuilder::t_ldouble() const {
            return this->cast<luramas::types::native::t_ldouble>();
      }
      builder::ebuilder builder::ebuilder::t_lldouble() const {
            return this->cast<luramas::types::native::t_lldouble>();
      }
      builder::ebuilder builder::ebuilder::t_m128f() const {
            return this->cast<luramas::types::native::t_m128f>();
      }
      builder::ebuilder builder::ebuilder::t_m128d() const {
            return this->cast<luramas::types::native::t_m128d>();
      }
      builder::ebuilder builder::ebuilder::t_m128i() const {
            return this->cast<luramas::types::native::t_m128i>();
      }
      builder::ebuilder builder::ebuilder::t_m256f() const {
            return this->cast<luramas::types::native::t_m256f>();
      }
      builder::ebuilder builder::ebuilder::t_m256d() const {
            return this->cast<luramas::types::native::t_m256d>();
      }
      builder::ebuilder builder::ebuilder::t_m256i() const {
            return this->cast<luramas::types::native::t_m256i>();
      }
      builder::ebuilder builder::ebuilder::t_m512f() const {
            return this->cast<luramas::types::native::t_m512f>();
      }
      builder::ebuilder builder::ebuilder::t_m512d() const {
            return this->cast<luramas::types::native::t_m512d>();
      }
      builder::ebuilder builder::ebuilder::t_m512i() const {
            return this->cast<luramas::types::native::t_m512i>();
      }
      builder::ebuilder builder::ebuilder::t_mmask8() const {
            return this->cast<luramas::types::native::t_mmask8>();
      }
      builder::ebuilder builder::ebuilder::t_mmask16() const {
            return this->cast<luramas::types::native::t_mmask16>();
      }
      builder::ebuilder builder::ebuilder::t_mmask32() const {
            return this->cast<luramas::types::native::t_mmask32>();
      }
      builder::ebuilder builder::ebuilder::t_mmask64() const {
            return this->cast<luramas::types::native::t_mmask64>();
      }
      builder::ebuilder builder::ebuilder::t_mmask128() const {
            return this->cast<luramas::types::native::t_mmask128>();
      }
      builder::ebuilder builder::ebuilder::t_mmask256() const {
            return this->cast<luramas::types::native::t_mmask256>();
      }
      builder::ebuilder builder::ebuilder::t_mmask512() const {
            return this->cast<luramas::types::native::t_mmask512>();
      }

      builder::ebuilder builder::ebuilder::vf_call(const std::vector<builder::ebuilder> &args, const luramas_int &id, const luramas_flag fsafe) const {
            return ebuilder(tools::exprs::generate::virtualfunction_call(this->expr, v(args), id, fsafe), this->getl());
      }
      builder::ebuilder builder::ebuilder::vf_call(const std::vector<builder::ebuilder> &args, const luramas::types::underlying_type t, const luramas_int &id, const luramas_flag fsafe) const {
            return ebuilder(tools::exprs::generate::virtualfunction_call(this->expr, v(args), t, id, fsafe), this->getl());
      }

      builder::ebuilder builder::ebuilder::memread(const luramas_bitwidth &bits, const builder::ebuilder &offset) const {
            return this->memread(bits, offset.get());
      }
      builder::ebuilder builder::ebuilder::memread(const luramas_bitwidth &bits, const std::shared_ptr<ir_stat::ir_expr> &other) const {
            return ebuilder(tools::exprs::generate::memoryread(this->expr, bits, other), this->getl());
      }

      builder::ebuilder builder::ebuilder::ternary(const builder::ebuilder &then, const builder::ebuilder &else_) const {
            return ebuilder(tools::exprs::generate::ternary(this->expr, then, else_), this->getl());
      }

      std::shared_ptr<ir_stat::ir_expr> builder::ebuilder::get() const {
            return this->expr;
      }
      std::optional<luramas_register> builder::ebuilder::getr() const {
            return this->reg;
      }
      std::shared_ptr<builder> builder::ebuilder::getl() const {
            return this->linked;
      }

      void builder::ebuilder::link(const std::shared_ptr<builder> &b) {
            this->linked = b;
            return;
      }
} // namespace luramas::ir::builder