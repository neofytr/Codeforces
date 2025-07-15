#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;

    vector<long long> arr(n);
    for (long long &val : arr)
    {
        cin >> val;
    }

    // we need to find how many times x occurs in the range [l, r - 1]
    unordered_map<long long, vector<int>> count; // count[r] stores all the indexes of the element r in the array arr in ascending order
    for (int index = 0; index < n; index++)
    {
        count[arr[index]].push_back(index);
    }

    int l, r;
    long long x;
    while (q--)
    {
        cin >> l >> r >> x;

        vector<int> find = count[x];
        if (!find.size())
        {
            cout << 0 << endl;
            continue;
        }

        // we need to find the min index x in find such that find[x] >= l
        int left = 0;
        int right = find.size() - 1;
        int minimum = -1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (find[mid] >= l)
            {
                right = mid - 1;
                minimum = mid;
            }
            else
            {
                left = mid + 1;
            }
        }

        // find the maximum index x in find such that find[x] < r
        left = 0;
        right = find.size() - 1;
        int maximum = -1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (find[mid] < r)
            {
                maximum = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        cout << maximum - minimum + 1 << endl;
    }

    return EXIT_SUCCESS;
}