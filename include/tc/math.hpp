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
		
		// Derivative of the sigmoid function (e^x / (e^x + 1)^2)
		template<typename T>
		std::enable_if_t<std::is_floating_point_v<T>, T> sigmoid_deriv(T x)
		{
			T ex = std::exp(x);
			T ex_p1 = ex + T{1};
			
			return ex / (ex_p1 * ex_p1);
		}
		
	}
}
