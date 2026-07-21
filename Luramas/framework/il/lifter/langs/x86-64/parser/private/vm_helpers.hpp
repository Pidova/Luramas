#pragma once
#ifdef LURAMAS_TARGET_X86
#include "cpu_data.hpp"

inline luramas::il::lifter::builder::build::expr temp(const vm::registrar &registrar, const luramas::il::lifter::builder::build::expr &expr) {
      return registrar.build->make_temp(expr);
}
inline luramas::il::lifter::builder::build::expr stack(const vm::registrar &registrar, const std::intptr_t stack_id = LURAMAS_IR_DEFAULT_STACK_ID) {
      luramas::il::lifter::builder::build::expr result;
      result.emit_stack(registrar.build);
      return result;
}
inline luramas::il::lifter::builder::build::expr read(const vm::registrar &registrar, const luramas::il::lifter::builder::build::expr &expr, const luramas::types::underlying_type &read) {
      auto result = temp(registrar, luramas::il::lifter::builder::build::expr(registrar.build, 0u));
      luramas::il::lifter::builder::build::expr t;
      t.emit_mem(registrar.build, temp(registrar, expr).r);
      t.r.size = read;
      result = t;
      return result;
}

namespace build {

      inline void page_calls(const vm::registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands, const luramas::il::lifter::builder::build::expr &r) {

            const auto loc = operands.front();
            const auto details = registrar.get_details();
            const auto single = details.size() == 1u;

            for (const auto &inst : details) {

                  if (inst.k != luramas::profile::inst_kind::call_to) {
                        continue;
                  }
                  if (const auto externals = registrar.externals.find(inst.lid); externals != registrar.externals.end()) {

                        /* External */
                        if (const auto external = externals->second.find(inst.loc); external != externals->second.end()) {

                              const auto &data = external->second;
                              if (single) {
                                    registrar.build->external_page_call(data.name, registrar.get(data.args), registrar.get(data.results));
                              } else {
                                    registrar.build->non_direct_external_page_call(loc, data.loc, data.name, registrar.get(data.args), registrar.get(data.results));
                              }
                              continue;
                        }
                  }
                  if (!registrar.build->is_page_loc(inst.lid, inst.loc)) {
                        luramas::error::error("Call not page: " + std::to_string(inst.loc));
                  }
                  if (single) {
                        registrar.build->page_call(inst.lid, inst.loc, r, inst.bytes.size() + inst.pc);
                  } else {
                        registrar.build->non_direct_page_call(loc, inst.lid, inst.loc, r, inst.bytes.size() + inst.pc);
                  }
            }
            return;
      }

      inline void page_gotos(const vm::registrar &registrar, const std::vector<luramas::il::lifter::builder::build::expr> &operands) {

            const auto loc = operands.front();
            const auto details = registrar.get_details();
            const auto single = details.size() == 1u;

            for (const auto &inst : details) {

                  if (inst.k != luramas::profile::inst_kind::jump_to) {
                        continue;
                  }
                  if (const auto externals = registrar.externals.find(inst.lid); externals != registrar.externals.end()) {

                        /* External */
                        if (const auto external = externals->second.find(inst.loc); external != externals->second.end()) {

                              const auto &data = external->second;
                              if (single) {
                                    registrar.build->external_page_jmp(data.loc);
                              } else {
                                    registrar.build->non_direct_external_page_jmp(loc, data.loc);
                              }
                              continue;
                        }
                  }

                  if (!registrar.build->is_page_loc(inst.lid, inst.loc)) {

                        if (single) {
                              registrar.build->make_goto(inst.lid, inst.loc);
                        } else {
                              registrar.build->make_non_direct_goto(loc, inst.lid, inst.loc);
                        }
                  } else {

                        if (single) {
                              registrar.build->page_jump(inst.lid, inst.loc);
                        } else {
                              registrar.build->non_direct_page_jmp(loc, inst.lid, inst.loc);
                        }
                  }
            }
            return;
      }

      inline luramas::il::lifter::builder::build::expr reg_stack(const vm::registrar &registrar) {
            switch (registrar.hw_constants.suggested_bit_set) {
                  case 16u: {
                        return REG_SP;
                  }
                  case 64u: {
                        return REG_RSP;
                  }
                  default: {
                        return REG_ESP;
                  }
            }
      }

      inline void stack_push(const vm::registrar &registrar, const luramas::il::lifter::builder::build::expr &expr) {

            auto stack = reg_stack(registrar);
            stack -= (stack.bits() / 8u);
            stack.emit_mem(stack.b, stack.r);
            stack = expr;
            return;
      }
      inline void stack_pop(const vm::registrar &registrar, const luramas::il::lifter::builder::build::expr &expr) {

            const auto &stack = reg_stack(registrar);
            expr = stack.memread(stack.bits());
            stack += (stack.bits() / 8u);
            return;
      }
} // namespace build

#endif