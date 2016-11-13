/**
 * @file
 * @brief .
 */

namespace gpx {
namespace math {
namespace basic {

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector():
	Parent(m_coords)
{
	//do not use mem* functions cause float/double/whatever representation of 0 is
	//not necessarily 0 binary. Compiler will hopefully unroll this loop.
	for (std::size_t i = 0; i < Parent::size(); i++)
		m_coords[i] = T();
}

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector(const Vector<N, T> & other):
	Parent(m_coords)
{
	memcpy(m_coords, other.m_coords, sizeof(T) * Parent::size());
}

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector(bool init, std::size_t size, T val, std::size_t reserve):
	Parent(m_coords)
{
	if (init)
		for (std::size_t i = 0; i < size; i++)
			m_coords[i] = val;
}

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector(const gpx::math::const_VectorPtr<N, T> & other):
	Parent(m_coords)
{
//	memcpy(m_coords, other.ptr(), sizeof(T) * Parent::size());
	std::copy(other.ptr(), other.ptr() + Parent::size(), m_coords);
}

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector(const T coords[N]):
	Parent(m_coords)
{
//	memcpy(m_coords, coords, sizeof(T) * Parent::size());
	std::copy(coords, coords + Parent::size(), m_coords);
}

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector(const T init[N], const T end[N]):
	Parent(m_coords)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < Parent::size(); i++)
		m_coords[i] = end[i] - init[i];
}

template <std::size_t N, typename T>
inline
Vector<N, T>::Vector(T val):
	Parent(m_coords)
{
	for (std::size_t i = 0; i < Parent::size(); i++)
		m_coords[i] = val;
}

template <std::size_t N, typename T>
inline
void Vector<N, T>::operator =(const Vector<N, T> & other)
{
	//self assignment branch not required here
	Parent::operator =(other);
}

template <std::size_t N, typename T>
inline
void Vector<N, T>::operator =(const gpx::math::const_VectorPtr<N, T> & other)
{
	//self assignment branch not required here
	Parent::operator =(other);
}

template <std::size_t N, typename T>
inline
void Vector<N, T>::operator =(const T other[N])
{
	//self assignment branch not required here
	Parent::operator =(other);
}

template <std::size_t N, typename T>
inline
void Vector<N, T>::operator =(T val)
{
	//self assignment branch not required here
	Parent::operator =(val);
}

template <std::size_t N, typename T>
inline
std::size_t Vector<N, T>::reserve() const
{
	return Parent::size();
}

template <std::size_t N, typename T>
inline
void Vector<N, T>::reserve(std::size_t size)
{
}

template <std::size_t N, typename T>
inline
void Vector<N, T>::resize(std::size_t p_size)
{
	GPX_ASSERT(p_size == Parent::size(), "can not resize fixed sized vector");
}

//N = SIZE_DYNAMIC

template <typename T>
inline
VectorCoordsInit<T>::VectorCoordsInit()
{
	m_coords = 0;
}

template <typename T>
inline
VectorCoordsInit<T>::VectorCoordsInit(std::size_t size)
{
	m_coords = new T[size];
}

template <typename T>
inline
Vector<gpx::math::SIZE_DYNAMIC, T>::Vector():
	VectorCoordsInit<T>(),
	Parent(VectorCoordsInit<T>::m_coords, 0),
	m_reserve(0)
{
}

template <typename T>
inline
Vector<gpx::math::SIZE_DYNAMIC, T>::Vector(std::size_t size, std::size_t reserve):
	VectorCoordsInit<T>(std::max(size, reserve)),
	Parent(VectorCoordsInit<T>::m_coords, size),
	m_reserve(reserve)
{
	//do not use mem* functions cause float/double/whatever representation of 0 is
	//not necessarily 0 binary. Compiler will hopefully unroll this loop.
	for (std::size_t i = 0; i < Parent::size(); i++)
		VectorCoordsInit<T>::m_coords[i] = T();
}

template <typename T>
inline
Vector<gpx::math::SIZE_DYNAMIC, T>::Vector(bool init, std::size_t size, T val, std::size_t reserve):
	VectorCoordsInit<T>(std::max(size, reserve)),
	Parent(VectorCoordsInit<T>::m_coords, size),
	m_reserve(reserve)
{
	if (init)
		for (std::size_t i = 0; i < size; i++)
			VectorCoordsInit<T>::m_coords[i] = val;
}

template <typename T>
inline
Vector<gpx::math::SIZE_DYNAMIC, T>::Vector(const Vector<gpx::math::SIZE_DYNAMIC, T> & other):
	VectorCoordsInit<T>(std::max(other.reserve(), other.size())),
	Parent(VectorCoordsInit<T>::m_coords, other.size()),
	m_reserve(other.reserve())
{
//	memcpy(VectorCoordsInit<T>::m_coords, other.ptr(), sizeof(T) * Parent::size());
	std::copy(other.ptr(), other.ptr() + Parent::size(), VectorCoordsInit<T>::m_coords);
}

template <typename T>
template <std::size_t ON>
inline
Vector<gpx::math::SIZE_DYNAMIC, T>::Vector(const gpx::math::const_VectorPtr<ON, T> & other, std::size_t reserve):
	VectorCoordsInit<T>(std::max(other.size(), reserve)),
	Parent(VectorCoordsInit<T>::m_coords, other.size()),
	m_reserve(reserve)
{
//	memcpy(VectorCoordsInit<T>::m_coords, other.ptr(), sizeof(T) * Parent::size());
	std::copy(other.ptr(), other.ptr() + Parent::size(), VectorCoordsInit<T>::m_coords);
}

template <typename T>
inline
Vector<gpx::math::SIZE_DYNAMIC, T>::Vector(const T * coords, std::size_t size, std::size_t reserve):
	VectorCoordsInit<T>(std::max(size, reserve)),
	Parent(VectorCoordsInit<T>::m_coords, size),
	m_reserve(reserve)
{
//	memcpy(VectorCoordsInit<T>::m_coords, coords, sizeof(T) * Parent::size());
	std::copy(coords, coords + Parent::size(), VectorCoordsInit<T>::m_coords);
}

template <typename T>
inline
Vector<gpx::math::SIZE_DYNAMIC, T>::Vector(const T * init, const T * end, std::size_t size, std::size_t reserve):
	VectorCoordsInit<T>(std::max(size, reserve)),
	Parent(VectorCoordsInit<T>::m_coords, size),
	m_reserve(reserve)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < Parent::size(); i++)
		VectorCoordsInit<T>::m_coords[i] = end[i] - init[i];
}

template <typename T>
inline
Vector<gpx::math::SIZE_DYNAMIC, T>::Vector(T val, std::size_t size, std::size_t reserve):
	VectorCoordsInit<T>(std::max(size, reserve)),
	Parent(VectorCoordsInit<T>::m_coords, size),
	m_reserve(reserve)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < Parent::size(); i++)
		VectorCoordsInit<T>::m_coords[i] = val;
}

template <typename T>
inline
Vector<gpx::math::SIZE_DYNAMIC, T>::~Vector()
{
	delete[] VectorCoordsInit<T>::m_coords;
}

template <typename T>
inline
void Vector<gpx::math::SIZE_DYNAMIC, T>::operator =(const Vector<gpx::math::SIZE_DYNAMIC, T> & other)
{
	//handle self assignment
	if (& other == this)
		return;

	resize(other.size());
	Parent::operator =(other);
}

template <typename T>
template <std::size_t ON>
inline
void Vector<gpx::math::SIZE_DYNAMIC, T>::operator =(const gpx::math::const_VectorPtr<ON, T> & other)
{
	//self assignment branch not required here
	resize(other.size());
	Parent::operator =(other);
}

template <typename T>
inline
void Vector<gpx::math::SIZE_DYNAMIC, T>::operator =(const T * other)
{
	//self assignment branch not required here
	Parent::operator =(other);
}

template <typename T>
inline
void Vector<gpx::math::SIZE_DYNAMIC, T>::operator =(T val)
{
	//self assignment branch not required here
	Parent::operator =(val);
}

template <typename T>
inline
std::size_t Vector<gpx::math::SIZE_DYNAMIC, T>::reserve() const
{
	return m_reserve;
}

template <typename T>
inline
void Vector<gpx::math::SIZE_DYNAMIC, T>::reserve(std::size_t size)
{
	if (size <= Parent::size()) {
		m_reserve = size;
		return;
	}
	T * newCoords = new T[size];
	for(std::size_t i = 0; i < Parent::size(); i++)
		newCoords[i] = VectorCoordsInit<T>::m_coords[i];
	Parent::setPtr(newCoords);
	delete[] VectorCoordsInit<T>::m_coords;
	VectorCoordsInit<T>::m_coords = newCoords;
	m_reserve = size;

}

template <typename T>
inline
void Vector<gpx::math::SIZE_DYNAMIC, T>::resize(std::size_t size)
{
	if (size == Parent::size())
		return;
	//grow or shrink
	if (std::max(size, Parent::size()) > reserve()) {
		delete[] VectorCoordsInit<T>::m_coords;
		VectorCoordsInit<T>::m_coords = new T[std::max(size, reserve())];
		Parent::setPtr(VectorCoordsInit<T>::m_coords, size);
	} else
		Parent::setSize(size);
}

// N = 2

template <typename T>
inline
Vector<2, T>::Vector():
	Parent(m_coords)
{
	//do not use mem* functions cause float/double/whatever representation of 0 is
	//not necessarily 0 binary. Compiler will hopefully unroll this loop.
	for (std::size_t i = 0; i < Parent::size(); i++)
		m_coords[i] = T();
}

template <typename T>
inline
Vector<2, T>::Vector(const Vector<2, T> & other):
	Parent(m_coords)
{
//	memcpy(m_coords, other.m_coords, sizeof(T) * Parent::size());
	std::copy(other.m_coords, other.m_coords + Parent::size(), m_coords);
}

template <typename T>
inline
Vector<2, T>::Vector(bool init, std::size_t size, T val, std::size_t reserve):
	Parent(m_coords)
{
	if (init)
		for (std::size_t i = 0; i < size; i++)
			m_coords[i] = val;
}

template <typename T>
inline
Vector<2, T>::Vector(const gpx::math::const_VectorPtr<2, T> & other):
	Parent(m_coords)
{
//	memcpy(m_coords, other.ptr(), sizeof(T) * Parent::size());
	std::copy(other.ptr(), other.ptr() + Parent::size(), m_coords);
}

template <typename T>
inline
Vector<2, T>::Vector(const T coords[2]):
	Parent(m_coords)
{
//	memcpy(m_coords, coords, sizeof(T) * Parent::size());
	std::copy(coords, coords + Parent::size(), m_coords);
}

template <typename T>
inline
Vector<2, T>::Vector(T x, T y):
	Parent(m_coords)
{
	m_coords[0] = x;
	m_coords[1] = y;
}

template <typename T>
inline
Vector<2, T>::Vector(const T init[2], const T end[2]):
	Parent(m_coords)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < Parent::size(); i++)
		m_coords[i] = end[i] - init[i];
}

template <typename T>
inline
Vector<2, T>::Vector(T val):
	Parent(m_coords)
{
	for (std::size_t i = 0; i < Parent::size(); i++)
		m_coords[i] = val;
}

template <typename T>
inline
void Vector<2, T>::operator =(const Vector<2, T> & other)
{
	//self assignment branch not required here
	Parent::operator =(other);
}

template <typename T>
inline
void Vector<2, T>::operator =(const gpx::math::const_VectorPtr<2, T> & other)
{
	//self assignment branch not required here
	Parent::operator =(other);
}

template <typename T>
inline
void Vector<2, T>::operator =(const T other[2])
{
	//self assignment branch not required here
	Parent::operator =(other);
}

template <typename T>
inline
void Vector<2, T>::operator =(T val)
{
	//self assignment branch not required here
	Parent::operator =(val);
}

template <typename T>
inline
std::size_t Vector<2, T>::reserve() const
{
	return Parent::size();
}

template <typename T>
inline
void Vector<2, T>::reserve(std::size_t size)
{
}

template <typename T>
inline
void Vector<2, T>::resize(std::size_t p_size)
{
	GPX_ASSERT(p_size == Parent::size(), "can not resize fixed sized vector");
}

// N = 3

template <typename T>
inline
Vector<3, T>::Vector():
	Parent(m_coords)
{
	//do not use mem* functions cause float/double/whatever representation of 0 is
	//not necessarily 0 binary. Compiler will hopefully unroll this loop.
	for (std::size_t i = 0; i < Parent::size(); i++)
		m_coords[i] = T();
}

template <typename T>
inline
Vector<3, T>::Vector(const Vector<3, T> & other):
	Parent(m_coords)
{
//	memcpy(m_coords, other.m_coords, sizeof(T) * Parent::size());
	std::copy(other.m_coords, other.m_coords + Parent::size(), m_coords);
}

template <typename T>
inline
Vector<3, T>::Vector(bool init, std::size_t size, T val, std::size_t reserve):
	Parent(m_coords)
{
	if (init)
		for (std::size_t i = 0; i < size; i++)
			m_coords[i] = val;
}

template <typename T>
inline
Vector<3, T>::Vector(const gpx::math::const_VectorPtr<3, T> & other):
	Parent(m_coords)
{
//	memcpy(m_coords, other.ptr(), sizeof(T) * Parent::size());
	std::copy(other.ptr(), other.ptr() + Parent::size(), m_coords);
}

template <typename T>
inline
Vector<3, T>::Vector(const T coords[3]):
	Parent(m_coords)
{
//	memcpy(m_coords, coords, sizeof(T) * Parent::size());
	std::copy(coords, coords + Parent::size(), m_coords);
}

template <typename T>
inline
Vector<3, T>::Vector(T x, T y, T z):
	Parent(m_coords)
{
	m_coords[0] = x;
	m_coords[1] = y;
	m_coords[2] = z;
}

template <typename T>
inline
Vector<3, T>::Vector(const T init[3], const T end[3]):
	Parent(m_coords)
{
	//decent compiler should unroll this loop
	for (std::size_t i = 0; i < Parent::size(); i++)
		m_coords[i] = end[i] - init[i];
}

template <typename T>
inline
Vector<3, T>::Vector(T val):
	Parent(m_coords)
{
	for (std::size_t i = 0; i < Parent::size(); i++)
		m_coords[i] = val;
}

template <typename T>
inline
void Vector<3, T>::operator =(const Vector<3, T> & other)
{
	//self assignment branch not required here
	Parent::operator =(other);
}

template <typename T>
inline
void Vector<3, T>::operator =(const gpx::math::const_VectorPtr<3, T> & other)
{
	//self assignment branch not required here
	Parent::operator =(other);
}

template <typename T>
inline
void Vector<3, T>::operator =(const T other[3])
{
	//self assignment branch not required here
	Parent::operator =(other);
}

template <typename T>
inline
void Vector<3, T>::operator =(T val)
{
	//self assignment branch not required here
	Parent::operator =(val);
}

template <typename T>
inline
std::size_t Vector<3, T>::reserve() const
{
	return Parent::size();
}

template <typename T>
inline
void Vector<3, T>::reserve(std::size_t size)
{
}

template <typename T>
inline
void Vector<3, T>::resize(std::size_t p_size)
{
	GPX_ASSERT(p_size == Parent::size(), "can not resize fixed sized vector");
}

}
}
}

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
