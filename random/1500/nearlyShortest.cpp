#include <bits/stdc++.h>
using namespace std;

#define int long long

struct RollingHash {
private:
	const int MOD = 1e9 + 7;
	const int p = 31;
	vector<int> hash, pw;
	int n;

public:
	RollingHash(vector<int> &str, int len) {
		hash.resize(len + 1);
		pw.resize(len + 1);
		n = len;

		pw[0] = 1, hash[0] = 0;
		for (int i = 1; i <= n; i++) 
			pw[i] = pw[i - 1] * p % MOD, hash[i] = (hash[i - 1] * p % MOD + str[i]) % MOD;
	}

	int get(int l, int r) {
		return (hash[r] - hash[l - 1] * pw[r - l + 1] % MOD + MOD) % MOD;
	}
};	

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	vector<int> str(n + 1);
	for (int i = 1; i <= n; i++) str[i] = s[i - 1] - 'a' + 1;
		
	vector<int> divs(1);
	for (int i = 1; i * i <= n; i++)
		if (!(n % i)) {
			divs.push_back(i);
			if (i != n / i) divs.push_back(n / i);
		}

	sort(divs.begin() + 1, divs.end());
	int sz = divs.size() - 1;

	RollingHash rh(str, n);
	for (int i = 1; i <= sz; i++) {
		unordered_map<int, pair<int, int>> f;
		int d = divs[i];
		for (int j = d; j <= n; j += d) {
			int hash = rh.get(j - d + 1, j);
			auto [cnt, right] = f[hash];
			f[hash] = {cnt + 1, j - d + 1};
		}


		if (f.size() == 1) {
			cout << d << endl;
			return;
		}

		if (f.size() == 2) {
			auto [h1, l1] = *f.begin();
			auto [h2, l2] = *(++f.begin());

			auto [cnt1, left1] = l1;
			auto [cnt2, left2] = l2;

			if (cnt1 > 1 && cnt2 > 1) continue;
			int g = 0;
			for (int k = 1; k <= d; k++)
				if (str[left1 + k - 1] != str[left2 + k - 1]) g++;

			if (g <= 1) {
				cout << d << endl;
				return;
			}
		}
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
} 