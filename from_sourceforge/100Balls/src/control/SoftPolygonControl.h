/**
 * @file
 * @brief .
 */

#ifndef GPX_100Balls_SOFTPOLYGONCONTROL_H_
#define GPX_100Balls_SOFTPOLYGONCONTROL_H_

#include <SFML/Window.hpp>

class SoftPolygon;


class SoftPolygonControl
{
	protected:
		const sf::Input & m_input;
		SoftPolygon * m_spoly;

	public:
		SoftPolygonControl(const sf::Input & input, SoftPolygon * spoly);
		virtual ~SoftPolygonControl();

		void update();
};

#endif /* GPX_100Balls_SOFTPOLYGONCONTROL_H_ */
