#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, target;
    cin >> n >> target;

    cin >> target;

    vector<int> arr(n);

    for (int &val : arr)
    {
        cin >> val;
    }

    // we need to find the smallest number's index in the array greater than target
    // array is sorted
    int ans = -1;

    int left = n - 1;
    int right = 0;
    int mid;

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (arr[mid] > target)
        {
            ans = mid;
            right = mid - 1; // search if there is any number less than the current but
            // also greater than target
        }
        else if (arr[mid] <= target)
        {
            left = mid + 1;
        }
    }

    if (ans == -1)
    {
        cout << "NO\n-1\n";
    }
    else
    {
        cout << "YES\n"
             << arr[ans] << "\n";
    }

    return EXIT_SUCCESS;
}