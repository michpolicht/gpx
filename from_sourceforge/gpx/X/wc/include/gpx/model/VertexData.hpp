#ifndef GPX_X_MODEL_VERTEXDATA_HPP_
#define GPX_X_MODEL_VERTEXDATA_HPP_

#include <algorithm>

#include "../platform.hpp"


namespace gpx {
namespace model {

/**
 * Vertex data.
 */
template <std::size_t DIM, typename T = real_t>
class VertexData
{
	template <typename IT_T>
	class Iterator;

	public:
		typedef Iterator<T> iterator;
		typedef Iterator<const T> const_iterator;

		VertexData();

		/**
		 * Constructor.
		 * @param data pointer to vertices data.
		 * @param num number of vertices (data size / DIM).
		 */
		VertexData(T * data, std::size_t num);

		/**
		 * Subscript operator.
		 * @param i subscript value.
		 * @return *pointer* to vertex specified by @a i.
		 */
		T * operator[](std::size_t i);

		/**
		 * Const version of subscript operator.
		 * @param i subscript value.
		 * @return *pointer* to vertex specified by @a i.
		 */
		const T * operator[](std::size_t i) const;

		/**
		 * Set data.
		 * @param data pointer to vertices data.
		 * @param num number of vertices (data size / DIM).
		 */
		void setData(T * data, std::size_t num);

		/**
		 * Copy data.
		 * @param data pointer to vertices data.
		 * @param num number of vertices to copy (data size / DIM).
		 *
		 * @warning size of copied data must not exceed the size of underlying vertex data
		 * container.
		 */
		void copyData(T * data, std::size_t num);

		/**
		 * Iterator begin.
		 * @return iterator begin.
		 */
		iterator begin();

		/**
		 * Const iterator begin.
		 * @return const iterator begin.
		 */
		const_iterator begin() const;

		/**
		 * Iterator end.
		 * @return iterator end.
		 */
		iterator end();

		/**
		 * Const iterator end.
		 * @return const iterator end.
		 */
		const_iterator end() const;

		/**
		 * Calculate distance between iterator begin and @a it.
		 * @param it iterator.
		 * @return distance between iterators.
		 */
		std::size_t distance(const iterator & it) const;
		std::size_t distance(const const_iterator & it) const;

		/**
		 * Get data.
		 * @return pointer to vertices data.
		 */
		T * data();

		/**
		 * Get const data.
		 * @return pointer to vertices data.
		 */
		const T * data() const;

		/**
		 * Get data size as number of data elements.
		 * @return data size (number of data elements).
		 */
		std::size_t size() const;

		/**
		 * Get data size in bytes.
		 * @return data size in bytes.
		 *
		 * @note byte is defined as sizeof(char) and char is not necessarily 8-bit.
		 */
		std::size_t bsize() const;

		/**
		 * Get number of vertices.
		 * @return number of vertices (size() / DIM).
		 */
		std::size_t num() const;

		/**
		 * Get dimensionality.
		 * @return number of dimensions.
		 */
		std::size_t dim() const;

	private:
		T * m_ptr;
		T * m_ptrEnd;
};

template <std::size_t DIM, typename T>
VertexData<DIM, T>::VertexData():
	m_ptr(0),
	m_ptrEnd(0)
{
}

template <std::size_t DIM, typename T>
VertexData<DIM, T>::VertexData(T * data, std::size_t num):
	m_ptr(data),
	m_ptrEnd(data + num * DIM)
{
}

template <std::size_t DIM, typename T>
T * VertexData<DIM, T>::operator[](std::size_t i)
{
	assert(m_ptr + (i * DIM) < m_ptrEnd); //out of bounds
	return m_ptr + (i * DIM);
}

template <std::size_t DIM, typename T>
const T * VertexData<DIM, T>::operator[](std::size_t i) const
{
	assert(m_ptr + (i * DIM) < m_ptrEnd); //out of bounds
	return m_ptr + (i * DIM);
}

template <std::size_t DIM, typename T>
void VertexData<DIM, T>::setData(T * data, std::size_t num)
{
	m_ptr = data;
	m_ptrEnd = data + num * DIM;
}

template <std::size_t DIM, typename T>
void VertexData<DIM, T>::copyData(T * data, std::size_t num)
{
	std::copy(data, data + num, m_ptr);
}

template <std::size_t DIM, typename T>
typename VertexData<DIM, T>::iterator VertexData<DIM, T>::begin()
{
	return iterator(m_ptr);
}

template <std::size_t DIM, typename T>
typename VertexData<DIM, T>::const_iterator VertexData<DIM, T>::begin() const
{
	return const_iterator(m_ptr);
}

template <std::size_t DIM, typename T>
typename VertexData<DIM, T>::iterator VertexData<DIM, T>::end()
{
	return iterator(m_ptrEnd);
}

template <std::size_t DIM, typename T>
typename VertexData<DIM, T>::const_iterator VertexData<DIM, T>::end() const
{
	return const_iterator(m_ptrEnd);
}

template <std::size_t DIM, typename T>
std::size_t VertexData<DIM, T>::distance(const iterator & it) const
{
	return (it.pos - m_ptr) / DIM;
}

template <std::size_t DIM, typename T>
std::size_t VertexData<DIM, T>::distance(const const_iterator & it) const
{
	return (it.pos - m_ptr) / DIM;
}

template <std::size_t DIM, typename T>
T * VertexData<DIM, T>::data()
{
	return m_ptr;
}

template <std::size_t DIM, typename T>
const T * VertexData<DIM, T>::data() const
{
	return m_ptr;
}

template <std::size_t DIM, typename T>
std::size_t VertexData<DIM, T>::size() const
{
	return m_ptrEnd - m_ptr;
}

template <std::size_t DIM, typename T>
std::size_t VertexData<DIM, T>::bsize() const
{
	return size() * sizeof(T);
}

template <std::size_t DIM, typename T>
std::size_t VertexData<DIM, T>::num() const
{
	return size() / DIM;
}

template <std::size_t DIM, typename T>
std::size_t VertexData<DIM, T>::dim() const
{
	return DIM;
}

/**
 * Vertex data iterator. Works similar to pointer, except that vertex data iterator jumps
 * over the data from vertex to vertex, considering @p DIM of enclosing class.
 */
template <std::size_t DIM, typename T>
template <typename IT_T>
class VertexData<DIM, T>::Iterator
{
	friend class VertexData<DIM, T>;

	public:
		Iterator();
		Iterator(IT_T * pos);

		IT_T * operator *() const;
		Iterator & operator++();
		Iterator operator++(int);
		Iterator & operator--();
		Iterator operator--(int);
		Iterator & operator+=(std::size_t n);
		Iterator & operator+=(int n);
		Iterator operator+(std::size_t n) const;
		Iterator operator+(int n) const;
		Iterator & operator-=(std::size_t n);
		Iterator & operator-=(int n);
		Iterator operator-(std::size_t n) const;
		Iterator operator-(int n) const;
//		IT_T & operator[](std::size_t i);
//		IT_T & operator[](int i);
		IT_T * operator[](std::size_t i) const;
		IT_T * operator[](int i) const;
	    bool operator==(const Iterator & other) const;
		bool operator!=(const Iterator & other) const;

	private:
		IT_T * pos;
};

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T>::Iterator():
	pos(0)
{
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T>::Iterator(IT_T * pos):
	pos(pos)
{
}

template <std::size_t DIM, typename T>
template <typename IT_T>
IT_T * VertexData<DIM, T>::Iterator<IT_T>::operator *() const
{
	return pos;
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> & VertexData<DIM, T>::Iterator<IT_T>::operator++()
{
	pos += DIM;
	return *this;
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> VertexData<DIM, T>::Iterator<IT_T>::operator++(int)
{
	Iterator tmp = *this;
	pos += DIM;
	return tmp;
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> & VertexData<DIM, T>::Iterator<IT_T>::operator--()
{
	pos -= DIM;
	return *this;
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> VertexData<DIM, T>::Iterator<IT_T>::operator--(int)
{
	Iterator tmp = *this;
	pos -= DIM;
	return tmp;
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> & VertexData<DIM, T>::Iterator<IT_T>::operator+=(std::size_t n)
{
	pos += DIM * n;
	return *this;
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> & VertexData<DIM, T>::Iterator<IT_T>::operator+=(int n)
{
	pos += DIM * n;
	return *this;
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> VertexData<DIM, T>::Iterator<IT_T>::operator+(std::size_t n) const
{
	return Iterator(pos + DIM * n);
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> VertexData<DIM, T>::Iterator<IT_T>::operator+(int n) const
{
	return Iterator(pos + DIM * n);
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> & VertexData<DIM, T>::Iterator<IT_T>::operator-=(std::size_t n)
{
	pos -= DIM * n;
	return *this;
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> & VertexData<DIM, T>::Iterator<IT_T>::operator-=(int n)
{
	pos -= DIM * n;
	return *this;
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> VertexData<DIM, T>::Iterator<IT_T>::operator-(std::size_t n) const
{
	return Iterator(pos - DIM * n);
}

template <std::size_t DIM, typename T>
template <typename IT_T>
VertexData<DIM, T>::Iterator<IT_T> VertexData<DIM, T>::Iterator<IT_T>::operator-(int n) const
{
	return Iterator(pos - DIM * n);
}

//template <std::size_t DIM, typename T>
//template <typename IT_T>
//IT_T & VertexData<DIM, T>::Iterator<IT_T>::operator[](std::size_t i)
//{
//	return pos[i];
//}
//
//template <std::size_t DIM, typename T>
//template <typename IT_T>
//IT_T & VertexData<DIM, T>::Iterator<IT_T>::operator[](int i)
//{
//	return pos[i];
//}

template <std::size_t DIM, typename T>
template <typename IT_T>
IT_T * VertexData<DIM, T>::Iterator<IT_T>::operator[](std::size_t i) const
{
	return pos + (i * DIM);
}

template <std::size_t DIM, typename T>
template <typename IT_T>
IT_T * VertexData<DIM, T>::Iterator<IT_T>::operator[](int i) const
{
	return pos + (i * DIM);
}

template <std::size_t DIM, typename T>
template <typename IT_T>
bool VertexData<DIM, T>::Iterator<IT_T>::operator==(const Iterator & other) const
{
	return pos == other.pos;
}

template <std::size_t DIM, typename T>
template <typename IT_T>
bool VertexData<DIM, T>::Iterator<IT_T>::operator!=(const Iterator & other) const
{
	return pos != other.pos;
}


}
}

#endif /* GPX_X_MODEL_VERTEXDATA_HPP_ */
