/*
    Expanded math functions
*/
#pragma once
#include "../builder.hpp"
#include "common/def.hpp"

namespace luramas::il::lifter::builder::libraries::math {

      build::expr abs(function_handler def, const build::expr &x);
      build::expr fabs(function_handler def, const build::expr &x);
      build::expr min(function_handler def, const build::expr &a, const build::expr &b);
      build::expr max(function_handler def, const build::expr &a, const build::expr &b);
      build::expr sign(function_handler def, const build::expr &x);
      build::expr clamp(function_handler def, const build::expr &x, const build::expr &min_val, const build::expr &max_val);
      build::expr is_even(function_handler def, const build::expr &x);
      build::expr is_odd(function_handler def, const build::expr &x);
      build::expr floor_div(function_handler def, const build::expr &a, const build::expr &b);
      build::expr mod(function_handler def, const build::expr &a, const build::expr &b);
      build::expr pow(function_handler def, const build::expr &base, const build::expr &exp);
      build::expr sqrt(function_handler def, const build::expr &n);
      build::expr sin(function_handler def, const build::expr &x);
      build::expr cos(function_handler def, const build::expr &x);
      build::expr tan(function_handler def, const build::expr &x);
      build::expr atan(function_handler def, const build::expr &x);
      build::expr log(function_handler def, const build::expr &x);
      build::expr log(function_handler def, const build::expr &x, const build::expr &base);
      build::expr floor(function_handler def, const build::expr &x);
      build::expr ceil(function_handler def, const build::expr &x);
      build::expr truncate(function_handler def, const build::expr &x);
      build::expr round_to_integer(function_handler def, const build::expr &src, const build::expr &round_control);
      build::expr parity(function_handler def, const build::expr &x);
      build::expr affine_byte(function_handler def, const build::expr &tsrc2qw, const build::expr &src1byte, const build::expr &imm8);
} // namespace luramas::il::lifter::builder::libraries::math