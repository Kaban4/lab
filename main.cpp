#include"Header.h"

class point {
private:
	int x;
	int y;
	int z;
	void check(int sum, int i, int j) const;
public:
	point();
	point(int i);
	point operator+(const point& m)const;
	point& operator = (const point& a);
	int get_x();
	int get_y();
	int get_z();
};

void point::check(int sum, int i, int j) const {
	if ((i >= 0) && (j >= 0)) {
		if ((sum < i) || (sum < j))
			throw (out_of_range("Stackoverflow!"));
	}
	if ((i < 0) && (j < 0)) {
		if ((sum > i) || (sum > j))
			throw (out_of_range("Stackoverflow!"));
	}
}

point::point() {
	x = 0;
	y = 0;
	z = 0;
}

point::point(int i) { x = i; y = i; z = i; }

point point::operator+(const point& m)const {
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

point& point:: operator = (const point& a) {
	x = a.x;
	y = a.y;
	z = a.z;
	return *this;
}

//bool operator >(const point a) const {
//	return (x + y + z) > (a.x + a.y + a.z);
//}

//bool operator >=(const point a) const {
//	return (x + y + z) >= (a.x + a.y + a.z);
//}

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
		Matrix <point> test(3, 5, 1);
		Matrix <point> test2(3, 5, 1);
		Matrix <point> test3(3, 2, 1);
		Matrix <int> a(3, 2);
		Matrix <int> b(5, 9, 5);
		Matrix <int> c(2, 2, 0);
		a.rows(1);
		//cout << "\n\n";
		a.columns(1);
		//cout << "\n\n";
		//a.set(1, 1, 'k');
		//a.get(1, 1);
		//cout << b << "\n";
		//test.set(1, 1, 1);
		//test3 = test + test2;
		//cout << test3;//-----------------------------------------
		//c = b + a;
		//int k = c.get(2, 2);
		//cout << k << endl;
		//cout << c;
	}
	catch (runtime_error& e) {
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
