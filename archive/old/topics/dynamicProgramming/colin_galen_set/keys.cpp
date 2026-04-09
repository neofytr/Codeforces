#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, p, k;
    cin >> n >> k >> p;

    vector<long long> people(n);
    for (long long &val : people)
    {
        cin >> val;
    }

    vector<long long> keys(k);
    for (long long &val : keys)
    {
        cin >> val;
    }

    sort(people.begin(), people.end());
    sort(keys.begin(), keys.end());

    // we need to assign people to keys in increasing order to get an optimal solution; crossing over
    // would definetely lead to a worse solution that this

    vector<vector<long long>> dp();

    return EXIT_SUCCESS;
}