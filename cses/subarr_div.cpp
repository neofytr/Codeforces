// https://cses.fi/problemset/task/1662

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> arr(n + 1, 0);

    for (int index = 1; index <= n; index++)
    {
        cin >> arr[index];
    }

    long long curr_sum = 0;
    long long count = 0;

    map<long long, int> prefix;
    prefix[0] = 1;

    for (int index = 1; index <= n; index++)
    {
        // we construct the prefix sum along with computing the differences
        // since we only need the prefix sums to the left of the current one
        // for the algorithm

        curr_sum += arr[index];
        long long target = (curr_sum % n + n) % n; // since we can have negative numbers too, we use this formula for the remainder

        if (prefix.count(target))
        {
            count += prefix[target];
            prefix[target]++;
        }
        else
        {
            prefix[target] = 1;
        }
    }

    cout << count << endl;
}