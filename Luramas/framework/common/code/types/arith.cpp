#include "../../types/arith.hpp"
#include <math.h>
#include <stdio.h>

inline std::pair<std::string, bool> sanatize(const std::string &s) {
      const auto b = s.find_first_not_of(" \t\n\r");
      const auto e = s.find_last_not_of(" \t\n\r");

      if (b == std::string::npos) {
            return {"0", false};
      }

      const auto trimmed = s.substr(b, e - b + 1);
      std::string r("");
      std::size_t i = 0u;
      bool precise = false;

      if (trimmed[i] == '-' || trimmed[i] == '+') {
            r += trimmed[i++];
      }
      for (; i < trimmed.size(); ++i) {
            const auto ch = trimmed[i];
            if (std::isdigit(ch)) {
                  r += ch;
            } else if (ch == '.') {
                  if (precise) {
                        break;
                  }
                  precise = true;
            }
      }
      return {(r == "-" || r == "+") ? "0" : r, precise};
}

luramas_int::luramas_int(const std::string &s) {
      const auto [str, percise] = sanatize(s);
      this->precision = percise;
      if (this->precision) {
            this->p = std::strtod(str.c_str(), nullptr);
      } else {
            this->b = luramas_int_xbase(str);
      }
      return;
}

luramas_int &luramas_int::operator=(const luramas_int &i) {
      this->precision = i.precision;
      this->b = i.b;
      this->p = i.p;
      return *this;
}
luramas_int &luramas_int::operator=(luramas_int &&i) {
      this->precision = i.precision;
      this->b = i.b;
      this->p = i.p;
      i.precision = false;
      i.b = 0;
      i.p = 0;
      return *this;
}
luramas_int &luramas_int::operator=(const luramas_int_base b) {
      this->precision = false;
      this->b = b;
      return *this;
}
luramas_int &luramas_int::operator=(const std::uintptr_t b) {
      this->precision = false;
      this->b = static_cast<luramas_int_base>(b);
      return *this;
}
luramas_int &luramas_int::operator=(const std::string &s) {
      const auto [str, percise] = sanatize(s);
      this->precision = percise;
      if (this->precision) {
            this->p = std::strtod(str.c_str(), nullptr);
      } else {
            this->b = luramas_int_xbase(str);
      }
      return *this;
}
luramas_int &luramas_int::operator=(const luramas_int_pbase p) {
      this->precision = true;
      this->p = p;
      return *this;
}
luramas_int &luramas_int::operator=(const luramas_int_xbase &b) {
      this->precision = false;
      this->b = b;
      return *this;
}
//luramas_int &luramas_int::operator=(const luramas_int_xpbase &p) {
//      this->precision = true;
//      this->p = p;
//      return *this;
//}

luramas_int luramas_int::operator+(const luramas_int &i) const {
      return this->precise() ? (i.precise() ? luramas_int(this->p + i.p) : luramas_int(this->p + i.cast_p()))
                             : (i.precise() ? luramas_int(this->cast_p() + i.p) : luramas_int(this->b + i.b));
}
luramas_int luramas_int::operator-(const luramas_int &i) const {
      return this->precise() ? (i.precise() ? luramas_int(this->p - i.p) : luramas_int(this->p - i.cast_p()))
                             : (i.precise() ? luramas_int(this->cast_p() - i.p) : luramas_int(this->b - i.b));
}
luramas_int luramas_int::operator*(const luramas_int &i) const {
      return this->precise() ? (i.precise() ? luramas_int(this->p * i.p) : luramas_int(this->p * i.cast_p()))
                             : (i.precise() ? luramas_int(this->cast_p() * i.p) : luramas_int(this->b * i.b));
}
luramas_int luramas_int::operator/(const luramas_int &i) const {
      return this->precise() ? (i.precise() ? luramas_int(this->p / i.p) : luramas_int(this->p / i.cast_p()))
                             : (i.precise() ? luramas_int(this->cast_p() / i.p) : luramas_int(this->b / i.b));
}
luramas_int luramas_int::operator%(const luramas_int &i) const {
      return this->precise() ? (i.precise() ? luramas_int(fmod(this->p, i.p)) : luramas_int(fmod(this->p, i.cast_p())))
                             : (i.precise() ? luramas_int(fmod(this->cast_p(), i.p)) : luramas_int(this->b % i.b));
}

luramas_int luramas_int::operator&(const luramas_int &i) const {
      return luramas_int(this->cast_b() & i.cast_b());
}
luramas_int luramas_int::operator|(const luramas_int &i) const {
      return luramas_int(this->cast_b() | i.cast_b());
}
luramas_int luramas_int::operator^(const luramas_int &i) const {
      return luramas_int(this->cast_b() ^ i.cast_b());
}
luramas_int luramas_int::operator<<(const luramas_int &i) const {
      return luramas_int(this->cast_b() << static_cast<std::size_t>(i.cast_b()));
}
luramas_int luramas_int::operator>>(const luramas_int &i) const {
      return luramas_int(this->cast_b() >> static_cast<std::size_t>(i.cast_b()));
}
luramas_int luramas_int::operator++() {
      return this->precision ? luramas_int(++this->p) : luramas_int(++this->b);
}
luramas_int luramas_int::operator--() {
      return this->precision ? luramas_int(--this->p) : luramas_int(--this->b);
}
luramas_int luramas_int::operator+() const {
      return this->precision ? luramas_int(+this->p) : luramas_int(+this->b);
}
luramas_int luramas_int::operator-() const {
      return this->precision ? luramas_int(-this->p) : luramas_int(-this->b);
}
luramas_int luramas_int::operator~() const {
      return luramas_int(~this->cast_b());
}

bool luramas_int::operator==(const luramas_int &i) const {
      return this->precise()
                 ? (i.precise() ? this->p == i.p : this->p == i.cast_p())
                 : (i.precise() ? this->cast_p() == i.p : this->b == i.b);
}
bool luramas_int::operator!=(const luramas_int &i) const {
      return this->precise()
                 ? (i.precise() ? this->p != i.p : this->p != i.cast_p())
                 : (i.precise() ? this->cast_p() != i.p : this->b != i.b);
}
bool luramas_int::operator<(const luramas_int &i) const {
      return this->precise()
                 ? (i.precise() ? this->p < i.p : this->p < i.cast_p())
                 : (i.precise() ? this->cast_p() < i.p : this->b < i.b);
}
bool luramas_int::operator<=(const luramas_int &i) const {
      return this->precise()
                 ? (i.precise() ? this->p <= i.p : this->p <= i.cast_p())
                 : (i.precise() ? this->cast_p() <= i.p : this->b <= i.b);
}
bool luramas_int::operator>(const luramas_int &i) const {
      return this->precise()
                 ? (i.precise() ? this->p > i.p : this->p > i.cast_p())
                 : (i.precise() ? this->cast_p() > i.p : this->b > i.b);
}
bool luramas_int::operator>=(const luramas_int &i) const {
      return this->precise()
                 ? (i.precise() ? this->p >= i.p : this->p >= i.cast_p())
                 : (i.precise() ? this->cast_p() >= i.p : this->b >= i.b);
}

bool luramas_int::operator==(const std::uint32_t i) const {
      return *this == luramas_int(i);
}
bool luramas_int::operator!=(const std::uint32_t i) const {
      return *this != luramas_int(i);
}
bool luramas_int::operator<(const std::uint32_t i) const {
      return *this < luramas_int(i);
}
bool luramas_int::operator<=(const std::uint32_t i) const {
      return *this <= luramas_int(i);
}
bool luramas_int::operator>(const std::uint32_t i) const {
      return *this > luramas_int(i);
}
bool luramas_int::operator>=(const std::uint32_t i) const {
      return *this >= luramas_int(i);
}

luramas_int &luramas_int::operator+=(const luramas_int &i) {
      return *this = *this + i;
}
luramas_int &luramas_int::operator-=(const luramas_int &i) {
      return *this = *this - i;
}
luramas_int &luramas_int::operator*=(const luramas_int &i) {
      return *this = *this * i;
}
luramas_int &luramas_int::operator/=(const luramas_int &i) {
      return *this = *this / i;
}
luramas_int &luramas_int::operator%=(const luramas_int &i) {
      return *this = *this % i;
}
luramas_int &luramas_int::operator&=(const luramas_int &i) {
      return *this = *this & i;
}
luramas_int &luramas_int::operator|=(const luramas_int &i) {
      return *this = *this | i;
}
luramas_int &luramas_int::operator^=(const luramas_int &i) {
      return *this = *this ^ i;
}
luramas_int &luramas_int::operator<<=(const luramas_int &i) {
      return *this = *this << i;
}
luramas_int &luramas_int::operator>>=(const luramas_int &i) {
      return *this = *this >> i;
}

luramas_int::operator bool() const {
      return this->precise() ? (this->p != 0.0) : (this->b != 0u);
}
luramas_int::operator luramas_int_base() const {
      return this->precise() ? static_cast<luramas_int_base>(this->p) : static_cast<luramas_int_base>(this->b);
}
luramas_int::operator luramas_int_pbase() const {
      return this->precise() ? static_cast<luramas_int_pbase>(this->p) : static_cast<luramas_int_pbase>(this->b);
}
luramas_int::operator luramas_int_xbase() const {
      return this->precise() ? static_cast<luramas_int_xbase>(this->p) : static_cast<luramas_int_xbase>(this->b);
}
luramas_int::operator luramas_int_xpbase() const {
      return this->precise() ? static_cast<luramas_int_xpbase>(this->p) : static_cast<luramas_int_xpbase>(this->b);
}

luramas_int_xbase luramas_int::cast_b() const {
      return this->precise() ? static_cast<decltype(this->b)>(this->p) : this->b;
}
double luramas_int::cast_p() const {
      return this->precise() ? this->p : static_cast<decltype(this->p)>(this->b);
}

double luramas_int::extract_double() const {
      return this->precise() ? this->p : double(this->b);
}
luramas_int_base luramas_int::extract_base() const {
      return static_cast<luramas_int_base>(this->b);
}

luramas_int luramas_int::min() const {
      return this->precise()
                 ? luramas_int(static_cast<luramas_int_pbase>(std::numeric_limits<luramas_int_pbase>::lowest()))
                 : luramas_int(static_cast<luramas_int_base>(std::numeric_limits<luramas_int_base>::lowest()));
}
luramas_int luramas_int::max() const {
      return this->precise()
                 ? luramas_int(static_cast<luramas_int_pbase>(std::numeric_limits<luramas_int_pbase>::max()))
                 : luramas_int(static_cast<luramas_int_base>(std::numeric_limits<luramas_int_base>::max()));
}

bool luramas_int::is_min_integral() const {
      return this->precise() ? this->p <= this->min().p : this->b <= this->min().b;
}
bool luramas_int::is_max_integral() const {
      return this->precise() ? this->p >= this->max().p : this->b >= this->max().b;
}

std::size_t luramas_int::size() const {
      return this->precise() ? sizeof(this->p) : MAX_BIT_WIDTH;
}
std::size_t luramas_int::max_size() const {
      return MAX_BIT_WIDTH > sizeof(this->p) ? MAX_BIT_WIDTH : sizeof(this->p);
}
bool luramas_int::precise() const {
      return this->precision;
}
bool luramas_int::negative() const {
      return this->precise() ? this->p < 0.0 : this->b < 0;
}
std::uint16_t luramas_int::bit_width() const {
      if (this->precise()) {
            return 1u;
      }
      const auto abs_b = boost::multiprecision::abs(this->b);
      return abs_b == 0 ? static_cast<std::uint16_t>(1) : static_cast<std::uint16_t>(boost::multiprecision::msb(abs_b) + 1);
}
std::uint16_t luramas_int::count_leading_ones() const {

      std::uint16_t result = 0u;
      if (!this->precise()) {

            auto v = this->b;
            for (auto i = this->bit_width() - 1u; i >= 0u; --i) {
                  if ((v >> i) & 1) {
                        ++result;
                  } else {
                        break;
                  }
            }
      }
      return result;
}
std::uint16_t luramas_int::count_trailing_zeros() const {

      std::uint16_t result = 0u;
      if (!this->precise()) {
            auto v = this->b;
            while (!(v & 1) && v) {
                  ++result;
                  v >>= 1;
            }
      }
      return result;
}
luramas_int luramas_int::read(const luramas_int &min, const luramas_int &max) const {

      if (max < min) {
            return 0u;
      }
      const auto mask = (luramas_int(1u) << (max - min + 1)) - 1;
      return (*this >> min) & mask;
}
std::pair<std::uint16_t, std::uint16_t> luramas_int::first_trailing_ones() const {

      bool in_run = false;
      const auto bw = this->bit_width();
      std::uint16_t start = 0u, end = 0u;

      for (auto i = 0u; i < bw; ++i) {
            if (((*this >> i) & 1u) == 1u) {
                  if (!in_run) {
                        start = i;
                        in_run = true;
                  }
                  end = i;
            } else if (in_run) {
                  break;
            }
      }
      return in_run ? std::make_pair(start, end) : std::make_pair(static_cast<std::uint16_t>(0u), static_cast<std::uint16_t>(0u));
}
luramas_int luramas_int::sign_extend(const std::uint16_t s) const {

      auto result = *this;
      const auto width = this->bit_width();
      if (s == width) {
            return *this;
      }
      if (result & (luramas_int(1) << (width - 1))) {
            result |= ((~luramas_int(0)) << width);
      }
      return result & ((luramas_int(1) << s) - 1);
}
luramas_int luramas_int::zero_extend(const std::uint16_t s) const {
      return s == this->bit_width() ? *this : *this & ((luramas_int(1) << s) - 1);
}
luramas_int luramas_int::extend(const std::uint16_t s, const bool unsign) const {
      return unsign ? this->zero_extend(s) : this->sign_extend(s);
}
luramas_int luramas_int::concat(const luramas_int &other) const {

      const auto rv = other.cast_b();
      auto temp = rv;
      luramas_int_xbase multiplier = 1;
      while (temp != 0) {
            temp /= 10;
            multiplier *= 10;
      }
      return luramas_int(this->cast_b() * multiplier + rv);
}

luramas_int luramas_int::mask(const std::uint16_t bits) const {

      auto result = *this;
      if (this->size() < bits) {
            result = luramas_int(0);
            result = ~result;
      } else {
            result = luramas_int((1 << bits) - 1);
      }
      return result;
}
luramas_int luramas_int::wrap(const std::uint16_t bits, const bool unsign, const std::uint16_t precision) const {

      if (bits == this->size()) {
            return *this;
      }
      if (!bits) {
            return luramas_int(0);
      }

      if (this->precision) {
            const auto range = std::pow(2.0, bits);
            const auto half = range / 2.0;
            const auto factor = std::pow(10.0, precision);
            auto val = std::fmod(std::fmod(std::round(p * factor) / factor, range) + range, range);
            if (!unsign && val >= half) {
                  val -= range;
            }
            return val;
      }
      if (unsign) {
            return *this & ((luramas_int(1) << bits) - 1);
      }
      const auto mod = luramas_int(1) << bits;
      auto val = *this % mod;
      if (val < 0) {
            val += mod;
      }
      if (val & (luramas_int(1) << (bits - 1))) {
            val -= mod;
      }
      return val;
}

void luramas_int::serialize(std::ostream &os) const {
      os.write(reinterpret_cast<const char *>(this), sizeof(*this));
      return;
}
void luramas_int::deserialize(std::istream &is) {
      is.read(reinterpret_cast<char *>(this), sizeof(*this));
      return;
}