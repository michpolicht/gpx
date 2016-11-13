#ifndef TESTS_HPP
#define TESTS_HPP

//#define GPX_X_MATH_BACKEND_HEADER "tnt_jama/backend.hpp"

#include <assert.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <typeinfo>
#include <cmath>

#define GPX_LOG_INIT_FUNC myLogInit
//#define GPX_LOG_INIT_FUNC gpx_log_initFuncCerrCout
//#define GPX_LOG_INIT_FUNC gpx_log_initFuncCout

//namespace gpx { namespace log { class Log; }}

#include <gpx/platform.hpp>
#include <gpx/math/constants.hpp>
#include <gpx/math/structures.hpp>

//#include <gpx/math/Solver.hpp>
#include <gpx/log.hpp>
//#include <gpx/math.hpp>

//#include <tnt_jama/jama_svd.h>

using namespace std;

inline
void myLogInit(gpx::log::Log * log)
{
	log->combinedStream().attachStream(std::cout);
}

bool silent = true;

template <typename T>
bool ape(T v1, T v2, const char * file = "", int line = -1, const char * func = "")
{
	GPX_UNUSED(file);

	T eps = 128.0 * 2048.0 * std::numeric_limits<T>::epsilon() * 0.5;
	int exp1, exp2;
	std::frexp(v1, & exp1);
	std::frexp(v2, & exp2);

	if (std::abs(v2 - v1) <= std::ldexp(eps, std::max(exp1, exp2))) {
		if (!silent) {
			cout << "OK: " << v1 << " == " << v2;
			if (line != -1)
				cout << " line: " << line << " function: " << func;
			cout << endl;
		}
		return true;
	} else {
		cerr << "Error: " << v1 << " != " << v2;
		if (line != -1)
			cerr << " line: " << line << " function: " << func;
		cerr << endl;
		return false;
	}
}

class TestStringStream : public ostringstream
{
	public:
		static bool Silent;

	public:
		ostringstream s;

	public:
		bool test(const char * teststr, const char * file = "", int line = -1, const char * func = "")
		{
			GPX_UNUSED(file);
			if (str() == teststr) {
				if (!Silent) {
					cout << "OK: " << str() << " == " << teststr;
					if (line != -1)
						cout << " line: " << line << " function: " << func;
					cout << endl;
				}
				str("");
				return true;
			} else {
				cerr << endl << "Error: " << str() << " != " << teststr;
				if (line != -1)
					cerr << " line: " << line << " function: " << func;
				cerr << endl;
				str("");
				return false;
			}
		}

		bool stest(const char * file = "", int line = -1, const char * func = "")
		{
			bool result = test(s.str().data(), file, line, func);
			s.str("");
			return result;
		}
};

bool TestStringStream::Silent = true;

#define A(V1, V2) (ape(V1, V2, __FILE__, __LINE__, __FUNCTION__))
#define STEST stest(__FILE__, __LINE__, __FUNCTION__)
#define TEST(TESTSTR) (test(TESTSTR, __FILE__, __LINE__, __FUNCTION__))

template <typename T>
T drand()
{
	T divisor;
	do {
		divisor = static_cast<T>(std::rand());
	} while (divisor == 0.0);
	T result = static_cast<T>(std::rand()) / divisor;
	if (std::rand() % 2)
		return result;
	else
		return -result;
}

template <typename T>
void rand5Coords(T * coords)
{
	T divisor;
	do {
		divisor = static_cast<T>(std::rand());
	} while (divisor == 0.0);
	for (int i = 0; i < 5; i++)
		coords[i] = static_cast<T>(std::rand()) / divisor;

	//random minus sign
	for (int i = 0; i < 5; i++)
		if (std::rand() % 2)
			coords[i] *= -1.0;
}

template <typename T>
void rand25Coords(T * coords)
{
	T divisor;
	do {
		divisor = static_cast<T>(std::rand());
	} while (divisor == 0.0);
	for (int i = 0; i < 25; i++)
		coords[i] = static_cast<T>(std::rand()) / divisor;

	//random minus sign
	for (int i = 0; i < 25; i++)
		if (std::rand() % 2)
			coords[i] *= -1.0;
}



//template <template <std::size_t, typename, bool DIMSPEC = true> class D_VECTORPTR, std::size_t N, typename T>
//void VectorPtrDynamicTest()
//{
//	typedef D_VECTORPTR<gpx::math::SIZE_DYNAMIC, T> DVPTR;

//	if (N > 5) {
//		cout << "Error: maximal N to perform VectorPtrDynamicTest() is: " << 5 << endl;
//		return;
//	}
//	cout << "VectorPtrDynamicTest: testing " << typeid(DVPTR).name() << " class type: " << typeid(T).name() << " size: " << N << endl;

//	T coords[5];

//	//setSize
//	{
//		DVPTR v(coords, N);
//		A(v.size() == N, true);
//		v.setSize(N + 1);
//		A(v.size() == N + 1, true);
//	}

//	{
//		gpx::math::Vector<N> v;
//		gpx::math::VectorPtr<N> vptr(v);
//		DVPTR dv(v);
//		A(dv.size() == N, true);
//		DVPTR dv2(vptr);
//		A(dv2.size() == N, true);
//	}

//	//setPtr
//	{
//		DVPTR v(coords, N);
//		T coords2[5];
//		rand5Coords(coords2);
//		v.setPtr(coords2);
//		for (std::size_t i = 0; i < N; i++)
//			A(v(i) == coords2[i], true);
//	}

//	//setPtr size
//	{
//		DVPTR v(coords, N);
//		T coords2[5];
//		rand5Coords(coords2);
//		std::size_t newSize = std::rand() % N;
//		v.setPtr(coords2, newSize);
//		for (std::size_t i = 0; i < newSize; i++)
//			A(v(i) == coords2[i], true);
//	}
//}




#endif // TESTS_HPP
