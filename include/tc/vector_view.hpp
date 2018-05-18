#pragma once

#include <cstddef>				// std::size_t
#include <iterator>				// std::data, std::size
#include <memory>				// std::pointer_traits, std::addressof
#include <stdexcept>			// std::out_of_range
#include <type_traits>			// std::remove_cv_t


namespace tc {

	/* Non-owning view of a contiguous array for use as a mathematical vector.
		Element access is 1-indexed. */
	template<typename T>
	class vector_view {
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
		~vector_view() = default;

		// Default constructor.
		vector_view() = default;
		
		// Copy constructor.
		vector_view(vector_view const&) = default;
		
		// Move constructor.
		vector_view(vector_view&&) = default;

		// Constructor from pointer to array and size.
		vector_view(pointer pointer, size_type size) :
			_data{pointer},
			_size{size}
		{}
		
		// Constructor from contiguous iterator range.
		template<typename ContiguousIterator>
		vector_view(ContiguousIterator begin, ContiguousIterator end) :
			_size(end - begin)
		{
			/* Need to handle a range such as [container.end(), container.end()).
				Valid, but taking the address of the end iterator will probably be UB. 
				So instead use a nullptr. */
			if(_size == 0) {
				_data = nullptr;
			}
			else {
				_data = std::addressof(*begin);
			}
		}

		// Constructor from generic contiguous container.
		template<class Container>
		vector_view(Container& container) :
			_data{std::data(container)},
			_size{std::size(container)}
		{}

		
		/* Operators */

		// Simple assignment - copy.
		vector_view& operator=(vector_view const&) = default;
		
		// Simple assignment - move.
		vector_view& operator=(vector_view&&) = default;

		// Function call - unchecked element access.
		reference operator()(size_type index) const
		{
			return _data[index - 1];
		}

		
		/* General member functions */

		// Bounds checked element access.
		reference at(size_type index) const
		{
			if (index < 1 || index >= _size) {
				throw std::out_of_range{"Specified index out of bounds."};
			}
			return operator()(index);
		}

		// Gets a pointer to the start of the viewed array.
		pointer data() const
		{
			return _data;
		}

		// Size getter.
		size_type size()
		{
			return _size;
		}


	private:

		/* Member variables */

		// Pointer to viewed array data.
		pointer _data;
		
		// Number of viewed elements.
		size_type _size;
	};

}
