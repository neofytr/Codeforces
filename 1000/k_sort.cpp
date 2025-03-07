#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        vector<ll> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        // Find the target non-decreasing array
        vector<ll> target = a;
        for (int i = 1; i < n; i++)
        {
            target[i] = max(target[i], target[i - 1]);
        }

        // Count how many times each position needs to be incremented
        vector<ll> increments;
        for (int i = 0; i < n; i++)
        {
            ll diff = target[i] - a[i];
            if (diff > 0)
            {
                // Add this position diff times to our list
                for (ll j = 0; j < diff; j++)
                {
                    increments.push_back(i);
                }
            }
        }

        ll answer = 0;

        // Process in batches - each batch is one operation
        for (int i = 0; i < increments.size(); i += n)
        {
            // For each operation, we take min(n, remaining) positions
            ll k = min(n, (ll)increments.size() - i);
            answer += k + 1; // Cost of the operation is k+1
        }

        cout << answer << "\n";
    }

    return 0;
}