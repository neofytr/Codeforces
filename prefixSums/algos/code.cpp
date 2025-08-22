#include <bits/stdc++.h>
using namespace std;

#define int long long

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
    return EXIT_SUCCESS;
}