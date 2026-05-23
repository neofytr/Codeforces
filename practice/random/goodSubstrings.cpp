#include <bits/stdc++.h>
using namespace std;

#define int long long

using u64 = uint64_t;
u64 hash_string(const string &s) {
	const u64 P = 1315423911ULL;
	u64 h = 0;
	for (char c : s) {
		h = h * P + (unsigned char)c + 1;
	}
	return h;
}

int32_t main() {
	string s; cin >> s;
	int n = s.length();
	vector<int> str(n + 1);
	for (int i = 1; i <= n; i++) str[i] = s[i - 1] - 'a';

	cin >> s;
	vector<int> f(26);
	for (int i = 0; i < 26; i++)
		f[i] = s[i] - '0';

	unordered_map<int, bool> g;
	int k; cin >> k;
	int l = 1; int cnt = 0;
	int res = 0;
	for (int r = 1; r <= n; r++) {
		if (!f[str[r]]) cnt++;
		while (l <= r && cnt > k) {
			if (!f[str[l]]) cnt--;
			l++;
		}

		if (l <= r) {
			string j;
			for (int i = r; i >= l; i--) {
				j.insert(j.begin(), str[i] + 'a');
				if (!g[hash_string(j)]) g[hash_string(j)] = true, res++;
			}
		}
	}

	cout << res << endl;
	return 0;
}