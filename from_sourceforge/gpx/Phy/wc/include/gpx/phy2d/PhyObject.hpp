/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_PHYOBJECT_HPP_
#define GPX_Phy2d_PHYOBJECT_HPP_

#include <gpx/platform.hpp>

#include <ostream>

namespace gpx {
namespace phy2d {

class GPX_API PhyObject
{
	public:
		void setName(const char * name);

		const char * name() const;

	protected:
		PhyObject();

	private:
		const char * m_name;
};

}
}

GPX_API
std::ostream & operator <<(std::ostream & s, const gpx::phy2d::PhyObject & obj);

#endif /* GPX_Phy2d_PHYOBJECT_HPP_ */
