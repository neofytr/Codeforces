#include <bits/stdc++.h>
using namespace std;

bool func(const double r, const double x) {
    return r * r < x;
}

int main() {
    double x;
    // x > 0
    cin >> x;

    // we have to estimate the square root of x
    // f[r] = 0 if square of r < x; 1 if square of r >= x
    // f is monotonic
    // f[0] = 0
    // f[x + 1] = 1

    // we maintain the invariant that
    // f[left] = 0
    // f[right] = 1

    double left = 0;
    double right = static_cast<double>(x) + 1;

    for (int index = 0; index < 100; index++) {
        double mid = left + (right - left) / 2;
        if (func(mid, x)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    cout << setprecision(20) << right << endl;
    return EXIT_SUCCESS;
}
