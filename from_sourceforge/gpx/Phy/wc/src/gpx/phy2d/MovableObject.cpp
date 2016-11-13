/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/phy2d/MovableObject.hpp"
#include "../../../include/gpx/phy/RecordableFloatPoint.hpp"
#include "../../../include/gpx/phy/RecordableFloatMatrix.hpp"

namespace gpx {
namespace phy2d {

MovableObject::MovableObject():
	m_pos(m_doubleBufferController),
	m_tMatrix(m_doubleBufferController),
	m_tMatrixInv(m_doubleBufferController)
//	m_updateTMatrix(m_doubleBufferController, true, false)	//update active matrix
{
	updateTMatricesB();
	swapBuffers();
	updateTMatricesB();
	swapBuffers();
}

MovableObject::~MovableObject()
{
}

const utils::DoubleBufferController & MovableObject::doubleBufferController() const
{
	return m_doubleBufferController;
}

math::const_PointRef<2> MovableObject::pos() const
{
	return posA();
}

real_t MovableObject::pos(std::size_t i)
{
	return posA(i);
}

void MovableObject::setPos(math::const_PointRef<2> pos)
{
	setPosB(pos);
	swapBuffers();
	setPosB(pos);
	swapBuffers();
}

void MovableObject::setPos(real_t x, real_t y)
{
	setPos(math::Point<2>(x, y));
}

const phy::TransformationMatrix & MovableObject::tMatrix() const
{
	return m_tMatrix.active();
}

const phy::TransformationMatrix & MovableObject::tMatrixInv() const
{
	return m_tMatrixInv.active();
}

math::Point<2> MovableObject::mapToLocal(math::const_PointRef<2> point) const
{
	return tMatrixInv().prod(point);
}

math::Point<2> MovableObject::mapToGlobal(math::const_PointRef<2> point) const
{
	return tMatrix().prod(point);
}

std::size_t MovableObject::snapshotSize() const
{
	std::size_t result = 0;
	//pos A + pos B
	result += 2 * phy::RecordableFloatPoint<2>::SnapshotSize();
	//tMatrix A + tMatrix B
	result += 2 * phy::RecordableFloatMatrix<4, 4>::SnapshotSize();
	//tMatrixInv A + tMatrixInv B
	result += 2 * phy::RecordableFloatMatrix<4, 4>::SnapshotSize();
	return result;
}

void MovableObject::store(char * snapshot) const
{
	//store pos
	phy::RecordableFloatPoint<2>::Store(snapshot, posA());
	snapshot += phy::RecordableFloatPoint<2>::SnapshotSize();
	phy::RecordableFloatPoint<2>::Store(snapshot, posB());
	snapshot += phy::RecordableFloatPoint<2>::SnapshotSize();
	//store tMatrix
	phy::RecordableFloatMatrix<4, 4>::Store(snapshot, m_tMatrix.active());
	snapshot += phy::RecordableFloatMatrix<4, 4>::SnapshotSize();
	phy::RecordableFloatMatrix<4, 4>::Store(snapshot, m_tMatrix.background());
	snapshot += phy::RecordableFloatMatrix<4, 4>::SnapshotSize();
	//store tMatrixInv
	phy::RecordableFloatMatrix<4, 4>::Store(snapshot, m_tMatrixInv.active());
	snapshot += phy::RecordableFloatMatrix<4, 4>::SnapshotSize();
	phy::RecordableFloatMatrix<4, 4>::Store(snapshot, m_tMatrixInv.background());
	snapshot += phy::RecordableFloatMatrix<4, 4>::SnapshotSize();
}

void MovableObject::restore(char * snapshot)
{
	//restore pos
	phy::RecordableFloatPoint<2>::Restore(snapshot, m_pos.active());
	snapshot += phy::RecordableFloatPoint<2>::SnapshotSize();
	phy::RecordableFloatPoint<2>::Restore(snapshot, m_pos.background());
	snapshot += phy::RecordableFloatPoint<2>::SnapshotSize();
	//restore tMatrix
	phy::RecordableFloatMatrix<4, 4>::Restore(snapshot, m_tMatrix.active());
	snapshot += phy::RecordableFloatMatrix<4, 4>::SnapshotSize();
	phy::RecordableFloatMatrix<4, 4>::Restore(snapshot, m_tMatrix.background());
	snapshot += phy::RecordableFloatMatrix<4, 4>::SnapshotSize();
	//restore tMatrixInv
	phy::RecordableFloatMatrix<4, 4>::Restore(snapshot, m_tMatrixInv.active());
	snapshot += phy::RecordableFloatMatrix<4, 4>::SnapshotSize();
	phy::RecordableFloatMatrix<4, 4>::Restore(snapshot, m_tMatrixInv.background());
	snapshot += phy::RecordableFloatMatrix<4, 4>::SnapshotSize();
}


void MovableObject::swapBuffers()
{
	m_doubleBufferController.swapBuffers();
}

math::const_PointRef<2> MovableObject::posA() const
{
	return m_pos.active();
}

real_t MovableObject::posA(std::size_t i)
{
	return m_pos.active().coord(i);
}

math::const_PointRef<2> MovableObject::posB() const
{
	return m_pos.background();
}

real_t MovableObject::posB(std::size_t i)
{
	return m_pos.background().coord(i);
}

void MovableObject::setPosB(math::const_PointRef<2> pos)
{
	m_pos.background() = pos;
	updateTMatricesB();
}

void MovableObject::setPosB(real_t x, real_t y)
{
	setPosB(math::Point<2>(x, y));
}

void MovableObject::updateTMatricesB()
{
	//currently instant calls are made
	constructTMatrix(m_tMatrix.background());
	constructTMatrixInv(m_tMatrixInv.background());
}

void MovableObject::constructTMatrix(phy::TransformationMatrix & tMatrix)
{
	tMatrix(0,3) = posB(0);
	tMatrix(1,3) = posB(1);
}

void MovableObject::constructTMatrixInv(phy::TransformationMatrix & tMatrixInv)
{
	tMatrixInv(0,3) = -posB(0);
	tMatrixInv(1,3) = -posB(1);
}

}
}
