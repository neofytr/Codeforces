#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: goodSubarrays
// URL: https://codeforces.com/contest/1398/problem/C
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string str;
        cin >> str;

        // a segment [l, r] of the string str is good iff the sum of the elements in this segment = the number of elements in the segment
        // we define an array arr of length n such that
        // arr[i] = str[i] - 1 for all 0 <= i < n

        // a segment [l, r] of the string str is good iff the sum of elements in the array arr segment [l, r] = 0
        //                                            iff prefix[r + 1] - prefix[l] = 0
        //                                            iff prefix[r + 1] = prefix[l]

        // any segment [l, r] where 0 <= l <= r < n of the string str is good iff prefix[r + 1] = prefix[l]
        // for each 0 <= r < n, we count all such 0 <= l <= r such that prefix[r + 1] = prefix[l]
        vector<int> arr(n);
        for (int index = 0; index < n; index++)
            arr[index] = str[index] - '0' - 1;
        vector<int> prefix(n + 1, 0);
        for (int index = 1; index <= n; index++)
            prefix[index] = prefix[index - 1] + arr[index - 1];

        unordered_map<int, int> freq;
        // for any 0 <= r < n, let
        // S(r) = {prefix[f] | 0 <=  f <= r}
        // T(r) = (prefix[0], ..., prefix[r])

        // we maintain that
        // at the start of any iteration r = k of the following loop
        // freq[x] is the number of times x appears in the sequence T(k) for all x in S(k)
        // for any 0 <= k < n

        freq[0] = 1; // maintain the invariant initially
        int count = 0;
        for (int r = 0; r < n; r++) {
            int x = prefix[r + 1];
            count += freq[x];
            freq[x]++;
        }
        cout << count << endl;
    }
}