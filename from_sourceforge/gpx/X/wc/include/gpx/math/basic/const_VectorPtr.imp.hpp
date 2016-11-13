/**
 * @file
 * @brief .
 */

#include <cmath>
#include <algorithm>

namespace gpx {
namespace math {
namespace basic {

template <std::size_t N, typename T, bool DIMSPEC>
inline
const VectorPtrStorage<N, T> & const_VectorPtr<N, T, DIMSPEC>::storage() const
{
	return *this;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
const_VectorPtr<N, T, DIMSPEC>::const_VectorPtr(const T * coords):
	Parent(const_cast<T *>(coords))
{
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
const_VectorPtr<N, T, DIMSPEC>::const_VectorPtr(const T * coords, std::size_t size):
	Parent(const_cast<T *>(coords), size)
{
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
const_VectorPtr<N, T, DIMSPEC>::const_VectorPtr(const const_VectorPtr<N, T, DIMSPEC> & other):
	Parent(other.storage())
{
}

//template <std::size_t N, typename T, bool DIMSPEC>
//inline
//const_VectorPtr<N, T, DIMSPEC>::operator const T *() const
//{
//	return m_ptr;
//}

template <std::size_t N, typename T, bool DIMSPEC>
inline
std::size_t const_VectorPtr<N, T, DIMSPEC>::size() const
{
	return Parent::size();
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void const_VectorPtr<N, T, DIMSPEC>::setSize(std::size_t size)
{
	Parent::setSize(size);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
const T * const_VectorPtr<N, T, DIMSPEC>::ptr() const
{
	return Parent::ptr();
}

//template <std::size_t N, typename T, bool DIMSPEC>
//inline
//const_VectorPtr<N, T, DIMSPEC>::operator std::size_t () const
//{
//	return (size_t)Parent::ptr();
//}

//template <std::size_t N, typename T, bool DIMSPEC>
//inline
//T const_VectorPtr<N, T, DIMSPEC>::operator [](int i) const
//{
//	GPX_ASSERT(sizeof(std::size_t) >= sizeof(int), "int can not be safely converted to std::size_t");
//	GPX_ASSERT(static_cast<std::size_t>(i) < N, "index [" << i << "] is out of bounds");
//	return m_ptr[i];
//}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::coord(std::size_t i) const
{
	return Parent::coord(i);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::operator ==(const gpx::math::const_VectorPtr<N, T> & other) const
{
	return std::equal(Parent::ptr(), Parent::ptr() + size(), other.ptr());
//	return memcmp(Parent::ptr(), other.ptr(), sizeof(T) * size()) == 0 ? true : false;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::operator ==(T val) const
{
	for (std::size_t i = 0; i < size(); i++)
		if (Parent::coord(i) != val)
			return false;
	return true;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::operator !=(const gpx::math::const_VectorPtr<N, T> & other) const
{
	return !std::equal(Parent::ptr(), Parent::ptr() + size(), other.ptr());
//	return memcmp(Parent::ptr(), other.ptr(), sizeof(T) * size()) == 0 ? false : true;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::operator !=(T val) const
{
	for (std::size_t i = 0; i < size(); i++)
		if (Parent::coord(i) != val)
			return true;
	return false;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::inverse() const
{
	gpx::math::Vector<N, T> result(static_cast<const gpx::math::const_VectorPtr<N, T> &>(*this));
	result.invert();
	return result;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::sum(const gpx::math::const_VectorPtr<N, T> & other) const
{
	gpx::math::Vector<N, T> result(static_cast<const gpx::math::const_VectorPtr<N, T> &>(*this));
	result += other;
	return result;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::diff(const gpx::math::const_VectorPtr<N, T> & other) const
{
	gpx::math::Vector<N, T> result(static_cast<const gpx::math::const_VectorPtr<N, T> &>(*this));
	result -= other;
	return result;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::prod(T scalar) const
{
	gpx::math::Vector<N, T> result(static_cast<const gpx::math::const_VectorPtr<N, T> &>(*this));
	result *= scalar;
	return result;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::prod(const gpx::math::Matrix<N, N, T> & matrix) const
{
	gpx::math::Vector<N, T> result(static_cast<const gpx::math::const_VectorPtr<N, T> &>(*this));
	result *= matrix;
	return result;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::quot(T scalar) const
{
	gpx::math::Vector<N, T> result(static_cast<const gpx::math::const_VectorPtr<N, T> &>(*this));
	result /= scalar;
	return result;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::dot(const gpx::math::const_VectorPtr<N, T> & other) const
{
	return _dot(other);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::dot() const
{
	return _dot(*this);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::length() const
{
	return std::sqrt(dot());
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::versor() const
{
	gpx::math::Vector<N, T> result(static_cast<const gpx::math::const_VectorPtr<N, T> &>(*this));
	result.div(length());
	return result;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::det(const gpx::math::const_VectorPtr<N, T> & other, std::size_t c1, std::size_t c2) const
{
	return (Parent::coord(c1) * other(c2)) - (Parent::coord(c2) * other(c1));
}

template <std::size_t N, typename T, bool DIMSPEC>
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::cross(const gpx::math::const_VectorPtr<N, T> * others) const
{
	//c0  a0 b0 ... z0
	//c1  a1 b1 ... z1
	//c2  a2 b2 ... z2
	//.   .  .  ... .
	//cN  aN bN ... zN
	//resulting vector is [+1 * det(minor(c0)), -1 * det(minor(c1)), +1 * det(minor(c2)), ..., +/-1 * det(minor(cN))]

	T resArr[size()];	//to prevent initialization of result standard array is used
	gpx::math::VectorPtr<N, T> result(resArr);	//resulting vector
	result.setSize(size());
	#if (N == 0)
		gpx::math::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> m(size() - 1, size() - 1);	//size - 1, one row is always excluded for each minor (together with cX column)
	#else
		gpx::math::Matrix<N - 1, N - 1, T> m(0, 0);	//N - 1, one row is always excluded for each minor (together with cX column)
	#endif /* (N == 0) */

	//fill matrix for minor c0
	for (std::size_t c = 0; c < size() - 1; c++) {
		m(c, 0) = this->coord(c + 1);
		for (std::size_t n = 0; n < size() - 2; n++)
			m(c, n + 1) = others[n].coord(c + 1);
	}
	result[0] = m.det();

	//considering minor c + 1 (c1 for c = 0)
	for (std::size_t c = 0; c < size() - 1; c++) {
		//overwrite row c
		m(c, 0) = this->coord(c);
		for (std::size_t n = 0; n < size() - 2; n++)
			m(c, n + 1) = others[n].coord(c);
		if (c % 2)	//minor(c1) for c = 0, minor(c2) for c = 2, ..., % 2 = 0 -> else block
			result[c + 1] = m.det();	//minor(c2), minor(c4), ...
		else
			result[c + 1] = -m.det();	//minor(c1), minor(c3), ...
	}
	return gpx::math::Vector<N, T>(result);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::ccross(const gpx::math::const_VectorPtr<N, T> * others) const
{
	gpx::math::Vector<N, T> result = cross(others);
	result.invert();
	return result;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::ape(const gpx::math::const_VectorPtr<N, T> & other) const
{
	for (std::size_t i = 0; i < size(); i++)
		if (!gpx::math::ape(coord(i), other(i)))
			return false;
	return true;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::ape(T val) const
{
	for (std::size_t i = 0; i < size(); i++)
		if (!gpx::math::ape(coord(i), val))
			return false;
	return true;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::ale(const gpx::math::const_VectorPtr<N, T> & other) const
{
	for (std::size_t i = 0; i < size(); i++)
		if (!gpx::math::ale(coord(i), other(i)))
			return false;
	return true;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
bool const_VectorPtr<N, T, DIMSPEC>::ale(T val) const
{
	for (std::size_t i = 0; i < size(); i++)
		if (!gpx::math::ale(coord(i), val))
			return false;
	return true;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::minimal(const gpx::math::const_VectorPtr<N, T> & other) const
{
	gpx::math::Vector<N, T> result(static_cast<const gpx::math::const_VectorPtr<N, T> & >(*this));
	result.minimize(other);
	return result;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::rotated(T sin, T cos, std::size_t c1, std::size_t c2) const
{
	gpx::math::Vector<N, T> result(static_cast<const gpx::math::const_VectorPtr<N, T> & >(*this));
	result.rotate(sin, cos, c1, c2);
	return result;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::rotated(T angle, std::size_t c1, std::size_t c2) const
{
	gpx::math::Vector<N, T> result(static_cast<const gpx::math::const_VectorPtr<N, T> & >(*this));
	result.rotate(angle, c1, c2);
	return result;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<N, T> const_VectorPtr<N, T, DIMSPEC>::rotated(T angle, const gpx::math::const_VectorPtr<2, T> & point, std::size_t c1, std::size_t c2) const
{
	gpx::math::Vector<N, T> result(static_cast<const gpx::math::const_VectorPtr<N, T> & >(*this));
	result.rotate(angle, point, c1, c2);
	return result;
}

//template <std::size_t N, typename T, bool DIMSPEC>
//inline
//gpx::math::Matrix<N, N, T> const_VectorPtr<N, T, DIMSPEC>::out(const const_VectorPtr<N, T> & other) const
//{
//	GPX_WARN("matrix initialization methods will be changed!");
//	gpx::math::Matrix<N, N, T> result(false);	//@todo as above
//	for (std::size_t i = 0; i < N; i++)
//		for (std::size_t j = 0; j < N; j++)
//			result(i, j) = (*this)(i) * other(j);
//	return result;
//}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T const_VectorPtr<N, T, DIMSPEC>::_dot(const const_VectorPtr<N, T, DIMSPEC> & other) const
{
	T result = T();
	for (std::size_t i = 0; i < size(); i++)
		result += this->coord(i) * other.coord(i);
	return result;
}


//DIMSPEC = true, N = SIZE_DYNAMIC

template <typename T>
inline
const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::const_VectorPtr(const T * coords, std::size_t size):
	Parent(coords, size)
{
}

template <typename T>
inline
void const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::setPtr(const T * ptr)
{
	Parent::setPtr(const_cast<T *>(ptr));
}

template <typename T>
inline
void const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::setPtr(const T * ptr, std::size_t size)
{
	Parent::setPtr(const_cast<T *>(ptr), size);
}

template <typename T>
template <std::size_t ON>
inline
gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> const_VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::prod(const gpx::math::Matrix<ON, ON, T> & matrix) const
{
	gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> result(static_cast<const gpx::math::const_VectorPtr<gpx::math::SIZE_DYNAMIC, T> &>(*this));
	result *= matrix;
	return result;
}

//DIMSPEC = true, N = 2

template <typename T>
inline
const_VectorPtr<2, T, true>::const_VectorPtr(const T * coords):
	Parent(coords)
{
}

template <typename T>
inline
gpx::math::Vector<2, T> const_VectorPtr<2, T, true>::cross() const
{
	return gpx::math::Vector<2, T>(Parent::coord(1), -Parent::coord(0));
}

template <typename T>
inline
gpx::math::Vector<2, T> const_VectorPtr<2, T, true>::ccross() const
{
	return gpx::math::Vector<2, T>(-Parent::coord(1), Parent::coord(0));
}

template <typename T>
inline
T const_VectorPtr<2, T, true>::det(const gpx::math::const_VectorPtr<2, T> & other) const
{
	return (Parent::coord(0) * other(1)) - (Parent::coord(1) * other(0));
}

template <typename T>
inline
gpx::math::Vector<2, T> const_VectorPtr<2, T, true>::sum(T x, T y) const
{
	gpx::math::Vector<2, T> result(static_cast<const gpx::math::const_VectorPtr<2, T> &>(*this));
	result.add(x, y);
	return result;
}

template <typename T>
inline
gpx::math::Vector<2, T> const_VectorPtr<2, T, true>::diff(T x, T y) const
{
	gpx::math::Vector<2, T> result(static_cast<const gpx::math::const_VectorPtr<2, T> &>(*this));
	result.sub(x, y);
	return result;
}

template <typename T>
inline
gpx::math::Vector<2, T> const_VectorPtr<2, T, true>::prod(const gpx::math::Matrix<4, 4, T> & matrix) const
{
	gpx::math::Vector<2, T> result(static_cast<const gpx::math::const_VectorPtr<2, T> &>(*this));
	result.mul(matrix);
	return result;
}

template <typename T>
inline
gpx::math::Vector<2, T> const_VectorPtr<2, T, true>::rotated(T sin, T cos) const
{
	gpx::math::Vector<2, T> result(static_cast<const gpx::math::const_VectorPtr<2, T> & >(*this));
	result.rotate(sin, cos);
	return result;
}

template <typename T>
inline
gpx::math::Vector<2, T> const_VectorPtr<2, T, true>::rotated(T angle) const
{
	gpx::math::Vector<2, T> result(static_cast<const gpx::math::const_VectorPtr<2, T> & >(*this));
	result.rotate(angle);
	return result;
}

template <typename T>
inline
gpx::math::Vector<2, T> const_VectorPtr<2, T, true>::rotated(T angle, const gpx::math::const_VectorPtr<2, T> & point) const
{
	gpx::math::Vector<2, T> result(static_cast<const gpx::math::const_VectorPtr<2, T> & >(*this));
	result.rotate(angle, point);
	return result;
}

//DIMSPEC = true, N = 3

template <typename T>
inline
const_VectorPtr<3, T, true>::const_VectorPtr(const T * coords):
	Parent(coords)
{
}

template <typename T>
inline
gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::cross(const gpx::math::const_VectorPtr<3, T> & other) const
{
	return gpx::math::Vector<3, T>(
			Parent::coord(1) * other(2) - Parent::coord(2) * other(1),
			Parent::coord(2) * other(0) - Parent::coord(0) * other(2),
			Parent::coord(0) * other(1) - Parent::coord(1) * other(0)
		);
}

template <typename T>
inline
gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::ccross(const gpx::math::const_VectorPtr<3, T> & other) const
{
	return gpx::math::Vector<3, T>(
			Parent::coord(2) * other(1) - Parent::coord(1) * other(2),
			Parent::coord(0) * other(2) - Parent::coord(2) * other(0),
			Parent::coord(1) * other(0) - Parent::coord(0) * other(1)
		);
}

template <typename T>
inline
gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::sum(T x, T y, T z) const
{
	gpx::math::Vector<3, T> result(static_cast<const gpx::math::const_VectorPtr<3, T> &>(*this));
	result.add(x, y, z);
	return result;
}

template <typename T>
inline
gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::diff(T x, T y, T z) const
{
	gpx::math::Vector<3, T> result(static_cast<const gpx::math::const_VectorPtr<3, T> &>(*this));
	result.sub(x, y, z);
	return result;
}

template <typename T>
inline
gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::prod(const gpx::math::Matrix<4, 4, T> & matrix) const
{
	gpx::math::Vector<3, T> result(static_cast<const gpx::math::const_VectorPtr<3, T> &>(*this));
	result.mul(matrix);
	return result;
}

template <typename T>
inline
gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::rotated(T sin, T cos, std::size_t axis) const
{
	gpx::math::Vector<3, T> result(static_cast<const gpx::math::const_VectorPtr<3, T> & >(*this));
	result.rotate(sin, cos, axis);
	return result;
}

template <typename T>
inline
gpx::math::Vector<3, T> const_VectorPtr<3, T, true>::rotated(T angle, std::size_t axis) const
{
	gpx::math::Vector<3, T> result(static_cast<const gpx::math::const_VectorPtr<3, T> & >(*this));
	result.rotate(angle, axis);
	return result;
}

}
}
}

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
