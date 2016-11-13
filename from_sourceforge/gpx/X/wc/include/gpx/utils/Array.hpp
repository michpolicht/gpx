/**
 * @file
 * @brief .
 */

#ifndef GPX_X_UTILS_ARRAY_HPP_
#define GPX_X_UTILS_ARRAY_HPP_

#include <iostream>
#include <iterator>
#include <algorithm>

#include "../platform.hpp"

namespace gpx {
namespace utils {

/**
 * Array wrapper.
 *
 * @note this class is an aggregate, which means that it can be initialized by an
 * initializer list in C++98.
 *
 * @note C++11 provides std::array, which should be used instead of this class.
 */
template <std::size_t N, typename T = real_t>
class Array
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// This class is an aggregate.
	//
	// "An aggregate is an array or a class (Clause 9) with no user-provided constructors (12.1), no private or
	//  protected non-static data members (Clause 11), no base classes (Clause 10), and no virtual functions (10.3)."
	//
	//                                       -- C++98 Standard (8.5.1) [dcl.init.aggr]

	public:
		typedef T * iterator;
		typedef const T * const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		T items[N];	//no private nor protected data members allowed in aggregate

		/**
		 * Get array size.
		 * @return array size in terms of number of elements.
		 */
		static size_t Size();

		//compiler-provided default constructor
		//compiler-provided copy constructor
		//compiler-provided destructor
		//compiler-provided copy assignment operator

		/**
		 * Subscript operator (coords access).
		 * @return reference to i-th element.
		 */
		T & operator [](std::size_t i);

		/**
		 * Const version of subscript operator.
		 * @return i-th element's value.
		 */
		const T & operator [](std::size_t i) const;

		/**
		 * Conversion to const T *.
		 */
		const T * ptr() const;

		/**
		 * Conversion to T *.
		 */
		T * ptr();

		/**
		 * Equality operator.
		 * @return @p true if this and other array are equal, @p false otherwise.
		 */
		bool operator ==(const Array<N, T> & other);

		/**
		 * Inequality operator.
		 * @return @p true if this and other array are unequal, @p false otherwise.
		 */
		bool operator !=(const Array<N, T> & other);

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
};


template <std::size_t N, typename T>
size_t Array<N, T>::Size()
{
	return N;
}

template <std::size_t N, typename T>
T & Array<N, T>::operator [](std::size_t i)
{
	return items[i];
}

template <std::size_t N, typename T>
const T & Array<N, T>::operator [](std::size_t i) const
{
	return items[i];
}

template <std::size_t N, typename T>
const T * Array<N, T>::ptr() const
{
	return items;
}

template <std::size_t N, typename T>
T * Array<N, T>::ptr()
{
	return items;
}

template <std::size_t N, typename T>
bool Array<N, T>::operator ==(const Array<N, T> & other)
{
	return std::equal(begin(), end(), other.begin());
//	return std::memcmp(items, other.items, N * sizeof(T)) == 0 ? true : false;
}

template <std::size_t N, typename T>
bool Array<N, T>::operator !=(const Array<N, T> & other)
{
	return !std::equal(begin(), end(), other.begin());
//	return std::memcmp(items, other.items, N * sizeof(T)) == 0 ? false : true;
}

template <std::size_t N, typename T>
typename Array<N, T>::iterator Array<N, T>::begin()
{
	return items;
}

template <std::size_t N, typename T>
typename Array<N, T>::const_iterator Array<N, T>::begin() const
{
	return items;
}

template <std::size_t N, typename T>
typename Array<N, T>::iterator Array<N, T>::end()
{
	return items + N;
}

template <std::size_t N, typename T>
typename Array<N, T>::const_iterator Array<N, T>::end() const
{
	return items + N;
}

template <std::size_t N, typename T>
typename Array<N, T>::reverse_iterator Array<N, T>::rbegin()
{
	return reverse_iterator(end());
}

template <std::size_t N, typename T>
typename Array<N, T>::const_reverse_iterator Array<N, T>::rbegin() const
{
	return const_reverse_iterator(end());
}

template <std::size_t N, typename T>
typename Array<N, T>::reverse_iterator Array<N, T>::rend()
{
	return reverse_iterator(begin());
}

template <std::size_t N, typename T>
typename Array<N, T>::const_reverse_iterator Array<N, T>::rend() const
{
	return const_reverse_iterator(begin());
}

}
}

//namespace std
//{
//	template <std::size_t N, typename T>
//	struct iterator_traits<typename gpx::utils::Array<N, T>::iterator>
//	{
//		typedef random_access_iterator_tag iterator_category;
//		typedef T value_type;
//		typedef ptrdiff_t difference_type;
//		typedef T * pointer;
//		typedef T & reference;
//	};
//
//	template <std::size_t N, typename T>
//	struct iterator_traits<typename gpx::utils::Array<N, T>::const_iterator>
//	{
//		typedef random_access_iterator_tag iterator_category;
//		typedef T value_type;
//		typedef ptrdiff_t difference_type;
//		typedef const T * pointer;
//		typedef const T & reference;
//	};
//}

//overloaded iostream operators
template <std::size_t N, typename T>
std::ostream & operator <<(std::ostream & s, const gpx::utils::Array<N, T> & a)
{
	s << "{";
	for (std::size_t i = 0; i < N - 1; i++)
		s << a[i] << ", ";
	s << a[N - 1] << "}" << std::endl;
    return s;
}

#endif /* GPX_X_UTILS_ARRAY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
