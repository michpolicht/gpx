#ifndef VECTORREFTEST_HPP
#define VECTORREFTEST_HPP

template <template <std::size_t, typename> class VECTORREF, std::size_t DIM, typename T,
		  template <std::size_t, typename> class VECTOR,
		  template <std::size_t, typename> class CONST_VECTORREF,
		  template <std::size_t, std::size_t, typename, bool = true> class MATRIX>
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
	{
		t << VECTORREF<DIM, T>(coords1);
		t.s << "[";
		for (std::size_t i = 0; i < DIM - 1; i++)
			t.s << "0, ";
		t.s << "0]" << endl;
		t.STEST;
	}

	//copy ctor
	{
		rand5Coords(coords2);
		VECTORREF<DIM, T> vecRef(coords2);
		t << VECTORREF<DIM, T>(vecRef);
		t.s << vecRef;
		t.STEST;
	}

	//from const_VectorRef; forbidden
//	rand5Coords(coords2);
//	gpx::math::CONST_VECTORREF<DIM, T> const_vecRef(coords2);
//	t << VECTORREF<DIM, T>(const_vecRef);
//	t.s << const_vecRef;
//	t.STEST;

	//from Vector (via conversion operator)
	{
		rand5Coords(coords2);
		VECTOR<DIM, T> vec(coords2);
		t << VECTORREF<DIM, T>(vec);
		t.s << vec;
		t.STEST;
	}

	//ptr
	{
		VECTORREF<DIM, T> vref(coords2);
		T * ptr = vref.ptr();
		for (std::size_t i = 0; i < DIM; i++)
			A(ptr[i], coords2[i]);
	}

	//assignment = array
	{
		VECTORREF<DIM, T> vecRef(coords2);
		vecRef = coords1;
		A(vecRef.ptr() == coords1, false);	//should copy values from coords1, not set pointer
		t << VECTORREF<DIM, T>(coords1);
		t.s << vecRef;
		t.STEST;
	}

	//assignment = const_VectorRef
	{
		VECTORREF<DIM, T> vecRef(coords2);
		rand5Coords(coords2);
		vecRef = CONST_VECTORREF<DIM, T>(coords1);
		A(vecRef.ptr() == coords1, false);	//should copy values from coords1, not set pointer
		t << vecRef;
		t.s << CONST_VECTORREF<DIM, T>(coords1);
		t.STEST;
	}

	//assignment = Vector
	{
		VECTORREF<DIM, T> vecRef(coords2);
		rand5Coords(coords2);
		vecRef = VECTOR<DIM, T>(coords1);
		A(vecRef.ptr() == coords1, false);	//should copy values from coords1, not set pointer
		t << vecRef;
		t.s << VECTOR<DIM, T>(coords1);
		t.STEST;
	}

//	//assignment = val
//	vecRef = coords2[0];
//	for (std::size_t i; i < DIM; i++)
//		A(vecRef(i), coords2[0]);

	//setters operator []
	{
		VECTORREF<DIM, T> vecRef(coords2);
		rand5Coords(coords2);
		for (std::size_t i = 0; i < DIM; i++) {
			vecRef[i] = coords1[i];
			t << vecRef[static_cast<int>(i)];
			t.s << coords1[i];
			t.STEST;
		}
	}

	//setters operator ()
	{
		VECTORREF<DIM, T> vecRef(coords2);
		rand5Coords(coords2);
		for (std::size_t i = 0; i < DIM; i++) {
			vecRef(i) = coords1[i];
			t << vecRef[static_cast<int>(i)];
			t.s << coords1[i];
			t.STEST;
		}
	}

	//setters coord
	{
		VECTORREF<DIM, T> vecRef(coords2);
		rand5Coords(coords2);
		for (std::size_t i = 0; i < DIM; i++) {
			vecRef.coord(i) = coords1[i];
			t << vecRef[static_cast<int>(i)];
			t.s << coords1[i];
			t.STEST;
		}
	}

	//add
	{
		VECTORREF<DIM, T> vecRef(coords2);
		vecRef = coords2;	//maybe vecRef = Vector<>
		rand5Coords(coords1);
		double coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = coords1[i] + coords2[i];
		vecRef.add(VECTORREF<DIM, T>(coords1));
		for (std::size_t i = 0; i < DIM; i++) {
			t << vecRef(i);
			t.s << coords3[i];
			t.STEST;
		}
	}

	//operator +=
	{
		VECTORREF<DIM, T> vecRef(coords2);
		vecRef = coords2;	//maybe vecRef = Vector<>
		rand5Coords(coords1);
		double coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = coords1[i] + coords2[i];
		vecRef += VECTORREF<DIM, T>(coords1);
		for (std::size_t i = 0; i < DIM; i++) {
			t << vecRef(i);
			t.s << coords3[i];
			t.STEST;
		}
	}

	//sub
	{
		VECTORREF<DIM, T> vecRef(coords2);
		vecRef = coords2;	//maybe vecRef = Vector<>
		rand5Coords(coords1);
		double coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = vecRef(i) - coords1[i];
		vecRef.sub(VECTORREF<DIM, T>(coords1));
		for (std::size_t i = 0; i < DIM; i++) {
			t << vecRef(i);
			t.s << coords3[i];
			t.STEST;
		}
	}

	//operator -=
	{
		VECTORREF<DIM, T> vecRef(coords2);
		vecRef = coords2;	//maybe vecRef = Vector<>
		rand5Coords(coords1);
		double coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = vecRef(i) - coords1[i];
		vecRef -= VECTORREF<DIM, T>(coords1);
		for (std::size_t i = 0; i < DIM; i++) {
			t << vecRef(i);
			t.s << coords3[i];
			t.STEST;
		}
	}

	//mul
	{
		VECTORREF<DIM, T> vecRef(coords2);
		vecRef = coords2;	//maybe vecRef = Vector<>
		rand5Coords(coords1);
		double coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = vecRef(i) * coords1[0];
		vecRef.mul(coords1[0]);
		for (std::size_t i = 0; i < DIM; i++) {
			t << vecRef(i);
			t.s << coords3[i];
			t.STEST;
		}
	}

	//operator *=
	{
		VECTORREF<DIM, T> vecRef(coords2);
		vecRef = coords2;	//maybe vecRef = Vector<>
		rand5Coords(coords1);
		double coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = vecRef(i) * coords1[0];
		vecRef *= coords1[0];
		for (std::size_t i = 0; i < DIM; i++) {
			t << vecRef(i);
			t.s << coords3[i];
			t.STEST;
		}
	}

	//mul matrix
	{
		MATRIX<DIM, DIM, T> m(static_cast<T>(1.0), DIM, DIM);
		rand5Coords(coords1);
		VECTORREF<DIM, T> v(coords1);
		VECTOR<DIM, T> vc(coords1);
		v.mul(m);
		A(v.ape(vc), true);
		T mcoords[25];
		rand25Coords(mcoords);
		MATRIX<DIM, DIM, T> m2(mcoords, DIM, DIM);
		v.mul(m2);
		A(v.ape(vc), false);
		MATRIX<DIM, DIM, T> m3(T(), DIM, DIM);
		v.mul(m3);
		A(v.isZero(), true);
	}

	//operator *= matrix
	{
		MATRIX<DIM, DIM, T> m(static_cast<T>(1.0), DIM, DIM);
		rand5Coords(coords1);
		VECTORREF<DIM, T> v(coords1);
		VECTOR<DIM, T> vc(coords1);
		v *= m;
		A(v.ape(vc), true);
		T mcoords[25];
		rand25Coords(mcoords);
		MATRIX<DIM, DIM, T> m2(mcoords, DIM, DIM);
		v *= m2;
		A(v.ape(vc), false);
		MATRIX<DIM, DIM, T> m3(T(), DIM, DIM);
		v *= m3;
		A(v.isZero(), true);
	}

	//div
	{
		VECTORREF<DIM, T> vecRef(coords2);
		vecRef = coords2;	//maybe vecRef = Vector<>
		rand5Coords(coords1);
		double coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = vecRef(i) / coords1[0];
		vecRef.div(coords1[0]);
		for (std::size_t i = 0; i < DIM; i++) {
			t << vecRef(i);
			t.s << coords3[i];
			t.STEST;
		}
	}

	//operator /=
	{
		VECTORREF<DIM, T> vecRef(coords2);
		vecRef = coords2;	//maybe vecRef = Vector<>
		rand5Coords(coords1);
		double coords3[DIM];
		for (std::size_t i = 0; i < DIM; i++)
			coords3[i] = vecRef(i) / coords1[0];
		vecRef /= coords1[0];
		for (std::size_t i = 0; i < DIM; i++) {
			t << vecRef(i);
			t.s << coords3[i];
			t.STEST;
		}
	}

	//zero
	{
		VECTORREF<DIM, T> vecRef(coords2);
		rand5Coords(coords2);
		vecRef.zero();
		for (std::size_t i = 0; i < DIM; i++) {
			t << vecRef(i);
			t.s << 0;
			t.STEST;
		}
	}

	//invert
	{
		VECTORREF<DIM, T> vecRef(coords2);
		rand5Coords(coords1);
		vecRef = coords1;
		vecRef.invert();
		for (std::size_t i = 0; i < DIM; i++) {
			t << vecRef(i);
			t.s << -coords1[i];
			t.STEST;
		}
	}

	//normalize
	{
		VECTORREF<DIM, T> vecRef(coords1);
		rand5Coords(coords1);
		vecRef.normalize();
		A(vecRef.length(), static_cast<T>(1.0));
	}

	//rotate sin cos
	{
		VECTORREF<DIM, T> vecRef(coords2);
		rand5Coords(coords1);
		vecRef = coords1;
		VECTOR<DIM, T> vec(coords1);
		std::size_t c1 = std::rand() % DIM;
		std::size_t c2 = std::rand() % DIM;
		gpx::real_t sin, cos;
		gpx::math::sincos(gpx::math::PI / 2, sin, cos);
		if (c1 != c2) {
			vecRef.rotate(sin, cos, c1, c2);
			A(vec.ape(vecRef), false);
			vecRef.rotate(sin, cos, c1, c2);
			vecRef.rotate(sin, cos, c1, c2);
			vecRef.rotate(sin, cos, c1, c2);
			A(vec.ape(vecRef), true);
		}
	}

	//rotate angle
	{
		VECTORREF<DIM, T> vecRef(coords2);
		rand5Coords(coords1);
		vecRef = coords1;
		VECTOR<DIM, T> vec(coords1);
		std::size_t c1 = std::rand() % DIM;
		std::size_t c2 = std::rand() % DIM;
		if (c1 != c2) {
			vecRef.rotate(gpx::math::PI / 2, c1, c2);
			A(vec.ape(vecRef), false);
			vecRef.rotate(gpx::math::PI / 2, c1, c2);
			vecRef.rotate(gpx::math::PI / 2, c1, c2);
			vecRef.rotate(gpx::math::PI / 2, c1, c2);
			A(vec.ape(vecRef), true);
		}
	}

	//rotate angle point
	{
		VECTORREF<DIM, T> vecRef(coords2);
		rand5Coords(coords1);
		vecRef = coords1;
		VECTOR<DIM, T> vec(coords1);
		std::size_t c1 = std::rand() % DIM;
		std::size_t c2 = std::rand() % DIM;
		if (c1 != c2) {
			gpx::math::Vector<2, T> p;
			p(0) = drand<T>();
			p(1) = drand<T>();
			vecRef.rotate(gpx::math::PI / 2, p, c1, c2);
			A(vec.ape(vecRef), false);
			vecRef.rotate(gpx::math::PI / 2, p, c1, c2);
			vecRef.rotate(gpx::math::PI / 2, p, c1, c2);
			vecRef.rotate(gpx::math::PI / 2, p, c1, c2);
			A(vec.ape(vecRef), true);
		}
	}

	//minimize
	{
		T coords0[5];
		rand5Coords(coords0);
		rand5Coords(coords1);
		VECTORREF<DIM, T> v0(coords1);
		VECTORREF<DIM, T> v1(coords1);
		VECTOR<DIM, T> vorg(v0);
		v0.minimize(v1);
		A(vorg.versor().ape(v0.versor()), true);
		VECTOR<DIM, T> vp = v1 + v0;
		A((vp == v1), false);
	}

	//swap
	{
		T coords0[5];
		rand5Coords(coords0);
		VECTORREF<DIM, T> v0(coords0);
		VECTORREF<DIM, T> v1(coords1);
		v1 = v0;
		std::size_t c1 = std::rand() % DIM;
		std::size_t c2 = std::rand() % DIM;
		v0.swap(c1, c2);
		A((v0(c1) == v1(c2)), true);
	}
}

template <template <std::size_t, typename> class VECTORREF, std::size_t DIM, typename T,
		  template <std::size_t, typename> class VECTOR,
		  template <std::size_t, typename> class CONST_VECTORREF>
void VectorRef2Test()
{
	const T cA = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
	const T cB = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
//	const T cC = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
//	const T cD = static_cast<T>(std::rand()) / static_cast<T>(std::rand());
//	const T cE = static_cast<T>(std::rand()) / static_cast<T>(std::rand());

	const T c1 = 0.0;
	const T c2 = 0.0;
	const T c3 = 0.0;
	const T c4 = 0.0;
	const T c5 = 0.0;

	T coords1[] = {c1, c2, c3, c4, c5};

	if (DIM != 2) {
		cout << "Error: DIM to perform VectorRef2Test() is: " << 2 << endl;
		return;
	}
	cout << "VectorRef2Test: testing " << typeid(VECTORREF<DIM, T>).name() << " class type: " << typeid(T).name() << " dimension: " << DIM << endl;

	//set x
	{
		rand5Coords(coords1);
		VECTORREF<DIM, T> vptr(coords1);
		vptr.setX(cA);
		A(cA == coords1[0], true);
	}

	//set y
	{
		rand5Coords(coords1);
		VECTORREF<DIM, T> vptr(coords1);
		vptr.setY(cB);
		A(cB == coords1[1], true);
	}

//	//set x, y
//	{
//		rand5Coords(coords1);
//		VECTORREF<DIM, T> vptr(coords1);
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

	//rotate sin cos
	{
		rand5Coords(coords1);
		VECTORREF<DIM, T> vptr(coords1);
		VECTOR<DIM, T> vec(coords1);
		gpx::real_t sin, cos;
		gpx::math::sincos(gpx::math::PI / 2, sin, cos);
		vptr.rotate(sin, cos);
		A(vec.ape(vptr), false);
		vptr.rotate(sin, cos);
		vptr.rotate(sin, cos);
		vptr.rotate(sin, cos);
		A(vec.ape(vptr), true);
	}

	//rotate angle
	{
		rand5Coords(coords1);
		VECTORREF<DIM, T> vptr(coords1);
		VECTOR<DIM, T> vec(coords1);
		T angle = static_cast<T>(gpx::math::PI / 2);
		vptr.rotate(angle);
		A(vec.ape(vptr), false);
		vptr.rotate(angle);
		vptr.rotate(angle);
		vptr.rotate(angle);
		A(vec.ape(vptr), true);
	}

	//rotate angle point
	{
		rand5Coords(coords1);
		VECTOR<DIM, T> point(coords1);
		rand5Coords(coords1);
		VECTORREF<DIM, T> vptr(coords1);
		VECTOR<DIM, T> vec(coords1);
		T angle = static_cast<T>(gpx::math::PI / 2);
		vptr.rotate(angle, point);
		A(vec.ape(vptr), false);
		vptr.rotate(angle, point);
		vptr.rotate(angle, point);
		vptr.rotate(angle, point);
		A(vec.ape(vptr), true);
	}

	//mul matrix 4 x 4
	{
		T mcoords[25];
		rand25Coords(mcoords);
		gpx::math::Matrix<4, 4, T> m(mcoords, 4, 4);
		VECTORREF<DIM, T> v(coords1);
		gpx::math::Vector<4, T> vc(coords1);
		vc(2) = static_cast<T>(0.0);
		vc(3) = static_cast<T>(1.0);
		v.mul(m);
		vc.mul(m);
		for(std::size_t i = 0; i < DIM; i++)
			A(v(i), vc(i));
	}

	//operator *= matrix 4 x 4
	{
		T mcoords[25];
		rand25Coords(mcoords);
		gpx::math::Matrix<4, 4, T> m(mcoords, 4, 4);
		VECTORREF<DIM, T> v(coords1);
		gpx::math::Vector<4, T> vc(coords1);
		vc(2) = static_cast<T>(0.0);
		vc(3) = static_cast<T>(1.0);
		v *= m;
		vc *= m;
		for(std::size_t i = 0; i < DIM; i++)
			A(v(i), vc(i));
	}
}

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
//		gpx::math::sincos(gpx::math::PI / 2, sin, cos);
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

template <std::size_t N, typename T>
class DVectorRefWrapper : public gpx::math::VectorRef<gpx::math::SIZE_DYNAMIC, T>
{
	typedef gpx::math::VectorRef<gpx::math::SIZE_DYNAMIC, T> Parent;

	public:
		DVectorRefWrapper(const gpx::math::VectorRef<gpx::math::SIZE_DYNAMIC, T> & other):
			Parent(other)
		{
		}

		DVectorRefWrapper(T * coords):
			Parent(& m_dv),
			m_dv(coords)
		{
		}

		template <std::size_t ON>
		DVectorRefWrapper(const gpx::math::const_VectorRef<ON, T> & other):
			Parent(other)
		{
		}

		using Parent::operator =;

		DVectorWrapper<N, T> m_dv;
};


#endif // VECTORREFTEST_HPP
