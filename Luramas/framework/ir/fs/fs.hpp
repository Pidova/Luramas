#pragma once
#include "../ir.hpp"
#include "../library/library.hpp"

namespace luramas::ir::fs {

      void save(const ir_stat::space &stats, const std::string &directory, const std::string &name);
      void save(const ir_stat::space &stats, std::ostream &os, const std::shared_ptr<std::vector<std::pair<std::string, std::vector<luramas_address>>>> &annotations = nullptr);

      ir_stat::space load(const std::string &directory, const std::string &name);
      ir_stat::space load(std::istream &is);
} // namespace luramas::ir::fs