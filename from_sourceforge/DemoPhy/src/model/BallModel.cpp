#include <gpx/math/functions.hpp>

#include "BallModel.hpp"

BallModel::BallModel(double r):
	r(r),
	verindex(VERTEX_NUM)
{
	double da = 2 * gpx::math::PI / VERTEX_NUM;
	double a = 0.0;
	double sina;
	double cosa;

	for (int i = 0; i < VERTEX_NUM; i++) {
		gpx::math::sincos(a, sina, cosa);
		vertices[i * 2] = r * cosa;
		vertices[i * 2 + 1] = r * sina;
		a += da;

		verindex[i] = i;
	}
	cvertices.setData(vertices, VERTEX_NUM);
}

BallModel::~BallModel()
{
}
