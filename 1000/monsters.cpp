#include <iostream>
#include <vector>
#include <set>
using namespace std;

void solve()
{
    int64_t n, k;
    cin >> n >> k;

    multiset<pair<int64_t, int64_t>> health;

    for (int64_t index = 0; index < n; index++)
    {
        int64_t temp;
        cin >> temp;
        health.insert({temp, index});
    }

    while (!health.empty())
    {
        auto it = prev(health.end());
        int64_t max_health = it->first;
        int64_t min_index = it->second;
        health.erase(it);

        if (max_health <= 0)
            break;

        max_health -= k;

        if (max_health > 0)
        {
            health.insert({max_health, min_index});
        }
        else
        {
            cout << min_index + 1 << " ";
        }
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
