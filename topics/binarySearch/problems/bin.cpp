#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, target;
    cin >> n >> target;

    // it is given that n >= 2

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    // it is given that arr is sorted

    // define
    // f(x) = 0 if arr[x] < target
    //      = 1 if arr[x] >= target
    // for 0 <= x <= n - 1

    // we argue that f is monotonically increasing
    // suppose that this is not the case, that is, there is x, y in the range [0, n - 1]
    // such that x < y and f(x) > f(y)
    // this implies that f(x) = 1 and f(y) = 0
    // thus, arr[x] >= target and arr[y] < target
    // thus, arr[x] > arr[y] for x < y
    // this is impossible since the array is sorted in non-decreasing order

    // we define
    // f(-1) = 0
    // f(n) = 1

    // then, since f is monotonically increasing, there is a unique -1 < x <= n such that
    // f(r) = 0 for all r < x
    // and f(r) = 1 for all r >= x

    // we are to find this x
    // this is the minimum index for which f(r) = 1, for any -1 <= r <= n

    // we maintain the invariant that
    // f(left) = 0, f(right) = 1, and left < right

    int left = -1;
    int right = n;

    while (right != left + 1)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }

    if (left == -1)
    {
        // all elements in the array are >= target
        cout << "All elements >= " << target << endl;
    }

    if (right == n)
    {
        cout << "All elements < " << target << endl;
    }

    cout << "Minimum index for " << target << " in the array is " << right << endl;
    return EXIT_SUCCESS;
}