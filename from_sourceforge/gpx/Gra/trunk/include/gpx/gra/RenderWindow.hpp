/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_RENDERWINDOW_HPP_
#define GPX_Gra_RENDERWINDOW_HPP_

//must include glew before gl.h
#include "../gl_wrap.hpp"

#include <list>

#include <SFML/Graphics.hpp>

#include <gpx/platform.hpp>
#include <gpx/log.hpp>

#include "Viewport.hpp"


namespace gpx {
namespace gra {


/**
 * Render window. This class is a wrapper of SFML sf::RenderWindow. In addition to
 * sf::RenderWindow it initializes GLEW and prints some information.
 */
class GPX_API RenderWindow : public sf::RenderWindow
{
	typedef sf::RenderWindow Parent;

//	public:
//		class Requirements;
//
//	protected:
//		typedef std::list<Requirements *> ReqListContainer;
//
//	protected:
//		static std::list<Requirements *> ReqList;
//	public:
//		static void AddRequirements(Requirements * req);
//
//		static void CheckRequirements();

	public:
		/**
		 * Default constructor.
		 */
		RenderWindow();

		/**
		 * Constructor.
		 * @param mode video mode to use.
		 * @param title title of the window.
		 * @param windowStyle windows style (Resize | Close by default).
		 * @param params creation parameters (see default constructor for default values).
		 */
		RenderWindow(sf::VideoMode mode, const std::string & title, unsigned long windowStyle = sf::Style::Resize | sf::Style::Close, const sf::WindowSettings & params = sf::WindowSettings());

		/**
		 * Constructor.
		 * @param handle platform-specific handle of the control.
		 * @param params creation parameters (see default constructor for default values).
		 */
		RenderWindow(sf::WindowHandle handle, const sf::WindowSettings & params = sf::WindowSettings());

		/**
		 * Destructor.
		 */
		virtual ~RenderWindow();

		/**
		 * Get viewport.
		 * @return viewport object.
		 */
		Viewport & viewport();

		/**
		 * Fetch event from the stack, if any. Works in the same way as GetEvent() but in
		 * addition RenderWindow object reacts to events addressed to itself.
		 * @param e event to be received.
		 * @return @p true if an event was returned, @p false if events stack was empty.
		 *
		 * @internal This is done in such way, because virtual sf::WindowListener::OnEvent()
		 * method is private in sf::Window and it is not possible to do both: catch window
		 * events and call method on parent class.
		 *
		 * @todo tell SFML team that sf::Window::OnEvent() should be protected.
		 */
		bool fetchEvent(sf::Event & e);

		/**
		 * Post event to the queue.
		 * @param e event.
		 */
		void postEvent(sf::Event & e);

		/**
		 * Print some OpenGL information to the info log.
		 * @param level verbosity level.
		 */
		void logGlInfo(int level) const;

		/**
		 * Display the window. Works in the same way as SFML sf::RenderWindow, but performs
		 * additional OpenGL error check.
		 */
		void display();

	protected:
		/**
		 * Get event from the stack. Use fetchEvent() instead, at least until not
		 * inheriting after this class.
		 * @param e received event.
		 * @return @p true if an event was returned, @p false if events stack was empty.
		 */
		bool GetEvent(sf::Event & e);

	protected:
		/**
		 * Prevent SFML Display() from being called.
		 *
		 * @note use display() instead.
		 */
		void Display();

	private:
		/**
		 * Initialize render window. This method is a part of constructor.
		 */
		void init();

	private:
		Viewport m_viewport;
};


}
}

#endif /* GPX_Gra_RENDERWINDOW_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
