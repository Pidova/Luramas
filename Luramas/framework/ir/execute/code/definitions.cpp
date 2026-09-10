#include "../definitions.hpp"

namespace luramas::ir::execution {

      namespace types {

            std::shared_ptr<object> object::table::append(const std::shared_ptr<object> &value) {
                  auto k = std::make_shared<object>();
                  k->emit(static_cast<luramas_int>(this->idx_start + this->map.size()));
                  this->map.emplace(k, value);
                  return k;
            }
            std::shared_ptr<object> object::table::add(const std::shared_ptr<object> &key, const std::shared_ptr<object> &value) {
                  this->map[key] = value;
                  return key;
            }
            std::shared_ptr<object> object::table::add(const luramas_int &key, const std::shared_ptr<object> &value) {
                  for (const auto &[idx, _] : this->map) {
                        if (*idx == key) {
                              this->add(idx, value);
                              return idx;
                        }
                  }
                  auto k = std::make_shared<object>();
                  k->emit(static_cast<luramas_int>(key));
                  this->map.emplace(k, value);
                  return k;
            }
            bool object::table::remove(const std::shared_ptr<object> &key) {
                  return this->map.erase(key) != 0U;
            }
            bool object::table::remove(const luramas_int &key) {
                  for (const auto &[idx, _] : this->map) {
                        if (*idx == key) {
                              return this->map.erase(idx) != 0U;
                        }
                  }
                  return false;
            }

            /* Object emitters  */
            void object::emit() {
                  this->k = tkind::none_obj;
                  return;
            }
            void object::emit(const bool b) {
                  this->k = tkind::boolean;
                  this->v = b;
                  return;
            }
            void object::emit(const luramas_int &i) {
                  this->k = tkind::lura_int;
                  this->v = i;
                  return;
            }
            void object::emit(const std::string &s) {
                  this->k = tkind::string;
                  this->v = s;
                  return;
            }
            void object::emit(const std::shared_ptr<luramas::ir::types::object::type> &t) {
                  this->k = tkind::object;
                  this->v = t;
                  return;
            }
            void object::emit(const table &t) {
                  this->k = tkind::table;
                  this->v = t;
                  return;
            }
            void object::emit(const std::vector<std::shared_ptr<object>> &v) {
                  this->k = tkind::variadic;
                  this->v = v;
                  return;
            }
            void object::emitk(const std::string &s) {
                  this->k = tkind::kvalue;
                  this->v = s;
                  return;
            }
            void object::emits(const luramas_int &stack_id) {
                  this->k = tkind::stack;
                  this->v = stack_id;
                  return;
            }
            void object::emit_ref(const std::shared_ptr<object> &o) {
                  this->f_ref = true;
                  this->v = o;
                  return;
            }

            bool object::operator<(const luramas_int &i) const {
                  return this->k == tkind::lura_int && std::get<luramas_int>(this->v) < i;
            }
            bool object::operator>(const luramas_int &i) const {
                  return this->k == tkind::lura_int && std::get<luramas_int>(this->v) > i;
            }
            bool object::operator==(const luramas_int &i) const {
                  return this->k == tkind::lura_int && std::get<luramas_int>(this->v) == i;
            }
            bool object::operator!=(const luramas_int &i) const {
                  return !(*this == i);
            }
            bool object::operator<=(const luramas_int &i) const {
                  return (*this < i) || (*this == i);
            }
            bool object::operator>=(const luramas_int &i) const {
                  return (*this > i) || (*this == i);
            }
            bool object::operator==(const bool b) const {
                  return this->k == tkind::boolean && std::get<bool>(this->v) == b;
            }
            bool object::operator!=(const bool i) const {
                  return !(*this == i);
            }
            bool object::operator==(const std::string &str) const {
                  return this->k == tkind::string && std::get<std::string>(this->v) == str;
            }
            bool object::operator!=(const std::string &str) const {
                  return !(*this == str);
            }

            object::operator bool() const {
                  return this->k != tkind::nothing;
            }

            void object::clear() {
                  *this = object();
                  return;
            }
            object object::clone() const {

                  object result;
                  result.k = this->k;

                  std::visit(
                      [&](const auto &held) {
                            if constexpr (std::is_same_v<std::decay_t<decltype(held)>, table>) {

                                  auto copy = held;
                                  copy.map.clear();
                                  for (const auto &[key, value] : held.map) {
                                        copy.map.emplace(key ? std::make_shared<object>(key->clone()) : nullptr,
                                            value ? std::make_shared<object>(value->clone()) : nullptr);
                                  }
                                  result.v = std::move(copy);

                            } else if constexpr (std::is_same_v<std::decay_t<decltype(held)>, std::vector<std::shared_ptr<object>>>) {

                                  std::vector<std::shared_ptr<object>> copy;
                                  copy.reserve(held.size());
                                  for (const auto &e : held) {
                                        copy.emplace_back(e ? std::make_shared<object>(e->clone()) : nullptr);
                                  }
                                  result.v = std::move(copy);

                            } else {
                                  result.v = held;
                            }
                      },
                      this->v);

                  return result;
            }

      } // namespace types
} // namespace luramas::ir::execution
