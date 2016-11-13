/**
 * @file
 * @brief .
 */

#ifndef GPX_Gra_GUI_WIDGET_HPP_
#define GPX_Gra_GUI_WIDGET_HPP_

#include "WidgetRenderer.hpp"
#include "Rect.hpp"
#include "IGuiDetection.hpp"
#include "IEventListener.hpp"
#include "../gra2d/GraphicsObject.hpp"

namespace gpx {
namespace gui {

class WidgetLogic;

/**
 * Widget.
 *
 * @todo size should have separate type (with width(), height() methods), not a vector.
 */
class GPX_API Widget : public gra2d::GraphicsObject,
					   public virtual IGuiDetection,
					   public virtual IEventListener
{
	typedef gra2d::GraphicsObject Parent;

	public:
		typedef WidgetRenderer Renderer;
		typedef int area_t;
		typedef int inheritFlags_t;

		enum areaNames_t {
				OUTER_AREA,
				WORK_AREA,
				//insert elements here if necessary. WIDGET_AREA must be last element.
				WIDGET_AREA
		};

		enum focusPolicy_t {
				FOCUS_ON_CURSOR_MOVE,
				FOCUS_ON_PRIMARY_PRESS
		};

		enum sizePolicy_t {
				FIXED_SIZE,
				PARENT_SIZE,
				CHILD_SIZE
		};

		enum inheritFlagsNames_t {
				INHERIT_NOTHING = 0,
				INHERIT_FOCUS_POLICY = 1,
				INHERIT_WIDTH_POLICY = 2,
				INHERIT_HEIGHT_POLICY = 4,
				INHERIT_SIZE_POLICY = INHERIT_HEIGHT_POLICY | INHERIT_WIDTH_POLICY
		};

		struct Properties
		{
			static const real_t INITIAL_WIDTH = 0.0;
			static const real_t INITIAL_HEIGHT = 0.0;
			static const real_t INITIAL_MIN_WIDTH = 0.0;
			static const real_t INITIAL_MIN_HEIGHT = 0.0;
			static const focusPolicy_t INITIAL_FOCUS_POLICY = FOCUS_ON_PRIMARY_PRESS;
			static const sizePolicy_t INITIAL_WIDTH_POLICY = FIXED_SIZE;
			static const sizePolicy_t INITIAL_HEIGHT_POLICY = FIXED_SIZE;
			static const inheritFlags_t INITIAL_INHERIT_FLAGS = INHERIT_FOCUS_POLICY;

			real_t width;
			real_t height;
			real_t minWidth;
			real_t minHeight;
			sizePolicy_t widthPolicy;
			sizePolicy_t heightPolicy;
			focusPolicy_t focusPolicy;
			inheritFlags_t inheritFlags;

			Properties();
		};

	public:
		Widget(WidgetRenderer * renderer, const Properties & defaults = Defaults());

		virtual ~Widget();

	public:
		/**
		 * Widget defaults.
		 * @return default values used to construct object.
		 */
		static Properties & Defaults();

	public:
		bool focus() const;

		void setFocus(bool focus);

		focusPolicy_t focusPolicy() const;

		void setFocusPolicy(focusPolicy_t);

		inheritFlags_t inheritFlags() const;

		sizePolicy_t widthPolicy() const;

		void setWidthPolicy(sizePolicy_t widthPolicy);

		sizePolicy_t heightPolicy() const;

		void setHeightPolicy(sizePolicy_t heightPolicy);

		void setSizePolicy(sizePolicy_t sizePolicy);

		void setInheritFlags(inheritFlags_t inheritFlags);

		void inheritPolicies(const Widget * widget);

		math::Vector<2> size() const;

		void setSize(math::const_VectorRef<2> size, sizePolicy_t widthType, sizePolicy_t heightType);

		void setSize(real_t width, real_t height, sizePolicy_t widthType, sizePolicy_t heightType);

		void setSize(math::const_VectorRef<2> size, sizePolicy_t type = FIXED_SIZE);

		void setSize(real_t width, real_t height, sizePolicy_t type = FIXED_SIZE);

		//nominal width (netto)
		real_t width() const;

		void setWidth(real_t width, sizePolicy_t type = FIXED_SIZE);

		real_t height() const;

		void setHeight(real_t width, sizePolicy_t type = FIXED_SIZE);

		real_t minWidth() const;

		void setMinWidth(real_t minWidth);

		real_t minHeight() const;

		void setMinHeight(real_t minHeight);

		math::Vector<2> minSize() const;

		void setMinSize(real_t minWidth, real_t minHeight);

		void setMinSize(math::const_VectorRef<2> size);

		math::Vector<2> totalSize() const;

		WidgetRenderer * renderer() const;  //WidgetRenderer contains const Widget *.

		Widget * parent() const;	//Parent widget has no direct connection with child.

		void setParent(Widget * parent);

		const Rect & rect() const;

		area_t activeArea() const;

		//IColliding
		math::Point<2> mapToGlobal(math::const_PointRef<2> point) const;

		//IColliding
		math::Point<2> mapToLocal(math::const_PointRef<2> point) const;

		//IEventListener
		void event(const CursorEvent & e);

		//IEventListener
		void event(const TriggerEvent & e);

		//IEventListener
		void event(const ScrollEvent & e);

		//IColliding
		virtual bool test(math::const_PointRef<2> cvertex) const;

		//IColliding
		virtual IGuiDetection::zHint_t zHint() const;

		virtual area_t area(real_t x, real_t y) const;

		//total width with decorations etc (brutto)
		virtual real_t totalWidth() const;

		virtual real_t totalHeight() const;

	protected:
		class StateEvent
		{
			public:
				typedef int state_t;

				enum stateNames_t {
					TOTAL_SIZE_CHANGED,
					FOCUS_RECEIVED,
					FOCUS_LOST,
					ACTIVE_AREA_CHANGED,
					PARENT_CHANGED,
					FOCUS_POLICY_CHANGED,
					SIZE_POLICY_CHANGED,
					//insert elements here if necessary. LAST_STATE_EVENT must be last element.
					LAST_STATE_EVENT
				};

			public:
				StateEvent(state_t state);

				state_t state() const;

			private:
				state_t m_state;
		};

		class ChildEvent : public StateEvent
		{
			typedef StateEvent Parent;

			public:
				ChildEvent(state_t state, const Widget * child);

				const Widget * child() const;

			private:
				const Widget * m_child;
		};

		template <class EVENT>
		class Event : public EVENT
		{
			public:
				Event(const EVENT & e, area_t area);

				area_t area() const;

			private:
				area_t m_area;
		};

	protected:
		//void setRenderer(WidgetRenderer * renderer);

		void attemptFocus(real_t x, real_t y);

		void event(const Widget::StateEvent & e);

		virtual void event(const Widget::Event<CursorEvent> & e);

		virtual void event(const Widget::Event<TriggerEvent> & e);

		virtual void event(const Widget::Event<ScrollEvent> & e);

		virtual void event(const Widget::Event<StateEvent> & e);

		virtual void event(const Widget::Event<ChildEvent> & e);

	private:
		void updateActiveArea(real_t x, real_t y);

	private:
		Properties m_props;
		bool m_focus;
		WidgetRenderer * m_renderer;
		Widget * m_parent;
		Rect m_rect;
		area_t m_activeArea;
};


inline
Widget::StateEvent::StateEvent(state_t state):
		m_state(state)
{
}

inline
Widget::StateEvent::state_t Widget::StateEvent::state() const
{
	return m_state;
}



inline
Widget::ChildEvent::ChildEvent(state_t state, const Widget * child):
		Parent(state),
		m_child(child)
{
}

inline
const Widget * Widget::ChildEvent::child() const
{
	return m_child;
}



template <class EVENT>
inline
Widget::Event<EVENT>::Event(const EVENT & e, area_t area):
		EVENT(e),
		m_area(area)
{
}

template <class EVENT>
inline
Widget::area_t Widget::Event<EVENT>::area() const
{
	return m_area;
}




}
}

#endif /* GPX_Gra_GUI_WIDGET_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
