#include <bits/stdc++.h>
using namespace std;

bool binary_search_recursive(const vector<long long> &arr, const long long target, const long long left,
                             const long long right) {
    if (right == left + 1) {
        return right < arr.size() && arr[right] == target;
    }

    long long mid = left + (right - left) / 2;
    if (arr[mid] >= target) {
        return binary_search_recursive(arr, target, left, mid);
    } else {
        return binary_search_recursive(arr, target, mid, right);
    }
}


bool binary_search(const vector<long long> &arr, const long long target) {
    // we assume arr[-1] < target and arr[arr.size()] >= target

    // in the array, since it's sorted
    // if arr[index] >= target, then arr[index + 1] >= target, for all 0 <= index < arr.size()
    // if arr[index] < target, then arr[index - 1] < target for all 0 <= index < arr.size()

    // let f(index) = 0 if arr[index] < target, and 1 otherwise
    // it is not possible that there are 0 <= r, s < arr.size() such that r < s and f(s) < f(r)
    // that is, f is monotonically increasing
    // then, since f(-1) = 0 and f(arr.size()) = 1, there is an index alpha such that
    // f(index) = 0 for all index < alpha
    // and f(index) = 1 for all index >= alpha
    // Thus, arr[alpha] is the minimum index in the array whose value is greater than equal to target

    // we maintain the invariant that
    // for every index <= left, arr[index] < target
    // for every index >= right, arr[index] >= target

    // initially
    long long left = -1; // we assume arr[-1] < target
    long long right = static_cast<long long>(arr.size()); // we assume arr[right] >= target

    // at the end, right = left + 1

    // in this case, if target is found in the array, then right will be in the range 0 to arr.size() - 1
    // and will indicate the index of first occurrence of target in the array

    // if right == arr.size() at the end, then left = arr.size() - 1 and all the elements in the array are
    // strictly less than the target

    // if left == -1 and right = 0, then either arr[right] == target or arr[right] > target
    // in the first case, we found target in the array at the first position; in the latter case, all the elements
    // in the array are strictly greater than target

    // so right will indicate the occurrence (and that too first occurrence) of the target in the array
    // if and only if right < arr.size() and arr[right] == target
    // otherwise if either of these two doesn't hold, the target doesn't exist in the array

    while (right != left + 1) {
        const long long mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            right = mid;
        } else {
            left = mid;
        }
    }

    if (right < arr.size() && arr[right] == target) {
        return true;
    }

    return false;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &val: arr) {
        cin >> val;
    }

    long long query;
    while (k--) {
        cin >> query;
        if (binary_search_recursive(arr, query, -1, n)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return EXIT_SUCCESS;
}
