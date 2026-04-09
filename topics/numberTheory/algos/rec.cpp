#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1000000000 + 7)
#define Mat vector<vector<int>>

// f(r) = 3 * f (r - 1) + 5 * f(r - 2) + 2 * f(r - 3) for r >= 4
// f(1) = 1, f(2) = 2 and f(3) = 3

// We are to find f(n) for any n >= 1 in O(log(n))

// we ensure that elements of matrix a and b are always stored modulo MOD
Mat mul(Mat &a, Mat &b) {
	// a -> n x m
	// b -> g x h

	int n = a.size();
	int m = a[0].size();

	int g = b.size();
	int h = b[0].size();

	if (m != g)
		return {};

	Mat res(n, vector<int>(h, 0));
	for (int row = 0; row < n; row++)
		for (int col = 0; col < h; col++) {
			int c = 0;
			for (int k = 0; k < m; k++) {
				c += ((a[row][k] % MOD) * (b[k][col] % MOD)) % MOD; 
				if (c >= MOD)
					c -= MOD;
			}
			res[row][col] = c;
		}
	return res;
}


Mat matpw(Mat base, int exp) {
	int n = base.size();
	Mat res(n, vector<int>(n, 0));
	for (int r = 0; r < n; r++)
		res[r][r] = 1;

	while(exp) {
		if (exp & 1)
			res = mul(res, base);
		base = mul(base, base);
		exp >>= 1;
	}
	return res;
}

int f(int n) {
	if (n < 0)
		return -1; // not defined

	if (n <= 3)
		return n;

	Mat T = {{0, 0, 2}, {1, 0, 5}, {0, 1, 3}};
	Mat a = {{1, 2, 3}};

	Mat res = matpw(T, n - 1);
	Mat fin = mul(a, res);
	return fin[0][0];
}

int32_t main() {
	int n;
	cin >> n;
	cout << f(n) << endl;
	return 0;
}