#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    if (n <= 1)
    {
        return EXIT_FAILURE;
    }

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    // the given array first increases and then decreases
    // find the maximum element in it in logn time

    // a peak always exists in this case

    int left = 0;
    int right = n - 1;
    int mid;
    int max = arr[0];

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (mid == 0 || arr[mid] > arr[mid - 1])
        {
            if (arr[mid] > max)
            {
                max = arr[mid];
            }

            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    cout << max << endl;
}