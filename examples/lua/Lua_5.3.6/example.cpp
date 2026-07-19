#if defined(LURAMAS_TARGET_LUA) && defined(LURAMAS_TARGET_VERSION_536)
#include "example.hpp"
#include "../../Luramas/framework/il/lifter/langs/lua/Lua_5.3.6/include.hpp"

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

std::optional<std::string> luramas::decompile_lua_536(const std::string &code, std::shared_ptr<luramas::ir::data::format::format> &format, const bool bytecode) {

      bool error = false;               /* Error buffer */
      lua_State *original_ls = nullptr; /* Buffer lua state */

      auto proto = compile_script(code, error, original_ls, bytecode); /* Compile code. */

      /* Error in code compilation. */
      if (error || !proto) {
            lua_close(original_ls);
            return std::nullopt;
      }

      auto il = luramas::il::lifter::lift_proto(proto);  /* Generate IL */
      auto closure = luramas::closures::gen_closure(il); /* Generate closure info */
      const auto lifted = luramas::ir::lift(closure);    /* Lift to IR */
      return luramas::ir::code::generation::generate(luramas::ir::code::emitter::syntax::emitter_syntax::lua, lifted, format);
}

#endif