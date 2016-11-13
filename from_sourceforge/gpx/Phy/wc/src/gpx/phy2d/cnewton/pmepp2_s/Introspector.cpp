#include "../../../../../include/gpx/phy2d/cnewton/pmepp2_s/Introspector.hpp"

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

const char * Introspector::DEFAULT_ERROR_MSG = "no error";

Introspector::Introspector():
	m_error(false),
	m_errorMsg(DEFAULT_ERROR_MSG)
{
}

void Introspector::triggerError(const char * msg)
{
	m_errorMsg = msg;
	m_error = true;
}

void Introspector::resetError()
{
	m_error = false;
	m_errorMsg = DEFAULT_ERROR_MSG;
}

bool Introspector::error() const
{
	return m_error;
}

const char * Introspector::errorMsg() const
{
	return m_errorMsg;
}

void Introspector::setSkipBreakpoints(bool )
{
}

void Introspector::breakpoint()
{
}

void Introspector::off(const ICFixed & )
{
}

void Introspector::light(const ICFixed & )
{
}

void Introspector::highlight(const ICFixed & )
{
}

void Introspector::playdown(const ICFixed & )
{
}

}
}
}
}
