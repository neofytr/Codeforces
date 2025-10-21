#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;

    if (l2 > r1) {
        cout << -1 << endl;
        return 0;
    }

    if (r2 < l1) {
        cout << -1 << endl;
        return 0;
    }

    if (r2 >= r1) {
        if (l2 >= l1)
            cout << l2 << " " << r1 << endl;
        else
            cout << l1 << " " << r1 << endl;
        return 0;
    }

    if (r1 > r2) {
        if (l2 >= l1)
            cout << l2 << " " << r2 << endl;
        else
            cout << l1 << " " << r2 << endl;
    }
    return 0;
}