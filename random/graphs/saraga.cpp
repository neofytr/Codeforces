#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string s, t;
	cin >> s >> t;

	int n = s.size(), m = t.size();
	vector<int> S(n + 1), T(m + 1);
	for (int r = 1; r <= n; r++)
		S[r] = s[r - 1] - 'a';
	for (int r = 1; r <= m; r++)
		T[r] = t[r - 1] - 'a';


	return 0;
}