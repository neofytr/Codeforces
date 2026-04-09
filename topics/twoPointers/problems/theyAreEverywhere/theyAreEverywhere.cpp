#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: theyAreEverywhere
// URL: https://codeforces.com/problemset/problem/701/C
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string str;
    cin >> str;

    unordered_map<char, int> freq;
    for (char c : str)
        freq[c]++;
    int uniqueCount = static_cast<int>(freq.size());

    // a segment [l, r] is good iff it contains uniqueCount unique characters
    // the goodness property is super-segment monotonic

    unordered_map<char, int> runningFreq;
    int mini = LLONG_MAX;
    int runningUniqueCount = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        if (!runningFreq[str[r]]) {
            runningUniqueCount++;
        }
        runningFreq[str[r]]++;
        while (l <= r && runningUniqueCount == uniqueCount) {
            if (!(--runningFreq[str[l++]]))
                runningUniqueCount--;
        }
        if (l > 0) {
            int tmp = runningUniqueCount;
            if (!runningFreq[str[l - 1]])
                tmp++;
            if (tmp == uniqueCount) // the minimum length good segment ending at r is [l - 1, r]
                mini = min(mini, r - l + 2);
        }
    }

    if (mini == LLONG_MIN)
        mini = 0;
    cout << mini << endl;

    return 0;
}