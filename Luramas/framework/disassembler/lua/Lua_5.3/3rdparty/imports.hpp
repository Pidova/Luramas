#pragma once
#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)
/* Common file for 3rd party imports. */

extern "C" {
#include "Lua_5.3.6/lauxlib.h"
#include "Lua_5.3.6/lcode.h"
#include "Lua_5.3.6/lobject.h"
#include "Lua_5.3.6/lopcodes.h"
#include "Lua_5.3.6/lstate.h"
#include "Lua_5.3.6/lua.h"
#include "Lua_5.3.6/lualib.h"
}
#endif
