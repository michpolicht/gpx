/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_COLOR_HPP_
#define GPX_Gra_COLOR_HPP_

#include "../gl_wrap.hpp"

#include <SFML/Graphics/Color.hpp>

#include <gpx/platform.hpp>

namespace gpx {
namespace gra {

class Color
{
	public:
		typedef float color_t;

	public:
		static const std::size_t SIZE = 4;

	public:
		Color();

		Color(const Color & other);

		Color(float red, float green, float blue, float alpha = 1.0f);

		Color(double red, double green, double blue, double alpha = 1.0);

		Color(int red, int green, int blue, int alpha = 255, color_t divisor = 255.0);

	public:
		Color & operator +=(const Color & other);

		Color & operator -=(const Color & other);

		Color operator +(const Color & other) const;

		Color operator -(const Color & other) const;

	public:
		color_t * rgba();

		const color_t * rgba() const;

		/**
		 * Set RGBA color values.
		 * @param rgba array containing new color values.
		 *
		 * @note color values are @b copied from an array pointed by @a rgba.
		 */
		void setRgba(color_t * rgba);

		void setRgba(float red, float green, float blue, float alpha);

		void setRgba(double red, double green, double blue, double alpha);

		void setRgba(int red, int green, int blue, int alpha, color_t divisor = 255.0);

		/**
		 * Set RGB color values.
		 * @param rgb array containing new color values.
		 *
		 * @note color values are @b copied from an array pointed by @a rgb.
		 */
		void setRgb(color_t * rgb);

		void setRgb(float red, float green, float blue);

		void setRgb(double red, double green, double blue);

		void setRgb(int red, int green, int blue, color_t divisor = 255.0);

		color_t red() const;

		void setRed(float red);

		void setRed(double red);

		void setRed(int red, color_t divisor = 255.0);

		color_t green() const;

		void setGreen(float green);

		void setGreen(double green);

		void setGreen(int green, color_t divisor = 255.0);

		color_t blue() const;

		void setBlue(float blue);

		void setBlue(double blue);

		void setBlue(int blue, color_t divisor = 255.0);

		color_t alpha() const;

		void setAlpha(float alpha);

		void setAlpha(double alpha);

		void setAlpha(int alpha, color_t divisor = 255.0);

		void glSetRgb() const;

		void glSetRgba() const;

		sf::Color toSfColor() const;

	private:
		color_t m_rgba[SIZE];

};


inline
Color::Color()
{
	for (std::size_t i = 0; i < SIZE; i++)
		m_rgba[i] = 0.0;
}

inline
Color::Color(const Color & other)
{
	for (std::size_t i = 0; i < SIZE; i++)
		m_rgba[i] = other.rgba()[i];
}

inline
Color::Color(float red, float green, float blue, float alpha)
{
	m_rgba[0] = static_cast<color_t>(red);
	m_rgba[1] = static_cast<color_t>(green);
	m_rgba[2] = static_cast<color_t>(blue);
	m_rgba[3] = static_cast<color_t>(alpha);
}

inline
Color::Color(double red, double green, double blue, double alpha)
{
	m_rgba[0] = static_cast<color_t>(red);
	m_rgba[1] = static_cast<color_t>(green);
	m_rgba[2] = static_cast<color_t>(blue);
	m_rgba[3] = static_cast<color_t>(alpha);
}

inline
Color::Color(int red, int green, int blue, int alpha, color_t divisor)
{
	m_rgba[0] = static_cast<color_t>(red) / divisor;
	m_rgba[1] = static_cast<color_t>(green) / divisor;
	m_rgba[2] = static_cast<color_t>(blue) / divisor;
	m_rgba[3] = static_cast<color_t>(alpha) / divisor;
}

inline
Color & Color::operator +=(const Color & other)
{
	for (std::size_t i = 0; i < SIZE; i++)
		m_rgba[i] += other.rgba()[i];
	return *this;
}

inline
Color & Color::operator -=(const Color & other)
{
	for (std::size_t i = 0; i < SIZE; i++)
		m_rgba[i] -= other.rgba()[i];
	return *this;
}

inline
Color Color::operator +(const Color & other) const
{
	Color result(other);
	for (std::size_t i = 0; i < SIZE; i++)
		result.rgba()[i] += other.rgba()[i];
	return *this;
}

inline
Color Color::operator -(const Color & other) const
{
	Color result(other);
	for (std::size_t i = 0; i < SIZE; i++)
		result.rgba()[i] -= other.rgba()[i];
	return *this;
}

inline
Color::color_t * Color::rgba()
{
	return m_rgba;
}

inline
const Color::color_t * Color::rgba() const
{
	return m_rgba;
}

inline
void Color::setRgba(color_t * rgba)
{
	for (std::size_t i = 0; i < SIZE; i++)
		m_rgba[i] = rgba[i];
}

inline
void Color::setRgba(float red, float green, float blue, float alpha)
{
	m_rgba[0] = static_cast<color_t>(red);
	m_rgba[1] = static_cast<color_t>(green);
	m_rgba[2] = static_cast<color_t>(blue);
	m_rgba[3] = static_cast<color_t>(alpha);
}

inline
void Color::setRgba(double red, double green, double blue, double alpha)
{
	m_rgba[0] = static_cast<color_t>(red);
	m_rgba[1] = static_cast<color_t>(green);
	m_rgba[2] = static_cast<color_t>(blue);
	m_rgba[3] = static_cast<color_t>(alpha);
}

inline
void Color::setRgba(int red, int green, int blue, int alpha, color_t divisor)
{
	m_rgba[0] = static_cast<color_t>(red) / divisor;
	m_rgba[1] = static_cast<color_t>(green) / divisor;
	m_rgba[2] = static_cast<color_t>(blue) / divisor;
	m_rgba[3] = static_cast<color_t>(alpha) / divisor;
}

inline
void Color::setRgb(color_t * rgb)
{
	for (std::size_t i = 0; i < SIZE - 1; i++)
		m_rgba[i] = rgb[i];
}

inline
void Color::setRgb(float red, float green, float blue)
{
	m_rgba[0] = static_cast<color_t>(red);
	m_rgba[1] = static_cast<color_t>(green);
	m_rgba[2] = static_cast<color_t>(blue);
}

inline
void Color::setRgb(double red, double green, double blue)
{
	m_rgba[0] = static_cast<color_t>(red);
	m_rgba[1] = static_cast<color_t>(green);
	m_rgba[2] = static_cast<color_t>(blue);
}

inline
void Color::setRgb(int red, int green, int blue, color_t divisor)
{
	m_rgba[0] = static_cast<color_t>(red) / divisor;
	m_rgba[1] = static_cast<color_t>(green) / divisor;
	m_rgba[2] = static_cast<color_t>(blue) / divisor;
}

inline
Color::color_t Color::red() const
{
	return m_rgba[0];
}

inline
void Color::setRed(float red)
{
	m_rgba[0] = static_cast<color_t>(red);
}

inline
void Color::setRed(double red)
{
	m_rgba[0] = static_cast<color_t>(red);
}

inline
void Color::setRed(int red, color_t divisor)
{
	m_rgba[0] = static_cast<color_t>(red) / divisor;
}

inline
Color::color_t Color::green() const
{
	return m_rgba[1];
}

inline
void Color::setGreen(float green)
{
	m_rgba[1] = static_cast<color_t>(green);
}

inline
void Color::setGreen(double green)
{
	m_rgba[1] = static_cast<color_t>(green);
}

inline
void Color::setGreen(int green, color_t divisor)
{
	m_rgba[1] = static_cast<color_t>(green) / divisor;
}

inline
Color::color_t Color::blue() const
{
	return m_rgba[2];
}

inline
void Color::setBlue(float blue)
{
	m_rgba[2] = static_cast<color_t>(blue);
}

inline
void Color::setBlue(double blue)
{
	m_rgba[2] = static_cast<color_t>(blue);
}

inline
void Color::setBlue(int blue, color_t divisor)
{
	m_rgba[2] = static_cast<color_t>(blue) / divisor;
}

inline
Color::color_t Color::alpha() const
{
	return m_rgba[3];
}

inline
void Color::setAlpha(float alpha)
{
	m_rgba[3] = static_cast<color_t>(alpha);
}

inline
void Color::setAlpha(double alpha)
{
	m_rgba[3] = static_cast<color_t>(alpha);
}

inline
void Color::setAlpha(int alpha, color_t divisor)
{
	m_rgba[3] = static_cast<color_t>(alpha) / divisor;
}

inline
void Color::glSetRgb() const
{
	glColor3fv(m_rgba);
}

inline
void Color::glSetRgba() const
{
	glColor4fv(m_rgba);
}

inline
sf::Color Color::toSfColor() const
{
	return sf::Color(static_cast<sf::Uint8>(red()),
					 static_cast<sf::Uint8>(green()),
					 static_cast<sf::Uint8>(blue()),
					 static_cast<sf::Uint8>(alpha()));
}

}
}

/**
 * Overloaded output stream << operator.
 */
inline
std::ostream & operator<<(std::ostream & s, const gpx::gra::Color & color)
{
	s.precision(3);
	s << "(";
	for (std::size_t i = 0; i < gpx::gra::Color::SIZE - 1; i++)
		s << color.rgba()[i] << ", ";
	s << color.rgba()[gpx::gra::Color::SIZE - 1] << ")" << std::endl;
	return s;
};


#endif /* GPX_Gra_COLOR_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
