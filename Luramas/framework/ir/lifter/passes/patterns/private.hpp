#pragma once
#include "../../generation.hpp"
#include "../../passes.hpp"
#include "../../tools/extras/exprs.hpp"
#include "../../tools/extras/stats.hpp"
#include "../../tools/tools.hpp"
#include "../process/process.hpp"

#if defined(LURAMAS_TARGET_LUA) || defined(LURAMAS_TARGET_LUAU)
#define LURAMAS_IR_CONSTANT_TABLE_BASE 1
#else
#define LURAMAS_IR_CONSTANT_TABLE_BASE 0
#endif