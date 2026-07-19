#include "../types.hpp"

/* Type */
void luramas::ir::types::object::type::emit_ptrs(const std::uint8_t n) {
      this->ptrs = n;
      return;
}
void luramas::ir::types::object::type::emit(const tkind native) {
      this->k = type_kind::native;
      this->native = native;
      return;
}
void luramas::ir::types::object::type::emit(const luramas::types::underlying_type &under) {
      this->k = type_kind::primitive;
      this->under = under;
      return;
}
void luramas::ir::types::object::type::emit(const std::shared_ptr<object> &obj) {
      this->k = type_kind::object;
      this->obj = obj;
      return;
}
void luramas::ir::types::object::type::emit_dynamic(const std::shared_ptr<object> &obj) {
      if (!this->dynamic_types.has_value()) {
            this->dynamic_types = std::vector<std::shared_ptr<object>>();
      }
      this->dynamic_types.value().emplace_back(obj);
      return;
}
void luramas::ir::types::object::type::clone(type &other) const {
      other.k = this->k;
      other.ptrs = this->ptrs;
      other.native = this->native;
      this->under.clone(other.under);
      if (other.obj) {
            this->obj->clone(*other.obj);
      } else {
            other.obj = nullptr;
      }
      if (this->dynamic_types.has_value()) {
            other.dynamic_types.emplace(std::vector<std::shared_ptr<object>>());
            other.dynamic_types.value().reserve(this->dynamic_types.value().size());
            for (const auto &i : this->dynamic_types.value()) {
                  auto ptr = std::make_shared<object>();
                  i->clone(*ptr);
                  other.dynamic_types.value().emplace_back(ptr);
            }
      } else if (other.dynamic_types.has_value()) {
            other.dynamic_types.value().clear();
      }
      return;
}
std::shared_ptr<luramas::ir::types::object::type> luramas::ir::types::object::type::clone() const {
      auto result = std::make_shared<luramas::ir::types::object::type>();
      this->clone(*result);
      return result;
}
std::string luramas::ir::types::object::type::str() const {
      std::string result("");
      for (auto i = 0u; i < this->ptrs; ++i) {
            result += "*";
      }
      switch (this->k) {
            case type_kind::native: {
                  result += luramas::ir::str(this->native);
                  break;
            }
            case type_kind::primitive: {
                  result += this->under.str();
                  break;
            }
            case type_kind::object: {
                  result += this->obj->str();
                  break;
            }
            case type_kind::dynamic: {
                  result += "(";
                  if (!this->dynamic_types.value().empty()) {
                        result += "<";
                        for (auto i = 0u; i < this->dynamic_types.value().size(); ++i) {
                              result += this->dynamic_types.value()[i]->str();
                              if ((i + 1u) < this->dynamic_types.value().size()) {
                                    result += ", ";
                              }
                        }
                        result += ">";
                  }
                  result += ")";
                  break;
            }
            default: {
                  break;
            }
      }
      return result;
}
void luramas::ir::types::object::type::serialize(std::ostream &os) const {
      os.write(reinterpret_cast<const char *>(&this->k), sizeof(this->k));
      os.write(reinterpret_cast<const char *>(&this->ptrs), sizeof(this->ptrs));
      os.write(reinterpret_cast<const char *>(&this->native), sizeof(this->native));
      this->under.serialize(os);

      const auto has_obj = (this->obj != nullptr);
      os.write(reinterpret_cast<const char *>(&has_obj), sizeof(has_obj));
      if (has_obj) {
            this->obj->serialize(os);
      }

      const auto has_dynamic_types = this->dynamic_types.has_value();
      os.write(reinterpret_cast<const char *>(&has_dynamic_types), sizeof(has_dynamic_types));
      if (has_dynamic_types) {
            const auto size = static_cast<std::size_t>(this->dynamic_types->size());
            os.write(reinterpret_cast<const char *>(&size), sizeof(size));
            for (const auto &i : *this->dynamic_types) {
                  i->serialize(os);
            }
      }
      return;
}
luramas::ir::types::object::type luramas::ir::types::object::type::load(std::istream &is) {
      object::type result;
      is.read(reinterpret_cast<char *>(&result.k), sizeof(result.k));
      is.read(reinterpret_cast<char *>(&result.ptrs), sizeof(result.ptrs));
      is.read(reinterpret_cast<char *>(&result.native), sizeof(result.native));
      result.under.load(is);

      bool has_obj = false;
      is.read(reinterpret_cast<char *>(&has_obj), sizeof(has_obj));
      if (has_obj) {
            this->obj = std::make_shared<object>();
            this->obj->load(is);
      }

      bool has_dynamic_types = false;
      is.read(reinterpret_cast<char *>(&has_dynamic_types), sizeof(has_dynamic_types));
      if (has_dynamic_types) {
            std::size_t dynamic_types_size = 0u;
            is.read(reinterpret_cast<char *>(&dynamic_types_size), sizeof(dynamic_types_size));
            result.dynamic_types.emplace(std::vector<std::shared_ptr<object>>());
            result.dynamic_types->reserve(dynamic_types_size);
            for (auto i = 0u; i < dynamic_types_size; ++i) {
                  this->dynamic_types->emplace_back(std::make_shared<object>());
                  this->dynamic_types->back()->load(is);
            }
      }
      return result;
}
void luramas::ir::types::object::type::clear() {
      *this = type();
      return;
}

bool luramas::ir::types::object::type::compare(const type &other) const {

      if (std::tie(this->k, this->ptrs, this->native) !=
          std::tie(other.k, other.ptrs, other.native)) {
            return false;
      }
      if (!this->under.compare(other.under)) {
            return false;
      }
      if ((!this->obj) != (!other.obj)) {
            return false;
      }
      if (this->obj && other.obj && !this->obj->compare(*other.obj)) {
            return false;
      }
      if ((this->dynamic_types.has_value() != other.dynamic_types.has_value()) ||
          (this->dynamic_types && other.dynamic_types &&
              !std::equal(this->dynamic_types->begin(), this->dynamic_types->end(), other.dynamic_types->begin(), other.dynamic_types->end(), [](const auto &a, const auto &b) { return a->compare(*b); }))) {
            return false;
      }
      return true;
}
bool luramas::ir::types::object::type::compare(const luramas::types::underlying_type &other) const {
      return this->k == type_kind::primitive && this->under == other;
}
bool luramas::ir::types::object::type::operator==(const type &other) const {
      return this->compare(other);
}
bool luramas::ir::types::object::type::operator!=(const type &other) const {
      return !(*this == other);
}
bool luramas::ir::types::object::type::operator==(const luramas::types::underlying_type &other) const {
      return this->compare(other);
}
bool luramas::ir::types::object::type::operator!=(const luramas::types::underlying_type &other) const {
      return !(*this == other);
}

/* Object */
bool luramas::ir::types::object::compare(const object &other) const {
      if (this->name != other.name) {
            return false;
      }

      if (!std::equal(this->members.begin(), this->members.end(), other.members.begin(), other.members.end(), [](const auto &a, const auto &b) { return a->compare(*b); })) {
            return false;
      }

      if (!std::equal(this->template_init.begin(), this->template_init.end(), other.template_init.begin(), other.template_init.end(), [](const auto &a, const auto &b) { return a->compare(*b); })) {
            return false;
      }
      return true;
}
void luramas::ir::types::object::clone(object &other) const {
      other.name = this->name;
      other.members.reserve(this->members.size());
      for (const auto &i : this->members) {
            auto ptr = std::make_shared<type>();
            i->clone(*ptr);
            other.members.emplace_back(ptr);
      }
      other.template_init.reserve(this->template_init.size());
      for (const auto &i : this->template_init) {
            auto ptr = std::make_shared<type>();
            i->clone(*ptr);
            other.template_init.emplace_back(ptr);
      }
      return;
}
luramas::ir::types::object luramas::ir::types::object::clone() const {
      object result;
      this->clone(result);
      return result;
}
std::string luramas::ir::types::object::str() const {

      auto result = this->name;

      if (!this->template_init.empty()) {
            result += "<";
            for (auto i = 0u; i < this->template_init.size(); ++i) {
                  result += this->template_init[i]->str();
                  if ((i + 1u) < this->template_init.size()) {
                        result += ", ";
                  }
            }
            result += ">";
      }
      result += "(";
      if (!this->members.empty()) {
            result += "<";
            for (auto i = 0u; i < this->members.size(); ++i) {
                  result += this->members[i]->str();
                  if ((i + 1u) < this->members.size()) {
                        result += ", ";
                  }
            }
            result += ">";
      }
      result += ")";
      return result;
}
void luramas::ir::types::object::serialize(std::ostream &os) {

      luramas::fs::serialize(os, this->name);

      const auto members_size = static_cast<std::size_t>(this->members.size());
      os.write(reinterpret_cast<const char *>(&members_size), sizeof(members_size));
      for (const auto &i : this->members) {
            i->serialize(os);
      }

      const auto template_init_size = static_cast<std::size_t>(this->template_init.size());
      os.write(reinterpret_cast<const char *>(&template_init_size), sizeof(template_init_size));
      for (const auto &i : this->template_init) {
            i->serialize(os);
      }
      return;
}
luramas::ir::types::object luramas::ir::types::object::load(std::istream &is) {

      object result;
      luramas::fs::load(is, result.name);

      std::size_t members_size = 0u;
      is.read(reinterpret_cast<char *>(&members_size), sizeof(members_size));
      result.members.reserve(members_size);
      for (auto i = 0u; i < members_size; ++i) {
            result.members.emplace_back(std::make_shared<type>());
            result.members.back()->load(is);
      }

      std::size_t template_init_size = 0u;
      is.read(reinterpret_cast<char *>(&template_init_size), sizeof(template_init_size));
      result.template_init.reserve(template_init_size);
      for (auto i = 0u; i < template_init_size; ++i) {
            result.template_init.push_back(std::make_shared<type>());
            result.template_init.back()->load(is);
      }
      return result;
}
void luramas::ir::types::object::clear() {
      *this = object();
      return;
}