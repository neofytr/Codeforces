#include <bits/stdc++.h>
using namespace std;

bool isGood(const vector<int> &arr, const int x) {
    if (x <= -1) {
        return true;
    } else if (x >= arr.size()) {
        return false;
    }

    if (arr[x] <= 5) {
        return true;
    }

    return false;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    // n >= 1
    // we have a function isGood(int x) that returns 1 if the element at index x is good, 0 otherwise (if it's bad)

    // the function isGood is decreasing, that is, if index x is good, then so is x - 1, for all but the first index

    // from this we can infer that if there is an index x in the array that is good, then all the indexes 0 <= i <= x
    // will be good

    // we implicitly assume that f(-1) is always good and f(n) is always bad (these are fictitious elements)

    // we are to find the maximum element in the array which is good
    // initially, we have
    // left = -1 and right = n
    // we maintain the following invariant
    // isGood(left) = 1
    // isGood(right) = 0
    // we stop when right = left + 1
    // in this case, the index we're searching for is left
    // if there are no elements in the array which are good, then left = -1 and right = 0 at the end

    int left = -1;
    int right = n;
    int mid;
    while (right != left + 1) {
        mid = left + (right - left) / 2;
        if (isGood(arr, mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (left == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES " << left << endl;
    }

    return EXIT_SUCCESS;
}
