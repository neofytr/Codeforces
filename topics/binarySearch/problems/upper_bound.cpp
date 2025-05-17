#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, target;
    cin >> n >> target;

    // we need to find the maximum index x in the array such that arr[x] <= target

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    int left = -1;
    int right = n;

    while (right != left + 1)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }

    // left == -1 -> all elements in the array > target
    cout << left << endl;

    // method 2
    left = 0;
    right = n - 1;
    int ans = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target)
        {
            ans = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    cout << ans << endl;

    return EXIT_SUCCESS;
}