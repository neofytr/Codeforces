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

int32_t main() {
	int q; cin >> q;

	set<int> s;
	s.insert(0);
	unordered_map<int, int, custom_hash> f;
	while (q--) {
		string t; cin >> t;
		if (t == "+") {
			int x; cin >> x;
			s.insert(x);			
		} else {
			int k; cin >> k;
			int m = *s.rbegin();
			for (int i = f[k]; i * k <= m + k; i++)
				if (s.find(i * k) == s.end()) {
					cout << i * k << endl;
					f[k] = i;
					break;
				}
		}
	}

	// We iterate over any multiple of k in the for loop at most once (since we
	// maintain the map f), and only iterate through those multiples which are
	// actually present in the set S.
	
	// For any element x ∈ S, it can be touched in the loop when we process
	// a query with k such that:
	//
	//     x = i * k
	//
	// i.e. when k is a divisor of x.
	
	// Therefore each element x ∈ S can be touched at most once for each
	// divisor of x.
	
	// Thus the total number of iterations of the for loop across all queries
	// is bounded by:
	//
	//     Σ d(x)   for all x ∈ S
	//
	// where d(x) is the number of divisors of x.
	
	// The number of divisors of any number ≤ 1e9 is at most about 1344,
	// and for most numbers is < 100.
	
	// Therefore:
	//
	//     total loop iterations ≤ 100 * |S|     (very safe bound)
	
	// Each iteration performs a set lookup:
	//
	//     s.find(...) → O(log |S|)
	
	// Thus the total complexity of all queries is bounded by:
	//
	//     O(100 * |S| * log |S|)
	//
	// which simplifies to:
	//
	//     O(|S| log |S|)
	return 0;
}