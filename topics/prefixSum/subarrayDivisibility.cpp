#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    unordered_map<long long, long long> map;
    map[0] = 1;
    long long count = 0;
    long long val;
    long long sum = 0;

    for (int index = 1; index <= n; index++)
    {
        cin >> val;
        sum = (sum + val % n + n) % n;
        if (map.count(sum))
        {
            // if already present
            count += map[sum];
        }

        map[sum]++;
    }

    cout << count << endl;
}