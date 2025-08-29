#include <bits/stdc++.h>
using namespace std;

void work() {
    long long x, y, z;
    cin >> x >> y >> z;

    if ((x - z) & 1) {
        cout << "NO\n";
        return;
    }
    if (!((x - y) & 1)) {
        cout << "YES\n";
        return;
    }
    if (y < z)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;
    while (q--)
        work();
}
