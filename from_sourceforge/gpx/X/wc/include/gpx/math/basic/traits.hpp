#ifndef GPX_X_MATH_BASIC_TRAITS_HPP
#define GPX_X_MATH_BASIC_TRAITS_HPP

#include "../structures.hpp"

namespace gpx {
namespace math {
namespace basic {

template <std::size_t M, std::size_t N, typename T>
struct MatrixTraits
{
	static gpx::math::Matrix<M, N, T> MakeUninitializedMatrix(std::size_t rows, std::size_t cols)
	{
		GPX_UNUSED(rows);
		GPX_UNUSED(cols);
		return gpx::math::Matrix<M, N, T>(T(), 0, 0);
	}

	typedef gpx::math::Matrix<N - 1, N - 1> MatrixMinor;
};

template <typename T>
struct MatrixTraits<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>
{
	static gpx::math::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> MakeUninitializedMatrix(std::size_t rows, std::size_t cols)
	{
		gpx::math::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> m(T(), 0, 0, rows * cols);
		m.resize(rows, cols);
		return m;
	}

	typedef gpx::math::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC> MatrixMinor;
};

template <std::size_t N, typename T>
struct VectorTraits
{
	static gpx::math::Vector<N, T> MakeUninitializedVector(std::size_t size)
	{
		GPX_UNUSED(size);
		return gpx::math::Vector<N, T>(T(), 0);
	}
};

template <typename T>
struct VectorTraits<gpx::math::SIZE_DYNAMIC, T>
{
	static gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> MakeUninitializedVector(std::size_t size)
	{
		gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> v(T(), 0, size);
		v.resize(size);
		return v;
	}
};

}
}
}

#endif // FUNCTIONS_HPP
