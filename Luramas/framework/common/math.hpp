#pragma once
#include "types/arith.hpp"
#include <cmath>
#include <cstddef>

namespace luramas::math {

      namespace hash {

            std::size_t mix(const std::size_t seed, std::size_t value);
      }

      bool is_decimal(const luramas_int &i);

      luramas_int log2(luramas_int n);

      luramas_int floor(const luramas_int &i);

      luramas_int round(const luramas_int &i);

      luramas_int abs(const luramas_int &i);

      luramas_int fmod(const luramas_int &a, const luramas_int &b);

      /* Calculates power of two given n (returns 0 if not) */
      luramas_int power_of_two(luramas_int n);

      luramas_int pow(const luramas_int &base, luramas_int exp);

      luramas_int count_digits(luramas_int n);

      /* If n is a max bites it counts its bytes */
      std::uint8_t count_byte_max(const luramas_int &n);

      /* Set int with n bits */
      luramas_int_base get_n_bits(const luramas_int_base n);

      namespace is {

            /* Is n a power of 2? */
            bool power_of_2(const luramas_int &n);

            /* Is n signed? */
            bool sign(const luramas_int &n);

            bool range_ee(const luramas_int &target, const luramas_int &start, const luramas_int &end); /* Treshold of target given range: inclusive, exclusive */
            bool range_ie(const luramas_int &target, const luramas_int &start, const luramas_int &end); /* Treshold of target given range: inclusive, exclusive */
            bool range_ei(const luramas_int &target, const luramas_int &start, const luramas_int &end); /* Treshold of target given range: exclusive, inclusive */
            bool range_ii(const luramas_int &target, const luramas_int &start, const luramas_int &end); /* Treshold of target given range: inclusive, inclusive */

            /* Is range mask? */
            bool range_mask(const luramas_int &n, std::uint16_t &istart, std::uint16_t &iend);
            bool range_mask(const luramas_int &n);
      } // namespace is

} // namespace luramas::math