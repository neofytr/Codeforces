#include <bits/stdc++.h>
using namespace std;

#define int long long 

struct SplitMix64 {
    size_t operator()(uint64_t x) const noexcept {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        x = x ^ (x >> 31);
        return x;
    }
};

std::unordered_map<int, int, SplitMix64> mp;


int32_t main() {
	int n, x;
	cin >> n >> x;

	vector<int> arr(n);
	for (int &val : arr)
		cin >> val;

	vector<int> p(n + 1, 0);
	for (int r = 1; r <= n; r++)
		p[r] += p[r - 1] + arr[r - 1];

	// Let 0 <= r < n
	// For any 0 <= l <= r, sum[l, r] = x iff (p[r + 1] - p[l]) = x iff p[r + 1] = p[l] + x
	// So, the number of subarrays ending at r is the number of elements in the range {p[0] + x, p[1] + x, ..., p[r] + x}
	// that are equal to p[r + 1]

	// at the beginning of iteration r = k, mp[a] is the number of elements in the
	// range {p[0] + x, ..., p[r] + x} that are equal to a
	unordered_map<int, int, SplitMix64> mp;

	int cnt = 0;
	// maintain the invariant initially
	mp[x + p[0]]++;
	for (int r = 0; r < n; r++) {
		int target = p[r + 1];
		cnt += mp[target];
		mp[target + x]++;
	}

	cout << cnt << endl;
	return 0;
}