#include "../library.hpp"

namespace luramas::ir::library {

      void library::members::emit(const ir_stat::space &space) {
            this->k = kind::stats;
            this->init_stats();
            this->stats.value() = space;
            return;
      }
      void library::members::emit(const ir_stat::ir_expr::space &space) {
            this->k = kind::exprs;
            this->init_exprs();
            this->exprs.value() = space;
            return;
      }
      void library::members::emit(const std::string &key, const std::shared_ptr<members> &lib) {
            this->k = kind::library;
            this->init_lib();
            this->lib.value().try_emplace(key, lib);
            return;
      }
      void library::members::emit(const std::string &key, const ir_stat::space &space) {
            this->k = kind::library;
            this->init_lib();
            auto ptr = std::make_shared<members>();
            ptr->emit(space);
            this->lib.value().try_emplace(key, ptr);
            return;
      }
      void library::members::emit(const std::string &key, const ir_stat::ir_expr::space &space) {
            this->k = kind::library;
            this->init_lib();
            auto ptr = std::make_shared<members>();
            ptr->emit(space);
            this->lib.value().try_emplace(key, ptr);
            return;
      }
      void library::members::init_lib() {
            if (!this->lib.has_value()) {
                  this->lib.emplace(boost::unordered_flat_map<std::string, std::shared_ptr<members>>());
            }
            return;
      }
      void library::members::init_stats() {
            if (!this->stats.has_value()) {
                  this->stats.emplace(ir_stat::space());
            }
            return;
      }
      void library::members::init_exprs() {
            if (!this->exprs.has_value()) {
                  this->exprs.emplace(ir_stat::ir_expr::space());
            }
            return;
      }
      void library::members::clear() {
            *this = library::members();
            return;
      }
      std::string library::members::str(const std::string &indent, bool is_last) const {
            std::ostringstream oss;

            oss << indent;
            if (!indent.empty()) {
                  oss << (is_last ? LURAMAS_PRETTY_BRANCH_END : LURAMAS_PRETTY_BRANCH_MID) << " ";
            }

            switch (this->k) {
                  case kind::library: {
                        oss << "[library]\n";
                        if (this->lib.has_value()) {
                              std::size_t count = 0u;
                              for (const auto &[key, value] : this->lib.value()) {
                                    const bool last = (++count == this->lib.value().size());
                                    oss << indent << (is_last ? LURAMAS_PRETTY_BRANCH_INDENT : LURAMAS_PRETTY_BRANCH_VERTICLE LURAMAS_PRETTY_BRANCH_INDENT) << key << ":\n";
                                    if (value) {
                                          oss << value->str(indent + LURAMAS_PRETTY_BRANCH_VERTICLE, last);
                                    }
                              }
                        }
                        break;
                  }
                  case kind::exprs: {
                        oss << "[exprs]\n";
                        if (this->exprs.has_value()) {
                              std::size_t count = 0u;
                              for (const auto &expr : this->exprs.value()) {
                                    const auto last = (++count == this->exprs.value().size());
                                    oss << indent + (is_last ? LURAMAS_PRETTY_BRANCH_INDENT : LURAMAS_PRETTY_BRANCH_VERTICLE LURAMAS_PRETTY_BRANCH_INDENT)
                                        << (last ? LURAMAS_PRETTY_BRANCH_END : LURAMAS_PRETTY_BRANCH_MID) << " "
                                        << expr->str(indent + LURAMAS_PRETTY_BRANCH_INDENT) << "\n";
                              }
                        }
                        break;
                  }
                  case kind::stats: {
                        oss << "[stats]\n";
                        if (this->stats.has_value()) {
                              std::size_t count = 0u;
                              for (const auto &stat : this->stats.value()) {
                                    const bool last = (++count == this->stats.value().size());
                                    oss << indent + (is_last ? LURAMAS_PRETTY_BRANCH_INDENT : LURAMAS_PRETTY_BRANCH_VERTICLE LURAMAS_PRETTY_BRANCH_INDENT)
                                        << (last ? LURAMAS_PRETTY_BRANCH_END : LURAMAS_PRETTY_BRANCH_MID) << " "
                                        << stat->str(indent + LURAMAS_PRETTY_BRANCH_INDENT) << "\n";
                              }
                        }
                        break;
                  }
                  default: {
                        oss << "[none]\n";
                        break;
                  }
            }
            return oss.str();
      }

      void library::clear() {
            *this = library();
            return;
      }

      namespace generate::members {

            std::shared_ptr<library::members> make(const ir_stat::space &space) {
                  auto ptr = std::make_shared<library::members>();
                  ptr->emit(space);
                  return ptr;
            }
            std::shared_ptr<library::members> make(const ir_stat::ir_expr::space &space) {
                  auto ptr = std::make_shared<library::members>();
                  ptr->emit(space);
                  return ptr;
            }
            std::shared_ptr<library::members> make(const std::string &key, const std::shared_ptr<library::members> &lib) {
                  auto ptr = std::make_shared<library::members>();
                  ptr->emit(key, lib);
                  return ptr;
            }
            std::shared_ptr<library::members> make(const std::string &key, const ir_stat::space &space) {
                  auto ptr = std::make_shared<library::members>();
                  ptr->emit(key, space);
                  return ptr;
            }
            std::shared_ptr<library::members> make(const std::string &key, const ir_stat::ir_expr::space &space) {
                  auto ptr = std::make_shared<library::members>();
                  ptr->emit(key, space);
                  return ptr;
            }

      } // namespace generate::members

} // namespace luramas::ir::library