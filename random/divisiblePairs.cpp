#include <bits/stdc++.h>
using namespace std;

#define int long long

struct pair_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(const pair<int,int>& p) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t a = p.first, b = p.second;
        return splitmix64(a + (b << 32) + FIXED_RANDOM);
    }
};



void solve() {
	int n, x, y;
	cin >> n >> x >> y;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	int cnt = 0;
	unordered_map<pair<int, int>, int, pair_hash> mp;
	for (int j = 1; j <= n; j++) {
		int needy = arr[j] % y;
		int needx = (x - arr[j] % x) % x;

		cnt += mp[{needx, needy}];
		mp[{arr[j] % x, arr[j] % y}]++;
	}

	cout << cnt << endl;
}

int32_t main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
} 