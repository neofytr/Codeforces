#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t rangeUpdate() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<int> update(n + 1, 0);
    int q;
    cin >> q;
    while (q--) {
        // for each query (l, r, x)
        // we need to increment all the elements in the array segment [l, r] by x
        int l, r, x;
        cin >> l >> r >> x; // l,r are 0-based indexes
        update[l] += x;
        update[r + 1] -= x;
    }

    // propagate all updates and finally update the real array
    arr[0] += update[0];
    for (int index = 1; index < n; index++) {
        update[index] += update[index - 1];
        arr[index] += update[index];
    }

    for (const int val : arr)
        cout << val << " ";
    cout << endl;
    return 0;
}

void twoDimPrefix() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> arr(n, vector<int>(m));
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            cin >> arr[row][col];
        }
    }

    // we want to answer queries like the following
    // (r1, c1) , (r2, c2) where n > r2 >= r1 >= 0 && m > c2 >= c1 >= 0
    // we have the give the sum of the elements in the subrectangle of the matrix arr bounded by the
    // points (r1, c1) and (r2, c2)

    vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));
    // for a, b >= 1, prefix[a][b] is the sum of the elements in the subrectangle of the matrix arr
    // bounded by the points (0, 0) and (a - 1, b - 1)
    // for !a || !b, prefix[a][b] = 0

    // it can be easily proved that this loop traverses the matrix in the correct order
    // so that for each (row, col), the values on the RHS are already correctly computed when (row, col) comes on the LHS
    for (int row = 1; row <= n; row++)
        for (int col = 1; col <= m; col++) // the following recurrence can easily be proven
            prefix[row][col] = prefix[row - 1][col] + prefix[row][col - 1] - prefix[row - 1][col - 1] + arr[row - 1][col - 1];

    // array to prefix -> add 1 to coordinate (used when querying)
    // prefix to array -> subtract 1 from coordinate (used when building prefix array)
    int q;
    cin >> q;
    while (q--) {
        int r1, c1;
        cin >> r1 >> c1;
        int r2, c2;
        cin >> r2 >> c2;
        // this recurrence can also be easily proven
        cout << prefix[r2 + 1][c2 + 1] - prefix[r1][c2 + 1] - prefix[r2 + 1][c1] + prefix[r1][c1] << endl;
    }
}

int32_t main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // for 1 <= r <= n, prefix[r] is the sum of the first r elements of the array arr, i.e, sum of elements
    // from index 0 to r - 1
    // prefix[0] is the sum of first 0 elements of the array arr, which is just 0
    // so sum of values from index 0 to some index k, where 0 <= k < n is just prefix[k + 1]
    // for 1 <= r <= n, prefix[r] = sum of first r elements of the array
    //                             = sum of the first r - 1 elements of the array + rth element of the array
    //                             = prefix[r - 1] + arr[r - 1]
    vector<int> prefix(n + 1, 0);
    for (int index = 1; index <= n; index++)
        prefix[index] = prefix[index - 1] + arr[index - 1];

    // if we want the sum of the elements in the segment [l, r] for 1 <= l <= r < n of the array arr ->
    // sum(l, r) = sum(0, r) - sum(0, l - 1)
    // sum(l, r) = prefix[r + 1] - prefix[l]

    // for the sum of the elements in the segment [0, r] ->
    // sum(0, r) = prefix[r + 1] = prefix[r + 1] - prefix[0]

    // so all in all,
    // if we want the sum of the elements in the segment [l, r] of the array arr for 0 <= l <= r < n ->
    // sum(l, r) = prefix[r + 1] - prefix[l]

    int q;
    cin >> q;
    int l, r;
    while (q--) {
        cin >> l >> r; // 0-indexed
        cout << prefix[r + 1] - prefix[l] << endl;
    }

    // we to use prefix sums?
    // 1. range sum
    // 2. xors, products (be careful with 0 in the array)
    // 3. frequency count (compute frequency of each character in each prefix)
    // 4. static update/queries (not a combination of both, which is called dynamic update/queries)

    // 5. combine with binary search (if all elements of the array are >= 0, then, the prefix sum array is monotonically increasing; vice versa when all elements <= 0)
    // 6. subtree/path sum in a tree
    // 7. 2D prefix sums
    // 8. Sum over Subsets (n-dimensional prefix sums)

    /*
     * Suppose you want to find the max(pref[r + 1] - pref[l] for 0 <= l <= r < n)
     * For this, do the following ->

    int mini = pref[0];
    int maxi = LLONG_MIN;
    for (int r = 0; r < n; r++) {
        maxi = max(maxi, pref[r + 1] - mini);
        mini = min(mini, pref[r]);
    }
    */

    /*
     * Suppose you want to count the number of segments [l, r] where 0 <= l <= r < n such that
     * prefix[r + 1] - prefix[l] == target for some target.
     * For this, do the following ->
     *
     * int count = 0;
     * unordered_map<int, int> mp;
     *
     * mp[prefix[0]]++;
     * for (int r = 0; r < n; r++) {
     *      int trg = prefix[r + 1] - target;
     *      count += mp[trg];
     *      mp[prefix[r + 1]]++;
     * }
     *
     */
    return EXIT_SUCCESS;
}

// also consider this example and especially the index thing in this

int32_t ans() {
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    vector<int> cows(n);
    for (int &val : cows)
        cin >> val;

    vector<int> prefix(n + 1, 0);
    for (int r = 1; r <= n; r++)
        prefix[r] += prefix[r - 1] + cows[r - 1];

    // for any 0 <= l <= r < n such that sum[l, r] % 7 = 0
    //, sum[l, r] % 7 = 0 iff (prefix[r + 1] - prefix[l]) % 7 iff prefix[r + 1] % 7 = prefix[l] % 7

    vector<int> c(n + 1, 0);
    for (int r = 1; r <= n; r++)
        c[r] = prefix[r] % 7;

    // Let 0 <= r < n
    // For any 0 <= l <= r, sum[l, r] % 7 = 0 is possible iff c[r + 1] = c[l]
    // So the number of subarrays ending at r that have sum divisible by 7 are precisely
    // the number of values in the range {c[0], c[1], ..., c[r]} such that c[x] = c[r + 1] for 0 <= x <= r

    // So, the maximum possible length subarray ending at r that has its sum divisible
    // by 7 is the subarray arr[l, r] where 0 <= l <= r such that c[l] is the first occurrence
    // of c[r + 1] in the range {c[0], ..., c[r]}

    // int cnt = 0;

    // at the beginning of each iteration, mp[k] is the number of values in the range [c[0], c[r]]
    // that have their values equal to k
    // unordered_map<int, int> mp;
    // mp[c[0]] = 1; // to maintain the invariant initially
 
    // for (int r = 0; r < n; r++) {
    //     int target = c[r + 1];
    //     cnt += mp[target];
 
    //     mp[target]++; // to maintain the invariant for the next iteration
    // }

    // cout << cnt << endl;

    // at the beginning of iteration r = a, mp[k] is the 
    // index of first occurence of k in the range {c[0], ..., c[a]}
    vector<int> mp(7, -1);
    int maxi = 0;

    // maintaining the invariant initially
    mp[c[0]] = 0;
    for (int r = 0; r < n; r++) {
        int target = c[r + 1];
        if (mp[target] != -1) 
            maxi = max(maxi, r - mp[target] + 1);
        else 
            mp[target] = r + 1; // since it's c[r + 1], we set the indexes according
            // to the range {c[0], ..., c[r + 1]}
    }

    cout << maxi << endl;
    return 0;
}