#include<iostream>
#include <time.h>
using namespace std;

template<class T>
class point{
public:
	T x;
	T y;
	T z;

	point() {
		x = 0;
		y = 0;
		z = 0;
	}

	point(T i) {  x = i; y = i; z = i;  }

	point<T> operator+(const point<T>& m)const {
		try {
			point<T> v;
			v.x = x + m.x;
			if ((x >= 0) && (m.x >= 0)) {
				if ((v.x < x) || (v.x < m.x))
					throw - 3;
			}
			if ((x < 0) && (m.x < 0)) {
				if ((v.x > x) || (v.x > m.x))
					throw - 3;
			}
			v.y = y + m.y;
			if ((y >= 0) && (m.y >= 0)) {
				if ((v.y < y) || (v.y < m.y))
					throw - 3;
			}
			if ((y < 0) && (m.y < 0)) {
				if ((v.y > y) || (v.y > m.y))
					throw - 3;
			}
			v.z = z + m.z;
			if ((z >= 0) && (m.z >= 0)) {
				if ((v.z < z) || (v.z < m.z))
					throw - 3;
			}
			if ((z < 0) && (m.z < 0)) {
				if ((v.z > z) || (v.z > m.z))
					throw - 3;
			}
			return v;
		}
		catch (int i) {
			cout << "Error ¹" << i << " stackoverflow" << endl;
			return *this;
		}
	}

	point& operator = (const point<T>& a) {
		x = a.x;
		y = a.y;
		z = a.z;
		return *this;
	}

	friend ostream& operator << (ostream& out, point<T>& n) {
		out << '{' << n.x << ' ' << n.y << ' ' << n.z << '}';
		return out;
	}

	bool operator >(const point<T> a) const {
		return (x + y + z) > (a.x + a.y + a.z);
	}

	bool operator >=(const point<T> a) const {
		return (x + y + z) >= (a.x + a.y + a.z);
	}

	bool operator <(const point<T> a) const {
		return (x + y + z) > (a.x + a.y + a.z);
	}
};

template<class T>
class Matrix {
private:
	T** matrix;
	T* raw_matrix;
	size_t row;
	size_t column;
public:
	Matrix(size_t rows, size_t columns, bool k) {
		row = rows;
		column = columns;
		try { matrix = new T * [row]; }
		catch (bad_alloc& ba) {
			throw bad_alloc(ba);
		}
		try { raw_matrix = new T[row * column]; }
		catch (bad_alloc& ba) {
			delete[] matrix;
			throw bad_alloc(ba);
		}
		for (size_t i = 0; i < row; i++)
			matrix[i] = raw_matrix + i * column;
		for (size_t i = 0; i < row; i++) {
			for (size_t j = 0; j < column; j++)
				matrix[i][j] = k;
		}
	}

	Matrix(size_t rows, size_t columns) {
		row = rows;
		column = columns;
		try { matrix = new T * [row]; }
		catch (bad_alloc& ba) {
			throw bad_alloc(ba);
		}
		try { raw_matrix = new T[row * column]; }
		catch (bad_alloc& ba) {
			delete[] matrix;
			throw bad_alloc(ba);
		}
		for (size_t i = 0; i < row; i++)
			matrix[i] = raw_matrix + i * column;
		srand((unsigned int)time(0));
		for (size_t i = 0; i < row; i++) {
			for (size_t j = 0; j < column; j++) {
				matrix[i][j] = (rand() % (100 * 2)) - 100;
			}
		}
	}

	Matrix(const Matrix& a) {
		*this = a;
	}

	Matrix& operator = (const Matrix<T>& a) {
		if (&a == this) return *this;
		row = a.row;
		column = a.column;
		delete[] raw_matrix;
		delete[] matrix;
		try { matrix = new T * [row]; }
		catch (bad_alloc& ba) {
			throw bad_alloc(ba);
		}
		try { raw_matrix = new T[row * column]; }
		catch (bad_alloc& ba) {
			delete[] matrix;
			throw bad_alloc(ba);
		}
		for (size_t i = 0; i < row; i++)
			matrix[i] = raw_matrix + i * column;
		for (size_t i = 0; i < row; i++) {
			for (size_t j = 0; j < column; j++)
				matrix[i][j] = a.matrix[i][j];
		}
		return *this;
	}

	friend ostream& operator << (ostream& out, Matrix<T>& n) {
		for (size_t i = 0; i < n.row; i++) {
			for (size_t j = 0; j < n.column; j++)
				out << n.matrix[i][j] << " ";
			out << "\n";
		}
		return out;
	}

	void set(size_t i, size_t j, T k) {
		try {
			if ((i >= row) || (j >= column))
				throw - 2;
			matrix[i][j] = k;
		}
		catch (int i) {
			cout << "Error ¹" << i << " index too big!" << endl;
			return;
		}
	}

	T get(const size_t i, const size_t j) const{
		try {
			if ((i >= row) || (j >= column))
				throw - 2;
		}
		catch (int i) {
			cout << "Error ¹" << i << " index too big" << endl;
			return;
		}
		return matrix[i][j];
	}

	void rows(const size_t k) {
		try {
			if (k >= row)
				throw - 2;
		}
		catch (int i) {
			cout << "Error ¹" << i << " index too big" << endl;
			return ;
		}
		for (int i = 0; i < column; i++) {
			cout << matrix[k][i];
		}
	}

	void columns(const size_t k) {
		try {
			if (k >= column)
				throw - 2;
		}
		catch (int i) {
			cout << "Error ¹" << i << " index too big" << endl;
			return ;
		}
		for (int i = 0; i < row; i++) {
			cout << matrix[i][k];
		}
	}

	Matrix operator+(const Matrix<T>& m)const {
		try {
			if ((row == m.row) && (column == m.column)) {
				Matrix<T> v(row, column);
				for (size_t i = 0; i < row; i++) {
					for (size_t j = 0; j < column; j++) {
						v.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
						/*if ((matrix[i][j] >= 0) && (m.matrix[i][j] >= 0)) {
							if ((v.matrix[i][j] < matrix[i][j]) || (v.matrix[i][j] < m.matrix[i][j]))
								throw - 3;
						}
						if ((matrix[i][j] < 0) && (m.matrix[i][j] < 0)) {
							if ((v.matrix[i][j] > matrix[i][j]) || (v.matrix[i][j] > m.matrix[i][j]))
								throw - 3;
						}*/
					}
				}
				return v;
			}
			else {
				throw - 1;
			}
		}
		catch (int i) {
			/*if (i == -3)
				cout << "Error ¹" << i << " stackoverflow" << endl;*/
			if (i == -1)
				cout << "Error ¹" << i << " different size" << endl;
			return *this;
		}
	}

	~Matrix() {
		delete[] raw_matrix;
		delete[] matrix;
	}
};

int main() {
	//Matrix <point<int>> test(3, 5, 1);
	//Matrix <point<int>> test2(3, 5, 1);
	Matrix <int> a(3, 2, 1);
	Matrix <int> b(3, 2, 0);
	Matrix <int> c(4, 4, 0);
	cout << a;
	//test.set(1, 1, 1);
	//auto test3 = test + test2;
	//cout << test3;
	/*a.set(1, 1);
	b.set(1, 1);
	c = b + a;
	int k = c.get(2, 2);
	cout << k << endl;
	cout << c;*/
	return 0;
}

//#4 #10 #12 #13 #14 #18 #21 #31