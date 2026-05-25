#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> build_sa(string &s) {
	int n = s.length();
	vector<int> sa(n + 1), rank(n + 1), tmp(n + 1), t(n + 1), cnt(n + 1);


	for (int k = 1; k < n; k <<= 1) {
		int ptr = 1;
		for (int i = n - k + 1; i <= n; i++)
			t[ptr++] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] - k >= 1)
				t[ptr++] = sa[i] - k;
		fill(count.begin(), count.end(), 0);
		for (int i = 1; i <= n; i++)
	}
	return sa;
}

int32_t main() {
	string s; cin >> s;
	for (int e : build_sa(s))
		cout << e << " ";
	cout << endl;
	return 0;
}