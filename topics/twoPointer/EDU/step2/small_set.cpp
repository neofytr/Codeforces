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
    long long count = 0;
    int size = 0;

    unordered_map<long long, int> freq;

    while (left < n)
    {
        // move to the maximum right until we can have <= k unique elements
        while (right < n && (size + (!freq[arr[right]] ? 1 : 0)) <= k)
        {
            if (!freq[arr[right]])
            {
                size++;
            }

            freq[arr[right]]++;
            right++;
        }

        count += (right - left);

        if (!(--freq[arr[left]]))
        {
            size--;
        }

        left++;
    }

    cout << count << endl;
    return EXIT_SUCCESS;
}