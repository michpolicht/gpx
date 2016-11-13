/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_BASIC_VECTOR_HPP_
#define GPX_X_MATH_BASIC_VECTOR_HPP_

#include "../VectorPtr.hpp"
//#note: "Vector.imp.hpp" included near eof

namespace gpx {
namespace math {
namespace basic {

template <std::size_t N, typename T>
class Vector : public gpx::math::VectorPtr<N, T>
{
	typedef gpx::math::VectorPtr<N, T> Parent;

	protected:
		T m_coords[N];

	protected:
		Vector();

		Vector(const Vector<N, T> & other);

		Vector(bool init, std::size_t size, T val, std::size_t reserve);

		Vector(const gpx::math::const_VectorPtr<N, T> & other);

		Vector(const T coords[N]);

		Vector(const T init[N], const T end[N]);

		Vector(T val);

	protected:
		void operator =(const Vector<N, T> & other);

		void operator =(const gpx::math::const_VectorPtr<N, T> & other);

		void operator =(const T other[N]);

		void operator =(T val);

		std::size_t reserve() const;

		void reserve(std::size_t size);

		void resize(std::size_t size);
};

/**
 * Vector coords initializer. This is so called base-from-member idiom. It is used to
 * initialize member before calling parent class constructor.
 */
template <typename T>
class VectorCoordsInit
{
	protected:
		VectorCoordsInit();

		VectorCoordsInit(std::size_t size);

	protected:
		T * m_coords;
};

template <typename T>
class Vector<gpx::math::SIZE_DYNAMIC, T> : private VectorCoordsInit<T>, public gpx::math::VectorPtr<gpx::math::SIZE_DYNAMIC, T>
{
	typedef gpx::math::VectorPtr<gpx::math::SIZE_DYNAMIC, T> Parent;

	protected:
		Vector();

		Vector(const Vector<gpx::math::SIZE_DYNAMIC, T> & other);

		Vector(bool init, std::size_t size, T val, std::size_t reserve);

		Vector(std::size_t size, std::size_t reserve);

		template <std::size_t ON>
		Vector(const gpx::math::const_VectorPtr<ON, T> & other, std::size_t reserve);

		Vector(const T * coords, std::size_t size, std::size_t reserve);

		Vector(const T * init, const T * end, std::size_t size, std::size_t reserve);

		Vector(T val, std::size_t size, std::size_t reserve);

		//non-virtual since this class won't be instantiated alone <=> dtor is protected
		~Vector();

	protected:
		void operator =(const Vector<gpx::math::SIZE_DYNAMIC, T> & other);

		template <std::size_t ON>
		void operator =(const gpx::math::const_VectorPtr<ON, T> & other);

		void operator =(const T * other);

		void operator =(T val);

		std::size_t reserve() const;

		void reserve(std::size_t size);

		void resize(std::size_t size);

	private:
		std::size_t m_reserve;
};

template <typename T>
class Vector<2, T> : public gpx::math::VectorPtr<2, T>
{
	typedef gpx::math::VectorPtr<2, T> Parent;

	protected:
		T m_coords[2];

	protected:
		Vector();

		Vector(const Vector<2, T> & other);

		Vector(bool init, std::size_t size, T val, std::size_t reserve);

		Vector(const gpx::math::const_VectorPtr<2, T> & other);

		Vector(const T coords[2]);

		Vector(T x, T y);

		Vector(const T init[2], const T end[2]);

		Vector(T val);

	protected:
		void operator =(const Vector<2, T> & other);

		void operator =(const gpx::math::const_VectorPtr<2, T> & other);

		void operator =(const T other[2]);

		void operator =(T val);

		std::size_t reserve() const;

		void reserve(std::size_t size);

		void resize(std::size_t size);
};

template <typename T>
class Vector<3, T> : public gpx::math::VectorPtr<3, T>
{
	typedef gpx::math::VectorPtr<3, T> Parent;

	protected:
		T m_coords[3];

	protected:
		Vector();

		Vector(const Vector<3, T> & other);

		Vector(bool init, std::size_t size, T val, std::size_t reserve);

		Vector(const gpx::math::const_VectorPtr<3, T> & other);

		Vector(const T coords[3]);

		Vector(T x, T y, T z);

		Vector(const T init[3], const T end[3]);

		Vector(T val);

	protected:
		void operator =(const Vector<3, T> & other);

		void operator =(const gpx::math::const_VectorPtr<3, T> & other);

		void operator =(const T other[3]);

		void operator =(T val);

		std::size_t reserve() const;

		void reserve(std::size_t size);

		void resize(std::size_t size);
};

}
}
}

#include "Vector.imp.hpp"

#endif /* GPX_X_MATH_BASIC_VECTOR_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
