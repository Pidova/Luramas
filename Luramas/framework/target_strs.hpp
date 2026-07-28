#pragma once

/* Target strings follow schema (ARCH)-(Version) */
namespace luramas {

      namespace tests {

            static constexpr auto output_folder = "output"; /* Output folder name to emit test output in tests, tests will ignore this folder */

            /* Sub-folders directory in tests for versions (Scripts not profiles) */
            namespace scripts_directory {

                  /* LURAMAS_TARGET_LUA */
                  static constexpr auto LUA_V51 = "scripts/lua/lua-5.1-tests"; /* Lua-5.1.x */
                  static constexpr auto LUA_V52 = "scripts/lua/lua-5.2-tests"; /* Lua-5.2.x */
                  static constexpr auto LUA_V53 = "scripts/lua/lua-5.3-tests"; /* Lua-5.3.x */
                  static constexpr auto LUA_V54 = "scripts/lua/lua-5.4-tests"; /* Lua-5.4.x */
                  static constexpr auto LUA_V55 = "scripts/lua/lua-5.5-tests"; /* Lua-5.5.x */
                  static constexpr auto LUA_EXTENSION = ".lua";                /* Lua extension output for tests */

                  /* LURAMAS_TARGET_LUAU */
                  static constexpr auto LUAU_V1 = "scripts/luau/V1";   /* LuaU-V1 */
                  static constexpr auto LUAU_V2 = "scripts/luau/V2";   /* LuaU-V2 */
                  static constexpr auto LUAU_V3 = "scripts/luau/V3";   /* LuaU-V3 */
                  static constexpr auto LUAU_V4 = "scripts/luau/V4";   /* LuaU-V4 */
                  static constexpr auto LUAU_V5 = "scripts/luau/V5";   /* LuaU-V5 */
                  static constexpr auto LUAU_V6 = "scripts/luau/V6";   /* LuaU-V6 */
                  static constexpr auto LUAU_V7 = "scripts/luau/V7";   /* LuaU-V7 */
                  static constexpr auto LUAU_V8 = "scripts/luau/V8";   /* LuaU-V8 */
                  static constexpr auto LUAU_V9 = "scripts/luau/V9";   /* LuaU-V9 */
                  static constexpr auto LUAU_V10 = "scripts/luau/V1";  /* LuaU-V10 */
                  static constexpr auto LUAU_V11 = "scripts/luau/V11"; /* LuaU-V11 */
                  static constexpr auto LUAU_V12 = "scripts/luau/V12"; /* LuaU-V12 */
                  static constexpr auto LUAU_EXTENSION = ".luau";      /* LuaU extension output for tests */

            } // namespace scripts_directory

      } // namespace tests

      /* Supported target relative strings */
      namespace supported_targets_str {

            /* LURAMAS_TARGET_LUA */
            static constexpr auto LUA_V53 = "Lua-V53"; /* LURAMAS_TARGET_LUA && LURAMAS_TARGET_VERSION_53 */

            /* LURAMAS_TARGET_LUAU */
            static constexpr auto LUAU_V6 = "LuaU-V6";   /* LURAMAS_TARGET_LUAU && LURAMAS_TARGET_VERSION_6 */
            static constexpr auto LUAU_V12 = "LuaU-V12"; /* LURAMAS_TARGET_LUAU && LURAMAS_TARGET_VERSION_12 */

            static constexpr auto X86 = "X86"; /* LURAMAS_TARGET_X86 */
      } // namespace supported_targets_str

} // namespace luramas