/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_RECT_HPP_
#define GPX_Gra_GUI_RECT_HPP_

#include <gpx/model/Poly.hpp>

namespace gpx {
namespace gui {

/**
 *
 */
class GPX_API Rect : public model::Poly<2, model::NONE>
{
	typedef model::Poly<2, model::NONE> Parent;

	public:
		static const std::size_t VERTEX_NUM = 4;
		static const std::size_t DIM = 2;

	public:
		Rect();

		Rect(real_t width, real_t height);

//		BoxFrame(real_t x, real_t y, real_t width, real_t height);

	public:
//		real_t x() const;
//
//		void setX(real_t x);
//
//		real_t y() const;
//
//		void setY(real_t y);

		void setSize(real_t width, real_t height);

		real_t width() const;

		void setWidth(real_t width);

		real_t height() const;

		void setHeight(real_t height);

	protected:
		real_t * vertices();

	private:
		real_t m_vertices[DIM * VERTEX_NUM];
};


}
}

#endif /* GPX_Gra_GUI_RECT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
