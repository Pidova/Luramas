#pragma once
#include "../generate.hpp"
#include "../supported.hpp"

namespace luramas::ir::code::emitter::common::table {

      /* Emits index */
      inline void emit_index(const syntax::emitter_syntax syn, std::string &buffer, std::string &table, std::string &index, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::table::emit_index(buffer, table, index, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::table::emit_index(buffer, table, index, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Table index");
                  }
            }
            return;
      }

      /* Emits generic index */
      inline void emit_index_generic(const syntax::emitter_syntax syn, std::string &buffer, std::string &table, std::string &index, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::table::emit_index_generic(buffer, table, index, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::table::emit_index_generic(buffer, table, index, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Table generic index");
                  }
            }
            return;
      }

      /* Emits table */
      inline void emit_table(const syntax::emitter_syntax syn, std::string &buffer, std::intptr_t indent, std::vector<std::pair<std::string, std::string>> &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            switch (syn) {
                  case syntax::emitter_syntax::lua: {
                        lua::table::emit_table(buffer, data, format);
                        break;
                  }
                  case syntax::emitter_syntax::luau: {
                        luau::table::emit_table(buffer, indent, data, format);
                        break;
                  }
                  default: {
                        luramas::error::error_expr_syn_emit("Table");
                  }
            }
            return;
      }

} // namespace luramas::ir::code::emitter::common::table