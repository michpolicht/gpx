/**
 * @file
 * @brief Algebraic structures header. This file binds (const_)Vector* and Matrix* class definitions
 * from separate headers. Include this file rather than any other (const_)Vector*.h or Matrix*.h.
 */

#ifndef GPX_X_MATH_STRUCTURES_HPP_
#define GPX_X_MATH_STRUCTURES_HPP_

#include "../platform.hpp"
#include "../log.hpp"
#include "constants.hpp"

//forward declare classes, so that compiler won't bitch if it sees them in method declarations
namespace gpx { namespace math { template <std::size_t N = SIZE_DYNAMIC, typename T = real_t> class const_PointRef; }}
namespace gpx { namespace math { template <std::size_t N = SIZE_DYNAMIC, typename T = real_t> class PointRef; }}
namespace gpx { namespace math { template <std::size_t N = SIZE_DYNAMIC, typename T = real_t> class Point; }}
namespace gpx { namespace math { template <std::size_t N = SIZE_DYNAMIC, typename T = real_t> class const_VectorRef; }}
namespace gpx { namespace math { template <std::size_t N = SIZE_DYNAMIC, typename T = real_t> class VectorRef; }}
namespace gpx { namespace math { template <std::size_t N = SIZE_DYNAMIC, typename T = real_t> class Vector; }}
namespace gpx { namespace math { template <std::size_t M = SIZE_DYNAMIC, std::size_t N = SIZE_DYNAMIC, typename T = real_t> class const_MatrixRef; }}
namespace gpx { namespace math { template <std::size_t M = SIZE_DYNAMIC, std::size_t N = SIZE_DYNAMIC, typename T = real_t> class MatrixRef; }}
namespace gpx { namespace math { template <std::size_t M = SIZE_DYNAMIC, std::size_t N = SIZE_DYNAMIC, typename T = real_t> class Matrix; }}

#include "const_PointTrait.hpp"
#include "PointTrait.hpp"
#include "const_PointRef.hpp"
#include "PointRef.hpp"
#include "Point.hpp"
#include "PointPrint.hpp"

#include "const_VectorTrait.hpp"
#include "VectorTrait.hpp"
#include "const_VectorRef.hpp"
#include "VectorRef.hpp"
#include "Vector.hpp"
#include "VectorPrint.hpp"

#include "const_MatrixTrait.hpp"
#include "MatrixTrait.hpp"
#include "const_MatrixRef.hpp"
#include "MatrixRef.hpp"
#include "Matrix.hpp"
#include "MatrixPrint.hpp"

#endif /* GPX_X_MATH_STRUCTURES_HPP_ */
