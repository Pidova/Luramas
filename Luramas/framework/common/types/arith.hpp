#pragma once
#define BOOST_MP_CPP_INT_LITERALS_HPP
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4146 4244 4267)
#endif
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/mpfr.hpp>
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
#include <cstdint>
#include <istream>
#include <limits>
#include <ostream>

#define MAX_BIT_WIDTH 1024u

using luramas_int_base = std::intptr_t;                                                                                                                                                                         /* Basic base */
using luramas_int_pbase = double;                                                                                                                                                                               /* Precision base */
using luramas_int_xbase = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<MAX_BIT_WIDTH, MAX_BIT_WIDTH, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>>; /* Extended base */
using luramas_int_xpbase = boost::multiprecision::mpfr_float;                                                                                                                                                   /* Extra percision base */
using luramas_int_range = std::pair<luramas_int_base, luramas_int_base>;                                                                                                                                        /* Range [start, end) */

/* Integer wrapper to support dynamic high bitwidth and precision */
struct luramas_int {

      constexpr luramas_int() noexcept
          : b(0) {
      }

      /* Str */
      luramas_int(const std::string &s);

      /* Signed */
      constexpr luramas_int(const std::int8_t v) noexcept
          : b(static_cast<luramas_int_base>(v)) {
      }
      constexpr luramas_int(const std::int16_t v) noexcept
          : b(static_cast<luramas_int_base>(v)) {
      }
      constexpr luramas_int(const std::int32_t v) noexcept
          : b(static_cast<luramas_int_base>(v)) {
      }
      constexpr luramas_int(const std::int64_t v) noexcept
          : b(static_cast<luramas_int_base>(v)) {
      }

      /* Unsigned */
      constexpr luramas_int(const std::uint8_t v) noexcept
          : b(static_cast<luramas_int_base>(v)) {
      }
      constexpr luramas_int(const std::uint16_t v) noexcept
          : b(static_cast<luramas_int_base>(v)) {
      }
      constexpr luramas_int(const std::uint32_t v) noexcept
          : b(static_cast<luramas_int_base>(v)) {
      }
      constexpr luramas_int(const std::uint64_t v) noexcept
          : b(static_cast<luramas_int_base>(v)) {
      }

      /* Percision */
      constexpr luramas_int(const float v) noexcept
          : precision(true), p(static_cast<luramas_int_pbase>(v)) {
      }
      constexpr luramas_int(const double v) noexcept
          : precision(true), p(static_cast<luramas_int_pbase>(v)) {
      }
      constexpr luramas_int(const long double v) noexcept
          : precision(true), p(static_cast<luramas_int_pbase>(v)) {
      }

      /* Extended */
      explicit constexpr luramas_int(const luramas_int_xbase &b) noexcept
          : b(b) {
      }
      //explicit constexpr luramas_int(const luramas_int_xpbase &p)
      //    : precision(true), p(p) {
      //}

      /* Same */
      constexpr luramas_int(const luramas_int &i) noexcept
          : precision(i.precision), b(i.b) {
      }
      constexpr luramas_int(luramas_int &&i) noexcept
          : precision(i.precision), b(i.b) {
            i.precision = false;
            i.b = 0;
            return;
      }
      ~luramas_int() noexcept {
            if (this->precision) {
                  //    this->p.~luramas_int_xpbase();
            } else {
                  this->b.~luramas_int_xbase();
            }
      }

      /* Assign */
      luramas_int &operator=(const luramas_int &i);
      luramas_int &operator=(luramas_int &&i);
      luramas_int &operator=(const luramas_int_base b);
      luramas_int &operator=(const std::uintptr_t b);
      luramas_int &operator=(const std::string &s);
      luramas_int &operator=(const luramas_int_pbase p);
      luramas_int &operator=(const luramas_int_xbase &b);

      /* Arith */
      luramas_int operator+(const luramas_int &i) const;
      luramas_int operator-(const luramas_int &i) const;
      luramas_int operator*(const luramas_int &i) const;
      luramas_int operator/(const luramas_int &i) const;
      luramas_int operator%(const luramas_int &i) const;
      luramas_int operator&(const luramas_int &i) const;
      luramas_int operator|(const luramas_int &i) const;
      luramas_int operator^(const luramas_int &i) const;
      luramas_int operator<<(const luramas_int &i) const;
      luramas_int operator>>(const luramas_int &i) const;
      luramas_int operator++();
      luramas_int operator--();
      luramas_int operator+() const;
      luramas_int operator-() const;
      luramas_int operator~() const;

      /* Condition */
      bool operator==(const luramas_int &i) const;
      bool operator!=(const luramas_int &i) const;
      bool operator<(const luramas_int &i) const;
      bool operator<=(const luramas_int &i) const;
      bool operator>(const luramas_int &i) const;
      bool operator>=(const luramas_int &i) const;

      /* Condition 32-Bit */
      bool operator==(const std::uint32_t i) const;
      bool operator!=(const std::uint32_t i) const;
      bool operator<(const std::uint32_t i) const;
      bool operator<=(const std::uint32_t i) const;
      bool operator>(const std::uint32_t i) const;
      bool operator>=(const std::uint32_t i) const;

      /* Arith assign */
      luramas_int &operator+=(const luramas_int &i);
      luramas_int &operator-=(const luramas_int &i);
      luramas_int &operator*=(const luramas_int &i);
      luramas_int &operator/=(const luramas_int &i);
      luramas_int &operator%=(const luramas_int &i);
      luramas_int &operator&=(const luramas_int &i);
      luramas_int &operator|=(const luramas_int &i);
      luramas_int &operator^=(const luramas_int &i);
      luramas_int &operator<<=(const luramas_int &i);
      luramas_int &operator>>=(const luramas_int &i);

      /* Arith */
      friend luramas_int operator+(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) + r;
      }
      friend luramas_int operator-(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) - r;
      }
      friend luramas_int operator*(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) * r;
      }
      friend luramas_int operator/(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) / r;
      }
      friend luramas_int operator&(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) & r;
      }
      friend luramas_int operator|(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) & r;
      }
      friend luramas_int operator^(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) ^ r;
      }
      friend luramas_int operator%(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) % r;
      }
      friend luramas_int operator<<(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) << r;
      }
      friend luramas_int operator>>(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) >> r;
      }
      /* Condition */
      friend bool operator==(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) == r;
      }
      friend bool operator!=(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) != r;
      }
      friend bool operator<(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) < r;
      }
      friend bool operator<=(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) <= r;
      }
      friend bool operator>(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) > r;
      }
      friend bool operator>=(const std::intptr_t l, const luramas_int &r) {
            return luramas_int(l) >= r;
      }

      /* Arith double */
      friend luramas_int operator+(const double l, const luramas_int &r) {
            return luramas_int(l) + r;
      }
      friend luramas_int operator-(const double l, const luramas_int &r) {
            return luramas_int(l) - r;
      }
      friend luramas_int operator*(const double l, const luramas_int &r) {
            return luramas_int(l) * r;
      }
      friend luramas_int operator/(const double l, const luramas_int &r) {
            return luramas_int(l) / r;
      }
      friend luramas_int operator&(const double l, const luramas_int &r) {
            return luramas_int(l) & r;
      }
      friend luramas_int operator|(const double l, const luramas_int &r) {
            return luramas_int(l) & r;
      }
      friend luramas_int operator^(const double l, const luramas_int &r) {
            return luramas_int(l) ^ r;
      }
      friend luramas_int operator%(const double l, const luramas_int &r) {
            return luramas_int(l) % r;
      }
      friend luramas_int operator<<(const double l, const luramas_int &r) {
            return luramas_int(l) << r;
      }
      friend luramas_int operator>>(const double l, const luramas_int &r) {
            return luramas_int(l) >> r;
      }
      /* Condition double */
      friend bool operator==(const double l, const luramas_int &r) {
            return luramas_int(l) == r;
      }
      friend bool operator!=(const double l, const luramas_int &r) {
            return luramas_int(l) != r;
      }
      friend bool operator<(const double l, const luramas_int &r) {
            return luramas_int(l) < r;
      }
      friend bool operator<=(const double l, const luramas_int &r) {
            return luramas_int(l) <= r;
      }
      friend bool operator>(const double l, const luramas_int &r) {
            return luramas_int(l) > r;
      }
      friend bool operator>=(const double l, const luramas_int &r) {
            return luramas_int(l) >= r;
      }

      /* Cast */
      explicit operator bool() const;
      explicit operator luramas_int_base() const;
      explicit operator luramas_int_pbase() const;
      explicit operator luramas_int_xbase() const;
      explicit operator luramas_int_xpbase() const;
      luramas_int_xbase cast_b() const;
      double cast_p() const;

      /* Extract */
      double extract_double() const;
      luramas_int_base extract_base() const;

      /* Min/Max */
      luramas_int min() const;
      luramas_int max() const;

      /* Is Min/Max */
      bool is_min_integral() const;
      bool is_max_integral() const;

      /* Misc */
      std::size_t size() const;     /* Size */
      std::size_t max_size() const; /* Max b size */

      bool precise() const;  /* Is percise? */
      bool negative() const; /* Is negative? */

      std::uint16_t bit_width() const;            /* Bit width of base */
      std::uint16_t count_leading_ones() const;   /* Count leading ones */
      std::uint16_t count_trailing_zeros() const; /* Count trailing zeros */

      luramas_int read(const luramas_int &min, const luramas_int &max) const; /* Read bits [min, max]; index starts 0 */
      std::pair<std::uint16_t, std::uint16_t> first_trailing_ones() const;
      luramas_int sign_extend(const std::uint16_t s) const;
      luramas_int zero_extend(const std::uint16_t s) const;
      luramas_int extend(const std::uint16_t s, const bool unsign) const;
      luramas_int concat(const luramas_int &other) const;

      /* Mutate */
      luramas_int mask(const std::uint16_t bits) const;
      luramas_int wrap(const std::uint16_t bits, const bool unsign = true, const std::uint16_t precision = 0u) const;

      /* Serialization*/
      void serialize(std::ostream &os) const;
      void deserialize(std::istream &is);

    private:
      bool precision = false; /* Uses precision? */
      union {
            luramas_int_xbase b; /* Basic base */
            double p;            /* Precision base */
      };
};