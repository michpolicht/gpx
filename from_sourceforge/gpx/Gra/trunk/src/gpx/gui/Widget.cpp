/**
 * @file
 * @brief .
 */

#include "../../../include/gpx/gui/Widget.hpp"
#include "../../../include/gpx/gui/WidgetLogic.hpp"
#include "../../../include/gpx/gui/WidgetRenderer.hpp"

namespace gpx {
namespace gui {


/*
==============
<PUBLIC>
==============
*/

Widget::Properties::Properties():
		width(INITIAL_WIDTH),
		height(INITIAL_HEIGHT),
		minWidth(INITIAL_MIN_WIDTH),
		minHeight(INITIAL_MIN_HEIGHT),
		widthPolicy(INITIAL_WIDTH_POLICY),
		heightPolicy(INITIAL_HEIGHT_POLICY),
		focusPolicy(INITIAL_FOCUS_POLICY),
		inheritFlags(INITIAL_INHERIT_FLAGS)
{
};





Widget::Widget(WidgetRenderer * renderer, const Properties & defaults):
		m_props(defaults),
		m_focus(false),
		m_renderer(renderer),
		m_parent(0),
		m_rect(m_props.width, m_props.height),
		m_activeArea(OUTER_AREA)
{
	assert(m_renderer != 0); //renderer passed to the constructor must not be NULL
}

Widget::~Widget()
{
	if (parent() != 0)
		GPX_WARN("deleting child object still referenced by parent");
}

Widget::Properties & Widget::Defaults()
{
	static Properties Defaults;
	return Defaults;
}

bool Widget::focus() const
{
	return m_focus;
}

void Widget::setFocus(bool focus)
{
	if (m_focus != focus) {
		m_focus = focus;
		if (focus)
			event(StateEvent(StateEvent::FOCUS_RECEIVED));
		else
			event(StateEvent(StateEvent::FOCUS_LOST));
	}
}

Widget::focusPolicy_t Widget::focusPolicy() const
{
	return m_props.focusPolicy;
}

void Widget::setFocusPolicy(focusPolicy_t focusPolicy)
{
	if (m_props.focusPolicy != focusPolicy) {
		m_props.focusPolicy = focusPolicy;
		event(StateEvent(StateEvent::FOCUS_POLICY_CHANGED));
	}
}

Widget::sizePolicy_t Widget::widthPolicy() const
{
	return m_props.widthPolicy;
}

void Widget::setWidthPolicy(sizePolicy_t widthPolicy)
{
	if (m_props.widthPolicy != widthPolicy) {
		m_props.widthPolicy = widthPolicy;
		event(StateEvent(StateEvent::SIZE_POLICY_CHANGED));
	}
}

Widget::sizePolicy_t Widget::heightPolicy() const
{
	return m_props.heightPolicy;
}

void Widget::setHeightPolicy(sizePolicy_t heightPolicy)
{
	if (m_props.heightPolicy != heightPolicy) {
		m_props.heightPolicy = heightPolicy;
		event(StateEvent(StateEvent::SIZE_POLICY_CHANGED));
	}
}

void Widget::setSizePolicy(sizePolicy_t sizePolicy)
{
	if ((m_props.widthPolicy != sizePolicy) || (m_props.heightPolicy != sizePolicy)) {
		m_props.widthPolicy = sizePolicy;
		m_props.heightPolicy = sizePolicy;
		event(StateEvent(StateEvent::SIZE_POLICY_CHANGED));
	}
}

Widget::inheritFlags_t Widget::inheritFlags() const
{
	return m_props.inheritFlags;
}

void Widget::setInheritFlags(inheritFlags_t inheritFlags)
{
	if (m_props.inheritFlags != inheritFlags) {
		m_props.inheritFlags = inheritFlags;
		if (parent() != 0)
			inheritPolicies(parent());
	}
}

void Widget::inheritPolicies(const Widget * widget)
{
	inheritFlags_t flags = inheritFlags();
	if (flags & INHERIT_FOCUS_POLICY)
		setFocusPolicy(widget->focusPolicy());
	if (flags & INHERIT_WIDTH_POLICY)
		setWidthPolicy(widget->widthPolicy());
	if (flags & INHERIT_HEIGHT_POLICY)
		setHeightPolicy(widget->heightPolicy());
}

math::Vector<2> Widget::size() const
{
	return math::Vector<2>(width(), height());
}

void Widget::setSize(math::const_VectorRef<2> size, sizePolicy_t widthType, sizePolicy_t heightType)
{
	setSize(size[0], size[1], widthType, heightType);
}

void Widget::setSize(real_t width, real_t height, sizePolicy_t widthType, sizePolicy_t heightType)
{
	if ((widthPolicy() == widthType) || (heightPolicy() == heightType)) {
		if ((width > minWidth()) || (height > minHeight())) {
			if (widthPolicy() == widthType)
				m_props.width = std::max(minWidth(), width);
			if (heightPolicy() == heightType)
				m_props.height = std::max(minHeight(), height);
			m_rect.setSize(m_props.width, m_props.height);
			event(StateEvent(StateEvent::TOTAL_SIZE_CHANGED));
		}
	}
}

void Widget::setSize(math::const_VectorRef<2> size, sizePolicy_t type)
{
	setSize(size[0], size[1], type, type);
}

void Widget::setSize(real_t width, real_t height, sizePolicy_t type)
{
	setSize(width, height, type, type);
}

real_t Widget::width() const
{
	return m_props.width;
}

void Widget::setWidth(real_t width, sizePolicy_t type)
{
	if ((widthPolicy() == type) && (width > minWidth())) {
		m_props.width = width;
		m_rect.setWidth(m_props.width);
		event(StateEvent(StateEvent::TOTAL_SIZE_CHANGED));
	}
}

real_t Widget::height() const
{
	return m_props.height;
}

void Widget::setHeight(real_t height, sizePolicy_t type)
{
	if ((heightPolicy() == type) && (height > minHeight())) {
		m_props.height = height;
		m_rect.setHeight(m_props.height);
		event(StateEvent(StateEvent::TOTAL_SIZE_CHANGED));
	}
}

real_t Widget::minWidth() const
{
	return m_props.minWidth;
}

void Widget::setMinWidth(real_t minWidth)
{
	if (width() < minWidth)
		setWidth(minWidth, widthPolicy());
	m_props.minWidth = minWidth;
}

real_t Widget::minHeight() const
{
	return m_props.minHeight;
}

void Widget::setMinHeight(real_t minHeight)
{
	if (height() < minHeight)
		setHeight(minHeight, heightPolicy());
	m_props.minHeight = minHeight;
}

math::Vector<2> Widget::minSize() const
{
	return math::Vector<2>(minWidth(), minHeight());
}

void Widget::setMinSize(real_t minWidth, real_t minHeight)
{
	if ((width() < minWidth) && (height() < minHeight))
		setSize(minWidth, minHeight, widthPolicy(), heightPolicy());
	else if (width() < minWidth)
		setWidth(minWidth, widthPolicy());
	else if (height() < minHeight)
		setHeight(minHeight, heightPolicy());
	m_props.minWidth = minWidth;
	m_props.minHeight = minHeight;
}

void Widget::setMinSize(math::const_VectorRef<2> size)
{
	setMinSize(size[0], size[1]);
}

math::Vector<2> Widget::totalSize() const
{
	return math::Vector<2>(totalWidth(), totalHeight());
}

WidgetRenderer * Widget::renderer() const
{
	return m_renderer;
}

Widget * Widget::parent() const
{
	return m_parent;
}

void Widget::setParent(Widget * parent)
{
	m_parent = parent;
	if (parent != 0)
		inheritPolicies(parent);
	event(StateEvent(StateEvent::PARENT_CHANGED));
}

const Rect & Widget::rect() const
{
	return m_rect;
}

Widget::area_t Widget::activeArea() const
{
	return m_activeArea;
}

math::Point<2> Widget::mapToGlobal(math::const_PointRef<2> point) const
{
	return Parent::mapToGlobal(point);
}

math::Point<2> Widget::mapToLocal(math::const_PointRef<2> point) const
{
	return Parent::mapToLocal(point);
}

void Widget::event(const CursorEvent & e)
{
	if (!focus() && (focusPolicy() == FOCUS_ON_CURSOR_MOVE) && (e.action() == CursorEvent::MOVE))
		attemptFocus(e.x(), e.y());
	if (focus()) {
		updateActiveArea(e.x(), e.y());
		event(Widget::Event<CursorEvent>(e, activeArea()));
		if ((focusPolicy() == FOCUS_ON_CURSOR_MOVE) && (e.action() == CursorEvent::MOVE))
			attemptFocus(e.x(), e.y());	//attemptFocus may be called second time for the same event, but this shouldn't be a problem
	}
}

void Widget::event(const TriggerEvent & e)
{
	if (!focus() && (focusPolicy() == FOCUS_ON_PRIMARY_PRESS) && (e.action() == TriggerEvent::PRESS)
	&& (e.type() == TriggerEvent::PRIMARY))
		attemptFocus(e.x(), e.y());
	if (focus()) {
		updateActiveArea(e.x(), e.y());
		event(Widget::Event<TriggerEvent>(e, activeArea()));
		if ((focusPolicy() == FOCUS_ON_PRIMARY_PRESS) && (e.action() == TriggerEvent::PRESS)
		&& (e.type() == TriggerEvent::PRIMARY))
			attemptFocus(e.x(), e.y());	//attemptFocus may be called second time for the same event, but this shouldn't be a problem
	}
}

void Widget::event(const ScrollEvent & e)
{
	if (focus())
		event(Widget::Event<ScrollEvent>(e, activeArea()));
}

bool Widget::test(math::const_PointRef<2> cvertex) const
{
	if ((cvertex[0] > 0.0 && cvertex[0] < width()) &&
		(cvertex[1] < 0.0 && cvertex[1] > -height()))
			return true;
		else
			return false;
}

IGuiDetection::zHint_t Widget::zHint() const
{
	return renderer()->painterPlane();
}

Widget::area_t Widget::area(real_t x, real_t y) const
{
	if (test(math::Point<2>(x, y)))
		return WORK_AREA;
	else
		return OUTER_AREA;
}

real_t Widget::totalWidth() const
{
	//@todo use m_renderer->width() to calculate size with decorations etc
	return width();
}

real_t Widget::totalHeight() const
{
	return height();
}

/*
==============
<PROTECTED>
==============
*/


void Widget::attemptFocus(real_t x, real_t y)
{
	if (test(mapToLocal(math::Point<2>(x, y))))
		setFocus(true);
	else
		setFocus(false);
}

void Widget::event(const Widget::StateEvent & e)
{
	//one for the object itself
	event(Widget::Event<StateEvent>(e, activeArea()));

	//second for the parent
	if (parent() != 0)
		parent()->event(Widget::Event<ChildEvent>(ChildEvent(e.state(), this), activeArea()));
}

void Widget::event(const Widget::Event<CursorEvent> & )
{
}

void Widget::event(const Widget::Event<TriggerEvent> & )
{
}

void Widget::event(const Widget::Event<ScrollEvent> & )
{
}

void Widget::event(const Widget::Event<StateEvent> & )
{
}

void Widget::event(const Widget::Event<ChildEvent> & )
{
}

/*
==============
<PRIVATE>
==============
*/

void Widget::updateActiveArea(real_t x, real_t y)
{
	area_t oldArea = m_activeArea;
	math::Point<2> pos(mapToLocal(math::Point<2>(x, y)));
	if ((m_activeArea = area(pos[0], pos[1])) != oldArea)
		event(StateEvent(StateEvent::ACTIVE_AREA_CHANGED));
}

}
}
