#pragma once

#include <cstddef>			// std::size_t


namespace tc {

	/*
		Function definitions
	*/
	
	/* Hybrid operations */

	// Matrix-vector multiplication (matrix by column vector).
	template<class InputMatrix, class InputVector, class OutputVector, typename SizeType = std::size_t>
	void mv_mul(InputMatrix& lhs, InputVector& rhs, OutputVector& result)
	{
		for (SizeType i = 0; i < lhs.rows(); ++i) {
			result(i) = OutputVector::value_type{};

			for (SizeType j = 0; j < lhs.columns(); ++j) {
				result(i) += lhs(i, j) * rhs(j);
			}
		}
	}

	// Vector-matrix multiplication (row vector by matrix).
	template<class InputVector, class InputMatrix, class OutputVector, typename SizeType = std::size_t>
	void vm_mul(InputVector& lhs, InputMatrix& rhs, OutputVector& result)
	{
		for (SizeType j = 0; j < rhs.columns(); ++j) {
			result(j) = OutputVector::value_type{};

			for (SizeType i = 0; i < lhs.size(); ++i) {
				result(j) += lhs(i) * rhs(i, j);
			}
		}
	}

}
