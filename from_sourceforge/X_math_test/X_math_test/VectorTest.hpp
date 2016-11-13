#ifndef VECTORTEST_HPP
#define VECTORTEST_HPP

template <template <std::size_t, typename> class VECTOR, std::size_t DIM, typename T,
		  template <std::size_t, typename> class VECTORREF,
		  template <std::size_t, typename> class CONST_VECTORREF>
void VectorTest()
{
	TestStringStream t;
	t.s.precision(gpx::math::VectorPrint<DIM, T>::Precision);

	const T c1 = 1.0;
	const T c2 = 2.0;
	const T c3 = 3.0;
	const T c4 = 4.0;
	const T c5 = 5.0;

	T coords1[] = {c1, c2, c3, c4, c5};
	T coords2[5];
	rand5Coords(coords2);

	if (DIM > 5) {
		cout << "Error: maximal DIM to perform VectorTest() is: " << 5 << endl;
		return;
	}
	cout << "VectorTest: testing " << typeid(VECTOR<DIM, T>).name() << " class type: " << typeid(T).name() << " dimension: " << DIM << endl;

	//default ctor
	{
		t << VECTOR<DIM, T>();
		t.s << "[";
		for (std::size_t i = 0; i < DIM - 1; i++)
			t.s << "0, ";
		t.s << "0]" << endl;
		t.STEST;
	}

////	//size ctor
////	t << VECTOR<DIM, T>(DIM, DIM);
////	t.s << "[";
////	for (std::size_t i = 0; i < DIM - 1; i++)
////		t.s << "0, ";
////	t.s << "0]" << endl;
////	t.STEST;

//	//bool ctor
//	t << VECTOR<DIM, T>(true);
//	t.s << "[";
//	for (std::size_t i = 0; i < DIM - 1; i++)
//		t.s << "0, ";
//	t.s << "0]" << endl;
//	t.STEST;

	//array ctor
	{
		t << VECTOR<DIM, T>(coords1);
		t.s << "[";
		for (std::size_t i = 0; i < DIM - 1; i++)
			t.s << coords1[i] << ", ";
		t.s << coords1[DIM - 1] << "]" << endl;
		t.STEST;
	}

	//val, num ctor
	{
		for (std::size_t num = 0; num <= DIM; num++) {
			T val = drand<T>();
			VECTOR<DIM, T> vec(val, num);
			for (std::size_t i = 0; i < num; i++)
				A(vec[i] == val, true);
		}
	}

	//copy ctor
	{
		VECTOR<DIM, T> vec(coords2);	//to avoid copy ctor ellision
		t << VECTOR<DIM, T>(vec);
		t.s << vec;
		t.STEST;
	}

	//from VectorRef ctor
	{
		VECTORREF<DIM, T> vecRef(coords2);
		t << VECTOR<DIM, T>(vecRef);
		t.s << vecRef;
		t.STEST;
	}

	//from const_VectorRef ctor
	{
		CONST_VECTORREF<DIM, T> const_vecRef(coords2);
		t << VECTOR<DIM, T>(const_vecRef);
		t.s << const_vecRef;
		t.STEST;
	}

//	//two point ctor
//	t << VECTOR<DIM, T>(coords1, coords1);
//	t.s << VECTOR<DIM, T>(); //shall have all 0s
//	t.STEST;

//	//val ctor
//	for (std::size_t i = 0; i < 5; i++)
//		coords2[i] = coords2[0];
//	t << VECTOR<DIM, T>(coords2[0]);
//	t.s << VECTOR<DIM, T>(coords2);
//	t.STEST;

//	//val size ctor
//	{
////		T val = drand<T>();
////		std::size_t num = std::rand() % DIM;
////		VECTOR<DIM, T> v(val, num);
////		for (std::size_t i = 0; i < num; i++)
////			A(v(i) == val, true);
//	}

	//assignment = array
	{
		rand5Coords(coords2);
		VECTOR<DIM, T> v;	//initializes with 0s
		v = coords2;
		t << v;
		t.s << VECTOR<DIM, T>(coords2);
		t.STEST;
	}

	//assignment = other Vector (copy assignment)
	{
		rand5Coords(coords2);
		VECTOR<DIM, T> v;	//initializes with 0s
		v = VECTOR<DIM, T>(coords2);
		t << v;
		t.s << VECTOR<DIM, T>(coords2);
		t.STEST;
	}

	//assignment = VectorPtr
	{
		rand5Coords(coords2);
		VECTOR<DIM, T> v;	//initializes with 0s
		v = VECTORREF<DIM, T>(coords2);
		t << v;
		t.s << VECTORREF<DIM, T>(coords2);
		t.STEST;
	}

	//assignment = const_VectorPtr
	{
		rand5Coords(coords2);
		VECTOR<DIM, T> v;	//initializes with 0s
		v = CONST_VECTORREF<DIM, T>(coords2);
		t << v;
		t.s << CONST_VECTORREF<DIM, T>(coords2);
		t.STEST;
	}

//	//assignment = val
//	v = coords2[0];
//	for (std::size_t i = 0; i < DIM; i++)
//		A(v(i), coords2[0]);

//	//reserve
//	{
//		VECTOR<DIM, T> v;
//		v.reserve(DIM);
//		A(v.reserve() == DIM, true);
//	}

//	//reserve set
//	{
//		VECTOR<DIM, T> v;
//		VECTOR<DIM, T> vc(v);
//		vc.reserve(DIM + 1);
//		A(vc == v, true);
//		vc.reserve(0);
//		A(vc == v, true);
//		vc.reserve(DIM);
//		A(vc == v, true);
//	}

//	//resize
//	{
//		VECTOR<DIM, T> v;
//		v.resize(DIM);
//	}

//	//this should not compile
////	VECTOR<DIM, T>(gpx::math::VectorPtr<3>(coords1));
////	VECTOR<DIM, T>(gpx::math::const_VectorPtr<3>(coords1));
}

template <template <std::size_t, typename> class VECTOR, std::size_t DIM, typename T,
		  template <std::size_t, typename> class VECTORPTR,
		  template <std::size_t, typename> class CONST_VECTORPTR>
void Vector2Test()
{
	const T c1 = 1.0;
	const T c2 = 2.0;
	const T c3 = 3.0;
	const T c4 = 4.0;
	const T c5 = 5.0;

	T coords1[] = {c1, c2, c3, c4, c5};
	T coords2[5];
	rand5Coords(coords2);

	if (DIM != 2) {
		cout << "Error: DIM to perform Vector2Test() is: " << 2 << endl;
		return;
	}
	cout << "Vector2Test: testing " << typeid(VECTOR<DIM, T>).name() << " class type: " << typeid(T).name() << " dimension: " << DIM << endl;

	//x y ctor
	VECTOR<DIM, T> v(coords1[0], coords1[1]);
	A(v(0) == coords1[0], true);
	A(v(1) == coords1[1], true);
}

//template <template <std::size_t, typename> class VECTOR, std::size_t DIM, typename T,
//		  template <std::size_t, typename, bool DIMSPEC = true> class VECTORPTR,
//		  template <std::size_t, typename, bool DIMSPEC = true> class CONST_VECTORPTR>
//void Vector3Test()
//{
//	const T c1 = 1.0;
//	const T c2 = 2.0;
//	const T c3 = 3.0;
//	const T c4 = 4.0;
//	const T c5 = 5.0;

//	T coords1[] = {c1, c2, c3, c4, c5};
//	T coords2[5];
//	rand5Coords(coords2);

//	if (DIM != 3) {
//		cout << "Error: DIM to perform Vector3Test() is: " << 3 << endl;
//		return;
//	}
//	cout << "Vector3Test: testing " << typeid(VECTOR<DIM, T>).name() << " class type: " << typeid(T).name() << " dimension: " << DIM << endl;

//	//x y z ctor
//	VECTOR<DIM, T> v(coords1[0], coords1[1], coords1[2]);
//	A(v(0) == coords1[0], true);
//	A(v(1) == coords1[1], true);
//	A(v(2) == coords1[2], true);
//}

template <template <std::size_t, typename> class D_VECTOR, std::size_t N, typename T>
void VectorDynamicTest()
{
	typedef D_VECTOR<gpx::math::SIZE_DYNAMIC, T> DVECTOR;

	if (N > 5) {
		cout << "Error: maximal N to perform VectorDynamicTest() is: " << 5 << endl;
		return;
	}
	cout << "VectorDynamicTest: testing " << typeid(DVECTOR).name() << " class type: " << typeid(T).name() << " size: " << N << endl;

	T coords[5];
	TestStringStream t;
	t.s.precision(gpx::math::VectorPrint<N, T>::Precision);

	//size ctor
	{
		t << DVECTOR(N);
		t.s << "[";
		for (std::size_t i = 0; i < N - 1; i++)
			t.s << "0, ";
		t.s << "0]" << endl;
		t.STEST;
	}

	//val size ctor
	{
		for (std::size_t num = 0; num <= N; num++) {
			T val = drand<T>();
			DVECTOR vec(val, num);
			for (std::size_t i = 0; i < num; i++)
				A(vec[i] == val, true);
		}
	}

	//array size ctor
	{
		rand5Coords(coords);
		t << DVECTOR(coords, N);
		t.s << "[";
		for (std::size_t i = 0; i < N - 1; i++)
			t.s << coords[i] << ", ";
		t.s << coords[N - 1] << "]" << endl;
		t.STEST;
	}

	//copy ctor
	{
		rand5Coords(coords);
		DVECTOR v(coords, N);
		t << v;
		t.s << DVECTOR(v);
		t.STEST;
	}

	//from Vector<ON>
	{
		rand5Coords(coords);
		gpx::math::Vector<1, T> v1(coords);
		t << v1;
		t.s << DVECTOR(v1);
		t.STEST;

		rand5Coords(coords);
		gpx::math::Vector<2, T> v2(coords);
		t << v2;
		t.s << DVECTOR(v2);
		t.STEST;

		rand5Coords(coords);
		gpx::math::Vector<3, T> v3(coords);
		t << v3;
		t.s << DVECTOR(v3);
		t.STEST;

		rand5Coords(coords);
		gpx::math::Vector<4, T> v4(coords);
		t << v4;
		t.s << DVECTOR(v4);
		t.STEST;

		rand5Coords(coords);
		gpx::math::Vector<5, T> v5(coords);
		t << v5;
		t.s << DVECTOR(v5);
		t.STEST;
	}

	//from VectorRef<ON>
	{
		rand5Coords(coords);
		DVECTOR dv(coords, N);
		gpx::math::VectorRef<0, T> v0(dv) ;
		t << v0;
		t.s << DVECTOR(v0);
		t.STEST;

		rand5Coords(coords);
		gpx::math::VectorRef<1, T> v1(coords);
		t << v1;
		t.s << DVECTOR(v1);
		t.STEST;

		rand5Coords(coords);
		gpx::math::VectorRef<2, T> v2(coords);
		t << v2;
		t.s << DVECTOR(v2);
		t.STEST;

		rand5Coords(coords);
		gpx::math::VectorRef<3, T> v3(coords);
		t << v3;
		t.s << DVECTOR(v3);
		t.STEST;

		rand5Coords(coords);
		gpx::math::VectorRef<4, T> v4(coords);
		t << v4;
		t.s << DVECTOR(v4);
		t.STEST;

		rand5Coords(coords);
		gpx::math::VectorRef<5, T> v5(coords);
		t << v5;
		t.s << DVECTOR(v5);
		t.STEST;
	}

	//from const_VectorRef<ON>
	{
		rand5Coords(coords);
		DVECTOR dv(coords, N);
		gpx::math::const_VectorRef<0, T> v0(dv) ;
		t << v0;
		t.s << DVECTOR(v0);
		t.STEST;

		rand5Coords(coords);
		gpx::math::const_VectorRef<1, T> v1(coords);
		rand5Coords(coords);
		t << v1;
		t.s << DVECTOR(v1);
		t.STEST;

		gpx::math::const_VectorRef<2, T> v2(coords);
		rand5Coords(coords);
		t << v2;
		t.s << DVECTOR(v2);
		t.STEST;

		gpx::math::const_VectorRef<3, T> v3(coords);
		rand5Coords(coords);
		t << v3;
		t.s << DVECTOR(v3);
		t.STEST;

		gpx::math::const_VectorRef<4, T> v4(coords);
		rand5Coords(coords);
		t << v4;
		t.s << DVECTOR(v4);
		t.STEST;

		gpx::math::const_VectorRef<5, T> v5(coords);
		t << v5;
		t.s << DVECTOR(v5);
		t.STEST;
	}

	//copy assignment (= Vector<SIZE_DYNAMIC>)
	{
		rand5Coords(coords);
		DVECTOR v(coords, N);
		DVECTOR v2(N);
		v2 = v;
		t << v;
		t.s << v2;
		t.STEST;
		//self assignment
		t << v;
		v = v;
		t.s << v;
		t.STEST;
	}

	//= VectorRef<ON>
	{
		DVECTOR v(coords, N);
		rand5Coords(coords);
		DVECTOR dv(coords, N);
		gpx::math::VectorRef<0, T> v0(dv) ;
		v = v0;
		t << v0;
		t.s << v;
		t.STEST;

		rand5Coords(coords);
		gpx::math::VectorRef<1, T> v1(coords);
		v = v1;
		t << v1;
		t.s << v;
		t.STEST;

		rand5Coords(coords);
		gpx::math::VectorRef<1, T> v2(coords);
		v = v2;
		t << v2;
		t.s << v;
		t.STEST;

		rand5Coords(coords);
		gpx::math::VectorRef<1, T> v3(coords);
		v = v3;
		t << v3;
		t.s << v;
		t.STEST;

		rand5Coords(coords);
		gpx::math::VectorRef<1, T> v4(coords);
		v = v4;
		t << v4;
		t.s << v;
		t.STEST;

		rand5Coords(coords);
		gpx::math::VectorRef<1, T> v5(coords);
		v = v5;
		t << v5;
		t.s << v;
		t.STEST;
	}

	//= const_VectorRef<ON>
	{
		DVECTOR v(coords, N);
		rand5Coords(coords);
		DVECTOR dv(coords, N);
		gpx::math::const_VectorRef<0, T> v0(dv) ;
		v = v0;
		t << v0;
		t.s << v;
		t.STEST;

		rand5Coords(coords);
		gpx::math::const_VectorRef<1, T> v1(coords);
		v = v1;
		t << v1;
		t.s << v;
		t.STEST;

		rand5Coords(coords);
		gpx::math::const_VectorRef<1, T> v2(coords);
		v = v2;
		t << v2;
		t.s << v;
		t.STEST;

		rand5Coords(coords);
		gpx::math::const_VectorRef<1, T> v3(coords);
		v = v3;
		t << v3;
		t.s << v;
		t.STEST;

		rand5Coords(coords);
		gpx::math::const_VectorRef<1, T> v4(coords);
		v = v4;
		t << v4;
		t.s << v;
		t.STEST;

		rand5Coords(coords);
		gpx::math::const_VectorRef<1, T> v5(coords);
		v = v5;
		t << v5;
		t.s << v;
		t.STEST;
	}

	//resize
	{
		DVECTOR v(coords, N);
		for (std::size_t size = 1; size < 5; size++) {
			v.resize(size);
			A(v.size() == size, true);
		}
	}
}

template <std::size_t N, typename T>
class DVectorWrapper : public gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T>
{
	typedef gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> Parent;

	public:
		DVectorWrapper():
			Parent(N)
		{
		}

		DVectorWrapper(const gpx::math::Vector<gpx::math::SIZE_DYNAMIC, T> & other):
			Parent(other)
		{
		}

		template <std::size_t ON>
		explicit DVectorWrapper(gpx::math::const_VectorRef<ON, T> other):
			Parent(other)
		{
		}

		template <std::size_t ON>
		explicit DVectorWrapper(const gpx::math::VectorRef<ON, T> & other):
			Parent(other)
		{
		}

		template <std::size_t ON>
		explicit DVectorWrapper(const gpx::math::Vector<ON, T> & other):
			Parent(other)
		{
		}

		explicit DVectorWrapper(const T * coords):
			Parent(coords, N)
		{
		}

//		DVectorWrapper(const T init[N], const T end[N]):
//			Parent(init, end, N)
//		{
//		}

		DVectorWrapper(T val):
			Parent(val, N)
		{
		}

		DVectorWrapper(T val, std::size_t size):
			Parent(val, size)
		{
		}

//		operator gpx::math::const_VectorRef<gpx::math::SIZE_DYNAMIC, T> () const
//		{
//			return static_cast<gpx::math::const_VectorRef<gpx::math::SIZE_DYNAMIC, T> >(*this);
//		}

//		operator gpx::math::VectorRef<gpx::math::SIZE_DYNAMIC, T> ()
//		{
//			return static_cast<gpx::math::VectorRef<gpx::math::SIZE_DYNAMIC, T> >(*this);
//		}

		using Parent::operator =;
};


#endif // VECTORTEST_HPP
