#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    // n >= 3

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    // the elements in the array first increase then decrease
    // find the maximum element in the array

    int left = 0;
    int right = n - 1;
    int ans = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        ans = arr[mid];

        if (arr[mid] <= arr[mid + 1]) // mid + 1 will always be in bound
        {
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