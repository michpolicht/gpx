/**
 * @file
 * @brief .
 */

#include "SoftPolygon.h"


SoftPolygon::SoftPolygon(const gpx::model::VertexData<2> & vdata, gpx::real_t mass, gpx::real_t svMass):
	CPolygon(vdata, mass),
	m_parts(vdata.num(), SoftPolygonVertex(this)),
	m_cVertices(doubleBufferController())
{
	m_vertexBuff[0] = new gpx::real_t[vdata.dsize()];
	m_vertexBuff[1] = new gpx::real_t[vdata.dsize()];
	std::memcpy(m_vertexBuff[0], vdata.data(), vdata.bsize());
	std::memcpy(m_vertexBuff[1], vdata.data(), vdata.bsize());
	m_cVertices.active().setData(m_vertexBuff[0], vdata.num());
	m_cVertices.background().setData(m_vertexBuff[1], vdata.num());
	std::size_t i = 0;
	for (std::vector<SoftPolygonVertex>::iterator part = m_parts.begin(); part != m_parts.end(); ++part) {
		part->setIndex(i++);
		part->setMass(svMass);
	}
}

SoftPolygon::~SoftPolygon()
{
	delete[] m_vertexBuff[0];
	m_vertexBuff[0] = 0;
	delete[] m_vertexBuff[1];
	m_vertexBuff[1] = 0;
}

std::vector<SoftPolygonVertex> & SoftPolygon::getParts()
{
	return m_parts;
}

bool SoftPolygon::test(const gpx::math::const_VectorPtr<2> & cvertex) const
{
//	double x = cvertex[0];
//	double y = cvertex[1];
//
//	if ((x < model->width / 2.0) && (x > - model->width / 2.0) && (y < model->height / 2.0) && (y > -model->height / 2.0))
//		return true;
	return false;
}

const gpx::model::VertexData<2> & SoftPolygon::cvertices() const
{
	static gpx::model::VertexData<2> empty;
	return empty;
}

void SoftPolygon::update(gpx::real_t dt)
{
	CPolygon::update(dt);
	for (std::vector<SoftPolygonVertex>::iterator part = m_parts.begin(); part != m_parts.end(); ++part)
		part->m_virtualSwap = false;
}







gpx::math::Vector<2> SoftPolygonField::operator()(const point_t & ref, const point_t & r)
{
	gpx::real_t k = -50.0;
	gpx::math::Vector<2> result(r - ref);
//	result(0) *= result(0) * result(0);
//	result(1) *= result(1) * result(1);
	return result * k;
}







SoftPolygonField SoftPolygonVertex::m_reactField;

SoftPolygonVertex::SoftPolygonVertex(SoftPolygon * parent, gpx::real_t mass):
		m_parent(parent),
		m_cVertices(parent->doubleBufferController()),
		m_relax(true),
		m_mass(mass)
{
}

SoftPolygonVertex::~SoftPolygonVertex()
{
}

void SoftPolygonVertex::setParent(SoftPolygon * parent)
{
	this->m_parent = parent;
}

void SoftPolygonVertex::setIndex(std::size_t index)
{
	this->m_index = index;
	m_cVertices.active().setData(m_parent->m_cVertices.active()[index], 1);
	m_cVertices.background().setData(m_parent->m_cVertices.background()[index], 1);
}

void SoftPolygonVertex::setMass(gpx::real_t mass)
{
	m_mass = mass;
}

gpx::real_t SoftPolygonVertex::mass() const
{
	return m_mass;
}

void SoftPolygonVertex::update(gpx::real_t dt)
{
	if (m_relax) {
		//this is immediate relaxation
		//might be changed to slower relaxation (eg depending on vertex mass)
//		m_cVertices.background()[0][0] = m_parent->vData()[m_index][0];
//		m_cVertices.background()[0][1] = m_parent->vData()[m_index][1];
//		gpx::math::Vector<2> force = m_reactField(m_parent->vData()[m_index], m_cVertices.background()[0]);
//		m_p[0] -= force[0] * dt;
//		m_p[1] -= force[1] * dt;
//		gpx::math::Vector<2> v;
//		v[0] = m_p[0] / (m_mass * 100);
//		v[1] = m_p[1] / (m_mass * 100);
//		m_cVertices.background()[0][0] -= v[0] * dt;
//		m_cVertices.background()[0][1] -= v[1] * dt;

		//temp relaxation
		m_cVertices.background()[0][0] = (10.0 * m_cVertices.background()[0][0] + m_parent->vdata()[m_index][0]) / 11.0;
		m_cVertices.background()[0][1] = (10.0 * m_cVertices.background()[0][1] + m_parent->vdata()[m_index][1]) / 11.0;
		//relaxField...
	}
	m_relax = true;
}

void SoftPolygonVertex::swapBuffers()
{
	//note that controller isn't swapped here
	m_virtualSwap = !m_virtualSwap;
}

gpx::math::Vector<2> SoftPolygonVertex::mapToGlobal(const gpx::math::const_VectorPtr<2> & point) const
{
	if (m_virtualSwap)
		m_parent->swapBuffers();
	else
		return m_parent->mapToGlobal(point);
	gpx::math::Vector<2> result(m_parent->mapToGlobal(point));
	m_parent->swapBuffers();
	return result;
}

gpx::math::Vector<2> SoftPolygonVertex::mapToLocal(const gpx::math::const_VectorPtr<2> & point) const
{
	if (m_virtualSwap)
		m_parent->swapBuffers();
	else
		return m_parent->mapToLocal(point);
	gpx::math::Vector<2> result(m_parent->mapToLocal(point));
	m_parent->swapBuffers();
	return result;
}

bool SoftPolygonVertex::test(const gpx::math::const_VectorPtr<2> & cvertex) const
{
	//never a bumper
	return false;
}

const gpx::model::VertexData<2> & SoftPolygonVertex::cvertices() const
{
	if (m_virtualSwap)
		m_parent->swapBuffers();
	else
		return m_cVertices.active();
	const gpx::model::VertexData<2> & result = m_cVertices.active();
	m_parent->swapBuffers();
	return result;
}

gpx::math::Vector<2> SoftPolygonVertex::eff(const gpx::math::const_VectorPtr<2> & pre, const gpx::math::const_VectorPtr<2> & post) const
{
	//never a bumper
	return gpx::math::Vector<2>();
}

gpx::math::Vector<2> SoftPolygonVertex::normal(const gpx::phy2d::CollisionPoints & ncPoints) const
{
	//never a bumper
	return gpx::math::Vector<2>();
}

//ICPolyGroup
gpx::phy2d::ICPolyGroup::element_t SoftPolygonVertex::elements() const
{
	return 1;
}

//ICPolyGroup
const gpx::phy2d::ICPoly * SoftPolygonVertex::element(gpx::phy2d::ICPolyGroup::element_t i) const
{
	return this;
}

gpx::math::Vector<2> SoftPolygonVertex::aCoef(const gpx::phy2d::NewtonCollisionBase & bData) const
{
	gpx::math::Vector<2> force = m_reactField(m_parent->vdata()[m_index], m_cVertices.active().data());
//	gpx::math::Vector<2> pot = m_reactField(m_parent->model->cvertices[m_index], bData.points.eff);
	gpx::math::Vector<2> dr(bData.points.post - bData.points.eff);
	dr.rotate(m_parent->m_angle.active()); 		//@todo optimize with cached angleSin, angleCos
	force.rotate(m_parent->m_angle.active());	//@todo optimize with cached angleSin, angleCos
//	pot(0) = std::abs(pot(0));
//	pot(1) = std::abs(pot(1));
	gpx::math::Vector<2> meff(force);
	meff *= bData.dData.dt * bData.dData.dt;
	if (meff(0) != 0.0)
		meff(0) /= dr(0);
	if (meff(1) != 0.0)
		meff(1) /= dr(1);

	//	meff(0) += m_mass;
//	meff(1) += m_mass;
	gpx::math::Vector<2> result(1.0 / meff(0), 1.0 / meff(1));
//	return gpx::math::Vector<2>(std::numeric_limits<gpx::real_t>::infinity(), std::numeric_limits<gpx::real_t>::infinity());	//tmp
//	return gpx::math::Vector<2>(100000.0, 100000.0);	//tmp
	return result;
}

gpx::math::Vector<2> SoftPolygonVertex::bCoef(gpx::real_t e, const gpx::phy2d::NewtonCollisionBase & bData) const
{
	gpx::math::Vector<2> v(bData.points.post - bData.points.eff);
	v.rotate(m_parent->m_angleSin.active(), m_parent->m_angleCos.active());
	v /= bData.dData.dt;
	std::cout << "v: " << v;
//	gpx::math::Vector<2> result(parent->model->cvertices[index]);
//	result -= cvertices.active().data();
//	result /= bData.dt;
	return v;
}

gpx::phy::material_t SoftPolygonVertex::material(gpx::phy2d::ICPolyGroup::element_t element) const
{
	return 0;
}

void SoftPolygonVertex::roundAwayImpulse(gpx::phy2d::Impulse & impulse, const gpx::phy2d::NewtonCollisionData & data, bool normal)
{
	if (normal) {
		gpx::math::Vector<2> dr(data.bData.points.post - data.bData.points.eff);
		std::cout << "post: " << data.bData.points.post;
		std::cout << "eff: " << data.bData.points.eff;
		if (data.bData.dData.moving == this) {
			gpx::real_t dangle = m_parent->m_angle.background() - m_parent->m_angle.active();
			dr.rotate(-dangle);
			m_cVertices.background()[0][0] -= dr[0];
			m_cVertices.background()[0][1] -= dr[1];
			m_relax = false;
			std::cout << "moving ------------------ dangle: " << dangle << " dr: " << dr << std::endl;
		} else {
			//virtualSwap will be set to true after update()
			if (m_virtualSwap) {
				//in cVertices() background will be swapped to active
				m_cVertices.background()[0][0] -= dr[0];
				m_cVertices.background()[0][1] -= dr[1];
				std::cout << "m_virtualSwap = true ------------------ dr: " << dr << std::endl;
			} else {
				//before update cVertices() won't swap, background will be relaxed anyway
				m_cVertices.active()[0][0] -= dr[0];
				m_cVertices.active()[0][1] -= dr[1];
				std::cout << "m_virtualSwap = false ------------------ dr: " << dr << std::endl;
			}
		}
	}
}

void SoftPolygonVertex::mountImpulse(const gpx::phy2d::Impulse & impulse, const gpx::math::const_VectorPtr<2> & point)
{
	m_parent->mountImpulse(impulse, point);
}

