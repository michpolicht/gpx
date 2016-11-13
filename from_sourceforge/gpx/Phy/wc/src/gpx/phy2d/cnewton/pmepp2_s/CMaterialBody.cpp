/**
 * @file
 * @brief .
 */

#include "../../../../../include/gpx/phy2d/cnewton/pmepp2_s/CMaterialBody.hpp"

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

CMaterialBody::CMaterialBody(real_t m, phy::material_t material):
		Parent(m),
		m_material(material)
{
}

CMaterialBody::~CMaterialBody()
{
}

void CMaterialBody::aCoefs(const DetectionData & dData, math::Matrix<> & a) const
{
	for (ContactDataContainer::const_iterator v = dData.contacts.begin(); v != dData.contacts.end(); ++v)
		for (ContactDataContainer::const_iterator i = dData.contacts.begin(); i != dData.contacts.end(); ++i)
			a(v->index, i->index) += v->normal.dot(i->normal) / m();
}

void CMaterialBody::bCoefs(const DetectionData & dData, math::Vector<> & b) const
{
	for (ContactDataContainer::const_iterator v = dData.contacts.begin(); v != dData.contacts.end(); ++v)
		b(v->index) += pB().dot(v->normal) / m();
}

//phy::material_t CMaterialBody::material() const
//{
//	return m_material;
//}
//
//void CMaterialBody::setMaterial(phy::material_t material)
//{
//	m_material = material;
//}

void CMaterialBody::applyImpulse(const Impulse & impulse, math::const_PointRef<2> point)
{
	Parent::applyImpulse(impulse, point);
}

void CMaterialBody::passLimit(const DetectionDataContainer & )
{
	GPX_DEBUG("subsequent collision limit");
}

bool CMaterialBody::dislocate(math::Vector<2> & disloc)
{
	GPX_UNUSED(disloc);

	GPX_WARN("dislocate not implemented yet");
	return false;
}

//void CMaterialBody::roundAwayImpulses(Impulse & normal, Impulse & parallel, const CollisionData & cData)
//{
//}
//
//phy::material_t CMaterialBody::material(element_t element) const
//{
//	return m_material;
//}

}
}
}
}

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
