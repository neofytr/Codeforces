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

        if (arr[0] >= 0) {
            // the maximum length alternating sequence will start with a positive number
            int i = 0;
            int maxPosCons = arr[0];
            int maxNegCons = LLONG_MIN;
            int sum = 0;
            while (i < n) {
                while (i < n && arr[i] >= 0)
                    maxPosCons = max(maxPosCons, arr[i++]);

                if (maxPosCons != LLONG_MIN)
                    sum += maxPosCons;
                maxPosCons = LLONG_MIN;
                while (i < n && arr[i] < 0)
                    maxNegCons = max(maxNegCons, arr[i++]);
                if (maxNegCons != LLONG_MIN)
                    sum += maxNegCons;
                maxNegCons = LLONG_MIN;
            }
            cout << sum << endl;
        } else {
            // the maximum length alternating sequence will start with a negative number
            int i = 0;
            int maxNegCons = arr[0];
            int maxPosCons = LLONG_MIN;
            int sum = 0;
            while (i < n) {
                while (i < n && arr[i] < 0)
                    maxNegCons = max(maxNegCons, arr[i++]);
                if (maxNegCons != LLONG_MIN)
                    sum += maxNegCons;
                maxNegCons = LLONG_MIN;
                while (i < n && arr[i] >= 0)
                    maxPosCons = max(maxPosCons, arr[i++]);
                if (maxPosCons != LLONG_MIN)
                    sum += maxPosCons;
                maxPosCons = LLONG_MIN;
            }
            cout << sum << endl;
        }
    }
    return EXIT_SUCCESS;
}