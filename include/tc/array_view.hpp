#pragma once

#include <algorithm>		// std::copy_n
#include <array>			// std::array
#ifdef _DEBUG
	#include <cassert>		// assert
#endif
#include <cstddef>			// std::size_t
#include <memory>			// std::pointer_traits
#include <stdexcept>		// std::out_of_range
#include <type_traits>		// std::remove_cv_t, std::enable_if_t


namespace tc {
	namespace array_view {

		// N-dimensional dimension sizes.
		template<std::size_t N, typename DimensionType = std::size_t>
		using dimensions = std::array<DimensionType, N>;

		// N-dimensional indices.
		template<std::size_t N, typename IndexType = std::size_t>
		using indices = std::array<IndexType, N>;

		/* Converts a set of N-dimensional set of dimensions and indices to a simple offset.
			Bounds checked for debug builds.
			Implementation for N > 4. */
		template<std::size_t N, typename SizeType = std::size_t>
		inline std::enable_if_t<(N > 4), SizeType> multidim_indices_offset
			(dimensions<N, SizeType> const& dims, indices<N, SizeType> const& idx)
		{
			#ifdef _DEBUG
				for (SizeType i = 0; i < N; ++i) {
					assert(idx[i] < dims[i]);
				}
			#endif
			
			SizeType offset = idx[N - 1];
			SizeType dim_size = 1;

			for (std::size_t i = N - 1; i > 0; --i) {
				dim_size *= dims[i];
				offset += idx[i - 1] * dim_size;
			}

			return offset;
		}

		/* Converts a set of N-dimensional set of dimensions and indices to a simple offset.
			Bounds checked for debug builds.
			Efficient implementation for N == 1. */
		template<std::size_t N, typename SizeType = std::size_t>
		inline std::enable_if_t<N == 1, SizeType> multidim_indices_offset
			(dimensions<N, SizeType> const& dims, indices<N, SizeType> const& idx)
		{
			#ifdef _DEBUG
				assert(idx[0] < dims[0]);
			#endif
			
			return idx[0];
		}

		/* Converts a set of N-dimensional set of dimensions and indices to a simple offset.
			Bounds checked for debug builds.
			Efficient implementation for N == 2. */
		template<std::size_t N, typename SizeType = std::size_t>
		inline std::enable_if_t<N == 2, SizeType> multidim_indices_offset
			(dimensions<N, SizeType> const& dims, indices<N, SizeType> const& idx)
		{
			#ifdef _DEBUG
				assert(idx[0] < dims[0]);
				assert(idx[1] < dims[1]);
			#endif
			
			SizeType offset = idx[1];
			offset += idx[0] * dims[1];

			return offset;
		}

		/* Converts a set of N-dimensional set of dimensions and indices to a simple offset.
			Bounds checked for debug builds.
			Efficient implementation for N == 3. */
		template<std::size_t N, typename SizeType = std::size_t>
		inline std::enable_if_t<N == 3, SizeType> multidim_indices_offset
			(dimensions<N, SizeType> const& dims, indices<N, SizeType> const& idx)
		{
			#ifdef _DEBUG
				assert(idx[0] < dims[0]);
				assert(idx[1] < dims[1]);
				assert(idx[2] < dims[2]);
			#endif
			
			SizeType const dim2_size = dims[2];
			SizeType const dim1_size = dim2_size * dims[1];

			SizeType offset = idx[2];
			offset += idx[1] * dim2_size;
			offset += idx[0] * dim1_size;

			return offset;
		}

		/* Converts a set of N-dimensional set of dimensions and indices to a simple offset.
			Bounds checked for debug builds.
			Efficient implementation for N == 4. */
		template<std::size_t N, typename SizeType = std::size_t>
		inline std::enable_if_t<N == 4, SizeType> multidim_indices_offset
			(dimensions<N, SizeType> const& dims, indices<N, SizeType> const& idx)
		{
			#ifdef _DEBUG
				assert(idx[0] < dims[0]);
				assert(idx[1] < dims[1]);
				assert(idx[2] < dims[2]);
				assert(idx[3] < dims[3]);
			#endif
			
			SizeType const dim3_size = dims[3];
			SizeType const dim2_size = dim3_size * dims[2];
			SizeType const dim1_size = dim2_size * dims[1];

			SizeType offset = idx[3];
			offset += idx[2] * dim3_size;
			offset += idx[1] * dim2_size;
			offset += idx[0] * dim1_size;

			return offset;
		}

		/* Non-owning view of an N-dimensional array.
			Efficient element access specialisations for N == 1, 2, 3, 4.
			N == 0 is dynamic dimensionality. */
		template<typename T, std::size_t N>
		class array_view {
		public:

			/* Member type aliases */
		
			using element_type = T;
			using value_type = std::remove_cv_t<element_type>;
			using size_type = std::size_t;
			using reference = element_type&;
			using const_reference = element_type const&;
			using pointer = element_type*;
			using const_pointer = element_type const*;
			using difference_type = typename std::pointer_traits<pointer>::difference_type;


			/* Special members */

			// Destructor.
			~array_view() = default;

			// Default constructor.
			array_view() :
				_dims{}
			{}

			// Copy constructor.
			array_view(array_view const&) = default;

			// Move constructor.
			array_view(array_view&&) = default;

			/* Constructor from pointer to array and dimensions parameter pack.
				Dimensions must be convertible to size_type. */
			template<typename... Dimensions>
			explicit array_view(
				std::enable_if_t<sizeof...(Dimensions) == N, pointer> array,
				Dimensions... dimensions
			) :
				_view{array},
				_dims{static_cast<size_type>(dimensions)...}
			{}

			// Constructor from pointer to array and dimensions type.
			array_view(pointer array, dimensions<N, size_type> const& dimensions) :
				_view{array},
				_dims{dimensions}
			{}


			/* Operators */

			// Simple assignment - copy.
			array_view& operator=(array_view const&) = default;

			// Simple assignment - move.
			array_view& operator=(array_view&&) = default;

			/* Subscript - dimension access.
				Same as operator() for N == 1.
				Otherwise, returns the specified dimension as a new array_view. 
				Bounds checked for debug builds. */
			std::conditional_t<N == 1, reference, array_view<T, N - 1>> operator[](size_type index) const
			{
				if constexpr (N == 1) {
					return operator()(index);
				}
				else {
					#ifdef _DEBUG
						assert(index < _dims[0]);
					#endif
					
					size_type dim0_size = 1;

					for (size_type i = N - 1; i > 0; --i) {
						dim0_size *= _dims[i];
					}

					pointer new_pointer = _view.data() + (dim0_size * index);

					dimensions<N - 1, size_type> new_dims{};
					std::copy(_dims.cbegin() + 1, _dims.cend(), new_dims.begin());

					return {new_pointer, new_dims};
				}
			}

			/* Function call - element access.
				Uses array_view<T, 0>::operator().*/
			template<typename... Indices>
			inline reference operator()(Indices... idx) const
			{
				return _view(_dims, idx...);
			}


			/* General member functions */

			// Pointer to array.
			pointer data() const
			{
				return _view.data();
			}

			/* Size of the specified dimension (zero-indexed).
				Bounds checked for debug builds. */
			size_type dim_size(size_type d) const
			{
				#ifdef _DEBUG
					assert(d < N);
				#endif
				
				return _dims[d];
			}

			// Total number of viewed elements.
			size_type size() const
			{
				size_type s = 1;

				for (auto d : _dims) {
					s *= d;
				}

				return s;
			}


		private:

			/* Member variables */

			// Underlying dynamic array view.
			array_view<T, 0> _view;

			// Dimensions of the view, from outermost to innermost.
			dimensions<N, size_type> _dims;
		};

		// array_view specialisation for N == 0 - dynamic dimensions.
		template<typename T>
		class array_view<T, 0> {
		public:

			/* Member type aliases */

			using element_type = T;
			using value_type = std::remove_cv_t<element_type>;
			using size_type = std::size_t;
			using reference = element_type&;
			using const_reference = element_type const&;
			using pointer = element_type*;
			using const_pointer = element_type const*;
			using difference_type = typename std::pointer_traits<pointer>::difference_type;


			/* Special members */

			// Destructor.
			~array_view() = default;

			// Default constructor.
			array_view() :
				_data{nullptr}
			{}

			// Copy constructor.
			array_view(array_view const&) = default;
			
			// Move constructor.
			array_view(array_view&&) = default;

			// Constructor from pointer to array.
			explicit array_view(pointer array) :
				_data(array) {}


			/* Operators */

			// Simple assignment - copy.
			array_view& operator=(array_view const&) = default;

			// Simple assignment - move.
			array_view& operator=(array_view&&) = default;

			/* Function call - element access.
				Uses multidim_indices_offset. */
			template<typename... Indices>
			inline reference operator()(dimensions<sizeof...(Indices), size_type> const& dims, Indices... idx) const
			{
				indices<sizeof...(Indices), size_type> const idx_arg{static_cast<size_type>(idx)...};

				return _data[multidim_indices_offset<sizeof...(Indices), size_type>(dims, idx_arg)];
			}
			

			/* General member functions */

			// Pointer to array.
			pointer data() const
			{
				return _data;
			}


		private:

			/* Member variables */

			// Pointer to the start of the viewed array.
			pointer _data;
		};

		// Dynamic dimension array_view.
		template<typename T>
		using array_view_dyn = array_view<T, 0>;

		// 1D array_view.
		template<typename T>
		using array_view1d = array_view<T, 1>;

		// 2D array_view.
		template<typename T>
		using array_view2d = array_view<T, 2>;

		// 3D array_view.
		template<typename T>
		using array_view3d = array_view<T, 3>;

		// 4D array_view.
		template<typename T>
		using array_view4d = array_view<T, 4>;
		
	}
}
