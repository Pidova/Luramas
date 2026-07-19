#include "../bitwise.hpp"
#include "../common/keywords.hpp"

namespace luramas::il::lifter::builder::libraries::bitwise {

      build::expr popcount(function_handler def, const build::expr &x) {
            auto t = def.temp();
            t = x;
            auto result = def.temp();
            result = 0u;
            kwhile(t);
            {
                  result += t & 1u;
                  t >>= 1u;
            }
            kend;
            return result;
      }
} // namespace luramas::il::lifter::builder::libraries::bitwise