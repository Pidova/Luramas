#pragma once
#include <cstdint>
#include <optional>
#include <vector>

// TODO:  SWITCH FROMM VIRTUAL OPYTIONS TO STD::OPTIONAL

/* Verbose definitions */
using luramas_address = std::uint64_t;   /* Address */
using luramas_vaddress = std::int64_t;   /* Virtual address */
using luramas_register = std::uint16_t;  /* Register */
using luramas_vregister = std::int16_t;  /* Virtual register */
using luramas_xregister = std::uint64_t; /* Extended register */
using luramas_xvregister = std::int64_t; /* Extended register */
using luramas_id = std::uint64_t;        /* ID */
using luramas_vid = std::int64_t;        /* Virtual ID */
using luramas_count = std::size_t;       /* Counter */
using luramas_index = std::size_t;       /* Index */
using luramas_length = std::size_t;      /* Length */
using luramas_flag = bool;               /* Flag */
using luramas_bitwidth = std::uint16_t;  /* Bit width */

/* Objects */
using luramas_blockrange = std::pair<luramas_address, luramas_address>;                                /* Range [start, end) */
using luramas_oblockrange = std::pair<std::optional<luramas_address>, std::optional<luramas_address>>; /* Optional blockrange  */
using luramas_addresses = std::vector<luramas_address>;                                                /* Address vector */
using luramas_registers = std::vector<luramas_register>;                                               /* Register vector */
using luramas_vregisters = std::vector<luramas_vregister>;                                             /* Virtual register vector */
using luramas_xregisters = std::vector<luramas_xregister>;                                             /* Extended register vector */
using luramas_vaddresses = std::vector<luramas_vaddress>;                                              /* Virtual address vector */
using luramas_ids = std::vector<luramas_id>;                                                           /* ID */

/* Iterators Range [start, end) */
struct luramas_range_iter {

      luramas_blockrange range;
      struct iterator {

            luramas_address value = 0u;
            inline constexpr auto operator*() const {
                  return this->value;
            }
            inline constexpr auto &operator++() {
                  ++this->value;
                  return *this;
            }
            inline constexpr auto operator!=(const iterator &other) const {
                  return this->value != other.value;
            }
      };
      inline constexpr auto begin() const {
            return iterator{this->range.first};
      }
      inline constexpr auto end() const {
            return iterator{this->range.second};
      }
};
/* Range [start, end) */
inline constexpr luramas_range_iter luramas_iter(const luramas_blockrange &r) {
      return {r};
}

/* Range [end, start) */
struct luramas_range_reverse_iter {

      luramas_blockrange range;
      struct iterator {

            luramas_address value = 0u;
            inline constexpr auto operator*() const {
                  return this->value;
            }
            inline constexpr auto &operator++() {
                  --this->value;
                  return *this;
            }
            inline constexpr auto operator!=(const iterator &other) const {
                  return this->value != other.value;
            }
      };
      inline constexpr auto begin() const {
            return iterator{this->range.second};
      }
      inline constexpr auto end() const {
            return !this->range.first ? iterator{static_cast<luramas_address>(-1)} : iterator{this->range.first};
      }
};
/* Range [end, start) */
inline constexpr luramas_range_reverse_iter luramas_riter(const luramas_blockrange &r) {
      return {r};
}