#ifndef Header
#define Header
#include<iostream>
#include<math.h>
#include<time.h>

using namespace std;
template<class T>
class Matrix {
private:
	T** matrix;
	size_t row;
	size_t column;
	void create();
public:
	Matrix(size_t rows, size_t columns, T value);
	Matrix(size_t rows, size_t columns);
	Matrix(const Matrix& a);
	Matrix& operator = (const Matrix<T>& a);
	//friend ostream& operator << (ostream& out, Matrix<T>& n);
	void set(size_t i, size_t j, T k);
	T get(const size_t i, const size_t j) const;
	size_t get_row() const;
	size_t get_column() const;
	void rows(const size_t k);
	void columns(const size_t k);
	Matrix operator+(const Matrix<T>& m)const;
	~Matrix();
};


#include"Source.ipp"
#endif



