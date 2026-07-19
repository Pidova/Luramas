#pragma once
#include "../ir.hpp"
#include "data.hpp"
#include "ir_kinds.hpp"
#include <boost/container/flat_map.hpp>
#include <variant>

namespace luramas::ir::execution {

      namespace types {

            struct memory {

                  luramas_address memory_base = 0u;
                  std::vector<std::int8_t> memory;

                  inline constexpr luramas_address allocate(const std::size_t size) {
                        luramas_address addr = this->memory_base + this->memory.size();
                        this->memory.resize(this->memory.size() + size, 0u);
                        return addr;
                  }
            };

            struct object {

                  struct table {

                        table() = default;
                        explicit table(const luramas_count start)
                            : idx_start(start) {
                        }

                        /* Append a value to table, returns key */
                        std::shared_ptr<object> append(const std::shared_ptr<object> &value);

                        /* Add key with value to table, returns key */
                        std::shared_ptr<object> add(const std::shared_ptr<object> &key, const std::shared_ptr<object> &value);
                        std::shared_ptr<object> add(const luramas_int &key, const std::shared_ptr<object> &value);

                        /* Removes key returns if it has been removed */
                        bool remove(const std::shared_ptr<object> &key);
                        bool remove(const luramas_int &key);

                        boost::container::flat_map<std::shared_ptr<object>, std::shared_ptr<object>> map;

                      private:
                        luramas_count idx_start = 0u;
                  };

                  /* Emitters */
                  void emit();
                  void emit(const bool b);
                  void emit(const luramas_int i);
                  void emit(const std::string &s);
                  void emit(const table &t);
                  void emit(const std::vector<std::shared_ptr<object>> &v);

                  /* Operators */
                  bool operator<(const luramas_int &i) const;
                  bool operator>(const luramas_int &i) const;
                  bool operator==(const luramas_int &i) const;
                  bool operator!=(const luramas_int &i) const;
                  bool operator<=(const luramas_int &i) const;
                  bool operator>=(const luramas_int &i) const;
                  bool operator==(const bool b) const;
                  bool operator!=(const bool b) const;
                  bool operator==(const std::string &str) const;
                  bool operator!=(const std::string &str) const;

                  /* Cast */
                  explicit operator bool() const;

                  /* Misc */
                  void clear();

                  tkind k = tkind::nothing; /* Kind */
                  std::variant<
                      std::monostate,
                      bool,                                 /* Boolean */
                      luramas_int,                          /* Integral */
                      std::string,                          /* String value, Kvalue, etc */
                      table,                                /* Map table */
                      std::vector<std::shared_ptr<object>>> /* Variadic, etc */
                      v;
            };

            class stack {

                  void write(const std::size_t loc) {
                        if (loc > this->capacity) {
                              luramas::error::error("Out of bounds for stack");
                        }
                        return;
                  }

                private:
                  std::size_t capacity = 0u;
            };

      } // namespace types

      struct execution_flags {

            luramas_flag flocals_only = false; /* Evaluate only locals */
      };

      class environment {

          public:
            environment_flags flags;

            std::vector<luramas_address> call_stack;
            std::vector<luramas_blockrange> breakables;
            types::memory memory;
            types::stack stack;
            boost::unordered_flat_map<luramas_register, types::object> registers;
            boost::unordered_flat_map<std::string, types::object> globals;
      };
      using c_function = void (*)(const environment &env, const std::vector<std::shared_ptr<types::object>> &args, const std::vector<std::shared_ptr<types::object>> &result);
} // namespace luramas::ir::execution