#pragma once
#include <cstdint>
#include <iostream>

namespace luramas::ir::code::emitter::syntax {

      /* Syntax of code for IL to emit. */
      enum class emitter_syntax : std::uint8_t {
            nothing, /* Nothing */
            python,  /* Python-3.11.0 */
            rust,    /* Rust-1.68.0 */
            c,       /* C-23 */
            cpp,     /* Cpp-23 */
            java,    /* Java-20 */
            lua,     /* Lua-5.4 */
            luau,    /* Lua-V6 */
            html,    /* HTML */
            css      /* CSS */
      };

      /* Syntax emitter enum to string. */
      inline const char *const emitter_syntax_str(const luramas::ir::code::emitter::syntax::emitter_syntax syn) {

            switch (syn) {
                  case luramas::ir::code::emitter::syntax::emitter_syntax::c: {
                        return "C-23";
                  }
                  case luramas::ir::code::emitter::syntax::emitter_syntax::cpp: {
                        return "Cpp-23";
                  }
                  case luramas::ir::code::emitter::syntax::emitter_syntax::java: {
                        return "Java-20";
                  }
                  case luramas::ir::code::emitter::syntax::emitter_syntax::lua: {
                        return "Lua-5.4";
                  }
                  case luramas::ir::code::emitter::syntax::emitter_syntax::luau: {
                        return "LuaU";
                  }
                  case luramas::ir::code::emitter::syntax::emitter_syntax::python: {
                        return "Python-3.11.0";
                  }
                  case luramas::ir::code::emitter::syntax::emitter_syntax::rust: {
                        return "Rust-1.68.0";
                  }
                  case luramas::ir::code::emitter::syntax::emitter_syntax::html: {
                        return "HTML";
                  }
                  case luramas::ir::code::emitter::syntax::emitter_syntax::css: {
                        return "CSS";
                  }
                  default: {
                        luramas::error::error("Unkown emittion syntax.");
                  }
            }
      }

} // namespace luramas::ir::code::emitter::syntax