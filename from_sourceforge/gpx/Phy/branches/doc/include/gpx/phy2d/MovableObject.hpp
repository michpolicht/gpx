/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_MOVABLEOBJECT_HPP_
#define GPX_Phy2d_MOVABLEOBJECT_HPP_

#include "../phy/TransformationMatrix.hpp"
#include "../phy/IMovable.hpp"
#include "ILocalFrame.hpp"

#include <gpx/platform.hpp>
#include <gpx/utils/DoubleBuffer.hpp>
#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy2d {


/**
 * Movable object. Represents time dependent, physical object, which location can be
 * determined. This class keeps transformation matrices and updates them according to
 * position. Derived classes may need to provide own matrix construction mechanism by
 * re-implementing virtual constructTMatrix() function. Position parameter and matrices
 * are double buffered. Class allocates double buffer controller which may be used by
 * derived classes.
 */
class GPX_API MovableObject: public virtual phy::IMovable,
							 public virtual phy2d::ILocalFrame
{
	protected:
		/**
		 * Constructor.
		 */
		MovableObject();

		/**
		 * Destructor.
		 */
		virtual ~MovableObject();

	public:
		/**
		 * Get double buffer controller.
		 * @return double buffer controller.
		 */
		const utils::DoubleBufferController & doubleBufferController() const;

		/**
		 * Get position.
		 * @return position vector.
		 */
		const math::Vector<2> & pos() const;

		/**
		 * Set position.
		 * @param pos position vector.
		 */
		void setPos(const math::const_VectorPtr<2> & pos);

		/**
		 * Set position.
		 * @param x x coordinate of position vector.
		 * @param y y coordinate of position vector.
		 */
		void setPos(real_t x, real_t y);

		/**
		 * Get x coordinate of position vector.
		 * @return x coordinate.
		 */
		real_t x() const;

		/**
		 * Set x coordinate of position vector.
		 * @param x x coordinate.
		 */
		void setX(real_t x);

		/**
		 * Get y coordinate of position vector.
		 * @return y coordinate.
		 */
		real_t y() const;

		/**
		 * Set y coordinate of position vector.
		 * @param y coordinate.
		 */
		void setY(real_t y);

		/**
		 * Get transformation matrix;
		 */
		const phy::TransformationMatrix & tMatrix() const;

		/**
		 * Map point from global to local coordinates.
		 * @param point point to be mapped.
		 */
		virtual math::Vector<2> mapToLocal(const math::const_VectorPtr<2> & point) const;

		/**
		 * Map point from local to global coordinates.
		 * @param point point to be mapped.
		 */
		virtual math::Vector<2> mapToGlobal(const math::const_VectorPtr<2> & point) const;

		//IMovable
		virtual void swapBuffers();

		/**
		 * Update object. This function is responsible for updating physical parameters.
		 * For double buffered parameters all new data should be written into background
		 * buffer.
		 * @param dt elapsed time.
		 */
		//IMovable
		virtual void update(real_t dt);

	protected:
		const math::Vector<2> & posA() const;

		real_t posA(std::size_t i);

		const math::Vector<2> & posB() const;

		real_t posB(std::size_t i);

		/**
		 * Update transformation matrix. Calls constructTMatrix() with active
		 * transformation matrices as parameters. Typically this function is
		 * being called after explicit change of positional parameter.
		 */
		void updateTMatrix();

		/**
		 * Update position. Function has to recalculate position and write it into
		 * given background buffer parameter. This function is called by update().
		 * @param dt elapsed time.
		 * @param posB variable into which new position should be written.
		 */
		virtual void updatePos(real_t dt, math::Vector<2> & posB) = 0;

		/**
		 * Construct transformation matrix. This function should be re-implemented whenever
		 * derived class provides own transformation parameters.
		 * @param tMatrix transformation matrix (existing data will be overwritten).
		 * @param tInvMatrix inverted transformation matrix (existing data will be overwritten).
		 *
		 * @note if transformation parameter is double buffered, then background buffer is used.
		 *
		 * @todo swap buffers before constructTMatrix(active, active) calls.
		 */
		virtual void constructTMatrix(phy::TransformationMatrix & tMatrix, phy::TransformationMatrix & tMatrixInv);

	private:
		utils::DoubleBufferController m_doubleBufferController;	///< Double buffer controller.
		utils::DoubleBuffer<math::Vector<2> > m_pos;			///< Position (double buffered).
		utils::DoubleBuffer<phy::TransformationMatrix> m_tMatrix;		///< Transformation matrix (double buffered).
		utils::DoubleBuffer<phy::TransformationMatrix> m_tMatrixInv;	///< Inverted transformation matrix (double buffered).
};

}
}

#endif /* GPX_Phy2d_MOVABLEOBJECT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
