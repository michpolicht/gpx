#include "tests.hpp"

template <template <std::size_t, typename> class VECTORREF, std::size_t DIM, typename T,
		  template <std::size_t, typename> class VECTOR,
		  template <std::size_t, typename> class CONST_VECTORREF>
void VectorRefTest()
{
	TestStringStream t;

	const T cA = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
	const T cB = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
	const T cC = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
	const T cD = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
	const T cE = static_cast<T>(std::rand()) / static_cast<T>(std::rand());

	const T c1 = 0.0;
	const T c2 = 0.0;
	const T c3 = 0.0;
	const T c4 = 0.0;
	const T c5 = 0.0;

	T coords1[] = {c1, c2, c3, c4, c5};
	T coords2[] = {cA, cB, cC, cD, cE};

	if (DIM > 5) {
		cout << "Error: maximal DIM to perform VectorRefTest() is: " << 5 << endl;
		return;
	}
	cout << "VectorRefTest: testing " << typeid(VECTORREF<DIM, T>).name() << " class type: " << typeid(T).name() << " dimension: " << DIM << endl;

	//default ctor forbidden
//	VECTORREF<DIM, T> v;

	//array ctor
	t << VECTORREF<DIM, T>(coords1);
	t.s << "(";
	for (std::size_t i = 0; i < DIM - 1; i++)
		t.s << "0, ";
	t.s << "0)" << endl;
	t.STEST;

	//copy ctor
	rand5Coords(coords2);
	VECTORREF<DIM, T> vecPtr(coords2);
	t << VECTORREF<DIM, T>(vecPtr);
	t.s << vecPtr;
	t.STEST;

	//from const_VectorRef; forbidden
//	rand5Coords(coords2);
//	gpx::math::CONST_VECTORREF<DIM, T> const_vecPtr(coords2);
//	t << VECTORREF<DIM, T>(const_vecPtr);
//	t.s << const_vecPtr;
//	t.STEST;

	//from Vector (via conversion operator)
	rand5Coords(coords2);
	VECTOR<DIM, T> vec(coords2);
	t << VECTORREF<DIM, T>(vec);
	t.s << vec;
	t.STEST;

	//ptr
	T * ptr = VECTORREF<DIM, T>(coords2).ptr();
	for (std::size_t i = 0; i < DIM; i++)
		A(ptr[i], coords2[i]);

	//assignment = array
	vecPtr = coords1;
	t << VECTORREF<DIM, T>(coords1);
	t.s << vecPtr;
	t.STEST;

//	//assignment = const_VectorRef
//	rand5Coords(coords2);
//	vecPtr = CONST_VECTORREF<DIM, T>(coords1);
//	t << vecPtr;
//	t.s << CONST_VECTORREF<DIM, T>(coords1);
//	t.STEST;

//	//assignment = Vector
//	rand5Coords(coords2);
//	vecPtr = VECTOR<DIM, T>(coords1);
//	t << vecPtr;
//	t.s << VECTOR<DIM, T>(coords1);
//	t.STEST;

//	//assignment = val
//	vecPtr = coords2[0];
//	for (std::size_t i; i < DIM; i++)
//		A(vecPtr(i), coords2[0]);

//	//setters operator []
//	rand5Coords(coords2);
//	for (std::size_t i = 0; i < DIM; i++) {
//		vecPtr[i] = coords1[i];
//		t << vecPtr[static_cast<int>(i)];
//		t.s << coords1[i];
//		t.STEST;
//	}

//	//setters operator ()
//	rand5Coords(coords2);
//	for (std::size_t i = 0; i < DIM; i++) {
//		vecPtr(i) = coords1[i];
//		t << vecPtr[static_cast<int>(i)];
//		t.s << coords1[i];
//		t.STEST;
//	}

//	//setters coord
//	rand5Coords(coords2);
//	for (std::size_t i = 0; i < DIM; i++) {
//		vecPtr.coord(i) = coords1[i];
//		t << vecPtr[static_cast<int>(i)];
//		t.s << coords1[i];
//		t.STEST;
//	}

//	//add
//	vecPtr = coords2;	//maybe vecPtr = Vector<>
//	rand5Coords(coords1);
//	double coords3[DIM];
//	for (std::size_t i = 0; i < DIM; i++)
//		coords3[i] = coords1[i] + coords2[i];
//	vecPtr.add(VECTORREF<DIM, T>(coords1));
//	for (std::size_t i = 0; i < DIM; i++) {
//		t << vecPtr(i);
//		t.s << coords3[i];
//		t.STEST;
//	}

//	//operator +=
//	vecPtr = coords2;	//maybe vecPtr = Vector<>
//	rand5Coords(coords1);
//	for (std::size_t i = 0; i < DIM; i++)
//		coords3[i] = coords1[i] + coords2[i];
//	vecPtr += VECTORREF<DIM, T>(coords1);
//	for (std::size_t i = 0; i < DIM; i++) {
//		t << vecPtr(i);
//		t.s << coords3[i];
//		t.STEST;
//	}

//	//sub
//	vecPtr = coords2;	//maybe vecPtr = Vector<>
//	rand5Coords(coords1);
//	for (std::size_t i = 0; i < DIM; i++)
//		coords3[i] = vecPtr(i) - coords1[i];
//	vecPtr.sub(VECTORREF<DIM, T>(coords1));
//	for (std::size_t i = 0; i < DIM; i++) {
//		t << vecPtr(i);
//		t.s << coords3[i];
//		t.STEST;
//	}

//	//operator -=
//	vecPtr = coords2;	//maybe vecPtr = Vector<>
//	rand5Coords(coords1);
//	for (std::size_t i = 0; i < DIM; i++)
//		coords3[i] = vecPtr(i) - coords1[i];
//	vecPtr -= VECTORREF<DIM, T>(coords1);
//	for (std::size_t i = 0; i < DIM; i++) {
//		t << vecPtr(i);
//		t.s << coords3[i];
//		t.STEST;
//	}

//	//mul
//	vecPtr = coords2;	//maybe vecPtr = Vector<>
//	rand5Coords(coords1);
//	for (std::size_t i = 0; i < DIM; i++)
//		coords3[i] = vecPtr(i) * coords1[0];
//	vecPtr.mul(coords1[0]);
//	for (std::size_t i = 0; i < DIM; i++) {
//		t << vecPtr(i);
//		t.s << coords3[i];
//		t.STEST;
//	}

//	//operator *=
//	vecPtr = coords2;	//maybe vecPtr = Vector<>
//	rand5Coords(coords1);
//	for (std::size_t i = 0; i < DIM; i++)
//		coords3[i] = vecPtr(i) * coords1[0];
//	vecPtr *= coords1[0];
//	for (std::size_t i = 0; i < DIM; i++) {
//		t << vecPtr(i);
//		t.s << coords3[i];
//		t.STEST;
//	}

//	//mul matrix
//	{
//		gpx::math::Matrix<DIM, DIM, T> m(static_cast<T>(1.0), DIM, DIM);
//		rand5Coords(coords1);
//		VECTORREF<DIM, T> v(coords1);
//		VECTOR<DIM, T> vc(coords1);
//		v.mul(m);
//		A(v.ape(vc), true);
//		T mcoords[25];
//		rand25Coords(mcoords);
//		gpx::math::Matrix<DIM, DIM, T> m2(mcoords, DIM, DIM);
//		v.mul(m2);
//		A(v.ape(vc), false);
//		gpx::math::Matrix<DIM, DIM, T> m3(T(), DIM, DIM);
//		v.mul(m3);
//		A(v == T(), true);
//	}

//	//operator *= matrix
//	{
//		gpx::math::Matrix<DIM, DIM, T> m(static_cast<T>(1.0), DIM, DIM);
//		rand5Coords(coords1);
//		VECTORREF<DIM, T> v(coords1);
//		VECTOR<DIM, T> vc(coords1);
//		v *= m;
//		A(v.ape(vc), true);
//		T mcoords[25];
//		rand25Coords(mcoords);
//		gpx::math::Matrix<DIM, DIM, T> m2(mcoords, DIM, DIM);
//		v *= m2;
//		A(v.ape(vc), false);
//		gpx::math::Matrix<DIM, DIM, T> m3(T(), DIM, DIM);
//		v *= m3;
//		A(v == T(), true);
//	}

//	//div
//	vecPtr = coords2;	//maybe vecPtr = Vector<>
//	rand5Coords(coords1);
//	for (std::size_t i = 0; i < DIM; i++)
//		coords3[i] = vecPtr(i) / coords1[0];
//	vecPtr.div(coords1[0]);
//	for (std::size_t i = 0; i < DIM; i++) {
//		t << vecPtr(i);
//		t.s << coords3[i];
//		t.STEST;
//	}

//	//operator /=
//	vecPtr = coords2;	//maybe vecPtr = Vector<>
//	rand5Coords(coords1);
//	for (std::size_t i = 0; i < DIM; i++)
//		coords3[i] = vecPtr(i) / coords1[0];
//	vecPtr /= coords1[0];
//	for (std::size_t i = 0; i < DIM; i++) {
//		t << vecPtr(i);
//		t.s << coords3[i];
//		t.STEST;
//	}

//	//zero
//	rand5Coords(coords2);
//	vecPtr.zero();
//	for (std::size_t i = 0; i < DIM; i++) {
//		t << vecPtr(i);
//		t.s << 0;
//		t.STEST;
//	}

//	//invert
//	rand5Coords(coords1);
//	vecPtr = coords1;
//	vecPtr.invert();
//	for (std::size_t i = 0; i < DIM; i++) {
//		t << vecPtr(i);
//		t.s << -coords1[i];
//		t.STEST;
//	}

//	//normalize
//	rand5Coords(coords1);
//	vecPtr = coords1;
//	vecPtr.normalize();
//	A(vecPtr.length(), static_cast<T>(1.0));

//	//rotate sin cos
//	{
//		rand5Coords(coords1);
//		vecPtr = coords1;
//		VECTOR<DIM, T> vec(coords1);
//		std::size_t c1 = std::rand() % DIM;
//		std::size_t c2 = std::rand() % DIM;
//		gpx::real_t sin, cos;
//		gpx::math::sincos(gpx::math::PI / 2, & sin, & cos);
//		if (c1 != c2) {
//			vecPtr.rotate(sin, cos, c1, c2);
//			A(vec.ape(vecPtr), false);
//			vecPtr.rotate(sin, cos, c1, c2);
//			vecPtr.rotate(sin, cos, c1, c2);
//			vecPtr.rotate(sin, cos, c1, c2);
//			A(vec.ape(vecPtr), true);
//		}
//	}

//	//rotate angle
//	{
//		rand5Coords(coords1);
//		vecPtr = coords1;
//		VECTOR<DIM, T> vec(coords1);
//		std::size_t c1 = std::rand() % DIM;
//		std::size_t c2 = std::rand() % DIM;
//		if (c1 != c2) {
//			vecPtr.rotate(gpx::math::PI / 2, c1, c2);
//			A(vec.ape(vecPtr), false);
//			vecPtr.rotate(gpx::math::PI / 2, c1, c2);
//			vecPtr.rotate(gpx::math::PI / 2, c1, c2);
//			vecPtr.rotate(gpx::math::PI / 2, c1, c2);
//			A(vec.ape(vecPtr), true);
//		}
//	}

//	//rotate angle point
//	{
//		rand5Coords(coords1);
//		vecPtr = coords1;
//		VECTOR<DIM, T> vec(coords1);
//		std::size_t c1 = std::rand() % DIM;
//		std::size_t c2 = std::rand() % DIM;
//		if (c1 != c2) {
//			gpx::math::Vector<2, T> p;
//			p(0) = drand<T>();
//			p(1) = drand<T>();
//			vecPtr.rotate(gpx::math::PI / 2, p, c1, c2);
//			A(vec.ape(vecPtr), false);
//			vecPtr.rotate(gpx::math::PI / 2, p, c1, c2);
//			vecPtr.rotate(gpx::math::PI / 2, p, c1, c2);
//			vecPtr.rotate(gpx::math::PI / 2, p, c1, c2);
//			A(vec.ape(vecPtr), true);
//		}
//	}

//	//minimize
//	{
//		T coords0[5];
//		rand5Coords(coords0);
//		rand5Coords(coords1);
//		VECTORREF<DIM, T> v0(coords1);
//		VECTORREF<DIM, T> v1(coords1);
//		VECTOR<DIM, T> vorg(v0);
//		v0.minimize(v1);
//		A(vorg.versor().ape(v0.versor()), true);
//		VECTOR<DIM, T> vp = v1 + v0;
//		A((vp == v1), false);
//	}

//	//swap
//	{
//		T coords0[5];
//		rand5Coords(coords0);
//		VECTORREF<DIM, T> v0(coords0);
//		VECTORREF<DIM, T> v1(coords1);
//		v1 = v0;
//		std::size_t c1 = std::rand() % DIM;
//		std::size_t c2 = std::rand() % DIM;
//		v0.swap(c1, c2);
//		A((v0(c1) == v1(c2)), true);
//	}
}

//template <template <std::size_t, typename, bool DIMSPEC = true> class VECTORREF, std::size_t DIM, typename T,
//		  template <std::size_t, typename> class VECTOR,
//		  template <std::size_t, typename, bool DIMSPEC = true> class CONST_VECTORREF>
//void VectorRef2Test()
//{
//	const T cA = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
//	const T cB = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
////	const T cC = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
////	const T cD = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
////	const T cE = static_cast<T>(std::rand()) / static_cast<T>(std::rand());

//	const T c1 = 0.0;
//	const T c2 = 0.0;
//	const T c3 = 0.0;
//	const T c4 = 0.0;
//	const T c5 = 0.0;

//	T coords1[] = {c1, c2, c3, c4, c5};

//	if (DIM != 2) {
//		cout << "Error: DIM to perform VECTORREF3Test() is: " << 2 << endl;
//		return;
//	}
//	cout << "VECTORREF2Test: testing " << typeid(VECTORREF<DIM, T>).name() << " class type: " << typeid(T).name() << " dimension: " << DIM << endl;

//	//set x y
//	{
//		VECTORREF<DIM, T> vptr(coords1);
//		vptr.setX(cA);
//		A(cA == coords1[0], true);
//		vptr.setY(cB);
//		A(cB == coords1[1], true);
//		vptr.set(T(), T());
//		A(vptr == T(), true);
//	}

//	//add xy
//	{
//		for (int i = 0; i < 5; i++)
//			coords1[i] = T();
//		VECTORREF<DIM, T> vptr(coords1);
//		vptr.add(cA, cB);
//		A(vptr[0] == cA, true);
//		A(vptr[1] == cB, true);
//	}

//	//sub xy
//	{
//		for (int i = 0; i < 5; i++)
//			coords1[i] = T();
//		VECTORREF<DIM, T> vptr(coords1);
//		vptr.add(cA, cB);
//		vptr.sub(cA, cB);
//		A(vptr == T(), true);
//	}

//	//rotate sin cos
//	{
//		rand5Coords(coords1);
//		VECTORREF<DIM, T> vptr(coords1);
//		VECTOR<DIM, T> vec(coords1);
//		gpx::real_t sin, cos;
//		gpx::math::sincos(gpx::math::PI / 2, & sin, & cos);
//		vptr.rotate(sin, cos);
//		A(vec.ape(vptr), false);
//		vptr.rotate(sin, cos);
//		vptr.rotate(sin, cos);
//		vptr.rotate(sin, cos);
//		A(vec.ape(vptr), true);
//	}

//	//rotate angle
//	{
//		rand5Coords(coords1);
//		VECTORREF<DIM, T> vptr(coords1);
//		VECTOR<DIM, T> vec(coords1);
//		T angle = static_cast<T>(gpx::math::PI / 2);
//		vptr.rotate(angle);
//		A(vec.ape(vptr), false);
//		vptr.rotate(angle);
//		vptr.rotate(angle);
//		vptr.rotate(angle);
//		A(vec.ape(vptr), true);
//	}

//	//rotate angle point
//	{
//		rand5Coords(coords1);
//		VECTOR<DIM, T> point(coords1);
//		rand5Coords(coords1);
//		VECTORREF<DIM, T> vptr(coords1);
//		VECTOR<DIM, T> vec(coords1);
//		T angle = static_cast<T>(gpx::math::PI / 2);
//		vptr.rotate(angle, point);
//		A(vec.ape(vptr), false);
//		vptr.rotate(angle, point);
//		vptr.rotate(angle, point);
//		vptr.rotate(angle, point);
//		A(vec.ape(vptr), true);
//	}

//	//mul matrix 4 x 4
//	{
//		T mcoords[25];
//		rand25Coords(mcoords);
//		gpx::math::Matrix<4, 4, T> m(mcoords, 4, 4);
//		VECTORREF<DIM, T> v(coords1);
//		gpx::math::Vector<4, T> vc(coords1);
//		vc(2) = static_cast<T>(0.0);
//		vc(3) = static_cast<T>(1.0);
//		v.mul(m);
//		vc.mul(m);
//		for(std::size_t i = 0; i < DIM; i++)
//			A(v(i), vc(i));
//	}

//	//operator *= matrix 4 x 4
//	{
//		T mcoords[25];
//		rand25Coords(mcoords);
//		gpx::math::Matrix<4, 4, T> m(mcoords, 4, 4);
//		VECTORREF<DIM, T> v(coords1);
//		gpx::math::Vector<4, T> vc(coords1);
//		vc(2) = static_cast<T>(0.0);
//		vc(3) = static_cast<T>(1.0);
//		v *= m;
//		vc *= m;
//		for(std::size_t i = 0; i < DIM; i++)
//			A(v(i), vc(i));
//	}
//}

//template <template <std::size_t, typename, bool DIMSPEC = true> class VECTORREF, std::size_t DIM, typename T,
//		  template <std::size_t, typename> class VECTOR,
//		  template <std::size_t, typename, bool DIMSPEC = true> class CONST_VECTORREF>
//void VectorRef3Test()
//{
//	const T cA = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
//	const T cB = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
//	const T cC = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
////	const T cD = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
////	const T cE = static_cast<T>(std::rand()) / static_cast<T>(std::rand());

//	const T c1 = 0.0;
//	const T c2 = 0.0;
//	const T c3 = 0.0;
//	const T c4 = 0.0;
//	const T c5 = 0.0;

//	T coords1[] = {c1, c2, c3, c4, c5};

//	if (DIM != 3) {
//		cout << "Error: DIM to perform VectorPtr3Test() is: " << 3 << endl;
//		return;
//	}
//	cout << "VectorPtr3Test: testing " << typeid(VECTORREF<DIM, T>).name() << " class type: " << typeid(T).name() << " dimension: " << DIM << endl;

//	//set x y z
//	{
//		VECTORREF<DIM, T> vptr(coords1);
//		vptr.setX(cA);
//		A(cA == coords1[0], true);
//		vptr.setY(cB);
//		A(cB == coords1[1], true);
//		vptr.setZ(cC);
//		A(cC == coords1[2], true);
//		vptr.set(T(), T(), T());
//		A(vptr == T(), true);
//	}

//	//add xyz
//	{
//		for (int i = 0; i < 5; i++)
//			coords1[i] = T();
//		VECTORREF<DIM, T> vptr(coords1);
//		vptr.add(cA, cB, cC);
//		A(vptr[0] == cA, true);
//		A(vptr[1] == cB, true);
//		A(vptr[2] == cC, true);
//	}

//	//sub xyz
//	{
//		for (int i = 0; i < 5; i++)
//			coords1[i] = T();
//		VECTORREF<DIM, T> vptr(coords1);
//		vptr.add(cA, cB, cC);
//		vptr.sub(cA, cB, cC);
//		A(vptr == T(), true);
//	}

//	//rotate sin cos axis
//	{
//		rand5Coords(coords1);
//		VECTORREF<DIM, T> vptr(coords1);
//		VECTOR<DIM, T> vec(coords1);
//		std::size_t axis = std::rand() % DIM;
//		gpx::real_t sin, cos;
//		gpx::math::sincos(gpx::math::PI / 2, & sin, & cos);
//		vptr.rotate(sin, cos, axis);
//		A(vec.ape(vptr), false);
//		vptr.rotate(sin, cos, axis);
//		vptr.rotate(sin, cos, axis);
//		vptr.rotate(sin, cos, axis);
//		A(vec.ape(vptr), true);
//	}

//	//rotate angle axis
//	{
//		rand5Coords(coords1);
//		VECTORREF<DIM, T> vptr(coords1);
//		VECTOR<DIM, T> vec(coords1);
//		std::size_t axis = std::rand() % DIM;
//		T angle = static_cast<T>(gpx::math::PI / 2);
//		vptr.rotate(angle, axis);
//		A(vec.ape(vptr), false);
//		vptr.rotate(angle, axis);
//		vptr.rotate(angle, axis);
//		vptr.rotate(angle, axis);
//		A(vec.ape(vptr), true);
//	}

//	//mul matrix 4 x 4
//	{
//		T mcoords[25];
//		rand25Coords(mcoords);
//		gpx::math::Matrix<4, 4, T> m(mcoords, 4, 4);
//		VECTORREF<DIM, T> v(coords1);
//		gpx::math::Vector<4, T> vc(coords1);
//		vc(3) = static_cast<T>(1.0);
//		v.mul(m);
//		vc.mul(m);
//		for(std::size_t i = 0; i < DIM; i++)
//			A(v(i), vc(i));
//	}

//	//operator *= matrix 4 x 4
//	{
//		T mcoords[25];
//		rand25Coords(mcoords);
//		gpx::math::Matrix<4, 4, T> m(mcoords, 4, 4);
//		VECTORREF<DIM, T> v(coords1);
//		gpx::math::Vector<4, T> vc(coords1);
//		vc(3) = static_cast<T>(1.0);
//		v *= m;
//		vc *= m;
//		for(std::size_t i = 0; i < DIM; i++)
//			A(v(i), vc(i));
//	}
//}
