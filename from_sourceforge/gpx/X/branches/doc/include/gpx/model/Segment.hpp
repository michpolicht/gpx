/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MODEL_SEGMENT_HPP_
#define GPX_X_MODEL_SEGMENT_HPP_

#include "../platform.hpp"

#include "../math/structures.hpp"


namespace gpx {
namespace model {

/**
 * Segment (const version). Segment holds two points of arbitrary dimension and type.
 * @param DIM point dimension.
 * @param T point coordinates type.
 */
template <std::size_t DIM, typename T = real_t>
struct const_Segment
{
	protected:
		T * m_first;
		T * m_second;

	public:
		/**
		 * Default constructor.
		 */
		const_Segment();

		/**
		 * Constructor.
		 * @param first coordinates of first point.
		 * @param second coordinates of second point.
		 */
		const_Segment(const T * first, const T * second);

		void setPoints(const T * first, const T * second);

		void setFirst(const T * first);

		void setSecond(const T * second);

		const T * first() const;

		const T * second() const;

		const math::const_VectorPtr<DIM, T> firstVec() const;

		const math::const_VectorPtr<DIM, T> secondVec() const;

		/**
		 * Get vector coordinates.
		 * @return vector coordinates of segment.
		 */
		math::Vector<DIM, T> vec() const;
};

template <std::size_t DIM, typename T>
inline
const_Segment<DIM, T>::const_Segment():
	m_first(0),
	m_second(0)
{
}

template <std::size_t DIM, typename T>
inline
const_Segment<DIM, T>::const_Segment(const T * first, const T * second):
	m_first(const_cast<T *>(first)),
	m_second(const_cast<T *>(second))
{
}

template <std::size_t DIM, typename T>
inline
void const_Segment<DIM, T>::setPoints(const T * first, const T * second)
{
	m_first = const_cast<T *>(first);
	m_second = const_cast<T *>(second);
}

template <std::size_t DIM, typename T>
inline
void const_Segment<DIM, T>::setFirst(const T * first)
{
	m_first = const_cast<T *>(first);
}

template <std::size_t DIM, typename T>
inline
const T * const_Segment<DIM, T>::first() const
{
	return m_first;
}

template <std::size_t DIM, typename T>
inline
void const_Segment<DIM, T>::setSecond(const T * second)
{
	m_second = const_cast<T *>(second);
}

template <std::size_t DIM, typename T>
inline
const T * const_Segment<DIM, T>::second() const
{
	return m_second;
}

template <std::size_t DIM, typename T>
inline
const math::const_VectorPtr<DIM, T> const_Segment<DIM, T>::firstVec() const
{
	return math::const_VectorPtr<DIM, T>(m_first);
}

template <std::size_t DIM, typename T>
inline
const math::const_VectorPtr<DIM, T> const_Segment<DIM, T>::secondVec() const
{
	return math::const_VectorPtr<DIM, T>(m_second);
}

template <std::size_t DIM, typename T>
inline
math::Vector<DIM, T> const_Segment<DIM, T>::vec() const
{
	math::Vector<DIM, T> result(m_second);
	result -= m_first;
	return result;
}


/**
 * Segment. Segment holds two points of arbitrary dimension and type.
 * @param DIM point dimension.
 * @param T point coordinates type.
 */
template <std::size_t DIM, typename T = real_t>
struct Segment: public const_Segment<DIM, T>
{
	private:
		typedef const_Segment<DIM, T> parent;

	public:
		/**
		 * Default constructor.
		 */
		Segment();

		/**
		 * Constructor.
		 * @param first coordinates of first point.
		 * @param second coordinates of second point.
		 */
		Segment(T * first, T * second);

		void setPoints(T * first, T * second);

		void setFirst(T * first);

		T * getFirst() const;

		void setSecond(T * second);

		T * getSecond() const;

		math::VectorPtr<DIM, T> first() const;

		math::VectorPtr<DIM, T> second() const;
};

template <std::size_t DIM, typename T>
inline
Segment<DIM, T>::Segment()
{
}

template <std::size_t DIM, typename T>
inline
Segment<DIM, T>::Segment(T * first, T * second):
	parent(first, second)
{
}

template <std::size_t DIM, typename T>
inline
void Segment<DIM, T>::setPoints(T * first, T * second)
{
	parent::setPoints(first, second);
}

template <std::size_t DIM, typename T>
inline
void Segment<DIM, T>::setFirst(T * first)
{
	parent::setFirst(first);
}

template <std::size_t DIM, typename T>
inline
T * Segment<DIM, T>::getFirst() const
{
	return parent::_first;
}

template <std::size_t DIM, typename T>
inline
void Segment<DIM, T>::setSecond(T * second)
{
	parent::setSecond(second);
}

template <std::size_t DIM, typename T>
inline
T * Segment<DIM, T>::getSecond() const
{
	return parent::_second;
}

template <std::size_t DIM, typename T>
inline
math::VectorPtr<DIM, T> Segment<DIM, T>::first() const
{
	return math::VectorPtr<DIM, T>(parent::_first);
}

template <std::size_t DIM, typename T>
inline
math::VectorPtr<DIM, T> Segment<DIM, T>::second() const
{
	return math::VectorPtr<DIM, T>(parent::_second);
}


}
}

#endif /* GPX_X_MODEL_SEGMENT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
