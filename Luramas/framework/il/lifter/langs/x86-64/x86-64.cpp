#ifdef LURAMAS_TARGET_X86
#include "x86-64.hpp"
#include "../../../il/architecture/emitter.hpp"
#include "../../../il/transformers/transformers.hpp"
#include "parser/parser.hpp"
#include <iostream>

/* Lifts current closure and child closures too IL disassembly. */
void luramas::il::X86::lifter::lift(const std::vector<std::pair<luramas::il::vinst, cs_insn>> &insts, std::shared_ptr<luramas::il::ilang> &buffer, const boost::unordered_flat_map<profile::module_id, profile::analyze::details> &details, const profile::externals::data<x86_reg> &external, const bit_mode mode) {

      luramas::il::helpers::low::disassembly_manager<cs_insn> dm(insts, buffer, details, x86_reg::X86_REG_ENDING + 1u, true);

      /* Parse instructions. */
      parser::parse_instruction(dm, external, mode);
      transformers::kinds(buffer);
      return;
}

#endif