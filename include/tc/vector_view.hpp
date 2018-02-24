#pragma once


#include <cstddef>			// std::size_t
#include <iterator>			// std::data(), std::size(), std::reverse_iterator
#include <memory>			// std::pointer_traits, std::addressof()
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

	// Non-owning view of a contiguous array for use as a mathematical vector.
	template<
		typename T
	>
	class vector_view {
		
	public:
		using value_type = T;
		using size_type = std::size_t;
		using reference = value_type&;
		using const_reference = value_type const&;
		using pointer = value_type*;
		using const_pointer = value_type const*;
		using difference_type = typename std::pointer_traits<pointer>::difference_type;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		// Destructor.
		~vector_view
		() = default;

		// Default constructor.
		vector_view
		() noexcept :
			_pointer(nullptr),
			_size(0)
		{}

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
		) noexcept :
			_pointer(pointer),
			_size(size)
		{}
		
		// Constructor from contiguous iterator range.
		template<
			typename ContiguousIterator
		>
		vector_view
		(
			ContiguousIterator begin,
			ContiguousIterator end
		) noexcept(noexcept(end - begin) && noexcept(*begin) && noexcept(std::addressof(*begin))) :
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
		vector_view
		(
			Container& container
		) noexcept(noexcept(std::data(container)) && noexcept(std::size(container))) :
			_pointer(std::data(container)),
			_size(std::size(container))
		{}


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
		) const noexcept
		{
			return _pointer[index - 1];
		}


		// Bounds checked element access.
		reference at
		(
			size_type index
		) const
		{
			if (index < 1 || index >= _size) {
				throw std::out_of_range("Specified index out of bounds.");
			}
			return _pointer[index];
		}

		// Accesses the last element of the view.
		reference back
		() const noexcept
		{
			return _pointer[_size - 1];
		}

		// Gets an iterator to the beginning of the view.
		iterator begin
		() const noexcept
		{
			return _pointer;
		}

		// Gets a read-only iterator to the beginning of the view.
		const_iterator cbegin
		() const noexcept
		{
			return _pointer;
		}

		// Gets a read-only iterator to the element following the last element of the view.
		const_iterator cend
		() const noexcept
		{
			return _pointer + _size;
		}

		// Gets a read-only reverse iterator to the beginning of the reversed view.
		const_reverse_iterator crbegin
		() const noexcept(noexcept(const_reverse_iterator{ this->cend() }))
		{
			// std::reverse_iterator constructor is explicit
			return const_reverse_iterator{ this->cend() };
		}

		// Gets a read-only reverse iterator to the end of the reversed view.
		const_reverse_iterator crend
		() const noexcept(noexcept(const_reverse_iterator{ this->cbegin() }))
		{
			// std::reverse_iterator constructor is explicit
			return const_reverse_iterator{ this->cbegin() };
		}

		// Gets a pointer to the viewed array data
		pointer data
		() const noexcept
		{
			return _pointer;
		}

		// Checks if the view's size is 0.
		bool empty
		() const noexcept
		{
			return _size == 0;
		}

		// Gets an iterator to the element following the last element of the view.
		iterator end
		() const noexcept
		{
			return _pointer + _size;
		}

		// Accesses the first element of the view.
		reference front
		() const noexcept
		{
			return _pointer[0];
		}

		// Gets a reverse iterator to the beginning of the reversed view.
		reverse_iterator rbegin
		() const noexcept(noexcept(reverse_iterator{ this->end() }))
		{
			// std::reverse_iterator constructor is explicit
			return reverse_iterator{ this->end() };
		}

		// Gets a reverse iterator to the end of the reversed view.
		reverse_iterator rend
		() const noexcept(noexcept(reverse_iterator{ this->begin() }))
		{
			// std::reverse_iterator constructor is explicit
			return reverse_iterator{ this->begin() };
		}


		// Shrinks the viewed data area from the back.
		void shrink_back
		(
			size_type count
		) noexcept
		{
			_size -= count;
		}

		// Shrinks the viewed data area from the front.
		void shrink_front
		(
			size_type count
		) noexcept
		{
			_pointer += count;
			_size -= count;
		}

		// Size getter.
		size_type size
		() const noexcept
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
