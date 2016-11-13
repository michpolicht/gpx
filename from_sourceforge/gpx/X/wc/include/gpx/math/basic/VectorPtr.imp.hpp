/**
 * @file
 * @brief .
 */

namespace gpx {
namespace math {
namespace basic {

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T, DIMSPEC>::VectorPtr(T * coords):
	Parent(coords)
{
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
VectorPtr<N, T, DIMSPEC>::VectorPtr(T * coords, std::size_t size):
	Parent(coords, size)
{
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T * VectorPtr<N, T, DIMSPEC>::ptr()
{
	return Storage::ptr();
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::operator =(const VectorPtr<N, T, DIMSPEC> & other)
{
	//self assignment branch not required here
//	memcpy(Storage::ptr(), other.ptr(), Parent::size() * sizeof(T));
	std::copy(other.ptr(), other.ptr() + Parent::size(), Storage::ptr());
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::operator =(const gpx::math::const_VectorPtr<N, T> & other)
{
	//self assignment branch not required here
//	memcpy(Storage::ptr(), other.ptr(), Parent::size() * sizeof(T));
	std::copy(other.ptr(), other.ptr() + Parent::size(), Storage::ptr());
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::operator =(const real_t other[2])
{
	//self assignment branch not required here
//	memcpy(Storage::ptr(), other, Parent::size() * sizeof(T));
	std::copy(other, other + Parent::size(), Storage::ptr());
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::operator =(T val)
{
	//self assignment branch not required here
	for (std::size_t i = 0; i < Parent::size(); i++)
		Storage::coord(i) = val;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
T & VectorPtr<N, T, DIMSPEC>::coord(std::size_t i)
{
	return Storage::coord(i);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::add(const gpx::math::const_VectorPtr<N, T> & other)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < Parent::size(); i++)
		Storage::coord(i) += other(i);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::sub(const gpx::math::const_VectorPtr<N, T> & other)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < Parent::size(); i++)
		Storage::coord(i) -= other(i);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::mul(T scalar)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < Parent::size(); i++)
		Storage::coord(i) *= scalar;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::mul(const gpx::math::Matrix<N, N, T> & matrix)
{
	gpx::math::Vector<N, T> copy(*this);
	for (std::size_t i = 0; i < Parent::size(); i++) {
		Storage::coord(i) = T();
		for (std::size_t j = 0; j < Parent::size(); j++)
			Storage::coord(i) += copy(j) * matrix(j, i);
	}
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::div(T scalar)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < Parent::size(); i++)
		Storage::coord(i) /= scalar;
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::zero()
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < Parent::size(); i++)
		Storage::coord(i) = T();
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::invert()
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < Parent::size(); i++)
		Storage::coord(i) = -Parent::coord(i);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::normalize()
{
	div(Parent::length());
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::rotate(T sin, T cos, std::size_t c1, std::size_t c2)
{
	T v1, v2;

	v1 = Parent::coord(c1);
	v2 = Parent::coord(c2);

	Storage::coord(c1) = (v1 * cos) - (v2 * sin);
	Storage::coord(c2) = (v2 * cos) + (v1 * sin);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::rotate(T angle, std::size_t c1, std::size_t c2)
{
	real_t sin, cos;
	gpx::math::sincos(angle, & sin, & cos);
	rotate(static_cast<T>(sin), static_cast<T>(cos), c1, c2);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::rotate(T angle, const gpx::math::const_VectorPtr<2, T> & point, std::size_t c1, std::size_t c2)
{
	Storage::coord(c1) -= point(0);
	Storage::coord(c2) -= point(1);
	rotate(angle, c1, c2);
	Storage::coord(c1) += point(0);
	Storage::coord(c2) += point(1);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::minimize(const gpx::math::const_VectorPtr<N, T> & other)
{
	int epsExp;
	int ptrExp[Parent::size()];
	int dExp;
	T ptrSig[Parent::size()];
	T epsilon = gpx::math::eps(other(0));
	for (std::size_t i = 1; i < Parent::size(); i++)
		epsilon = std::max(epsilon, gpx::math::eps(other(i)));
	std::frexp(epsilon, & epsExp);
	for (std::size_t i = 0; i < Parent::size(); i++)
		ptrSig[i] = std::frexp(Parent::coord(i), & ptrExp[i]);
	int minExp = ptrExp[0];
	for (std::size_t i = 1; i < Parent::size(); i++)
		minExp = std::min(minExp, ptrExp[i]);
	dExp = -epsExp + minExp;
	for (std::size_t i = 0; i < Parent::size(); i++)
		Storage::coord(i) = std::ldexp(ptrSig[i], ptrExp[i] - dExp);
}

template <std::size_t N, typename T, bool DIMSPEC>
inline
void VectorPtr<N, T, DIMSPEC>::swap(std::size_t c1, std::size_t c2)
{
	Parent::swap(c1, c2);
}

//DIMSPEC = true, N = SIZE_DYNAMIC

template <typename T>
inline
VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::VectorPtr(T * coords, std::size_t size):
	Parent(coords, size)
{
}

template <typename T>
template <std::size_t ON>
inline
void VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::operator =(const gpx::math::const_VectorPtr<ON, T> & other)
{
	//self assignment branch not required
	Parent::setSize(other.size());
	Parent::operator =(other.ptr());
}

template <typename T>
inline
void VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::operator =(const real_t * other)
{
	//self assignment branch not required
	Parent::operator =(other);
}

template <typename T>
inline
void VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::operator =(T val)
{
	//self assignment branch not required
	Parent::operator =(val);
}

template <typename T>
template <std::size_t ON>
inline
void VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::mul(const gpx::math::Matrix<ON, ON, T> & matrix)
{
	gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> copy(*this);
	for (std::size_t i = 0; i < Parent::size(); i++) {
		Parent::coord(i) = T();
		for (std::size_t j = 0; j < Parent::size(); j++)
			Parent::coord(i) += copy(j) * matrix(j, i);
	}
}

template <typename T>
inline
void VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::setPtr(T * ptr)
{
	Parent::setPtr(ptr);
}

template <typename T>
inline
void VectorPtr<gpx::math::SIZE_DYNAMIC, T, true>::setPtr(T * ptr, std::size_t size)
{
	Parent::setPtr(ptr, size);
}

//DIMSPEC = true, N = 2

template <typename T>
inline
VectorPtr<2, T, true>::VectorPtr(T * coords):
	Parent(coords)
{
}

template <typename T>
inline
void VectorPtr<2, T, true>::add(T x, T y)
{
	Parent::coord(0) += x;
	Parent::coord(1) += y;
}

template <typename T>
inline
void VectorPtr<2, T, true>::sub(T x, T y)
{
	Parent::coord(0) -= x;
	Parent::coord(1) -= y;
}

template <typename T>
inline
void VectorPtr<2, T, true>::mul(const gpx::math::Matrix<4, 4, T> & matrix)
{
	gpx::math::Vector<2, T> copy(*this);
	Parent::coord(0) = (copy(0) * matrix(0, 0)) + (copy(1) * matrix(1, 0)) + matrix(3, 0);
	Parent::coord(1) = (copy(0) * matrix(0, 1)) + (copy(1) * matrix(1, 1)) + matrix(3, 1);
}

template <typename T>
inline
void VectorPtr<2, T, true>::rotate(T sin, T cos)
{
	T v1 = Parent::coord(0);
	T v2 = Parent::coord(1);

	Parent::coord(0) = (v1 * cos) - (v2 * sin);
	Parent::coord(1) = (v2 * cos) + (v1 * sin);
}

template <typename T>
inline
void VectorPtr<2, T, true>::rotate(T angle)
{
	real_t sin, cos;
	gpx::math::sincos(angle, & sin, & cos);
	rotate(static_cast<T>(sin), static_cast<T>(cos));
}

template <typename T>
inline
void VectorPtr<2, T, true>::rotate(T angle, const gpx::math::const_VectorPtr<2, T> & point)
{
	Parent::coord(0) -= point(0);
	Parent::coord(1) -= point(1);
	rotate(angle);
	Parent::coord(0) += point(0);
	Parent::coord(1) += point(1);
}

//DIMSPEC = true, N = 3

template <typename T>
inline
VectorPtr<3, T, true>::VectorPtr(T * coords):
	Parent(coords)
{
}

template <typename T>
inline
void VectorPtr<3, T, true>::add(T x, T y, T z)
{
	Parent::coord(0) += x;
	Parent::coord(1) += y;
	Parent::coord(2) += z;
}

template <typename T>
inline
void VectorPtr<3, T, true>::sub(T x, T y, T z)
{
	Parent::coord(0) -= x;
	Parent::coord(1) -= y;
	Parent::coord(2) -= z;
}

template <typename T>
inline
void VectorPtr<3, T, true>::mul(const gpx::math::Matrix<4, 4, T> & matrix)
{
	gpx::math::Vector<3, T> copy(*this);
	Parent::coord(0) = (copy(0) * matrix(0, 0)) + (copy(1) * matrix(1, 0)) + (copy(2) * matrix(2, 0)) + matrix(3, 0);
	Parent::coord(1) = (copy(0) * matrix(0, 1)) + (copy(1) * matrix(1, 1)) + (copy(2) * matrix(2, 1)) + matrix(3, 1);
	Parent::coord(2) = (copy(0) * matrix(0, 2)) + (copy(1) * matrix(1, 2)) + (copy(2) * matrix(2, 2)) + matrix(3, 2);
}

template <typename T>
inline
void VectorPtr<3, T, true>::rotate(T sin, T cos, std::size_t axis)
{
	std::size_t c1 = (axis + 1) % 3;
	std::size_t c2 = (axis + 2) % 3;

	T v1 = Parent::coord(c1);
	T v2 = Parent::coord(c2);

	Parent::coord(c1) = (v1 * cos) - (v2 * sin);
	Parent::coord(c2) = (v2 * cos) + (v1 * sin);
}

template <typename T>
inline
void VectorPtr<3, T, true>::rotate(T angle, std::size_t axis)
{
	real_t sin, cos;
	gpx::math::sincos(angle, & sin, & cos);
	rotate(static_cast<T>(sin), static_cast<T>(cos), axis);
}

}
}
}

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
