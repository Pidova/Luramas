#pragma once
#include <algorithm>
#include <vector>

namespace luramas::recursion {

      template <typename T>
      class manager {

          public:
            inline constexpr manager(const std::size_t reserve = 0u) {
                  this->stack.reserve(reserve);
                  return;
            }
            inline constexpr manager(const T &s, const std::size_t reserve = 0u) {
                  this->stack.reserve(reserve);
                  this->stack.emplace_back(s);
                  return;
            }
            inline constexpr auto lazy_reset(const T &s) {
                  if (this->stack.empty()) {
                        this->stack.emplace_back(s);
                  }
                  return;
            }
            inline constexpr auto reset(const T &s) {
                  this->stack.clear();
                  this->stack.emplace_back(s);
                  return;
            }
            inline constexpr auto push(const T &value) {
                  this->stack.emplace_back(value);
                  return;
            }
            inline constexpr auto push(const std::vector<T> &v) {
                  this->stack.reserve(this->stack.size() + v.size());
                  this->stack.insert(this->stack.end(), v.begin(), v.end());
                  return;
            }
            inline constexpr auto curr() {
                  if (!this->stack.empty()) {
                        const auto result = this->stack.back();
                        this->stack.pop_back();
                        return result;
                  }
                  return T{};
            }
            inline constexpr auto valid() const {
                  return this->stack.empty();
            }
            inline constexpr operator bool() const {
                  return this->valid();
            }

          private:
            std::vector<T> stack;
      };
} // namespace luramas::recursion