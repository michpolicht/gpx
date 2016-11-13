/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CDETECT_INTERSEG_CPOLY_HPP_
#define GPX_Phy2d_CDETECT_INTERSEG_CPOLY_HPP_

#include "ICPolyGroup.hpp"

#include <gpx/model/Poly.hpp>
#include <gpx/model/functions.hpp>
#include <gpx/log.hpp>

namespace gpx {
namespace phy2d {
namespace cdetect {
namespace interseg {

/**
 * Colliding polygon frame implementation.
 *
 * @todo consider using/test model::sqdistance() instead of model::intersection(prePost, seg)).dot() in normal().
 */
template <class DERIVED>
class base_CPoly : public virtual ICPoly,
				   public virtual ICPolyGroup
{
	template <model::index_t INDEX>
	friend class CPoly;

	public:
		//ICPoly
		virtual const model::VertexData<2> & cvertices() const;

		//ICPoly
		virtual math::Vector<2> normal(math::const_PointRef<2> pre, math::const_PointRef<2> post) const;

		//ICPoly
		virtual bool test(math::const_PointRef<2> pre, math::const_PointRef<2> post) const;

		//ICPolyGroup
		virtual element_t elements() const;

		//ICPolyGroup
		virtual const ICPoly * element(element_t i) const;

	protected:
		/**
		 * Default constructor. This class is not intended to be used directly - use
		 * CPoly.
		 */
		base_CPoly();

	private:
		DERIVED & derived();

		const DERIVED & derived() const;
};

template <class DERIVED>
base_CPoly<DERIVED>::base_CPoly()
{
}

template <class DERIVED>
const model::VertexData<2> & base_CPoly<DERIVED>::cvertices() const
{
	return derived().vdata();
}

template <class DERIVED>
math::Vector<2> base_CPoly<DERIVED>::normal(math::const_PointRef<2> pre, math::const_PointRef<2> post) const
{
	model::const_SegmentPtr<2> seg, result;
	real_t dst = std::numeric_limits<real_t>::infinity(); //distance
	model::const_SegmentPtr<2> prePost(pre.ptr(), post.ptr());

	typename DERIVED::const_iterator i = derived().begin();
	seg.setFirstPtr(*i);
	while (++i != derived().end()) {
		seg.setSecondPtr(*i);
		if (model::intersect(seg, prePost)) {
			//if more segments are intersecting take one closer to post-collision point (note that bumper's post is wedge's pre)
			real_t newDst = (post - model::intersection(prePost, seg)).dot();
			if (newDst < dst) {
				result = seg;
				dst = newDst;
			}
		}
		seg.setFirstPtr(seg->second().ptr()); //next iteration
	}
	seg.setSecondPtr(*(derived().begin())); //looping segment
	if (model::intersect(seg, prePost))
		//if more segments are intersecting take one closer to post-collision point (note that bumper's post is wedge's pre)
		if ((post - model::intersection(prePost, seg)).dot() < dst)
			result = seg;

	if (result.isNull()) {
		//shouldn't happen if segment was tested with test() before, but to avoid tragedy...
		//note: this warning is going to be removed after test and normal are merged.
		GPX_WARN("can't determine normal vector for given collision points: " << pre << post);
		return math::Vector<2>();
	}
	return (result->second() - result->first()).normalize().orthoCW();
}

template <class DERIVED>
bool base_CPoly<DERIVED>::test(math::const_PointRef<2> pre, math::const_PointRef<2> post) const
{
	const real_t * first;
	const real_t * second;

	typename DERIVED::const_iterator i = derived().begin();
	first = *i;
	while (++i != derived().end()) {
		second = *i;
		if (model::intersect(model::const_SegmentPtr<2>(pre.ptr(), post.ptr()), model::const_SegmentPtr<2>(first, second)))
			return true;
		first = second;	//next iteration
	}
	second = *(derived().begin()); //looping segment
	if (model::intersect(model::const_SegmentPtr<2>(pre.ptr(), post.ptr()), model::const_SegmentPtr<2>(first, second)))
		return true;
	return false;
}

template <class DERIVED>
ICPolyGroup::element_t base_CPoly<DERIVED>::elements() const
{
	return 1;
}

template <class DERIVED>
const ICPoly * base_CPoly<DERIVED>::element(element_t ) const
{
	return this;
}

template <class DERIVED>
const DERIVED & base_CPoly<DERIVED>::derived() const
{
	return static_cast<const DERIVED & >(*this);
}

template <class DERIVED>
DERIVED & base_CPoly<DERIVED>::derived()
{
	return static_cast<DERIVED & >(*this);
}

/**
 * Colliding polygon frame (indexed variants).
 */
template <model::index_t INDEX>
class CPoly : public model::Poly<2, INDEX, real_t>,
			  public base_CPoly<CPoly<INDEX> >
{
	typedef model::Poly<2, INDEX, real_t> Parent;

	public:
		/**
		 * Constructor.
		 * @param indices pointer to indices data.
		 * @param size indices data size.
		 * @param vdata vertices data.
		 */
		CPoly(typename Parent::index_t * indices, std::size_t size, const model::VertexData<2> & vdata);

		/**
		 * Constructor.
		 * @param index indices data.
		 * @param vdata vertices data.
		 */
		CPoly(const typename Parent::Index & index, const model::VertexData<2> & vdata);
};

template <model::index_t INDEX>
CPoly<INDEX>::CPoly(typename Parent::index_t * indices, std::size_t size, const model::VertexData<2> & vdata):
	Parent(indices, size, vdata)
{
}

template <model::index_t INDEX>
CPoly<INDEX>::CPoly(const typename Parent::Index & index, const model::VertexData<2> & vdata):
	Parent(index, vdata)
{
}


/**
 * Colliding polygon frame (non-indexed specialization).
 */
template <>
class CPoly<model::NONE> : public model::Poly<2, model::NONE, real_t>,
						   public base_CPoly<CPoly<model::NONE> >
{
	typedef model::Poly<2, model::NONE, real_t> Parent;

	public:
		/**
		 * Constructor.
		 * @param vdata vertices data.
		 */
		CPoly(const model::VertexData<2> & vdata);
};

inline
CPoly<model::NONE>::CPoly(const model::VertexData<2> & vdata):
	Parent(vdata)
{
}


}
}
}
}

#endif /* GPX_Phy2d_CDETECT_INTERSEG_CPOLY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
