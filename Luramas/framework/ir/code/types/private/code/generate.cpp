#include "../types.hpp"

namespace luramas::ir::types::generate {

      std::shared_ptr<object::type> basic(const tkind native) {
            auto result = std::make_shared<object::type>();
            result->emit(native);
            return result;
      }
      std::shared_ptr<object::type> basic(const luramas_bitwidth bits, const bool unsign, const std::uint8_t precision) {
            auto result = std::make_shared<object::type>();
            luramas::types::underlying_type ut;
            ut.emit(bits, unsign, precision);
            result->emit(ut);
            return result;
      }
      std::shared_ptr<object::type> basic(const luramas::types::underlying_type &t) {
            auto result = std::make_shared<object::type>();
            result->emit(t);
            return result;
      }
      std::shared_ptr<object::type> basic(const std::shared_ptr<object> &obj) {
            auto result = std::make_shared<object::type>();
            result->emit(obj);
            return result;
      }

} // namespace luramas::ir::types::generate
