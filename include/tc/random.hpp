#pragma once

#include <chrono>			// std::system_clock
#include <limits>			// std::numeric_limits
#include <random>			// std::mt19937_64, std::random_device, std::uniform_int_distribution, std::uniform_real_distribution
#include <type_traits>		// std::enable_if_t, std::is_floating_point_v, std::is_integral_v, std::conditional_t, std::is_signed_v, std::is_same_v


namespace tc {
	namespace random {
		
		// Generic pseudorandom engine, seeded (hopefully) randomly.
		static std::mt19937_64 generic_rand_eng(std::random_device{}() + std::chrono::system_clock::now().time_since_epoch().count());
		
		/* Generates a uniformly distributed random floating point value.
			The random value is generated with generic_rand_eng and std::uniform_real_distribution. */
		template<typename T>
		std::enable_if_t<std::is_floating_point_v<T>, T> random_uniform()
		{
			std::uniform_real_distribution<T> dist{std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max()};
			
			return dist(generic_rand_eng);
		}
		
		/* Generates a uniformly distributed random integral value.
			The random value is generated with generic_rand_eng and std::uniform_real_distribution. */
		template<typename T>
		std::enable_if_t<std::is_integral_v<T>, T> random_uniform()
		{
			/* std::uniform_int_distribution is not defined for certain unsigned arithmetic types.
				So need to use the largest type that it's defined for and cast down. */
				
			// Largest type with the same signedness as T.
			using largest_type = std::conditional_t<std::is_signed_v<T>, long long, unsigned long long>;
			
			std::uniform_int_distribution<largest_type> dist{std::numeric_limits<T>::min(), std::numeric_limits<T>::max()};
			
			// Narrowing cast is OK, value will always be representable and thus well-defined.
			return static_cast<T>(dist(generic_rand_eng));
		}
		
		/* Generates a uniformly distributed boolean value.
			The random value is generated with generic_rand_eng. */
		template<typename T>
		std::enable_if_t<std::is_same_v<T, bool>, bool> random_uniform()
		{
			// Arbitrary unsigned type for which std::uniform_int_distribution is defined, doesn't matter which.
			using type = unsigned;
			
			std::uniform_int_distribution<type> dist{};
			
			return dist(generic_rand_eng) > (std::numeric_limits<type>::max() / 2U);
		}
		
	}
}
