#include "../math.hpp"

namespace luramas::math {

      namespace hash {

            std::size_t mix(const std::size_t seed, std::size_t value) {
                  value ^= value >> 33;
                  value *= 0xff51afd7ed558ccd;
                  value ^= value >> 33;
                  value *= 0xc4ceb9fe1a85ec53;
                  value ^= value >> 33;
                  return seed ^ (value + 0x9e3779b97f4a7c15 + (seed << 6) + (seed >> 2));
            }
      } // namespace hash

      bool is_decimal(const luramas_int &i) {
            double n;
            return std::modf(i.precise() ? i.extract_double() : i.extract_base(), &n) != 0.0;
      }

      luramas_int log2(luramas_int n) {
            auto result = luramas_int(0U);
            while (n >>= 1) {
                  ++result;
            }
            return result;
      }

      luramas_int fmod(const luramas_int &a, const luramas_int &b) {
            if (a.precise() || b.precise()) {
                  return luramas_int(std::fmod(a.extract_double(), b.extract_double()));
            }
            return luramas_int(a.extract_base() % b.extract_base());
      }

      luramas_int floor(const luramas_int &i) {
            return i.precise() ? luramas_int(static_cast<luramas_int_pbase>(std::floor(i.extract_double()))) : i;
      }

      luramas_int round(const luramas_int &i) {
            return i.precise() ? luramas_int(static_cast<luramas_int_pbase>(std::round(i.extract_double()))) : i;
      }

      luramas_int abs(const luramas_int &i) {
            return i.precise() ? luramas_int(std::abs(i.extract_double())) : luramas_int(std::abs(i.extract_base()));
      }

      luramas_int power_of_two(luramas_int n) {
            if (!is::power_of_2(n)) {
                  return 0;
            }
            luramas_int result = 0;
            while (n > 1) {
                  n >>= 1;
                  ++result;
            }
            return result;
      }

      luramas_int pow(const luramas_int &base, luramas_int exp) {
            if (exp == 0) {
                  return 1;
            }
            auto result = base;
            while (exp > 1) {
                  result *= base;
                  --exp;
            }
            return result;
      }

      luramas_int count_digits(luramas_int n) {

            luramas_int count = 0U;
            if (n == 0) {
                  return 1;
            }
            if (n < 0) {
                  n = -n;
            }
            while (n > 0) {
                  n /= 10;
                  ++count;
            }
            return count;
      }

      std::uint8_t count_byte_max(const luramas_int &n) {
            if (n.precise()) {
                  return 0U;
            }
            switch (n.extract_base()) {
                  case 0xFF: {
                        return 1U;
                  }
                  case 0xFFFF: {
                        return 2U;
                  }
                  case 0xFFFFFF: {
                        return 3U;
                  }
                  case 0xFFFFFFFF: {
                        return 4U;
                  }
                  case 0xFFFFFFFFFF: {
                        return 5U;
                  }
                  case 0xFFFFFFFFFFFF: {
                        return 6U;
                  }
                  case 0xFFFFFFFFFFFFFF: {
                        return 7U;
                  }
                  default: {
                        return n.is_max_integral() ? sizeof(luramas_int_base) : 0U;
                  }
            }
      }

      luramas_int_base get_n_bits(const luramas_int_base n) {
            if (n >= sizeof(luramas_int_base) * 8U) {
                  return ~static_cast<luramas_int_base>(0U);
            }
            return !n ? 0 : (static_cast<luramas_int_base>(1U) << n) - 1;
      }

      namespace is {

            bool power_of_2(const luramas_int &n) {
                  return n != 0 && (n & (n - 1)) == 0;
            }
            bool sign(const luramas_int &n) {
                  return n.precise() ? std::signbit(n.extract_double()) : (n.extract_base() < 0);
            }

            bool range_ee(const luramas_int &target, const luramas_int &start, const luramas_int &end) {
                  return target > start && target < end;
            }
            bool range_ie(const luramas_int &target, const luramas_int &start, const luramas_int &end) {
                  return target >= start && target < end;
            }
            bool range_ei(const luramas_int &target, const luramas_int &start, const luramas_int &end) {
                  return target > start && target <= end;
            }
            bool range_ii(const luramas_int &target, const luramas_int &start, const luramas_int &end) {
                  return target >= start && target <= end;
            }

            bool range_mask(const luramas_int &n, std::uint16_t &istart, std::uint16_t &iend) {
                  const auto width = n.bit_width();
                  std::tie(istart, iend) = n.first_trailing_ones();
                  return ((istart == 0U) || !n.read(0U, istart - 1U)) && (iend + 1U > width - 1U || !n.read(iend + 1U, width - 1U));
            }
            bool range_mask(const luramas_int &n) {
                  [[maybe_unused]] std::uint16_t s = 0U;
                  [[maybe_unused]] std::uint16_t e = 0U;
                  return range_mask(n, s, e);
            }
      } // namespace is

} // namespace luramas::math