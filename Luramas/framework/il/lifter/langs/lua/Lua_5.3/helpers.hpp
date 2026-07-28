#pragma once

static constexpr auto LUA_BITRK = 1u << 8; /* Bit Mask of RK flag */

namespace helpers {

      /* RK is kvalue? */
      template <typename T>
      inline bool rk_is_k(const T v) {
            return (v & LUA_BITRK) != 0u;
      }

      /* Converts RK index to KV index */
      template <typename T>
      inline unsigned rk_idx(const T v) {
            return v & ~LUA_BITRK;
      }
} // namespace helpers