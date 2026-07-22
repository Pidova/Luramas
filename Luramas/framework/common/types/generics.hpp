#pragma once
#include "arith.hpp"
#include "types.hpp"
#include <boostpp/flat_sets.hpp>

/* Evaluated kinds */
enum class LURAMAS_IR_EVAL_KINDS : std::uint8_t {
      false_, /* Falsey */
      true_,  /* Truthy */
      nothing /* Nothing */
};

/* Direction */
enum LURAMAS_IR_DIRECTION_KINDS : std::uint8_t {
      forward, /* Forwards */
      backward /* Backwards */
};

/* Track register contents */
struct luramas_register_contents {
      std::uintptr_t id = 0u;    /* Register ID */
      luramas_int_base data = 0; /* Data */
};

/* Track register data  */
template <typename T>
struct luramas_track_reg {

      bool contiguous_truthy = true; /* True if all offsets are aligned to slot_size */
      luramas_address offset = 0u;   /* Starting offset */
      std::vector<T> mem_data;       /* Stored T data */

      luramas_track_reg(const std::size_t slot_size)
          : slot_size(slot_size) {
      }
      void emit_offset(const luramas_address off) {
            if (off % this->slot_size) {
                  this->contiguous_truthy = false;
            }
            this->offset = off;
            return;
      }

    private:
      std::size_t slot_size = 0u;
};

/* Track multiple register data */
template <typename T>
struct luramas_regtracker {
      boost::unordered_flat_map<luramas_register, luramas_track_reg<T>> data; /* Register to data */
};
