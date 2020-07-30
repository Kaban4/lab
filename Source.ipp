#ifdef Header
template<class T>
void Matrix<T>::create() {
	matrix = new T * [row];
	try { 
		matrix[0] = new T[row * column];
		if ((((row * column) / row) != column) || (((row * column) / column) != row))
			throw overflow_error("Error");
	}
	catch (bad_alloc) {
		delete[] matrix;
		matrix = nullptr;
		throw;
	}
	catch (overflow_error) {
		delete[] matrix;
		matrix = nullptr;
		throw;
	}
	for (size_t i = 0; i < row; i++)
		matrix[i] = matrix[0] + i * column;
}

template<class T>
inline Matrix<T>::Matrix(size_t rows, size_t columns, T value) {
	row = rows;
	column = columns;
	create();
	fill_n(matrix[0], row * column, value);
}

template<class T>
Matrix<T>::Matrix(size_t rows, size_t columns) {
	row = rows;
	column = columns;
	create();
	srand((unsigned int)time(0));
	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < column; j++) {
			matrix[i][j] = (rand() % (100 * 2)) - 100;
		}
	}
}

template<class T>
Matrix<T>::Matrix(const Matrix& a) {
	row = a.row;
	column = a.column;
	create();
	size_t bound = row * column;
	for (size_t i = 0; i < bound; ++i)
		* (*matrix + i) = *(*a.matrix + i);
}

template<class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& a) {
	if (&a == this) return *this;
	row = a.row;
	column = a.column;
	delete[] matrix[0];
	matrix[0] = nullptr;
	delete[] matrix;
	matrix = nullptr;
	create();
	size_t bound = row * column;
	for (size_t i = 0; i < bound; ++i)
		*(*matrix + i) = *(*a.matrix + i);
	return *this;
}

//template<class T>
//ostream& operator << (ostream& out, Matrix<T>& n) {
//	for (size_t i = 0; i < n.row; i++) {
//		for (size_t j = 0; j < n.column; j++)
//			out << n.matrix[i][j] << " ";
//		out << "\n";
//	}
//	return out;
//}

template<class T>
void Matrix<T>::set(size_t i, size_t j, T k) {
	if ((i >= row) || (j >= column))
		throw (invalid_argument("Wrong index!"));
	matrix[i][j] = k;
}

template<class T>
T Matrix<T>::get(const size_t i, const size_t j) const {
	try {
		if ((i >= row) || (j >= column))
			throw (invalid_argument("Wrong index!"));
	}
	catch (invalid_argument) {
		throw (invalid_argument("Wrong index!"));
	}
	return matrix[i][j];
}

template<class T>
size_t Matrix<T>::get_row() const {
	return row;
}

template<class T>
size_t Matrix<T>::get_column() const {
	return column;
}

template<class T>
void Matrix<T>::rows(const size_t k) {
	if (k < row) {
		for (size_t i = 0; i < column; i++)
			cout << matrix[k][i] << " ";
	}
	else
		throw (invalid_argument("Wrong index!"));
}

template<class T>
void Matrix<T>::columns(const size_t k) {
	if (k < column) {
		for (size_t i = 0; i < row; i++)
			cout << matrix[i][k] << " ";
	}
	else
		throw (invalid_argument("Wrong index"));
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m)const {
	if ((row != m.row) || (column != m.column)) {
		throw (invalid_argument("Different size!")); 
	Matrix<T> v(row, column);
	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < column; j++) 
			v.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
	}
		return v;
	}
	return *this;
}

template<class T>
Matrix<T>::~Matrix() {
	delete[] matrix[0];
	matrix[0] = nullptr;
	delete[] matrix;
	matrix = nullptr;
}
#endif