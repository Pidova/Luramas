#pragma once
#include "../ir.hpp"

namespace luramas::ir::library {

      enum class kind : std::uint8_t {
            nothing,
            library,
            exprs,
            stats
      };
      class library {

          public:
            struct members {

                  kind k = kind::nothing;

                  std::optional<ir_stat::space> stats;
                  std::optional<ir_stat::ir_expr::space> exprs;
                  std::optional<boost::unordered_flat_map<std::string, std::shared_ptr<members>>> lib;

                  void emit(const ir_stat::space &space);
                  void emit(const ir_stat::ir_expr::space &space);
                  void emit(const std::string &key, const std::shared_ptr<members> &lib);
                  void emit(const std::string &key, const ir_stat::space &space);
                  void emit(const std::string &key, const ir_stat::ir_expr::space &space);

                  std::string str(const std::string &indent = "", bool is_last = true) const;
                  void clear();

                private:
                  void init_lib();
                  void init_stats();
                  void init_exprs();
            };

            library() = default;
            library(const std::shared_ptr<members> &m)
                : entry(m) {
                  };

            std::shared_ptr<members> entry = nullptr;
            void clear();
      };

      namespace generate::members {

            std::shared_ptr<library::members> make(const ir_stat::space &space);
            std::shared_ptr<library::members> make(const ir_stat::ir_expr::space &space);
            std::shared_ptr<library::members> make(const std::string &key, const std::shared_ptr<library::members> &lib);
            std::shared_ptr<library::members> make(const std::string &key, const ir_stat::space &space);
            std::shared_ptr<library::members> make(const std::string &key, const ir_stat::ir_expr::space &space);

      } // namespace generate::members
} // namespace luramas::ir::library