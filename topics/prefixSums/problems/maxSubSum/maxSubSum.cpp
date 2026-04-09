#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: maxSubSum
// URL: https://codeforces.com/contest/2107/problem/C
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        string str;
        cin >> str;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        // let m is the current maximum subarray sum
        // there are only three possible cases ->
        // m < k
        // in this case, since k <= 10^12, and we can insert upto 10^18, if there's a free space
        // somewhere, we can make the maximum subarray sum = k by just putting k into one of the empty
        // places, and zero in all other places,
        // however, if there's no free space anywhere, we can't make the maximum subarray sum = k

        // m > k
        // in this case, all the subarrays which have sum > k should have a space inside them.
        // otherwise, we can't make the maximum subarray sum = k

        // m = k
        // we can always make the maximum subarray sum = k in this case (by putting a zero in every empty place, if any)

    }
    return 0;
}