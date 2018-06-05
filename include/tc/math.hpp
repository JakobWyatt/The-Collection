#pragma once

#include <cmath>			// std::exp
#include <type_traits>		// std::enable_if_t, std::is_floating_point_v


namespace tc {
	namespace math {
		
		// Sigmoid function (e^x / (e^x + 1))
		template<typename T>
		std::enable_if_t<std::is_floating_point_v<T>, T> sigmoid(T x)
		{
			T ex = std::exp(x);
			return ex / (ex + T{1});
		}
		
	}
}
