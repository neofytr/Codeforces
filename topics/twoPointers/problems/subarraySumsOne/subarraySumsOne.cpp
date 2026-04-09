#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: subarraySumsOne
// URL: https://cses.fi/problemset/task/1660
// Difficulty: easy
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;
    vector<int> arr(n);

    // array of n positive integers
    // count the number of subarrays having sum x
    for (int &val : arr)
        cin >> val;

    int left = 0, right = 0;
    int sum = 0;
    int cnt = 0;
    while (left < n) {
        while (right < n && sum < x)
            sum += arr[right++];
        if (sum == x)
            cnt++; // [left, right - 1] is one such subarray
        sum -= arr[left++];
    }
    cout << cnt << endl;
    return 0;
}