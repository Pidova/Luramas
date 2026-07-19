#pragma once
#include "../emit.hpp"

namespace luramas::ir::code::emitter::luau::table {

      static constexpr std::array<const char *const, 22u> black_listed_idxs = {
          "and",
          "break",
          "do",
          "else",
          "elseif",
          "end",
          "false",
          "for",
          "function",
          "goto",
          "if",
          "in",
          "local",
          "nil",
          "not",
          "or",
          "repeat",
          "return",
          "then",
          "true",
          "until",
          "while"};

      /* Emits index */
      inline void emit_index(std::string &buffer, const std::string &table, const std::string &index, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += table;
            buffer += format->spacing.format_index_ref(luau_langkeyword_index_open, index, luau_langkeyword_index_close);
            return;
      }

      /* Emits generic index */
      inline void emit_index_generic(std::string &buffer, std::string &table, std::string &index, const std::shared_ptr<luramas::ir::data::format::format> &format) {
            buffer += table;
            buffer += luau_langkeyword_index_generic;
            buffer += index;
            return;
      }

      /* Emits table */
      inline void emit_table(std::string &buffer, const std::intptr_t indent, std::vector<std::pair<std::string, std::string>> &data, const std::shared_ptr<luramas::ir::data::format::format> &format) {

            buffer += format->spacing.format_table_start(luau_langkeyword_table_start);

            std::string indenting("");
            for (auto o = 0u; o < indent; ++o) {
                  indenting.append(format->indent.indent_space);
            }
            const auto count = data.size();
            for (auto i = 0u; i < count; ++i) {

                  /* Indenting */
                  if (indent) {
                        line::emit_linebreak(buffer, 1u, format);
                  }

                  /* Content */
                  buffer += indenting;
                  if (!data[i].first.empty()) {

                        auto cleaned = data[i].first;
                        luramas_str_sanitize(cleaned);
                        if (luramas_str_valid_index(cleaned) && !std::any_of(black_listed_idxs.begin(), black_listed_idxs.end(), [&](const auto &i) { return cleaned == i; })) {
                              buffer += format->spacing.format_table_index(luau_langkeyword_empty, cleaned, luau_langkeyword_empty, luau_langkeyword_table_index_assignment);
                        } else {
                              buffer += format->spacing.format_table_index(luau_langkeyword_table_index_start, data[i].first, luau_langkeyword_table_index_end, luau_langkeyword_table_index_assignment);
                        }
                  }
                  buffer += data[i].second;

                  /* Add delimiter */
                  if ((i + 1u) != count) {
                        buffer += format->spacing.format_parameter_delimiter(luau_langkeyword_table_delimiter);
                  }
            }

            buffer += format->spacing.format_table_end(luau_langkeyword_table_end);
            return;
      }

} // namespace luramas::ir::code::emitter::luau::table