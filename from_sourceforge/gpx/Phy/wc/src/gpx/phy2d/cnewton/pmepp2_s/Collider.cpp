/**
 * @file
 * @brief .
 */

#include "../../../../../include/gpx/phy2d/cnewton/pmepp2_s/Collider.hpp"
#include "../../../../../include/gpx/phy2d/cnewton/pmepp2_s/Cluster.hpp"
#include "../../../../../include/gpx/phy2d/PhyObject.hpp"

#include <vector>
#include <gpx/math/Solver.hpp>
#include <gpx/math/NNSolver.hpp>

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

Collider::Collider(BasicExecutor & collisionContractor, phy::NewtonPlasticityTable & plasticityTable):
		m_collisionContractor(collisionContractor),
		m_plasticityTable(plasticityTable),
		m_subsequentCollisionLimit(INITIAL_SUBSEQUENT_COLLISION_LIMIT),
		m_a(0u, 0u, INITIAL_CPOINTS_PER_OBJECT * INITIAL_CPOINTS_PER_OBJECT),
		m_aWC(0u, 0u, INITIAL_CPOINTS_PER_OBJECT * INITIAL_CPOINTS_PER_OBJECT),
		m_b(0u, INITIAL_CPOINTS_PER_OBJECT),
		m_bWC(0u, INITIAL_CPOINTS_PER_OBJECT)
{
#ifndef GPX_NO_INTROSPECT
	m_introspector = & m_introspectorInstance;
#endif
}

Collider::~Collider()
{
	// Delete movables wrappers, which are allocated on a heap by addMovable().
	for (MovablesContainer::iterator mov = movables().begin(); mov != movables().end(); ++mov)
		delete mov->second;
}

BasicExecutor & Collider::DefaultCollisionContractor()
{
	static BasicExecutor executor;
	return executor;
}

void Collider::setIntrospector(Introspector & introspector)
{
#ifndef GPX_NO_INTROSPECT
	m_introspector = & introspector;
#endif
}

int Collider::subsequentCollisionLimit() const
{
	return m_subsequentCollisionLimit;
}

void Collider::setSubsequentCollisionLimit(int limit)
{
	m_subsequentCollisionLimit = limit;
}

void Collider::addFixed(ICFixed * obj)
{
	m_fixed.insert(obj);
}

void Collider::removeFixed(ICFixed * obj)
{
	GPX_ASSERT(m_fixed.find(obj) != m_fixed.end(), "element does not exist");
	m_fixed.erase(obj);
}

void Collider::addMovable(ICMovable * obj)
{
	m_movables[obj] = new MovableData;
}

void Collider::removeMovable(ICMovable * obj)
{
	GPX_ASSERT(m_movables.find(obj) != m_movables.end(), "element does not exist");
	MovablesContainer::iterator i = m_movables.find(obj);
	delete i->second;
	m_movables.erase(i);
}

void Collider::update(real_t dt)
{
	ClustersContainer clusters;
	Cluster * cluster = new Cluster(dt);	//@todo possible optimization: preallocate clusters, detection data and other structures.
//	bool collision;
//	int pass = 0;

	//update positions
	for (MovablesContainer::iterator mov = movables().begin(); mov != movables().end(); ++mov) {
		mov->second->checked = false;	//set check flag to false
		mov->first->update(dt);
		mov->first->swapBuffers();	//swap to new position
	}

	GPX_DEBUG("-------------------------------------------------------------------");
	for (MovablesContainer::iterator mov = movables().begin(); mov != movables().end(); ++mov) {
		DetectionData movData(*(mov->first), mov->first, *cluster);
//		collision = false;
		if (mov->second->checked)
			continue;	//already checked
		mov->second->checked = true;	//mark as being checked
		fillCluster(*cluster, movData);
		if (cluster->endIndex > 0) {
			clusters.push_back(cluster);
			cluster = new Cluster(dt);
		}
	}
	if (!clusters.empty()) {
		fulfillClusters(clusters);
		handleCollisions(clusters);
		updateClusters(clusters, dt);
	} else
		GPX_DEBUG("no collision");
	for (ClustersContainer::iterator i = clusters.begin(); i != clusters.end(); ++i)
		delete *i;
	delete cluster;
	clusters.clear();
}

phy::NewtonPlasticityTable & Collider::plasticityTable()
{
	return m_plasticityTable;
}

const Collider::FixedContainer & Collider::fixed() const
{
	return m_fixed;
}

Collider::FixedContainer & Collider::fixed()
{
	return m_fixed;
}

const Collider::MovablesContainer & Collider::movables() const
{
	return m_movables;
}

Collider::MovablesContainer & Collider::movables()
{
	return m_movables;
}

void Collider::fillCluster(Cluster & cluster, DetectionData & firstData)
{
	for (MovablesContainer::iterator mov = movables().begin(); mov != movables().end(); ++mov) {
		if (mov->second->checked)
			continue;	//already checked or checking
		DetectionData secondData(*(mov->first), mov->first, cluster);
		std::size_t newIndex = testPairCollect(cluster.endIndex, firstData, secondData);
		if (newIndex > cluster.endIndex) {
			cluster.endIndex = newIndex;
			mov->second->checked = true;	//mark as being checked
			fillCluster(cluster, secondData);
		}
	}

	for (FixedContainer::iterator pas = fixed().begin(); pas != fixed().end(); ++pas) {
		DetectionData secondData(**pas, 0, cluster);
		std::size_t newIndex = testPairCollect(cluster.endIndex, firstData, secondData);
		if (newIndex > cluster.endIndex) {
			cluster.endIndex = newIndex;
			cluster.detections.push_back(secondData);
		}
	}

	if (!firstData.contacts.empty())
		cluster.detections.push_back(firstData);
}

void Collider::moveBackClusters(ClustersContainer & clusters) const
{
	//move back objects in cluster
	for (ClustersContainer::iterator cluster = clusters.begin(); cluster != clusters.end(); ++cluster)
		for (DetectionDataContainer::const_iterator detection = (*cluster)->detections.begin(); detection != (*cluster)->detections.end(); ++detection)
			if (detection->mov)
				detection->mov->swapBuffers();	//move back to the past
}

void Collider::fulfillClusters(ClustersContainer & clusters)
{
	//move back objects in cluster and set their check flag to false
	for (ClustersContainer::iterator cluster = clusters.begin(); cluster != clusters.end(); ++cluster)
		for (DetectionDataContainer::const_iterator detection = (*cluster)->detections.begin(); detection != (*cluster)->detections.end(); ++detection) {
			if (detection->mov) {
				detection->mov->swapBuffers();	//move back to the past
				movables()[detection->mov]->checked = false;	//@todo possible optimization: hash map may be replaced by wrapping structure to avoid lookups, although currently this is not a big deal.
			}
		}

	//Currently during fulfill object can be attached to one cluster even if it falls on two or more.
	//Implementation is also not very elegant. Symmetry between fillCluster and fulfillCluster should be exploited.
	//todo this probably should be done better with some graph structure providing joins of clusters etc.
	//probably it would be better to swap back

	for (ClustersContainer::iterator cluster = clusters.begin(); cluster != clusters.end(); ++cluster)
		for (MovablesContainer::iterator mov = movables().begin(); mov != movables().end(); ++mov) {
			if (!mov->second->checked)
				continue;	//already in cluster
			DetectionData movData(*(mov->first), mov->first, **cluster);
			for (DetectionDataContainer::iterator oldData = (*cluster)->detections.begin(); oldData != (*cluster)->detections.end(); ++oldData) {
				ICMovable * saveMov = oldData->mov;
				oldData->mov = 0;	//act as fixed
				(*cluster)->endIndex = testPairCollect((*cluster)->endIndex, *oldData, movData);
				oldData->mov = saveMov;
			}
			if (!movData.contacts.empty()) {
				mov->second->checked = false;
				mov->first->swapBuffers(); //move fresh member of cluster to the past
				fulfillCluster(**cluster, movData);
			}
		}
}

void Collider::fulfillCluster(Cluster & cluster, DetectionData & firstData)
{
	ICMovable * saveMov = firstData.mov;
	firstData.mov = 0;
	for (MovablesContainer::iterator mov = movables().begin(); mov != movables().end(); ++mov) {
		if (!mov->second->checked)
			continue;	//already in cluster or just being added
		DetectionData secondData(*(mov->first), mov->first, cluster);
		std::size_t newIndex = testPairCollect(cluster.endIndex, firstData, secondData);
		if (newIndex > cluster.endIndex) {
			cluster.endIndex = newIndex;
			mov->second->checked = false;
			mov->first->swapBuffers(); //move fresh member of cluster to the past
			fulfillCluster(cluster, secondData);
		}
	}
	firstData.mov = saveMov;
	cluster.detections.push_back(firstData);
}

std::size_t Collider::testPairCollect(std::size_t startIndex, DetectionData & firstData, DetectionData & secondData)
{
	ContactData cFirst, cSecond;
	DoubleBufferSwapper bSwapper(firstData.mov, secondData.mov);

	//case 1: first is a wedge, second is a bumper
	SeekContactState stateA(firstData.fix, secondData.fix);
	while (seekContactCollect(stateA, bSwapper, cFirst, cSecond)) {
		cFirst.index = startIndex;
		cSecond.index = startIndex;
		firstData.contacts.push_back(cFirst);
		secondData.contacts.push_back(cSecond);
		startIndex++;
	}

	//case 2: second is a wedge, first is a bumper
	SeekContactState stateB(secondData.fix, firstData.fix);
	while (seekContactCollect(stateB, bSwapper, cSecond, cFirst)) {
		cFirst.index = startIndex;
		cSecond.index = startIndex;
		firstData.contacts.push_back(cFirst);
		secondData.contacts.push_back(cSecond);
		startIndex++;
	}

	return startIndex;
}

bool Collider::seekContactCollect(SeekContactState & s, DoubleBufferSwapper & b, ContactData & wedgeData, ContactData & bumperData)
{
	while (s.isValid()) {
		//bumper.pre = wedge.post
		bumperData.pre = s.bumper.mapToLocal(s.wedge.mapToGlobal(*s.vertIt));

		b.swapBuffers(); //swap to pre-collision
		//wedge.post = bumper.pre
		wedgeData.post = s.wedge.mapToLocal(s.bumper.mapToGlobal(bumperData.pre));
		//bumper.post = wedge.pre
		//get pre-collision vertices (however they may differ only for shape-shifting, double buffered objects)
		const model::VertexData<2> & preVertices = s.wedge.element(s.wi)->cvertices();
		wedgeData.pre = preVertices[s.vertices->distance(s.vertIt)];
		bumperData.post = s.bumper.mapToLocal(s.wedge.mapToGlobal(wedgeData.pre));
		b.swapBuffers(); //back to the future

		if (s.bumper.element(s.bi)->test(bumperData.pre, bumperData.post)) {
			wedgeData.wedge = true;
			wedgeData.cvertIt = s.vertIt;
			bumperData.wedge = false;
			bumperData.cvertIt = s.bumper.element(s.bi)->cvertices().end();

			wedgeData.element = s.wi;
			bumperData.element = s.bi;

			//obtain normals
			b.swapBuffers(); //swap to pre-collision
			bumperData.normal = s.bumper.element(s.bi)->normal(bumperData.pre, bumperData.post);
			wedgeData.normal = bumperData.normal.inverse();
			b.swapBuffers(); //back to the future

			s.inc();
			return true;
		}
		s.inc();
	}
	return false;
}

void Collider::handleCollisions(ClustersContainer & clusters)
{
	GPX_DEBUG("Number of clusters: " << clusters.size());

	//swap all movables to pre-collision state
//	for (MovablesContainer::iterator mov = movables().begin(); mov != movables().end(); ++mov)
//		mov->first->swapBuffers();

	for (ClustersContainer::iterator cluster = clusters.begin(); cluster != clusters.end(); ++cluster) {

		//collect coefficients
		std::size_t numContacts = (*cluster)->endIndex;
		GPX_DEBUG("Contacts in cluster: " << numContacts);

		m_a.resize(numContacts, numContacts);
		m_a.zero();

		m_b.resize(numContacts);
		m_b.zero();

		for (DetectionDataContainer::const_iterator detection = (*cluster)->detections.begin(); detection != (*cluster)->detections.end(); ++detection) {
			GPX_DEBUG("colliding object: "  << *dynamic_cast<PhyObject *>(detection->fix));
			//tmp
			for (ContactDataContainer::const_iterator contact = detection->contacts.begin(); contact != detection->contacts.end(); ++contact) {
				GPX_DEBUG("index -> pre: " << contact->index << " -> " << contact->pre);
				GPX_DEBUG("index -> normal: " << contact->index << " -> " << contact->normal);
			}
			GPX_DEBUG("--");
			//endtmp
			detection->fix->aCoefs(*detection, m_a);
			detection->fix->bCoefs(*detection, m_b);
		}

		GPX_DEBUG("A: " << std::endl << m_a);
		GPX_DEBUG("b: " << std::endl << m_b);

		//remove points with negative velocity
		for (std::size_t i = 0; i < m_b.size(); ++i)
			if (m_b(i) < 0.0) {
				for (std::size_t col = 0; col < m_a.cols(); ++col)
					m_a(i, col) = 0.0;
				for (std::size_t row = 0; row < m_a.rows(); ++row)
					m_a(row, i) = 0.0;
				m_b(i) = 0.0;
			}
		GPX_DEBUG("A: " << std::endl << m_a);
		GPX_DEBUG("b: " << std::endl << m_b);

		//calculate impulses
		//@todo current method for cancellation of negative imps based on recalculations of whole system is slow.
		math::Vector<> normalProjs(0u);
		bool negativeProjs;
		do {
			negativeProjs = false;
			m_aWC = m_a;
			m_bWC = m_b;

			//@todo possible optimization: matrix is symmetric and in many cases sparse.
//			math::Solver<math::EQ_GENERAL> solver(m_aWC);
			math::NNSolver<math::EQ_GENERAL> solver(m_aWC);
			normalProjs = solver.solve(m_bWC);

			#pragma message("temporary code")
			for (std::size_t i = 0; i < normalProjs.size(); ++i)
				if (gpx::math::cgt(real_t(), normalProjs(i))) {
					m_introspector->triggerError("solver could not remove negative impulse");
					m_introspector->breakpoint();
				}
			//end tmp

//			GPX_DEBUG("normal projs: " << normalProjs);

			//remove negative impulses
//			for (std::size_t i = 0; i < normalProjs.size(); ++i)
//				if (normalProjs(i) < 0.0) {
//					negativeProjs = true;
//					for (std::size_t col = 0; col < m_a.cols(); ++col)
//						m_a(i, col) = 0.0;
//					for (std::size_t row = 0; row < m_a.rows(); ++row)
//						m_a(row, i) = 0.0;
//					m_b(i) = 0.0;
//				}
		} while (negativeProjs);

		//apply impulses
		for (DetectionDataContainer::const_iterator detection = (*cluster)->detections.begin(); detection != (*cluster)->detections.end(); ++detection)
			if (detection->mov)
				for (ContactDataContainer::const_iterator contact = detection->contacts.begin(); contact != detection->contacts.end(); ++contact) {
					math::Vector<2> Fdt = contact->normal.inverse() * normalProjs(contact->index);
					detection->mov->applyImpulse(Fdt, contact->pre);
					GPX_DEBUG("Apply impulse to " << *dynamic_cast<PhyObject *>(detection->fix) << " at point: " << contact->pre);
					GPX_DEBUG("Fdt: " << Fdt);
				}
	}

//	movDetections->collectACoefs(m_a);
//	GPX_DEBUG("A: " << std::endl << m_a);
//
//	movDetections->collectBCoefs(m_b);
//	GPX_DEBUG("b: " << std::endl << m_b);
//
//	//movDetections.collectCoefs end.
//
//	math::Vector<> normalProjs;
//	bool negativeProjs;
//	do {
//		negativeProjs = false;
//		m_aWC = m_a;
//		m_bWC = m_b;
//
//		math::Solver<math::EQ_GENERAL> solver(m_aWC);
//		normalProjs = solver.solve(m_bWC);
//
//		GPX_DEBUG("normal projs: " << normalProjs);
//
//		//remove negative impulses
//		for (std::size_t i = 0; i < normalProjs.size(); ++i)
//			if (normalProjs(i) < 0.0) {
//				negativeProjs = true;
//				for (std::size_t col = 0; col < m_a.cols(); ++col)
//					m_a(i, col) = 0.0;
//				for (std::size_t row = 0; row < m_a.rows(); ++row)
//					m_a(row, i) = 0.0;
//				m_b(i) = 0.0;
//			}
//	} while (negativeProjs);
//
//	// applyImps
//	movDetections->applyNormalImps(normalProjs);
}

void Collider::updateClusters(ClustersContainer & clusters, real_t dt)
{
//	ClustersContainer reposClusters;

	//move objects in clusters
	for (ClustersContainer::iterator cluster = clusters.begin(); cluster != clusters.end(); ++cluster)
		for (DetectionDataContainer::const_iterator detection = (*cluster)->detections.begin(); detection != (*cluster)->detections.end(); ++detection) {
			if (detection->mov) {
				detection->mov->update(dt);
				detection->mov->swapBuffers();	//move to new position
			}
		}

	//tmp
//	bool dislocated;
//	do {
//		dislocated = false;
//		for (ClustersContainer::iterator cluster = clusters.begin(); cluster != clusters.end(); ++cluster)
//			for (DetectionDataContainer::const_iterator detection = (*cluster)->detections.begin(); detection != (*cluster)->detections.end(); ++detection) {
//				if (detection->mov) {
////					dislocateMovable(*(detection->mov), math::Vector<2>(0.0, 0.0), math::Vector<2>(0.0, 0.0));
//					for (FixedContainer::iterator fix = fixed().begin(); fix != fixed().end(); ++fix)
//						if (testPairDislocate(*(detection->mov), **fix, 0))
//							dislocated = true;
//					for (MovablesContainer::iterator mov = movables().begin(); mov != movables().end(); ++mov)
//						if (detection->mov == mov->first)
//							continue;
//						else
//							if (testPairDislocate(*(detection->mov), *(mov->first), mov->first))
//								dislocated = true;
//				}
//			}
//	} while (dislocated);
//	return;
	//endtmp

	GPX_DEBUG("========= dislocating clusters =========");
	for (ClustersContainer::iterator cluster = clusters.begin(); cluster != clusters.end(); ++cluster) {
#ifndef GPX_NO_INTROSPECT
		for (DetectionDataContainer::const_iterator detection = (*cluster)->detections.begin(); detection != (*cluster)->detections.end(); ++detection)
			m_introspector->light(*detection->fix);
		m_introspector->breakpoint();
#endif
		DislocMovablesContainer initialInputContainer;
		for (DetectionDataContainer::const_iterator detection = (*cluster)->detections.begin(); detection != (*cluster)->detections.end(); ++detection)
			if (detection->mov)
				initialInputContainer.push_back(detection->mov);
		DislocMovablesContainer * inContainer = & initialInputContainer;
		DislocMovablesContainer initialOutputContainer;
		DislocMovablesContainer * outContainer = & initialOutputContainer;
		int pass = 0;
		while (inContainer->size() > 0) {
			GPX_DEBUG("dislocating cluster (pass: " << pass << ")");
			dislocateMovables(*inContainer, *outContainer);
			//swap input with output
			DislocMovablesContainer * tmp = outContainer;
			outContainer = inContainer;
			inContainer = tmp;
			//clean output for fresh data
			outContainer->clear();
			pass++;
		}
#ifndef GPX_NO_INTROSPECT
		for (DetectionDataContainer::const_iterator detection = (*cluster)->detections.begin(); detection != (*cluster)->detections.end(); ++detection)
			m_introspector->off(*detection->fix);
#endif
	}
}

void Collider::dislocateMovables(DislocMovablesContainer & in, DislocMovablesContainer & out)
{
//	GPX_DEBUG("dislocateCluster pass: " << pass);
//	if (pass == 70)
//		m_introspector->setSkipBreakpoints(false);
//	if (pass == 100)	//@todo tmp	- add parameter instead of hard coded value and provide fallbak mechanims istead of fata error
//		GPX_FATAL("subsequent dislocate limit");
//	for (DislocMovablesContainer::iterator clusterMov = in.begin(); clusterMov != in.end(); ++clusterMov)
//		m_introspector->light(**clusterMov);
//	m_introspector->breakpoint();

	for (DislocMovablesContainer::iterator inMov = in.begin(); inMov != in.end(); ++inMov) {
		bool dislocWithFixed = false;
		for (FixedContainer::iterator fix = fixed().begin(); fix != fixed().end(); ++fix) {
			if (testPairDislocate(**inMov, **fix, 0)) {
				dislocWithFixed = true;
				GPX_DEBUG(*dynamic_cast<PhyObject *>(*inMov) << ": added to container after collision with fixed: " << *dynamic_cast<PhyObject *>(*fix));
			}
		}
		if (dislocWithFixed)
			out.push_back(*inMov);
		for (MovablesContainer::iterator mov = movables().begin(); mov != movables().end(); ++mov) {
			if (*inMov == mov->first)
				continue;
			if (testPairDislocate(*(mov->first), **inMov, *inMov)) {
				out.push_back(mov->first);
				GPX_DEBUG(*dynamic_cast<PhyObject *>(*inMov) << ": added to container after collision with movable: " << *dynamic_cast<PhyObject *>(mov->first));
			}
		}
	}

//	for (DislocMovablesContainer::iterator clusterMov = in.begin(); clusterMov != in.end(); ++clusterMov)
//		m_introspector->off(**clusterMov);
}

bool Collider::testPairDislocate(ICMovable & mov, const ICFixed & passive, ICMovable * passiveMov)
{
	bool result = false;
	math::Vector<2> normal;
	math::Vector<2> dsp;
	DoubleBufferSwapper bSwapper(& mov, passiveMov);

	//case 1: mov is a wedge, passive is a bumper
	SeekContactState stateA(& mov, & passive);
	while (seekContactDislocate(stateA, bSwapper, normal, dsp)) {
		//need to invert, since normal is taken from bumper
		normal.invert();
		dislocateMovable(mov, normal, dsp);
		result = true;
	}

	//case 2: passive is a wedge, mov is a bumper
	SeekContactState stateB(& passive, & mov);
	while (seekContactDislocate(stateB, bSwapper, normal, dsp)) {
		dislocateMovable(mov, normal, dsp);
		result = true;
	}

	return result;
}

bool Collider::seekContactDislocate(SeekContactState & s, DoubleBufferSwapper & b, math::Vector<2> & normal, math::Vector<2> & dsp)
{
	while (s.isValid()) {
		//bumper.pre = wedge.post
		math::Point<2> bumperPre = s.bumper.mapToLocal(s.wedge.mapToGlobal(*s.vertIt));

		b.swapBuffers(); //swap to pre-collision
		//bumper.post = wedge.pre
		//get pre-collision vertices (however they may differ only for shape-shifting, double buffered objects)
		const model::VertexData<2> & preVertices = s.wedge.element(s.wi)->cvertices();
		math::Point<2> bumperPost = s.bumper.mapToLocal(s.wedge.mapToGlobal(preVertices[s.vertices->distance(s.vertIt)]));
		b.swapBuffers(); //back to the future

		if (s.bumper.element(s.bi)->test(bumperPre, bumperPost)) {
			dsp = s.bumper.mapToGlobal(bumperPre) - s.bumper.mapToGlobal(bumperPost);
			normal = s.bumper.element(s.bi)->normal(bumperPre, bumperPost);
			s.inc();
			return true;
		}
		s.inc();
	}
	return false;
}

void Collider::dislocateMovable(ICMovable & mov, const math::Vector<2> & normal, const math::Vector<2> & dsp)
{
#ifndef GPX_NO_INTROSPECT
	m_introspector->highlight(mov);
	m_introspector->breakpoint();
#endif
	math::Vector<2> dislocVector(normal);
	//While displacement depends on direction of motion, normals always point
	//outwards the body, therefore absolute value must be taken from dot product.
	dislocVector *= -std::abs(normal.dot(dsp));
	if (!mov.dislocate(dislocVector)) {
		GPX_DEBUG("dislocation unsuccessful, performing second attempt with higher values");
		math::Vector<2> minVector(normal);
		minVector *= -1.0;
		minVector.minimize(dislocVector);
		if (!mov.dislocate(minVector))
			GPX_DEBUG("second attempt unsuccessful");
	}
#ifndef GPX_NO_INTROSPECT
	m_introspector->playdown(mov);
#endif
}

//void Collider::handleCollisions(MovableDetectionContainer * movDetections)
//{
//	//lines below can be moved to one public method movDetections.collectCoefs:
//
//	std::size_t pointsTotal = movDetections->enumeratePoints();
//	GPX_DEBUG("objs colliding with " << *dynamic_cast<PhyObject *>(movDetections->movable()) << ": " << movDetections->size());
//	GPX_DEBUG("movable points: " << movDetections->pointsNum() << ", points in the system: " << pointsTotal);
//	GPX_DEBUG("point (number) -> (counterpart, index) : (x, y)");
//	for (std::size_t i = 0; i < movDetections->pointsNum(); i++)
//		GPX_DEBUG("point (" << i << ") -> ("  << *dynamic_cast<PhyObject *>(movDetections->pointDetectionData(i).counterpart) << ", "<< movDetections->collisionIndex(i) << ") :" << movDetections->point(i).pre);
//
//	m_a.resize(pointsTotal, pointsTotal);
//	m_a = 0.0;
//
//	m_b.resize(pointsTotal);
//	m_b = 0.0;
//
//	movDetections->collectACoefs(m_a);
//	GPX_DEBUG("A: " << std::endl << m_a);
//
//	movDetections->collectBCoefs(m_b);
//	GPX_DEBUG("b: " << std::endl << m_b);
//
//	//movDetections.collectCoefs end.
//
//	math::Vector<> normalProjs;
//	bool negativeProjs;
//	do {
//		negativeProjs = false;
//		m_aWC = m_a;
//		m_bWC = m_b;
//
//		math::Solver<math::EQ_GENERAL> solver(m_aWC);
//		normalProjs = solver.solve(m_bWC);
//
//		GPX_DEBUG("normal projs: " << normalProjs);
//
//		//remove negative impulses
//		for (std::size_t i = 0; i < normalProjs.size(); ++i)
//			if (normalProjs(i) < 0.0) {
//				negativeProjs = true;
//				for (std::size_t col = 0; col < m_a.cols(); ++col)
//					m_a(i, col) = 0.0;
//				for (std::size_t row = 0; row < m_a.rows(); ++row)
//					m_a(row, i) = 0.0;
//				m_b(i) = 0.0;
//			}
//	} while (negativeProjs);
//
//	// applyImps
//	movDetections->applyNormalImps(normalProjs);
//}


Collider::DoubleBufferSwapper::DoubleBufferSwapper(ICMovable * p_firstMov, ICMovable * p_secondMov):
	firstMov(p_firstMov),
	secondMov(p_secondMov)
{
}

void Collider::DoubleBufferSwapper::swapBuffers()
{
	if (firstMov)
		firstMov->swapBuffers();
	if (secondMov)
		secondMov->swapBuffers();
}


Collider::SeekContactState::SeekContactState(const ICFixed * const p_wedge, const ICFixed * const p_bumper):
		wedge(*p_wedge),
		bumper(*p_bumper),
		wi(0),
		bi(0),
		vertices(& wedge.element(0)->cvertices()),
		vertIt(vertices->begin())
{
}

bool Collider::SeekContactState::isValid()
{
	return vertIt != vertices->end();
}

void Collider::SeekContactState::inc()
{
	++vertIt;
	if (vertIt == vertices->end()) {
		bi++;
		if (bi >= bumper.elements()) {
			wi++;
			if (wi < wedge.elements()) {
				bi = 0;
				vertices = & wedge.element(wi)->cvertices();
				vertIt = vertices->begin();
			}
		} else
			vertIt = vertices->begin();
	}
}

}
}
}
}

//(c)MP: Copyright © 2014, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
