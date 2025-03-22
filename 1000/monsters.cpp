#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int64_t n, k;
    cin >> n >> k;

    vector<pair<int64_t, int64_t>> health(n);

    int64_t temp;
    for (int64_t index = 0; index < n; index++)
    {
        cin >> temp;
        health[index] = {temp, index};
    }

    sort(health.begin(), health.end(), [](const pair<int64_t, int64_t> &a, const pair<int64_t, int64_t> &b)
         { return a.first < b.first; });

    while (true)
    {
        if (health[n - 1].first <= 0)
        {
            break;
        }

        int64_t max = health[n - 1].first;
        int64_t index_of_min_index = n - 1;
        for (int64_t index = n - 1; index >= 0; index--)
        {
            if (health[index].first == max)
            {
                if (health[index].second < health[index_of_min_index].second)
                {
                    index_of_min_index = index;
                }
            }
            else
            {
                break;
            }
        }

        health[index_of_min_index].first -= k;
        if (health[index_of_min_index].first <= 0)
        {
            cout << health[index_of_min_index].second + 1 << " ";
        }

        sort(health.begin(), health.end(), [](const pair<int64_t, int64_t> &a, const pair<int64_t, int64_t> &b)
             { return a.first < b.first; });
    }

    cout << endl;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}
