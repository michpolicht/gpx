/**
 * @file
 * @brief .
 */

namespace gpx {
namespace math {
namespace basic {

template <std::size_t M, std::size_t N, typename T>
inline
MatrixStorage<M, N, T>::MatrixStorage(std::size_t reserve)
{
	GPX_UNUSED(reserve);

	for (std::size_t i = 0; i < M * N; i++)
		m_elements[i] = T();
}

template <std::size_t M, std::size_t N, typename T>
inline
MatrixStorage<M, N, T>::MatrixStorage(std::size_t rows, std::size_t cols, std::size_t reserve)
{
	GPX_UNUSED(reserve);

	for (std::size_t j = 0; j < cols; j++)
		for (std::size_t i = 0; i < rows; i++)
			m_elements[j * M + i] = T();
}

template <std::size_t M, std::size_t N, typename T>
inline
MatrixStorage<M, N, T>::MatrixStorage(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve)
{
	GPX_UNUSED(reserve);

	for (std::size_t j = 0; j < cols; j++)
		for (std::size_t i = 0; i < rows; i++)
			m_elements[j * M + i] = elements[j * M + i];
//	memcpy(m_elements, elements, sizeof(m_elements));
}

template <std::size_t M, std::size_t N, typename T>
inline
MatrixStorage<M, N, T>::MatrixStorage(T d, std::size_t rows, std::size_t cols, std::size_t )
{
	for (std::size_t j = 0; j < cols; j++)
		for (std::size_t i = 0; i < rows; i++)
			m_elements[j * M + i] = T();
	for (std::size_t i = 0; i < std::min(rows, cols); i++)
		m_elements[M * i + i] = d;
}

template <std::size_t M, std::size_t N, typename T>
inline
std::size_t MatrixStorage<M, N, T>::rows() const
{
	return M;
}

template <std::size_t M, std::size_t N, typename T>
inline
std::size_t MatrixStorage<M, N, T>::cols() const
{
	return N;
}

template <std::size_t M, std::size_t N, typename T>
inline
std::size_t MatrixStorage<M, N, T>::size() const
{
	return N * M;
}

template <std::size_t M, std::size_t N, typename T>
inline
void MatrixStorage<M, N, T>::resize(std::size_t p_rows, std::size_t p_cols)
{
	GPX_ASSERT(rows() == p_rows && cols() == p_cols, "can not resize fixed sized matrix");
}

template <std::size_t M, std::size_t N, typename T>
inline
std::size_t MatrixStorage<M, N, T>::reserve() const
{
	return size();
}

template <std::size_t M, std::size_t N, typename T>
inline
void MatrixStorage<M, N, T>::reserve(std::size_t p_size)
{
}

template <std::size_t M, std::size_t N, typename T>
inline
const T * MatrixStorage<M, N, T>::ptr() const
{
	return m_elements;
}

template <std::size_t M, std::size_t N, typename T>
inline
T * MatrixStorage<M, N, T>::ptr()
{
	return m_elements;
}

template <std::size_t M, std::size_t N, typename T>
inline
T MatrixStorage<M, N, T>::element(std::size_t i) const
{
	GPX_ASSERT(i < size(), "element out of bounds");
	return m_elements[i];
}

template <std::size_t M, std::size_t N, typename T>
inline
T & MatrixStorage<M, N, T>::element(std::size_t i)
{
	GPX_ASSERT(i < size(), "element out of bounds");
	return m_elements[i];
}

template <std::size_t M, std::size_t N, typename T>
inline
void MatrixStorage<M, N, T>::swapRows(std::size_t r1, std::size_t r2)
{
	for (std::size_t c = 0; c < cols(); c++)
		std::swap(m_elements[c * rows() + r1], m_elements[c * rows() + r2]);
}

template <std::size_t M, std::size_t N, typename T>
inline
void MatrixStorage<M, N, T>::swapCols(std::size_t c1, std::size_t c2)
{
	for (std::size_t r = 0; r < rows(); r++)
		std::swap(m_elements[c1 * rows() + r], m_elements[c2 * rows() + r]);
}

//M = SIZE_DYNAMIC, N = SIZE_DYNAMIC

template <typename T>
inline
MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::MatrixStorage(std::size_t p_reserve):
	m_rows(0),
	m_cols(0),
	m_reserve(p_reserve)
{
	m_elements = new T[reserve()];
}

template <typename T>
inline
MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::MatrixStorage(std::size_t p_rows, std::size_t p_cols, std::size_t p_reserve):
	m_rows(p_rows),
	m_cols(p_cols),
	m_reserve(p_reserve)
{
	m_elements = new T[std::max(size(), reserve())];
	for (std::size_t i = 0; i < size(); i++)
		m_elements[i] = T();
}

template <typename T>
inline
MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::MatrixStorage(const MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & other):
	m_rows(other.rows()),
	m_cols(other.cols()),
	m_reserve(other.reserve())
{
	m_elements = new T[std::max(size(), reserve())];
	for (std::size_t i = 0; i < size(); i++)
		m_elements[i] = other.element(i);
}

template <typename T>
template <std::size_t OM, std::size_t ON>
inline
MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::MatrixStorage(const MatrixStorage<OM, ON, T> & other, std::size_t p_reserve):
	m_rows(other.rows()),
	m_cols(other.cols()),
	m_reserve(p_reserve)
{
	m_elements = new T[std::max(size(), reserve())];
	for (std::size_t i = 0; i < size(); i++)
		m_elements[i] = other.element(i);
}

template <typename T>
inline
MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::MatrixStorage(const T * elements, std::size_t p_rows, std::size_t p_cols, std::size_t p_reserve):
	m_rows(p_rows),
	m_cols(p_cols),
	m_reserve(p_reserve)
{
	m_elements = new T[std::max(size(), reserve())];
	for (std::size_t i = 0; i < size(); i++)
		m_elements[i] = elements[i];
}

template <typename T>
inline
MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::MatrixStorage(T d, std::size_t p_rows, std::size_t p_cols, std::size_t p_reserve):
	m_rows(p_rows),
	m_cols(p_cols),
	m_reserve(p_reserve)
{
	m_elements = new T[std::max(size(), reserve())];
	for (std::size_t i = 0; i < size(); i++)
		m_elements[i] = T();
	for (std::size_t i = 0; i < std::min(rows(), cols()); i++)
		m_elements[rows() * i + i] = d;
}

template <typename T>
inline
MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::~MatrixStorage()
{
	delete[] m_elements;
}

template <typename T>
inline
void MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::operator =(const MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> & other)
{
	//handle self assignment
	if (& other == this)
		return;

	resize(other.rows(), other.cols());
	for (std::size_t i = 0; i < size(); i++)
		m_elements[i] = other.element(i);
}

template <typename T>
template <std::size_t OM, std::size_t ON>
inline
void MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::operator =(const MatrixStorage<OM, ON, T> & other)
{
	resize(other.rows(), other.cols());
	for (std::size_t i = 0; i < size(); i++)
		m_elements[i] = other.element(i);
}

template <typename T>
inline
std::size_t MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::rows() const
{
	return m_rows;
}

template <typename T>
inline
std::size_t MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::cols() const
{
	return m_cols;
}

template <typename T>
inline
std::size_t MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::size() const
{
	return rows() * cols();
}

template <typename T>
inline
void MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::resize(std::size_t p_rows, std::size_t p_cols)
{
	//grow or shrink
	if (std::max(p_rows * p_cols, size()) > reserve()) {
		delete[] m_elements;
		m_elements = new T[std::max(p_rows * p_cols, reserve())];
	}
	m_rows = p_rows;
	m_cols = p_cols;
}

template <typename T>
inline
std::size_t MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::reserve() const
{
	return m_reserve;
}

template <typename T>
inline
void MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::reserve(std::size_t p_size)
{
	if (p_size <= size()) {
		m_reserve = p_size;
		return;
	}
	T * newElements = new T[p_size];
	for(std::size_t i = 0; i < size(); i++)
		newElements[i] = m_elements[i];
	delete[] m_elements;
	m_elements = newElements;
	m_reserve = p_size;
}

template <typename T>
inline
const T * MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::ptr() const
{
	return m_elements;
}

template <typename T>
inline
T * MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::ptr()
{
	return m_elements;
}

template <typename T>
inline
T MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::element(std::size_t i) const
{
	GPX_ASSERT(i < size(), "element out of bounds");
	return m_elements[i];
}

template <typename T>
inline
T & MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::element(std::size_t i)
{
	GPX_ASSERT(i < size(), "element out of bounds");
	return m_elements[i];
}

template <typename T>
inline
void MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::swapRows(std::size_t r1, std::size_t r2)
{
	for (std::size_t c = 0; c < cols(); c++)
		std::swap(m_elements[c * rows() + r1], m_elements[c * rows() + r2]);
}

template <typename T>
inline
void MatrixStorage<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T>::swapCols(std::size_t c1, std::size_t c2)
{
	for (std::size_t r = 0; r < rows(); r++)
		std::swap(m_elements[c1 * rows() + r], m_elements[c2 * rows() + r]);
}

}
}
}

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
