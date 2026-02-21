#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e3)
#define MAX_K (int)(25)
#define INF (int)(1e12)

int dp[MAX + 1][MAX_K + 1];
int arr[MAX + 1];
int cost[MAX + 1][MAX + 1];

struct slidingMedian {
	multiset<int> lower, upper;
	void rebalance() {
		if (lower.size() - upper.size() == 2) {
			int x = *lower.rbegin();
			lower.erase(--lower.end());
			upper.insert(x);
			return;
		}

		if (lower.size() - upper.size() == 1 && !upper.empty())
			if (*lower.rbegin() > *upper.begin()) {
				int x = *lower.rbegin(), y = *upper.begin();
				lower.erase(--lower.end()), upper.erase(upper.begin());
				upper.insert(x), lower.insert(y);
				return;
			}

		if (upper.size() - lower.size() == 1) {
			int x = *upper.begin();
			upper.erase(upper.begin());
			lower.insert(x);
		}
	}

	void insert(int x) {
		lower.insert(x);
		rebalance();
	}

	void remove(int x) {
		if (lower.empty() && upper.empty()) return;

		if (!lower.empty() && lower.find(x) != lower.end()) {
			lower.erase(lower.find(x));
			rebalance();
			return;
		}

		if (!upper.empty() && upper.find(x) != upper.end()) {
			upper.erase(upper.find(x));
			rebalance();
			return;
		}
	}

	int median() {
		if (lower.empty()) return -1;
		return *lower.rbegin();
	}
};

struct doubleHeap {
	multiset<int> lower, upper;
	int lowersum = 0, uppersum = 0;

	void rebalance() {
		if (lower.size() - upper.size() == 2) {
			int x = *lower.rbegin();
			lower.erase(--lower.end());
			upper.insert(x), lowersum -= x, uppersum += x;
			return;
		}

		if (lower.size() - upper.size() == 1 && !upper.empty()) 
			if (*lower.rbegin() > *upper.begin()) {
				int x = *lower.rbegin();
				lower.erase(--lower.end());
				upper.insert(x); lowersum -= x, uppersum += x;
				int y = *upper.begin();
				upper.erase(upper.begin()), uppersum -= y, lowersum += y;
				lower.insert(y);
			}
	}

	void insert(int x) {
		if (lower.empty()) {
			lower.insert(x);
			lowersum += x;
			return;
		}

		lower.insert(x);
		lowersum += x;
		rebalance();
	}

	int median() {
		return *lower.rbegin();
	}
};

int32_t main() {
	int n, k; cin >> n >> k;
	for (int r = 1; r <= n; r++) cin >> arr[r];

	// dp[i][j] is the minimum cost for arr[1, i] using j intervals
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= k; j++)
			dp[i][j] = INF;

	for (int r = 1; r <= n; r++)
		cout << arr[r] << " ";
	cout << endl;

	slidingMedian med;
	for (int r = 1; r <= n; r++) {
		med.insert(arr[r]);
		cout << med.median() << " ";
	}
	cout << endl;
	for (int r = 1; r <= n; r++) {
		med.remove(arr[r]);
		cout << med.median() << " ";
	}
	cout << endl;

	for (int i = 1; i <= n; i++) {
		doubleHeap dh;
		for (int j = i; j <= n; j++) {
			dh.insert(arr[j]);
			cost[i][j] = dh.median() * dh.lower.size() - dh.lowersum + dh.uppersum - dh.median() * dh.upper.size();
		}
	}

	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = INF;
		for (int j = 1; j <= min(i, k); j++) {
			// the jth interval ends at arr[i] but can start
			// at any 1 <= z <= i
			for (int z = 1; z <= i; z++) 
				dp[i][j] = min(dp[i][j], cost[z][i] + dp[z - 1][j - 1]);
		}
	}

	cout << dp[n][k] << endl;
	return 0;
}