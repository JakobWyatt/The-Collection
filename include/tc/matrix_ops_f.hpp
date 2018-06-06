#pragma once

#ifdef _DEBUG
	#include <cassert>		// assert
#endif
#include <cstddef>			// std::size_t
#include <algorithm>		// std::transform, std::copy, std::fill
#include <execution>		// std::execution::par_unseq
#include <functional>		// std::plus

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
			
			std::copy(std::execution::par_unseq, in.data(), in.data() + in.size(), out.data());
		}
		
		// Sets all matrix elements to a value.
		template<typename SizeType = std::size_t, class OutputMatrix, typename Element>
		void m_fill(OutputMatrix& matrix, Element const& val)
		{
			std::fill(std::execution::par_unseq, matrix.data(), matrix.data() + matrix.size(), val);
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
		
		// Matrix-matrix elementwise addition.
		template<typename SizeType = std::size_t, class InputMatrix1, class InputMatrix2, class OutputMatrix>
		void mm_add(InputMatrix1 const& lhs, InputMatrix2 const& rhs, OutputMatrix& result)
		{
			#ifdef _DEBUG
				assert(lhs.rows() == rhs.rows());
				assert(lhs.columns() == rhs.columns());
				assert(lhs.rows() == result.rows());
				assert(lhs.columns() == result.columns());
			#endif
			
			std::transform(std::execution::par_unseq, lhs.data(), lhs.data() + lhs.size(), rhs.data(), result.data(), std::plus());
		}

		// Matrix-matrix Hadamard (elementwise) product.
		template<typename SizeType = std::size_t, class InputMatrix1, class InputMatrix2, class OutputMatrix>
		void mm_hprod(InputMatrix1 const& lhs, InputMatrix2 const& rhs, OutputMatrix& result)
		{
			#ifdef _DEBUG
				assert(lhs.rows() == rhs.rows());
				assert(lhs.columns() == rhs.columns());
				assert(lhs.rows() == result.rows());
				assert(lhs.columns() == result.columns());
			#endif
			
			std::transform(std::execution::par_unseq, lhs.data(), lhs.data() + lhs.size(), rhs.data(), result.data(), std::multiplies());
		}

	}
}
