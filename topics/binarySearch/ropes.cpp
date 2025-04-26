#include <bits/stdc++.h>
using namespace std;

bool isGood(const vector<double> &arr, const double len, const int k) {
    if (len <= -1) {
        return true;
    } else if (len >= 1e7) {
        return false;
    }

    long long sum = 0;
    for (const double index: arr) {
        sum += floor(index / len);
        if (sum >= k) {
            return true;
        }
    }

    return false;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<double> arr(n);
    for (double &val: arr) {
        cin >> val;
    }

    double left = -1;
    double right = 10000000 + 1;
    for (int index = 0; index < 100; index++) {
        const double mid = left + (right - left) / 2;
        if (isGood(arr, mid, k)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    cout << fixed << setprecision(10) << left << endl; // fix precision
    return EXIT_SUCCESS;
}
