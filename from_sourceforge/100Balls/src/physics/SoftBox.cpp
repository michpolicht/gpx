/**
 * @file
 * @brief .
 */

#include "SoftBox.h"

#include "../models/BoxModel.h"


SoftBox::SoftBox(BoxModel * model, double mass):
	Box(model, mass),
	m_parts(model->cvertices.num(), SoftBoxVertex(this)),
	m_cVertices(doubleBufferController())
{
	m_vertexBuff[0] = new gpx::real_t[model->cvertices.dsize()];
	m_vertexBuff[1] = new gpx::real_t[model->cvertices.dsize()];
	std::memcpy(m_vertexBuff[0], model->cvertices.data(), model->cvertices.bsize());
	std::memcpy(m_vertexBuff[1], model->cvertices.data(), model->cvertices.bsize());
	m_cVertices.active().setData(m_vertexBuff[0], model->cvertices.num());
	m_cVertices.background().setData(m_vertexBuff[1], model->cvertices.num());
	std::size_t i = 0;
	for (std::vector<SoftBoxVertex>::iterator part = m_parts.begin(); part != m_parts.end(); ++part)
		part->setIndex(i++);
}

SoftBox::~SoftBox()
{
	delete[] m_vertexBuff[0];
	m_vertexBuff[0] = 0;
	delete[] m_vertexBuff[1];
	m_vertexBuff[1] = 0;
}

std::vector<SoftBoxVertex> & SoftBox::getParts()
{
	return m_parts;
}

bool SoftBox::test(const gpx::math::const_VectorPtr<2> & cvertex) const
{
//	double x = cvertex[0];
//	double y = cvertex[1];
//
//	if ((x < model->width / 2.0) && (x > - model->width / 2.0) && (y < model->height / 2.0) && (y > -model->height / 2.0))
//		return true;
	return false;
}

const gpx::model::VertexData<2> & SoftBox::cvertices() const
{
	static gpx::model::VertexData<2> empty;
	return empty;
}

void SoftBox::update(gpx::real_t dt)
{
	Box::update(dt);
	for (std::vector<SoftBoxVertex>::iterator part = m_parts.begin(); part != m_parts.end(); ++part)
		part->m_virtualSwap = false;
}







gpx::math::Vector<2> SoftBoxField::operator()(const point_t & ref, const point_t & r)
{
	gpx::real_t k = -1.0;
	gpx::math::Vector<2> result(r - ref);
//	result(0) *= result(0);
//	result(1) *= result(1);
//	result(0) *= result(0);
//	result(1) *= result(1);
	return result * k;
}







SoftBoxField SoftBoxVertex::m_reactField;

SoftBoxVertex::SoftBoxVertex(SoftBox * parent):
		m_parent(parent),
		m_cVertices(parent->doubleBufferController()),
		m_relax(true)
{
}

SoftBoxVertex::~SoftBoxVertex()
{
}

void SoftBoxVertex::setParent(SoftBox * parent)
{
	this->m_parent = parent;
}

void SoftBoxVertex::setIndex(std::size_t index)
{
	this->m_index = index;
	m_cVertices.active().setData(m_parent->m_cVertices.active()[index], 1);
	m_cVertices.background().setData(m_parent->m_cVertices.background()[index], 1);
}

void SoftBoxVertex::update(gpx::real_t dt)
{
	if (m_relax) {
		//this is immediate relaxation
		//might be changed to slower relaxation (eg depending on vertex mass)
		m_cVertices.background()[0][0] = m_parent->model->cvertices[m_index][0];
		m_cVertices.background()[0][1] = m_parent->model->cvertices[m_index][1];
		//relaxField...
	}
	m_relax = true;
}

void SoftBoxVertex::swapBuffers()
{
	//note that controller isn't swapped here
	m_virtualSwap = !m_virtualSwap;
}

gpx::math::Vector<2> SoftBoxVertex::mapToGlobal(const gpx::math::const_VectorPtr<2> & point) const
{
	if (m_virtualSwap)
		m_parent->swapBuffers();
	else
		return m_parent->mapToGlobal(point);
	gpx::math::Vector<2> result(m_parent->mapToGlobal(point));
	m_parent->swapBuffers();
	return result;
}

gpx::math::Vector<2> SoftBoxVertex::mapToLocal(const gpx::math::const_VectorPtr<2> & point) const
{
	if (m_virtualSwap)
		m_parent->swapBuffers();
	else
		return m_parent->mapToLocal(point);
	gpx::math::Vector<2> result(m_parent->mapToLocal(point));
	m_parent->swapBuffers();
	return result;
}

bool SoftBoxVertex::test(const gpx::math::const_VectorPtr<2> & cvertex) const
{
	//never a bumper
	return false;
}

const gpx::model::VertexData<2> & SoftBoxVertex::cvertices() const
{
	if (m_virtualSwap)
		m_parent->swapBuffers();
	else
		return m_cVertices.active();
	const gpx::model::VertexData<2> & result = m_cVertices.active();
	m_parent->swapBuffers();
	return result;
}

gpx::math::Vector<2> SoftBoxVertex::eff(const gpx::math::const_VectorPtr<2> & pre, const gpx::math::const_VectorPtr<2> & post) const
{
	//never a bumper
	return gpx::math::Vector<2>();
}

gpx::math::Vector<2> SoftBoxVertex::normal(const gpx::phy2d::CollisionPoints & ncPoints) const
{
	//never a bumper
	return gpx::math::Vector<2>();
}

gpx::phy2d::ICPolyGroup::element_t SoftBoxVertex::elements() const
{
	return 1;
}

//ICPolyGroup
const gpx::phy2d::ICPoly * SoftBoxVertex::element(gpx::phy2d::ICPolyGroup::element_t i) const
{
	return this;
}

gpx::math::Vector<2> SoftBoxVertex::aCoef(const gpx::phy2d::NewtonCollisionBase & bData) const
{
	gpx::math::Vector<2> force = m_reactField(m_parent->model->cvertices[m_index], m_cVertices.active().data());
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

//		meff(0) = std::numeric_limits<gpx::real_t>::
//	if (dr(0) != 0.0)
//		meff(0) /= dr(0);// * dr(0);
//	if (dr(1) != 0.0)
//		meff(1) /= dr(1);// * dr(1);
//	meff.rotate(m_parent->m_angle.active());	//optimize with cached angleSin, angleCos
//	std::cout << "MASS " << meff;

	//	gpx::phy2d::Impulse imp = field(parent->model->cvertices[index], bData.points.eff) * bData.dt;
//	gpx::math::Vector<2> meff = field(parent->model->cvertices[index], bData.points.eff) * bData.dt * bData.dt;
//	std::cout << std::endl << "field dt dt: " << meff;
//	gpx::math::Vector<2> dr(bData.points.post - bData.points.eff);
////		meff.rotate(parent->angleSin, parent->angleCos);
////		dr.rotate(parent->angleSin, parent->angleCos);
//	meff(0) /= dr(0);
//	meff(1) /= dr(1);
//	std::cout << "pre: " << bData.points.pre;
//	std::cout << "eff: " << bData.points.eff;
//	std::cout << "pot: " << pot;
//	std::cout << "dr: " << dr;
//	std::cout << "mass: " << meff;
////	meff = gpx::math::Vector<2>(1.0, 1.0) / 10000.0;
//	meff.rotate(parent->angle);
//	meff(0) = std::abs(meff(0));
//	meff(1) = std::abs(meff(1));
	gpx::math::Vector<2> result(1.0 / meff(0), 1.0 / meff(1));
////	result.rotate(parent->angle);
//	return gpx::math::Vector<2>(std::numeric_limits<gpx::real_t>::infinity(), std::numeric_limits<gpx::real_t>::infinity());	//tmp
//	return gpx::math::Vector<2>(100000.0, 100000.0);	//tmp
	return result;
//
////	std::cout << bData.points.eff - bData.points.pre;
////	gpx::math::Vector<2> pos(cvertices.background().data());
////	pos -= bData.points.eff - bData.points.pre;
//	gpx::real_t k = 1.0;
//	gpx::math::Vector<2> dx(parent->model->cvertices[index]);
////	dx -= cvertices.active().data();
////	gpx::math::Vector<2> F(dx * k);
//	return gpx::math::Vector<2>(k * bData.dt * bData.dt, k * bData.dt * bData.dt);	//temp
}

gpx::math::Vector<2> SoftBoxVertex::bCoef(gpx::real_t e, const gpx::phy2d::NewtonCollisionBase & bData) const
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

gpx::phy::material_t SoftBoxVertex::material(gpx::phy2d::ICPolyGroup::element_t element) const
{
	return 0;
}

void SoftBoxVertex::roundAwayImpulse(gpx::phy2d::Impulse & impulse, const gpx::phy2d::NewtonCollisionData & data, bool normal)
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
//		gpx::phy2d::Impulse imp = field(parent->model->cvertices[index], cvertices.active().data()) * data.bData.dt;
//		imp.rotate(parent->angleSin, parent->angleCos);
//		parent->mountImpulse(imp, data.bData.points.eff);
//		parent->mountImpulse(dr.invert().rotate(parent->angleSin, parent->angleCos)* 0.02, data.bData.points.eff);
	}
}

void SoftBoxVertex::mountImpulse(const gpx::phy2d::Impulse & impulse, const gpx::math::const_VectorPtr<2> & point)
{
	m_parent->mountImpulse(impulse, point);
}

