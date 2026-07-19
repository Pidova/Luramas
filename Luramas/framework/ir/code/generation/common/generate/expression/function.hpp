#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::function {

      /* Emits global function */
      inline void emit_global_function(const syntax::emitter_syntax syn, std::string &buffer, const std::string &name, const std::vector<std::string> &params, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            switch (syn) {
                  case syntax::emitter_syntax::luau: {
                        luau::function::emit_global_function(buffer, name, params, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Global function");
                  }
            }
            return;
      }
      /* Emits anonymous function end */
      inline void emit_global_function_end(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::luau: {
                        luau::function::emit_global_function_end(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Global function end");
                  }
            }
            return;
      }

      /* Emits local function */
      inline void emit_local_function(const syntax::emitter_syntax syn, std::string &buffer, const std::string &name, const std::vector<std::string> &params, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            switch (syn) {
                  case syntax::emitter_syntax::luau: {
                        luau::function::emit_local_function(buffer, name, params, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Local function");
                  }
            }
            return;
      }
      /* Emits anonymous function end */
      inline void emit_local_function_end(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::luau: {
                        luau::function::emit_local_function_end(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Local function end");
                  }
            }
            return;
      }

      /* Emits anonymous function */
      inline void emit_anonymous_function(const syntax::emitter_syntax syn, std::string &buffer, const std::vector<std::string> &params, const std::string &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            switch (syn) {
                  case syntax::emitter_syntax::luau: {
                        luau::function::emit_anonymous_function(buffer, params, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Anonymous function");
                  }
            }
            return;
      }
      /* Emits anonymous function end */
      inline void emit_anonymous_function_end(const syntax::emitter_syntax syn, std::string &buffer, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::luau: {
                        luau::function::emit_anonymous_function_end(buffer, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Anonymous function end");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::function