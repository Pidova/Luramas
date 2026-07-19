#pragma once
#include "error.hpp"
#include <filesystem>
#include <fstream>
#include <istream>
#include <optional>
#include <ostream>

namespace luramas::fs {

      void serialize(std::ostream &os, const std::string &str);

      void load(std::istream &is, std::string &str);

      /* Sees if directory exists or can create it */
      std::optional<std::filesystem::path> get_directory(const std::string &directory);

      /* Generates file input */
      std::optional<std::ifstream> file_input(const std::filesystem::path &directory, const std::string &name, const char *const extension);
      std::optional<std::ifstream> file_input(const std::string &directory, const std::string &name, const char *const extension);

      /* Generates file output */
      std::optional<std::ofstream> file_output(const std::filesystem::path &directory, const std::string &name, const char *const extension);
      std::optional<std::ofstream> file_output(const std::string &directory, const std::string &name, const char *const extension);
} // namespace luramas::fs