#include "../structure.hpp"
#include "../common/keywords.hpp"

namespace luramas::il::lifter::builder::libraries::structure {

      void assign_pair(const build::expr &l, const build::expr &r, const build::expr &v) {
            l = (v & ((1u << l.bits()) - 1u));
            r = (v >> l.bits());
            return;
      }

      build::expr least_significant_bit(function_handler def, const build::expr &x) {

            auto result = def.temp();
            result = x & 1u;
            return result;
      }

      build::expr most_significant_bit(function_handler def, const build::expr &x, const luramas_bitwidth pos) {

            auto result = def.temp();
            result = (x >> (x.bits() - pos)) & 1;
            return result;
      }

      build::expr extend_sign(function_handler def, const build::expr &x, const types::underlying_type &t) {

            auto result = def.temp(x);
            if (x.bits() > t.bits()) {
                  return result.cast(t);
            }
            const auto mask = (1ull << (x.bits() - 1u));
            result = (result.cast(t) ^ mask) - mask;
            return result;
      }

      build::expr concat(function_handler def, const build::expr &hi, const build::expr &lo) {

            auto result = def.temp();
            result.cast(types::underlying_type(false, types::read_type::bits, 0u, hi.bits() + lo.bits()));
            result = (hi << lo.bits()) | lo;
            return result;
      }

      build::expr zero_extend(const build::expr &expr, const luramas_bitwidth n) {
            auto result = expr;
            return result.cast(types::underlying_type(false, types::read_type::bits, 0u, n));
      }

      build::expr saturate_to_unsigned_byte(function_handler def, const build::expr &expr) {

            auto result = def.temp().cast(true);
            kif(expr < 0u);
            {
                  result = 0u;
            }
            kelseif(expr > 255u);
            {
                  result = 255u;
            }
            kelse;
            {
                  result = expr;
            }
            kend;
            kend;
            kend;
            return result;
      }

      build::expr saturate_to_unsigned_word(function_handler def, const build::expr &expr) {

            auto result = def.temp().cast(true);
            kif(expr < 0u);
            {
                  result = 0u;
            }
            kelseif(expr > 65535u);
            {
                  result = 65535u;
            }
            kelse;
            {
                  result = expr;
            }
            kend;
            kend;
            kend;
            return result;
      }

      build::expr saturate_to_unsigned_dword(function_handler def, const build::expr &expr) {

            auto result = def.temp().cast(true);
            kif(expr < 0u);
            {
                  result = 0u;
            }
            kelseif(expr > 4294967295ll);
            {
                  result = 4294967295ll;
            }
            kelse;
            {
                  result = expr;
            }
            kend;
            kend;
            kend;
            return result;
      }

      build::expr saturate_to_unsigned_qword(function_handler def, const build::expr &expr) {

            auto result = def.temp().cast(true);
            kif(expr < 0u);
            {
                  result = 0u;
            }
            kelseif(expr > 18446744073709551615ull);
            {
                  result = 18446744073709551615ull;
            }
            kelse;
            {
                  result = expr;
            }
            kend;
            kend;
            kend;
            return result;
      }

      build::expr saturate_to_signed_byte(function_handler def, const build::expr &expr) {

            auto result = def.temp().cast(false);
            kif(expr < -128);
            {
                  result = -128;
            }
            kelseif(expr > 127);
            {
                  result = 127;
            }
            kelse;
            {
                  result = expr;
            }
            kend;
            kend;
            kend;
            return result;
      }

      build::expr saturate_to_signed_word(function_handler def, const build::expr &expr) {

            auto result = def.temp().cast(false);
            kif(expr < -32768);
            {
                  result = -32768;
            }
            kelseif(expr > 32767);
            {
                  result = 32767;
            }
            kelse;
            {
                  result = expr;
            }
            kend;
            kend;
            kend;
            return result;
      }

      build::expr saturate_to_signed_dword(function_handler def, const build::expr &expr) {

            auto result = def.temp().cast(false);
            kif(expr < -2147483648ll);
            {
                  result = -2147483648ll;
            }
            kelseif(expr > 2147483647ll);
            {
                  result = 2147483647ll;
            }
            kelse;
            {
                  result = expr;
            }
            kend;
            kend;
            kend;
            return result;
      }

      build::expr saturate_to_signed_qword(function_handler def, const build::expr &expr) {

            auto result = def.temp().cast(false);
            kif(expr < (-9223372036854775807ll - 1));
            {
                  result = (-9223372036854775807ll - 1);
            }
            kelseif(expr > 9223372036854775807ll);
            {
                  result = 9223372036854775807ll;
            }
            kelse;
            {
                  result = expr;
            }
            kend;
            kend;
            kend;
            return result;
      }

      build::expr interleave_blocks(function_handler def, const build::expr &a, const build::expr &b, const luramas_bitwidth bit_width, const luramas_bitwidth block_size) {

            auto r = def.temp();
            r.cast(types::underlying_type(false, types::read_type::bits, 0u, bit_width));

            const auto blocks = bit_width / block_size;
            for (auto i = 0; i < blocks; ++i) {

                  const auto ab = a.read(i * block_size, i * block_size + block_size - 1);
                  const auto bb = b.read(i * block_size, i * block_size + block_size - 1);
                  const auto out = i * block_size * 2;
                  r.write(out, out + block_size - 1, ab);
                  r.write(out + block_size, out + block_size * 2 - 1, bb);
            }
            return r;
      }
} // namespace luramas::il::lifter::builder::libraries::structure