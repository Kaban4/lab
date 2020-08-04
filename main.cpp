#include"Header.h"

class point {
private:
	int x;
	int y;
	int z;
public:
	point();
	point(int x);
	point operator+(const point& m)const;
	point& operator = (const point& a);
	int get_x();
	int get_y();
	int get_z();
};

void check(const int sum, const int i, const int j) {
	if ((i >= 0) && (j >= 0)) {
		if ((sum < i) || (sum < j))
			throw (overflow_error("Overflow!"));
	}
	if ((i < 0) && (j < 0)) {
		if ((sum > i) || (sum > j))
			throw (overflow_error("Overflow!"));
	}
}

point::point() {
	x = 0;
	y = 0;
	z = 0;
}

point::point(int x) : x(x), y(x), z(x) {}

point point::operator+(const point& m)const {
	point v;
	v.x = x + m.x;
	check(v.x, x, m.x);
	v.y = y + m.y;
	check(v.y, y, m.y);
	v.z = z + m.z;
	check(v.z, z, m.z);
	return v;
}

point& point:: operator = (const point& a) {
	x = a.x;
	y = a.y;
	z = a.z;
	return *this;
}

//bool operator >(const point a) const {
//	return (x + y + z) > (a.x + a.y + a.z);
//}
//
//bool operator >=(const point a) const {
//	return (x + y + z) >= (a.x + a.y + a.z);
//}
//
//bool operator <(const point a) const {
//	int rez1 = 0, rez2 = 0;
//	rez1 = sqrt(x * x + y * y + z * z);
//	rez2 = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
//	return rez1 > rez2;
//}

int point::get_x() {
	return x;
}

int point::get_y() {
	return y;
}

int point::get_z() {
	return z;
}

ostream& operator << (ostream& out, point& n) {
	out << '{' << n.get_x() << ' ' << n.get_y() << ' ' << n.get_z() << '}';
	return out;
}


int main() {
	try {
		Matrix <point> test(2,2,1);
		Matrix <point> test2(2,2,1);
		Matrix <point> test3(2,2);
		Matrix <int> a(3, 2, 0);
		Matrix <int> b(3, 2, 5);
		Matrix <int> c(5, 9, 0);
		a.rows(1);
		cout << "\n\n";
		a.columns(1);
		cout << "\n\n";
		a.set(1, 1, 9);
		a.get(1, 1);
		cout << b << "\n";
		test.set(1, 1, 1);
		test3 = test + test2;
		cout << test3 << "\n";//-----------------------------------------
		c = b + a;
		//int k = c.get(2, 2);
		//cout << k << endl;
		cout << c;
	}
	catch (const exception e) {
		cerr << e.what();
	}

} //51 50 49 47 46 45
