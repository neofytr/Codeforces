#include <bits/stdc++.h>
using namespace std;

bool func(double x, double c) {
    return (x * x + sqrt(x) - c) >= 0;
}

int main() {
    // find a number x such that x^2 + root(x) = c
    // relative or absolute error should not be more than 10^-6
    double c;
    cin >> c;

    // func is an increasing function
    // it is false(0) upto a real number x (not including x) and then true(1) afterwards for every real number >= x
    // so we can use binary search here to get an estimate of this x

    // we maintain the invariant that func(left) is false and func(right) is true
    double left = 0;
    double right = sqrt(c);

    for (int index = 0; index < 100; index++) {
        double mid = left + (right - left) / 2;
        if (func(mid, c)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << setprecision(20) << right << endl;
    return EXIT_SUCCESS;
}
