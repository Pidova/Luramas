#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include <memory>
#include <optional>
#include <initializer_list>
#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) || defined(__clang__)
#include <cpuid.h>
#endif

/* Types */
namespace std {
#if defined(__GNUC__) || defined(__clang__)
	using uint128_t = __uint128_t;
	using int128_t = __int128_t;
#endif
}


/* Dead macros */
#define lura_deadv(x) { [[maybe_unused]] x; };
#define lura_dead(x) x;


/* Flags */
static constexpr auto flag_grow_stack_downwards = true; /* Grow the stack downwards? */


/* Stack */
static constexpr auto stack_size = 0x1000; /* Size of stack in bytes */
inline auto lura_stack = reinterpret_cast<std::int32_t>((new std::int8_t[stack_size]) + (flag_grow_stack_downwards ? stack_size : 0u));


/* Bitread [Min, Max] */
template<typename R, typename T>
inline constexpr R lura_bitread(const T v, const unsigned low, const unsigned high) {
	return R((v >> low) & ((T(1) << (high - low + 1)) - 1));
}


/* Memory */
static constexpr auto base = 0u;
template<typename T, typename R>
inline constexpr T lura_memread(const R offset) {
	static_assert(std::is_trivially_copyable_v<T>);
	T val;
	std::memcpy(&val, reinterpret_cast<std::uintptr_t*>(base + offset), sizeof(T));
	return val;
}
template<typename T, typename R>
inline constexpr T& lura_memset(const R offset) {
	static_assert(std::is_trivially_copyable_v<T>);
	return *reinterpret_cast<T*>(base + offset);
}


/* Page functions */
template <auto Fn, typename... Args>
inline decltype(auto) lura_page_function_goto(Args&&... args) {
	return Fn(std::forward<Args>(args)...);
}
template <auto Fn, std::uintptr_t RES = 0u, typename s, typename... Args>
inline decltype(auto) lura_page_function_call(s& stack, Args&&... args) {

	stack -= sizeof(s);
	*reinterpret_cast<s*>(stack) = RES;
	return Fn(std::forward<Args>(args)...);
}


/* Logicals */
template <typename T>
inline constexpr bool lura_truthy(const T& value) {
	return static_cast<bool>(value);
}
template <typename T>
inline constexpr bool lura_truthy(const T* ptr) {
	return ptr != nullptr;
}
template <typename T>
inline constexpr bool lura_truthy(const std::optional<T>& opt) {
	return opt.has_value();
}
template <typename A, typename B>
decltype(auto) lura_and(A&& a, B&& b) {
	return lua_truthy(a) ? std::forward<B>(b) : std::forward<A>(a);
}
template <typename A, typename B>
decltype(auto) lura_or(A&& a, B&& b) {
	return lua_truthy(a) ? std::forward<A>(a) : std::forward<B>(b);
}