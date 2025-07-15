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

    long long left = 0;
    long long right = 0;
    long long max_len = -1;
    long long sum = 0;

    while (right < n)
    {
        sum += arr[right]; // include the element at ptr right

        // if sum exceeds s, keep removing elements from left
        while (sum > s)
        {
            sum -= arr[left++];
        }

        max_len = max(max_len, right - left + 1);
        right++; // go the next element at right
    }

    cout << max_len << endl;
    return 0;
}
