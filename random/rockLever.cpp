#include <bits/stdc++.h>
using namespace std;

#define int long long

int countOnes(long long num) {
    if (!num)
        return 0;

    int count = 0;
    while (true) {
        num &= (num - 1);
        count++;
        if (!num)
            return count;
    }

    return 0;
}

int countTrailingZeroes(long long num) {
    if (!num)
        return sizeof(long long) * 8;

    return countOnes(num - 1) - countOnes(num) + 1;
}

int countLeadingZeroes(long long num) {
    if (!num)
        return sizeof(long long) * 8;

    while (true) {
        if (!(num & (num - 1)))
            return (sizeof(long long) * 8 - countTrailingZeroes(num) - 1);
        else
            num &= (num - 1);
    }

    return 0;
}

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    int cnt = 0;
    unordered_map<int, int> bt;
    for (int r = 0; r < n; r++) {
        cnt += bt[countLeadingZeroes(arr[r])];
        bt[countLeadingZeroes(arr[r])]++;
    }
    cout << cnt << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}