#include "../bitwise.hpp"
#include "../common/keywords.hpp"

namespace luramas::il::lifter::builder::libraries::bitwise {

      build::expr popcount(function_handler def, const build::expr &x) {
            auto t = def.temp();
            t = x;
            auto result = def.temp();
            result = 0U;
            kwhile(t);
            {
                  result += t & 1U;
                  t >>= 1U;
            }
            kend;
            return result;
      }
} // namespace luramas::il::lifter::builder::libraries::bitwise