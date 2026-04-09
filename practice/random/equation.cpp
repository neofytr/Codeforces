#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define double long double

// r + r^4 = c

double f(double x, double c) {
	return x * x * x * x + x <= c;
}

int32_t main() {
	double c;
	cin >> c;

	double left = 0;
	double right = 1e3;

	for (int r = 1; r <= 100; r++) {
		double mid = left + (right - left) / 2;
		if (f(mid, c))
			left = mid;
		else 
			right = mid;
	}

	cout << setprecision(24) << left * left << endl;
	return 0;
}