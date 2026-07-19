#pragma once
#include <array>
#include <cstdint>
#include <stdexcept>

namespace boost {

      template <typename T, std::size_t N, typename NT = std::size_t>
      class fixed_vector {
          public:
            inline constexpr fixed_vector()
                : msize(0) {
            }
            inline constexpr fixed_vector(std::initializer_list<T> init_list)
                : msize(init_list.size()) {

                  if (init_list.size() > N) [[unlikely]] {
                        throw std::out_of_range("Initializer list exceeds maximum size");
                  }
                  NT i = 0u;
                  for (auto v : init_list) {
                        this->mdata[i++] = v;
                  }
                  return;
            }

            using iterator = typename std::array<T, N>::iterator;
            using const_iterator = typename std::array<T, N>::const_iterator;

            inline constexpr auto max_size() const {
                  return N;
            }
            inline constexpr auto size() const {
                  return this->msize;
            }
            inline constexpr auto empty() const {
                  return !this->size();
            }
            inline constexpr auto push_back(const T &value) {
                  if (this->msize >= N) [[unlikely]] {
                        throw std::out_of_range("Overflow");
                  }
                  this->mdata[this->msize++] = value;
                  return;
            }
            inline constexpr auto push_back(T &&value) {
                  if (this->msize >= N) [[unlikely]] {
                        throw std::out_of_range("Overflow");
                  }
                  this->mdata[this->msize++] = std::move(value);
                  return;
            }
            template <typename... Args>
            inline constexpr void emplace_back(Args &&...args) {
                  if (this->msize >= N) [[unlikely]] {
                        throw std::out_of_range("Overflow");
                  }
                  new (&this->mdata[this->msize]) T(std::forward<Args>(args)...);
                  ++this->msize;
                  return;
            }
            inline constexpr auto pop_back() {
                  if (!this->msize) [[unlikely]] {
                        throw std::out_of_range("Underflow");
                  }
                  --this->msize;
                  return;
            }
            inline constexpr T &at(const NT idx) {
                  if (idx >= this->msize) [[unlikely]] {
                        throw std::out_of_range("Index out of range");
                  }
                  return this->mdata[idx];
            }
            inline constexpr const T &at(const NT idx) const {
                  if (idx >= msize) [[unlikely]] {
                        throw std::out_of_range("Index out of range");
                  }
                  return this->mdata[idx];
            }
            inline constexpr auto clear() {
                  this->msize = 0u;
                  return;
            }
            inline constexpr auto erase(const T &data) {
                  NT result = 0u;
                  for (auto i = 0u; i < this->msize - 1u; ++i) {
                        const auto &val = this->mdata[i];
                        if (val != data) {
                              this->mdata[result++] = val;
                        }
                  }
                  this->msize = result;
                  return;
            }
            inline constexpr auto count(const T &data) const {
                  NT result = 0u;
                  for (auto i = 0u; i < this->msize; ++i) {
                        result += this->mdata[i] == data;
                  }
                  return result;
            }
            inline constexpr auto find(const T &value) {
                  for (auto i = 0u; i < this->msize; ++i) {
                        if (this->mdata[i] == value) {
                              return this->mdata.begin() + i;
                        }
                  }
                  return this->mdata.begin() + this->msize;
            }
            inline constexpr auto find(const T &value) const {
                  for (auto i = 0u; i < this->msize; ++i) {
                        if (this->mdata[i] == value) {
                              return this->mdata.begin() + i;
                        }
                  }
                  return this->mdata.begin() + this->msize;
            }
            inline constexpr auto &operator[](const NT idx) {
                  return this->mdata[idx];
            }
            inline constexpr const auto &operator[](const NT idx) const {
                  return this->mdata[idx];
            }
            inline constexpr auto front() {
                  return this->mdata[0u];
            }
            inline constexpr auto back() {
                  auto idx = this->msize;
                  if (idx) {
                        --idx;
                  }
                  return this->mdata[idx];
            }
            inline constexpr auto front() const {
                  return this->mdata[0u];
            }
            inline constexpr auto back() const {
                  auto idx = this->msize;
                  if (idx) {
                        --idx;
                  }
                  return this->mdata[idx];
            }
            inline constexpr auto begin() {
                  return this->mdata.begin();
            }
            inline constexpr auto end() {
                  return this->mdata.begin() + this->msize;
            }
            inline constexpr auto rbegin() {
                  return this->mdata.rbegin();
            }
            inline constexpr auto rend() {
                  return this->mdata.rend();
            }
            inline constexpr auto begin() const {
                  return this->mdata.begin();
            }
            inline constexpr auto end() const {
                  return this->mdata.begin() + this->msize;
            }
            inline constexpr auto rbegin() const {
                  return this->mdata.rbegin();
            }
            inline constexpr auto rend() const {
                  return this->mdata.rend();
            }
            inline constexpr auto contains_idx(const std::size_t idx) const {
                  return idx < this->msize;
            }
            inline constexpr auto data() noexcept {
                  return this->mdata.data();
            }
            inline constexpr auto data() const noexcept {
                  return this->mdata.data();
            }
            inline constexpr auto resize(const NT size) {
                  this->msize = size;
                  return;
            }

          private:
            std::array<T, N> mdata{};
            NT msize = 0u;
      };

} // namespace boost
