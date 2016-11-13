/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/StaticObject.hpp"

namespace gpx {

namespace phy2d {

StaticObject::StaticObject()
{
	constructTMatrix(m_tMatrix, m_tMatrixInv);
}

StaticObject::~StaticObject()
{
}

void StaticObject::constructTMatrix(phy::TransformationMatrix & tMatrix, phy::TransformationMatrix & tMatrixInv)
{
	tMatrix(0,3) = m_pos(0);
	tMatrix(1,3) = m_pos(1);

	tMatrixInv(0,3) = -m_pos(0);
	tMatrixInv(1,3) = -m_pos(1);
}

math::const_PointRef<2> StaticObject::pos() const
{
	return m_pos;
}

void StaticObject::setPos(math::const_PointRef<2> pos)
{
	m_pos = pos;

	constructTMatrix(m_tMatrix, m_tMatrixInv);
}

void StaticObject::setPos(real_t x, real_t y)
{
	setPos(math::Point<2>(x, y));
}

real_t StaticObject::x() const
{
	return m_pos(0);
}

void StaticObject::setX(real_t x)
{
	setPos(math::Point<2>(x, m_pos(1)));
}

real_t StaticObject::y() const
{
	return m_pos(1);
}

void StaticObject::setY(real_t y)
{
	setPos(math::Point<2>(m_pos(0), y));
}

const phy::TransformationMatrix & StaticObject::tMatrix() const
{
	return m_tMatrix;
}

math::Point<2> StaticObject::mapToLocal(math::const_PointRef<2> point) const
{
	return m_tMatrixInv.prod(point);
}

math::Point<2> StaticObject::mapToGlobal(math::const_PointRef<2> point) const
{
	return m_tMatrix.prod(point);
}



}
}
