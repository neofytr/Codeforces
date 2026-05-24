#include <bits/stdc++.h>
using namespace std;

#define int long long

struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM =
			chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

void solve() {
	int n; cin >> n;
	int a;
	unordered_map<int, int, custom_hash> f;
	for (int i = 1; i <= n; i++) cin >> a, f[a]++;

	int maxi = -1;
	for (int i = 1; i <= n; i++) {
		int cnt = 0;
		for (int j = 1; j * j <= i; j++)
			if (!(i % j)) {
				cnt += f[j];
				if (j != i / j) cnt += f[i / j];
			}

		maxi = max(maxi, cnt);
	}

	cout << maxi << endl;
}

int32_t main() {
    std::ios_base::sync_with_stdio(false);    
    std::cin.tie(NULL);
	int t; cin >> t;
	while (t--) solve();
	return 0;
}