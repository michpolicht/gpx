/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_CLIP_HPP_
#define GPX_Gra_CLIP_HPP_

#include <gpx/platform.hpp>
#include <gpx/utils/Observable.hpp>

namespace gpx {
namespace gra2d {


/**
 * Clip region.
 */
class GPX_API Clip : public utils::Observable<Clip>
{
	public:
		enum plane_t {LEFT, RIGHT, BOTTOM, TOP};

	protected:
		real_t m_planes[4];

	public:
		Clip(real_t width, real_t height);

		Clip(real_t left, real_t right, real_t bottom, real_t top);

		virtual ~Clip();

	public:
		real_t operator[](plane_t plane) const; //const version only, since on modification must notify observers

	public:
		real_t plane(plane_t plane) const;

		void setPlane(plane_t plane, real_t val);

		const real_t * planes() const;

		void setPlanes(const real_t planes[4]);

		/**
		 * Set clip planes.
		 * @param left left clip plane position.
		 * @param right right clip plane position.
		 * @param bottom bottom clip plane position.
		 * @param top top clip plane position.
		 */
		void setPlanes(real_t left, real_t right, real_t bottom, real_t top);

		/**
		 * Set clip region size.
		 * @param width width.
		 * @param height height.
		 */
		void setSize(real_t width, real_t height);

		/**
		 * Set clip region position.
		 * @param width width.
		 * @param height height.
		 */
		void setPos(real_t x, real_t y);

		real_t left() const;

		void setLeft(real_t left);

		real_t right() const;

		void setRight(real_t right);

		real_t bottom() const;

		void setBottom(real_t bottom);

		real_t top() const;

		void setTop(real_t top);

		real_t width() const;

		real_t height() const;

};


}
}

#endif /* GPX_Gra_CLIP_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
