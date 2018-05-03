#pragma once

#include <climits>			// CHAR_BIT
#include <cstddef>			// std::size_t
#include <cstdint>			// std::uint16_t, std::uint32_t, std::uint64_t
#include <intrin.h>			// __popcount16, __popcount, __popcount64
#include <type_traits>		// std::enable_if_t


namespace tc {
	
	/*
		Variable templates
	*/
	
	// Size, in bits, of a type.
	template<typename T>
	constexpr inline std::size_t bits = sizeof(T) * CHAR_BIT;
	
	
	
	/*
		Function templates
	*/
	
	// Gets the value of the nth bit (bit 0 is LSB).
	template<typename T>
	inline bool get_bit(T value, std::size_t n)
	{
		return (value >> n) & static_cast<T>(1U);
	}
	
	// Popcount (number of bits set) (<=16 bit type).
	template<typename T>
	inline std::enable_if_t<(bits<T> <= 16), std::size_t> popcount(T val)
	{
		return __popcnt16(static_cast<std::uint16_t>(val));
	}

	// Popcount (number of bits set) (16-32 bit type).
	template<typename T>
	inline std::enable_if_t<(bits<T> > 16) && (bits<T> <= 32), std::size_t> popcount(T val)
	{
		return __popcnt(static_cast<std::uint32_t>(val));
	}

	// Popcount (number of bits set) (32-64 bit type).
	template<typename T>
	inline std::enable_if_t<(bits<T> > 32) && (bits<T> <= 64), std::size_t> popcount(T val)
	{
		return __popcnt64(static_cast<std::uint64_t>(val));
	}
	
	// Conditionally set the nth bit to 1 (bit 0 is LSB).
	template<typename T>
	inline void set_bit_cond(T& val, std::size_t n, bool condition)
	{
		val |= static_cast<T>(condition) << n;
	}
	
}