#pragma once
#include "../../passes.hpp"

namespace luramas::ir::pass::process {

      void values(const ir_stat::space &data, boost::unordered_flat_map<std::shared_ptr<ir_stat>, definitions::exprs> &buffer);
      void values(luramas::ir::passes::pass_manager &pm);
} // namespace luramas::ir::pass::process