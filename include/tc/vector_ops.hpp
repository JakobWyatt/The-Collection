#pragma once

#include <cmath>			// std::abs, std::pow
#include <cstddef>			// std::size_t


namespace tc {
	namespace vector_ops {

		// Scalar-vector elementwise multiplication.
		template<typename Element, class InputVector, class OutputVector, typename SizeType = std::size_t>
		void sv_mul(Element const& lhs, InputVector& rhs, OutputVector& result)
		{
			for (SizeType i = 1; i <= rhs.size(); ++i) {
				result(i) = lhs * rhs(i);
			}
		}

		// Vector elementwise copy.
		template<class InputVector, class OutputVector, typename SizeType = std::size_t>
		void v_cpy(InputVector& in, OutputVector& out)
		{
			for (SizeType i = 1; i <= in.size(); ++i) {
				out(i) = in(i);
			}
		}

		// Vector element sum.
		template<class InputVector, typename Element, typename SizeType = std::size_t>
		void v_esum(InputVector& in, Element& result)
		{
			result = Element{};

			for (SizeType i = 1; i <= in.size(); ++i) {
				result += in(i);
			}
		}

		// Sets all vector elements to a value.
		template<class OutputVector, typename Element, typename SizeType = std::size_t>
		void v_fill(OutputVector& vector, Element const& value)
		{
			for (SizeType i = 1; i <= vector.size(); ++i) {
				vector(i) = value;
			}
		}
		
		// Transforms each vector element with a function.
		template<class InputVector, class OutputVector, typename Function, typename SizeType = std::size_t>
		void v_fn(InputVector& in, OutputVector& result, Function function)
		{
			for (SizeType i = 1; i <= in.size(); ++i) {
				result(i) = function(in(i));
			}
		}

		// Vector L^2 (Euclidean) norm.
		template<class InputVector, typename Element, typename SizeType = std::size_t>
		void v_l2norm(InputVector& in, Element& result)
		{
			result = Element{};

			for (SizeType i = 1; i <= in.size(); ++i) {
				auto a = std::abs(in(i));
				result += a * a;
			}

			result = std::sqrt(result);
		}

		// Vector p-norm.
		template<class InputVector, typename Value, typename Element, typename SizeType = std::size_t>
		void v_pnorm(InputVector& in, Value const& p, Element& result)
		{
			result = Element{};

			for (SizeType i = 1; i <= in.size(); ++i) {
				result += std::pow(std::abs(in(i)), p);
			}

			result = std::pow(result, Value{1.0L} / p);
		}

		// Vector-scalar elementwise multiplication.
		template<class InputVector, typename Element, class OutputVector, typename SizeType = std::size_t>
		void vs_mul(InputVector& lhs, Element const& rhs, OutputVector& result)
		{
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				result(i) = lhs(i) * rhs;
			}
		}

		// Vector-vector elementwise addition.
		template<class InputVector1, class InputVector2, class OutputVector, typename SizeType = std::size_t>
		void vv_add(InputVector1& lhs, InputVector2& rhs, OutputVector& result)
		{
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				result(i) = lhs(i) + rhs(i);
			}
		}

		// Vector-vector cross product (3-vectors only).
		template<class InputVector1, class InputVector2, class OutputVector>
		void vv_cprod(InputVector1& lhs, InputVector2& rhs, OutputVector result)
		{
			result(1) = lhs(2) * rhs(3) - lhs(3) * rhs(2);
			result(2) = lhs(3) * rhs(1) - lhs(1) * rhs(3);
			result(3) = lhs(1) * rhs(2) - lhs(2) * rhs(1);
		}

		// Vector-vector dot (inner) product.
		template<class InputVector1, class InputVector2, typename Element, typename SizeType = std::size_t>
		void vv_dprod(InputVector1& lhs, InputVector2& rhs, Element& result)
		{
			result = Element{};
			
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				result += lhs(i) * rhs(i);
			}
		}

		// Vector-vector Hadamard (elementwise) product.
		template<class InputVector1, class InputVector2, class OutputVector, typename SizeType = std::size_t>
		void vv_hprod(InputVector1& lhs, InputVector2& rhs, OutputVector& result)
		{
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				result(i) = lhs(i) * rhs(i);
			}
		}

		// Vector-vector matrix product (column vector by row vector).
		template<class InputVector, class OutputMatrix, typename SizeType = std::size_t>
		void vv_mprod(InputVector& lhs, InputVector& rhs, OutputMatrix& result)
		{
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				for (SizeType j = 1; j <= rhs.size(); ++j) {
					result(i, j) = lhs(i) * rhs(j);
				}
			}
		}

		// Vector-vector elementwise subtraction.
		template<class InputVector1, class InputVector2, class OutputVector, typename SizeType = std::size_t>
		void vv_sub(InputVector1& lhs, InputVector2& rhs, OutputVector& result)
		{
			for (SizeType i = 1; i <= lhs.size(); ++i) {
				result(i) = lhs(i) - rhs(i);
			}
		}

	}
}
