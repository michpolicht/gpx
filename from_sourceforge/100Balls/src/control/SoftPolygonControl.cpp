/**
 * @file
 * @brief .
 */

#include "SoftPolygonControl.h"

#include "../physics/SoftPolygon.h"


SoftPolygonControl::SoftPolygonControl(const sf::Input & input, SoftPolygon * spoly):
	m_input(input),
	m_spoly(spoly)
{
}

SoftPolygonControl::~SoftPolygonControl()
{
}

void SoftPolygonControl::update()
{
	if (m_input.IsKeyDown(sf::Key::Left))
		m_spoly->mountImpulse(gpx::math::Vector<2>(-0.05, 0.0));
	if (m_input.IsKeyDown(sf::Key::Right))
		m_spoly->mountImpulse(gpx::math::Vector<2>(0.05, 0.0));
	if (m_input.IsKeyDown(sf::Key::Down))
		m_spoly->mountImpulse(gpx::math::Vector<2>(0.0, -0.05));
	if (m_input.IsKeyDown(sf::Key::Up))
		m_spoly->mountImpulse(gpx::math::Vector<2>(0.0, 0.05));
}
