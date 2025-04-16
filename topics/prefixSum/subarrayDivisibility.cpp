#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> arr(n);
    vector<long long> prefix(n + 1);
    prefix[0] = 0;

    for (long long &val : arr)
    {
        cin >> val;
    }

    for (int index = 1; index <= n; index++)
    {
        prefix[index] = (prefix[index - 1] + arr[index - 1]) % n;
    }

    unordered_map<int, long long> map;
    map[0] = 1;
    long long count = 0;

    for (int index = 1; index <= n; index++)
    {
        if (map.count(prefix[index]))
        {
            // if already present
            count += map[prefix[index]];
        }

        map[prefix[index]]++;
    }

    cout << count << endl;
}