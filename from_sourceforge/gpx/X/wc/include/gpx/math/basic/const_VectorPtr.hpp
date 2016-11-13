/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MATH_BASIC_CONST_VECTORPTR_HPP_
#define GPX_X_MATH_BASIC_CONST_VECTORPTR_HPP_

#include "VectorPtrStorage.hpp"
//#note: "const_VectorPtr.imp.hpp" included near eof

namespace gpx {
namespace math {
namespace basic {

template <std::size_t N, typename T, bool DIMSPEC = true>
class const_VectorPtr : protected VectorPtrStorage<N, T>
{
	typedef VectorPtrStorage<N, T> Parent;

	public:
		const VectorPtrStorage<N, T> & storage() const;

	protected:
		const_VectorPtr(const T * coords);

		const_VectorPtr(const T * coords, std::size_t size);

		//necessary since can not down-cast other to Parent, because Parent is protected
		const_VectorPtr(const const_VectorPtr<N, T, DIMSPEC> & other);

	protected:
		std::size_t size() const;

		void setSize(std::size_t size);

//		operator const T * () const;
		const T * ptr() const;

//		operator size_t() const;

		T coord(std::size_t i) const;

		bool operator ==(const gpx::math::const_VectorPtr<N, T> & other) const;

		bool operator ==(T val) const;

		bool operator !=(const gpx::math::const_VectorPtr<N, T> & other) const;

		bool operator !=(T val) const;

		gpx::math::Vector<N, T> inverse() const;

		gpx::math::Vector<N, T> sum(const gpx::math::const_VectorPtr<N, T> & other) const;

		gpx::math::Vector<N, T> diff(const gpx::math::const_VectorPtr<N, T> & other) const;

		gpx::math::Vector<N, T> prod(T scalar) const;

		gpx::math::Vector<N, T> prod(const gpx::math::Matrix<N, N, T> & matrix) const;

		gpx::math::Vector<N, T> quot(T scalar) const;

		T dot(const gpx::math::const_VectorPtr<N, T> & other) const;

		T dot() const;

		T length() const;

		gpx::math::Vector<N, T> versor() const;

		T det(const gpx::math::const_VectorPtr<N, T> & other, std::size_t c1, std::size_t c2) const;

		gpx::math::Vector<N, T> cross(const gpx::math::const_VectorPtr<N, T> * others) const;

		gpx::math::Vector<N, T> ccross(const gpx::math::const_VectorPtr<N, T> * others) const;

		bool ape(const gpx::math::const_VectorPtr<N, T> & other) const;

		bool ape(T val) const;

		bool ale(const gpx::math::const_VectorPtr<N, T> & other) const;

		bool ale(T val) const;

		gpx::math::Vector<N, T> minimal(const gpx::math::const_VectorPtr<N, T> & other) const;

		gpx::math::Vector<N, T> rotated(T sin, T cos, std::size_t c1, std::size_t c2) const;

		gpx::math::Vector<N, T> rotated(T angle, std::size_t c1, std::size_t c2) const;

		gpx::math::Vector<N, T> rotated(T angle, const gpx::math::const_VectorPtr<2, T> & point, std::size_t c1, std::size_t c2) const;

	private:
		/**
		 * Dot product helper.
		 * @param other other vector.
		 * @return dot product of this vector and other.
		 */
		T _dot(const const_VectorPtr<N, T, DIMSPEC> & other) const;
};

template <typename T>
class const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, true> : public const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, false>
{
	typedef const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, false> Parent;

	public:
		//generated copy ctor OK

	protected:
		const_VectorPtr(const T * coords, std::size_t size);

	protected:
		void setPtr(const T * ptr);

		void setPtr(const T * ptr, std::size_t size);

		using Parent::prod;

		template <std::size_t ON>
		gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> prod(const gpx::math::Matrix<ON, ON, T> & matrix) const;

	private:
		//forbidden
		const_VectorPtr<gpx::math::SIZE_DYNAMIC, T> & operator =(const const_VectorPtr<gpx::math::SIZE_DYNAMIC, T> & other);
};

template <typename T>
class const_VectorPtr<2, T, true> : public const_VectorPtr<2, T, false>
{
	typedef const_VectorPtr<2, T, false> Parent;

	public:
		//generated copy ctor OK

	protected:
		const_VectorPtr(const T * coords);

		using Parent::cross;

		gpx::math::Vector<2, T> cross() const;

		using Parent::ccross;

		gpx::math::Vector<2, T> ccross() const;

		using Parent::det;

		T det(const gpx::math::const_VectorPtr<2, T> & other) const;

		using Parent::sum;

		gpx::math::Vector<2, T> sum(T x, T y) const;

		using Parent::diff;

		gpx::math::Vector<2, T> diff(T x, T y) const;

		using Parent::prod;

		gpx::math::Vector<2, T> prod(const gpx::math::Matrix<4, 4, T> & matrix) const;

		using Parent::rotated;

		gpx::math::Vector<2, T> rotated(T sin, T cos) const;

		gpx::math::Vector<2, T> rotated(T angle) const;

		gpx::math::Vector<2, T> rotated(T angle, const gpx::math::const_VectorPtr<2, T> & point) const;

	private:
		//forbidden
		const_VectorPtr<2, T> & operator =(const const_VectorPtr<2, T> & other);
};

template <typename T>
class const_VectorPtr<3, T, true> : public const_VectorPtr<3, T, false>
{
	typedef const_VectorPtr<3, T, false> Parent;

	public:
		//generated copy ctor OK

	protected:
		const_VectorPtr(const T * coords);

		using Parent::cross;

		gpx::math::Vector<3, T> cross(const gpx::math::const_VectorPtr<3, T> & other) const;

		using Parent::ccross;

		gpx::math::Vector<3, T> ccross(const gpx::math::const_VectorPtr<3, T> & other) const;

		using Parent::sum;

		gpx::math::Vector<3, T> sum(T x, T y, T z) const;

		using Parent::diff;

		gpx::math::Vector<3, T> diff(T x, T y, T z) const;

		using Parent::prod;

		gpx::math::Vector<3, T> prod(const gpx::math::Matrix<4, 4, T> & matrix) const;

		using Parent::rotated;

		gpx::math::Vector<3, T> rotated(T sin, T cos, std::size_t axis) const;

		gpx::math::Vector<3, T> rotated(T angle, std::size_t axis) const;

	private:
		//forbidden
		const_VectorPtr<3, T> & operator =(const const_VectorPtr<3, T> & other);
};

}
}
}

#include "const_VectorPtr.imp.hpp"

#endif /* GPX_X_MATH_BASIC_CONST_VECTORPTR_HPP_ */

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
