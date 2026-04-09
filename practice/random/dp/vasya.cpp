#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int pa[MAX + 1];
int pb[MAX + 1];
int str[MAX + 1];

int32_t main() {
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;
    for (int r = 1; r <= n; r++)
        str[r] = s[r - 1] - 'a'; // a is 0 and b is 1

    pa[0] = 0;
    for (int r = 1; r <= n; r++)
        pa[r] += pa[r - 1] + (!str[r] ? 1 : 0);

    pb[0] = 0;
    for (int r = 1; r <= n; r++)
        pb[r] += pb[r - 1] + (str[r] ? 1 : 0);

    // a subarray str[l, r] is good iff the number of bs in it <= k, i.e, pb[r] - pb[l - 1] <= k
    // we are to find the largest length good subarray

    // the property good is subsequence monotonic
    int l = 1;
    int maxib = LLONG_MIN;
    for (int r = 1; r <= n; r++) {
        while (l <= r && pb[r] - pb[l - 1] > k)
            l++;
        if (l <= r)
            maxib = max(maxib, r - l + 1);
    }

    int maxia = LLONG_MIN;
    l = 1;
    for (int r = 1; r <= n; r++) {
        while (l <= r && pa[r] - pa[l - 1] > k)
            l++;
        if (l <= r)
            maxia = max(maxia, r - l + 1);
    }

    if (maxia == LLONG_MIN && maxib == LLONG_MIN) {
        cout << 1 << endl;
        return 0;
    }
    cout << max(maxia, maxib) << endl;
    return 0;
}