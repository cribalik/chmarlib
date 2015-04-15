/*
 * matrix.h
 *
 *      Author: Christopher Mårtensson
 */

#ifndef CMARTE_MATRIX_H_
#define CMARTE_MATRIX_H_ 1

#include <algorithm>
#include <ostream>

namespace matrix {

template<class T> class Matrix;
template<class T> std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);

/* @summary: a tight 2 dimensional matrix with static size
 * @Constructor: Matrix(N,M) creates a N-row, N-column matrix 
 * @operator(): m(i,j) gets the element on the ith row and jth column
 * 
 * @efficiency: the elements are stored in row order, i.e. iterating through elements is fastest when going through a row at a time
 *				example: for (j = 0:M) m(i,j) 
 */
template<class T>
class Matrix {
	std::size_t colsize;
	T* _data, *_end;
public:
	Matrix(std::size_t N, std::size_t M) noexcept : colsize(M), _data(new T[N*M]), _end(_data + (N*M)) {}
	Matrix(std::size_t N, std::size_t M, const T& t) noexcept : colsize(M), _data(new T[N*M]), _end(_data + (N*M)) {
		std::fill(_data, _end, t);
	}
	Matrix(const Matrix& m) noexcept : colsize(m.colsize), _data(new T[ m._end - m._data ]), _end(_data + (m._end - m._data)) {
		std::copy(m._data, m._end, _data);
	}
	Matrix(Matrix&& m) noexcept : colsize(m.colsize), _data(m._data), _end(m._end) {
		m._data = m._end = NULL;
	}
	Matrix& operator= (const Matrix& m) noexcept {
		std::copy(m._data, m._end, _data);
	}
	void fill(const T& t) {std::fill(_data, _end, t);}
	std::size_t rows() const noexcept {return (_end-_data)/colsize;}
	std::size_t cols() const noexcept {return colsize;}
	T* operator[] (std::size_t i) noexcept {return _data + i*colsize;}
	const T* operator[] (std::size_t i) const noexcept {return _data + i*colsize;}
	T& operator() (std::size_t i, std::size_t j) noexcept {return _data[i*colsize + j];}
	const T& operator() (std::size_t i, std::size_t j) const noexcept {return _data[i*colsize + j];}
	~Matrix() noexcept {delete [] _data;}

private:
	friend std::ostream& operator<< <>(std::ostream& os, const Matrix<T>& m);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m){
	for (std::size_t i = 0, rows = m.rows(); i < rows; ++i){
		for (std::size_t j = 0, cols = m.cols(); j < cols; ++j)
			os << m(i,j) << ' ';
		os << '\n';
	}
	return os;
}


} /* namespace Matrix */

#endif