#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int a = -1, b = -1, c = -1;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                a = i;
                n /= i;
                break;
            }
        }

        if (a == -1) {
            cout << "NO\n";
            continue;
        }

        for (int i = a + 1; i * i <= n; i++) {
            if (n % i == 0) {
                b = i;
                n /= i;
                break;
            }
        }

        c = n;

        if (b != -1 && c > 1 && c != a && c != b) {
            cout << "YES\n";
            cout << a << " " << b << " " << c << "\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
