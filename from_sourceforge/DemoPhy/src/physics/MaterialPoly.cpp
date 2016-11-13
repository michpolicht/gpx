/**
 * @file
 * @brief .
 */

#include "MaterialPoly.hpp"

namespace pmepp2_s
{

MaterialPoly::MaterialPoly(const gpx::model::VertexData<2> & vdata, gpx::real_t mass, gpx::phy::material_t material):
	CMaterialBody(mass, material),
	CPoly(vdata)
{
}

MaterialPoly::~MaterialPoly()
{
}

}
