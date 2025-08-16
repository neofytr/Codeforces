#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

#define int long long

// Problem: threeSum
// URL: https://cses.fi/problemset/task/1641
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;
    vector<pair<int, int>> arr(n);
    int index = 1;
    for (auto &val : arr) {
        cin >> val.first;
        val.second = index++;
    }

    // all elements of the array are non-negative
    // we are to find three distinct indexes in arr with sum == x
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++) {
        int sum = x - arr[i].first;
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            int s = arr[left].first + arr[right].first;
            if (s < sum)
                left++;
            else if (s > sum)
                right--;
            else {
                cout << arr[i].second << " " << arr[left].second << " " << arr[right].second << endl;
                return EXIT_SUCCESS;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}