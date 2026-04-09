// https://codeforces.com/group/MWSDmqGsZm/contest/223339/problem/U
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, w;
    cin >> n >> w;

    vector<int> weights(n), values(n);
    for (int index = 0; index < n; index++)
        cin >> weights[index] >> values[index];

    long long maxVal = LLONG_MIN;
    for (int subset = 0; subset < (1 << n); subset++)
    {
        long long currWt = 0, currVal = 0;
        for (int bit = 0; bit < n; bit++)
        {
            if (subset & (1 << bit))
            {
                currWt += weights[bit];
                currVal += values[bit];
            }
        }

        if (currWt <= w && currVal > maxVal)
            maxVal = currVal;
    }

    cout << maxVal << endl;
    return EXIT_SUCCESS;
}