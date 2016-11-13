/**
 * @file
 * @brief .
 */

#ifndef GPX_Phy2d_CPOLY_HPP_
#define GPX_Phy2d_CPOLY_HPP_

#include "ICPolyGroup.hpp"

#include <gpx/model/Poly.hpp>
#include <gpx/model/functions.hpp>
#include <gpx/log.hpp>

namespace gpx {
namespace phy2d {


/**
 * Colliding polygon frame implementation.
 *
 * @todo there's better algorithm for test().
 */
template <class F>
class base_CPoly : public virtual ICPoly,
				   public virtual ICPolyGroup
{
	template <model::index_t INDEX>
	friend class CPoly;

	public:
		static const real_t INITIAL_EFF_MULTIPLIER = 1.0 / 128.0;	///< Default value of effective point offset multiplier.

	public:
		/**
		 * Set effective point's offset multiplier. CPoly is able to calculate
		 * effective point value. For NewtonCollider simulation it is crucial to assure
		 * that effective point lies slightly outside polygon. Even if algorithm could find
		 * points which satisfy that assumption, they may lie in very close distance to the
		 * edge of the polygon. As a consequence precise position of effective point may be
		 * defected due to nature of floating point arithmetics (for example during
		 * transformations between local and global coordinates). To prevent this, effective
		 * point is slightly moved into direction normal to considered edge of the polygon.
		 * This parameter describes how far effective point should be dislocated. Initial
		 * dislocation distance, to be multiplied by this parameter, is the length of
		 * the edge for which effective point is being calculated.
		 *
		 * @param effMultiplier effective point's offset multiplier.
		 */
		void setEffMultiplier(real_t effMultiplier);

		/**
		 * Get effective point's offset multiplier.
		 * @return effective point's offset multiplier.
		 */
		real_t effMultiplier() const;

		//IPointDetection
		virtual bool test(const math::const_VectorPtr<2> & cvertex) const;

		//ICPoly
		virtual const model::VertexData<2> & cvertices() const;

		//ICPoly
		virtual math::Vector<2> eff(const math::const_VectorPtr<2> & pre, const math::const_VectorPtr<2> & post) const;

		//ICPoly
		virtual math::Vector<2> normal(const CollisionPoints & ncPoints) const;

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
		//special case - vertex lies on vertical edge...
		bool vertexOnVEdge(const math::const_VectorPtr<2> & cvertex, real_t * first, real_t * second) const;

		//test if vertex is inside a polygon
		int testVertex(const math::const_VectorPtr<2> & cvertex, real_t * first, real_t * second) const;

		/**
		 * Find polygon's segment intersecting with segment @a seg. If two or more intersection
		 * points exist, function will consider only first encountered intersecting segments.
		 *
		 * @param seg segment.
		 * @return @p true if intersecting segments were found, @p false otherwise.
		 */
		bool findIntersectingSeg(const model::const_Segment<2> & seg) const;

	private:
		F & m_me;
		real_t m_effMultiplier;	///< Effective point offset multiplier.
		mutable model::const_Segment<2> m_intSegCache;
};

template <class F>
inline
base_CPoly<F>::base_CPoly():
	m_me(static_cast<F & >(*this)),
	m_effMultiplier(INITIAL_EFF_MULTIPLIER),
	m_intSegCache(*(m_me.end()), *(m_me.begin()))	//looped segment as initial cached segment prevents null pointer crashes
{
}

template <class F>
inline
void base_CPoly<F>::setEffMultiplier(real_t effMultiplier)
{
	m_effMultiplier = effMultiplier;
}

template <class F>
inline
real_t base_CPoly<F>::effMultiplier() const
{
	return m_effMultiplier;
}

template <class F>
inline
bool base_CPoly<F>::vertexOnVEdge(const math::const_VectorPtr<2> & cvertex, real_t * first, real_t * second) const
{
	if ((second[0] == first[0]) && (cvertex[0] == first[0]))
		if (second[1] > first[1]) {
			if ((cvertex[1] < second[1]) && (cvertex[1] > first[1]))
				return true;
		} else {
			if ((cvertex[1] > second[1]) && (cvertex[1] < first[1]))
				return true;
		}
	return false;
}

template <class F>
inline
int base_CPoly<F>::testVertex(const math::const_VectorPtr<2> & cvertex, real_t * first, real_t * second) const
{
	if ((second[0] > first[0]) && (cvertex[0] >= first[0]) && (cvertex[0] < second[0]))
		return model::ccw<math::const_VectorPtr<2> >(first, second, cvertex);
	else // (second[0] <= first[0]) note that if (second[0] == first[0]) ccw won't be called
		if ((cvertex[0] <= first[0]) && (cvertex[0] > second[0]))
			return model::ccw<math::const_VectorPtr<2> >(first, second, cvertex);
	return 0;
}

template <class F>
inline
bool base_CPoly<F>::findIntersectingSeg(const model::const_Segment<2> & seg) const
{
	typename F::iterator i = m_me.begin();
	m_intSegCache.setFirst(*i);
	while (++i != m_me.end()) {
		m_intSegCache.setSecond(*i);
		if (model::intersect(seg, m_intSegCache))
			return true;
		m_intSegCache.setFirst(m_intSegCache.second());	//next iteration
	}
	m_intSegCache.setSecond(*(m_me.begin())); //looping segment
	if (model::intersect(seg, m_intSegCache))
		return true;
	return false;
}

//template <class F>
//inline
//void base_CPoly<F>::findNearest(const math::const_VectorPtr<2> & point) const
//{
//	typename F::iterator i = m_me.begin();
//	real_t minTr = model::const_Segment<2>(*i, point).vec().dot();
//	model::const_Segment<2> c(*i, *(++i));
//	m_intSegCache = c;
//	model::const_Segment<2> b(*i, point);
//	real_t bDot = b.vec().dot();
//	minTr += bDot;
//	minTr /= c.vec().dot();
//	while (i != m_me.end()) {
//		c.setPoints(*i, *(++i));
//		b.setFirst(*i);
//		//bDot becomes aDot in next iteration
//		real_t tr = bDot;
//		bDot = b.vec().dot();
//		tr += bDot;
//		tr /= c.vec().dot();
//		if (tr < minTr) {
//			minTr = tr;
//			m_intSegCache = c;
//		}
//	}
//	//looping segment
//	c.setPoints(*i, *(m_me.begin()));
//	b.setFirst(*(m_me.begin()));
//	if (bDot + b.vec().dot() / c.vec().dot())
//		m_intSegCache = c;
//}

template <class F>
const model::VertexData<2> & base_CPoly<F>::cvertices() const
{
	return m_me.vdata();
}

template <class F>
bool base_CPoly<F>::test(const math::const_VectorPtr<2> & cvertex) const
{
	real_t * first;
	real_t * second;
	int ccw = 0;

	typename F::iterator i = m_me.begin();
	first = *i;
	while (++i != m_me.end()) {
		second = *i;
		if (vertexOnVEdge(cvertex, first, second))
			return false;
		ccw += testVertex(cvertex, first, second);
		first = second;	//next iteration
	}
	second = *(m_me.begin()); //looping segment
	if (vertexOnVEdge(cvertex, first, second))
		return false;
	ccw += testVertex(cvertex, first, second);

	if (std::abs(ccw) >= 2)
		return true;
	else
		return false;
}

template <class F>
math::Vector<2> base_CPoly<F>::eff(const math::const_VectorPtr<2> & pre, const math::const_VectorPtr<2> & post) const
{
	model::const_Segment<2> cseg(pre, post);
	if (findIntersectingSeg(cseg)) {
		math::Vector<2> result = model::intersection(cseg.vec(), pre, m_intSegCache.vec(), m_intSegCache.firstVec());
		result += m_intSegCache.vec().orthoCW() * m_effMultiplier;
		#ifndef NDEBUG
			if (test(result))
				GPX_WARN("test() returned true, intersection point inside polygon");
			return result;
		#else
			return result;
		#endif /* NDEBUG */
	} else
		GPX_WARN("effective point doesn't exist for given collision points");
	return math::Vector<2>(pre);
}

template <class F>
math::Vector<2> base_CPoly<F>::normal(const CollisionPoints & ncPoints) const
{
	if (!model::intersect(model::const_Segment<2>(ncPoints.pre, ncPoints.post), m_intSegCache))
		if (!findIntersectingSeg(model::const_Segment<2>(ncPoints.pre, ncPoints.post))) {
			GPX_WARN("can't determine normal vector for given collision points: " << ncPoints.pre << ncPoints.post);
			return math::Vector<2>();
		}
	return m_intSegCache.vec().normalize().orthoCW();
}

template <class F>
ICPolyGroup::element_t base_CPoly<F>::elements() const
{
	return 1;
}

template <class F>
const ICPoly * base_CPoly<F>::element(element_t i) const
{
	return this;
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
inline
CPoly<INDEX>::CPoly(typename Parent::index_t * indices, std::size_t size, const model::VertexData<2> & vdata):
	Parent(indices, size, vdata)
{
}

template <model::index_t INDEX>
inline
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

#endif /* GPX_Phy2d_CPOLY_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
