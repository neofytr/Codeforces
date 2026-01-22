#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX_N (int)(5 * 1e2)
#define MAX_K (int)(1e2)
#define MAX_T (int) (MAX_N * MAX_K)

int k[MAX_N + 1];
int p[MAX_N + 1][MAX_K + 1];
int w[MAX_N + 1][MAX_K + 1];
int s[MAX_N + 1][MAX_K + 1];
int ord[MAX_N + 1][MAX_K + 1];
int ordsum[MAX_N + 1];
int cls[MAX_N + 1];
int wsum[MAX_N + 1];
int psum[MAX_N + 1];

int curr = -1;
auto cmpwithin = [](int one, int two) -> bool {
	int t1 = w[curr][one] * p[curr][one] + w[curr][two] * (p[curr][one] + p[curr][two]);
	int t2 = w[curr][two] * p[curr][two] + w[curr][one] * (p[curr][one] + p[curr][two]);
	if (t1 < t2) return true;
	return false;
};

auto cmp = [](int one, int two) -> bool {
	int t1 = ordsum[one] + psum[one] * wsum[two] + ordsum[two];
	int t2 = ordsum[two] + psum[two] * wsum[one] + ordsum[one];
	if (t1 < t2) return true;
	return false;
};

int32_t main() {
	// freopen("student.in", "r", stdin);
	// freopen("student.out", "w", stdout);

	int n;
	cin >> n;

	for (int c = 1; c <= n; c++)
		cin >> k[c];

	for (int c = 1; c <= n; c++)
		for (int l = 1; l <= k[c]; l++)
			cin >> p[c][l];

	for (int c = 1; c <= n; c++)
		for (int l = 1; l <= k[c]; l++)
			cin >> w[c][l];

	for (int c = 1; c <= n; c++) {
		wsum[c] = 0;
		for (int l = 1; l <= k[c]; l++)
			wsum[c] += w[c][l];
	}

	for (int c = 1; c <= n; c++) {
		psum[c] = 0;
		for (int l = 1; l <= k[c]; l++)
			psum[c] += p[c][l];
	}

	for (int c = 1; c <= n; c++) 
		for (int l = 1; l <= k[c]; l++)
			ord[c][l] = l;

	for (int c = 1; c <= n; c++) {
		curr = c;
		sort(ord[c] + 1, ord[c] + k[c] + 1, cmp);

		int t = 0;
		ordsum[c] = 0;
		for (int l = 1; l <= k[c]; l++) {
			int elt = ord[c][l];
			t += p[c][elt];
			ordsum[c] += t * w[c][elt];
		}
	}

	for (int c = 1; c <= n; c++)
		cls[c] = c;

	sort(cls + 1, cls + n + 1, cmp);
	for (int c = 1; c <= n; c++)
		cout << cls[c] << " ";
	cout << endl;
	return 0;
}