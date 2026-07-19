#include "types.hpp"
#include <istream>
#include <ostream>

namespace luramas::types {

      /* Underlying type */
      bool underlying_type::compare(const std::uint16_t memsize) const {
            return this->is<read_type::bytes>() && this->storage_size == memsize;
      }
      bool underlying_type::compare(const luramas_bitwidth bits, const bool unsign) const {
            return this->is<read_type::bits>() && this->storage_size == bits && this->unsign == unsign && !this->precision;
      }
      bool underlying_type::weak_compare(const underlying_type &other) const {
            return std::tie(this->read, this->storage_size) == std::tie(other.read, other.storage_size);
      }
      bool underlying_type::compare(const underlying_type &other) const {
            return std::tie(this->unsign, this->read, this->precision, this->storage_size) == std::tie(other.unsign, other.read, other.precision, other.storage_size);
      }
      void underlying_type::dominant(const underlying_type &other, const signess dom) {
            if (this->storage_size < other.storage_size) {
                  this->storage_size = other.storage_size;
            }
            if (this->precision < other.precision) {
                  this->precision = other.precision;
            }
            if (other.read == read_type::bytes && this->read == read_type::bits) {
                  this->read = other.read;
            }
            if (other.unsign != this->unsign) {
                  this->unsign = dom == signess::unsign;
            }
            return;
      }
      underlying_type underlying_type::dominant_t(const underlying_type &other, const signess dom) const {
            auto result = underlying_type(*this);
            result.dominant(other);
            return result;
      }
      luramas_bitwidth underlying_type::bits() const {
            return this->read == read_type::bits ? this->storage_size : this->storage_size * 8u;
      }
      bool underlying_type::empty() const {
            return *this == underlying_type();
      }

      luramas_int_base underlying_type::bmin() const {
            if (this->unsign) {
                  return 0;
            }
            return -(1LL << (this->bits() - 1));
      }
      luramas_int_base underlying_type::bmax() const {
            if (this->unsign) {
                  return (1ULL << this->bits()) - 1;
            }
            return (1LL << (this->bits() - 1)) - 1;
      }

      void underlying_type::emit(const std::uint16_t memsize) {
            this->read = read_type::bytes;
            this->storage_size = memsize;
            return;
      }
      void underlying_type::emit(const luramas_bitwidth bits, const bool unsign, const std::uint8_t precision) {
            this->read = read_type::bits;
            this->unsign = unsign;
            this->storage_size = bits;
            this->precision = precision;
            return;
      }

      bool underlying_type::operator==(const underlying_type &other) const {
            return this->compare(other);
      }
      bool underlying_type::operator!=(const underlying_type &other) const {
            return !(*this == other);
      }
      underlying_type::operator bool() const {
            return *this != underlying_type();
      }

      signess underlying_type::signess_t() const {
            return this->unsign ? signess::unsign : signess::sign;
      }
      underlying_type underlying_type::clone(underlying_type &other) const {
            other.unsign = this->unsign;
            other.read = this->read;
            other.precision = this->precision;
            other.storage_size = this->storage_size;
            return other;
      }
      std::shared_ptr<underlying_type> underlying_type::clone() const {
            auto result = std::make_shared<underlying_type>();
            this->clone(*result);
            return result;
      }
      std::string underlying_type::str() const {

            std::string result("");

            if (this->is<read_type::bytes>()) {
                  result += "int8_t[" + std::to_string(this->storage_size) + "]";
            } else if (this->storage_size == 32u && this->precision == 7u) {
                  if (this->unsign) {
                        result = "unsigned ";
                  }
                  result += "float";
            } else if (this->storage_size == 64u && this->precision == 15u) {
                  if (this->unsign) {
                        result = "unsigned ";
                  }
                  result += "double";
            } else {
                  if (this->unsign) {
                        result = "u";
                  }
                  result += (this->precision ? "f" + std::to_string(this->storage_size) + "_p" + std::to_string(this->precision) : "int" + std::to_string(this->storage_size)) + "_t";
            }
            return result;
      }
      void underlying_type::serialize(std::ostream &os) const {
            os.write(reinterpret_cast<const char *>(&this->unsign), sizeof(this->unsign));
            os.write(reinterpret_cast<const char *>(&this->read), sizeof(this->read));
            os.write(reinterpret_cast<const char *>(&this->precision), sizeof(this->precision));
            os.write(reinterpret_cast<const char *>(&this->storage_size), sizeof(this->storage_size));
      }
      underlying_type underlying_type::load(std::istream &is) const {
            underlying_type result;
            is.read(reinterpret_cast<char *>(result.unsign), sizeof(result.unsign));
            is.read(reinterpret_cast<char *>(result.read), sizeof(result.read));
            is.read(reinterpret_cast<char *>(result.precision), sizeof(result.precision));
            is.read(reinterpret_cast<char *>(result.storage_size), sizeof(result.storage_size));
            return result;
      }
      bool underlying_type::has_native() const {
            auto size = this->storage_size;
            if (this->read == read_type::bytes) {
                  size *= 8u;
            }
            if (!this->precision) {
                  switch (size) {
                        case 1u:
                        case 8u:
                        case 16u:
                        case 32u:
                        case 64u:
                        case 128u:
                        case 256u:
                        case 512u: {
                              return true;
                        }
                        default: {
                              break;
                        }
                  }
            }
            switch (this->precision) {
                  case 6u:
                  case 7u:
                  case 9u:
                  case 15u:
                  case 16u:
                  case 17u: {
                        return true;
                  }
                  default: {
                        break;
                  }
            }
            return false;
      }
      void underlying_type::clear() {
            *this = underlying_type();
            return;
      }

      namespace is {

            bool diff_bits(const underlying_type &a, const underlying_type &b) {

                  return a.unsign == b.unsign && a.bits() != b.bits();
            }

            bool diff_signess(const underlying_type &a, const underlying_type &b) {

                  return a.bits() == b.bits() && a.unsign != b.unsign;
            }
      } // namespace is

      namespace native::compiler {

            std::string object::str() const {
                  std::string result("");
                  if (this->synthetic_type) {
                        result += "[SYNTHETIC] ";
                  }
                  if (this->constant_ptr) {
                        result += "const ";
                  }
                  if (std::strlen(this->name)) {
                        result += this->name + std::string(" ");
                  }
                  result += this->type.str();
                  for (auto i = 0u; i < this->ptrs; ++i) {
                        result += "*";
                  }

                  if (this->constant_value) {
                        result += "const";
                  }
                  return result;
            }
            void object::clear() {
                  *this = object();
                  return;
            }
            bool object::empty() const {
                  return !std::strlen(this->name);
            }
      } // namespace native::compiler

      std::size_t hash_value(const underlying_type &u) {
            std::size_t seed = 0u;
            boost::hash_combine(seed, u.unsign);
            boost::hash_combine(seed, static_cast<std::underlying_type_t<decltype(u.read)>>(u.read));
            boost::hash_combine(seed, u.precision);
            boost::hash_combine(seed, u.storage_size);
            return seed;
      }
} // namespace luramas::types