/*
    Expanded bitwise functions
*/
#pragma once
#include "../builder.hpp"
#include "common/def.hpp"

namespace luramas::il::lifter::builder::libraries::bitwise {

      build::expr popcount(function_handler def, const build::expr &x);

} // namespace luramas::il::lifter::builder::libraries::bitwise