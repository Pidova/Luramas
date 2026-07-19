#pragma once
#include "builder.hpp"

#define builder_kif(jbuild, def_cmp) \
      (jbuild)->cmp((def_cmp));      \
      (jbuild)->make_scope<luramas::il::arch::data::bin_kinds::et_>(LURAMAS_IR_DEFAULT_SEGREGATION_ID);

#define builder_kelseif(jbuild, def_cmp) \
      (jbuild)->make_else();             \
      (jbuild)->cmp((def_cmp));          \
      (jbuild)->make_scope<luramas::il::arch::data::bin_kinds::et_>(LURAMAS_IR_DEFAULT_SEGREGATION_ID);

#define builder_kelse(jbuild) (jbuild)->make_else()
#define builder_kend(jbuild) (jbuild)->close_scope()

#define builder_kwhile(jbuild, def_cmp)            \
      (jbuild)->make_label(LURAMAS_DEFAULT_LABEL); \
      (jbuild)->cmp((def_cmp));                    \
      (jbuild)->make_scope<luramas::il::arch::data::bin_kinds::et_>(LURAMAS_IR_DEFAULT_SEGREGATION_ID);

#define builder_kwhile_end(jbuild)                \
      (jbuild)->make_goto(LURAMAS_DEFAULT_LABEL); \
      (jbuild)->close_scope();

#define builder_klura_call(jbuild, func, args, ...) \
      (jbuild)->make_lura_built_in(func, args __VA_OPT__(, ) __VA_ARGS__)

#define builder_klura_vtemp(jbuild) (jbuild)->make_temp()
#define builder_klura_tint(jbuild, n) luramas::il::lifter::builder::build::expr((jbuild), n)
#define builder_klura_tglobal(jbuild, str) luramas::il::lifter::builder::build::expr((jbuild), str)
#define builder_klura_internal_set(jbuild, g_str, v) (jbuild)->set_internal_global(g_str, v)
