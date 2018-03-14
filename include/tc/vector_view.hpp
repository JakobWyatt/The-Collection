#pragma once

#include "array_view.hpp"
#include <stdexcept>		// std::out_of_range


namespace tc {

	/*
		Class forward declarations
	*/

	template<
		typename T
	>
	class vector_view;



	/*
		Class definitions
	*/

	/* Non-owning view of a contiguous array for use as a mathematical vector.
		Simply forwards the functionality of `array_view`, except that elements are 1-indexed.
	*/
	template<
		typename T
	>
	class vector_view {
		
	public:
	
		/* Member type aliases */
	
		using value_type = typename array_view<T>::value_type;
		using size_type = typename array_view<T>::size_type;
		using reference = typename array_view<T>::reference;
		using const_reference = typename array_view<T>::const_reference;
		using pointer = typename array_view<T>::pointer;
		using const_pointer = typename array_view<T>::const_pointer;
		using difference_type = typename array_view<T>::difference_type;
		using iterator = typename array_view<T>::iterator;
		using const_iterator = typename array_view<T>::const_iterator;
		using reverse_iterator = typename array_view<T>::reverse_iterator;
		using const_reverse_iterator = typename array_view<T>::const_reverse_iterator;

		
		/* Special members */
		
		// Destructor.
		~vector_view
		() = default;

		// Default constructor.
		vector_view
		() = default;
		
		// Copy constructor.
		vector_view
		(
			vector_view const&
		) = default;

		// Constructor from pointer to array and size.
		vector_view
		(
			pointer pointer,
			size_type size
		) noexcept(noexcept(array_view<T>::array_view(pointer, size))) :
			_array_view(pointer, size)
		{}
		
		// Constructor from contiguous iterator range.
		template<
			typename ContiguousIterator
		>
		vector_view
		(
			ContiguousIterator begin,
			ContiguousIterator end
		) noexcept(noexcept(array_view<T>::array_view(begin, end))) :
			_array_view(begin, end)
		{}

		// Constructor from generic contiguous container.
		template<
			class Container
		>
		vector_view
		(
			Container& container
		) noexcept(noexcept(array_view<T>::array_view(container))) :
			array_view(container)
		{}

		
		/* Operators */

		// Simple assignment operator - copy.
		vector_view& operator=
		(
			vector_view const&
		) = default;
		
		// Simple assignment operator - move.
		vector_view& operator=
		(
			vector_view&&
		) = default;

		// Subscript operator - unchecked element access.
		reference operator[]
		(
			size_type index
		) const noexcept(noexcept(_array_view[index - 1]))
		{
			return _array_view[index - 1];
		}

		
		/* General member functions */

		// Bounds checked element access.
		reference at
		(
			size_type index
		) const
		{
			if (index < 1) {
				throw std::out_of_range("Specified index out of bounds.");
			}
			else {
				return _array_view.at(index - 1);
			}
		}

		// Accesses the last element of the view.
		reference back
		() const noexcept(noexcept(_array_view.back()))
		{
			return _array_view.back();
		}

		// Gets an iterator to the beginning of the view.
		iterator begin
		() const noexcept(noexcept(_array_view.begin()))
		{
			return _array_view.begin();
		}

		// Gets a read-only iterator to the beginning of the view.
		const_iterator cbegin
		() const noexcept(noexcept(_array_view.cbegin()))
		{
			return _array_view.cbegin();
		}

		// Gets a read-only iterator to the element following the last element of the view.
		const_iterator cend
		() const noexcept(noexcept(_array_view.cend()))
		{
			return _array_view.cend();
		}

		// Gets a read-only reverse iterator to the beginning of the reversed view.
		const_reverse_iterator crbegin
		() const noexcept(noexcept(_array_view.crbegin()))
		{
			return _array_view.crbegin();
		}

		// Gets a read-only reverse iterator to the end of the reversed view.
		const_reverse_iterator crend
		() const noexcept(noexcept(_array_view.crend()))
		{
			return _array_view.crend();
		}

		// Gets a pointer to the viewed array data
		pointer data
		() const noexcept(noexcept(_array_view.data()))
		{
			return _array_view.data();
		}

		// Checks if the view's size is 0.
		bool empty
		() const noexcept(noexcept(_array_view.empty()))
		{
			return _array_view.empty();
		}

		// Gets an iterator to the element following the last element of the view.
		iterator end
		() const noexcept(noexcept(_array_view.end()))
		{
			return _array_view.end();
		}

		// Accesses the first element of the view.
		reference front
		() const noexcept(noexcept(_array_view.front()))
		{
			return _array_view.front();
		}

		// Gets a reverse iterator to the beginning of the reversed view.
		reverse_iterator rbegin
		() const noexcept(noexcept(_array_view.rbegin()))
		{
			// std::reverse_iterator constructor is explicit
			return _array_view.rbegin();
		}

		// Gets a reverse iterator to the end of the reversed view.
		reverse_iterator rend
		() const noexcept(noexcept(_array_view.rend()))
		{
			return _array_view.rend();
		}


		// Shrinks the viewed data area from the back.
		void shrink_back
		(
			size_type count
		) noexcept(noexcept(_array_view.shrink_back(count)))
		{
			_array_view.shrink_back(count);
		}

		// Shrinks the viewed data area from the front.
		void shrink_front
		(
			size_type count
		) noexcept(noexcept(_array_view.shrink_front(count)))
		{
			_array_view.shrink_front(count);
		}

		// Size getter.
		size_type size
		() const noexcept(noexcept(_array_view.size()))
		{
			return _array_view.size();
		}


	private:

		/* Member variables */

		// Underlying view of the array
		array_view<T> _array_view;

	};

}
