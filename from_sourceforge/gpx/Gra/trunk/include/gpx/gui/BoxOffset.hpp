/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_BOXOFFSET_HPP_
#define GPX_Gra_GUI_BOXOFFSET_HPP_

#include <gpx/platform.hpp>
#include <gpx/utils/Observable.hpp>

namespace gpx {
namespace gui {

class BoxOffset : public utils::Observable<BoxOffset>
{
	public:
		enum eventType_t {
			LEFT_CHANGED,
			RIGHT_CHANGED,
			TOP_CHANGED,
			BOTTOM_CHANGED,
			VERTICAL_CHANGED,
			HORIZONTAL_CHANGED,
			ALL_CHANGED
		};

		enum offset_t {
				LEFT,
				RIGHT,
				TOP,
				BOTTOM
		};

	public:
		static const real_t INITIAL_LEFT = 0.0;
		static const real_t INITIAL_RIGHT = 0.0;
		static const real_t INITIAL_TOP = 0.0;
		static const real_t INITIAL_BOTTOM = 0.0;

	public:
		BoxOffset();

		BoxOffset(real_t all);

		BoxOffset(real_t vertical, real_t horizontal);

		BoxOffset(real_t left, real_t right, real_t top, real_t bottom);

	public:
		const BoxOffset & operator =(const BoxOffset & other);

		BoxOffset & operator +=(const BoxOffset & other);

		BoxOffset & operator -=(const BoxOffset & other);

		BoxOffset operator +(const BoxOffset & other) const;

		BoxOffset operator -(const BoxOffset & other) const;

	public:
		real_t offset(offset_t offset) const;

		real_t left() const;

		void setLeft(real_t left);

		real_t right() const;

		void setRight(real_t right);

		real_t top() const;

		void setTop(real_t top);

		real_t bottom() const;

		void setBottom(real_t bottom);

		/**
		 * Get sum of vertical parameters (top, bottom).
		 */
		real_t vertical() const;

		void setVertical(real_t vertical);

		/**
		 * Get sum of horizontal parameters (left, right).
		 */
		real_t horizontal() const;

		void setHorizontal(real_t horizontal);

		void setAll(real_t all);

	private:
		real_t m_offset[4];
};

inline
BoxOffset::BoxOffset()
{
	m_offset[LEFT] = INITIAL_LEFT;
	m_offset[RIGHT] = INITIAL_RIGHT;
	m_offset[TOP] = INITIAL_TOP;
	m_offset[BOTTOM] = INITIAL_BOTTOM;
}

inline
BoxOffset::BoxOffset(real_t all)
{
	m_offset[LEFT] = all;
	m_offset[RIGHT] = all;
	m_offset[TOP] = all;
	m_offset[BOTTOM] = all;
}

inline
BoxOffset::BoxOffset(real_t vertical, real_t horizontal)
{
	m_offset[LEFT] = horizontal;
	m_offset[RIGHT] = horizontal;
	m_offset[TOP] = vertical;
	m_offset[BOTTOM] = vertical;
}

inline
BoxOffset::BoxOffset(real_t left, real_t right, real_t top, real_t bottom)
{
	m_offset[LEFT] = left;
	m_offset[RIGHT] = right;
	m_offset[TOP] = top;
	m_offset[BOTTOM] = bottom;
}

inline
const BoxOffset & BoxOffset::operator =(const BoxOffset & other)
{
	m_offset[LEFT] = other.left();
	m_offset[RIGHT] = other.right();
	m_offset[TOP] = other.top();
	m_offset[BOTTOM] = other.bottom();
	notifyObservers(ALL_CHANGED);
	return *this;
}

inline
BoxOffset & BoxOffset::operator +=(const BoxOffset & other)
{
	m_offset[LEFT] += other.left();
	m_offset[RIGHT] += other.right();
	m_offset[TOP] += other.top();
	m_offset[BOTTOM] += other.bottom();
	notifyObservers(ALL_CHANGED);
	return *this;
}

inline
BoxOffset & BoxOffset::operator -=(const BoxOffset & other)
{
	m_offset[LEFT] -= other.left();
	m_offset[RIGHT] -= other.right();
	m_offset[TOP] -= other.top();
	m_offset[BOTTOM] -= other.bottom();
	notifyObservers(ALL_CHANGED);
	return *this;
}

inline
BoxOffset BoxOffset::operator +(const BoxOffset & other) const
{
	BoxOffset result(*this);
	result += other;
	return result;
}

inline
BoxOffset BoxOffset::operator -(const BoxOffset & other) const
{
	BoxOffset result(*this);
	result -= other;
	return result;
}

inline
real_t BoxOffset::offset(offset_t offset) const
{
	return m_offset[offset];
}

inline
real_t BoxOffset::left() const
{
	return m_offset[LEFT];
}

inline
void BoxOffset::setLeft(real_t left)
{
	m_offset[LEFT] = left;
	notifyObservers(LEFT_CHANGED);
}

inline
real_t BoxOffset::right() const
{
	return m_offset[RIGHT];
}

inline
void BoxOffset::setRight(real_t right)
{
	m_offset[RIGHT] = right;
	notifyObservers(RIGHT_CHANGED);
}

inline
real_t BoxOffset::top() const
{
	return m_offset[TOP];
}

inline
void BoxOffset::setTop(real_t top)
{
	m_offset[TOP] = top;
	notifyObservers(TOP_CHANGED);
}

inline
real_t BoxOffset::bottom() const
{
	return m_offset[BOTTOM];
}

inline
void BoxOffset::setBottom(real_t bottom)
{
	m_offset[BOTTOM] = bottom;
	notifyObservers(BOTTOM_CHANGED);
}

inline
real_t BoxOffset::vertical() const
{
	return m_offset[TOP] + m_offset[BOTTOM];
}

inline
void BoxOffset::setVertical(real_t vertical)
{
	m_offset[TOP] = vertical;
	m_offset[BOTTOM] = vertical;
	notifyObservers(VERTICAL_CHANGED);
}

inline
real_t BoxOffset::horizontal() const
{
	return m_offset[LEFT] + m_offset[RIGHT];
}

inline
void BoxOffset::setHorizontal(real_t horizontal)
{
	m_offset[LEFT] = horizontal;
	m_offset[RIGHT] = horizontal;
	notifyObservers(HORIZONTAL_CHANGED);
}

inline
void BoxOffset::setAll(real_t all)
{
	m_offset[LEFT] = all;
	m_offset[RIGHT] = all;
	m_offset[TOP] = all;
	m_offset[BOTTOM] = all;
	notifyObservers(ALL_CHANGED);
}



}
}

#endif /* GPX_Gra_GUI_BOXOFFSET_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
