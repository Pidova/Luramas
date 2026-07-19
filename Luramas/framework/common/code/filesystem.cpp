#include "../filesystem.hpp"
#include <filesystem>

namespace luramas::fs {

      void serialize(std::ostream &os, const std::string &str) {
            const auto len = static_cast<std::size_t>(str.size());
            os.write(reinterpret_cast<const char *>(&len), sizeof(len));
            os.write(str.data(), len);
            return;
      }

      void load(std::istream &is, std::string &str) {
            std::size_t len = 0u;
            is.read(reinterpret_cast<char *>(&len), sizeof(len));
            str.resize(len);
            is.read(str.data(), len);
            return;
      }

      std::optional<std::filesystem::path> get_directory(const std::string &directory) {
            const std::filesystem::path dir(directory);
            return (std::filesystem::exists(dir) || std::filesystem::create_directories(dir)) ? std::make_optional(dir) : std::nullopt;
      }

      std::optional<std::ifstream> file_input(const std::filesystem::path &directory, const std::string &name, const char *const extension) {
            const auto file_path = directory / (name + extension);
            std::ifstream ifs(file_path, std::ios::binary);
            return ifs ? std::make_optional<std::ifstream>(std::move(ifs)) : std::nullopt;
      }
      std::optional<std::ifstream> file_input(const std::string &directory, const std::string &name, const char *const extension) {
            return file_input(std::filesystem::path(directory), name, extension);
      }

      std::optional<std::ofstream> file_output(const std::filesystem::path &directory, const std::string &name, const char *const extension) {
            const auto file_path = directory / (name + extension);
            std::ofstream ofs(file_path, std::ios::binary);
            return ofs ? std::make_optional<std::ofstream>(std::move(ofs)) : std::nullopt;
      }
      std::optional<std::ofstream> file_output(const std::string &directory, const std::string &name, const char *const extension) {
            return file_output(std::filesystem::path(directory), name, extension);
      }

} // namespace luramas::fs