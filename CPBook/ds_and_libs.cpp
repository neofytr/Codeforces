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

void binar