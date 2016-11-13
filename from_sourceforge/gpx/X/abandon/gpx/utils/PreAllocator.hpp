/**
 * @file
 * @brief .
 */

#ifndef GPX_X_UTILS_PREALLOCATOR_HPP_
#define GPX_X_UTILS_PREALLOCATOR_HPP_

#include <memory>	//std::allocator header

namespace gpx {
namespace utils {

/**
 * Pre-allocator. Preallocator pre-allocates memory during construction and it is
 * able to pass its storage to requesting container without the need of allocation
 * during request.
 *
 * @warning this class resembles STL allocator, but it is not STL compliant. STL
 * allocator instances are required to be equivalent for the same type, implying
 * that they have no state. Objects of this class poses a state and therefore can't
 * be used with some STL container types, notably std::list.
 */
template <typename T>
class PreAllocator : public std::allocator<T>
{
	typedef std::allocator<T> Parent;

	public:
		typedef typename Parent::value_type value_type;
		typedef typename Parent::size_type size_type;
		typedef typename Parent::difference_type difference_type;
		typedef typename Parent::pointer pointer;
		typedef typename Parent::const_pointer const_pointer;
		typedef typename Parent::reference reference;
		typedef typename Parent::const_reference const_reference;

		template<typename OT>
		struct rebind
		{
			typedef PreAllocator<OT> other;
		};

	public:
		PreAllocator():
			m_reserve(0),
			m_pool(0)
		{
		}

		PreAllocator(size_type reserve):
			m_reserve(reserve),
			m_pool(static_cast<pointer>(::operator new(reserve * sizeof(value_type))))
		{
		}

		PreAllocator(const PreAllocator & other):
			Parent(other),
			m_reserve(other.reserve()),
			m_pool(static_cast<pointer>(::operator new(other.reserve() * sizeof(value_type))))
		{
			cout << "copy ctor" << endl;

		}

		template<typename OT>
		PreAllocator(const PreAllocator<OT> & other):
			Parent(other),
			m_reserve(other.reserve()),
			m_pool(static_cast<pointer>(::operator new(other.reserve() * sizeof(value_type))))
		{
			cout << "copy ctor OT" << endl;
		}

		~PreAllocator()
		{
			cout << "dtor called" << endl;
			::operator delete(m_pool);
		}

	public:
		pointer allocate(size_type n, const void * = 0)
		{
			cout << "allocate(" << n << "): ";
			if (n > m_reserve)
				cout << "n > m_reserve - allocating new storage" << endl;
			else
				cout << "n <= m_reserve - giving m_pool" << endl;

			if (n > m_reserve)
				return static_cast<pointer>(::operator new(n * sizeof(T)));
			else
				return m_pool;
		}

		void deallocate(pointer p, size_type)
		{
			cout << "deallocate(pointer p): ";
			if (p != m_pool)
				cout << "p != m_pool - deleting p" << endl;
			else
				cout << "p == m_pool - will not delete p" << endl;

			if (p != m_pool)
				::operator delete(p);
		}

		size_type reserve() const
		{
			return m_reserve;
		}

	private:
		size_type m_reserve;
		pointer m_pool;
};

}
}

#endif /* GPX_X_UTILS_PREALLOCATOR_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
