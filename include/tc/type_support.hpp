#pragma once

#include <cstdint>			// std::uintmax_t
#include <type_traits>		// std::add_pointer_t, std::conjunction, std::is_same


namespace tc {
	
	/*
		Class templates
	*/

	// Provides member type alias `type` which is equivalent to adding `N` levels of pointers to `T`.
	template<typename T, std::uintmax_t N>
	struct add_pointers {
		using type = std::add_pointer_t<typename add_pointers<T, N - 1>::type>;
	};

	/* Provides member type alias `type` which is equivalent to adding `N` levels of pointers to `T`.
		Specialisation for adding zero pointers, member type alias `type` equivalent to `T`.	*/
	template<typename T>
	struct add_pointers<T, 0> {
		using type = T;
	};
	
	// std::true_type if T1, T2, and all of Ts are the same type, otherwise std::false_type.
	template<typename T1, typename T2, typename... Ts>
	struct are_same : std::conjunction<std::is_same<T1, T2>, std::is_same<T2, Ts>...> {};
	
	
	
	/*
		Helper alias templates
	*/

	// Equivalent to adding `N` levels of pointers to `T`.
	template<typename T, std::uintmax_t N>
	using add_pointers_t = typename add_pointers<T, N>::type;
	
	// true if T1, T2, and all of Ts are the same type, otherwise false.
	template<typename T1, typename T2, typename... Ts>
	constexpr inline bool are_same_v = are_same<T1, T2, Ts>::value;
	
}
