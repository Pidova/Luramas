#pragma once
#include "../../passes.hpp"

using pattern_cb = void (*)(luramas::ir::passes::pass_manager &, luramas::ir::passes::shared &, const luramas_address);