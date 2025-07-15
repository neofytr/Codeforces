#include <bits/stdc++.h> // include all standard c++ libraries
using namespace std;

// function to check if we can cut the ropes into at least 'k' pieces
bool isGood(const vector<double> &arr, const double len, const int k) {
    long long sum = 0; // to count total pieces
    for (const double index: arr) {
        // iterate over each rope length
        sum += floor(index / len); // add how many pieces we get from this rope
        if (sum >= k) {
            // if already enough pieces, no need to check further
            return true;
        }
    }
    return false; // not enough pieces
}

int main() {
    int n, k;
    cin >> n >> k; // input number of ropes and required number of pieces

    vector<double> arr(n);
    for (double &val: arr) {
        cin >> val; // input the length of each rope
    }

    // initialize search space: we can search lengths between 0 and 1e8
    // we choose left to be good and right to be bad initially
    // len is 0 is always good, and since all the array elements are less than or equal to 1e7, we choose right to be 1e8
    // we always maintain the invariant that left is good and right is bad
    // we end when we get the desired accuracy; 100 iterations will do it
    double left = 0;
    double right = 1e8;

    // binary search for the maximum possible length
    for (int index = 0; index < 100; index++) {
        // 100 iterations for high precision
        const double mid = left + (right - left) / 2; // find the middle value
        if (isGood(arr, mid, k)) {
            // if it is possible to cut with length mid
            left = mid; // try to find a bigger length
        } else {
            right = mid; // otherwise try smaller lengths
        }
    }

    // output the result with 10 decimal places
    cout << fixed << setprecision(10) << left << endl; // fix precision
    return EXIT_SUCCESS;
}
