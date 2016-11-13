/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CNEWTON_PMEPP2_S_CLUSTER_HPP_
#define GPX_Phy2d_CNEWTON_PMEPP2_S_CLUSTER_HPP_

#include "../../cdetect/interseg/ICPolyGroup.hpp"

#include <vector>

namespace gpx {
namespace phy2d {
namespace cnewton {
namespace pmepp2_s {

class ICFixed;
class ICMovable;
struct Cluster;

struct ContactData
{
	std::size_t index;				///< Index of contact within a cluster.
	math::Point<2> pre;				///< C-vertex position before collision (given in local coordinates).
	math::Point<2> post;			///< C-vertex position after collision (given in local coordinates).
	math::Vector<2> normal;			///< Normal to the "bumper's" surface (calculated by "bumper", given in global coordinates).
	bool wedge;						///< Indicates if object collides as a wedge or a bumper. @todo replace by cvertIt.
	cdetect::interseg::ICPolyGroup::element_t element;	///< Colliding element index.
	model::VertexData<2>::const_iterator cvertIt;		///< C-vertex iterator. Points to a c-vertex which makes contact in case of wedge, while in case of bumper it points to end() of bumper c-vertex data.
};

typedef std::vector<ContactData> ContactDataContainer;

struct DetectionData
{
	ICFixed * fix;
	ICMovable * mov;
	const Cluster * cluster;
	ContactDataContainer contacts;

	DetectionData(ICFixed & p_fix, ICMovable * p_mov, const Cluster & p_cluster):
		fix(& p_fix),
		mov(p_mov),
		cluster(& p_cluster)
	{
	}
};

typedef std::vector<DetectionData> DetectionDataContainer;

struct Cluster
{
	real_t dt;				///< Collision time.
	std::size_t endIndex;	///< End index. Equivalent to total number of contacts.
	DetectionDataContainer detections;

	Cluster(real_t p_dt):
		dt(p_dt),
		endIndex(0)
	{
	}
};

typedef std::vector<Cluster *> ClustersContainer;

}
}
}
}

#endif /* GPX_Phy2d_CNEWTON_PMEPP2_S_CLUSTER_HPP_ */

//(c)MP: Copyright © 2013, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
