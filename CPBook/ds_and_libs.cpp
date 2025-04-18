#include <bits/stdc++.h>
using namespace std;

void sorting()
{
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    // sort in non-decreasing order
    sort(arr.begin(), arr.end(), [](const int a, const int b)
         { return a < b; });

    // another way for non-increasing
    sort(arr.begin(), arr.end());

    // sort in non-increasing order
    sort(arr.begin(), arr.end(), [](const int a, const int b)
         { return a > b; });

    // another way for non-increasing
    sort(arr.rbegin(), arr.rend());
}

int binarySearch()
{
    int n, target;
    cin >> n >> target;

    vector<int> arr(n);
    for (int &val : arr)
    {
        cin >> val;
    }

    sort(arr.begin(), arr.end());

    // returns iterator to the first element that is not less than target
    auto first = lower_bound(arr.begin(), arr.end(), target);
    int first_index = first - arr.begin();

    // returns iterator to the first element that is greater than target
    auto second = upper_bound(arr.begin(), arr.end(), target);
    int second_index = second - arr.begin();

    // checks if the target exists in the array
    if (binary_search(arr.begin(), arr.end(), target))
    {
        return first_index;
    }
    else
    {
        return -1;
    }
}