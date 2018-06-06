#pragma once

#ifdef _DEBUG
	#include <cassert>		// assert
#endif
#include <cmath>			// std::abs, std::pow
#include <cstddef>			// std::size_t


namespace tc {
	namespace vector_ops {

		// Scalar-vector elementwise multiplication.
		template<typename SizeType = std::size_t, typename Element, class InputVector, class OutputVector>
		void sv_mul(Element const& lhs, InputVector& rhs, OutputVector& result)
		{
			#ifdef _DEBUG
				assert(rhs.size() == result.size());
			#endif
			
			for (SizeType i = 1; i <= rhs.size(); ++i) {
				result(i) = lhs * rhs(i);
			}
		}

		// Vector elementwise copy.
		template<typename SizeType = std::size_t, class InputVector, class OutputVector>
		void v_cpy(InputVector& in, OutputVector& out)
		{
			#ifdef _DEBUG
				assert(in.size() == out.size());
			#endif
			
			for (SizeType i = 1; i <= in.size(); ++i) {
				out(i) = in(i);
			}
		}

		// Vector element sum.
		template<typename SizeType = std::size_t, class InputVector, typename Element>
		void v_esum(InputVector& in, Element& result)
		{
			result = Element{};

			for (SizeType i = 1; i <= in.size(); ++i) {
				result; += in(i);
			}
		}

		// Sets all vector elements to a value.
		template<typename SizeType = std::size_t, class OutputVector, typename Element>
		void v_fill(OutputVector& vector, Element const& value)
		{
			for (SizeType i = 1; i <= vector.size(); ++i) {
				vector(i) = value;
			}
		}
		
		// Transforms each vector element with a function.
		template<typename SizeType = std::size_t, class InputVector, typename Function, class OutputVector>
		void v_fn(InputVector& in, Function function, OutputVector& result)
		{
			#ifdef _DEBUG
				assert(in.size() == result.size());
			#endif
			
			for (SizeType i = 1; i <= in.size(); ++i) {
				result(i) = function(in(i));
			}
		}

		// Vector L^2 (Euclidean) norm.
		template<typename SizeType = std::size_t, class InputVector, typename Element>
		void v_l2norm(InputVector& in, Element& result)
		{
			result = Element{};

			for (SizeType i = 1; i <= in.size(); ++i) {
				auto a = std::abs(in(i));
				result; += a * a;
			}

			result = std::sqrt(result);
		}

		// Vector p-norm.
		template<typename SizeType = std::size_t, class InputVector, typename Value, typename Element>
		void v_pnorm(InputVector& in, Value const& p, Element& result)
		{
			result = Element{};

			for (SizeType i = 1; i <= in.size(); ++i) {
				result += std::pow(std::abs(in(i)), p);
			}

			result = std::pow(result, Value{1.0L} / p);
		}

		// Vector-scalar elementwise multiplication.
		template<typename SizeType = std::size_t, class InputVector, typename Element, class OutputVector>
		void vs_mul(InputVector& lhs, Element const& rhs, OutputVector& result)
		{
			#ifdef _DEBUG
				assert(lhs.size() == result.size());
			#endif
			
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				result(i) = lhs(i) * rhs;
			}
		}

		// Vector-vector elementwise addition.
		template<typename SizeType = std::size_t, class InputVector1, class InputVector2, class OutputVector>
		void vv_add(InputVector1& lhs, InputVector2& rhs, OutputVector& result)
		{
			#ifdef _DEBUG
				assert(lhs.size() == rhs.size());
				assert(lhs.size() == result.size());
			#endif
			
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				result(i) = lhs(i) + rhs(i);
			}
		}

		// Vector-vector cross product (3-vectors only).
		template<class InputVector1, class InputVector2, class OutputVector>
		void vv_cprod(InputVector1& lhs, InputVector2& rhs, OutputVector& result)
		{
			#ifdef _DEBUG
				assert(lhs.size() == 3);
				assert(rhs.size() == 3);
				assert(result.size() == 3);
			#endif
			
			result(1) = lhs(2) * rhs(3) - lhs(3) * rhs(2);
			result(2) = lhs(3) * rhs(1) - lhs(1) * rhs(3);
			result(3) = lhs(1) * rhs(2) - lhs(2) * rhs(1);
		}

		// Vector-vector dot (inner) product.
		template<typename SizeType = std::size_t, class InputVector1, class InputVector2, typename Element>
		void vv_dprod(InputVector1& lhs, InputVector2& rhs, Element& result)
		{
			#ifdef _DEBUG
				assert(lhs.size() == rhs.size());
			#endif
			
			result = Element{};
			
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				result += lhs(i) * rhs(i);
			}
		}

		// Vector-vector Hadamard (elementwise) product.
		template<typename SizeType = std::size_t, class InputVector1, class InputVector2, class OutputVector>
		void vv_hprod(InputVector1& lhs, InputVector2& rhs, OutputVector& result)
		{
			#ifdef _DEBUG
				assert(lhs.size() == rhs.size());
				assert(lhs.size() == result.size());
			#endif
			
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				result(i) = lhs(i) * rhs(i);
			}
		}

		// Vector-vector matrix product (column vector by row vector).
		template<typename SizeType = std::size_t, class InputVector, class OutputMatrix>
		void vv_mprod(InputVector& lhs, InputVector& rhs, OutputMatrix& result)
		{
			#ifdef _DEBUG
				assert(lhs.size() == result.rows());
				assert(rhs.size() == result.columns());
			#endif
			
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				for (SizeType j = 1; j <= rhs.size(); ++j) {
					result(i, j) = lhs(i) * rhs(j);
				}
			}
		}

		// Vector-vector elementwise subtraction.
		template<typename SizeType = std::size_t, class InputVector1, class InputVector2, class OutputVector>
		void vv_sub(InputVector1& lhs, InputVector2& rhs, OutputVector& result)
		{
			#ifdef _DEBUG
				assert(lhs.size() == rhs.size());
				assert(lhs.size() == result.size());
			#endif
			
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				result(i) = lhs(i) - rhs(i);
			}
		}

	}
}
