#pragma once

#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_536)
#include "../../../Luramas/framework/closures/closures.hpp"
#include "../../../Luramas/framework/il/il/il.hpp"
#include "../../../Luramas/framework/il/il/transformers/transformers.hpp"
#include "../../../Luramas/framework/ir/builder/builder.hpp"
#include "../../../Luramas/framework/ir/code/generate.hpp"
#include "../../../Luramas/framework/ir/ir.hpp"
#include <luramas/formatting/formatting.hpp>

namespace luramas {

      std::optional<std::string> decompile_lua_536(const std::string &code, std::shared_ptr<luramas::ir::data::format::format> &format, const bool bytecode);
}
#endif