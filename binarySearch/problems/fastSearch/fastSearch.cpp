#include <bits/stdc++.h>
#include <vector>
using namespace std;

// Problem: fastSearch
// URL: https://codeforces.com/edu/course/2/lesson/6/1/practice/contest/283911/problem/D
// Difficulty: medium
// Tags:
// Strategy:

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    sort(arr.begin(), arr.end());
    int k;
    cin >> k;
    int l, r;
    while (k--) {
        cin >> l >> r;

        // l <= r

        int left = -1; // arr[left] < l
        int right = n; // arr[right] >= l
        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < l)
                left = mid;
            else
                right = mid;
        }

        if (right == n) {
            // all elements in the array are < l
            cout << 0 << " ";
            continue;
        }

        int minL = right;

        left = -1; // arr[left] <= r
        right = n; // arr[right] > r
        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= r)
                left = mid;
            else
                right = mid;
        }

        if (left == -1) {
            // all elements in the array are > r
            cout << 0 << " ";
            continue;
        }

        cout << left - minL + 1 << " ";
    }

    cout << endl;
    return 0;
}