/* Luau */
#ifdef LURAMAS_TARGET_LUAU

#ifdef LURAMAS_TARGET_VERSION_6
#include "luau/V6/example.hpp"
#endif

#endif

/* Lua */
#ifdef LURAMAS_TARGET_LUA

#ifdef LURAMAS_TARGET_VERSION_536
#include "lua/Lua_5.3.6/example.hpp"
#endif

#endif

/* X86 */
#ifdef LURAMAS_TARGET_X86
#include "x86-64/example.hpp"
#endif

#include <CLI\CLI.hpp>

/* Read file to string data given path */
std::optional<std::string> read_file(const std::string &path) {

      std::ifstream file(path);
      if (!file.is_open()) {
            return std::nullopt;
      }
      std::stringstream buffer;
      buffer << file.rdbuf();
      return buffer.str();
}

std::optional<std::string> decompile(const std::string &target, const std::string &code, std::shared_ptr<luramas::ir::data::format::format> &format, const bool is_bytecode) {

#ifdef LURAMAS_TARGET_LUAU
      if (target == "luau-v6") {

#ifdef LURAMAS_TARGET_VERSION_6
#include "luau/V6/example.hpp"
            return luramas::decompile_luau_v6(code, format, is_bytecode);
#endif
      }
#endif

#ifdef LURAMAS_TARGET_X86
      if (target == "x86") {
#include "x86-64/example.hpp"
            return luramas::decompile_x86(code, format, is_bytecode);
      }
#endif
#ifdef LURAMAS_TARGET_LUA
      if (target == "lua-536") {

#ifdef LURAMAS_TARGET_VERSION_536
#include "lua/Lua_5.3.6/example.hpp"
            return luramas::decompile_lua_536(code, format, is_bytecode);
#endif
      }
#endif
      return "";
}

int main(int argc, char **argv) {

      CLI::App app{"Luramas"};

      /* CLI options */
      std::string input("");
      std::string target("x86");
      luramas_flag is_bytecode = false;

      //app.set_help_flag("-h,--help,?", "Print help message and exit");
      //app.add_option("-i,--input", input, "Input bytecode/source file")->required();
      //app.add_option("-t,--target", target, "Target architecture / VM version")->default_val("x86")->transform(CLI::IsMember({"luau-v6", "x86", "lua-536"}));
      //app.add_flag("-b,--bytecode", is_bytecode, "Treat the input file as bytecode (defaults to source code)");
      //CLI11_PARSE(app, argc, argv);
      //
      //const auto code = read_file(input);
      //
      ///* Could not open file */
      //if (!code) {
      //      std::cerr << "Failed to read input file: " << input << std::endl;
      //      return 1;
      //}

      auto format = std::make_shared<luramas::ir::data::format::format>();
      std::cout << "Decomp " << *decompile(target, "", format, is_bytecode);
      return 0;
}