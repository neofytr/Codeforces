// https://codeforces.com/problemset/problem/1343/C

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        int sum = 0;
        int i = 0;
        while(i < n) {
            int j = i;

            int maxi = LLONG_MIN, mini = LLONG_MAX;
            while(j < n && arr[j] * arr[i] > 0)
                maxi = max(maxi, arr[j]), j++;

            sum += maxi;
            i = j;
        }

        cout << sum << endl;
    }
    return EXIT_SUCCESS;
}