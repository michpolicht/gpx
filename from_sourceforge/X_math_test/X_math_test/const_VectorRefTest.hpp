#ifndef CONST_VECTORREFTEST_HPP
#define CONST_VECTORREFTEST_HPP

template <template <std::size_t, typename> class CONST_VECTORREF, std::size_t DIM, typename T,
		  template <std::size_t, typename> class VECTOR,
		  template <std::size_t, typename> class VECTORREF,
		  template <std::size_t, std::size_t, typename> class MATRIX>
void const_VectorRefTest()
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
		cout << "Error: maximal DIM to perform const_VectorRefTest() is: " << 5 << endl;
		return;
	}
	cout << "const_VectorRefTest: testing " << typeid(CONST_VECTORREF<DIM, T>).name() << " class type: " << typeid(T).name() << " dimension: " << DIM << endl;

	//default ctor (forbidden)
//	CONST_VECTORREF<DIM, T> v;

	//array ctor
	{
		t << CONST_VECTORREF<DIM, T>(coords1);
		t.s << "[";
		for (std::size_t i = 0; i < DIM - 1; i++)
			t.s << "0, ";
		t.s << "0]" << endl;
		t.STEST;
	}

	//copy ctor
	{
		rand5Coords(coords2);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		t << CONST_VECTORREF<DIM, T>(const_vecRef);
		t.s << const_vecRef;
		t.STEST;
	}

	//from VectorRef
	{
		rand5Coords(coords2);
		VECTORREF<DIM, T> vecRef(coords2);
		t << CONST_VECTORREF<DIM, T>(vecRef);
		t.s << vecRef;
		t.STEST;
	}

	//from Vector
	{
		rand5Coords(coords2);
		VECTOR<DIM, T> vec(coords2);
		t << CONST_VECTORREF<DIM, T>(vec);
		t.s << vec;
		t.STEST;
	}

	//size
	{
		CONST_VECTORREF<DIM, T> vec(coords2);
		A(DIM == vec.size(), true);
	}

	//ptr const
	{
		CONST_VECTORREF<DIM, T> vec(coords2);
		const T * ptr = vec.ptr();
		for (std::size_t i = 0; i < DIM; i++)
			A(ptr[i], coords2[i]);
	}

//	//cast opreator std::size_t
////	t << "0x" << hex << static_cast<std::size_t>(CONST_VECTORREF<DIM, T>(coords2));
////	t.s << coords2;
////	t.STEST;

	//getters opreator []
	{
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		for (std::size_t i = 0; i < DIM; i++)
			A(const_vecRef[static_cast<int>(i)], coords2[i]);
	}

	//getters operator ()
	{
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		for (std::size_t i = 0; i < DIM; i++)
			A(const_vecRef(i), coords2[i]);
	}

	//getters coord
	{
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		for (std::size_t i = 0; i < DIM; i++)
			A(const_vecRef.coord(i), coords2[i]);
	}

	//operator ==
	{
		coords1[0] = coords2[0];
		coords1[1] = coords2[1];
		coords1[2] = coords2[2];
		coords1[3] = coords2[3];
		coords1[4] = coords2[4];
		t << (CONST_VECTORREF<DIM, T>(coords2) == CONST_VECTORREF<DIM, T>(coords1));
		do {
			T dr = drand<T>();
			while (dr == T())
				dr = drand<T>();
			coords1[std::rand() % DIM] += dr;
		} while (std::rand() % DIM);
		t << (CONST_VECTORREF<DIM, T>(coords2) == CONST_VECTORREF<DIM, T>(coords1));
		t.s << "10";
		t.STEST;
	}

//	//operator ==(val)
//	rand5Coords(coords2);
//	A((CONST_VECTORREF<DIM, T>(coords2) == (coords2[0] + 0.5)), false);
//	for (std::size_t i = 1; i < 5; i++)
//		coords2[i] = coords2[0];
//	A((CONST_VECTORREF<DIM, T>(coords2) == (coords2[0])), true);

	//operator !=
	{
		t << (CONST_VECTORREF<DIM, T>(coords2) != CONST_VECTORREF<DIM, T>(coords1));
		coords1[0] = coords2[0];
		coords1[1] = coords2[1];
		coords1[2] = coords2[2];
		coords1[3] = coords2[3];
		coords1[4] = coords2[4];
		t << (CONST_VECTORREF<DIM, T>(coords2) != CONST_VECTORREF<DIM, T>(coords1));
		t.s << "10";
		t.STEST;
	}

//	//operator !=(val)
//	rand5Coords(coords2);
//	A((CONST_VECTORREF<DIM, T>(coords2) != (coords2[0] + 0.5)), true);
//	for (std::size_t i = 1; i < 5; i++)
//		coords2[i] = coords2[0];
//	A((CONST_VECTORREF<DIM, T>(coords2) != (coords2[0])), false);

	//inverse()
	{
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		rand5Coords(coords2);
		VECTOR<DIM, T> invVec = const_vecRef.inverse();
		for (std::size_t i = 0; i < DIM; i++)
			A(invVec(i), -const_vecRef(i));
	}

	//operator - unary
	{
		rand5Coords(coords2);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		VECTOR<DIM, T> invVec2 = -const_vecRef;
		for (std::size_t i = 0; i < DIM; i++)
			A(invVec2(i), -coords2[i]);
	}

	//sum
	{
		rand5Coords(coords2);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		T coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = coords1[i] + coords2[i];
		VECTOR<DIM, T> vecSum = const_vecRef.sum(CONST_VECTORREF<DIM, T>(coords1));
		for (std::size_t i = 0; i < DIM; i++)
			A(vecSum(i), coords3[i]);
	}

	//operator +
	{
		rand5Coords(coords2);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		T coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = coords1[i] + coords2[i];
		VECTOR<DIM, T> vecSum2 = const_vecRef + CONST_VECTORREF<DIM, T>(coords1);
		for (std::size_t i = 0; i < DIM; i++)
			A(vecSum2(i), coords3[i]);
	}

	//diff
	{
		rand5Coords(coords2);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		T coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = coords2[i] - coords1[i];
		VECTOR<DIM, T> vecDiff = const_vecRef.diff(CONST_VECTORREF<DIM, T>(coords1));
		for (std::size_t i = 0; i < DIM; i++)
			A(vecDiff(i), coords3[i]);
	}

	//operator -
	{
		rand5Coords(coords2);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		T coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = coords2[i] - coords1[i];
		VECTOR<DIM, T> vecDiff2 = const_vecRef - CONST_VECTORREF<DIM, T>(coords1);
		for (std::size_t i = 0; i < DIM; i++)
			A(vecDiff2(i), coords3[i]);
	}

	//prod
	{
		rand5Coords(coords2);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		T coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = coords2[i] * coords1[0];
		VECTOR<DIM, T> vecProd = const_vecRef.prod(coords1[0]);
		for (std::size_t i = 0; i < DIM; i++)
			A(vecProd(i), coords3[i]);
	}

	//operator *
	{
		rand5Coords(coords2);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		T coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = coords2[i] * coords1[0];
		VECTOR<DIM, T> vecProd2 = const_vecRef * coords1[0];
		for (std::size_t i = 0; i < DIM; i++)
			A(vecProd2(i), coords3[i]);
	}

	//prod matrix
	{
		rand5Coords(coords1);
		MATRIX<DIM, DIM, T> m(static_cast<T>(1.0), DIM, DIM);
		CONST_VECTORREF<DIM, T> v(coords1);
		VECTOR<DIM, T> vc = v.prod(m);
		A(v.ape(vc), true);
		T mcoords[25];
		rand25Coords(mcoords);
		MATRIX<DIM, DIM, T> m2(mcoords, DIM, DIM);
		vc = v.prod(m2);
		A(v.ape(vc), false);
		MATRIX<DIM, DIM, T> m3(T(), DIM, DIM);
		vc = v.prod(m3);
		A(vc.isZero(), true);
	}

	//operator *= matrix
	{
		MATRIX<DIM, DIM, T> m(static_cast<T>(1.0), DIM, DIM);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> v(coords1);
		VECTOR<DIM, T> vc = v * m;
		A(v.ape(vc), true);
		T mcoords[25];
		rand25Coords(mcoords);
		MATRIX<DIM, DIM, T> m2(mcoords, DIM, DIM);
		vc = v * m2;
		A(v.ape(vc), false);
		MATRIX<DIM, DIM, T> m3(T(), DIM, DIM);
		vc = v * m3;
		A(vc.isZero(), true);
	}

	//quot
	{
		rand5Coords(coords2);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		T coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = coords2[i] / coords1[0];
		VECTOR<DIM, T> vecQuot = const_vecRef.quot(coords1[0]);
		for (std::size_t i = 0; i < DIM; i++)
			A(vecQuot(i), coords3[i]);
	}

	//operator /
	{
		rand5Coords(coords2);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		T coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = coords2[i] / coords1[0];
		VECTOR<DIM, T> vecQuot2 = const_vecRef / coords1[0];
		for (std::size_t i = 0; i < DIM; i++)
			A(vecQuot2(i), coords3[i]);
	}

	//dot
	{
		rand5Coords(coords2);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		T scalar = T();
		for (std::size_t i = 0; i < DIM; i++)
			scalar += coords2[i] * coords1[i];
		A(const_vecRef.dot(CONST_VECTORREF<DIM, T>(coords1)), scalar);
	}

	//dot 2
	{
		rand5Coords(coords2);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		T scalar = T();
		for (std::size_t i = 0; i < DIM; i++)
			scalar += coords2[i] * coords2[i];
		A(const_vecRef.dot(), scalar);
	}

	//length
	{
		rand5Coords(coords2);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		T scalar = T();
		for (std::size_t i = 0; i < DIM; i++)
			scalar += coords2[i] * coords2[i];
		scalar = std::sqrt(scalar);
		A(const_vecRef.length(), scalar);
	}

	//versor
	{
		rand5Coords(coords2);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		A(const_vecRef.versor().length(), static_cast<T>(1.0));
	}

	//det
	{
		rand5Coords(coords2);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		std::size_t cn1 = std::rand() % DIM;
		std::size_t cn2 = std::rand() % DIM;
		A(const_vecRef.det(CONST_VECTORREF<DIM, T>(coords1), cn1, cn2), (coords2[cn1] * coords1[cn2]) - (coords2[cn2] * coords1[cn1]));
	}

	//cross
	{
		T coords0[5];
		T coords3[5];
		rand5Coords(coords0);
		rand5Coords(coords1);
		rand5Coords(coords2);
		rand5Coords(coords3);
		CONST_VECTORREF<DIM, T> v0(coords0);
		gpx::math::const_VectorRef<DIM, T> v1(coords1);
		gpx::math::const_VectorRef<DIM, T> v2(coords2);
		gpx::math::const_VectorRef<DIM, T> v3(coords3);
		gpx::math::const_VectorRef<DIM, T> vArr[] = {v1, v2, v3};
		A(v0.cross(vArr).dot(v0), 0.0);
		for (int i = 0; i < static_cast<int>(DIM) - 2; i++)
			A(v0.cross(vArr).dot(vArr[i]), 0.0);
	}

	//ccross
	{
		T coords0[5];
		T coords3[5];
		rand5Coords(coords0);
		rand5Coords(coords1);
		rand5Coords(coords2);
		rand5Coords(coords3);
		CONST_VECTORREF<DIM, T> v0(coords0);
		gpx::math::const_VectorRef<DIM, T> v1(coords1);
		gpx::math::const_VectorRef<DIM, T> v2(coords2);
		gpx::math::const_VectorRef<DIM, T> v3(coords3);
		gpx::math::const_VectorRef<DIM, T> vArr[] = {v1, v2, v3};
		A(v0.ccross(vArr).dot(v0), 0.0);
		for (int i = 0; i < static_cast<int>(DIM) - 2; i++)
			A(v0.ccross(vArr).dot(vArr[i]), 0.0);
	}

//	//ape
//	{
//		T coords0[5];
//		rand5Coords(coords0);
//		for (int i = 0; i < 5; i++)
//			coords1[i] = coords0[i];
//		CONST_VECTORREF<DIM, T> v(coords0);
//		A(v.ape(CONST_VECTORREF<DIM, T>(coords0)), true);
//		std::size_t c = std::rand() % DIM;
//		coords0[c] += gpx::math::eps(coords0[c]);
//		A((*v == *CONST_VECTORREF<DIM, T>(coords1)), false);
//		A(v.ape(CONST_VECTORREF<DIM, T>(coords1)), true);
//		coords0[c] += 100.0 * gpx::math::eps(coords0[c]);
//		A(v.ape(CONST_VECTORREF<DIM, T>(coords1)), false);
//	}

//	//ape val
//	{
//		T val = drand<T>();
//		for (int i = 0; i < 5; i++)
//			coords1[i] = val;
//		CONST_VECTORREF<DIM, T> v0(coords1);
//		A(v0.ape(val), true);
//		for (int i = 0; i < 5; i++)
//			coords1[i] += gpx::math::eps(val);

//		A(v0 == val, false);
//		A(v0.ape(val), true);
//		for (int i = 0; i < 5; i++)
//			coords1[i] += 100.0 * gpx::math::eps(val);
//		A(v0.ape(val), false);
//	}

	//ale
	{
		T coords0[5];
		rand5Coords(coords0);
		for (int i = 0; i < 5; i++)
			coords1[i] = coords0[i];
		A((CONST_VECTORREF<DIM, T>(coords0)).ale(CONST_VECTORREF<DIM, T>(coords0)), true);
		std::size_t c = std::rand() % DIM;
		coords0[c] += gpx::math::eps(coords0[c]);
		A(((CONST_VECTORREF<DIM, T>(coords0)) == CONST_VECTORREF<DIM, T>(coords1)), false);
		A((CONST_VECTORREF<DIM, T>(coords0)).ale(CONST_VECTORREF<DIM, T>(coords1)), true);
		coords0[c] += 100.0 * gpx::math::eps(coords0[c]);
		A((CONST_VECTORREF<DIM, T>(coords0)).ale(CONST_VECTORREF<DIM, T>(coords1)), false);
	}

//	//ale val
//	{
//		T val = drand<T>();
//		for (int i = 0; i < 5; i++)
//			coords1[i] = val;
//		CONST_VECTORREF<DIM, T> v0(coords1);
//		A(v0.ale(val), true);
//		for (int i = 0; i < 5; i++)
//			coords1[i] += gpx::math::eps(val);

//		A(v0 == val, false);
//		A(v0.ale(val), true);
//		for (int i = 0; i < 5; i++)
//			coords1[i] += 100.0 * gpx::math::eps(val);
//		A(v0.ale(val), false);
//	}

	//isZero
	{
		rand5Coords(coords2);
		for (std::size_t i = 0; i < 5; i++)
			if (coords2[i] == T())
				coords2[i] = 0.5;
		A((CONST_VECTORREF<DIM, T>(coords2).isZero()), false);
		for (std::size_t i = 0; i < 5; i++)
			coords2[i] = T();
		A((CONST_VECTORREF<DIM, T>(coords2).isZero()), true);
	}

	//apeZero
	{
		T val = T();
		for (int i = 0; i < 5; i++)
			coords1[i] = val;
		A((CONST_VECTORREF<DIM, T>(coords1)).apeZero(), true);
		for (int i = 0; i < 5; i++)
			coords1[i] += gpx::math::eps(val);

		A((CONST_VECTORREF<DIM, T>(coords1)).isZero(), false);
		A((CONST_VECTORREF<DIM, T>(coords1)).apeZero(), true);
		for (int i = 0; i < 5; i++)
			coords1[i] += 100.0 * gpx::math::eps(val);
		A((CONST_VECTORREF<DIM, T>(coords1)).apeZero(), false);
	}

	//aleZero (isZero test performed because of sensitivity of ale function)
	{
		T val = T();
		for (int i = 0; i < 5; i++)
			coords1[i] = val;
		A((CONST_VECTORREF<DIM, T>(coords1)).aleZero(), true);
		for (int i = 0; i < 5; i++)
			coords1[i] += 100.0 * gpx::math::eps(val);
		A((CONST_VECTORREF<DIM, T>(coords1)).aleZero(), false);
	}

	//minimal
	{
		T coords0[5];
		rand5Coords(coords0);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> v0(coords1);
		CONST_VECTORREF<DIM, T> v1(coords1);
		VECTOR<DIM, T> vm = v0.minimal(v1);
		A(vm.versor().ape(v0.versor()), true);
		VECTOR<DIM, T> vp = v1 + vm;
		A((vp == v1), false);
	}

	//rotated sin cos
	{
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> v(coords1);
		std::size_t c1 = std::rand() % DIM;
		std::size_t c2 = std::rand() % DIM;
		gpx::real_t sin, cos;
		if (c1 != c2) {
			gpx::math::sincos(gpx::math::PI / 2, sin, cos);
			VECTOR<DIM, T> vec = v.rotated(sin, cos, c1, c2);
			A(vec.ape(v), false);
			gpx::math::sincos(2.0 * gpx::math::PI, sin, cos);
			vec = v.rotated(sin, cos, c1, c2);
			A(vec.ape(v), true);
		}
	}

	//rotated angle
	{
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> v(coords1);
		std::size_t c1 = std::rand() % DIM;
		std::size_t c2 = std::rand() % DIM;
		if (c1 != c2) {
			VECTOR<DIM, T> vec = v.rotated(gpx::math::PI / 2, c1, c2);
			A(vec.ape(v), false);
			vec = v.rotated(2.0 * gpx::math::PI, c1, c2);
			A(vec.ape(v), true);
		}
	}

//	//rotate angle point
//	{
//		rand5Coords(coords1);
//		CONST_VECTORREF<DIM, T> v(coords1);
//		std::size_t c1 = std::rand() % DIM;
//		std::size_t c2 = std::rand() % DIM;
//		if (c1 != c2) {
//			gpx::math::Vector<2, T> p;
//			p(0) = drand<T>();
//			p(1) = drand<T>();
//			VECTOR<DIM, T> vec = v.rotated(gpx::math::PI / 2, p, c1, c2);
//			A(vec.ape(v), false);
//			vec = v.rotated(2.0 * gpx::math::PI, p, c1, c2);
//			A(vec.ape(v), true);
//		}
//	}
}

template <template <std::size_t, typename> class CONST_VECTORREF, std::size_t DIM, typename T,
		  template <std::size_t, typename> class VECTOR,
		  template <std::size_t, typename> class VECTORREF>
void const_VectorRef2Test()
{
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

	if (DIM != 2) {
		cout << "Error: DIM to perform const_VectorRef2Test() is: " << 2 << endl;
		return;
	}
	cout << "const_VectorRef2Test: testing " << typeid(CONST_VECTORREF<DIM, T>).name() << " class type: " << typeid(T).name() << " dimension: " << DIM << endl;

	//get x y
	{
		CONST_VECTORREF<DIM, T> vptr(coords1);
		A(vptr.x() == c1, true);
		A(vptr.y() == c2, true);
	}

	//cross
	{
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> vptr(coords1);
		VECTOR<DIM, T> cv = vptr.cross();
		A(vptr.dot(cv), 0.0);
		A(cv.ape(vptr.rotated(-gpx::math::PI / 2.0)), true);
	}

	//cross
	{
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> vptr(coords1);
		VECTOR<DIM, T> cv = vptr.orthoCW();
		A(vptr.dot(cv), 0.0);
		A(cv.ape(vptr.rotated(-gpx::math::PI / 2.0)), true);
	}

	//ccross
	{
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> vptr(coords1);
		VECTOR<DIM, T> cv = vptr.ccross();
		A(vptr.dot(cv), 0.0);
		A(cv.ape(vptr.rotated(gpx::math::PI / 2.0)), true);
	}

	//ccross
	{
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> vptr(coords1);
		VECTOR<DIM, T> cv = vptr.orthoCCW();
		A(vptr.dot(cv), 0.0);
		A(cv.ape(vptr.rotated(gpx::math::PI / 2.0)), true);
	}

	//det
	{
		rand5Coords(coords1);
		rand5Coords(coords2);
		CONST_VECTORREF<DIM, T> vptr(coords1);
		CONST_VECTORREF<DIM, T> other(coords2);
		T a = vptr.det(other);
		T b = vptr.det(other, 0, 1);
		A(a == b, true);
	}

//	//sum xy
//	{
//		rand5Coords(coords1);
//		rand5Coords(coords2);
//		CONST_VECTORREF<DIM, T> vptr(coords1);
//		T coords3[DIM];
//		for (std::size_t i = 0; i < DIM; i++)
//			coords3[i] = coords1[i] + coords2[i];
//		VECTOR<DIM, T> vecSum = vptr.sum(coords2[0], coords2[1]);
//		for (std::size_t i = 0; i < DIM; i++)
//			A(vecSum(i), coords3[i]);
//	}

//	//dif xy
//	{
//		rand5Coords(coords1);
//		rand5Coords(coords2);
//		CONST_VECTORREF<DIM, T> vptr(coords1);
//		T coords3[DIM];
//		for (std::size_t i = 0; i < DIM; i++)
//			coords3[i] = coords1[i] - coords2[i];
//		VECTOR<DIM, T> vecDiff = vptr.diff(coords2[0], coords2[1]);
//		for (std::size_t i = 0; i < DIM; i++)
//			A(vecDiff(i), coords3[i]);
//	}

	//prod matrix 4 x 4
	{
		T mcoords[25];
		rand25Coords(mcoords);
		gpx::math::Matrix<4, 4, T> m(mcoords, 4, 4);
		CONST_VECTORREF<DIM, T> v(coords1);
		gpx::math::Vector<DIM, T> vc(coords1);
		vc *= m;
		gpx::math::Vector<DIM, T> vc2 = v.prod(m);
		A(vc2.ape(vc), true);
	}

	//operator * matrix 4 x 4
	{
		T mcoords[25];
		rand25Coords(mcoords);
		gpx::math::Matrix<4, 4, T> m(mcoords, 4, 4);
		CONST_VECTORREF<DIM, T> v(coords1);
		gpx::math::Vector<DIM, T> vc(coords1);
		vc *= m;
		gpx::math::Vector<DIM, T> vc2 = v * m;
		A(vc2.ape(vc), true);
	}

	//rotated sin cos
	{
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> v(coords1);
		gpx::real_t sin, cos;
		gpx::math::sincos(gpx::math::PI / 2, sin, cos);
		VECTOR<DIM, T> vec = v.rotated(sin, cos);
		A(vec.ape(v), false);
		gpx::math::sincos(2.0 * gpx::math::PI, sin, cos);
		vec = v.rotated(sin, cos);
		A(vec.ape(v), true);
	}

	//rotated angle
	{
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> v(coords1);
		VECTOR<DIM, T> vec = v.rotated(gpx::math::PI / 2);
		A(vec.ape(v), false);
		vec = v.rotated(2.0 * gpx::math::PI);
		A(vec.ape(v), true);
	}

	//rotated angle point
	{
		rand5Coords(coords1);
		VECTOR<DIM, T> point(coords1);
		rand5Coords(coords1);
		CONST_VECTORREF<DIM, T> v(coords1);
		VECTOR<DIM, T> vec = v.rotated(gpx::math::PI / 2, point);
		A(vec.ape(v), false);
		vec = v.rotated(2.0 * gpx::math::PI, point);
		A(vec.ape(v), true);
	}
}

//template <template <std::size_t, typename, bool DIMSPEC = true> class CONST_VECTORREF, std::size_t DIM, typename T,
//		  template <std::size_t, typename> class VECTOR,
//		  template <std::size_t, typename, bool DIMSPEC = true> class VECTORREF>
//void const_VectorRef3Test()
//{
//	const T cA = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
//	const T cB = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
//	const T cC = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
//	const T cD = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
//	const T cE = static_cast<T>(std::rand()) / static_cast<T>(std::rand());

//	const T c1 = 0.0;
//	const T c2 = 0.0;
//	const T c3 = 0.0;
//	const T c4 = 0.0;
//	const T c5 = 0.0;

//	T coords1[] = {c1, c2, c3, c4, c5};
//	T coords2[] = {cA, cB, cC, cD, cE};

//	if (DIM != 3) {
//		cout << "Error: DIM to perform const_VectorRef3Test() is: " << 3 << endl;
//		return;
//	}
//	cout << "const_VectorRef3Test: testing " << typeid(CONST_VECTORREF<DIM, T>).name() << " class type: " << typeid(T).name() << " dimension: " << DIM << endl;

//	//get x y z
//	{
//		CONST_VECTORREF<DIM, T> vptr(coords1);
//		A(vptr.x() == c1, true);
//		A(vptr.y() == c2, true);
//		A(vptr.z() == c3, true);
//	}

//	//cross
//	{
//		rand5Coords(coords1);
//		rand5Coords(coords2);
//		CONST_VECTORREF<DIM, T> vptr(coords1);
//		CONST_VECTORREF<DIM, T> vptr2(coords2);
//		VECTOR<DIM, T> vc = vptr.cross(vptr2);
//		A(vc.dot(vptr), 0.0);
//		A(vc.dot(vptr2), 0.0);
//	}

//	//ccross
//	{
//		rand5Coords(coords1);
//		rand5Coords(coords2);
//		CONST_VECTORREF<DIM, T> vptr(coords1);
//		CONST_VECTORREF<DIM, T> vptr2(coords2);
//		VECTOR<DIM, T> vc = vptr.ccross(vptr2);
//		A(vc.dot(vptr), 0.0);
//		A(vc.dot(vptr2), 0.0);
//	}

//	//sum xyz
//	{
//		rand5Coords(coords1);
//		rand5Coords(coords2);
//		CONST_VECTORREF<DIM, T> vptr(coords1);
//		T coords3[DIM];
//		for (std::size_t i = 0; i < DIM; i++)
//			coords3[i] = coords1[i] + coords2[i];
//		VECTOR<DIM, T> vecSum = vptr.sum(coords2[0], coords2[1], coords2[2]);
//		for (std::size_t i = 0; i < DIM; i++)
//			A(vecSum(i), coords3[i]);
//	}

//	//dif xyz
//	{
//		rand5Coords(coords1);
//		rand5Coords(coords2);
//		CONST_VECTORREF<DIM, T> vptr(coords1);
//		T coords3[DIM];
//		for (std::size_t i = 0; i < DIM; i++)
//			coords3[i] = coords1[i] - coords2[i];
//		VECTOR<DIM, T> vecDiff = vptr.diff(coords2[0], coords2[1], coords2[2]);
//		for (std::size_t i = 0; i < DIM; i++)
//			A(vecDiff(i), coords3[i]);
//	}

//	//prod matrix 4 x 4
//	{
//		T mcoords[25];
//		rand25Coords(mcoords);
//		gpx::math::Matrix<4, 4, T> m(mcoords, 4, 4);
//		CONST_VECTORREF<DIM, T> v(coords1);
//		gpx::math::Vector<DIM, T> vc(coords1);
//		vc *= m;
//		gpx::math::Vector<DIM, T> vc2 = v.prod(m);
//		A(vc2.ape(vc), true);
//	}

//	//operator * matrix 4 x 4
//	{
//		T mcoords[25];
//		rand25Coords(mcoords);
//		gpx::math::Matrix<4, 4, T> m(mcoords, 4, 4);
//		CONST_VECTORREF<DIM, T> v(coords1);
//		gpx::math::Vector<DIM, T> vc(coords1);
//		vc *= m;
//		gpx::math::Vector<DIM, T> vc2 = v * m;
//		A(vc2.ape(vc), true);
//	}

//	//rotated sin cos axis
//	{
//		rand5Coords(coords1);
//		CONST_VECTORREF<DIM, T> v(coords1);
//		std::size_t axis = std::rand() % DIM;
//		gpx::real_t sin, cos;
//		gpx::math::sincos(gpx::math::PI / 2, sin, cos);
//		VECTOR<DIM, T> vec = v.rotated(sin, cos, axis);
//		A(vec.ape(v), false);
//		gpx::math::sincos(2.0 * gpx::math::PI, sin, cos);
//		vec = v.rotated(sin, cos, axis);
//		A(vec.ape(v), true);
//	}

//	//rotated angle axis
//	{
//		rand5Coords(coords1);
//		CONST_VECTORREF<DIM, T> v(coords1);
//		std::size_t axis = std::rand() % DIM;
//		VECTOR<DIM, T> vec = v.rotated(gpx::math::PI / 2, axis);
//		A(vec.ape(v), false);
//		vec = v.rotated(2.0 * gpx::math::PI, axis);
//		A(vec.ape(v), true);
//	}
//}

//template <template <std::size_t, typename, bool DIMSPEC = true> class DCONST_VECTORPTR, std::size_t N, typename T>
//void const_VectorPtrDynamicTest()
//{
//	typedef DCONST_VECTORPTR<gpx::math::SIZE_DYNAMIC, T> DCVPTR;

//	if (N > 5) {
//		cout << "Error: maximal N to perform const_VectorPtrDynamicTest() is: " << 5 << endl;
//		return;
//	}
//	cout << "VectorPtrDynamicTest: testing " << typeid(DCVPTR).name() << " class type: " << typeid(T).name() << " size: " << N << endl;

//	T coords[5];

//	{
//		DCVPTR v(coords, N);
//		A(v.size() == N, true);
//		v.setSize(N + 1);
//		A(v.size() == N + 1, true);
//	}

//	{
//		gpx::math::Vector<N> v;
//		gpx::math::VectorPtr<N> vptr(v);
//		gpx::math::const_VectorPtr<N> cvptr(v);
//		DCVPTR dv(v);
//		A(dv.size() == N, true);
//		DCVPTR dv2(vptr);
//		A(dv2.size() == N, true);
//		DCVPTR dv3(cvptr);
//		A(dv3.size() == N, true);
//	}

//	//setPtr
//	{
//		DCVPTR v(coords, N);
//		T coords2[5];
//		rand5Coords(coords2);
//		v.setPtr(coords2);
//		for (std::size_t i = 0; i < N; i++)
//			A(v(i) == coords2[i], true);
//	}

//	//setPtr size
//	{
//		DCVPTR v(coords, N);
//		T coords2[5];
//		rand5Coords(coords2);
//		std::size_t newSize = std::rand() % N;
//		v.setPtr(coords2, newSize);
//		for (std::size_t i = 0; i < newSize; i++)
//			A(v(i) == coords2[i], true);
//	}
//}

template <std::size_t N, typename T> class DVectorWrapper;

template <std::size_t N, typename T>
class Dconst_VectorRefWrapper : public gpx::math::const_VectorRef<gpx::math::SIZE_DYNAMIC, T>
{
	typedef gpx::math::const_VectorRef<gpx::math::SIZE_DYNAMIC, T> Parent;

	public:
		Dconst_VectorRefWrapper(const gpx::math::const_VectorRef<gpx::math::SIZE_DYNAMIC, T> & other):
			Parent(other)
		{
		}

		Dconst_VectorRefWrapper(const gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> & other):
			Parent(other)
		{
		}

		Dconst_VectorRefWrapper(const T * coords):
			Parent(& m_dv),
			m_dv(coords)
		{
		}

//		template <std::size_t ON>
//		Dconst_VectorRefWrapper(const gpx::math::const_VectorRef<ON, T> & other):
//			Parent(other)
//		{
//		}

		DVectorWrapper<N, T> m_dv;
};

#endif // CONST_VECTORREFTEST_HPP
