/**
 * @file
 * @brief .
 */

#ifndef GPX_X_MODEL_FUNCTIONS_HPP_
#define GPX_X_MODEL_FUNCTIONS_HPP_

#include "const_SegmentPtr.hpp"
#include "VertexData.hpp"

namespace gpx {
namespace model {

/**
 * Check orientation of triangle ABC. This function checks orientation of triangle
 * on the plane (considering two first coordinates of given vertices).
 * @param A triangle's first vertex.
 * @param B triangle's second vertex.
 * @param C triangle's third vertex.
 * @return 1 if curve is positively (or counterclockwise) oriented, -1 if curve is
 * negatively (or clockwise) oriented. When curve is non-orientable
 * (points are collinear) function returns 0.
 */
inline
int ccw(math::const_PointRef<2> A, math::const_PointRef<2> B, math::const_PointRef<2> C)
{
	real_t ccw = ((C[1] - A[1]) * (B[0] - A[0])) - ((B[1] - A[1]) * (C[0] - A[0]));
	return ccw > 0.0 ? 1 : ccw < 0.0 ? -1 : 0;
}

/**
 *  Check whenever two segments intersect (including endpoints).
 *  @param AB first segment.
 *  @param CD second segment.
 *  @return @p true when two segments intersect, @p false otherwise.
 */
inline
bool intersect(const_SegmentPtr<2> AB, const_SegmentPtr<2> CD)
{
	return ccw(AB->first(), CD->first() , CD->second()) != ccw(AB->second(), CD->first(), CD->second())
		&& ccw(AB->first(), AB->second(), CD->first()) != ccw(AB->first(), AB->second(), CD->second());
}

/**
 *  Check whenever two segments intersect (excluding endpoints).
 *  @param AB first segment.
 *  @param CD second segment.
 *  @return @p true when two segments intersect, @p false otherwise.
 */
inline
bool xintersect(const_SegmentPtr<2> AB, const_SegmentPtr<2> CD)
{
	return ccw(AB->first(), CD->first() , CD->second()) == -ccw(AB->second(), CD->first(), CD->second())
		&& ccw(AB->first(), AB->second(), CD->first()) == -ccw(AB->first(), AB->second(), CD->second());
}

/**
 * Calculate intersection point. Calculates intersection point of two lines. Lines are
 * given in form at + b, where @a t is an independent parametric variable, @a a is a slope
 * and b is an initial point.
 * @param a1 slope of the first line.
 * @param b1 initial point of the first line.
 * @param a2 slope of the second line.
 * @param b2 initial point of the second line.
 * @return intersection point. If no intersection point exists result is undefined.
 *
 * @todo remove.
 */
inline
math::Point<2> intersection(math::const_VectorRef<2> a1, math::const_PointRef<2> b1,
							math::const_VectorRef<2> a2, math::const_PointRef<2> b2)
{
	//solving equations:
	//a1(0) s - a2(0) t = b2(0) - b1(0)
	//a1(1) s - a2(1) t = b2(1) - b1(1)
	//this is basic implementation, using Cramer's rules.
	//@todo possibly find better algorithm.

	real_t det = (a1[1] * a2[0]) - (a1[0] * a2[1]);

	//it doesn't matter if s or t is used (this redundancy of information gives a premise that better algorithm may exist)
	real_t detS = ((b2[1] - b1[1]) * a2[0]) - ((b2[0] - b1[0]) * a2[1]);
//	real_t detT = ((b2[1] - b1[1]) * a1[0]) - ((b2[0] - b1[0]) * a1[1]);
	real_t s = detS/det;
//	real_t t = detT/det;
//	std::cout << "intersection() s: (" << a1[0] * s + b1[0] << ", " << a1[1] * s + b1[1] << ")" << std::endl;
//	std::cout << "intersection() t: (" << a2[0] * t + b2[0] << ", " << a2[1] * t + b2[1] << ")" << std::endl;
	return math::Point<2>(a1[0] * s + b1[0], a1[1] * s + b1[1]);
}

/**
 * Calculate intersection point. Calculates intersection point of two lines. Lines are
 * defined by line segments @a AB, @a CD. If lines are parallel or coincide result is
 * undefined.
 * @param AB first segment.
 * @param CD second segment.
 * @return intersection point. If no intersection point exists result is undefined.
 */
inline
math::Point<2> intersection(const_SegmentPtr<2> AB, const_SegmentPtr<2> CD)
{
	//algorithm is taken from http://mathworld.wolfram.com/Line-LineIntersection.html
	//and Wikipedia http://en.wikipedia.org/wiki/Line-line_intersection

	real_t M = ((AB->first(0) - AB->second(0)) * (CD->first(1) - CD->second(1))) - ((AB->first(1) - AB->second(1)) * (CD->first(0) - CD->second(0)));
	real_t AdetB = math::const_VectorRef<2>(AB->first().ptr()).det(AB->second().ptr());
	real_t CdetD = math::const_VectorRef<2>(CD->first().ptr()).det(CD->second().ptr());
	real_t Lx = (AdetB * (CD->first(0) - CD->second(0))) - ((AB->first(0) - AB->second(0)) * CdetD);
	real_t Ly = (AdetB * (CD->first(1) - CD->second(1))) - ((AB->first(1) - AB->second(1)) * CdetD);
	return math::Point<2>(Lx / M, Ly / M);
}

/**
 * Calculate distance between point and line coming through two points, defined by a segment.
 * Algorithm is taken from Wolfram MathWorld, which quotes Kimberling 1998, p. 31.
 * @param point point from which distance should be calculated.
 * @param line line to which distance should be calculated.
 */
inline
real_t distance(math::const_PointRef<2> point, const_SegmentPtr<2> line)
{
	//algorthm taken from Wolfram MathWorld, which quotes Kimberling 1998, p. 31
	math::Vector<2> v = line->second() - line->first(); //v = line.second - line.first
	return std::fabs((point[0] - line->first(0)) * (v[1]) - (point[1] - line->first(1)) * (v[0])) / v.length();
}

/**
 * Calculate squared distance between point and line coming through two points, defined by a
 * segment. This function can be slightly faster than distance(), because it doesn't
 * use square root to obtain distance.
 * @param point point from which distance should be calculated.
 * @param line line to which distance should be calculated.
 */
inline
real_t sqdistance(math::const_PointRef<2> point, const_SegmentPtr<2> line)
{
	math::Vector<2> v = line->second() - line->first(); //v = line.second - line.first
	//determinant |point - line.first , v|
	real_t det = (point[0] - line->first(0)) * (v[1]) - (point[1] - line->first(1)) * (v[0]);
	return det * det / v.dot();
}

/**
 * Find squared bounding radius for given set of vertices.
 * @param vdata set of vertices.
 * @return bounding radius.
 */
template <std::size_t DIM, typename T>
real_t sqboundr(const VertexData<DIM, T> & vdata)
{
	real_t sqBoundR = 0.0;
	for (typename VertexData<DIM, T>::const_iterator vertIt = vdata.begin(); vertIt != vdata.end(); ++vertIt) {
		math::const_VectorRef<DIM, T> r(*vertIt);
		sqBoundR = std::max(sqBoundR, r.dot());
	}
	return sqBoundR;
}

/**
 * Find bounding radius for given set of vertices.
 * @param vdata set of vertices.
 * @return bounding radius.
 */
template <std::size_t DIM, typename T>
real_t boundr(const VertexData<DIM, T> & vdata)
{
	return std::sqrt(sqboundr(vdata));
}

}
}

#endif /* GPX_X_MODEL_FUNCTIONS_HPP_ */
