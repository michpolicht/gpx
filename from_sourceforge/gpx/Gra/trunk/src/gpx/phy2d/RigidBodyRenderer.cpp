/**
 * @file
 * @brief .
 */


#include <gpx/phy2d/RigidBody.hpp>
#include <gpx/phy2d/Force.hpp>

#include "../../../include/gpx/phy2d/RigidBodyRenderer.hpp"

namespace gpx {
namespace phy2d {


RigidBodyRenderer::RigidBodyRenderer(const RigidBody * rigidBody):
	m_rigidBody(rigidBody),
	m_renderRotationPoint(true),
	m_renderCenterOfMass(true),
	m_renderForcePoints(true),
	m_pointRenderer(0),
	m_vectorRenderer(0, 0)
{
}

RigidBodyRenderer::~RigidBodyRenderer()
{
}

void RigidBodyRenderer::render(gra2d::RenderContext * context)
{
	GPX_UNUSED(context);

	glMultMatrix(m_rigidBody->tMatrix().ptr());
	if (m_renderRotationPoint) {
//		m_pointRenderer.setPoint(m_rigidBody->rotationPoint());
//		m_pointRenderer.setStyle(gra2d::PointRenderer::Cross);
//		m_pointRenderer.render(context);
	}
	if (m_renderCenterOfMass) {
//		m_pointRenderer.setPoint(m_rigidBody->centerOfMass());
//		m_pointRenderer.setStyle(gra2d::PointRenderer::Dot);
//		m_pointRenderer.render(context);
	}
//	if (m_renderForcePoints) {
//		const RigidBody::ForcePointsContainer & forcePoints = m_rigidBody->forcePoints();
//		for (RigidBody::ForcePointsContainer::const_iterator forcePoint = forcePoints.begin(); forcePoint != forcePoints.end(); ++forcePoint) {
//			m_vectorRenderer.setInitial(forcePoint->second.ptr());	//iterator shall give direct access to what's inside hash_map
//			math::Vector<2> fCopy(*(forcePoint->first));
//			fCopy.rotate(-m_rigidBody->angle());
//			m_vectorRenderer.setVector(fCopy.ptr());
//			m_vectorRenderer.render(context);
//			m_vectorRenderer.setVector(0);
//		}
//	}
}

}
}
