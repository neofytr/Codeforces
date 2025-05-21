#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    long long m;
    cin >> n >> m;

    vector<long long> weight(n), profit(n);
    vector<tuple<double, long long, long long>> unit(n);

    for (int i = 0; i < n; ++i)
        cin >> weight[i];

    for (int i = 0; i < n; ++i)
    {
        cin >> profit[i];
        unit[i] = make_tuple((double)profit[i] / weight[i], profit[i], weight[i]);
    }

    sort(unit.begin(), unit.end(), [](const auto &a, const auto &b)
         {
             return std::get<0>(a) > std::get<0>(b); // descending order
         });

    int index = 0;
    double max_prof = 0;
    while (index < n && m > 0)
    {
        auto [ratio, prof, wt] = unit[index];
        long long quantity = min(m, wt);
        max_prof += quantity * ratio;
        m -= quantity;
        index++;
    }

    cout << fixed << setprecision(10) << max_prof << endl;
    return EXIT_SUCCESS;
}
