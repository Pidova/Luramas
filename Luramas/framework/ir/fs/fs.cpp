#include "fs.hpp"
#include "../standardize/standardize.hpp"
#include <filesystem>
#include <fstream>

namespace luramas::ir::fs {

      void save(const ir_stat::space &stats, std::ostream &os, const std::shared_ptr<std::vector<std::pair<std::string, std::vector<luramas_address>>>> &annotations) {

            const auto size = stats.size();
            os.write(reinterpret_cast<const char *>(&size), sizeof(size));

            for (const auto &i : stats) {
                  i->serialize(os, annotations);
            }
            return;
      }

      void save(const ir_stat::space &stats, const std::string &directory, const std::string &name) {

            const auto dir_opt = luramas::fs::get_directory(directory);
            if (!dir_opt) {
                  return;
            }
            auto dir = std::move(*dir_opt);

            std::ostringstream oss;
            save(stats, oss);

            const auto &serialized_data = oss.str();

            auto ofs_opt = luramas::fs::file_output(dir, name, LURAMAS_IR_FS_EXTENSION);
            if (!ofs_opt) {
                  return;
            }
            auto ofs = std::move(*ofs_opt);

            ofs.write(serialized_data.data(), serialized_data.size());
            return;
      }

      ir_stat::space load(std::istream &is) {
            ir_stat::space result;

            std::size_t size = 0u;
            is.read(reinterpret_cast<char *>(&size), sizeof(size));
            result.reserve(size);

            for (auto i = 0u; i < size; ++i) {
                  auto stat = std::make_shared<ir_stat>();
                  stat->load(is);
                  result.emplace_back(stat);
            }
            return result;
      }

      ir_stat::space load(const std::string &directory, const std::string &name) {

            ir_stat::space result;

            auto input_opt = luramas::fs::file_input(directory, name, LURAMAS_IR_FS_EXTENSION);
            if (!input_opt) {
                  return result;
            }
            auto ifs = std::move(*input_opt);

            std::ostringstream oss;
            oss << ifs.rdbuf();

            std::istringstream iss(oss.str());
            return load(iss);
      }
} // namespace luramas::ir::fs