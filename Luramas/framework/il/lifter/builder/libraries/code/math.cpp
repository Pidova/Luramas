#include "../math.hpp"
#include "../common/keywords.hpp"

namespace luramas::il::lifter::builder::libraries::math {

      build::expr abs(function_handler def, const build::expr &x) {

            auto result = def.temp();
            kif(x < 0);
            {
                  result = -x;
            }
            kelse;
            {
                  result = x;
            }
            kend;
            return result;
      }
      build::expr fabs(function_handler def, const build::expr &x) {

            return abs(def, x);
      }

      build::expr min(function_handler def, const build::expr &a, const build::expr &b) {

            auto result = def.temp();
            kif(a < b);
            {
                  result = a;
            }
            kelse;
            {
                  result = b;
            }
            kend;
            return result;
      }

      build::expr max(function_handler def, const build::expr &a, const build::expr &b) {

            auto result = def.temp();
            kif(a > b);
            {
                  result = a;
            }
            kelse;
            {
                  result = b;
            }
            kend;
            return result;
      }

      build::expr sign(function_handler def, const build::expr &x) {

            auto result = def.temp();
            kif(x > 0);
            {
                  result = 1;
            }
            kelseif(x < 0);
            {
                  result = -1;
            }
            kelse;
            {
                  result = 0;
            }
            kend;
            kend;
            kend;
            return result;
      }

      build::expr clamp(function_handler def, const build::expr &x, const build::expr &min_val, const build::expr &max_val) {

            auto result = def.temp();
            result = max(def, min_val, min(def, x, max_val));
            return result;
      }

      build::expr is_even(function_handler def, const build::expr &x) {

            auto result = def.temp();
            result = (x % 2 == 0);
            return result;
      }

      build::expr is_odd(function_handler def, const build::expr &x) {

            auto result = def.temp();
            result = (x % 2 != 0);
            return result;
      }

      build::expr floor_div(function_handler def, const build::expr &a, const build::expr &b) {

            auto result = def.temp();
            result = (a / b);
            kif(((a < 0) != (b < 0)) && (a % b != 0));
            {
                  result -= 1;
            }
            kend;
            return result;
      }

      build::expr mod(function_handler def, const build::expr &a, const build::expr &b) {

            auto result = def.temp();
            result = a % b;
            kif(result < 0);
            {
                  result += abs(def, b);
            }
            kend;
            return result;
      }

      build::expr pow(function_handler def, const build::expr &base, const build::expr &exp) {

            auto result = def.temp();
            result = 1;
            kwhile(exp > 0);
            {
                  kif(exp % 2 == 1);
                  {
                        result *= base;
                  }
                  kend;
                  base *= base;
                  exp /= 2;
            }
            kend;
            return result;
      }
      build::expr sqrt(function_handler def, const build::expr &n) {

            auto result = def.temp();
            kif(n < 0);
            {
                  result.error<expr_error::NaN>();
            }
            kelseif(n == 0 || n == 1);
            {
                  result = 0;
            }
            kelse;
            {
                  auto x = def.temp();
                  auto y = def.temp();

                  x = n;
                  y = (x + n / x) / 2;
                  kwhile(y < x);
                  {
                        x = y;
                        y = (x + n / x) / 2;
                  }
                  kend;
            }
            kend;
            kend;
            kend;
            return result;
      }

      build::expr sin(function_handler def, const build::expr &x) {
            return x - (pow(def, x, build::expr(x.b, 3u)) / build::expr(x.b, 6u)) + (pow(def, x, build::expr(x.b, 5u)) / build::expr(x.b, 120u)) - (pow(def, x, build::expr(x.b, 7u)) / 5040u);
      }
      build::expr cos(function_handler def, const build::expr &x) {
            return 1 - (pow(def, x, build::expr(x.b, 2u)) / build::expr(x.b, 2u)) + (pow(def, x, build::expr(x.b, 4u)) / build::expr(x.b, 24u)) - (pow(def, x, build::expr(x.b, 6u)) / 720u);
      }
      build::expr tan(function_handler def, const build::expr &x) {
            return sin(def, x) / cos(def, x);
      }
      build::expr atan(function_handler def, const build::expr &x) {

            auto absx = abs(def, x);
            auto result = def.temp();

            kif(absx <= 1);
            {
                  result = x - pow(def, x, build::expr(x.b, 3u)) / 3 + pow(def, x, build::expr(x.b, 5u)) / 5 - pow(def, x, build::expr(x.b, 7u)) / 7;
            }
            kelse;
            {
                  auto invx = 1 / x;
                  auto approx = invx - pow(def, invx, build::expr(x.b, 3u)) / 3 + pow(def, invx, build::expr(x.b, 5u)) / 5 - pow(def, invx, build::expr(x.b, 7u)) / 7;

                  result = (1570796327 - approx) * sign(def, x);
            }
            kend;

            return result;
      }

      build::expr log(function_handler def, const build::expr &x) {
            auto y = def.temp();
            auto prev = def.temp();

            y = x - 1u;
            prev = 0u;

            kwhile(abs(def, y - prev) > 1) {
                  prev = y;
                  const auto e = pow(def, build::expr(x.b, 2718281828), y);
                  y -= (e - x) / e;
            }
            kend;
            return y;
      }
      build::expr log(function_handler def, const build::expr &x, const build::expr &base) {
            return log(def, x) / log(def, base);
      }

      build::expr floor(function_handler def, const build::expr &x) {

            auto trunc = def.temp();
            auto result = def.temp();
            auto adjust = def.temp();

            trunc = x;
            result = trunc;

            adjust = def.temp();
            kif((x < 0) & (x != result));
            {
                  adjust = build::expr(def.b, 1.0);
            }
            kelse;
            {
                  adjust = build::expr(def.b, 0.0);
            }
            kend;
            result -= adjust;
            return result;
      }
      build::expr ceil(function_handler def, const build::expr &x) {

            auto trunc = def.temp();
            auto result = def.temp();
            auto adjust = def.temp();

            trunc = x;
            result = trunc;

            adjust = def.temp();
            kif((x > 0) & (x != result));
            {
                  adjust = build::expr(def.b, 1.0);
            }
            kelse;
            {
                  adjust = build::expr(def.b, 0.0);
            }
            kend;
            result += adjust;
            return result;
      }
      build::expr truncate(function_handler def, const build::expr &x) {

            auto result = def.temp();
            auto sign = def.temp();

            sign = x < 0;

            kif(x < 0);
            {
                  result = ceil(def, x);
            }
            kelse;
            {
                  result = floor(def, x);
            }
            return result;
      }
      build::expr round_to_integer(function_handler def, const build::expr &src, const build::expr &round_control) {

            auto result = def.temp();
            auto half = def.temp();
            auto sign = def.temp();

            sign = src < 0;
            kif(sign != 0);
            {
                  half = build::expr(def.b, -0.5);
            }
            kelse;
            {
                  half = build::expr(def.b, 0.5);
            }

            kif(round_control == 0u); /* round to nearest */
            {
                  result = src + half;
            }
            kelseif(round_control == 1u); /* truncate */
            {
                  result = src;
            }
            kelseif(round_control == 2u); /* floor */
            {
                  kif(sign != 0);
                  {
                        result = src - build::expr(def.b, 1.0);
                  }
                  kelse;
                  {
                        half = src;
                  }
            }
            kelseif(round_control == 3u); /* ceil */
            {
                  kif(sign != 0);
                  {
                        result = src;
                  }
                  kelse;
                  {
                        half = src + build::expr(def.b, 1.0);
                  }
            }
            kelse;
            {
                  result = src + half;
            }
            kend;
            kend;
            kend;
            kend;

            result = truncate(def, result);
            return result;
      }

} // namespace luramas::il::lifter::builder::libraries::math