///**
// * @file
// * @brief .
// */
//
//#ifndef GPX_Phy2d_CNEWTON_PMEPP_S_DETECTIONDATACONTAINER_HPP_
//#define GPX_Phy2d_CNEWTON_PMEPP_S_DETECTIONDATACONTAINER_HPP_
//
//#include "../../cdetect/interseg/ICPolyGroup.hpp"
//
//#include <gpx/utils/NonCopyable.hpp>
//
//#include <vector>
//#include <iterator>
//
//namespace gpx {
//namespace phy2d {
//namespace cnewton {
//namespace pmepp_s {
//
//class ICFixed;
//class ICMovable;
//class PassiveDetectionContainer;
//
///**
// * Point detection data. Collision detection data.
// */
//struct PointData
//{
//	math::Point<2> pre;			///< C-vertex position before collision (given in local coordinates).
//	math::Point<2> post;			///< C-vertex position after collision (given in local coordinates).
//	math::Vector<2> normal;			///< Normal to the "bumper's" surface (calculated by "bumper", given in global coordinates).
//	bool wedge;						///< Indicates if object collides as a wedge or a bumper.
//	cdetect::interseg::ICPolyGroup::element_t element;	///< Colliding element index.
//};
//
///**
// * Point data container.
// */
//typedef std::vector<PointData> PointDataContainer;
//
///**
// * Point indices container.
// */
//typedef std::vector<std::size_t> CollisionIndicesContainer;
//
///**
// * Detection data.
// */
//struct GPX_API DetectionData
//{
////	real_t dt;
//	ICFixed * counterpart;
//	CollisionIndicesContainer * indices; //collision indices
//	PointDataContainer points;
//
//	DetectionData();
//};
//
///**
// * Detection data container. Contains all detection data of owning object. As standard
// * container it provides methods to access, maintain and manipulate data. Specifically
// * DetectionDataContainer provides two ways to access point related data: subscript access
// * and iterator type of access. Subscript access is realized via sequential indexing in
// * respect to container object. This may create some confusion, when one asks for point
// * index, because DetectionData contains a member named @a indices, which assigns an index
// * to each collision point. To distinguish them, the latter will be called collision indices.
// * Collision index can be easily found by using collisionIndex() method or iterator access
// * with DIPFacade (or const_DIPFacade).
// */
//class GPX_API DetectionDataContainer : utils::NonCopyable
//{
//	class Iterator;
//	class const_Iterator;
//
//	public:
//		typedef DetectionData value_type;
//		typedef value_type & reference;
//		typedef const value_type & const_reference;
//		typedef value_type * pointer;
//		typedef const value_type * const_pointer;
//		typedef std::ptrdiff_t difference_type;
//		typedef std::size_t size_type;
//		typedef Iterator iterator;
//		typedef const_Iterator const_iterator;
//		typedef std::reverse_iterator<iterator> reverse_iterator;
//		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
//		struct DIPData;
//		class DIPFacade;
//		struct const_DIPData;
//		class const_DIPFacade;
//
//	public:
//		/**
//		 * Iterator begin.
//		 * @return iterator begin.
//		 */
//		iterator begin();
//
//		/**
//		 * Const iterator begin.
//		 * @return const iterator begin.
//		 */
//		const_iterator begin() const;
//
//		/**
//		 * Iterator end.
//		 * @return iterator end.
//		 */
//		iterator end();
//
//		/**
//		 * Const iterator end.
//		 * @return const iterator end.
//		 */
//		const_iterator end() const;
//
//		/**
//		 * Reverse iterator begin.
//		 * @return iterator begin.
//		 */
//		reverse_iterator rbegin();
//
//		/**
//		 * Const reverse iterator begin.
//		 * @return const iterator begin.
//		 */
//		const_reverse_iterator rbegin() const;
//
//		/**
//		 * Reverse iterator end.
//		 * @return iterator end.
//		 */
//		reverse_iterator rend();
//
//		/**
//		 * Const reverse iterator end.
//		 * @return const iterator end.
//		 */
//		const_reverse_iterator rend() const;
//
//		/**
//		 * Get size.
//		 * @return size of container in terms of number of nodes.
//		 */
//		std::size_t size() const;
//
//		const PointData & point(std::size_t i) const;
//
//		/**
//		 * Get number of collision points.
//		 * @return number of collision points.
//		 */
//		std::size_t pointsNum() const;
//
//		/**
//		 * Get collision index for specific point.
//		 * @param i point index.
//		 * @return collision index.
//		 */
//		std::size_t collisionIndex(std::size_t i) const;
//
//		/**
//		 * Get detection data related to specific collision point.
//		 * @param i point index.
//		 * @return detection data related to specific collision point.
//		 */
//		const DetectionData & pointDetectionData(std::size_t i) const;
//
//		/**
//		 * Get time differential.
//		 * @return amount of time during which current collision is performed.
//		 */
//		real_t dt() const;
//
//		/**
//		 * Get moving object.
//		 * @return object that is participating as moving in current collision.
//		 */
//		const ICMovable * moving() const;
//
//	protected:
//		struct Node
//		{
//			PassiveDetectionContainer & owner;
////			Detections & parent;
//			Node * next;
//			Node * prev;
//			Node * other;
////			PointIndicesContainer * pointIndices;
//			DetectionData data;
//
//			Node(PassiveDetectionContainer & p_owner, Node * next, Node * prev);
//		};
//
//	protected:
//		DetectionDataContainer(const real_t & dt, const ICMovable * & moving, PassiveDetectionContainer & passive);
//
//		~DetectionDataContainer();
//
//	protected:
//		void commit(PassiveDetectionContainer & newDraftOwner);
//
//		void conjugate(Node * other);
//
//		void erase(Node * node);
//
//		Node * draftNode();
//
//		const Node * draftNode() const;
//
//	private:
//		const real_t & m_dt;
//		const ICMovable * & m_moving;
//		std::size_t m_size;
//		Node * m_draftNode;
//};
//
///**
// * Detections iterator.
// */
//class GPX_API DetectionDataContainer::Iterator
//{
//	friend class DetectionDataContainer;
//
//	public:
//		typedef DetectionData value_type;
//		typedef value_type & reference;
//		typedef value_type * pointer;
//		typedef std::ptrdiff_t difference_type;
//		typedef std::size_t size_type;
//
//	public:
////		Iterator();
//
//		//generated copy ctor ok
//
//		//generated operator = ok
//
//		//generated dtor ok
//
//	public:
//		reference operator *() const;
//
//		pointer operator ->() const;
//
//		iterator & operator ++();
//
//		iterator operator ++(int);
//
//		iterator & operator --();
//
//		iterator operator --(int);
//
//		bool operator ==(const iterator & other) const;
//
//		bool operator !=(const iterator & other) const;
//
//	private:
//		Iterator(DetectionDataContainer::Node * pos);
//
//		DetectionDataContainer::Node * pos() const;
//
//	private:
//		DetectionDataContainer::Node * m_pos;
//};
//
///**
// * Detections const iterator.
// */
//class GPX_API DetectionDataContainer::const_Iterator
//{
//	friend class DetectionDataContainer;
//
//	public:
//		typedef DetectionData value_type;
//		typedef const value_type & reference;
//		typedef const value_type * pointer;
//		typedef std::ptrdiff_t difference_type;
//		typedef std::size_t size_type;
//
//	public:
////		const_Iterator();
//
//		//generated copy ctor ok
//
//		//generated operator = ok
//
//		//generated dtor ok
//
//	public:
//		reference operator *() const;
//
//		pointer operator ->() const;
//
//		const_iterator & operator ++();
//
//		const_iterator operator ++(int);
//
//		const_iterator & operator --();
//
//		const_iterator operator --(int);
//
//		bool operator ==(const const_iterator & other) const;
//
//		bool operator !=(const const_iterator & other) const;
//
//	private:
//		const_Iterator(const DetectionDataContainer::Node * pos);
//
//		const DetectionDataContainer::Node * pos() const;
//
//	private:
//		const DetectionDataContainer::Node * m_pos;
//};
//
//
//struct GPX_API DetectionDataContainer::const_DIPData
//{
//	DetectionDataContainer::const_iterator detection;
//	CollisionIndicesContainer::const_iterator index;
//	PointDataContainer::const_iterator point;
//
//	const_DIPData(const DetectionDataContainer::const_iterator & p_detection);
//};
//
///**
// * Detection-index-point iterator facade (const version).
// */
//class GPX_API DetectionDataContainer::const_DIPFacade
//{
//	public:
//		typedef const_DIPData value_type;
//		typedef const value_type & reference;
//		typedef const value_type * pointer;
//		typedef std::ptrdiff_t difference_type;
//		typedef std::size_t size_type;
//
//	public:
//		const_DIPFacade(const DetectionDataContainer::const_iterator & detection);
//
//	public:
//		reference operator *() const;
//
//		pointer operator ->() const;
//
//		const_DIPFacade & operator ++();
//
//		const_DIPFacade operator ++(int);
//
//		bool operator ==(const DetectionDataContainer::const_iterator & other) const;
//
//		bool operator !=(const DetectionDataContainer::const_iterator & other) const;
//
//	private:
//		value_type m_pos;
//
//};
//
//struct GPX_API DetectionDataContainer::DIPData
//{
//	DetectionDataContainer::iterator detection;
//	CollisionIndicesContainer::iterator index;
//	PointDataContainer::iterator point;
//
//	DIPData(const DetectionDataContainer::iterator & p_detection);
//};
//
///**
// * Detection-index-point iterator facade.
// */
//class GPX_API DetectionDataContainer::DIPFacade
//{
//	public:
//		typedef DIPData value_type;
//		typedef value_type & reference;
//		typedef value_type * pointer;
//		typedef std::ptrdiff_t difference_type;
//		typedef std::size_t size_type;
//
//	public:
//		DIPFacade(const DetectionDataContainer::iterator & detection);
//
//	public:
//		reference operator *();
//
//		pointer operator ->();
//
//		DIPFacade & operator ++();
//
//		DIPFacade operator ++(int);
//
//		bool operator ==(const DetectionDataContainer::iterator & other) const;
//
//		bool operator !=(const DetectionDataContainer::iterator & other) const;
//
//	private:
//		value_type m_pos;
//
//};
//
//}
//}
//}
//}
//
//namespace std
//{
//	template <>
//	struct iterator_traits<gpx::phy2d::cnewton::pmepp_s::DetectionDataContainer::iterator>
//	{
//		typedef bidirectional_iterator_tag iterator_category;
//		typedef gpx::phy2d::cnewton::pmepp_s::DetectionDataContainer::iterator::value_type value_type;
//		typedef gpx::phy2d::cnewton::pmepp_s::DetectionDataContainer::iterator::difference_type difference_type;
//		typedef gpx::phy2d::cnewton::pmepp_s::DetectionDataContainer::iterator::pointer pointer;
//		typedef gpx::phy2d::cnewton::pmepp_s::DetectionDataContainer::iterator::reference reference;
//	};
//
//	template <>
//	struct iterator_traits<gpx::phy2d::cnewton::pmepp_s::DetectionDataContainer::const_iterator>
//	{
//		typedef bidirectional_iterator_tag iterator_category;
//		typedef gpx::phy2d::cnewton::pmepp_s::DetectionDataContainer::const_iterator::value_type value_type;
//		typedef gpx::phy2d::cnewton::pmepp_s::DetectionDataContainer::const_iterator::difference_type difference_type;
//		typedef gpx::phy2d::cnewton::pmepp_s::DetectionDataContainer::const_iterator::pointer pointer;
//		typedef gpx::phy2d::cnewton::pmepp_s::DetectionDataContainer::const_iterator::reference reference;
//	};
//}
//
//#endif /* GPX_Phy2d_CNEWTON_PMEPP_S_DETECTIONDATACONTAINER_HPP_ */
//
////(c)MP: Copyright © 2013, Michał Policht. All rights reserved.
////(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
////(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
