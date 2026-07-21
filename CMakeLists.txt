cmake_minimum_required(VERSION 3.21)
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/conan_provider.cmake")
project(Luramas VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compile options 
if(MSVC AND CMAKE_GENERATOR MATCHES "Visual Studio")
    add_compile_options(/MP)
endif()
if(MSVC)
    add_compile_options(/W3 /utf-8 /wd4458 /wd4456 /wd4244 /wd4100)
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:/Zc:preprocessor>)
    set(THIRDPARTY_NO_WARN /w)
else()
    add_compile_options(-Wall -Wextra -Wno-invalid-constexpr -Wno-ignored-qualifiers -Wno-unused-parameter)
    set(THIRDPARTY_NO_WARN -w)
endif()
if(CMAKE_GENERATOR MATCHES "Ninja")
    set_property(GLOBAL PROPERTY JOB_POOLS compile_pool=8)
    set(CMAKE_JOB_POOL_COMPILE compile_pool)
endif()

# Targets
option(LURAMAS_TARGET_X86  "Enable x86-64 assembly lifters and disassemblers" ON)
option(LURAMAS_TARGET_LUA  "Enable Lua lifters and disassemblers"             ON)
option(LURAMAS_TARGET_LUAU "Enable Luau lifters and disassemblers"            ON)
option(LURAMAS_TARGET_VERSION_536 "Target Lua 5.3.6 bytecode"  ON)
option(LURAMAS_TARGET_VERSION_6   "Target Luau version 6 bytecode" ON)
# Other
option(LURAMAS_ECC     "Enable internal error correction checks" OFF)
option(LURAMAS_PROFILE "Enable time checks on passes"            OFF)
# Debug
option(LURAMAS_DEBUG_SSA_STEPS       "Print each SSA step to debug"        OFF)
option(LURAMAS_DEBUG_NO_DUMP         "Disallow dumps"                      OFF)
option(LURAMAS_DEBUG_ERROR_CLIPBOARD "Copy dumped data to clipboard"       OFF)
option(LURAMAS_TARGET_BIGDATA        "Dump big data into LURAMAS_GLOBAL_PDUMP" OFF)

# Gather all source file groups
file(GLOB_RECURSE EXAMPLE_FILES
    "examples/*.hpp" 
    "examples/*.cpp" 
    "examples/*.h" 
    "examples/*.c")
file(GLOB_RECURSE SOURCE_FILES
    "Luramas/framework/*.hpp" 
    "Luramas/framework/*.cpp" 
    "Luramas/framework/*.h" 
    "Luramas/framework/*.c")
file(GLOB_RECURSE LUA_FILES
    "Luramas/3rdparty/lua/*.c" 
    "Luramas/3rdparty/lua/*.h")
file(GLOB_RECURSE LUAU_FILES
    "Luramas/3rdparty/luau/*.hpp" 
    "Luramas/3rdparty/luau/*.cpp" 
    "Luramas/3rdparty/luau/*.h" 
    "Luramas/3rdparty/luau/*.c")
file(GLOB_RECURSE SHARED_FILES
    "Luramas/shared/*.hpp" 
    "Luramas/shared/*.cpp" 
    "Luramas/shared/*.h" 
    "Luramas/shared/*.c")

# Silence warnings coming from 3rd party
set_source_files_properties(
        ${LUA_FILES} ${LUAU_FILES}
        PROPERTIES COMPILE_OPTIONS "${THIRDPARTY_NO_WARN}")

add_executable(Luramas ${SOURCE_FILES} ${LUA_FILES} ${LUAU_FILES} ${SHARED_FILES} ${EXAMPLE_FILES})

target_compile_definitions(Luramas PRIVATE
        $<$<BOOL:${LURAMAS_TARGET_X86}>:LURAMAS_TARGET_X86>
        $<$<BOOL:${LURAMAS_TARGET_LUA}>:LURAMAS_TARGET_LUA>
        $<$<BOOL:${LURAMAS_TARGET_LUAU}>:LURAMAS_TARGET_LUAU>
        $<$<BOOL:${LURAMAS_TARGET_VERSION_536}>:LURAMAS_TARGET_VERSION_536>
        $<$<BOOL:${LURAMAS_TARGET_VERSION_6}>:LURAMAS_TARGET_VERSION_6>

        $<$<BOOL:${LURAMAS_ECC}>:LURAMAS_ECC>
        $<$<BOOL:${LURAMAS_PROFILE}>:LURAMAS_PROFILE>

        $<$<BOOL:${LURAMAS_DEBUG_SSA_STEPS}>:LURAMAS_DEBUG_SSA_STEPS>
        $<$<BOOL:${LURAMAS_DEBUG_NO_DUMP}>:LURAMAS_DEBUG_NO_DUMP>
        $<$<BOOL:${LURAMAS_DEBUG_ERROR_CLIPBOARD}>:LURAMAS_DEBUG_ERROR_CLIPBOARD>
        $<$<BOOL:${LURAMAS_TARGET_BIGDATA}>:LURAMAS_TARGET_BIGDATA>

        $<$<CONFIG:Debug>:DEBUG>
        _CONSOLE
        _CRT_SECURE_NO_WARNINGS
        HUNSPELL_STATIC
)

target_include_directories(Luramas PRIVATE
    Luramas/3rdparty/lua
    Luramas/3rdparty/luau
    Luramas/shared
)

# Conan
find_package(mpfr)
find_package(capstone)
find_package(Boost)
find_package(RapidJSON)
find_package(hunspell)
find_package(frozen)
find_package(gmp)
find_package(CLI11)

target_link_libraries(Luramas
                      mpfr::mpfr
                      capstone::capstone
                      boost::boost
                      rapidjson
                      hunspell::hunspell
                      frozen::frozen
                      gmp::gmp
                      CLI11::CLI11)