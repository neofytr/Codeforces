#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
using namespace std;

#define int long long

// Problem: ternaryString
// URL: Not provided
// Difficulty: https://codeforces.com/problemset/problem/1354/B
// Tags:
// Strategy:

void solve() {
    string str;
    cin >> str;

    int n = (int)str.length();
    // we are to find the length of the shortest contiguous substring of s that contains 1, 2, 3 atleast once
    int left = 0;
    int right = 0;
    int countOne = 0;
    int countTwo = 0;
    int countThree = 0;

    int mini = LLONG_MAX;
    while (left < n) {
        while (right < n && (!countOne || !countTwo || !countThree)) {
            if (str[right] == '1')
                countOne++;
            else if (str[right] == '2')
                countTwo++;
            else
                countThree++;
            right++;
        }

        if (countOne && countTwo && countThree) {
            mini = min(mini, right - left);
        }
        if (str[left] == '1')
            countOne--;
        else if (str[left] == '2')
            countTwo--;
        else
            countThree--;
        left++;
    }

    if (mini == LLONG_MAX)
        cout << 0 << endl;
    else
        cout << mini << endl;
    return;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}