#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, s;
    cin >> n >> s;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    // each good segment either ends at index 0, 1, ..., n - 1
    // these cases are mutually exclusive and exhaustive

    long long left = 0;
    long long right = 0;
    long long count = 0;
    long long sum = 0;

    while (left < n)
    {
        while (right < n && sum + arr[right] < s)
        {
            sum += arr[right++];
        }

        count += (n - right);
        sum -= arr[left++];
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}