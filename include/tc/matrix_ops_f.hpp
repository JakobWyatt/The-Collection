#pragma once

#ifdef _DEBUG
	#include <cassert>		// assert
#endif
#include <cstddef>			// std::size_t
#include <algorithm>		// std::transform, std::copy
#include <execution>		// std::execution::par_unseq

namespace tc {
	namespace matrix_ops_f {
		
		// Matrix elementwise copy.
		template<typename SizeType = std::size_t, class InputMatrix, class OutputMatrix>
		void m_cpy(InputMatrix const& in, OutputMatrix& out)
		{
			#ifdef _DEBUG
				assert(in.rows() == out.rows());
				assert(in.columns() == out.columns());
			#endif
			
			std::copy(std::excecution::par_unseq, in.data(), in.data() + in.size(), out.data());
		}
		
		// Transforms each matrix element with a function.
		template<typename SizeType = std::size_t, class InputMatrix, class OutputMatrix, typename Function>
		void m_fn(InputMatrix const& in, OutputMatrix& result, Function function)
		{
			#ifdef _DEBUG
				assert(in.rows() == result.rows());
				assert(in.columns() == result.columns());
			#endif
			
			std::transform(std::execution::par_unseq, in.data(), in.data() + in.size(), result.data(), function);
		}
		
	}
}
