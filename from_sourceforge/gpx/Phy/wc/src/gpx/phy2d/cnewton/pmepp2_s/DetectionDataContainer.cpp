///**
// * @file
// * @brief .
// */
//
//#include "../../../../../include/gpx/phy2d/cnewton/pmepp_s/DetectionDataContainer.hpp"
//#include "../../../../../include/gpx/phy2d/cnewton/pmepp_s/ACoefsMapper.hpp"
//#include "../../../../../include/gpx/phy2d/cnewton/pmepp_s/BCoefsMapper.hpp"
//#include "../../../../../include/gpx/phy2d/cnewton/pmepp_s/ICFixed.hpp"
//#include "../../../../../include/gpx/phy2d/cnewton/pmepp_s/ICMovable.hpp"
//#include "../../../../../include/gpx/phy2d/cnewton/pmepp_s/PassiveDetectionContainer.hpp"
//
//namespace gpx {
//namespace phy2d {
//namespace cnewton {
//namespace pmepp_s {
//
//DetectionData::DetectionData():
//	counterpart(0),
//	indices(0)
//{
//}
//
//DetectionDataContainer::iterator DetectionDataContainer::begin()
//{
//	return m_draftNode->next;
//}
//
//DetectionDataContainer::const_iterator DetectionDataContainer::begin() const
//{
//	return m_draftNode->next;
//}
//
//DetectionDataContainer::iterator DetectionDataContainer::end()
//{
//	return m_draftNode;
//}
//
//DetectionDataContainer::const_iterator DetectionDataContainer::end() const
//{
//	return m_draftNode;
//}
//
//DetectionDataContainer::reverse_iterator DetectionDataContainer::rbegin()
//{
//	return reverse_iterator(end());
//}
//
//DetectionDataContainer::const_reverse_iterator DetectionDataContainer::rbegin() const
//{
//	return const_reverse_iterator(end());
//}
//
//DetectionDataContainer::reverse_iterator DetectionDataContainer::rend()
//{
//	return reverse_iterator(begin());
//}
//
//DetectionDataContainer::const_reverse_iterator DetectionDataContainer::rend() const
//{
//	return const_reverse_iterator(begin());
//}
//
//std::size_t DetectionDataContainer::size() const
//{
//	return m_size;
//}
//
//const PointData & DetectionDataContainer::point(std::size_t i) const
//{
//	const_iterator dData = begin();
//	while (i >= dData->points.size()) {
//		i -= dData->points.size();
//		++dData;
//		GPX_ASSERT(dData != end(), "point index is out of bounds");
//	};
//	GPX_ASSERT(i < dData->points.size(), "point index is out of bounds");
//	return dData->points[i];
//}
//
//std::size_t DetectionDataContainer::pointsNum() const
//{
//	std::size_t result = 0;
//	for (const_iterator i = begin(); i != end(); ++i)
//		result += i->points.size();
//	return result;
//}
//
//std::size_t DetectionDataContainer::collisionIndex(std::size_t i) const
//{
//	Node * node = m_draftNode->next;
//	while (i >= node->data.indices->size()) {
//		i -= node->data.indices->size();
//		node = node->next;
//		GPX_ASSERT(node != m_draftNode, "point index is out of bounds");
//	}
//	GPX_ASSERT(i < node->data.indices->size(), "point index is out of bounds");
//	return node->data.indices->operator [](i);
//}
//
//const DetectionData & DetectionDataContainer::pointDetectionData(std::size_t i) const
//{
//	const_iterator dData = begin();
//	while (i >= dData->points.size()) {
//		i -= dData->points.size();
//		++dData;
//		GPX_ASSERT(dData != end(), "point index is out of bounds");
//	};
//	GPX_ASSERT(i < dData->points.size(), "point index is out of bounds");
//	return *dData;
//}
//
//real_t DetectionDataContainer::dt() const
//{
//	return m_dt;
//}
//
//const ICMovable * DetectionDataContainer::moving() const
//{
//	return m_moving;
//}
//
//DetectionDataContainer::DetectionDataContainer(const real_t & dt, const ICMovable * & moving, PassiveDetectionContainer & passive):
//	m_dt(dt),
//	m_moving(moving),
//	m_size(0),
//	m_draftNode(new DetectionDataContainer::Node(passive, 0, 0))
//{
//	m_draftNode->next = m_draftNode;
//	m_draftNode->prev = m_draftNode;
//}
//
//DetectionDataContainer::~DetectionDataContainer()
//{
//	delete m_draftNode;
//}
//
//void DetectionDataContainer::commit(PassiveDetectionContainer & newDraftOWner)
//{
//	//list is cyclic and is defined as follows:
//	// end -> 1st -> ... -> last -> end
//	// end <- 1st <- ... <- last <- end
//	//where: -> next, <- prev.
//
//	//m_draft is current end (but will become last)
//	//m_draft->next points to 1st element
//	DetectionDataContainer::Node * newDraft = new DetectionDataContainer::Node(newDraftOWner, m_draftNode->next, m_draftNode);
//	m_draftNode->next->prev = newDraft;	//m_draft->next->prev (1st->prev) points to new end
//	m_draftNode->next = newDraft;		//m_draft->next (last->next) points to new end also
//	m_draftNode = newDraft;				//set newDraft as new end
//	m_size++;
//}
//
//void DetectionDataContainer::conjugate(Node * other)
//{
//	m_draftNode->data.indices = other->data.indices;
//	m_draftNode->other = other;
//	other->other = m_draftNode;
//}
//
//void DetectionDataContainer::erase(DetectionDataContainer::Node * node)
//{
//	node->prev->next = node->next;
//	node->next->prev = node->prev;
//	delete node;
//	m_size--;
//}
//
////void Detections::clearSiblingIndices(Node * node)
////{
////	for (Node * sibling = node->next; sibling != m_draftNode; sibling = sibling->next) {
////		if (!sibling->pointIndices->empty()) {
////			sibling->pointIndices->clear();
////			sibling->other->owner.clearSiblingIndices(sibling->other);
////		}
////	}
////	for (Node * sibling = node->prev; sibling != m_draftNode; sibling = sibling->prev)
////		if (!sibling->pointIndices->empty()) {
////			sibling->pointIndices->clear();
////			sibling->other->owner.clearSiblingIndices(sibling->other);
////		}
////}
////
////std::size_t Detections::createNodeIndices(Node * node, std::size_t n)
////{
////	for (PointDataContainer::iterator i = node->data.points.begin(); i != node->data.points.end(); ++i)
////		node->pointIndices->push_back(n++);
////	return n;
////}
////
////std::size_t Detections::createSiblingIndices(Node * node, std::size_t n)
////{
////	for (Node * sibling = node->prev; sibling != m_draftNode; sibling = sibling->prev)
////		if (sibling->pointIndices->empty()) {
////			n = createNodeIndices(sibling, n);
////			n = sibling->other->parent.createSiblingIndices(sibling->other, n);
////		}
////	for (Node * sibling = node->next; sibling != m_draftNode; sibling = sibling->next)
////		if (sibling->pointIndices->empty()) {
////			n = createNodeIndices(sibling, n);
////			n = sibling->other->parent.createSiblingIndices(sibling->other, n);
////		}
////	return n;
////}
//
////void Detections::collectSiblingACoefs(Node * node, math::Matrix<> & a) const
////{
////	if (m_visiting)
////		return;
////
////	m_visiting = true;
////	ACoefsMapper mapper(*this, a);
////	passive()->aCoefs(*this, mapper);
////	for (Node * sibling = node->prev; sibling != m_draftNode; sibling = sibling->prev)
////		sibling->other->parent.collectSiblingACoefs(sibling->other, a);
////	for (Node * sibling = node->next; sibling != m_draftNode; sibling = sibling->next)
////		sibling->other->parent.collectSiblingACoefs(sibling->other, a);
////	m_visiting = false;
////}
//
////void Detections::collectSiblingBCoefs(Node * node, math::Vector<> & b) const
////{
////	if (m_visiting)
////		return;
////
////	m_visiting = true;
////	BCoefsMapper mapper(*this, b);
////	passive()->bCoefs(*this, mapper);
////	for (Node * sibling = node->prev; sibling != m_draftNode; sibling = sibling->prev)
////		sibling->other->parent.collectSiblingBCoefs(sibling->other, b);
////	for (Node * sibling = node->next; sibling != m_draftNode; sibling = sibling->next)
////		sibling->other->parent.collectSiblingBCoefs(sibling->other, b);
////	m_visiting = false;
////}
//
////void Detections::applySiblingNormalImps(Node * node, math::Vector<> & projs) const
////{
////	if (m_visiting)
////		return;
////
////	m_visiting = true;
////	if (movable())
////		for (std::size_t i = 0; i < pointsNum(); ++i)
////			applyImp(point(pointIndex(i)), projs(pointIndex(i)));
////
////	for (Node * sibling = node->prev; sibling != m_draftNode; sibling = sibling->prev)
////		sibling->other->parent.applySiblingNormalImps(sibling->other, projs);
////	for (Node * sibling = node->next; sibling != m_draftNode; sibling = sibling->next)
////		sibling->other->parent.applySiblingNormalImps(sibling->other, projs);
////	m_visiting = false;
////}
//
//DetectionDataContainer::Node * DetectionDataContainer::draftNode()
//{
//	return m_draftNode;
//}
//
//const DetectionDataContainer::Node * DetectionDataContainer::draftNode() const
//{
//	return m_draftNode;
//}
//
////void Detections::applyImp(const PointData & pData, real_t proj) const
////{
////	math::Vector<2> Fdt = pData.normal.inverse() * proj;
////	GPX_DEBUG("Fdt: " << Fdt);
////	movable()->applyImpulse(Fdt, pData.pre);
////}
//
//DetectionDataContainer::Node::Node(PassiveDetectionContainer & p_owner, Node * p_next, Node * p_prev):
//	owner(p_owner),
//	next(p_next),
//	prev(p_prev),
//	other(0)
//{
//}
//
////Detections::Iterator::Iterator():
////	m_pos(0)
////{
////}
//
//DetectionDataContainer::Iterator::Iterator(DetectionDataContainer::Node * pos):
//	m_pos(pos)
//{
//}
//
//DetectionDataContainer::iterator::reference DetectionDataContainer::Iterator::operator *() const
//{
//	return m_pos->data;
//}
//
//DetectionDataContainer::iterator::pointer DetectionDataContainer::Iterator::operator ->() const
//{
//	return & m_pos->data;
//}
//
//DetectionDataContainer::iterator & DetectionDataContainer::Iterator::operator ++()
//{
//	m_pos = m_pos->next;
//	return *this;
//}
//
//DetectionDataContainer::iterator DetectionDataContainer::Iterator::operator ++(int)
//{
//	Iterator tmp = *this;
//	m_pos = m_pos->next;
//	return tmp;
//}
//
//DetectionDataContainer::iterator & DetectionDataContainer::Iterator::operator --()
//{
//	m_pos = m_pos->prev;
//	return *this;
//}
//
//DetectionDataContainer::iterator DetectionDataContainer::Iterator::operator --(int)
//{
//	Iterator tmp = *this;
//	m_pos = m_pos->prev;
//	return tmp;
//}
//
//bool DetectionDataContainer::Iterator::operator ==(const DetectionDataContainer::Iterator & other) const
//{
//	return m_pos == other.m_pos;
//}
//
//bool DetectionDataContainer::Iterator::operator !=(const DetectionDataContainer::Iterator & other) const
//{
//	return m_pos != other.m_pos;
//}
//
//DetectionDataContainer::Node * DetectionDataContainer::Iterator::pos() const
//{
//	return m_pos;
//}
//
////Detections::const_Iterator::const_Iterator():
////	m_pos(0)
////{
////}
//
//DetectionDataContainer::const_Iterator::const_Iterator(const DetectionDataContainer::Node * pos):
//	m_pos(pos)
//{
//}
//
//DetectionDataContainer::const_iterator::reference DetectionDataContainer::const_Iterator::operator *() const
//{
//	return m_pos->data;
//}
//
//DetectionDataContainer::const_iterator::pointer DetectionDataContainer::const_Iterator::operator ->() const
//{
//	return & m_pos->data;
//}
//
//DetectionDataContainer::const_iterator & DetectionDataContainer::const_Iterator::operator ++()
//{
//	m_pos = m_pos->next;
//	return *this;
//}
//
//DetectionDataContainer::const_iterator DetectionDataContainer::const_Iterator::operator ++(int)
//{
//	const_Iterator tmp = *this;
//	m_pos = m_pos->next;
//	return tmp;
//}
//
//DetectionDataContainer::const_iterator & DetectionDataContainer::const_Iterator::operator --()
//{
//	m_pos = m_pos->prev;
//	return *this;
//}
//
//DetectionDataContainer::const_iterator DetectionDataContainer::const_Iterator::operator --(int)
//{
//	const_iterator tmp = *this;
//	m_pos = m_pos->prev;
//	return tmp;
//}
//
//bool DetectionDataContainer::const_iterator::operator ==(const DetectionDataContainer::const_iterator & other) const
//{
//	return m_pos == other.m_pos;
//}
//
//bool DetectionDataContainer::const_iterator::operator !=(const DetectionDataContainer::const_iterator & other) const
//{
//	return m_pos != other.m_pos;
//}
//
//const DetectionDataContainer::Node * DetectionDataContainer::const_Iterator::pos() const
//{
//	return m_pos;
//}
//
//
//DetectionDataContainer::const_DIPData::const_DIPData(const DetectionDataContainer::const_iterator & p_detection):
//	detection(p_detection),
//	index(p_detection->indices->begin()),
//	point(p_detection->points.begin())
//{
//}
//
//
//DetectionDataContainer::const_DIPFacade::const_DIPFacade(const DetectionDataContainer::const_iterator & detection):
//		m_pos(detection)
//{
//};
//
//DetectionDataContainer::const_DIPFacade::reference DetectionDataContainer::const_DIPFacade::operator *() const
//{
//	return m_pos;
//}
//
//DetectionDataContainer::const_DIPFacade::pointer DetectionDataContainer::const_DIPFacade::operator ->() const
//{
//	return & m_pos;
//}
//
//DetectionDataContainer::const_DIPFacade & DetectionDataContainer::const_DIPFacade::operator ++()
//{
//	if (++m_pos.point == m_pos.detection->points.end()) {
//		++m_pos.detection;
//		//draft node will have no collision points
//		if (m_pos.detection->points.size() != 0) {
//			m_pos.point = m_pos.detection->points.begin();
//			m_pos.index = m_pos.detection->indices->begin();
//		}
//	} else
//		++m_pos.index;
//	return *this;
//}
//
//DetectionDataContainer::const_DIPFacade DetectionDataContainer::const_DIPFacade::operator ++(int)
//{
//	const_DIPFacade tmp = *this;
//	this->operator ++();
//	return tmp;
//}
//
//bool DetectionDataContainer::const_DIPFacade::operator ==(const DetectionDataContainer::const_iterator & other) const
//{
//	return m_pos.detection == other;
//}
//
//bool DetectionDataContainer::const_DIPFacade::operator !=(const DetectionDataContainer::const_iterator & other) const
//{
//	return m_pos.detection != other;
//}
//
//
//DetectionDataContainer::DIPData::DIPData(const DetectionDataContainer::iterator & p_detection):
//	detection(p_detection),
//	index(detection->indices->begin()),
//	point(detection->points.begin())
//{
//}
//
//
//DetectionDataContainer::DIPFacade::DIPFacade(const DetectionDataContainer::iterator & detection):
//		m_pos(detection)
//{
//};
//
//DetectionDataContainer::DIPFacade::reference DetectionDataContainer::DIPFacade::operator *()
//{
//	return m_pos;
//}
//
//DetectionDataContainer::DIPFacade::pointer DetectionDataContainer::DIPFacade::operator ->()
//{
//	return & m_pos;
//}
//
//DetectionDataContainer::DIPFacade & DetectionDataContainer::DIPFacade::operator ++()
//{
//	if (++m_pos.point == m_pos.detection->points.end()) {
//		++m_pos.detection;
//		//draft node will have no collision points
//		if (m_pos.detection->points.size() != 0) {
//			m_pos.point = m_pos.detection->points.begin();
//			m_pos.index = m_pos.detection->indices->begin();
//		}
//	} else
//		++m_pos.index;
//	return *this;
//}
//
//DetectionDataContainer::DIPFacade DetectionDataContainer::DIPFacade::operator ++(int)
//{
//	DIPFacade tmp = *this;
//	this->operator ++();
//	return tmp;
//}
//
//bool DetectionDataContainer::DIPFacade::operator ==(const DetectionDataContainer::iterator & other) const
//{
//	return m_pos.detection == other;
//}
//
//bool DetectionDataContainer::DIPFacade::operator !=(const DetectionDataContainer::iterator & other) const
//{
//	return m_pos.detection != other;
//}
//
//}
//}
//}
//}
//
////(c)MP: Copyright © 2013, Michał Policht. All rights reserved.
////(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
////(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
