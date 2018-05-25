#pragma once

#include <cstddef>			// std::size_t


namespace tc {
	namespace matrix_ops {

		// Matrix elementwise copy.
		template<typename SizeType = std::size_t, class InputMatrix, class OutputMatrix>
		void m_cpy(InputMatrix& in, OutputMatrix& out)
		{
			for (SizeType i = 1; i <= in.rows(); ++i) {
				for (SizeType j = 1; j <= in.columns(); ++j) {
					out(i, j) = in(i, j);
				}
			}
		}

		// Sets all matrix elements to a value.
		template<typename SizeType = std::size_t, class OutputMatrix, typename Element>
		void m_fill(OutputMatrix& matrix, Element const& val)
		{
			for (SizeType i = 1; i <= matrix.rows(); ++i) {
				for (SizeType j = 1; j <= matrix.columns(); ++j) {
					matrix(i ,j) = val;
				}
			}
		}

		// Transforms each matrix element with a function.
		template<typename SizeType = std::size_t, class InputMatrix, class OutputMatrix, typename Function>
		void m_fn(InputMatrix& in, OutputMatrix& result, Function function)
		{
			for (SizeType i = 1; i <= in.rows(); ++i) {
				for (SizeType j = 1; j <= in.columns(); ++j) {
					result(i, j) = function(in(i, j));
				}
			}
		}

		/* Matrix transposition.
			Does not work for in place transposition. */
		template<typename SizeType = std::size_t, class InputMatrix, class OutputMatrix>
		void m_trn(InputMatrix& in, OutputMatrix& result)
		{
			for (SizeType i = 1; i <= in.rows(); ++i) {
				for (SizeType j = 1; j <= in.columns(); ++j) {
					result(j, i) = in(i, j);
				}
			}
		}

		// Matrix-matrix elementwise addition.
		template<typename SizeType = std::size_t, class InputMatrix1, class InputMatrix2, class OutputMatrix>
		void mm_add(InputMatrix1& lhs, InputMatrix2& rhs, OutputMatrix& result)
		{
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i, j) = lhs(i, j) + rhs(i, j);
				}
			}
		}

		// Matrix-matrix Hadamard (elementwise) product.
		template<typename SizeType = std::size_t, class InputMatrix1, class InputMatrix2, class OutputMatrix>
		void mm_hprod(InputMatrix1& lhs, InputMatrix2& rhs, OutputMatrix& result)
		{
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i, j) = lhs(i, j) * rhs(i, j);
				}
			}
		}

		// Matrix-matrix multiplication.
		template<typename SizeType = std::size_t, class InputMatrix1, class InputMatrix2, class OutputMatrix>
		void mm_mul(InputMatrix1& lhs, InputMatrix2& rhs, OutputMatrix& result)
		{
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				for (SizeType j = 1; j <= rhs.columns(); ++j) {
					result(i, j) = OutputMatrix::value_type{};
					for (SizeType k = 1; k <= lhs.columns(); ++k) {
						result(i, j) += lhs(i, k) * rhs(k, j)
					}
				}
			}
		}

		// Matrix-matrix elementwise subtraction.
		template<typename SizeType = std::size_t, class InputMatrix1, class InputMatrix2, class OutputMatrix>
		void mm_sub(InputMatrix1& lhs, InputMatrix2& rhs, OutputMatrix& result)
		{
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i, j) = lhs(i, j) - rhs(i, j);
				}
			}
		}

		// Matrix-scalar elementwise multiplication.
		template<typename SizeType = std::size_t, class InputMatrix, typename Element, class OutputMatrix>
		void ms_mul(InputMatrix& lhs, Element const& rhs, OutputMatrix& result)
		{
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i, j) = lhs(i, j) * rhs;
				}
			}
		}

		// Scalar-matrix elementwise multiplication.
		template<typename SizeType = std::size_t, typename Element, class InputMatrix, class OutputMatrix>
		void sm_mul(Element lhs, InputMatrix& rhs, OutputMatrix& result)
		{
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i, j) = lhs * rhs(i, j);
				}
			}
		}
		
	}
}
