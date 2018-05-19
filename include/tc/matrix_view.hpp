#pragma once

#include <cstddef>				// std::size_t
#include <memory>				// std::pointer_traits
#include <stdexcept>			// std::out_of_range
#include <type_traits>			// std::remove_cv_t


namespace tc {

	/* Non-owning view of a contiguous array for use as a mathematical matrix.
		Elements are viewed as row major.
		Element access is 1-indexed. */
	template<typename T>
	class matrix_view {
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
		~matrix_view() = default;

		// Default constructor.
		matrix_view() :
			_data{nullptr},
			_rows{0},
			_columns{0}
		{}

		// Copy constructor.
		matrix_view(matrix_view const&) = default;

		// Move constructor.
		matrix_view(matrix_view&&) = default;

		// Constructor from pointer to array and dimensions.
		matrix_view(pointer data, size_type rows, size_type columns) :
			_data{data},
			_rows{rows},
			_columns{columns}
		{}


		/* Operators */

		// Simple assignment - copy.
		matrix_view& operator=(matrix_view const&) = default;

		// Simple assignment - move.
		matrix_view& operator=(matrix_view&&) = default;

		// Function call - element access.
		reference operator()(size_type row, size_type column) const
		{
			return _data[((row - 1) * _columns) + (column - 1)];
		}

		
		/* General member functions */

		// Bounds checked element access.
		reference at(size_type row, size_type column) const
		{
			if(row < 1 || row >= _rows) {
				throw std::out_of_range{"Specified row out of bounds."};
			}
			if(column < 1 || column >= _columns) {
				throw std::out_of_range{"Specified column out of bounds."};
			}
			
			return operator()(row, column);
		}

		// Gets the number of rows viewed.
		size_type columns() const
		{
			return _columns;
		}

		// Gets the pointer to the start of the array.
		pointer data() const
		{
			return _data;
		}

		// Gets the number of columns viewed.
		size_type rows() const
		{
			return _rows;
		}

		// Gets the total number of viewed elements.
		size_type size() const
		{
			return _rows * _columns;
		}


	private:

		/* Member variables */

		// Pointer to viewed array.
		pointer _data;

		// Number of viewed rows.
		size_type _rows;

		// Number of viewed columns.
		size_type _columns;
	};

}