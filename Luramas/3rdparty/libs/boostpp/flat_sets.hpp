#pragma once
#include "vector.hpp"
#include <boost/unordered/unordered_flat_map.hpp>
#include <boost/unordered/unordered_flat_set.hpp>
#include <iterator>
#include <variant>

namespace boost {

      template <typename T>
      class unordered_flat_multiset {

          public:
            void insert(const T &value) {
                  ++this->data[value];
                  return;
            }

            void erase(const T &value) {
                  auto it = this->data.find(value);
                  if (it != this->data.end()) {
                        if (!(--it->second)) {
                              this->data.erase(it);
                        }
                  }
                  return;
            }

            std::size_t count(const T &value) const {
                  const auto it = this->data.find(value);
                  return it != this->data.end() ? it->second : 0u;
            }

            std::size_t size() const {
                  std::size_t total = 0u;
                  for (const auto &[key, count] : this->data) {
                        total += count;
                  }
                  return total;
            }

            auto contains(const T &value) const {
                  return this->data.contains(value);
            }
            auto max_load_factor() const {
                  return this->data.max_load_factor();
            }
            auto reserve(const std::size_t amt) {
                  this->data.reserve(amt);
                  return;
            }
            auto empty() const {
                  return this->data.empty();
            }
            auto clear() {
                  this->data.clear();
                  return;
            }

            auto begin() {
                  return flattened_iterator(data.begin(), data.end());
            }
            auto end() {
                  return flattened_iterator(data.end(), data.end());
            }
            auto begin() const {
                  return flattened_iterator(data.begin(), data.end());
            }
            auto end() const {
                  return flattened_iterator(data.end(), data.end());
            }

            template <typename input_it>
            void insert(input_it first, input_it last) {
                  for (auto it = first; it != last; ++it) {
                        this->insert(*it);
                  }
                  return;
            }

            auto find(const T &value) {
                  auto it = this->data.find(value);
                  if (it == this->data.end()) {
                        return this->end();
                  }
                  return flattened_iterator(it, this->data.end());
            }
            auto find(const T &value) const {
                  auto it = this->data.find(value);
                  if (it == this->data.end()) {
                        return this->end();
                  }
                  return flattened_iterator(it, this->data.end());
            }

          private:
            boost::unordered_flat_map<T, std::size_t> data;
            struct flattened_iterator {

                  boost::unordered_flat_map<T, std::size_t>::const_iterator map_it;
                  boost::unordered_flat_map<T, std::size_t>::const_iterator map_end;
                  std::size_t repeat_count;

                  flattened_iterator(boost::unordered_flat_map<T, std::size_t>::const_iterator it, boost::unordered_flat_map<T, std::size_t>::const_iterator end)
                      : map_it(it), map_end(end), repeat_count(it != end ? it->second : 0) {
                  }

                  auto operator*() const {
                        return this->map_it->first;
                  }
                  auto operator->() const {
                        return &this->map_it->first;
                  }

                  flattened_iterator &operator++() {
                        if (this->map_it == this->map_end) {
                              return *this;
                        }
                        if (!(--this->repeat_count)) {
                              ++this->map_it;
                              this->repeat_count = this->map_it != this->map_end ? this->map_it->second : 0u;
                        }
                        return *this;
                  }

                  flattened_iterator operator++(int) {
                        auto tmp = *this;
                        ++(*this);
                        return tmp;
                  }

                  bool operator==(const flattened_iterator &other) const {
                        return this->map_it == other.map_it && this->repeat_count == other.repeat_count;
                  }
                  bool operator!=(const flattened_iterator &other) const {
                        return !(*this == other);
                  }
            };
      };

      template <typename T, std::uint8_t threshold>
      class unordered_flat_smallpolyset {

          public:
            unordered_flat_smallpolyset() {
            }

            unordered_flat_smallpolyset(const T &t) {
                  this->insert(t);
                  return;
            }
            unordered_flat_smallpolyset(const boost::unordered_flat_set<T>::iterator &begin, const boost::unordered_flat_set<T>::iterator &end) {
                  for (auto it = begin; it != end; ++it) {
                        this->insert(*it);
                  }
                  return;
            }

            inline std::pair<std::size_t /* Placeholder */, bool> insert(const T &data) {
                  if (!this->tranformed && this->size() + 1u > threshold) {
                        boost::unordered_flat_set<T> set;
                        set.reserve(this->reserve_n + threshold);
                        set.insert(this->vect.begin(), this->vect.end());
                        this->data = std::move(set);
                        this->tranformed = true;
                  }
                  if (this->tranformed) {
                        return std::make_pair(0u, this->data.value().insert(data).second);
                  }
                  if (this->contains(data)) {
                        return std::make_pair(0u, false);
                  }
                  this->vect.push_back(data);
                  return std::make_pair(0u, true);
            }
            template <class input_it>
            inline void insert(const input_it &begin, const input_it &end) {
                  for (auto it = begin; it != end; ++it) {
                        this->insert(*it);
                  }
                  return;
            }

            inline bool contains(const T &data) const {
                  if (this->tranformed) {
                        return this->data.value().contains(data);
                  }
                  for (const auto &i : this->vect) {
                        if (i == data) {
                              return true;
                        }
                  }
                  return false;
            }
            inline std::size_t size() const {
                  return this->tranformed ? this->data.value().size() : this->vect.size();
            }
            inline bool empty() const {
                  return !this->size();
            }
            inline std::size_t count(const T &data) const {
                  if (this->tranformed) {
                        return this->data.value().count(data);
                  }
                  return this->vect.count(data);
            }
            inline void reserve(const std::size_t n) {
                  if (this->tranformed) {
                        this->data.value().reserve(n);
                  } else {
                        this->reserve_n = n;
                  }
                  return;
            }
            inline void clear() {
                  if (this->tranformed) {
                        this->data.value().clear();
                  } else {
                        this->vect.clear();
                  }
                  return;
            }
            inline std::size_t erase(const T &data) {
                  if (this->tranformed) {
                        return this->data.value().erase(data);
                  }
                  const auto pre_count = this->vect.size();
                  this->vect.erase(data);
                  return pre_count - this->vect.size();
            }

            class iterator {
                  using vect_iterator = typename boost::fixed_vector<T, threshold>::iterator;
                  using set_iterator = typename boost::unordered_flat_set<T>::iterator;

                  std::variant<vect_iterator, set_iterator> iter_;

                public:
                  explicit iterator(const vect_iterator &it)
                      : iter_(it) {
                  }
                  explicit iterator(const set_iterator &it)
                      : iter_(it) {
                  }

                  T &operator*() {
                        return std::visit([](auto &it) -> T & { return const_cast<T &>(*it); }, this->iter_);
                  }

                  iterator &operator++() {
                        std::visit([](auto &it) { ++it; }, this->iter_);
                        return *this;
                  }

                  bool operator!=(const iterator &other) const {
                        return this->iter_ != other.iter_;
                  }
            };

            class const_iterator {
                  using vect_iterator = typename boost::fixed_vector<T, threshold>::const_iterator;
                  using set_iterator = typename boost::unordered_flat_set<T>::const_iterator;

                  std::variant<vect_iterator, set_iterator> iter_;

                public:
                  explicit const_iterator(const vect_iterator &it)
                      : iter_(it) {
                  }
                  explicit const_iterator(const set_iterator &it)
                      : iter_(it) {
                  }

                  const T &operator*() const {
                        return std::visit([](const auto &it) -> const T & { return *it; }, this->iter_);
                  }

                  const_iterator &operator++() {
                        std::visit([](auto &it) { ++it; }, this->iter_);
                        return *this;
                  }

                  bool operator!=(const const_iterator &other) const {
                        return this->iter_ != other.iter_;
                  }
            };
            inline auto find(const T &data) {
                  if (this->tranformed) {
                        return iterator(this->data.value().find(data));
                  }
                  return iterator(this->vect.find(data));
            }
            inline auto find(const T &data) const {
                  if (this->tranformed) {
                        return const_iterator(this->data.value().find(data));
                  }
                  return const_iterator(this->vect.find(data));
            }
            iterator begin() {
                  return this->tranformed ? iterator(this->data.value().begin()) : iterator(this->vect.begin());
            }

            iterator end() {
                  return this->tranformed ? iterator(this->data.value().end()) : iterator(this->vect.end());
            }

            const_iterator begin() const {
                  return this->tranformed ? const_iterator(this->data.value().begin()) : const_iterator(this->vect.begin());
            }

            const_iterator end() const {
                  return this->tranformed ? const_iterator(this->data.value().end()) : const_iterator(this->vect.end());
            }

          private:
            bool tranformed = false;
            std::size_t reserve_n = 0u;
            std::optional<boost::unordered_flat_set<T>> data;
            boost::fixed_vector<T, threshold> vect;
      };

} // namespace boost
