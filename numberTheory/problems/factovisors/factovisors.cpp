#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while(cin >> n >> m) {
        int orig_m = m;
        if (m == 0) {
            cout << orig_m << " does not divide " << n << "!\n";
            continue;
        }
        if (m < 0) m = -m; // work with positive

        bool divides = true;

        for (int r = 2; r * r <= m; r++) {
            if (m % r == 0) {
                int cnt = 0;
                while (m % r == 0) {
                    cnt++;
                    m /= r;
                }

                int power_in_fact = 0;
                long long temp = n;
                while (temp) {
                    power_in_fact += temp / r;
                    temp /= r;
                }

                if (cnt > power_in_fact) {
                    divides = false;
                    break;
                }
            }
        }

        if (m > 1) { // leftover prime factor
            int power_in_fact = 0;
            long long temp = n;
            while (temp) {
                power_in_fact += temp / m;
                temp /= m;
            }
            if (power_in_fact < 1)
                divides = false;
        }

        if (divides)
            cout << orig_m << " divides " << n << "!\n";
        else
            cout << orig_m << " does not divide " << n << "!\n";
    }
    return 0;
}
