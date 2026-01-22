#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX_N (int)(5 * 1e2)
#define MAX_K (int)(1e2)
#define MAX_T (int) (MAX_N * MAX_K)

int p[MAX_T + 1];
int w[MAX_T + 1];
int l[MAX_T + 1];

auto cmp = [](int a, int b) {
    return p[a] * w[b] < p[b] * w[a];
};


int32_t main() {
	freopen("student.in", "r", stdin);
	freopen("student.out", "w", stdout);

	int n;
	cin >> n;

	int t = 0;
	int k;
	for (int r = 1; r <= n; r++)
		cin >> k, t += k;

	for (int r = 1; r <= t; r++)
		cin >> p[r];
	for (int r = 1; r <= t; r++)
		cin >> w[r];
	for (int r = 1; r <= t; r++)
		l[r] = r;

	sort(l + 1, l + t + 1, cmp);

	int c = 0;
	int e = 0;
	for (int r = 1; r <= t; r++) {
		int elt = l[r];
		e += p[elt];
		c += e * w[elt];
	}

	cout << c << endl;
	for (int r = 1; r <= t; r++)
		cout << l[r] << " ";
	cout << endl;
}