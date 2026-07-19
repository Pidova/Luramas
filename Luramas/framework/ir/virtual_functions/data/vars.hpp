#include "../../lifter/tools/extras/exprs.hpp"

namespace luramas::ir::virtual_functions::vars {

      template <const luramas::types::underlying_type &T>
      inline std::shared_ptr<ir_stat::ir_expr> cast(const std::shared_ptr<ir_stat::ir_expr> &expr) {
            return tools::exprs::generate::cast(expr, T);
      };

      inline const auto x = tools::exprs::generate::wild_card("x");
      inline const auto x_i8 = cast<luramas::types::native::t_int8>(x);
      inline const auto x_i16 = cast<luramas::types::native::t_int16>(x);
      inline const auto x_i32 = cast<luramas::types::native::t_int32>(x);
      inline const auto x_i64 = cast<luramas::types::native::t_int64>(x);
      inline const auto x_i128 = cast<luramas::types::native::t_int128>(x);
      inline const auto x_u8 = cast<luramas::types::native::t_uint8>(x);
      inline const auto x_u16 = cast<luramas::types::native::t_uint16>(x);
      inline const auto x_u32 = cast<luramas::types::native::t_uint32>(x);
      inline const auto x_u64 = cast<luramas::types::native::t_uint64>(x);
      inline const auto x_u128 = cast<luramas::types::native::t_uint128>(x);

      inline const auto y = tools::exprs::generate::wild_card("y");
      inline const auto y_i8 = cast<luramas::types::native::t_int8>(y);
      inline const auto y_i16 = cast<luramas::types::native::t_int16>(y);
      inline const auto y_i32 = cast<luramas::types::native::t_int32>(y);
      inline const auto y_i64 = cast<luramas::types::native::t_int64>(y);
      inline const auto y_i128 = cast<luramas::types::native::t_int128>(y);
      inline const auto y_u8 = cast<luramas::types::native::t_uint8>(y);
      inline const auto y_u16 = cast<luramas::types::native::t_uint16>(y);
      inline const auto y_u32 = cast<luramas::types::native::t_uint32>(y);
      inline const auto y_u64 = cast<luramas::types::native::t_uint64>(y);
      inline const auto y_u128 = cast<luramas::types::native::t_uint128>(y);

      inline const auto z = tools::exprs::generate::wild_card("z");
      inline const auto z_i16 = cast<luramas::types::native::t_int16>(z);
      inline const auto z_i32 = cast<luramas::types::native::t_int32>(z);
      inline const auto z_i64 = cast<luramas::types::native::t_int64>(z);
      inline const auto z_i128 = cast<luramas::types::native::t_int128>(z);
      inline const auto z_u8 = cast<luramas::types::native::t_uint8>(z);
      inline const auto z_u16 = cast<luramas::types::native::t_uint16>(z);
      inline const auto z_u32 = cast<luramas::types::native::t_uint32>(z);
      inline const auto z_u64 = cast<luramas::types::native::t_uint64>(z);
      inline const auto z_u128 = cast<luramas::types::native::t_uint128>(z);
} // namespace luramas::ir::virtual_functions::vars
