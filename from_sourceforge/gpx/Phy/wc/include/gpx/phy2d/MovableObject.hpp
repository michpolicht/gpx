/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_MOVABLEOBJECT_HPP_
#define GPX_Phy2d_MOVABLEOBJECT_HPP_

#include "../phy/TransformationMatrix.hpp"
#include "../phy/IMovable.hpp"
#include "../phy/IRecordable.hpp"
#include "ILocalFrame.hpp"
#include "PhyObject.hpp"

#include <gpx/platform.hpp>
#include <gpx/utils/DoubleBuffer.hpp>
#include <gpx/math/structures.hpp>

namespace gpx {
namespace phy2d {


/**
 * Movable object. Represents time dependent, physical object, which location can be
 * determined. This class keeps transformation matrices and updates them according to
 * position. Derived classes may need to provide own matrix construction mechanism by
 * re-implementing virtual constructTMatrix() and constructTMatrixInv() functions.
 * Position parameter and matrices are double buffered. Class allocates double
 * buffer controller which may be used by derived classes.
 */
class GPX_API MovableObject: public PhyObject,
							 public virtual phy::IMovable,
							 public virtual phy::IRecordable,
							 public virtual ILocalFrame
{
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
		math::const_PointRef<2> pos() const;

		/**
		 * Get specific position coordinate.
		 * @param i coordinate.
		 * @return position coordinate.
		 */
		real_t pos(std::size_t i);

		/**
		 * Set position.
		 * @param pos new position.
		 */
		void setPos(math::const_PointRef<2> pos);

		/**
		 * Set position.
		 * @param x x coordinate of new position.
		 * @param y y coordinate of new position.
		 */
		void setPos(real_t x, real_t y);

		/**
		 * Get transformation matrix.
		 */
		const phy::TransformationMatrix & tMatrix() const;

		/**
		 * Get inverted transformation matrix.
		 */
		const phy::TransformationMatrix & tMatrixInv() const;

		//ILocalFrame
		virtual math::Point<2> mapToLocal(math::const_PointRef<2> point) const;

		//ILocalFrame
		virtual math::Point<2> mapToGlobal(math::const_PointRef<2> point) const;

		//IRecordable
		virtual std::size_t snapshotSize() const;

		//IRecordable
		virtual void store(char * snapshot) const;

		//IRecordable
		virtual void restore(char * snapshot);

		//IMovable
		virtual void swapBuffers();

	protected:
		/**
		 * Constructor.
		 */
		MovableObject();

		/**
		 * Destructor.
		 */
		virtual ~MovableObject();

	protected:
		/**
		 * Get position from active buffer.
		 * @return position from active buffer.
		 */
		math::const_PointRef<2> posA() const;

		/**
		 * Get specific position coordinate from active buffer.
		 * @param i coordinate.
		 * @return position coordinate from active buffer.
		 */
		real_t posA(std::size_t i);

		/**
		 * Get position from background buffer.
		 * @return position from background buffer.
		 */
		math::const_PointRef<2> posB() const;

		/**
		 * Get specific position coordinate from background buffer.
		 * @param i coordinate.
		 * @return position coordinate from background buffer.
		 */
		real_t posB(std::size_t i);

		/**
		 * Set position in background buffer.
		 * @param pos new position.
		 */
		void setPosB(math::const_PointRef<2> pos);

		/**
		 * Set position in background buffer.
		 * @param x x coordinate of new position.
		 * @param y y coordinate of new position.
		 */
		void setPosB(real_t x, real_t y);

		/**
		 * Update transformation matrix and inverted transformation matrix.
		 * Calling this function denotes that background parameter, which
		 * affects transformation matrix has been changed and matrices should
		 * be updated. In response function will call constructTMatrix() and
		 * constructTMatrixInv() (request *may* be lazy evaluated and these
		 * functions will not be called immediately).
		 */
		void updateTMatricesB();

		/**
		 * Construct transformation matrix. This function should be re-implemented whenever
		 * derived class provides own transformation parameters.
		 * @param tMatrix transformation matrix (existing data will be overwritten).
		 *
		 * @note if transformation parameter is double buffered, then background buffer values shall be used.
		 *
		 * @todo swap buffers before constructTMatrix(active, active) calls.
		 */
		virtual void constructTMatrix(phy::TransformationMatrix & tMatrix);

		/**
		 * Construct inverted transformation matrix. This function should be re-implemented
		 * whenever derived class provides own transformation parameters.
		 * @param tInvMatrix inverted transformation matrix (existing data will be overwritten).
		 *
		 * @note if transformation parameter is double buffered, then background buffer values shall be used.
		 */
		virtual void constructTMatrixInv(phy::TransformationMatrix & tMatrixInv);

	private:
		utils::DoubleBufferController m_doubleBufferController;	///< Double buffer controller.
		utils::DoubleBuffer<math::Point<2> > m_pos;				///< Position (double buffered).
		utils::DoubleBuffer<phy::TransformationMatrix> m_tMatrix;		///< Transformation matrix (double buffered).
		utils::DoubleBuffer<phy::TransformationMatrix> m_tMatrixInv;	///< Inverted transformation matrix (double buffered).
//		utils::DoubleBuffer<bool> m_updateTMatrix;
};

}
}

#endif /* GPX_Phy2d_MOVABLEOBJECT_HPP_ */
