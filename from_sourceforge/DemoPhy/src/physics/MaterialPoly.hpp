/**
 * @file
 * @brief .
 */

#ifndef MATERIALPOLY_HPP_
#define MATERIALPOLY_HPP_

#include <gpx/phy2d/cdetect/interseg/CPoly.hpp>
#include <gpx/phy2d/cnewton/pmepp2_s/CMaterialBody.hpp>

namespace pmepp2_s
{

class MaterialPoly : public gpx::phy2d::cnewton::pmepp2_s::CMaterialBody,
					 public gpx::phy2d::cdetect::interseg::CPoly<gpx::model::NONE>
{
	typedef gpx::phy2d::cnewton::pmepp2_s::CMaterialBody CMaterialBody;
	typedef gpx::phy2d::cdetect::interseg::CPoly<gpx::model::NONE> CPoly;

	public:
		MaterialPoly(const gpx::model::VertexData<2> & vdata, gpx::real_t mass, gpx::phy::material_t material = 0);

		virtual ~MaterialPoly();
};

}

#endif /* MATERIALPOLY_HPP_ */
