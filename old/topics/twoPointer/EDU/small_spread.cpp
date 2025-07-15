#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    long long left = 0;
    long long right = 0;
    long long count = 0;

    multiset<long long> num; // keeps (possibly duplicate) elements in sorted order

    while (left < n)
    {
        // count number of good segments starting at left

        // expand segment as much as possible to the right
        while (right < n)
        {
            num.insert(arr[right]);

            long long min_elt = *num.begin();
            long long max_elt = *num.rbegin();

            if (max_elt - min_elt > k)
            {
                // undo the changes and stop; there's no point going forward
                num.erase(num.find(arr[right]));
                break;
            }
            else
            {
                right++;
            }
        }

        count += (right - left);

        num.erase(num.find(arr[left++]));
    }

    cout << count << endl;
    return 0;
}
