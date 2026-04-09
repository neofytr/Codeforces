#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: littleGirl
// URL: https://codeforces.com/contest/276/problem/C
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<int> freq(n + 1);
    int l, r;
    while (q--) {
        cin >> l >> r;
        l--, r--;
        freq[l] += 1;
        freq[r + 1] -= 1;
    }
    for (int r = 1; r <= n; r++)
        freq[r] += freq[r - 1];

    sort(freq.begin(), freq.end(), greater<int>());
    sort(arr.begin(), arr.end(), greater<int>());

    int sum = 0;
    for (int r = 0; r < n; r++)
        sum += freq[r] * arr[r];
    cout << sum << endl;
    return 0;
}