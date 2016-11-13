/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_BASIC_VECTORPTR_HPP_
#define GPX_X_MATH_BASIC_VECTORPTR_HPP_

#include "../const_VectorPtr.hpp"
//#note: "VectorPtr.imp.hpp" included near eof

namespace gpx {
namespace math {
namespace basic {

template <std::size_t N, typename T, bool DIMSPEC = true>
class VectorPtr : public gpx::math::const_VectorData<N, T>
{
	typedef gpx::math::const_VectorData<N, T> Parent;
	typedef VectorPtrStorage<N, T> Storage;

	public:
		//generated copy ctor OK

	protected:
		VectorPtr(T * coords);

		VectorPtr(T * coords, std::size_t size);

	protected:
		T * ptr();
		using Parent::ptr;	//const version

		void operator =(const VectorPtr<N, T, DIMSPEC> & other);

		void operator =(const gpx::math::const_VectorData<N, T> & other);

		void operator =(const real_t other[N]);

		void operator =(T val);

		T & coord(std::size_t i);

		void add(const gpx::math::const_VectorData<N, T> & other);

		void sub(const gpx::math::const_VectorData<N, T> & other);

		void mul(T scalar);

		void mul(const gpx::math::Matrix<N, N, T> & matrix);

		void div(T scalar);

		void zero();

		void invert();

		void normalize();

		void rotate(T sin, T cos, std::size_t c1, std::size_t c2);

		void rotate(T angle, std::size_t c1, std::size_t c2);

		void rotate(T angle, const gpx::math::const_VectorData<2, T> & point, std::size_t c1, std::size_t c2);

		void minimize(const gpx::math::const_VectorData<N, T> & other);

		void swap(std::size_t c1, std::size_t c2);
};

//template <std::size_t N, typename T>
//class VectorPtr<N, T, true> : public VectorPtr<N, T, false>
//{
//	typedef VectorPtr<N, T, false> Parent;
//
//	protected:
//		VectorPtr(T * coords);
//
//		//generated copy assignment OK
//};

template <typename T>
class VectorPtr<gpx::math::SIZE_DYNAMIC, T, true> : public VectorPtr<gpx::math::SIZE_DYNAMIC, T, false>
{
	typedef VectorPtr<gpx::math::SIZE_DYNAMIC, T, false> Parent;

	public:
		//generated copy ctor OK

		//generated copy assignment OK

	protected:
		VectorPtr(T * coords, std::size_t size = 0);

	protected:
		template <std::size_t ON>
		void operator =(const gpx::math::const_VectorData<ON, T> & other);

		void operator =(const real_t * other);

		void operator =(T val);

		using Parent::mul;

		template <std::size_t ON>
		void mul(const gpx::math::Matrix<ON, ON, T> & matrix);

		void setPtr(T * ptr);

		void setPtr(T * ptr, std::size_t size);
};

template <typename T>
class VectorPtr<2, T, true> : public VectorPtr<2, T, false>
{
	typedef VectorPtr<2, T, false> Parent;

	public:
		//generated copy ctor OK

		//generated copy assignment OK

	protected:
		VectorPtr(T * coords);

	protected:
		using Parent::operator =;

		using Parent::add;

		void add(T x, T y);

		using Parent::sub;

		void sub(T x, T y);

		using Parent::mul;

		void mul(const gpx::math::Matrix<4, 4, T> & matrix);

		using Parent::rotate;

		void rotate(T sin, T cos);

		void rotate(T angle);

		void rotate(T angle, const gpx::math::const_VectorData<2, T> & point);
};

template <typename T>
class VectorPtr<3, T, true> : public VectorPtr<3, T, false>
{
	typedef VectorPtr<3, T, false> Parent;

	public:
		//generated copy ctor OK

		//generated copy assignment OK

	protected:
		VectorPtr(T * coords);

	protected:
		using Parent::operator =;

		using Parent::add;

		void add(T x, T y, T z);

		using Parent::sub;

		void sub(T x, T y, T z);

		using Parent::mul;

		void mul(const gpx::math::Matrix<4, 4, T> & matrix);

		using Parent::rotate;

		void rotate(T sin, T cos, std::size_t axis);

		void rotate(T angle, std::size_t axis);
};

}
}
}

#include "VectorPtr.imp.hpp"

#endif /* GPX_X_MATH_BASIC_VECTORPTR_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
