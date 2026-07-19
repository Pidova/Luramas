/*
    Expanded structure functions
*/
#pragma once
#include "../builder.hpp"
#include "common/def.hpp"

namespace luramas::il::lifter::builder::libraries::structure {

      void assign_pair(const build::expr &l, const build::expr &r, const build::expr &v);
      build::expr least_significant_bit(function_handler def, const build::expr &x);
      build::expr most_significant_bit(function_handler def, const build::expr &x, const luramas_bitwidth pos = 1u);
      build::expr extend_sign(function_handler def, const build::expr &x, const types::underlying_type &t);
      build::expr concat(function_handler def, const build::expr &hi, const build::expr &lo);
      build::expr zero_extend(const build::expr &expr, const luramas_bitwidth n);
      build::expr saturate_to_unsigned_byte(function_handler def, const build::expr &expr);
      build::expr saturate_to_unsigned_word(function_handler def, const build::expr &expr);
      build::expr saturate_to_unsigned_dword(function_handler def, const build::expr &expr);
      build::expr saturate_to_unsigned_qword(function_handler def, const build::expr &expr);
      build::expr saturate_to_signed_byte(function_handler def, const build::expr &expr);
      build::expr saturate_to_signed_word(function_handler def, const build::expr &expr);
      build::expr saturate_to_signed_dword(function_handler def, const build::expr &expr);
      build::expr saturate_to_signed_qword(function_handler def, const build::expr &expr);
      build::expr interleave_blocks(function_handler def, const build::expr &a, const build::expr &b, const luramas_bitwidth bit_width, const luramas_bitwidth block_size);

} // namespace luramas::il::lifter::builder::libraries::structure