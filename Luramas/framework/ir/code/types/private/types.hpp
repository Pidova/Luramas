#pragma once
#include "../../../../misc/types.hpp"
#include "../../../definitions.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace luramas::ir::types {

      enum class type_kind : std::uint8_t {
            native,    /* Native object */
            primitive, /* Primitive to underlying type */
            object,    /* Abstract object type */
            dynamic    /* Dynamic */
      };
      struct object {

            struct type {

                  type_kind k = type_kind::native; /* Type kind */
                  std::uint8_t ptrs = 0u;          /* Pointer count */
                  tkind native = tkind::nothing;   /* Native type kind */

                  luramas::types::underlying_type under;                             /* Underlying type */
                  std::shared_ptr<object> obj = nullptr;                             /* Object type */
                  std::optional<std::vector<std::shared_ptr<object>>> dynamic_types; /* Dynamic types */

                  /* Emit */
                  void emit_ptrs(const std::uint8_t n);
                  void emit(const tkind native);
                  void emit(const luramas::types::underlying_type &under);
                  void emit(const std::shared_ptr<object> &obj);
                  void emit_dynamic(const std::shared_ptr<object> &obj);

                  /* Is */
                  template <type_kind k>
                  inline bool is() const {
                        return this->k == k;
                  }
                  template <tkind k>
                  inline bool is() const {
                        return this->is<type_kind::native>() && this->native == k;
                  }

                  /* Misc */
                  void clone(type &other) const;
                  std::shared_ptr<type> clone() const;
                  std::string str() const;
                  void serialize(std::ostream &os) const;
                  type load(std::istream &is);
                  void clear();

                  /* Compare */
                  bool compare(const type &other) const;
                  bool compare(const luramas::types::underlying_type &other) const;
                  bool operator==(const type &other) const;
                  bool operator!=(const type &other) const;
                  bool operator==(const luramas::types::underlying_type &other) const;
                  bool operator!=(const luramas::types::underlying_type &other) const;

                  inline bool basic() const {
                        return this->is<type_kind::primitive>();
                  };
                  inline std::shared_ptr<type> basic_dominant(const std::shared_ptr<type> &t) const {
                        if (!t || !t->basic()) {
                              return nullptr;
                        }
                        auto ut = this->under;
                        ut.dominant_t(t->under);
                        auto ptr = std::make_shared<type>();
                        ptr->emit(ut);
                        return ptr;
                  };
            };

            std::string name = "";                            /* Name of the object */
            std::vector<std::shared_ptr<type>> members;       /* Members of the object */
            std::vector<std::shared_ptr<type>> template_init; /* Template initialization */

            bool compare(const object &other) const;
            void clone(object &other) const;
            object clone() const;
            std::string str() const;
            void serialize(std::ostream &os);
            object load(std::istream &is);
            void clear();
      };

      namespace generate {

            std::shared_ptr<object::type> basic(const tkind native);
            std::shared_ptr<object::type> basic(const luramas::types::underlying_type &t);
            std::shared_ptr<object::type> basic(const luramas_bitwidth bits, const bool unsign, const std::uint8_t precision = 0u);
            std::shared_ptr<object::type> basic(const std::shared_ptr<object> &obj);
      } // namespace generate

      struct signature {
            luramas_flag fconstant = false;
            std::shared_ptr<luramas::ir::types::object::type> t = nullptr;

            signature() = default;

            explicit signature(const luramas_flag fconstant)
                : fconstant(fconstant), t(nullptr) {
            }
            explicit signature(const std::shared_ptr<luramas::ir::types::object::type> &t)
                : fconstant(false), t(t) {
            }
            explicit signature(const std::shared_ptr<luramas::ir::types::object::type> &t, const luramas_flag fconstant)
                : fconstant(fconstant), t(t) {
            }
      };
} // namespace luramas::ir::types