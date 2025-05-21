#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    int left = 0;
    int right = 0;
    int count = 0;

    unordered_map<long long, int> freq;

    while (left < n)
    {
        // move to the maximum right until we can have <= k unique elements
        while (right < n && freq.size() + (!freq.count(arr[right]) ? 1 : 0) <= k)
        {
            freq[arr[right++]]++;
        }

        count += (right - left);

        if (!(--freq[arr[left]]))
        {
            freq.erase(freq.find(arr[left]));
        }

        left++;
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}