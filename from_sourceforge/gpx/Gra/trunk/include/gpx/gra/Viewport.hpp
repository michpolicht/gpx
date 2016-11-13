/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_VIEWPORT_HPP_
#define GPX_Gra_VIEWPORT_HPP_

//must include glew before gl.h
#include "../gl_wrap.hpp"

#include <gpx/platform.hpp>
#include <gpx/utils/Observable.hpp>


namespace gpx {
namespace gra {


/**
 * Viewport. Defines viewable region onto which certain view is displayed.
 */
class GPX_API Viewport : public utils::Observable<Viewport>
{
	public:
		enum param_t {X, Y, WIDTH, HEIGHT};

	protected:
		GLint m_params[4];	//one array for better integration with OpenGL

	public:
		Viewport(GLint width, GLint height);

		Viewport(GLint x, GLint y, GLint width, GLint height);

		virtual ~Viewport();

	public:
		GLint operator[](param_t param) const;	//const version only, since on modification must notify observers

	public:
		GLint param(param_t param) const;

		void setParam(param_t param, GLint val);

		const GLint * params() const;

		void setParams(const GLint params[4]);

		void setParams(GLint x, GLint y, GLint width, GLint height);

		void setSize(GLint width, GLint height);

		void setPos(GLint x, GLint y);

		GLint width() const;

		void setWidth(GLint width);

		GLint height() const;

		void setHeight(GLint height);

		GLint x() const;

		void setX(GLint x);

		GLint y() const;

		void setY(GLint y);
};


}
}

#endif /* GPX_Gra_VIEWPORT_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
