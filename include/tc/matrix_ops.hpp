#pragma once

#ifdef _DEBUG
	#include <cassert>		// assert
#endif
#include <cstddef>			// std::size_t


namespace tc {
	namespace matrix_ops {

		// Matrix elementwise copy.
		template<typename SizeType = std::size_t, class InputMatrix, class OutputMatrix>
		void m_cpy(InputMatrix const& in, OutputMatrix& out)
		{
			#ifdef _DEBUG
				assert(in.rows() == out.rows());
				assert(in.columns() == out.columns());
			#endif
			
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
		void m_fn(InputMatrix const& in, OutputMatrix& result, Function function)
		{
			#ifdef _DEBUG
				assert(in.rows() == result.rows());
				assert(in.columns() == result.columns());
			#endif
			
			for (SizeType i = 1; i <= in.rows(); ++i) {
				for (SizeType j = 1; j <= in.columns(); ++j) {
					result(i, j) = function(in(i, j));
				}
			}
		}

		/* Matrix transposition.
			`in` must not refer to the same data as `result`, ie in-place transposition is not supported. */
		template<typename SizeType = std::size_t, class InputMatrix, class OutputMatrix>
		void m_trn(InputMatrix const& in, OutputMatrix& result)
		{
			#ifdef _DEBUG
				assert(in.rows() == result.rows());
				assert(in.columns() == result.columns());
			#endif
			
			for (SizeType i = 1; i <= in.rows(); ++i) {
				for (SizeType j = 1; j <= in.columns(); ++j) {
					result(j, i) = in(i, j);
				}
			}
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
			
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i, j) = lhs(i, j) + rhs(i, j);
				}
			}
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
			
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i, j) = lhs(i, j) * rhs(i, j);
				}
			}
		}

		// Matrix-matrix multiplication.
		template<typename SizeType = std::size_t, class InputMatrix1, class InputMatrix2, class OutputMatrix>
		void mm_mul(InputMatrix1 const& lhs, InputMatrix2 const& rhs, OutputMatrix& result)
		{
			#ifdef _DEBUG
				assert(lhs.columns() == rhs.rows());
				assert(lhs.rows() == result.rows());
				assert(rhs.columns() == result.columns());
			#endif
			
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
		void mm_sub(InputMatrix1 const& lhs, InputMatrix2 const& rhs, OutputMatrix& result)
		{
			#ifdef _DEBUG
				assert(lhs.rows() == rhs.rows());
				assert(lhs.columns() == rhs.columns());
				assert(lhs.rows() == result.rows());
				assert(lhs.columns() == result.columns());
			#endif
			
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i, j) = lhs(i, j) - rhs(i, j);
				}
			}
		}

		// Matrix-scalar elementwise multiplication.
		template<typename SizeType = std::size_t, class InputMatrix, typename Element, class OutputMatrix>
		void ms_mul(InputMatrix const& lhs, Element const& rhs, OutputMatrix& result)
		{
			#ifdef _DEBUG
				assert(lhs.rows() == result.rows());
				assert(lhs.columns() == result.columns());
			#endif
			
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i, j) = lhs(i, j) * rhs;
				}
			}
		}

		// Scalar-matrix elementwise multiplication.
		template<typename SizeType = std::size_t, typename Element, class InputMatrix, class OutputMatrix>
		void sm_mul(Element const& lhs, InputMatrix const& rhs, OutputMatrix& result)
		{
			#ifdef _DEBUG
				assert(rhs.rows() == result.rows());
				assert(rhs.columns() == result.columns());
			#endif
			
			for (SizeType i = 1; i <= lhs.rows(); ++i) {
				for (SizeType j = 1; j <= lhs.columns(); ++j) {
					result(i, j) = lhs * rhs(i, j);
				}
			}
		}
		
	}
}
