#include <bits/stdc++.h>
using namespace std;

struct Item
{
    double ratio;
    long long profit;
    long long weight;

    bool operator<(const Item &other) const
    {
        return ratio > other.ratio; // descending order
    }
};

int main()
{
    int n;
    long long m;
    cin >> n >> m;

    vector<Item> items(n);

    for (int i = 0; i < n; ++i)
        cin >> items[i].weight;

    for (int i = 0; i < n; ++i)
    {
        cin >> items[i].profit;
        items[i].ratio = (double)items[i].profit / items[i].weight;
    }

    sort(items.begin(), items.end());

    double max_profit = 0;

    for (const auto &item : items)
    {
        if (m == 0)
            break;

        long long take = min(m, item.weight);
        max_profit += take * item.ratio;
        m -= take;
    }

    cout << fixed << setprecision(10) << max_profit << '\n';
    return 0;
}
