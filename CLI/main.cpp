/* Luau */
#ifdef LURAMAS_TARGET_LUAU

#ifdef LURAMAS_TARGET_VERSION_6
#include "luau/V6/example.hpp"
#endif

#endif

/* Lua */
#ifdef LURAMAS_TARGET_LUA

#ifdef LURAMAS_TARGET_VERSION_53
#include "lua/Lua_5.3/example.hpp"
#endif

#endif

/* X86 */
#ifdef LURAMAS_TARGET_X86
#include "x86-64/example.hpp"
#endif
#include "../../Luramas/framework/target_strs.hpp"

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

struct test_script {
      std::string directory = ""; /* Reltive directory in test */
      std::string name = "";      /* File name WITHOUT extension */
      std::string code = "";      /* Read code */
};

/* Writes string content to <test_dir>/<scripts_dir>/<output_folder>/<script.name><extension> */
bool write_output(const std::string &test_dir, const test_script &script, const std::string &content, const char *const extension) {

      const std::filesystem::path rel_path(script.directory);

      auto out_path = std::filesystem::path(test_dir) / rel_path.parent_path() / luramas::tests::output_folder / script.name;
      out_path.replace_extension(extension);

      try {

            std::filesystem::create_directories(out_path.parent_path());

            std::ofstream file(out_path, std::ios::out | std::ios::trunc);
            if (!file.is_open()) {
                  return false;
            }

            file << content;
            return true;
      } catch (const std::exception &e) {
            std::cerr << "Failed to write file: " << e.what() << "\n";
            return false;
      }
}

/* Get script contents and location given dir */
std::vector<test_script> get_scripts(const char *const test_dir, const char *const scripts_dir) {

      std::vector<test_script> result;

      const std::filesystem::path test_path(test_dir);
      const auto base_path = test_path / scripts_dir;

      if (!std::filesystem::exists(base_path) || !std::filesystem::is_directory(base_path)) {
            return result;
      }

      std::filesystem::recursive_directory_iterator iter(base_path, std::filesystem::directory_options::skip_permission_denied);

      for (auto it = std::filesystem::begin(iter); it != std::filesystem::end(iter); ++it) {

            const auto &entry = *it;
            const auto &path = entry.path();

            /* Skip output folder branch entirely */
            if (entry.is_directory() && path.filename() == luramas::tests::output_folder) {
                  it.disable_recursion_pending();
                  continue;
            }

            if (entry.is_regular_file()) {

                  const auto full_file_path = path.string();
                  const auto rel_stem = (std::filesystem::relative(path, base_path).parent_path() / path.stem()).generic_string();
                  if (auto content = read_file(full_file_path); content.has_value()) {
                        result.push_back({std::filesystem::relative(path, test_path).generic_string(), rel_stem, std::move(*content)});
                  }
            }
      }
      return result;
}

std::optional<std::string> decompile(const std::string &target, const std::string &code, std::shared_ptr<luramas::ir::data::format::format> &format, const bool is_bytecode) {

#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)
      if (target == luramas::supported_targets_str::LUAU_V6) {
#include "luau/V6/example.hpp"
            return luramas::decompile_luau_v6(code, format, is_bytecode);
      }
#endif

#ifdef LURAMAS_TARGET_X86
      if (target == luramas::supported_targets_str::X86) {
#include "x86-64/example.hpp"
            return luramas::decompile_x86(code, format, is_bytecode);
      }
#endif

#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)
      if (target == luramas::supported_targets_str::LUA_V53) {
#include "lua/Lua_5.3/example.hpp"
            return luramas::decompile_lua_53(code, format, is_bytecode);
      }
#endif
      return "";
}

/* Read, decompile, and output tests */
void decompile_tests(const std::string &test_dir, std::shared_ptr<luramas::ir::data::format::format> &format, const char *const scripts_directory, const char *const supported_targets_str, const char *const extension) {

      for (const auto &i : get_scripts(test_dir.c_str(), scripts_directory)) {
            if (const auto dec = decompile(supported_targets_str, i.code, format, false); dec) {
                  write_output(test_dir, i, *dec, extension);
            }
      }
      return;
}

int main(int argc, char **argv) {

      CLI::App app{"Luramas"};                                             /* App name */
      auto format = std::make_shared<luramas::ir::data::format::format>(); /* Syntax format */

      /* CLI options */
      std::string input("");                         /* Input directory */
      std::string target("x86");                     /* Input target */
      std::string test_dir("C:/repo/Luramas/tests"); /* Directory of repo/tests */
      luramas_flag is_bytecode = false;              /* Is input bytecode (Only for input) */
      luramas_flag all_tests = false;                /* Run all tests */

     // decompile_tests(test_dir, format, luramas::tests::scripts_directory::LUA_V53, luramas::supported_targets_str::X86, luramas::tests::scripts_directory::LUA_EXTENSION);

      /* Options */
      app.set_help_flag("-h,--help,?", "Print help message and exit");
      app.add_option("-i,--input", input, "Input bytecode/source file")->required();
      app.add_option("-t,--target", target, "Target architecture / VM version")->default_val("x86")->transform(CLI::IsMember({"luau-v6", "x86", "lua-536"}));
      app.add_flag("-b,--bytecode", is_bytecode, "Treat the input file as bytecode (defaults to source code)");
      const auto test_opt = app.add_option("-test", test_dir, "Run tests from root test directory")->check(CLI::ExistingDirectory);
      app.add_flag("-all-tests", all_tests, "Run test suite across ALL supported target versions");
      CLI11_PARSE(app, argc, argv);

      if (test_opt) {

#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)
            decompile_tests(test_dir, format, luramas::tests::scripts_directory::LUA_V53, luramas::supported_targets_str::LUA_V53, luramas::tests::scripts_directory::LUA_EXTENSION);
#endif
#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)
            decompile_tests(test_dir, format, luramas::tests::scripts_directory::LUAU_V6, luramas::supported_targets_str::LUAU_V6, luramas::tests::scripts_directory::LUAU_EXTENSION);
#endif
      }
      if (!input.empty()) {

            const auto code = read_file(input);

            /* Could not open file */
            if (!code) {
                  std::cerr << "Failed to read input file: " << input << std::endl;
                  return 1;
            }

            std::cout << "Decomp " << *decompile(target, "", format, is_bytecode);
      }
      return 0;
}