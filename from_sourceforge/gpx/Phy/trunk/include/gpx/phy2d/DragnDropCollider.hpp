/*
 * DragnDropCollider.h
 *
 *      Author: doc
 */

#ifndef GPX_Phy2d_DRAGNDROPCOLLIDER_HPP_
#define GPX_Phy2d_DRAGNDROPCOLLIDER_HPP_

#include "../phy_config.hpp"
#include "../phy/ITimePerformer.hpp"

#include <gpx/platform.hpp>
#include <gpx/utils/functions.hpp>
#include <gpx/ext/UnorderedSet.hpp>

#include <vector>

namespace gpx {
namespace phy2d {

class ICDragnDrop;

class GPX_API DragnDropCollider: public virtual phy::ITimePerformer
{
	public:
		#ifdef GPX_EXT_UNORDERED_SET
			typedef ext::UnorderedSet<ICDragnDrop * , utils::hash<ICDragnDrop *> >::Type ObjectsContainer;
		#else //fallback to std::set
			typedef std::set<ICDragnDrop *> ObjectsContainer;
		#endif /* GPX_HASH_SET */
		typedef std::vector<ICDragnDrop * > DraggedContainer;

	public:
		/**
		 * Constructor.
		 */
		DragnDropCollider();

		/**
		 * Destructor.
		 */
		virtual ~DragnDropCollider();

		/**
		 * Drag.
		 */
		void drag(const real_t pos[2]);

		/**
		 * Drag.
		 */
		void drag(real_t x, real_t y);

		/**
		 * Drop.
		 */
		void drop();

		/**
		 * Check if one or more objects are dragged.
		 * @return number of dragged objects.
		 */
		std::size_t draggedNum() const;

		/**
		 * Set current pointer position
		 * @param pos array containing (x, y) coordinates of pointer position.
		 */
		void setPos(const real_t pos[2]);

		/**
		 * Set current pointer position.
		 * @param x x coordinate of pointer position.
		 * @param y y coordinate of pointer position.
		 */
		void setPos(real_t x, real_t y);

		/**
		 * Get current position.
		 * @return pointer to (x, y) coordinates of pointer position.
		 */
		const real_t * pos() const;	//const real_t *; must not be changed directly in respect to oldPos

		/**
		 * Set x coordinate of current pointer position.
		 * @param x x coordinate of pointer position.
		 */
		void setX(real_t x);

		/**
		 * Get x coordinate of stored pointer position.
		 * @return x coordinate of stored pointer position.
		 */
		real_t x() const;

		/**
		 * Get x coordinate subtraction of current and last stored position.
		 * @return x coordinate subtraction of current and last stored position.
		 */
		real_t dx() const;

		/**
		 * Set y coordinate of current pointer position.
		 * @param y y coordinate of pointer position.
		 */
		void setY(real_t y);

		/**
		 * Get y coordinate of stored pointer position.
		 * @return y coordinate of stored pointer position.
		 */
		real_t y() const;

		/**
		 * Get y coordinate subtraction of current and last stored position.
		 * @return y coordinate subtraction of current and last stored position.
		 */
		real_t dy() const;

		/**
		 * Get time step.
		 * @return time step.
		 */
		real_t dt() const;

		/**
		 * Detect collisions and request collision performance from colliding object (if any).
		 * @param dt time step.
		 */
		void update(real_t dt);

		/**
		 * Add object to collider.
		 * @param obj object.
		 */
		void add(ICDragnDrop * obj);

		/**
		 * Remove object from collider.
		 * @param obj object.
		 */
		void remove(ICDragnDrop * obj);

	protected:
		/**
		 * Set time step.
		 * @param dt time step.
		 */
		void setDt(real_t dt);

	private:
		ObjectsContainer m_objects;
		DraggedContainer m_dragged; //dragged objects
		real_t m_pos[2];
		real_t m_oldPos[2];
		real_t m_dt;
};

}
}

#endif /* GPX_Phy2d_DRAGNDROPCOLLIDER_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
