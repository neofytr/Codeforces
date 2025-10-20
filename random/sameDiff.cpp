#include <bits/stdc++.h>
using namespace std;

#define int long long

#define FAST_IO()                                                                                                                                                                                                                                                                                                                                                                                              \
    ios::sync_with_stdio(false);                                                                                                                                                                                                                                                                                                                                                                               \
    cin.tie(NULL)

/*

num &= (num - 1) turns off the last 1 in num (for num > 0)

*/

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

// generating the next string in lexicographic order is equivalent to
// adding 1 in base 26
void next(string &str) {
    int n = (int)str.length();
    int r = n - 1;
    while (r >= 0 && str[r] == 'z') // these will generate a carry when 1 is added
        str[r] = 'a', r--;

    if (r >= 0)
        str[r]++; // increment the first non carry generating character
    else
        str = string(n + 1, 'a'); // if everything is a z
}

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    // number of pair of indices (i, j) such that i < j && arr[j] - arr[i] = j - i
    // iff i < j && arr[j] - j == arr[i] - i
    // iff i < j && p[j] == p[i]

    int cnt = 0;
    vector<int> p(n + 1);
    unordered_map<int, int> mp;
    for (int r = 1; r <= n; r++)
        p[r] = arr[r] - r, cnt += mp[p[r]], mp[p[r]]++;
    cout << cnt << endl;
}

int32_t main() {
    FAST_IO();

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}