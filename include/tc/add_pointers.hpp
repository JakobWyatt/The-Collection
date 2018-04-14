#pragma once

#include <cstdint>				// std::uintmax_t
#include <type_traits>			// std::add_pointer_t


namespace tc {

	/*
		Class definitions
	*/

	// Provides member type alias `type` which is equivalent to adding `N` levels of pointers to `T`.
	template<
		typename T,
		std::uintmax_t N
	>
	struct add_pointers {
		using type = std::add_pointer_t<typename add_pointers<T, N - 1>::type>;
	};

	/* Provides member type alias `type` which is equivalent to adding `N` levels of pointers to `T`.
		Specialisation for adding zero pointers, member type alias `type` equivalent to `T`.	*/
	template<
		typename T
	>
	struct add_pointers<T, 0> {
		using type = T;
	};



	/*
		Helper type aliases
	*/

	// Equivalent to adding `N` levels of pointers to `T`.
	template<
		typename T,
		std::uintmax_t N
	>
	using add_pointers_t = typename add_pointers<T, N>::type;

}