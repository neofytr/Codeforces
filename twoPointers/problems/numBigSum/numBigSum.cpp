#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: numBigSum
// URL: Not provided
// Difficulty: Unknown
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s;
    cin >> n >> s;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // all elements of the array are >= 1

    int left = 0;
    int right = 0;
    int sum = 0;
    int cnt = 0;
    while (left < n) {
        if (right < left)
            right = left;
        while (right < n && sum < s)
            sum += arr[right++];
        if (sum >= s) {
            // all segments [left, r] where n > r >= right - 1 are good segments (since all elements of array are >= 0)
            // and they are all the good segments that start at left
            cnt += (n - right + 1);
            sum -= arr[left];
        }
        left++;
    }
    cout << cnt << endl;
    return 0;
}