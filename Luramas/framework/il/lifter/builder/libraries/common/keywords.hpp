#pragma once
#include "../../keywords.hpp"

#define kif(def_cmp) builder_kif(def.b, def_cmp)

#define kelseif(def_cmp) builder_kelseif(def.b, def_cmp)

#define kelse builder_kelse(def.b)
#define kend builder_kend(def.b)

#define kwhile(def_cmp) builder_kwhile(def.b, def_cmp)

#define kwhile_end builder_kwhile_end(def.b)

#define klura_call(func, args, ...) builder_klura_call(def.b, func, args __VA_OPT__(, ) __VA_ARGS__)

#define klura_vtemp builder_klura_vtemp(def.b)
#define klura_tint(n) builder_klura_tint(def.b, n)
#define klura_tglobal(str) builder_klura_tglobal(def.b, str)
#define klura_internal_set(g_str, v) builder_klura_internal_set(def.b, g_str, v)