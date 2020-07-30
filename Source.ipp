#ifdef Header
template<class T>
void Matrix<T>::input() {
	matrix = new T * [row];
	try { matrix[0] = new T[row * column]; }
	catch (bad_alloc) {
		delete[] matrix;
		matrix = nullptr;
		throw;
	}
	if ((((row * column) / row) != column) || (((row * column) / column) != row))
		throw overflow_error("Error");
	for (size_t i = 0; i < row; i++)
		matrix[i] = matrix[0] + i * column;
}

template<class T>
inline Matrix<T>::Matrix(size_t rows, size_t columns, T value) {
	row = rows;
	column = columns;
	input();
	fill_n(matrix[0], row * column, value);
}

template<class T>
Matrix<T>::Matrix(size_t rows, size_t columns) {
	row = rows;
	column = columns;
	input();
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
	input();
	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < column; j++)
			matrix[i][j] = a.matrix[i][j];
	}
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
	input();
	for (size_t i = 0; i < row; i++) {
		for (size_t j = 0; j < column; j++)
			matrix[i][j] = a.matrix[i][j];
	}
	return *this;
}

//template<class T>
//ostream& operator << (ostream& out, Matrix<T>& n) {
//	for (size_t i = 0; i < n.get_row(); i++) {
//		for (size_t j = 0; j < n.get_column(); j++)
//			out << n.get(i, j) << " ";
//		out << "\n";
//	}
//	return out;
//}

template<class T>
void Matrix<T>::set(size_t i, size_t j, T k) {
	try {
		if ((i >= row) || (j >= column))
			throw (invalid_argument("Wrong index!"));
		matrix[i][j] = k;
	}
	catch (invalid_argument) {
		throw (invalid_argument("Wrong index!"));
	}
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
	if (k < row) {
		for (size_t i = 0; i < row; i++)
			cout << matrix[i][k] << " ";
	}
	else
		throw (invalid_argument("Wrong index"));
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m)const {
	if ((row == m.row) && (column == m.column)) {
		Matrix<T> v(row, column);
		for (size_t i = 0; i < row; i++) {
			for (size_t j = 0; j < column; j++) {
				v.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
			}
		}
		return v;
	}
	else {
		throw (invalid_argument("Different size!"));
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