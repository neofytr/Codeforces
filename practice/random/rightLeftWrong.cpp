// https://codeforces.com/problemset/problem/2000/D

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N (size_t)(2 * 1e5 + 1)
int arr[MAX_N];
int prefix[MAX_N];

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        for (int i = 1; i <= n; i++)
            prefix[i] = prefix[i - 1] + arr[i - 1];

        string str;
        cin >> str;

        int l = 0;
        int r = n - 1;
        int ans = 0;
        while (l < r) {
            while (l < r && str[l] == 'R')
                l++;
            while (l < r && str[r] == 'L')
                r--;

            if (str[l] == 'L' && str[r] == 'R') {
                ans += prefix[r + 1] - prefix[l];
            }
            l++, r--;
        }

        cout << ans << endl;
    }
    return 0;
}