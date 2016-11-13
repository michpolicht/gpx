/**
 * @file
 * @brief .
 */

#ifndef GPX_X_UTILS_DYNAMICARRAY_HPP_
#define GPX_X_UTILS_DYNAMICARRAY_HPP_

#include "../platform.hpp"
#include "../log.hpp"

#include <new> //placement new
#include <string> //mem* functions
#include <iterator> //reverse_iterator
#include <memory> //allocator

namespace gpx {
namespace utils {

/**
 * Dynamic array. This class template is made in response to std::vector approach, which
 * requires elements to provide assignment operators, hence it is not possible to create
 * std::vector on structures containing references. Also default constructor is not
 * required for the elements.
 *
 * Above does not mean that DynamicArray is better or that it shall be used instead of
 * std::vector! It just uses different approach, to provide functionalities mentioned above.
 * This approach has plenty of drawbacks on its side compared to std::vector. So this
 * class template can be used if its functionalities are required, but in other cases
 * std::vector is preferred.
 *
 * @param T type of array elements. Required public interface for type T:
 * 		- T(const & T other). Construct object from @a other.
 * 		.
 * @param A allocator type.  Required public interface for type A:
 * 		- typedef pointer. Typedefed pointer type.
 * 		- typedef size_type.  Typedefed size type.
 * 		- A(). Default constructor.
 * 		- A(const & A other). Construct allocator from @a other. Copy must be equal to
 * 			@a other, which means that space allocated with @a other must be correctly
 * 			deallocated by a copy and vice versa.
 * 		- pointer allocate(size_type n, const void * = 0). Allocate space for @a n elements.
 * 			Second parameter is not required. Return pointer to allocated space.
 * 		- void deallocate(pointer p, size_type). Deallocate space allocated with allocate()
 * 			by passing a pointer returned by allocate(). Second parameter is not required.
 * 		.
 * 	Interface is compatible with STL. STL requirement that allocators for the same type
 * 	must be equal is weakened, so that only all copies of allocator must be equal.
 *
 * @todo extensive testing; current implementation seems to be buggy.
 * @todo is memory aligned when using placement new?
 */
template <typename T, class A = std::allocator<T> >
class DynamicArray
{
	public:
		//initial reserve must not be 0! add() depends on reserve multiplication.
		static const std::size_t INITIAL_RESERVE = 1;	///< Initial memory reserve in terms of number of elements.

	public:
		typedef T * iterator;
		typedef const T * const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	public:
		/**
		 * Default constructor.
		 * @param allocator allocator.
		 */
		DynamicArray(const A & allocator = A());

		/**
		 * Copy constructor.
		 * @param other other array.
		 *
		 * @todo non-copyable version of this class, without copy ctor and required allocator parameter in other ctors.
		 */
		DynamicArray(const DynamicArray<T, A> & other);

		/**
		 * Constructor.
		 * @param reserve amount of memory to reserve in terms of number of elements.
		 * @param allocator allocator.
		 */
		DynamicArray(std::size_t reserve, const A & allocator = A());

		/**
		 * Constructor.
		 * @param val element to be copied.
		 * @param size array size in terms of number of elements. Elements are initialized
		 * using their copy constructor and element provided as @a val.
		 * @param allocator allocator.
		 */
		DynamicArray(const T & val, std::size_t size, const A & allocator = A());

		/**
		 * Destructor.
		 */
		virtual ~DynamicArray();

	public:
		/**
		 * Data pointer (const version).
		 * @return pointer to array elements.
		 */
		const T * ptr() const;

		/**
		 * Get allocator.
		 * @param array allocator.
		 */
		const A & allocator() const;

		/**
		 * Assignment operator.
		 * @param other other array.
		 */
		DynamicArray<T, A> & operator =(const DynamicArray<T, A> & other);

		/**
		 * Subscript operator (coords access).
		 * @return reference to i-th element.
		 */
		T & operator [](std::size_t i);

		/**
		 * Const version of subscript operator.
		 * @return i-th element value.
		 */
		const T & operator [](std::size_t i) const;

		/**
		 * Equality operator.
		 * @return @p true if this and other array are equal, @p false otherwise.
		 */
		bool operator ==(const DynamicArray<T, A> & other);

		/**
		 * Inequality operator.
		 * @return @p true if this and other array are unequal, @p false otherwise.
		 */
		bool operator !=(const DynamicArray<T, A> & other);

		/**
		 * Amount of reserved memory.
		 * @return amount of reserved memory in terms of number of array elements.
		 */
		std::size_t reserve() const;

		/**
		 * Reserve memory.
		 * @param reserve amount of memory to reserve in terms of number of array elements.
		 */
		void reserve(std::size_t reserve);

		/**
		 * Get array size.
		 * @return array size in terms of number of elements.
		 */
		std::size_t size() const;

		/**
		 * Clear array. Remove all elements calling destructor on each.
		 */
        void clear();

        /**
         * Check whenever array is empty.
         * @return @p true if array is empty, @p false otherwise.
         */
        bool empty() const;

		/**
		 * Push value. Stack-like functionality. Adds element to the end of the array.
		 * @param val value to be pushed.
		 */
		void push(const T & val);

		/**
		 * Push value. Alias of push(). Provided for compatibility with STL containers.
		 * @param val value to be pushed.
		 */
		void push_back(const T & val);

		/**
		 * Pop element. Stack-like functionality. Remove last element from the array.
		 * Calls destructor of removed element.
		 */
		void pop();

		/**
		 * Pop element. Alias of pop(). Provided for compatibility with STL containers.
		 */
		void pop_back();

		/**
		 * Front element access.
		 * @return front element.
		 */
		T & front();

		/**
		 * Front element access.
		 * @return front element.
		 */
		const T & front() const;

		/**
		 * Back element access.
		 * @return back element.
		 */
		T & back();

		/**
		 * Back element access.
		 * @return back element.
		 */
		const T & back() const;

		/**
		 * Iterator begin.
		 * @return iterator.
		 */
        iterator begin();

        /**
         * Const iterator begin.
         * @return const iterator.
         */
        const_iterator begin() const;

        /**
         * Iterator end.
         * @return iterator.
         */
        iterator end();

        /**
         * Const iterator end.
         * @return iterator end.
         */
        const_iterator end() const;

		/**
		 * Reverse iterator begin.
		 * @return reverse iterator.
		 */
        reverse_iterator rbegin();

        /**
         * Const reverse iterator begin.
         * @return const reverse iterator.
         */
        const_reverse_iterator rbegin() const;

        /**
         * Reverse iterator end.
         * @return reverse iterator.
         */
        reverse_iterator rend();

        /**
         * Const reverse iterator end.
         * @return reverse iterator end.
         */
        const_reverse_iterator rend() const;

	protected:
        static const std::size_t GROW_MULTIPLIER = 2;
        static const std::size_t SHRINK_DIVISOR = 4;

	protected:
		/**
		 * Data pointer.
		 * @return pointer to array elements.
		 */
		T * ptr();

        /**
         * Grow if necessary. Check the amount of allocated memory and reserve some,
         * if not enough.
         */
        void maybeGrow();

        /**
         * Shrink if reasonable. Check the amount of allocated memory and free some,
         * if too much.
         */
        void maybeShrink();

        /**
         * Destructively reserve memory. Allocate memory without copying data from old
         * location to new one.
         */
        void destructiveReserve(std::size_t reserve);

        /**
         * Destroy elements. Call destructor on each element and move "end" pointer.
         */
        void destroy();

        /**
         * Raw push. Push element onto array without checking if there is enough memory
         * reserved.
         * @param val element value.
         */
        void rawPush(const T & val);

	private:
		T * m_begin;
		T * m_end;
		T * m_reserve;
		A m_allocator;
};

template <typename T, class A>
DynamicArray<T, A>::DynamicArray(const A & allocator):
	m_begin(0),
	m_end(0),
	m_reserve(0),
	m_allocator(allocator)
{
	destructiveReserve(INITIAL_RESERVE);
}

template <typename T, class A>
DynamicArray<T, A>::DynamicArray(const DynamicArray<T, A> & other):
	m_begin(0),
	m_end(0),
	m_reserve(0)
{
	destructiveReserve(other.reserve());
	for(const_iterator i = other.begin(); i != other.end(); ++i)
		rawPush(*i);
}

template <typename T, class A>
DynamicArray<T, A>::DynamicArray(std::size_t p_reserve, const A & allocator):
	m_begin(0),
	m_end(0),
	m_reserve(0),
	m_allocator(allocator)
{
	destructiveReserve(p_reserve);
}

template <typename T, class A>
DynamicArray<T, A>::DynamicArray(const T & val, std::size_t size, const A & allocator):
	m_begin(0),
	m_end(0),
	m_reserve(0),
	m_allocator(allocator)
{
	destructiveReserve(size);
	for (std::size_t i = 0; i < size; i++)
		rawPush(val);
}

template <typename T, class A>
DynamicArray<T, A>::~DynamicArray()
{
	destroy();
	if (m_begin != 0)
		m_allocator.deallocate(m_begin, reserve());
}

template <typename T, class A>
const T * DynamicArray<T, A>::ptr() const
{
	return m_begin;
}

template <typename T, class A>
const A & DynamicArray<T, A>::allocator() const
{
	return m_allocator;
}

template <typename T, class A>
DynamicArray<T, A> & DynamicArray<T, A>::operator =(const DynamicArray<T, A> & other)
{
	//handle self-assignment
	if (& other = this)
		return *this;
	destroy();
	if (other.size() > reserve())
		destructiveReserve(other.reserve());
	for(const_iterator i = other.begin(); i != other.end(); ++i)
		rawPush(*i);
	return *this;
}

template <typename T, class A>
T & DynamicArray<T, A>::operator [](std::size_t i)
{
	return m_begin[i];
}

template <typename T, class A>
const T & DynamicArray<T, A>::operator [](std::size_t i) const
{
	return m_begin[i];
}

template <typename T, class A>
bool DynamicArray<T, A>::operator ==(const DynamicArray<T, A> & other)
{
	if (other.size() == size())
		return std::memcmp(ptr(), other.ptr(), size() * sizeof(T)) == 0 ? true : false;
	return false;
}

template <typename T, class A>
bool DynamicArray<T, A>::operator !=(const DynamicArray<T, A> & other)
{
	if (other.size() == size())
		return std::memcmp(ptr(), other.ptr(), size() * sizeof(T)) == 0 ? false : true;
	return true;
}

template <typename T, class A>
std::size_t DynamicArray<T, A>::reserve() const
{
	return m_reserve - m_begin;
}

template <typename T, class A>
void DynamicArray<T, A>::reserve(std::size_t p_reserve)
{
	std::size_t curSize = size();
	T * alloc = m_allocator.allocate(p_reserve);
	std::memcpy(alloc, m_begin, curSize * sizeof(T));
	if (m_begin != 0)
		m_allocator.deallocate(m_begin, reserve());
	m_begin = alloc;
	m_end = m_begin + curSize;
	m_reserve = m_begin + p_reserve;
}

template <typename T, class A>
std::size_t DynamicArray<T, A>::size() const
{
	return m_end - m_begin;
}

template <typename T, class A>
void DynamicArray<T, A>::clear()
{
	destroy();
	destructiveReserve(INITIAL_RESERVE);
}

template <typename T, class A>
bool DynamicArray<T, A>::empty() const
{
	return size() == 0;
}

template <typename T, class A>
void DynamicArray<T, A>::push(const T & val)
{
	maybeGrow();
	rawPush(val);
}

template <typename T, class A>
void DynamicArray<T, A>::push_back(const T & val)
{
	push(val);
}

template <typename T, class A>
void DynamicArray<T, A>::pop()
{
	GPX_ASSERT(size() > 0, "attempting to remove element from empty array");
	maybeShrink();
	m_end--;
	m_end->~T();
}

template <typename T, class A>
void DynamicArray<T, A>::pop_back()
{
	pop();
}

template <typename T, class A>
T & DynamicArray<T, A>::front()
{
	return *m_begin;
}

template <typename T, class A>
const T & DynamicArray<T, A>::front() const
{
	return *m_begin;
}

template <typename T, class A>
T & DynamicArray<T, A>::back()
{
	return *(m_end - 1);
}

template <typename T, class A>
const T & DynamicArray<T, A>::back() const
{
	return *(m_end - 1);
}

template <typename T, class A>
typename DynamicArray<T, A>::iterator DynamicArray<T, A>::begin()
{
	return m_begin;
}

template <typename T, class A>
typename DynamicArray<T, A>::const_iterator DynamicArray<T, A>::begin() const
{
	return m_begin;
}

template <typename T, class A>
typename DynamicArray<T, A>::iterator DynamicArray<T, A>::end()
{
	return m_end;
}

template <typename T, class A>
typename DynamicArray<T, A>::const_iterator DynamicArray<T, A>::end() const
{
	return m_end;
}

template <typename T, class A>
typename DynamicArray<T, A>::reverse_iterator DynamicArray<T, A>::rbegin()
{
	return reverse_iterator(end());
}

template <typename T, class A>
typename DynamicArray<T, A>::const_reverse_iterator DynamicArray<T, A>::rbegin() const
{
	return const_reverse_iterator(end());
}

template <typename T, class A>
typename DynamicArray<T, A>::reverse_iterator DynamicArray<T, A>::rend()
{
	return reverse_iterator(begin());
}

template <typename T, class A>
typename DynamicArray<T, A>::const_reverse_iterator DynamicArray<T, A>::rend() const
{
	return const_reverse_iterator(begin());
}

template <typename T, class A>
T * DynamicArray<T, A>::ptr()
{
	return m_begin;
}

template <typename T, class A>
void DynamicArray<T, A>::maybeShrink()
{
	if ((reserve() >= SHRINK_DIVISOR * size()) && (reserve() > INITIAL_RESERVE))
		reserve(std::max(GROW_MULTIPLIER * size(), INITIAL_RESERVE));
}

template <typename T, class A>
void DynamicArray<T, A>::maybeGrow()
{
	if (m_end == m_reserve) {
		GPX_ASSERT(reserve() != 0, "function depends on reserve multiplication");
		reserve(GROW_MULTIPLIER * reserve());
	}
}

template <typename T, class A>
void DynamicArray<T, A>::destroy()
{
	while(!empty()) {
		m_end--;
		m_end->~T();
	}
}

template <typename T, class A>
void DynamicArray<T, A>::destructiveReserve(std::size_t p_reserve)
{
	T * alloc = m_allocator.allocate(p_reserve);
	if (m_begin != 0)
		m_allocator.deallocate(m_begin, reserve());
	m_begin = alloc;
	m_end = m_begin;
	m_reserve = m_begin + p_reserve;
}

template <typename T, class A>
void DynamicArray<T, A>::rawPush(const T & val)
{
	::new (m_end) T(val);
	m_end++;
}

}
}

//namespace std
//{
//	template<typename T, class A>
//	struct iterator_traits<typename gpx::utils::DynamicArray<T, A>::iterator>
//	{
//		typedef random_access_iterator_tag iterator_category;
//		typedef T value_type;
//		typedef ptrdiff_t difference_type;
//		typedef T * pointer;
//		typedef T & reference;
//	};
//
//	template<typename T, class A>
//	struct iterator_traits<typename gpx::utils::DynamicArray<T, A>::const_iterator>
//	{
//		typedef random_access_iterator_tag iterator_category;
//		typedef T value_type;
//		typedef ptrdiff_t difference_type;
//		typedef const T * pointer;
//		typedef const T & reference;
//	};
//}

//overloaded iostream operators
template <typename T, class A>
std::ostream & operator <<(std::ostream & s, const gpx::utils::DynamicArray<T, A> & a)
{
	s << "{";
	if (a.size() != 0) {
		for (std::size_t i = 0; i < a.size() - 1; i++)
			s << a[i] << ", ";
		s << *(a.rbegin());
	}
	s << "}" << std::endl;
    return s;
};

#endif /* GPX_X_UTILS_DYNAMICARRAY_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
