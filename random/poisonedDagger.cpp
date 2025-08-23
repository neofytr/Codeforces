// https://codeforces.com/problemset/problem/1613/C
#include <bits/stdc++.h>
using namespace std;

#define int long long

bool can(int k, const vector<int> &arr, int h) {
    int damage = 0;
    for (int i = 0; i < arr.size() - 1; i++) {
        damage += min(arr[i + 1] - arr[i], k);
        if (damage >= h)
            return true;
    }
    damage += k; // last
    return damage >= h;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        int n, h;
        cin >> n >> h;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        int left = 0;         // this won't work
        int right = 3 * 1e18; // this will most definitely work

        while (right != left + 1) {
            if (const int mid = left + (right - left) / 2; can(mid, arr, h))
                right = mid;
            else
                left = mid;
        }

        cout << right << endl;
    }
    return 0;
}