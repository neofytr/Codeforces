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
    return EXIT_SUCCESS;
}