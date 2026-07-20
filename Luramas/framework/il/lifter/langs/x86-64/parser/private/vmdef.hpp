#pragma once
#ifdef LURAMAS_TARGET_X86
#include "../../../../builder/builder.hpp"
#include "../../../../builder/keywords.hpp"
#include "../parser.hpp"
#include "flags.hpp"

#define kif(def_cmp) builder_kif(registrar.build, def_cmp)

#define kelseif(def_cmp) builder_kelseif(registrar.build, def_cmp)

#define kelse builder_kelse(registrar.build)
#define kend builder_kend(registrar.build)

#define kwhile(def_cmp) builder_kwhile(registrar.build, def_cmp)

#define kwhile_end builder_kwhile_end(registrar.build)

#define klura_call(func, args, ...) builder_klura_call(registrar.build, func, args __VA_OPT__(, ) __VA_ARGS__)

#define klura_vtemp builder_klura_vtemp(registrar.build)
#define klura_tint(n) builder_klura_tint(registrar.build, n)
#define klura_tglobal(str) builder_klura_tglobal(registrar.build, str)
#define klura_internal_set(g_str, v) builder_klura_internal_set(registrar.build, g_str, v)

namespace vm {

      using registrar = luramas::il::lifter::builder::registrar<x86_insn, x86_reg, xeflags, luramas::il::X86::lifter::hardware_constants>;
}

inline luramas::il::lifter::builder::build::expr klura_internal_read(const vm::registrar &registrar, const char *const g_str) {
      const auto temp = klura_vtemp;
      registrar.build->load_internal_global(g_str, temp);
      return temp;
}
#endif