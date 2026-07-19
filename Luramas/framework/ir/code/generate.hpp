#pragma once
#include "../ir.hpp"
#include "generation/common/generate/generate.hpp"
#include "generation/common/generation_syntax.hpp"

namespace luramas::ir::code::generation {

      std::string generate(const ir::code::emitter::syntax::emitter_syntax syn, const ir_stat::space &code, const std::shared_ptr<ir::data::format::format> &format, const bool use_annotations = true);
} // namespace luramas::ir::code::generation