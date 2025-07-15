#include <bits/stdc++.h>
using namespace std;

bool isGood(vector<int> &arr, int x) {
    if (x <= -1) {
        return false;
    }

    if (x >= arr.size()) {
        return true;
    }

    return arr[x] >= 5;
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    // n >= 1

    // we have a function isGood(int x) that returns 1 if the element at index x is good or 0 if it's not good (bad)

    // it's given that the function isGood is increasing, that is, in the array, if index x is good, then so is index x + 1, for all but the last index

    // from this, we can infer that either all the numbers in the array are bad (not good), or there is an index in the array
    // x which is good, and it's true that all indexes x <= i <= n - 1 are good

    // we implicitly assume that f(-1) is always bad and f(n) is always good (these are fictitious elements)

    // we are to find the minimum index in the array which is good
    // we start with left = -1 and right = n
    // we uphold the following invariant at each loop iteration
    // f(left) = 0 (not good)
    // f(right) = 1 (good)
    // we stop when right = left + 1
    // in this case, the index we're searching for is right
    // if there are no elements in the array which are good, then right = n and left = n - 1 at the end

    int left = -1;
    int right = n;
    int mid;
    while (right != left + 1) {
        mid = left + (right - left) / 2;
        if (isGood(arr, mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    if (right == n) {
        cout << "NO\n";
    } else {
        cout << "YES " << right << endl;
    }

    // this method is useful to solve a large class of problems where the indexes of an array
    // can be associated with either a value 0 or 1 by a monotone function f

    return EXIT_SUCCESS;
}
