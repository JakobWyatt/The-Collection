#pragma once

#include <cstddef>			// std::size_t


namespace tc {
	namespace mv_ops {

		// Matrix-vector multiplication (matrix by column vector).
		template<typename SizeType = std::size_t, class InputMatrix, class InputVector, class OutputVector>
		void mv_mul(InputMatrix& lhs, InputVector& rhs, OutputVector& result)
		{
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				result(i) = OutputVector::value_type{};

				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i) += lhs(i, j) * rhs(j);
				}
			}
		}

		// Vector-matrix multiplication (row vector by matrix).
		template<typename SizeType = std::size_t, class InputVector, class InputMatrix, class OutputVector>
		void vm_mul(InputVector& lhs, InputMatrix& rhs, OutputVector& result)
		{
			for (SizeType j = 1; j <= rhs.columns(); ++j) {
				result(j) = OutputVector::value_type{};

				for (SizeType i = 1; i <= lhs.size(); ++i) {
					result(j) += lhs(i) * rhs(i, j);
				}
			}
		}

	}
}
