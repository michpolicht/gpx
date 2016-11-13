#ifndef MATRIXTEST_HPP
#define MATRIXTEST_HPP

template <template <std::size_t, std::size_t, typename> class MATRIX, std::size_t M, std::size_t N, typename T,
			template <std::size_t, typename> class VECTOR,
			template <std::size_t, typename> class VECTORPTR,
			template <std::size_t, typename> class CONST_VECTORPTR>
void MatrixTest()
{
	if (M > 5) {
		cout << "Error: maximal M to perform MatrixTest() is: " << 5 << endl;
		return;
	}
	if (N > 5) {
		cout << "Error: maximal N to perform MatrixTest() is: " << 5 << endl;
		return;
	}
	cout << "MatrixTest: testing " << typeid(MATRIX<M, N, T>).name() << " class type: " << typeid(T).name() << " size (rows x cols): " << M << "x" << N << endl;

	T coords1[25];
	T coords2[25];

	//default ctor
	MATRIX<M, N, T>();

	//ctor d, rows, cols
	MATRIX<M, N, T>(T(), 0, 0);

	//ctor from T *
	rand25Coords(coords1);
	MATRIX<M, N, T>(static_cast<T *>(coords1));	//static_cast to distinguish from defining coords1 as function ptr

	//ctor val
	{
		MATRIX<M, N, T> m(static_cast<T>(4.0));
		for (std::size_t col = 0; col < N; col++)	//col
			for (std::size_t row = 0; row < M; row++)	//row
				if (row == col)
					A(m(row, col), static_cast<T>(4.0));
				else
					A(m(row, col), static_cast<T>(0.0));
	}

	//rows
	{
		MATRIX<M, N, T> m;
		A(m.rows() == M, true);
	}

	//cols
	{
		MATRIX<M, N, T> m;
		A(m.cols() == N, true);
	}

	//size
	{
		MATRIX<M, N, T> m;
		A(m.size() == N * M, true);
	}

//	//resize
//	{
//		MATRIX<M, N, T> m;
//		m.resize(M, N);
//		std::size_t r = M;
//		std::size_t c = N;
//		while (r == M)
//			r = std::rand() % M;
//		while (c == N)
//			c = std::rand() % N;
//		if ((MATRIX<M, N, T>::ROWS == gpx::math::SIZE_DYNAMIC) && (MATRIX<M, N, T>::COLS == gpx::math::SIZE_DYNAMIC))
//			m.resize(r, c);
//	}

//	//reserve set
//	{
//		MATRIX<M, N, T> m;
//		MATRIX<M, N, T> mc(m);
//		mc.reserve(M * N + 1);
//		A(mc == m, true);
//		mc.reserve(0);
//		A(mc == m, true);
//		mc.reserve(M * N);
//		A(mc == m, true);
//	}

//	//reserve
//	{
//		MATRIX<M, N, T> m;
//		m.reserve(M * N);
//		A(m.reserve() == M * N, true);
//	}

	//operator () const
	rand25Coords(coords1);
	MATRIX<M, N, T> m(coords1);
	for (std::size_t col = 0; col < N; col++)	//col
		for (std::size_t row = 0; row < M; row++)	//row
			A(m(row, col), coords1[col * M + row]);

	//operator ()
	rand25Coords(coords2);
	MATRIX<M, N, T> m2(coords2);
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++) {
			m(row, col) = m2(row, col);
			A(m(row, col), m2(row, col));
		}

	//operator ==
	A((MATRIX<M, N, T>(coords2) == m2), true);
	A((MATRIX<M, N, T>(coords1) == m2), false);

//	//operator == val
//	A((MATRIX<M, N, T>(4.0) == 4.0), true);
//	A((MATRIX<M, N, T>(4.0) == 5.0), false);
//	{
//		MATRIX<M, N, T> m(1.0);
//		A(m == 1.0, true);
//		m(std::rand() % M, std::rand() % N) = 2.0;
//		A((m == 1.0), false);
//	}

	//isIdentity
	{
		MATRIX<M, N, T> m(1.0);
		A(m.isIdentity(), true);
		m(std::rand() % M, std::rand() % N) = 2.0;
		A(m.isIdentity(), false);
	}

	//isZero
	{
		MATRIX<M, N, T> m(0.0);
		A(m.isZero(), true);
		m(std::rand() % M, std::rand() % N) = 2.0;
		A(m.isZero(), false);
	}

	//ape
	{
		rand25Coords(coords1);
		m = coords1;
		A(m.ape(MATRIX<M, N, T>(coords1)), true);
		std::size_t row = std::rand() % M;
		std::size_t col = std::rand() % N;
		m(row, col) += gpx::math::eps(m(row, col));
		A((MATRIX<M, N, T>(coords1) == m), false);
		A(m.ape(MATRIX<M, N, T>(coords1)), true);
		m(row, col) += 100.0 * gpx::math::eps(m(row, col));
		A(m.ape(MATRIX<M, N, T>(coords1)), false);
	}

	//apeIdentity
	{
		MATRIX<M, N, T> m(1.0);
		A(m.apeIdentity(), true);

		std::size_t d = std::rand() % std::min(M, N);
		m(d, d) += gpx::math::eps(1.0);
		A(m.apeIdentity(), true);

		m(std::rand() % M, std::rand() % N) = 2.0;
		A(m.apeIdentity(), false);
	}

	//apeZero
	{
		MATRIX<M, N, T> m(0.0);
		A(m.apeZero(), true);

		std::size_t d = std::rand() % std::min(M, N);
		m(d, d) += gpx::math::eps(0.0);
		A(m.apeZero(), true);

		m(std::rand() % M, std::rand() % N) = 2.0;
		A(m.apeZero(), false);
	}

//	//ape val
//	{
//		A((MATRIX<M, N, T>(4.0).ape(4.0)), true);
//		A((MATRIX<M, N, T>(4.0).ape(5.0)), false);
//		A((MATRIX<M, N, T>(4.0).ape(4.0 + gpx::math::eps(4.0))), true);
//	}

	//ale
	{
		rand25Coords(coords1);
		m = coords1;
		A(m.ale(MATRIX<M, N, T>(coords1)), true);
		std::size_t row = std::rand() % M;
		std::size_t col = std::rand() % N;
		m(row, col) += gpx::math::eps(m(row, col));
		A((MATRIX<M, N, T>(coords1) == m), false);
		A(m.ale(MATRIX<M, N, T>(coords1)), true);
		m(row, col) += 100.0 * gpx::math::eps(m(row, col));
		A(m.ale(MATRIX<M, N, T>(coords1)), false);
	}

	//apeIdentity
	{
		MATRIX<M, N, T> m(1.0);
		A(m.aleIdentity(), true);

		std::size_t d = std::rand() % std::min(M, N);
		m(d, d) += gpx::math::eps(1.0);
		A(m.aleIdentity(), true);

		m(std::rand() % M, std::rand() % N) = 2.0;
		A(m.aleIdentity(), false);
	}

	//aleZero
	{
		MATRIX<M, N, T> m(0.0);
		A(m.aleZero(), true);

		m(std::rand() % M, std::rand() % N) = 2.0;
		A(m.aleZero(), false);
	}

//	//ale val
//	{
//		A((MATRIX<M, N, T>(4.0).ale(4.0)), true);
//		A((MATRIX<M, N, T>(4.0).ale(5.0)), false);
//		A((MATRIX<M, N, T>(4.0).ale(4.0 + gpx::math::eps(4.0))), true);
//	}

	//operator !=
	A((MATRIX<M, N, T>(coords2) != m2), false);
	A((MATRIX<M, N, T>(coords1) != m2), true);

//	//operator != val
//	A((MATRIX<M, N, T>(4.0) != 5.0), true);
//	A((MATRIX<M, N, T>(4.0) != 4.0), false);
//	{
//		MATRIX<M, N, T> m(1.0);
//		A(m != 1.0, false);
//		m(std::rand() % M, std::rand() % N) = 2.0;
//		A((m != 1.0), true);
//	}

	//copy ctor
	MATRIX<M, N, T> mc(m2);
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++)
			A(m2(row, col), mc(row, col));

	//operator =
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;	//implicit ctor
	m2 = MATRIX<M, N, T>(coords2);	//explicit ctor
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++) {
			A(m(row, col), coords1[col * M + row]);
			A(m2(row, col), coords2[col * M + row]);
		}

//	//operator = val
//	m = 4.0;
//	for (std::size_t col = 0; col < N; col++)
//		for (std::size_t row = 0; row < M; row++)
//			if (row == col)
//				A(m(row, col), 4.0);
//			else
//				A(m(row, col), 0.0);
//	rand25Coords(coords1);
//	m = coords1;
//	m = 0.0;
//	for (std::size_t col = 0; col < N; col++)
//		for (std::size_t row = 0; row < M; row++)
//			A(m(row, col), T());

	//zero
	{
		rand25Coords(coords1);
		MATRIX<M, N, T> m(coords1);
		A(m.isZero(), false);
		m.zero();
		A(m.isZero(), true);
	}

	//identity
	{
		rand25Coords(coords1);
		MATRIX<M, N, T> m(coords1);
		A(m.isIdentity(), false);
		m.identity();
		A(m.isIdentity(), true);
	}

	//ptr
	T * ptr = m.ptr();
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++)
			A(m(row, col), ptr[col * M + row]);

	//const ptr
	const T * const_ptr = m.ptr();
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++)
			A(m(row, col), const_ptr[col * M + row]);

	//ptr(i, j)
	{
		std::size_t i = std::rand() % M;
		std::size_t j = std::rand() % N;
		ptr = m.ptr(i, j);
		for (std::size_t col = 0; col + j < N; col++)
			for (std::size_t row = 0; row + i < M; row++)
				A(m(row + i, col + j), ptr[col * M + row]);
	}

	//const ptr(i, j)
	{
		std::size_t i = std::rand() % M;
		std::size_t j = std::rand() % N;
		const_ptr = m.ptr(i, j);
		for (std::size_t col = 0; col + j < N; col++)
			for (std::size_t row = 0; row + i < M; row++)
				A(m(row + i, col + j), const_ptr[col * M + row]);
	}

	//add
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	m2 = coords2;
	m.add(m2);
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++)
			A(m(row, col), coords1[col * M + row] + m2(row, col));

	//+=
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	m2 = coords2;
	m += m2;
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++)
			A(m(row, col), coords1[col * M + row] + m2(row, col));

	//sub
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	m2 = coords2;
	m.sub(m2);
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++)
			A(m(row, col), coords1[col * M + row] - m2(row, col));

	//-=
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	m2 = coords2;
	m -= m2;
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++)
			A(m(row, col), coords1[col * M + row] - m2(row, col));

	//mul
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	mc = m;
	MATRIX<N, N, T> msq(coords2);
	m.mul(msq);
	for (std::size_t r = 0; r < M; r++) {
		for (std::size_t c = 0; c < N; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += mc(r, cr) * msq(cr, c);
			A(el, m(r, c));
		}
	}

	//mul val
	rand25Coords(coords1);
	m = coords1;
	mc = m;
	T multiplier = drand<T>();
	m.mul(multiplier);
	for (std::size_t r = 0; r < M; r++) {
		for (std::size_t c = 0; c < N; c++) {
			A(mc(r, c) * multiplier, m(r, c));
		}
	}

	//operator *=
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	mc = m;
	m *= msq;
	for (std::size_t r = 0; r < M; r++) {
		for (std::size_t c = 0; c < N; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += mc(r, cr) * msq(cr, c);
			A(el, m(r, c));
		}
	}

	//operator *= val
	rand25Coords(coords1);
	m = coords1;
	mc = m;
	multiplier = drand<T>();
	m *= multiplier;
	for (std::size_t r = 0; r < M; r++) {
		for (std::size_t c = 0; c < N; c++) {
			A(mc(r, c) * multiplier, m(r, c));
		}
	}

	//sum
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	m2 = coords2;
	MATRIX<M, N, T> mSum = m.sum(m2);
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++)
			A(mSum(row, col), coords1[col * M + row] + coords2[col * M + row]);

	//operator +
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	m2 = coords2;
	mSum = m + (m2);
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++)
			A(mSum(row, col), coords1[col * M + row] + coords2[col * M + row]);

	//diff
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	m2 = coords2;
	MATRIX<M, N, T> mDiff = m.diff(m2);
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++)
			A(mDiff(row, col), coords1[col * M + row] - coords2[col * M + row]);

	//operator -
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	m2 = coords2;
	mDiff = m - m2;
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < M; row++)
			A(mDiff(row, col), coords1[col * M + row] - coords2[col * M + row]);

	//prod
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	MATRIX<N, 1, T> mp1(coords2);
	MATRIX<N, 2, T> mp2(coords2);
	MATRIX<N, 3, T> mp3(coords2);
	MATRIX<N, 4, T> mp4(coords2);
	MATRIX<N, 5, T> mp5(coords2);
	MATRIX<M, 1, T> m1Prod = m.prod(mp1);
	MATRIX<M, 2, T> m2Prod = m.prod(mp2);
	MATRIX<M, 3, T> m3Prod = m.prod(mp3);
	MATRIX<M, 4, T> m4Prod = m.prod(mp4);
	MATRIX<M, 5, T> m5Prod = m.prod(mp5);
	for (std::size_t r = 0; r < M; r++) {
		for (std::size_t c = 0; c < 1; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += m(r, cr) * mp1(cr, c);
			A(el, m1Prod(r, c));
		}
		for (std::size_t c = 0; c < 2; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += m(r, cr) * mp2(cr, c);
			A(el, m2Prod(r, c));
		}
		for (std::size_t c = 0; c < 3; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += m(r, cr) * mp3(cr, c);
			A(el, m3Prod(r, c));
		}
		for (std::size_t c = 0; c < 4; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += m(r, cr) * mp4(cr, c);
			A(el, m4Prod(r, c));
		}
		for (std::size_t c = 0; c < 5; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += m(r, cr) * mp5(cr, c);
			A(el, m5Prod(r, c));
		}
	}

	//prod vec
	{
		T vc[5];
		rand5Coords(vc);
		CONST_VECTORPTR<N, T> v(vc);
		rand25Coords(coords1);
		m = coords1;
		VECTOR<M, T> result = m.prod(v);
		for (std::size_t r = 0; r < M; r++) {
			T el = T();
			for (std::size_t c = 0; c < N; c++)
				el += m(r, c) * v(c);
			A(el, result(r));
		}
	}

	//prod val
	rand25Coords(coords1);
	m = coords1;
	multiplier = drand<T>();
	m2 = m.prod(multiplier);
	for (std::size_t r = 0; r < M; r++) {
		for (std::size_t c = 0; c < N; c++) {
			A(m(r, c) * multiplier, m2(r, c));
		}
	}

	//operator *
	rand25Coords(coords1);
	rand25Coords(coords2);
	m = coords1;
	m1Prod = m * mp1;
	m2Prod = m * mp2;
	m3Prod = m * mp3;
	m4Prod = m * mp4;
	m5Prod = m * mp5;
	for (std::size_t r = 0; r < M; r++) {
		for (std::size_t c = 0; c < 1; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += m(r, cr) * mp1(cr, c);
			A(el, m1Prod(r, c));
		}
		for (std::size_t c = 0; c < 2; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += m(r, cr) * mp2(cr, c);
			A(el, m2Prod(r, c));
		}
		for (std::size_t c = 0; c < 3; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += m(r, cr) * mp3(cr, c);
			A(el, m3Prod(r, c));
		}
		for (std::size_t c = 0; c < 4; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += m(r, cr) * mp4(cr, c);
			A(el, m4Prod(r, c));
		}
		for (std::size_t c = 0; c < 5; c++) {
			T el = T();
			for (std::size_t cr = 0; cr < N; cr++)
				el += m(r, cr) * mp5(cr, c);
			A(el, m5Prod(r, c));
		}
	}

	//operator * val
	rand25Coords(coords1);
	m = coords1;
	multiplier = drand<T>();
	m2 = m * multiplier;
	for (std::size_t r = 0; r < M; r++) {
		for (std::size_t c = 0; c < N; c++) {
			A(m(r, c) * multiplier, m2(r, c));
		}
	}

	//transposed
	rand25Coords(coords1);
	m = coords1;
	A(m.transposed().transposed() == m, true);

	//swap rows
	rand25Coords(coords1);
	m = coords1;
	m2 = m;
	std::size_t r1 = std::rand() % M;
	std::size_t r2 = std::rand() % M;
	m.swapRows(r1, r2);
	for (std::size_t c = 0; c < N; c++)
		A((m(r1, c) == m2(r2, c)), true);

	//swap cols
	rand25Coords(coords1);
	m = coords1;
	m2 = m;
	std::size_t c1 = std::rand() % N;
	std::size_t c2 = std::rand() % N;
	m.swapCols(c1, c2);
	for (std::size_t r = 0; r < M; r++)
		A((m(r, c1) == m2(r, c2)), true);
}

template <template <std::size_t, std::size_t, typename> class MATRIX, std::size_t N, typename T>
void MatrixSqTest()
{
	if (N > 5) {
		cout << "Error: maximal M to perform MatrixSqTest() is: " << 5 << endl;
		return;
	}
	if (N > 5) {
		cout << "Error: maximal N to perform MatrixSqTest() is: " << 5 << endl;
		return;
	}
	cout << "MatrixSqTest: testing " << typeid(MATRIX<N, N, T>).name() << " class type: " << typeid(T).name() << " size (rows x cols): " << N << "x" << N << endl;

	T coords1[25];
//	T coords2[25];

	//transpose
	rand25Coords(coords1);
	MATRIX<N, N, T> m(coords1);
	m.transpose().transpose();
	for (std::size_t el = 0; el < N * N; el++)
		A(m.ptr()[el], coords1[el]);

	//invert
	MATRIX<N, N, T> m2(m);
	m2.invert();
	m *= m2;
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < N; row++)
			if (row == col)
				A(m(row, col), 1.0);
			else
				A(m(row, col), 0.0);

	//det
	rand25Coords(coords1);
	for (std::size_t col = 0; col < N; col++)
		for (std::size_t row = 0; row < N; row++)
			m(row, col) = 1.0;
	if (N != 1)
		A(m.det(), 0.0);
	else
		A(m.det(), 1.0);
	m.identity();
	A(m.det(), 1.0);
	m = coords1;
	T det1 = m.det();
	m.transpose();
	A(m.det(), det1);
	det1 = m.det();
	m.invert();
	A(m.det(), 1.0 / det1);
}

template <std::size_t M, std::size_t N, typename T>
void MatrixDynamicTest()
{
	typedef gpx::math::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> DynamicMatrix;

	if (N > 5) {
		cout << "Error: maximal M to perform MatrixDynamicTest() is: " << 5 << endl;
		return;
	}
	if (N > 5) {
		cout << "Error: maximal N to perform MatrixDynamicTest() is: " << 5 << endl;
		return;
	}
	cout << "MatrixDynamicTest: testing " << typeid(DynamicMatrix).name() << " class type: " << typeid(T).name() << " size (rows x cols): " << M << "x" << N << endl;

	//default ctor
	{
		DynamicMatrix m(M, N);
	}

	//copy ctor
	{
		DynamicMatrix m(M, N);
		DynamicMatrix md(m);
	}

//	//coversion ctor
//	{
//		gpx::math::Matrix<M, N> m;
//		DynamicMatrix md(m);
//	}

	//assignment
	{
		DynamicMatrix m(M, N);
		DynamicMatrix m2(2, 2);
		m2(0, 0) = 12.0;
		m = m2;
	}

//	//assignment conversion
//	{
//		gpx::math::Matrix<M, N> m;
//		DynamicMatrix md;
//		m(0, 0) = 12.0;
//		md = m;
//	}

	//resize
	{
		DynamicMatrix md(T(), M, N);
		md.resize(1, 3);
	}

	//reserve
	{
		DynamicMatrix md(1, 1);
		md(0, 0) = 1.5;
		md.reserve(10);
		A(md(0, 0) == 1.5, true);
	}

	T coords[25];
	for (std::size_t i = 0; i < 25; i++)
		coords[i] = i;
	{
		DynamicMatrix m(coords, M, N);
	}

	{
		DynamicMatrix md(1.5, 1, 2);
	}

	//transpose
	{
		DynamicMatrix d(coords, 2, 5);
		d.transpose();
	}

	//invert
	{
		DynamicMatrix d(coords, 5, 5);
		d.invert();
	}

	//det
	{
		if (M == N) {
			DynamicMatrix d(coords, M, N);
			d.det();
		}
	}
}


template <std::size_t M, std::size_t N, typename T>
class DMatrixWrapper : public gpx::math::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>
{
	typedef gpx::math::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> Parent;

	public:
		DMatrixWrapper():
			Parent(M, N)
		{
		}

		DMatrixWrapper(const T * elements):
			Parent(elements, M, N)
		{
		}

		DMatrixWrapper(const T * elements, std::size_t rows, std::size_t cols):
			Parent(elements, rows, cols)
		{
		}

		explicit DMatrixWrapper(T d):
			Parent(d, M, N)
		{
		}

		DMatrixWrapper(T d, std::size_t rows, std::size_t cols):
			Parent(d, rows, cols, M * N)
		{
		}

		template <std::size_t OM, std::size_t ON>
		DMatrixWrapper(const gpx::math::Matrix<OM, ON, T> & other):
			Parent(other)
		{
		}

		using Parent::operator =;
};

#endif // MATRIXTEST_HPP
