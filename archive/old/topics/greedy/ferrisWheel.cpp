#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    long long x;
    cin >> n >> x;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    long long count = 0;

    sort(arr.begin(), arr.end());
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        if (arr[left] + arr[right] <= x)
        {
            count++;
            left++;
            right--;
            continue;
        }

        right--;
        count++; // send off that right child in a single gondola since we won't get a
        // traveller for it
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}