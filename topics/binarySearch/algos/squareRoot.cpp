#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

int main() {
    double x;
    cin >> x;

    if (x == 0) {
        cout << 0 << endl;
        return EXIT_SUCCESS;
    }

    if (x == 1) {
        cout << 1 << endl;
        return EXIT_SUCCESS;
    }

    // we want to find sqrt(x)

    // we will maintain the invariant
    // left * left < x
    // right * right >= x
    // also, if r * r >= x, then so is any y >= r

    // this maintains the invariant since x != 0 or 1
    double left = 0;
    double right = x;

    for (int i = 0; i < 100; i++) {
        double mid = left + (right - left) / 2;
        if (mid * mid < x)
            left = mid;
        else
            right = mid;
    }

    cout << setprecision(12) << right << endl;
    return EXIT_SUCCESS;
}