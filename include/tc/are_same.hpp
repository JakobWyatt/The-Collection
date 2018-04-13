#pragma once

#include <type_traits>			// std::conjunction, std::is_same


namespace tc {

	/*
		Class definitions
	*/

	// std::true_type if T1, T2, and all of Ts are the same type, otherwise std::false_type.
	template<
		typename T1,
		typename T2,
		typename... Ts
	>
	struct are_same : std::conjunction<std::is_same<T1, T2>, std::is_same<T2, Ts>...> {};



	/*
		Helper type aliases
	*/

	// true if T1, T2, and all of Ts are the same type, otherwise false.
	template<
		typename T1,
		typename T2,
		typename... Ts
	>
	constexpr inline bool are_same_v = are_same<T1, T2, Ts>::value;
}