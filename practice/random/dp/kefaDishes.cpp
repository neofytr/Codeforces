#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(18)
#define KMAX (int)(MAX * (MAX - 1))

// dp[mask][r] is the maximum satisfaction we can get by eating mask with the
// last element eaten being r
int dp[(1ll << MAX)][MAX];
int arr[MAX];

map<pair<int, int>, int> f;
int32_t main() {
	int n, m, k;
	cin >> n >> m >> k;

	for (int r = 0; r < n; r++) cin >> arr[r];

	int x, y, c;
	for (int r = 1; r <= k; r++)
		cin >> x >> y >> c, f[{x - 1, y - 1}] = c;
	
	for (int mask = 0; mask < (1ll << n); mask++) {
		if (__builtin_popcountll(mask) > m) continue; // not a valid state since we have
		// to eat exactly m dishes

        for (int last = 0; last < n; last++)
          if (mask & (1ll << last)) // this can be the last dish
            for (int next = 0; next < n; next++)
              if (!(mask & (1ll << next))) // this can be the next dish
                dp[mask | (1ll << next)][next] =
                    max(dp[mask | (1ll << next)][next],
                        f[{last, next}] + dp[mask][last]);
    }

    int maxi = LLONG_MIN;
    for (int mask = 0; mask < (1ll << n); mask++) {
    	if (__builtin_popcountll(mask) != m) continue;

    	int sum = 0;
    	for (int bit = 0; bit < n; bit++)
    		if (mask & (1ll << bit))
    			sum += arr[bit];

    	int mn = LLONG_MIN;
    	for (int last = 0; last < n; last++)
    		if (mask & (1ll << last))
    			mn = max(mn, dp[mask][last]);
    	sum += mn;
    	maxi = max(maxi, sum);
    }

    cout << maxi << endl;
	return 0;
}