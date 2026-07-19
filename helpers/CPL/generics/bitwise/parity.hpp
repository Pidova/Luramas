#pragma once
#include <cstdint>

namespace cpl::bitwise::parity {

	/*

	*/
	inline constexpr auto xor_fold_n(auto x, const auto n) {

		static_assert(std::is_unsigned<T>::value, "Only unsigned types supported");
		for (auto i = 0u, shift = (sizeof(T) * 8u) / 2u; i < n && shift > 0u; ++i, shift /= 2u) {
			x ^= x >> shift;
		}
		return x;
	}

}