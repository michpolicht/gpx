/**
 * @file
 * @brief .
 */

#include <algorithm>

namespace gpx {
namespace math {
namespace basic {

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
const typename Matrix<M, N, T, DIMSPEC>::Parent & Matrix<M, N, T, DIMSPEC>::storage() const
{
	return *this;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T, DIMSPEC>::Matrix(std::size_t reserve):
	Parent(reserve)
{
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T, DIMSPEC>::Matrix(std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(rows, cols, reserve)
{
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T, DIMSPEC>::Matrix(const Matrix<M, N, T, DIMSPEC> & other):
	Parent(other.storage())
{
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t OM, std::size_t ON>
inline
Matrix<M, N, T, DIMSPEC>::Matrix(const Matrix<OM, ON, T, DIMSPEC> & other, std::size_t reserve):
	Parent(other.storage(), reserve)
{
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T, DIMSPEC>::Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(elements, rows, cols, reserve)
{
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
Matrix<M, N, T, DIMSPEC>::Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(d, rows, cols, reserve)
{
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
std::size_t Matrix<M, N, T, DIMSPEC>::rows() const
{
	return Parent::rows();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
std::size_t Matrix<M, N, T, DIMSPEC>::cols() const
{
	return Parent::cols();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
std::size_t Matrix<M, N, T, DIMSPEC>::size() const
{
	return Parent::size();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::resize(std::size_t rows, std::size_t cols)
{
	Parent::resize(rows, cols);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
std::size_t Matrix<M, N, T, DIMSPEC>::reserve() const
{
	return Parent::reserve();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::reserve(std::size_t size)
{
	Parent::reserve(size);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
const T * Matrix<M, N, T, DIMSPEC>::ptr() const
{
	return Parent::ptr();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
T * Matrix<M, N, T, DIMSPEC>::ptr()
{
	return Parent::ptr();
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
const T * Matrix<M, N, T, DIMSPEC>::ptr(std::size_t i, std::size_t j) const
{
	return (ptr() + j * rows() + i);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
T * Matrix<M, N, T, DIMSPEC>::ptr(std::size_t i, std::size_t j)
{
	return (ptr() + j * rows() + i);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::operator =(const Matrix<M, N, T, DIMSPEC> & other)
{
	//self assignment branch not required here
	Parent::operator =(other.storage());
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t OM, std::size_t ON>
inline
void Matrix<M, N, T, DIMSPEC>::operator =(const Matrix<OM, ON, T, DIMSPEC> & other)
{
	//self assignment branch not required here
	Parent::operator =(other.storage());
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::operator =(const T * elements)
{
	//self assignment branch not required here
	for (std::size_t i = 0; i < size(); i++)
		Parent::element(i) = elements[i];
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::operator =(T val)
{
	//self assignment branch not required here
	for (std::size_t i = 0; i < size(); i++)
		Parent::element(i) = T();
	if (val == T())
		return;
	for (std::size_t i = 0; i < std::min(rows(), cols()); i++)
		Parent::element(rows() * i + i) = val;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
T Matrix<M, N, T, DIMSPEC>::operator()(std::size_t i, std::size_t j) const
{
	return Parent::element(j * rows() + i);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
T & Matrix<M, N, T, DIMSPEC>::operator()(std::size_t i, std::size_t j)
{
	return Parent::element(j * rows() + i);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::operator ==(const gpx::math::Matrix<M, N, T> & other) const
{
	return std::equal(ptr(), ptr() + size(), other.ptr());
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::operator ==(T val) const
{
	//diagonal
	for (std::size_t i = 0; i < std::min(rows(), cols()); i++)
		if (Parent::element(rows() * i + i) != val)
			return false;
	//lower triangle
	for (std::size_t i = 1; i < rows(); i++)
		for (std::size_t j = 0; j < std::min(i, cols()); j++)
			if (Parent::element(rows() * j + i) != T())
				return false;
	//upper triangle
	for (std::size_t j = 1; j < cols(); j++)
		for (std::size_t i = 0; i < std::min(j, rows()); i++)
			if (Parent::element(rows() * j + i) != T())
				return false;
	return true;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::ape(const gpx::math::Matrix<M, N, T> & other) const
{
	for (std::size_t i = 0; i < size(); i++)
		if (!gpx::math::ape(Parent::element(i), other.element(i)))
			return false;
	return true;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::ape(T val) const
{
	//diagonal
	for (std::size_t i = 0; i < std::min(rows(), cols()); i++)
		if (!gpx::math::ape(Parent::element(rows() * i + i), val))
			return false;
	//lower triangle
	for (std::size_t i = 1; i < rows(); i++)
		for (std::size_t j = 0; j < std::min(i, cols()); j++)
			if (!gpx::math::ape(Parent::element(rows() * j + i), T()))
				return false;
	//upper triangle
	for (std::size_t j = 1; j < cols(); j++)
		for (std::size_t i = 0; i < std::min(j, rows()); i++)
			if (!gpx::math::ape(Parent::element(rows() * j + i), T()))
				return false;
	return true;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::ale(const gpx::math::Matrix<M, N, T> & other) const
{
	for (std::size_t i = 0; i < rows() * cols(); i++)
		if (!gpx::math::ale(Parent::element(i), other.element(i)))
			return false;
	return true;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::ale(T val) const
{
	//diagonal
	for (std::size_t i = 0; i < std::min(rows(), cols()); i++)
		if (!gpx::math::ale(Parent::element(rows() * i + i), val))
			return false;
	//lower triangle
	for (std::size_t i = 1; i < rows(); i++)
		for (std::size_t j = 0; j < std::min(i, cols()); j++)
			if (!gpx::math::ale(Parent::element(rows() * j + i), T()))
				return false;
	//upper triangle
	for (std::size_t j = 1; j < cols(); j++)
		for (std::size_t i = 0; i < std::min(j, rows()); i++)
			if (!gpx::math::ale(Parent::element(rows() * j + i), T()))
				return false;
	return true;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::operator !=(const gpx::math::Matrix<M, N, T> & other) const
{
	return !std::equal(ptr(), ptr() + size(), other.ptr());
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
bool Matrix<M, N, T, DIMSPEC>::operator !=(T val) const
{
	//diagonal
	for (std::size_t i = 0; i < std::min(rows(), cols()); i++)
		if (Parent::element(rows() * i + i) != val)
			return true;
	//lower triangle
	for (std::size_t i = 1; i < rows(); i++)
		for (std::size_t j = 0; j < std::min(i, cols()); j++)
			if (Parent::element(rows() * j + i) != T())
				return true;
	//upper triangle
	for (std::size_t j = 1; j < cols(); j++)
		for (std::size_t i = 0; i < std::min(rows(), j); i++)
			if (Parent::element(rows() * j + i) != T())
				return true;
	return false;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::add(const gpx::math::Matrix<M, N, T> & other)
{
	for (std::size_t i = 0; i < rows() * cols(); i++)
		Parent::element(i) += other.element(i);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::sub(const gpx::math::Matrix<M, N, T> & other)
{
	for (std::size_t i = 0; i < rows() * cols(); i++)
		Parent::element(i) -= other.element(i);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::mul(const gpx::math::Matrix<N, N, T> & other)
{
	Matrix<M, N, T, DIMSPEC> tmp(*this);	//temporal copy
	for (std::size_t r = 0; r < rows(); r++) {
		for (std::size_t c = 0; c < cols(); c++) {
			(*this)(r, c) = 0.0;
			for (std::size_t cr = 0; cr < cols(); cr++)
				(*this)(r, c) += tmp(r, cr) * other(cr, c);
		}
	}
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::mul(T val)
{
	for (std::size_t i = 0; i < rows() * cols(); i++)
		Parent::element(i) *= val;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Matrix<M, N, T> Matrix<M, N, T, DIMSPEC>::sum(const gpx::math::Matrix<M, N, T> & other) const
{
	gpx::math::Matrix<M, N, T> result(static_cast<const gpx::math::Matrix<M, N, T> & >(*this));
	result += other;
	return result;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Matrix<M, N, T> Matrix<M, N, T, DIMSPEC>::diff(const gpx::math::Matrix<M, N, T> & other) const
{
//	gpx::math::Matrix<M, N, T> result(this->ptr());
	gpx::math::Matrix<M, N, T> result(static_cast<const gpx::math::Matrix<M, N, T> & >(*this));
	result -= other;
	return result;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
template <std::size_t ON>
inline
gpx::math::Matrix<M, ON, T> Matrix<M, N, T, DIMSPEC>::prod(const gpx::math::Matrix<N, ON, T> & other) const
{
	gpx::math::Matrix<M, ON, T> result(T(), rows(), other.cols());
	for (std::size_t r = 0; r < rows(); r++) {
		for (std::size_t c = 0; c < other.cols(); c++) {
			for (std::size_t cr = 0; cr < cols(); cr++)
				result(r, c) += (*this)(r, cr) * other(cr, c);
		}
	}
	return result;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Vector<M, T> Matrix<M, N, T, DIMSPEC>::prod(gpx::math::const_VectorRef<N, T> vec) const
{
	gpx::math::Vector<M, T> result(rows());
	for (std::size_t r = 0; r < rows(); r++)
		for (std::size_t c = 0; c < cols(); c++)
			result(r) += (*this)(r, c) * vec(c);
	return result;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Matrix<M, N, T> Matrix<M, N, T, DIMSPEC>::prod(T val) const
{
	gpx::math::Matrix<M, N, T> result(static_cast<const gpx::math::Matrix<M, N, T> & >(*this));
	result *= val;
	return result;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
gpx::math::Matrix<N, M, T> Matrix<M, N, T, DIMSPEC>::transposed() const
{
	gpx::math::Matrix<N, M, T> result;
	result.resize(cols(), rows());	//should optimize out for sized matrix
	for (std::size_t i = 0; i < rows(); i++)
		for(std::size_t j = 0; j < cols(); j++)
			result(j, i) = (*this)(i, j);
	return result;
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::swapRows(std::size_t r1, std::size_t r2)
{
	Parent::swapRows(r1, r2);
}

template <std::size_t M, std::size_t N, typename T, bool DIMSPEC>
inline
void Matrix<M, N, T, DIMSPEC>::swapCols(std::size_t c1, std::size_t c2)
{
	Parent::swapCols(c1, c2);
}


// M = N

template <std::size_t N, typename T>
inline
Matrix<N, N, T, true>::Matrix(std::size_t reserve):
	Parent(reserve)
{
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T, true>::Matrix(std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(rows, cols, reserve)
{
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T, true>::Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(elements, rows, cols, reserve)
{
}

template <std::size_t N, typename T>
inline
Matrix<N, N, T, true>::Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(d, rows, cols, reserve)
{
}

template <std::size_t N, typename T>
inline
void Matrix<N, N, T, true>::operator =(const T * elements)
{
	Parent::operator =(elements);
}

template <std::size_t N, typename T>
inline
void Matrix<N, N, T, true>::operator =(T val)
{
	Parent::operator =(val);
}

template <std::size_t N, typename T>
inline
void Matrix<N, N, T, true>::transpose()
{
	T save;
	for (std::size_t i = 0; i < N; i++)
		for(std::size_t j = i + 1; j < N; j++)  {
			save = (*this)(i,j);
			(*this)(i,j) = (*this)(j,i);
			(*this)(j,i) = save;
		}
}

template <std::size_t N, typename T>
inline
void Matrix<N, N, T, true>::invert()
{
	gpx::math::Matrix<N, N, T> I(1.0); //identity matrix
	std::size_t index[N]; //index holds columns order

	for (std::size_t j = 0; j < N; j++)
		index[j] = j;

	//perform operations on col j (leading element(j,j))
	for (std::size_t j = 0; j < N; j++) {
		//find max pivot
		for (std::size_t jj = j + 1; jj < N; jj++)
			if (std::abs(this->ptr()[index[jj]*N + j]) > std::abs(this->ptr()[index[j]*N + j])) {
				//swap cols
				std::size_t swap = index[jj];
				index[jj] = index[j];
				index[j] = swap;
			}
		//divisor may be 0, then matrix is singular and function will fail
		T divisor = this->ptr()[index[j]*N + j];
		for (std::size_t i = 0; i < N; i++) {
			I.ptr()[index[j]*N + i] /= divisor;
			this->ptr()[index[j]*N + i] /= divisor;
		}
		for (std::size_t ii = 0; ii < N; ii++)
			if (ii != j) {
				T multiplier = this->ptr()[index[ii]*N + j];
				for (std::size_t i = 0; i < N; i++) {
					I.ptr()[index[ii]*N + i] -= multiplier * I.ptr()[index[j]*N + i];
					this->ptr()[index[ii]*N + i] -= multiplier * this->ptr()[index[j]*N + i];
				}
			}
	}
	//copy column by column
	for (std::size_t j = 0; j < N; j++)
		std::copy(& I.ptr()[index[j] * N], & I.ptr()[index[j] * N] + N, & this->ptr()[j * N]);
//		memcpy(& this->ptr()[j * N], & I.ptr()[index[j] * N], sizeof(T) * N);
}

template <std::size_t N, typename T>
inline
T Matrix<N, N, T, true>::det() const
{
	if (Parent::size() == 1)
		return Parent::element(0);
	return _det(this->ptr(), N);
}

template<std::size_t N, typename T>
inline
T Matrix<N, N, T, true>::_det(const T * elements, std::size_t size) const
{
	T result = T();
	T tmp[--size * size++];

	if (size == 2)
		return elements[0] * elements[3] - (elements[1] * elements[2]);
	for (std::size_t j = 0; j < size; j++) {
		for(std::size_t k = size, ctr = 0; k < size * size; k++)
			if (k % size != j)
				tmp[ctr++] = elements[k];
		result += elements[j] * ((j % 2) ? -1.0 : 1.0) * _det(tmp, size - 1);
	}
	return result;
}

//M = SIZE_DYNAMIC, N = SIZE_DYNAMIC

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::Matrix(std::size_t reserve):
	Parent(reserve)
{
}

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::Matrix(std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(rows, cols, reserve)
{
}

template <typename T>
template <std::size_t OM, std::size_t ON>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::Matrix(const Matrix<OM, ON, T> & other, std::size_t reserve):
	Parent(other, reserve)
{
}

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::Matrix(const T * elements, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(elements, rows, cols, reserve)
{
}

template <typename T>
inline
Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::Matrix(T d, std::size_t rows, std::size_t cols, std::size_t reserve):
	Parent(d, rows, cols, reserve)
{
}

template <typename T>
inline
void Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::operator =(const T * elements)
{
	Parent::operator =(elements);
}

template <typename T>
inline
void Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::operator =(T val)
{
	Parent::operator =(val);
}

template <typename T>
template <std::size_t OM, std::size_t ON>
inline
void Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::operator =(const Matrix<OM, ON, T> & other)
{
	Parent::operator =(other);
}

template <typename T>
inline
void Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::transpose()
{
	gpx::math::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> copy(static_cast<gpx::math::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> &>(*this));
	Parent::resize(Parent::cols(), Parent::rows());
	for (std::size_t i = 0; i < Parent::rows(); i++)
		for(std::size_t j = 0; j < Parent::cols(); j++)
			(*this)(i, j) = copy(j, i);
}

template <typename T>
inline
void Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::invert()
{
	//rows != cols may cause buffer overflow
	if (Parent::rows() != Parent::cols())
		return;

	gpx::math::Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T> I(1.0, Parent::rows(), Parent::cols()); //identity matrix
	std::size_t index[Parent::cols()]; //index holds columns order

	for (std::size_t j = 0; j < Parent::cols(); j++)
		index[j] = j;

	//perform operations on col j (leading element(j, j))
	for (std::size_t j = 0; j < Parent::cols(); j++) {
		//find max pivot
		for (std::size_t jj = j + 1; jj < Parent::cols(); jj++)
			if (std::abs(this->ptr()[index[jj] * Parent::cols() + j]) > std::abs(this->ptr()[index[j] * Parent::cols() + j])) {
				//swap cols
				std::size_t swap = index[jj];
				index[jj] = index[j];
				index[j] = swap;
			}
		//divisor may be 0, then matrix is singular and function will fail
		T divisor = this->ptr()[index[j] * Parent::cols() + j];
		for (std::size_t i = 0; i < Parent::cols(); i++) {
			I.ptr()[index[j] * Parent::cols() + i] /= divisor;
			this->ptr()[index[j] * Parent::cols() + i] /= divisor;
		}
		for (std::size_t ii = 0; ii < Parent::cols(); ii++)
			if (ii != j) {
				T multiplier = this->ptr()[index[ii] * Parent::cols() + j];
				for (std::size_t i = 0; i < Parent::cols(); i++) {
					I.ptr()[index[ii] * Parent::cols() + i] -= multiplier * I.ptr()[index[j] * Parent::cols() + i];
					this->ptr()[index[ii] * Parent::cols() + i] -= multiplier * this->ptr()[index[j] * Parent::cols() + i];
				}
			}
	}
	//copy column by column
	for (std::size_t j = 0; j < Parent::cols(); j++)
		std::copy(& I.ptr()[index[j] * Parent::cols()], & I.ptr()[index[j] * Parent::cols()] + Parent::cols(), & this->ptr()[j * Parent::cols()]);
//		memcpy(& this->ptr()[j * Parent::cols()], & I.ptr()[index[j] * Parent::cols()], sizeof(T) * Parent::cols());
}

template <typename T>
inline
T Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::det() const
{
	if (Parent::rows() != Parent::cols())
		return std::numeric_limits<T>::quiet_NaN();
	if (Parent::size() == 1)
		return Parent::element(0);
	return _det(this->ptr(), Parent::cols());
}

template <typename T>
inline
T Matrix<gpx::math::SIZE_DYNAMIC, gpx::math::SIZE_DYNAMIC, T, true>::_det(const T * elements, std::size_t size) const
{
	T result = T();
	T tmp[--size * size++];

	if (size == 2)
		return elements[0] * elements[3] - (elements[1] * elements[2]);
	for (std::size_t j = 0; j < size; j++) {
		for(std::size_t k = size, ctr = 0; k < size * size; k++)
			if (k % size != j)
				tmp[ctr++] = elements[k];
		result += elements[j] * ((j % 2) ? -1.0 : 1.0) * _det(tmp, size - 1);
	}
	return result;
}

}
}
}

//(c)MP: Copyright © 2012, Michał Policht. All rights reserved.
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
