#if defined(LURAMAS_TARGET_LUAU) && defined(LURAMAS_TARGET_VERSION_6)
#include "example.hpp"
#include "../../Luramas/framework/il/lifter/langs/luau/V6/include.hpp"

/* Load bytecode to lua Proto */
static Proto *load_bytecode(const std::vector<std::uint8_t> &data, lua_State *ls) {

      if (luau_load(ls, "Luramas", (char *)data.data(), data.size(), 0)) {

            std::size_t len;
            const char *msg = lua_tolstring(ls, -1, &len);
            std::string error(msg, len);
            lua_pop(ls, 1);
            return NULL;
      }
      return gco2cl((ls->top - 1)->value.gc)->l.p;
}

/* Compile script data or load bytecode to lua state */
static Proto *compile_script(const std::string &code, bool &error, lua_State *&buffer, const bool bytecode) {

      buffer = luaL_newstate();
      if (bytecode) {
            return load_bytecode(std::vector<std::uint8_t>(code.begin(), code.end()), buffer);
      }
      std::size_t size = 0u; /* Size buffer of compiled code. */
      auto ops = std::make_shared<lua_CompileOptions>();
      ops->optimizationLevel = 0;
      const auto compiled = luau_compile(code.c_str(), std::strlen(code.c_str()), ops.get(), &size);
      return (!size) ? NULL : load_bytecode(std::vector<std::uint8_t>(compiled, compiled + size), buffer);
}

std::optional<std::string> luramas::decompile_luau_v6(const std::string &code, std::shared_ptr<luramas::ir::data::format::format> &format, const bool bytecode) {

      bool error = false;               /* Error buffer */
      lua_State *original_ls = nullptr; /* Buffer lua state */

      auto proto = compile_script(code, error, original_ls, bytecode); /* Compile code. */

      /* Error in code compilation. */
      if (error || !proto) {
            lua_close(original_ls);
            return std::nullopt;
      }

      auto il = luramas::il::lifter::lift(proto);        /* Generate IL */
      auto closure = luramas::closures::gen_closure(il); /* Generate closure info */
      const auto lifted = luramas::ir::lift(closure);    /* Lift to IR */
      return luramas::ir::code::generation::generate(luramas::ir::code::emitter::syntax::emitter_syntax::luau, lifted, format);
}
#endif