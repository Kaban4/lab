#include<iostream>
#include <time.h>
using namespace std;

class point {
private:
	int x;
	int y;
	int z;
	void check(int sum,int i, int j) const{
		if ((i >= 0) && (j >= 0)) {
			if ((sum < i) || (sum < j))
				throw (out_of_range("Stackoverflow!"));
		}
		if ((i < 0) && (j < 0)) {
			if ((sum > i) || (sum > j))
				throw (out_of_range("Stackoverflow!"));
		}
	}
public:
	point() {
		x = 0;
		y = 0;
		z = 0;
	}

	point(int i) { x = i; y = i; z = i; }

	point operator+(const point& m)const {
		try {
			point v;
			v.x = x + m.x;
			check(v.x, x, m.x);
			v.y = y + m.y;
			check(v.y, y, m.y);
			v.z = z + m.z;
			check(v.z, z, m.z);
			return v;
		}
		catch (out_of_range) {
			throw (out_of_range("Stackoverflow!"));
		}
	}

	point& operator = (const point& a) {
		x = a.x;
		y = a.y;
		z = a.z;
		return *this;
	}

	bool operator >(const point a) const {
		return (x + y + z) > (a.x + a.y + a.z);
	}

	bool operator >=(const point a) const {
		return (x + y + z) >= (a.x + a.y + a.z);
	}

	bool operator <(const point a) const {
		return (x + y + z) > (a.x + a.y + a.z);
	}

	int get_x() {
		return x;
	}

	int get_y() {
		return y;
	}

	int get_z() {
		return z;
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
			matrix = nullptr;
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
			matrix = nullptr;
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
		row = a.row;
		column = a.column;
		try { matrix = new T * [row]; }
		catch (bad_alloc& ba) {
			throw bad_alloc(ba);
		}
		try { raw_matrix = new T[row * column]; }
		catch (bad_alloc& ba) {
			delete[] matrix;
			matrix = nullptr;
			throw bad_alloc(ba);
		}
		for (size_t i = 0; i < row; i++)
			matrix[i] = raw_matrix + i * column;
		for (size_t i = 0; i < row; i++) {
			for (size_t j = 0; j < column; j++)
				matrix[i][j] = a.matrix[i][j];
		}
	}

	Matrix& operator = (const Matrix<T>& a) {
		if (&a == this) return *this;
		row = a.row;
		column = a.column;
		delete[] raw_matrix;
		raw_matrix = nullptr;
		delete[] matrix;
		matrix = nullptr;
		try { matrix = new T * [row]; }
		catch (bad_alloc& ba) {
			throw bad_alloc(ba);
		}
		try { raw_matrix = new T[row * column]; }
		catch (bad_alloc& ba) {
			delete[] matrix;
			matrix = nullptr;
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
				throw (invalid_argument("Wrong index!"));
			matrix[i][j] = k;
		}
		catch (invalid_argument) {
			throw (invalid_argument("Wrong index!"));
		}
	}

	T get(const size_t i, const size_t j) const {
		try {
			if ((i >= row) || (j >= column))
				throw (invalid_argument("Wrong index!"));
		}
		catch (invalid_argument) {
			throw (invalid_argument("Wrong index!"));
		}
		return matrix[i][j];
	}

	size_t get_row() const {
		return row;
	}

	size_t get_column() const {
		return column;
	}

	void rows(const size_t k) {
		if (k < row) {
			for (size_t i = 0; i < column; i++)
				cout << matrix[k][i] << " ";
		}
		else
			throw (invalid_argument("Wrong index!"));
	}

	void columns(const size_t k) {
		if (k < row) {
			for (size_t i = 0; i < row; i++)
				cout << matrix[i][k] << " ";
		}
		else
			throw (invalid_argument("Wrong index"));
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
		raw_matrix = nullptr;
		delete[] matrix;
		matrix = nullptr;
	}
};

 ostream& operator << (ostream& out, point& n) {
	out << '{' << n.get_x() << ' ' << n.get_y() << ' ' << n.get_z() << '}';
	return out;
}

int main() {
	try {
		Matrix <point> test(3, 5, 1);
		Matrix <point> test2(3, 5, 1);
		Matrix <point> test3(3, 2, 1);
		Matrix <int> a(3, 2, 1);
		Matrix <int> b(2, 2, 0);
		Matrix <int> c(2, 2, 0);
		a.rows(1);
		cout << "\n\n";
		a.columns(1);
		cout << "\n\n";
		a.set(1, 1, 4);
		a.get(1, 1);
		cout << a << "\n";
		test.set(1, 1, 1);
		test3 = test + test2;
		cout << test3;//-----------------------------------------
		//b.set(1, 1);
		//c = b + a;
		//int k = c.get(2, 2);
		//cout << k << endl;
		//cout << c;
	}
	catch(runtime_error& e){
		cerr << e.what();
	}
	catch (logic_error& e) {
		cerr << e.what();
	}
	catch (bad_alloc& e) {
		cerr << e.what();
	}
	return 0;
}

// #6 #7 #8 #11 #17 #20 #22 #25 #28  