#pragma once

#include <cstddef>			// std::size_t
#include <iterator>			// std::data(), std::size(), std::reverse_iterator
#include <memory>			// std::pointer_traits, std::addressof()
#include <stdexcept>		// std::out_of_range
#include <type_traits>		// std::remove_cv_t


namespace tc {

	/*
		Class forward declarations
	*/

	template<
		typename T
	>
	class array_view;



	/*
		Class definitions
	*/

	// Non-owning view of a contiguous array.
	template<
		typename T
	>
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
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		
		/* Special members */
		
		// Destructor.
		~array_view
		() = default;

		// Default constructor.
		array_view
		() :
			_pointer(nullptr),
			_size(0)
		{}

		// Copy constructor.
		array_view
		(
			array_view const&
		) = default;
		
		// Move constructor.
		array_view
		(
			array_view&&
		) = default;

		// Constructor from pointer to array and size.
		array_view
		(
			pointer pointer,
			size_type size
		) :
			_pointer(pointer),
			_size(size)
		{}
		
		// Constructor from contiguous iterator range.
		template<
			typename ContiguousIterator
		>
		array_view
		(
			ContiguousIterator begin,
			ContiguousIterator end
		) :
			_size(end - begin)
		{
			if(_size == 0) {
				_pointer = nullptr;
			}
			else {
				_pointer = std::addressof(*begin);
			}
		}

		// Constructor from generic contiguous container.
		template<
			class Container
		>
		array_view
		(
			Container& container
		) :
			_pointer(std::data(container)),
			_size(std::size(container))
		{}


		/* Operators */
		
		// Simple assignment - copy.
		array_view& operator=
		(
			array_view const&
		) = default;
		
		// Simple assignment - move.
		array_view& operator=
		(
			array_view&&
		) = default;

		// Subscript - unchecked element access.
		reference operator[]
		(
			size_type index
		) const
		{
			return _pointer[index];
		}
		
		
		/* General member functions */

		// Bounds checked element access.
		reference at
		(
			size_type index
		) const
		{
			if (index >= _size) {
				throw std::out_of_range("Specified index out of bounds.");
			}
			return _pointer[index];
		}

		// Accesses the last element of the view.
		reference back
		() const
		{
			return _pointer[_size - 1];
		}

		// Gets an iterator to the beginning of the view.
		iterator begin
		() const
		{
			return _pointer;
		}

		// Gets a read-only iterator to the beginning of the view.
		const_iterator cbegin
		() const
		{
			return _pointer;
		}

		// Gets a read-only iterator to the element following the last element of the view.
		const_iterator cend
		() const
		{
			return _pointer + _size;
		}

		// Gets a read-only reverse iterator to the beginning of the reversed view.
		const_reverse_iterator crbegin
		() const
		{
			// std::reverse_iterator constructor is explicit
			return const_reverse_iterator{ this->cend() };
		}

		// Gets a read-only reverse iterator to the end of the reversed view.
		const_reverse_iterator crend
		() const
		{
			// std::reverse_iterator constructor is explicit
			return const_reverse_iterator{ this->cbegin() };
		}

		// Gets a pointer to the viewed array data
		pointer data
		() const
		{
			return _pointer;
		}

		// Checks if the view's size is 0.
		bool empty
		() const
		{
			return _size == 0;
		}

		// Gets an iterator to the element following the last element of the view.
		iterator end
		() const
		{
			return _pointer + _size;
		}

		// Accesses the first element of the view.
		reference front
		() const
		{
			return _pointer[0];
		}

		// Gets a reverse iterator to the beginning of the reversed view.
		reverse_iterator rbegin
		() const
		{
			// std::reverse_iterator constructor is explicit
			return reverse_iterator{ this->end() };
		}

		// Gets a reverse iterator to the end of the reversed view.
		reverse_iterator rend
		() const
		{
			// std::reverse_iterator constructor is explicit
			return reverse_iterator{ this->begin() };
		}


		// Shrinks the viewed data area from the back.
		void shrink_back
		(
			size_type count
		)
		{
			_size -= count;
		}

		// Shrinks the viewed data area from the front.
		void shrink_front
		(
			size_type count
		)
		{
			_pointer += count;
			_size -= count;
		}

		// Size getter.
		size_type size
		() const
		{
			return _size;
		}


	private:

		/* Member variables */

		// Pointer to the first element of the viewed array data.
		pointer _pointer;

		// Number of elements to view.
		size_type _size;

	};

}
