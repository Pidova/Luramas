#pragma once
#include "../ir.hpp"

namespace luramas::ir::library {

      /* Type of library entry */
      enum class kind : std::uint8_t {
            nothing, /* No entry */
            library, /* Sub-library */
            exprs,   /* Expressions */
            stats    /* Statements */
      };

      /* Library manager for exprs, stats, and sub-libraries */
      class library {

          public:
            /* Library member */
            struct members {

                  kind k = kind::nothing; /* Member kind */

                  std::optional<ir_stat::space> stats;                                                 /* Statements */
                  std::optional<ir_stat::ir_expr::space> exprs;                                        /* Expressions */
                  std::optional<boost::unordered_flat_map<std::string, std::shared_ptr<members>>> lib; /* Member indexed by name -> other member pointer */

                  /* Emitters */
                  void emit(const ir_stat::space &space);
                  void emit(const ir_stat::ir_expr::space &space);
                  void emit(const std::string &key, const std::shared_ptr<members> &lib);
                  void emit(const std::string &key, const ir_stat::space &space);
                  void emit(const std::string &key, const ir_stat::ir_expr::space &space);

                  /* String representation */
                  std::string str(const std::string &indent = "", bool is_last = true) const;

                  /* Clear out member */
                  void clear();

                private:
                  void init_lib();   /* Init member as a sub-library reference */
                  void init_stats(); /* Init member as statements */
                  void init_exprs(); /* Init member as expressions */
            };

            library() = default;
            library(const std::shared_ptr<members> &m)
                : entry(m) {
                  };

            std::shared_ptr<members> entry = nullptr; /* Entry member */
            void clear();                             /* Clear library */
      };

      namespace generate::members {

            std::shared_ptr<library::members> make(const ir_stat::space &space);
            std::shared_ptr<library::members> make(const ir_stat::ir_expr::space &space);
            std::shared_ptr<library::members> make(const std::string &key, const std::shared_ptr<library::members> &lib);
            std::shared_ptr<library::members> make(const std::string &key, const ir_stat::space &space);
            std::shared_ptr<library::members> make(const std::string &key, const ir_stat::ir_expr::space &space);
      } // namespace generate::members
} // namespace luramas::ir::library