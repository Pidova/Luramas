#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::lua::table {

      /* Emits index */
      inline void emit_index(std::string &buffer, std::string &table, std::string &index, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += table;
            buffer += format->spacing.format_index_ref(lua_langkeyword_index_open, index, lua_langkeyword_index_close);
            return;
      }

      /* Emits generic index */
      inline void emit_index_generic(std::string &buffer, std::string &table, std::string &index, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += table;
            buffer += lua_langkeyword_index_generic;
            buffer += index;
            return;
      }

      /* Emits table */
      inline void emit_table(std::string &buffer, std::vector<std::pair<std::string /* Index */, std::string /* Value */>> &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_table_start(lua_langkeyword_table_start);

            const auto count = data.size();
            for (auto i = 0ull; i < count; ++i) {

                  if (!data[i].first.empty()) {
                        buffer += format->spacing.format_table_index(lua_langkeyword_table_index_start, data[i].first, lua_langkeyword_table_index_end, lua_langkeyword_table_index_assignment);
                  }
                  buffer += data[i].second;

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        buffer += format->spacing.format_parameter_delimiter(lua_langkeyword_table_delimiter);
                  }
            }

            buffer += format->spacing.format_table_end(lua_langkeyword_table_end);
            return;
      }

} // namespace luramas::ir::code::emitter::lua::table