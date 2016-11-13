/**
 * @file
 * @brief .
 */

#include "../../../../../include/gpx/phy2d/cnewton/pmepp2_s/CRigidBody.hpp"

#include <gpx/log.hpp>

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

CRigidBody::CRigidBody(real_t m, real_t I, phy::material_t material):
		Parent(m, I),
		m_material(material)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::aCoefs(const DetectionData & dData, math::Matrix<> & a) const
{
	for (ContactDataContainer::const_iterator v = dData.contacts.begin(); v != dData.contacts.end(); ++v) {
		const math::Vector<2> & nv = v->normal;
		math::Vector<2> rv = v->pre.diff();
		rotateToGlobal(rv);
		real_t detRvNv = rv.det(nv);
		for (ContactDataContainer::const_iterator i = dData.contacts.begin(); i != dData.contacts.end(); ++i) {
			const math::Vector<2> & ni = i->normal;
			math::Vector<2> ri = i->pre.diff();
			rotateToGlobal(ri);
			a(v->index, i->index) += (detRvNv * ri.det(ni)) / I() + nv.dot(ni) / m();
		}
	}
}

void CRigidBody::bCoefs(const DetectionData & dData, math::Vector<> & b) const
{
//	GPX_DEBUG("b coefs called " << *dynamic_cast<const PhyObject *>(this));
	for (ContactDataContainer::const_iterator v = dData.contacts.begin(); v != dData.contacts.end(); ++v) {
		const math::Vector<2> & nv = v->normal;
		math::Vector<2> rv = v->pre.diff();
		rotateToGlobal(rv);
//		GPX_DEBUG("normal vector is: " << v->normal);
//		GPX_DEBUG("pB() is: " << pB());
//		GPX_DEBUG("adding to b(" << v->index << "): " << LB() * rv.det(nv) / I() + pB().dot(nv) / m());
		b(v->index) += LB() * rv.det(nv) / I() + pB().dot(nv) / m();
	}
}

//phy::material_t CRigidBody::material() const
//{
//	return m_material;
//}
//
//void CRigidBody::setMaterial(phy::material_t material)
//{
//	m_material = material;
//}

void CRigidBody::applyImpulse(const Impulse & impulse, math::const_PointRef<2> point)
{
	Parent::applyImpulse(impulse, point);
}

void CRigidBody::passLimit(const DetectionDataContainer & )
{
//	GPX_DEBUG("subsequent collision limit");
//	math::Vector<2> avgNormal;
//	for (DetectionDataContainer::const_DIPFacade v = detections.begin(); v != detections.end(); ++v)
////		avgNormal += v->point->normal;
//		avgNormal += v->point->pre - v->point->post;
//	rotateToGlobal(avgNormal);
//	avgNormal /= static_cast<real_t>(detections.pointsNum());
//	GPX_DEBUG("avgNormal: " << avgNormal);
//	setDisloc(avgNormal);
}

bool CRigidBody::dislocate(math::Vector<2> & disloc)
{
//	//tmp
//	if (posA() != posB()) {
//		swapBuffers();
//		setPosB(posA()); //move back
//		setAngleB(angleA()); //move back
//		swapBuffers();
//	}
//	return true;

	GPX_DEBUG(*this << ": dislocating by vector: " << disloc);

	swapBuffers();	//swap buffer to update active position in background
	math::Point<2> oldPos = posB();
	setPosB(posB() + disloc);
	swapBuffers();	//move to new position (should be non-colliding)

	if (oldPos == posA()) {
		disloc = posA().ptr();
		return false;
	}
	return true;
}

//void CRigidBody::roundAwayImpulses(Impulse & normal, Impulse & parallel, const CollisionData & cData)
//{
//}
//
//phy::material_t CRigidBody::material(element_t element) const
//{
//	return m_material;
//}

}
}
}
}
