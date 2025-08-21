#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: threeParts
// URL: https://codeforces.com/problemset/problem/1006/C
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<int> prefix(n, 0);
    vector<int> suffix(n + 1, 0);

    prefix[0] = arr[0];
    for (int index = 1; index < n; index++)
        prefix[index] = prefix[index - 1] + arr[index];
    for (int index = n - 1; index >= 0; index--)
        suffix[index] = suffix[index + 1] + arr[index];

    int l = 0, r = n - 1;
    int maxi = 0;
    while (l < r) {
        if (prefix[l] < suffix[r])
            l++;
        else if (prefix[l] > suffix[r])
            r--;
        else {
            maxi = max(maxi, prefix[l]);
            l++;
            r--;
        }
    }

    cout << maxi << endl;

    return 0;
}