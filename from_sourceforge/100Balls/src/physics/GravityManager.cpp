/**
 * @file /FastBall/src/physics/GravityManager.cpp
 * @brief .
 */

#include "GravityManager.h"

GravityManager::GravityManager(gpx::real_t g):
	m_g(g)
{
}

GravityManager::~GravityManager()
{
}

gpx::real_t	GravityManager::acceleration()
{
	return m_g;
}

void GravityManager::setAcceleration(gpx::real_t g)
{
	this->m_g = g;
}

void GravityManager::updateForce(MaterialBody * obj, Force * f)
{
	f->coord(1) = m_g * obj->mass();
}

void GravityManager::attachForce(MaterialBody * obj, Force * f)
{
	obj->mountForce(f);
}

void GravityManager::detachForce(MaterialBody * obj, Force * f)
{
	obj->unmountForce(f);
}
