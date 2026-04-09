#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    set<int> s;
    for (int r = 1; r * r <= n; r++)
        if (!(n % r))
            s.insert(r), s.insert(n / r);
    for (const int e : s)
        cout << e << endl;
    return 0;
}