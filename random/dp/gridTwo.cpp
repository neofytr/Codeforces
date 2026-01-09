#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define MOD (int)(1e9 + 7)

int32_t main() {
    int h, w, n;
    cin >> h >> w >> n;

    int x, y;
    set<pair<int, int>> blocked;
    while (n--)
        cin >> y >> x, blocked.insert({y, x});

    return 0;
}