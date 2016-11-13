/**
 * @file
 * @brief .
 */

#include "../../log.hpp"

namespace gpx {
namespace math {
namespace basic {

template <std::size_t N, typename T>
inline
VectorPtrStorage<N, T>::VectorPtrStorage(T * coords):
	m_ptr(coords)
{
}

template <std::size_t N, typename T>
inline
std::size_t VectorPtrStorage<N, T>::size() const
{
	return N;
}

template <std::size_t N, typename T>
inline
void VectorPtrStorage<N, T>::setSize(std::size_t p_size)
{
	if (size() != p_size)
		GPX_FATAL("can not set different size on fixed sized vector");
}

template <std::size_t N, typename T>
inline
const T * VectorPtrStorage<N, T>::ptr() const
{
	return m_ptr;
}

template <std::size_t N, typename T>
inline
T * VectorPtrStorage<N, T>::ptr()
{
	return m_ptr;
}

template <std::size_t N, typename T>
inline
T VectorPtrStorage<N, T>::coord(std::size_t i) const
{
	return m_ptr[i];
}

template <std::size_t N, typename T>
inline
T & VectorPtrStorage<N, T>::coord(std::size_t i)
{
	return m_ptr[i];
}

template <std::size_t N, typename T>
inline
void VectorPtrStorage<N, T>::swap(std::size_t c1, std::size_t c2)
{
	std::swap(m_ptr[c1], m_ptr[c2]);
}

// N = SIZE_DYNAMIC

template <typename T>
inline
VectorPtrStorage<gpx::math::SIZE_DYNAMIC, T>::VectorPtrStorage(T * coords, std::size_t size):
	m_ptr(coords),
	m_size(size)
{
}

template <typename T>
inline
std::size_t VectorPtrStorage<gpx::math::SIZE_DYNAMIC, T>::size() const
{
	return m_size;
}

template <typename T>
inline
void VectorPtrStorage<gpx::math::SIZE_DYNAMIC, T>::setSize(std::size_t size)
{
	m_size = size;
}

template <typename T>
inline
const T * VectorPtrStorage<gpx::math::SIZE_DYNAMIC, T>::ptr() const
{
	return m_ptr;
}

template <typename T>
inline
T * VectorPtrStorage<gpx::math::SIZE_DYNAMIC, T>::ptr()
{
	return m_ptr;
}

template <typename T>
inline
void VectorPtrStorage<gpx::math::SIZE_DYNAMIC, T>::setPtr(T * ptr)
{
	m_ptr = ptr;
}

template <typename T>
inline
void VectorPtrStorage<gpx::math::SIZE_DYNAMIC, T>::setPtr(T * ptr, std::size_t size)
{
	m_ptr = ptr;
	m_size = size;
}

template <typename T>
inline
T VectorPtrStorage<gpx::math::SIZE_DYNAMIC, T>::coord(std::size_t i) const
{
	return m_ptr[i];
}

template <typename T>
inline
T & VectorPtrStorage<gpx::math::SIZE_DYNAMIC, T>::coord(std::size_t i)
{
	return m_ptr[i];
}

template <typename T>
inline
void VectorPtrStorage<gpx::math::SIZE_DYNAMIC, T>::swap(std::size_t c1, std::size_t c2)
{
	std::swap(m_ptr[c1], m_ptr[c2]);
}

}
}
}

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
