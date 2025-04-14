#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<int> &arr, int target)
{
    int left = 0;
    int right = arr.size() - 1;

    int mid;

    while (left <= right)
    {
        mid = left + (right - left) / 2; // (left + right) / 2 can cause overflow
        if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else if (arr[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}