#pragma once

#ifdef _DEBUG
	#include <cassert>		// assert
#endif
#include <cstddef>			// std::size_t


namespace tc {
	namespace mv_ops {

		// Matrix-vector multiplication (matrix by column vector).
		template<typename SizeType = std::size_t, class InputMatrix, class InputVector, class OutputVector>
		void mv_mul(InputMatrix& lhs, InputVector& rhs, OutputVector& result)
		{
			#ifdef _DEBUG
				assert(lhs.columns() == rhs.size());
				assert(lhs.rows() == result.size());
			#endif
			
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				result(i) = OutputVector::value_type{};

				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i) += lhs(i, j) * rhs(j);
				}
			}
		}
		
		// Matrix-vector multiplication (matrix by column vector) (matrix transposed).
		template<typename SizeType = std::size_t, class InputMatrix, class InputVector, class OutputVector>
		void mv_tmul(InputMatrix& lhs, InputVector& rhs, OutputVector& result)
		{
			#ifdef _DEBUG
				assert(lhs.rows() == rhs.size());
				assert(lhs.columns() == result.size());
			#endif
			
			for (SizeType j = 1; j <= lhs.columns(); ++j) {
				result(j) = OutputVector::value_type{};
				
				for (SizeType i = 1; i <= lhs.rows(); ++i) {
					result(j) += lhs(i, j) * rhs(i);
				}
			}
		}

		// Vector-matrix multiplication (row vector by matrix).
		template<typename SizeType = std::size_t, class InputVector, class InputMatrix, class OutputVector>
		void vm_mul(InputVector& lhs, InputMatrix& rhs, OutputVector& result)
		{
			#ifdef _DEBUG
				assert(lhs.size() == rhs.rows());
				assert(rhs.columns() == result.size());
			#endif
			
			for (SizeType j = 1; j <= rhs.columns(); ++j) {
				result(j) = OutputVector::value_type{};

				for (SizeType i = 1; i <= lhs.size(); ++i) {
					result(j) += lhs(i) * rhs(i, j);
				}
			}
		}

	}
}
