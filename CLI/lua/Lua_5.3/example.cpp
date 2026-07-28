#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_53)
#include "example.hpp"
#include "../../Luramas/framework/il/lifter/langs/lua/Lua_5.3/include.hpp"

/* Compiles script/bytecode and returns proto. */
static Proto *compile_script(const std::string &code, bool &error, lua_State *&buffer, const bool bytecode) {

      error = false;
      buffer = luaL_newstate(); /* New lua state */

      if (!buffer) {
            error = true;
            return nullptr;
      }
      if (bytecode ? luaL_loadbuffer(buffer, code.data(), code.size(), "Luramas") : luaL_loadstring(buffer, code.c_str()) != LUA_OK) {
            error = true;
            return nullptr;
      }
      return gco2cl((buffer->top - 1)->value_.gc)->l.p; /* Code proto */
}
static constexpr auto LUA_ENV_UPV_IDX = 0u;    /* Lua _ENV upvalue index */
static constexpr auto LUA_RESERVED_REG = 255u; /* All regs are below this number */

static constexpr std::array keywords = {
    "and", "break", "do", "else", "elseif", "end", "false", "for", "function", "goto", "if", "in", "local", "nil", "not", "or", "repeat", "return", "then", "true", "until", "while"}; /* Lua reserved keywords */

/* String can be converted to a lua var? */
bool is_lua_identifier(const std::string &s) {

      if (s.empty() || !(std::isalpha(static_cast<std::uint8_t>(s[0u])) || s[0u] == '_')) {
            return false;
      }
      for (const auto c : s.substr(1u)) {
            if (!(std::isalnum(c) || c == '_')) {
                  return false;
            }
      }
      return std::find(keywords.begin(), keywords.end(), s) == keywords.end();
}

std::optional<std::string> luramas::decompile_lua_53(const std::string &code, std::shared_ptr<luramas::ir::data::format::format> &format, const bool bytecode) {

      bool error = false;               /* Error buffer */
      lua_State *original_ls = nullptr; /* Buffer lua state */

      auto proto = compile_script(code, error, original_ls, bytecode); /* Compile code. */

      /* Error in code compilation. */
      if (error || !proto) {
            lua_close(original_ls);
            return std::nullopt;
      }

      auto il = luramas::il::lifter::lift_proto(proto, LUA_RESERVED_REG); /* Generate IL */
      auto closure = luramas::closures::gen_closure(il);                  /* Generate closure info */

      luramas::ir::passes::environment_flags f; /* Env flags */
      f.fallow_ternaries = false;               /* Disable ternaries */
      f.options.oresolve_global_qualifier = [](const std::shared_ptr<luramas::ir::ir_stat::ir_expr> &e) {
            auto s = e->v;

            /* Remove " and ' */
            if (!s.empty() && s.front() == '"') {
                  s.erase(s.begin());
                  if (!s.empty() && s.back() == '"') {
                        s.pop_back();
                  }
            } else if (!s.empty() && s.front() == '\'') {
                  s.erase(s.begin());
                  if (!s.empty() && s.back() == '\'') {
                        s.pop_back();
                  }
            }
            return is_lua_identifier(s) ? std::optional<std::string>(s) : std::nullopt;
      };

      const auto env = luramas::ir::tools::exprs::generate::global("_ENV"); /* Env global */
      env->flags.fimplicit_table = true;                                    /* Set Env global as implicit table */
      f.input.iupvalues[LUA_ENV_UPV_IDX] = env;                             /* Add Lua default Env */
      const auto lifted = luramas::ir::lift(closure, f);                    /* Lift to IR */
      return luramas::ir::code::generation::generate(luramas::ir::code::emitter::syntax::emitter_syntax::lua, lifted, format);
}

#endif