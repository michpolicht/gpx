/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CNEWTON_PMEPP2_S_COLLIDER_HPP_
#define GPX_Phy2d_CNEWTON_PMEPP2_S_COLLIDER_HPP_

#include "../../../phy_config.hpp"
#include "../../../phy/NewtonPlasticityTable.hpp"
#include "BasicExecutor.hpp"
#include "Introspector.hpp"	//@todo wrap inside ifndfef NDEBUG condition perhaps

//#include <gpx/utils/DynamicArray.hpp>
#include <gpx/utils/functions.hpp>
#include <gpx/ext/UnorderedMap.hpp>
#include <gpx/ext/UnorderedSet.hpp>

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

/**
 * Sequential, multi-element, parallel-point collider with intersecting segments detection
 * and normals, variant 5. In this variant one movable and any number of passive objects,
 * which directly participate in collision with movable, are represented by a system of
 * linear equations. Full collision trees are built for objects participating in collision.
 */
class GPX_API Collider
{
	public:
		static const std::size_t INITIAL_SUBSEQUENT_COLLISION_LIMIT = 2;
		static const std::size_t INITIAL_OBJECTS_PER_COLLISION = 8;	///< Expected maximal number of objects per collision (this is for memory reservation only, not a strict limit).
		static const std::size_t INITIAL_CPOINTS_PER_OBJECT = 32;	///< Expected maximal number of collision points per object (this is for memory reservation only, not a strict limit).

	public:
		typedef class ACoefsMapper ACoefsMapper;
		typedef class BCoefsMapper BCoefsMapper;

	public:
		Collider(BasicExecutor & collisionContractor = DefaultCollisionContractor(),
				 phy::NewtonPlasticityTable & m_plasticityTable = phy::NewtonPlasticityTable::Instance());

		virtual ~Collider();

	public:
		static BasicExecutor & DefaultCollisionContractor();

	public:
		/**
		 * Set introspector.
		 * @param introspector introspector object.
		 *
		 * @note this function does nothing if GPX_NO_INTROSPECT macro
		 * has been defined.
		 */
		void setIntrospector(Introspector & introspector);

		/**
		 * Get subsequent collision limit.
		 * @return current subsequent collision limit.
		 */
		int subsequentCollisionLimit() const;

		/**
		 * Set subsequent collision limit.
		 * @param limit new subsequent collision limit.
		 */
		void setSubsequentCollisionLimit(int limit);

		/**
		 * Add fixed object.
		 * @param obj object to add.
		 *
		 * @warning do not add objects during update().
		 */
		void addFixed(ICFixed * obj);

		/**
		 * Remove fixed object.
		 * @param obj object to remove.
		 *
		 * @warning do not remove objects during update().
		 */
		void removeFixed(ICFixed * obj);

		/**
		 * Add movable object.
		 * @param obj object to add.
		 *
		 * @warning do not add objects during update().
		 */
		void addMovable(ICMovable * obj);

		/**
		 * Remove movable object.
		 * @param obj object to remove.
		 *
		 * @warning do not remove objects during update().
		 */
		void removeMovable(ICMovable * obj);

		//phy::ITimePerformer
		void update(real_t dt);

	protected:
		/**
		 * Point iteration state. Helper structure to ease iteration through all elements of
		 * wedge and bumper with wedge vertices.
		 */
		struct SeekContactState
		{
			const ICFixed & wedge;
			const ICFixed & bumper;
			cdetect::interseg::ICPolyGroup::element_t wi;	///< Wedge element index.
			cdetect::interseg::ICPolyGroup::element_t bi;	///< Bumper element index.
			const model::VertexData<2> * vertices;			///< Actual set of c-vertices.
			model::VertexData<2>::const_iterator vertIt;	///< Vertex iterator.

			SeekContactState(const ICFixed * const p_wedge, const ICFixed * const p_bumper);

			bool isValid();

			void inc();
		};

		struct DoubleBufferSwapper
		{
			ICMovable * firstMov;
			ICMovable * secondMov;

			DoubleBufferSwapper(ICMovable * p_firstMov, ICMovable * p_secondMov);

			void swapBuffers();
		};

		struct MovableData
		{
			bool checked;

			MovableData():
				checked(false)
			{
			}
		};

		typedef typename ext::UnorderedSet<ICFixed *> FixedContainer;
		typedef typename ext::UnorderedMap<ICMovable *, MovableData *> MovablesContainer;

	protected:
		phy::NewtonPlasticityTable & plasticityTable();

		const FixedContainer & fixed() const;

		FixedContainer & fixed();

		const MovablesContainer & movables() const;

		MovablesContainer & movables();

	private:
		typedef std::vector<ICMovable *> DislocMovablesContainer;

		void fillCluster(Cluster & cluster, DetectionData & firstData);

		void moveBackClusters(ClustersContainer & clusters) const;

		void fulfillClusters(ClustersContainer & clusters);

		void fulfillCluster(Cluster & cluster, DetectionData & firstData);

		/**
		 * Test pair of objects for collision.
		 * @param startIndex value of index to start with.
		 * @param firstData data to be filled for first potentially colliding object.
		 * @param secondData data to be filled for second potentially colliding object.
		 * @return last index. If objects are not colliding returned value is equal to
		 * @a startIndex. Otherwise it will be @a startIndex incremented by a number
		 * of contacts.
		 */
		std::size_t testPairCollect(std::size_t startIndex, DetectionData & firstData, DetectionData & secondData);

		bool seekContactCollect(SeekContactState & s, DoubleBufferSwapper & b, ContactData & wedgeData, ContactData & bumperData);

		void handleCollisions(ClustersContainer & clusters);

		void updateClusters(ClustersContainer & clusters, real_t dt);

		void dislocateMovables(DislocMovablesContainer & in, DislocMovablesContainer & out);

		bool testPairDislocate(ICMovable & mov, const ICFixed & passive, ICMovable * passiveMov);

		bool seekContactDislocate(SeekContactState & s, DoubleBufferSwapper & b, math::Vector<2> & normal, math::Vector<2> & dsp);

		void dislocateMovable(ICMovable & mov, const math::Vector<2> & normal, const math::Vector<2> & dsp);

//		void handleCollisions(MovableDetectionContainer * movDetections);

	private:
		BasicExecutor & m_collisionContractor;
		phy::NewtonPlasticityTable & m_plasticityTable;
		int m_subsequentCollisionLimit;
		math::Matrix<> m_a; //equation matrix for the A Fdt = B system.
		math::Matrix<> m_aWC; //working copy of matrix A.
		math::Vector<> m_b; //equation vector for the A Fdt = B system.
		math::Vector<> m_bWC; //working copy of vector B.
		FixedContainer m_fixed;
		MovablesContainer m_movables;
#ifndef GPX_NO_INTROSPECT
		Introspector m_introspectorInstance;
		Introspector * m_introspector;
#endif
};

}
}
}
}

#endif /* GPX_Phy2d_CNEWTON_PMEPP2_S_COLLIDER_HPP_ */

//(c)MP: Copyright © 2014, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
