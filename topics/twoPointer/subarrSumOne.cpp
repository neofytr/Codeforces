#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, x;
    cin >> n >> x;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    long long left = 0;
    long long right = 0;
    long long sum = 0;
    long long count = 0;

    while (left < n)
    {
        // count the number of subarrays having sum x starting at left
        while (right < n && sum + arr[right] <= x)
        {
            sum += arr[right++];
        }

        // sum <= right
        if (sum == x)
        {
            count++;
        }

        sum -= arr[left++];
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}